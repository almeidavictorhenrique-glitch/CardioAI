#include <Arduino.h>
#include <WiFi.h>
#include <WiFiClientSecure.h>
#include <PubSubClient.h>

#include "DHT.h"
#include "FS.h"
#include "LittleFS.h"
#include "emqx_ca.h"

#include <Wire.h>
#include <Adafruit_MPU6050.h>
#include <Adafruit_Sensor.h>
#include "secrets.h"

// ==========================================
// CARDIOIA - FASE 3
// Monitoramento cardiaco simulado com ESP32
// ==========================================

// Definicao dos pinos
#define DHT_PIN 15
#define DHT_TYPE DHT22
#define BUTTON_PIN 4
#define LED_PIN 19    
#define MPU_SDA 21 // Pinos do MPU6050 (comunicacao I2C)
#define MPU_SCL 22

// Inicializacao do sensor
DHT dht(DHT_PIN, DHT_TYPE);

// Inicializacao do sensor de movimento
Adafruit_MPU6050 mpu;

// ==========================================
// VARIAVEIS DE MONITORAMENTO
// ==========================================

int bpm = 0;
int lastButtonState = HIGH;
int currentButtonState = HIGH;

float temperature = 0.0;
float humidity = 0.0;

// Dados de aceleracao do MPU6050
float accelerationX = 0.0;
float accelerationY = 0.0;
float accelerationZ = 0.0;


// ==========================================
// CONEXAO WIFI E MQTT
// ==========================================

const char* WIFI_SSID = "Wokwi-GUEST";
const char* WIFI_PASSWORD = "";

const char* MQTT_SERVER = "xc01fe91.ala.us-east-1.emqxsl.com";
const int MQTT_PORT = 8883;

const char* MQTT_USER = "cardioai_esp32";

// Preencha a senha diretamente neste arquivo, no seu computador.
// Nao compartilhe essa senha.
const char* MQTT_PASSWORD = MQTT_PASSWORD_SECRET;
const char* MQTT_TOPIC = "cardioai/telemetria";

WiFiClientSecure espClient;
PubSubClient mqttClient(espClient);

unsigned long lastMqttAttempt = 0;
const unsigned long MQTT_RETRY_INTERVAL = 5000;

unsigned long lastWiFiAttempt = 0;
const unsigned long WIFI_RETRY_INTERVAL = 10000;

// ==========================================
// FUNCOES DE CONEXAO WIFI E MQTT
// ==========================================

void conectarWiFi() {

  if (WiFi.status() == WL_CONNECTED) {
    return;
  }

  if (millis() - lastWiFiAttempt < WIFI_RETRY_INTERVAL) {
    return;
  }

  lastWiFiAttempt = millis();

  Serial.println("Tentando conectar ao Wi-Fi Wokwi...");

  WiFi.begin(WIFI_SSID, WIFI_PASSWORD, 6);
}

void conectarMQTT() {
  // So tenta conectar se o Wi-Fi estiver conectado
  if (WiFi.status() != WL_CONNECTED) {
    return;
  }

  // Se ja estiver conectado, nao precisa reconectar
  if (mqttClient.connected()) {
    return;
  }

  // Aguarda o intervalo entre tentativas
  if (millis() - lastMqttAttempt < MQTT_RETRY_INTERVAL) {
    return;
  }

  lastMqttAttempt = millis();

  Serial.println("Tentando conectar ao broker EMQX...");

  if (mqttClient.connect("CardioAI-ESP32", MQTT_USER, MQTT_PASSWORD)) {
    Serial.println("MQTT conectado com sucesso!");

  } else {
    Serial.print("Falha na conexao MQTT. Codigo: ");
    Serial.println(mqttClient.state());
  }
}

// ==========================================
// PUBLICACAO DOS DADOS NO MQTT
// ==========================================

bool publicarDadosMQTT() {

    if (!mqttClient.connected()) {
        Serial.println("MQTT desconectado. Dados nao enviados.");
        return false;
    }
    char mensagem[256];

    snprintf(
        mensagem,
        sizeof(mensagem),
        "{\"tempo_ms\":%lu,\"temperatura\":%.2f,\"umidade\":%.2f,\"bpm\":%d,\"aceleracao_x\":%.2f,\"aceleracao_y\":%.2f,\"aceleracao_z\":%.2f}",
        millis(),
        temperature,
        humidity,
        bpm,
        accelerationX,
        accelerationY,
        accelerationZ
    );

    if (mqttClient.publish(MQTT_TOPIC, mensagem)) {
        Serial.print("Dados enviados ao MQTT: ");
        Serial.println(mensagem);
        return true;
    }

    Serial.println("Erro ao publicar dados MQTT!");
    return false;
}


// ==========================================
// INTERVALOS DE LEITURA E CONTROLE
// ==========================================

const unsigned long DHT_INTERVAL = 2000;
const unsigned long DEBOUNCE_TIME = 50;
const unsigned long HEARTBEAT_TIMEOUT = 3000;
const unsigned long HISTORY_INTERVAL = 10000;

// ==========================================
// CONTROLE DE TEMPO
// ==========================================

unsigned long lastDHTRead = 0;
unsigned long lastButtonChange = 0;
unsigned long lastHeartbeat = 0;
unsigned long inicioMonitoramento = 0;

// Controle do armazenamento
bool storageReady = false;
bool historicoExibido = false;

// ==========================================
// ARMAZENAMENTO LOCAL - LITTLEFS
// ==========================================

void salvarDados(float temp, float umid, int batimentos,
                 float accX, float accY, float accZ) {

  if (!storageReady) {
    Serial.println("Armazenamento local indisponivel!");
    return;
  }

  File arquivo = LittleFS.open("/dados_cardio_v2.csv", FILE_APPEND);

  if (!arquivo) {
    Serial.println("Erro ao abrir arquivo para gravacao!");
    return;
  }

  // Registro dos dados em formato CSV
  arquivo.print(millis());
  arquivo.print(",");
  arquivo.print(temp, 2);
  arquivo.print(",");
  arquivo.print(umid, 2);
  arquivo.print(",");
  arquivo.print(batimentos);
  arquivo.print(",");
  arquivo.print(accX, 2);
  arquivo.print(",");
  arquivo.print(accY, 2);
  arquivo.print(",");
  arquivo.println(accZ, 2);

  arquivo.close();

  // Confere se o arquivo continua acessivel
  File teste = LittleFS.open("/dados_cardio_v2.csv", FILE_READ);

  if (teste) {
    Serial.print("Gravacao confirmada. Tamanho do arquivo: ");
    Serial.print(teste.size());
    Serial.println(" bytes");

    teste.close();
  } else {
    Serial.println("Erro ao verificar arquivo gravado!");
  }
}
// ==========================================
// LEITURA DO HISTORICO CSV
// ==========================================

void lerDados() {

  if (!storageReady) {
    Serial.println("Armazenamento local indisponivel!");
    return;
  }

  File arquivo = LittleFS.open("/dados_cardio_v2.csv", FILE_READ);

  if (!arquivo) {
    Serial.println("Erro ao abrir arquivo para leitura!");
    return;
  }

  Serial.println("\n===== HISTORICO CARDIOIA =====");

  while (arquivo.available()) {
    Serial.write(arquivo.read());
  }

  arquivo.close();

  Serial.println("\n===== FIM DO HISTORICO =====");
}

// ==========================================
// INICIALIZACAO
// ==========================================

void setup() {

  Serial.begin(115200);

  pinMode(BUTTON_PIN, INPUT_PULLUP);
  pinMode(LED_PIN, OUTPUT);

  digitalWrite(LED_PIN, LOW);

  dht.begin();

  // Inicializacao da comunicacao I2C
Wire.begin(21, 22);

// Inicializacao do MPU6050
if (!mpu.begin()) {
  Serial.println("Erro: MPU6050 nao encontrado!");
} else {
  Serial.println("MPU6050 iniciado com sucesso!");
}
  
  // Configuracao da conexao segura TLS
espClient.setCACert(EMQX_CA_CERT);

// Configuracao do broker MQTT
mqttClient.setServer(MQTT_SERVER, MQTT_PORT);

// Inicia a conexao Wi-Fi
conectarWiFi();

  // Inicializacao do sistema de arquivos local
  storageReady = LittleFS.begin(true);

  if (!storageReady) {

    Serial.println("Erro ao inicializar LittleFS!");

  } else {

    Serial.println("Armazenamento local iniciado!");

    // Criacao do arquivo CSV
    if (!LittleFS.exists("/dados_cardio_v2.csv")) {

      File arquivo = LittleFS.open(
        "/dados_cardio_v2.csv",
        FILE_WRITE
      );

      if (arquivo) {

       arquivo.println(
         "tempo_ms,temperatura,umidade,bpm,aceleracao_x,aceleracao_y,aceleracao_z"
        );

        arquivo.close();

        Serial.println("Arquivo CSV criado!");

      } else {

        Serial.println("Erro ao criar arquivo CSV!");
      }
    }
  }

  Serial.println("================================");
  Serial.println("       CARDIOIA - FASE 3");
  Serial.println("================================");
  Serial.println("Monitoramento iniciado!");

  inicioMonitoramento = millis();
}

void lerMovimento() {
  static unsigned long ultimaLeitura = 0;

  if (millis() - ultimaLeitura < 1000) {
    return;
  }

  ultimaLeitura = millis();

  sensors_event_t aceleracao, giro, temperatura;
  mpu.getEvent(&aceleracao, &giro, &temperatura);
  accelerationX = aceleracao.acceleration.x;
  accelerationY = aceleracao.acceleration.y;
  accelerationZ = aceleracao.acceleration.z;

  Serial.print("Aceleracao X: ");
  Serial.print(aceleracao.acceleration.x);

  Serial.print(" | Y: ");
  Serial.print(aceleracao.acceleration.y);

  Serial.print(" | Z: ");
  Serial.println(aceleracao.acceleration.z);
}

// ==========================================
// LOOP PRINCIPAL
// ==========================================

void loop() {

    lerMovimento();

  unsigned long currentTime = millis();

  // Mantem a conexao Wi-Fi e MQTT
if (WiFi.status() != WL_CONNECTED) {
  conectarWiFi();
} else {
  conectarMQTT();
}

if (mqttClient.connected()) {
  mqttClient.loop();
}

  // ========================================
  // 1. LEITURA DO SENSOR DHT22
  // ========================================

  if (currentTime - lastDHTRead >= DHT_INTERVAL) {

    lastDHTRead = currentTime;

    float newTemperature = dht.readTemperature();
    float newHumidity = dht.readHumidity();

    if (isnan(newTemperature) || isnan(newHumidity)) {

      Serial.println("Erro na leitura do DHT22!");

    } else {

      temperature = newTemperature;
      humidity = newHumidity;

      Serial.println("\n--- DADOS AMBIENTAIS ---");

      Serial.print("Temperatura: ");
      Serial.print(temperature);
      Serial.println(" °C");

      Serial.print("Umidade: ");
      Serial.print(humidity);
      Serial.println(" %");

      // Armazenamento dos dados na memoria local
    salvarDados(
      temperature,
      humidity,
      bpm,
      accelerationX,
      accelerationY,
      accelerationZ
    );      
    
         // Envio dos dados para o broker MQTT
      publicarDadosMQTT();
    }
  }


  // ========================================
  // 2. DETECCAO DOS BATIMENTOS
  // ========================================

  int reading = digitalRead(BUTTON_PIN);

  if (reading != lastButtonState) {
    lastButtonChange = currentTime;
  }

  if (currentTime - lastButtonChange > DEBOUNCE_TIME) {

    if (reading != currentButtonState) {

      currentButtonState = reading;

      // INPUT_PULLUP: LOW significa pressionado
      if (currentButtonState == LOW) {

        if (lastHeartbeat > 0) {

          unsigned long interval =
            currentTime - lastHeartbeat;

          // Limita a simulacao a ate 200 BPM
          if (interval >= 300 && interval <= 2000) {
            bpm = 60000 / interval;
          }
        }

        lastHeartbeat = currentTime;

        Serial.println("\n--- BATIMENTO DETECTADO ---");

        Serial.print("BPM: ");
        Serial.println(bpm);
      }
    }
  }

  lastButtonState = reading;

  // ========================================
  // 3. VERIFICACAO DE AUSENCIA DE BATIMENTOS
  // ========================================

  if (lastHeartbeat > 0 &&
      currentTime - lastHeartbeat > HEARTBEAT_TIMEOUT) {

    bpm = 0;
  }

  // ========================================
  // 4. CONTROLE DO LED DE ALERTA
  // ========================================

  if (bpm > 120 || temperature > 38.0) {

    digitalWrite(LED_PIN, HIGH);

  } else {

    digitalWrite(LED_PIN, LOW);
  }

  // ========================================
  // 5. EXIBICAO DO HISTORICO APOS 10 SEGUNDOS
  // ========================================

   if (!historicoExibido &&
      currentTime - inicioMonitoramento >= HISTORY_INTERVAL) {

    lerDados();

    historicoExibido = true;
  }

} // FIM DO LOOP


