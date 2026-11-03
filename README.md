# 🫀 CardioAI — Plataforma de Monitoramento Inteligente Cardiovascular

**FIAP | Curso Superior de Tecnologia em Inteligência Artificial**

O CardioAI é um projeto acadêmico desenvolvido para explorar a aplicação de Ciência de Dados, Inteligência Artificial, Machine Learning, Processamento de Linguagem Natural (NLP) e Internet das Coisas (IoT) no contexto da cardiologia.

O projeto evolui por fases, integrando diferentes tipos de dados e tecnologias para demonstrar como soluções inteligentes podem auxiliar no monitoramento e na análise de informações cardiovasculares.

> **Aviso:** Projeto exclusivamente educacional. Utiliza simulações e dados de demonstração. Não realiza diagnóstico médico, não substitui profissionais de saúde e não deve ser utilizado para decisões clínicas.

---

## 👨‍💻 Integrante

- Victor Henrique de Almeida — RM 657469

---

# 📌 Sumário

- [Fase 1 — Batimentos de Dados](#-fase-1--batimentos-de-dados)
- [Fase 2 — Diagnóstico Inteligente](#-fase-2--diagnóstico-inteligente)
- [Fase 3 — CardioAI Conectada](#-fase-3--cardioai-conectada)
  - [Objetivo](#-objetivo-da-fase-3)
  - [Arquitetura](#-arquitetura-da-solução)
  - [Hardware e sensores](#-hardware-e-sensores)
  - [Firmware ESP32](#-firmware-esp32)
  - [Comunicação MQTT](#-comunicação-mqtt)
  - [Armazenamento local com LittleFS](#-armazenamento-local-com-littlefs)
  - [Node-RED e dashboard](#-node-red-e-dashboard)
  - [Portal CardioAI](#-portal-cardioai)
  - [Simulação no Wokwi](#-simulação-no-wokwi)
  - [Instalação e execução](#-instalação-e-execução)
  - [Estrutura do projeto](#-estrutura-do-projeto)
  - [Resultados e validações](#-resultados-e-validações)
  - [Limitações](#-limitações-e-considerações)
- [Tecnologias utilizadas](#-tecnologias-utilizadas)
- [Considerações finais](#-considerações-finais)

---

# 🩸 FASE 1 — Batimentos de Dados

A primeira fase teve como objetivo trabalhar com diferentes tipos de dados relacionados ao contexto cardiovascular.

Foram exploradas três categorias:

### 📊 Dados numéricos

Organização e exploração de dados estruturados relacionados à saúde cardiovascular, preparando a base para análises posteriores.

### 📝 Dados textuais

Exploração de informações textuais relacionadas a sintomas e condições cardiovasculares, introduzindo conceitos de Processamento de Linguagem Natural.

### 🖼️ Dados visuais

Exploração de imagens médicas, especialmente eletrocardiogramas, considerando possibilidades futuras de aplicação de técnicas de Visão Computacional.

### ⚖️ Governança e responsabilidade

A fase também abordou aspectos importantes da utilização de dados em Inteligência Artificial, como qualidade, representatividade, privacidade, equidade e possíveis vieses.

---

# 🧠 FASE 2 — Diagnóstico Inteligente

Na segunda fase, o projeto avançou para a análise de dados textuais relacionados a sintomas e situações de risco.

O objetivo foi desenvolver uma abordagem capaz de identificar padrões em relatos simulados de pacientes e relacioná-los a possíveis condições e classificações de risco.

### 🔎 Mapa de sintomas

Foi desenvolvida uma base relacionando sintomas a possíveis associações, permitindo identificar expressões presentes em frases e relacioná-las aos registros existentes.

Exemplos:

| Sintoma relatado | Associação |
|---|---|
| Dor ou pressão no peito | Infarto |
| Cansaço e fadiga | Insuficiência cardíaca |
| Falta de ar | Angina |
| Palpitação | Arritmia |
| Inchaço nas pernas | Insuficiência cardíaca |
| Tontura | Arritmia |

### 🤖 Classificação de risco com Machine Learning

A fase também explorou a classificação automática de frases em categorias de risco.

Foram utilizados:

- TF-IDF para transformar textos em representações numéricas.
- Regressão Logística para classificação.
- Divisão entre dados de treinamento e teste.
- Avaliação de desempenho e análise de frases ambíguas.

Os experimentos permitiram observar como os modelos identificam padrões textuais e como o tamanho e a representatividade da base influenciam os resultados.

---

# ❤️ FASE 3 — CardioAI Conectada

<badge>IoT • Monitoramento • Telemetria • Visualização</badge>

A terceira fase representa a evolução do CardioAI para um ecossistema conectado, integrando sensores, microcontrolador, comunicação MQTT, armazenamento de dados e visualização em tempo real.

O foco passou a ser a coleta de informações provenientes de sensores, seu processamento no ESP32 e sua disponibilização para acompanhamento por meio de ferramentas de monitoramento.

## 🎯 Objetivo da Fase 3

Desenvolver um protótipo de monitoramento cardiovascular utilizando IoT, capaz de:

- Coletar dados de sensores conectados ao ESP32.
- Simular a medição de batimentos cardíacos.
- Monitorar temperatura e umidade.
- Capturar dados de aceleração e movimento.
- Transmitir telemetria utilizando MQTT.
- Armazenar registros localmente no ESP32.
- Exibir informações em um dashboard.
- Disponibilizar uma interface web para o ecossistema CardioAI.

## 🏗️ Arquitetura da solução

A solução foi organizada em diferentes camadas:

```text
                 ┌───────────────────────┐
                 │      SENSORES         │
                 │                       │
                 │ DHT22                 │
                 │ MPU6050               │
                 │ Botão BPM             │
                 └───────────┬───────────┘
                             │
                             ▼
                 ┌───────────────────────┐
                 │         ESP32         │
                 │                       │
                 │ Leitura dos sensores  │
                 │ Processamento         │
                 │ Firmware C++          │
                 └───────────┬───────────┘
                             │
                 ┌───────────┴───────────┐
                 │                       │
                 ▼                       ▼
        ┌─────────────────┐    ┌─────────────────┐
        │     LittleFS    │    │      MQTT       │
        │                 │    │                 │
        │ Histórico CSV   │    │ Broker EMQX     │
        │ Armazenamento   │    │ Telemetria      │
        └─────────────────┘    └────────┬────────┘
                                        │
                                        ▼
                              ┌──────────────────┐
                              │     Node-RED     │
                              │                  │
                              │ Recebimento MQTT │
                              │ Processamento    │
                              │ Histórico CSV   │
                              └────────┬─────────┘
                                       │
                                       ▼
                              ┌──────────────────┐
                              │    Dashboard     │
                              │                  │
                              │ Indicadores      │
                              │ Gráficos         │
                              └──────────────────┘
```

O portal web CardioAI complementa o projeto com uma interface desenvolvida em React.

## 🔌 Hardware e sensores

O protótipo utiliza um ESP32 DevKit C V4 como unidade central de processamento.

### Componentes utilizados

| Componente | Função |
|---|---|
| ESP32 DevKit C V4 | Processamento e comunicação |
| DHT22 | Leitura de temperatura e umidade |
| MPU6050 | Leitura de aceleração nos eixos X, Y e Z |
| Botão físico | Simulação de batimentos cardíacos |
| LED | Sinalização visual |
| Resistor de 1 kΩ | Limitação de corrente do LED |

### Conexões do ESP32

| Componente | Pino ESP32 |
|---|---|
| DHT22 | GPIO 15 |
| Botão BPM | GPIO 4 |
| LED | GPIO 19 |
| MPU6050 SDA | GPIO 21 |
| MPU6050 SCL | GPIO 22 |
| MPU6050 VCC | 3V3 |
| MPU6050 GND | GND |

O botão utiliza a configuração `INPUT_PULLUP`, com conexão entre o GPIO 4 e o GND.

O MPU6050 utiliza comunicação I2C, inicializada com:

```cpp
Wire.begin(21, 22);
```

### 📡 Dados coletados

O sistema trabalha com as seguintes informações:

- Temperatura.
- Umidade.
- BPM simulado.
- Aceleração no eixo X.
- Aceleração no eixo Y.
- Aceleração no eixo Z.

## 💻 Firmware ESP32

O firmware foi desenvolvido em C++, utilizando o ambiente PlatformIO.

Suas principais responsabilidades são:

1. Inicializar sensores e periféricos.
2. Estabelecer conexão Wi-Fi.
3. Conectar ao broker MQTT.
4. Realizar leituras periódicas.
5. Calcular o BPM a partir do intervalo entre acionamentos do botão.
6. Registrar os dados no armazenamento local.
7. Publicar os dados no broker MQTT.

### Bibliotecas utilizadas

| Biblioteca | Finalidade |
|---|---|
| WiFi | Conexão à rede sem fio |
| Wire | Comunicação I2C |
| DHT | Comunicação com o DHT22 |
| Adafruit Unified Sensor | Abstração de sensores |
| Adafruit MPU6050 | Comunicação com o acelerômetro |
| PubSubClient | Comunicação MQTT |
| LittleFS | Armazenamento local |

### Configuração do ambiente

O projeto utiliza o arquivo `platformio.ini` para definir a plataforma, placa, framework e dependências do firmware.

A compilação é realizada pelo PlatformIO.

## 📡 Comunicação MQTT

Para transmitir os dados coletados, foi utilizado o protocolo MQTT, com o broker EMQX Cloud.

O ESP32 estabelece uma conexão segura com o broker utilizando TLS.

### Configurações

| Parâmetro | Configuração |
|---|---|
| Broker | EMQX Cloud |
| Porta | 8883 |
| Protocolo | MQTT sobre TLS |
| Tópico | `cardioai/telemetria` |
| Usuário | `cardioai_esp32` |

As credenciais são mantidas localmente no arquivo:

```text
include/secrets.h
```

Esse arquivo é ignorado pelo Git por meio do `.gitignore`. Portanto, a senha não deve ser publicada no repositório.

### Estrutura da mensagem

Os dados são transmitidos em formato JSON.

Exemplo ilustrativo:

```json
{
  "tempo_ms": 12500,
  "temperatura": 25.5,
  "umidade": 60.0,
  "bpm": 75,
  "aceleracao_x": 0.12,
  "aceleracao_y": 0.08,
  "aceleracao_z": 9.75
}
```

Os valores são ilustrativos.

O campo `tempo_ms` representa o tempo decorrido desde a inicialização do ESP32, obtido por `millis()`, e não um horário absoluto.

## 💾 Armazenamento local com LittleFS

Além da transmissão MQTT, o firmware utiliza o sistema de arquivos LittleFS para registrar o histórico localmente.

Arquivo utilizado:

```text
/dados_cardio_v2.csv
```

### Estrutura do CSV

```csv
tempo_ms,temperatura,umidade,bpm,aceleracao_x,aceleracao_y,aceleracao_z
```

O armazenamento permite registrar os dados coletados pelo ESP32 e realizar sua leitura posteriormente.

As principais funções implementadas são:

- `salvarDados()`: registra os dados no arquivo.
- `lerDados()`: realiza a leitura do histórico.

O arquivo é armazenado no sistema LittleFS do ESP32, não sendo necessário mantê-lo como arquivo de dados versionado no GitHub.

## 📊 Node-RED e Dashboard

O Node-RED foi utilizado para receber, processar e visualizar as informações transmitidas pelo ESP32.

O fluxo recebe mensagens do broker EMQX por meio de um nó MQTT IN, utilizando o tópico:

```text
cardioai/telemetria
```

Os dados são encaminhados para nós de processamento e visualização.

### Processamento e histórico

O fluxo realiza:

1. Recebimento da mensagem MQTT.
2. Processamento do JSON.
3. Organização dos valores.
4. Registro do histórico em CSV.
5. Encaminhamento dos dados para os indicadores do dashboard.

O histórico gerado pelo Node-RED utiliza o arquivo:

```text
cardioai_historico.csv
```

O registro contém:

```csv
tempo_ms,temperatura,umidade,bpm,aceleracao_x,aceleracao_y,aceleracao_z
```

### Dashboard

O painel apresenta indicadores e gráficos para acompanhamento dos dados recebidos.

Entre as informações visualizadas estão:

- Temperatura.
- Umidade.
- BPM.
- Aceleração X.
- Aceleração Y.
- Aceleração Z.
- Histórico de telemetria.

O dashboard pode ser acessado localmente em:

```text
http://localhost:1880/dashboard/cardioai
```

O endereço pressupõe que o Node-RED esteja em execução na máquina local.

## 🌐 Portal CardioAI

O projeto também possui uma interface web desenvolvida com React.

A estrutura contempla componentes e páginas para organização da experiência de utilização.

### Componentes

- Navbar.
- Sidebar.
- ProtectedRoute.
- Contexto de autenticação.

### Páginas

- Login.
- Dashboard.
- Pacientes.
- Agendamentos.

### Tecnologias

- React.
- JavaScript.
- CSS.

O portal faz parte da estrutura do projeto. Sua presença no repositório não significa que todas as funcionalidades estejam integradas ao fluxo de telemetria MQTT.

## 🧪 Simulação no Wokwi

O projeto utiliza o Wokwi para simulação do circuito e validação do funcionamento do firmware.

O arquivo:

```text
diagram.json
```

descreve os componentes e suas conexões.

O arquivo:

```text
wokwi.toml
```

contém a configuração de integração com a simulação.

A simulação permite verificar o comportamento dos sensores, do botão, do LED e do processamento realizado pelo ESP32.

## 🚀 Instalação e execução

### 1. Clonar o repositório

```bash
git clone https://github.com/almeidavictorhenrique-glitch/CardioAI.git
cd CardioAI
```

### 2. Preparar o ambiente Python

O ambiente virtual utilizado no projeto pode ser ativado pelo Git Bash:

```bash
python -m venv .venv
source .venv/Scripts/activate
```

### 3. Instalar o PlatformIO

Com o ambiente virtual ativado:

```bash
pip install platformio
```

### 4. Configurar as credenciais MQTT

Crie o arquivo:

```text
include/secrets.h
```

Com o conteúdo:

```cpp
#ifndef SECRETS_H
#define SECRETS_H

#define MQTT_PASSWORD_SECRET "SUA_SENHA_MQTT"

#endif
```

Substitua o valor de exemplo pela senha configurada no broker EMQX.

**Importante:** não publique esse arquivo no GitHub.

### 5. Compilar o firmware

Com o ambiente virtual ativado:

```bash
python -m platformio run
```

### 6. Executar a simulação

Abra o projeto no VS Code com a extensão PlatformIO e utilize a integração com o Wokwi para executar a simulação do circuito.

### 7. Executar o Node-RED

Com o Node-RED instalado e configurado:

```bash
node-red
```

Acesse:

```text
http://localhost:1880
```

O fluxo deve estar configurado para receber mensagens do EMQX pelo tópico `cardioai/telemetria`.

O dashboard fica disponível em:

```text
http://localhost:1880/dashboard/cardioai
```

## 📁 Estrutura do projeto

Principais diretórios e arquivos presentes no repositório:

```text
CardioAI/
│
├── cardioia-portal/       # Estrutura do portal CardioAI
├── data/                  # Dados do projeto
├── docs/                  # Documentação
├── images/                # Imagens e materiais visuais
├── notebooks/             # Notebooks de análise
│
├── include/
│   └── emqx_ca.h          # Certificado CA do broker
│
├── src/
│   ├── main.cpp           # Firmware ESP32
│   ├── App.jsx            # Interface React
│   ├── App.css
│   ├── main.jsx
│   ├── index.css
│   ├── components/        # Componentes da interface
│   ├── contexts/          # Contextos da aplicação
│   ├── pages/             # Páginas do portal
│   └── services/          # Serviços da aplicação
│
├── diagram.json           # Circuito Wokwi
├── platformio.ini         # Configuração PlatformIO
├── partitions.csv         # Tabela de partições
├── wokwi.toml             # Configuração Wokwi
├── package.json           # Configuração Node.js
├── package-lock.json
└── README.md
```

Arquivos locais de execução, como credenciais, ambiente virtual, dependências instaladas e históricos gerados, são mantidos fora do versionamento por meio do `.gitignore`.

## ✅ Resultados e validações

Durante o desenvolvimento da Fase 3, foram realizadas as seguintes validações:

| Item | Resultado |
|---|---|
| Compilação do firmware | Validada |
| Inicialização do ESP32 | Validada |
| Leitura do DHT22 | Validada |
| Leitura do MPU6050 | Validada |
| Simulação de BPM pelo botão | Validada |
| Sinalização pelo LED | Validada |
| Armazenamento LittleFS | Validado |
| Leitura do histórico local | Validada |
| Conexão com EMQX | Validada |
| Publicação MQTT | Validada |
| Recebimento no Node-RED | Validado |
| Indicadores e gráficos do dashboard | Validados |
| Simulação no Wokwi | Validada |

O funcionamento integrado foi testado, permitindo acompanhar os dados desde sua coleta no ESP32 até sua transmissão e visualização no dashboard.

## ⚠️ Limitações e considerações

A Fase 3 é um protótipo acadêmico de IoT e monitoramento simulado.

Algumas considerações importantes:

- O BPM é obtido por simulação utilizando um botão, não por sensor biométrico de frequência cardíaca.
- O DHT22 mede temperatura e umidade do ambiente, não temperatura corporal.
- O MPU6050 fornece dados de aceleração, não um diagnóstico de atividade cardíaca.
- O campo `tempo_ms` representa o tempo desde a inicialização do microcontrolador.
- O armazenamento local e o histórico do Node-RED são mecanismos distintos.
- O portal React está presente no projeto, mas não se deve presumir integração completa com todos os componentes de IoT.
- O protótipo não possui validação clínica e não deve ser utilizado para monitoramento médico real.

---

# 🛠️ Tecnologias utilizadas

| Categoria | Tecnologias |
|---|---|
| Microcontrolador | ESP32 |
| Linguagem do firmware | C++ |
| Ambiente embarcado | PlatformIO |
| Simulação | Wokwi |
| Sensores | DHT22 e MPU6050 |
| Comunicação | Wi-Fi e MQTT |
| Broker MQTT | EMQX Cloud |
| Segurança de comunicação | TLS |
| Armazenamento embarcado | LittleFS |
| Formato de dados | JSON e CSV |
| Processamento de fluxo | Node-RED |
| Visualização | Node-RED Dashboard 2.0 |
| Interface web | React, JavaScript e CSS |
| Controle de versão | Git e GitHub |

---

# 🎯 Considerações finais

A terceira fase representa um avanço importante na evolução do CardioAI.

Após trabalhar com organização de dados na Fase 1 e técnicas de NLP e Machine Learning na Fase 2, o projeto passou a incorporar uma camada de Internet das Coisas, conectando sensores, processamento embarcado, comunicação em nuvem e visualização de dados.

A integração entre ESP32, sensores, MQTT, EMQX, LittleFS e Node-RED demonstra como diferentes tecnologias podem trabalhar em conjunto para construir uma arquitetura de monitoramento conectada.

O desenvolvimento também permitiu explorar conceitos fundamentais de sistemas embarcados, protocolos de comunicação, armazenamento local, processamento de telemetria e construção de interfaces.

O CardioAI continua evoluindo como um projeto acadêmico multidisciplinar, aproximando Inteligência Artificial, Ciência de Dados e IoT do contexto da saúde.

---

**Repositório:** https://github.com/almeidavictorhenrique-glitch/CardioAI

**Projeto acadêmico — FIAP | Inteligência Artificial**