# 🫀 CardioIA — A Nova Era da Cardiologia Inteligente

> **FIAP — Curso de Inteligência Artificial**
> **Fase 1:** Batimentos de Dados
> **Fase 2:** Diagnóstico Inteligente com Dados Textuais

---

## 📋 Sobre o Projeto

O **CardioIA** é um projeto desenvolvido no curso de **Inteligência Artificial da FIAP**, com o objetivo de explorar diferentes formas de utilização de dados aplicados ao contexto da cardiologia.

O projeto aborda desde a coleta e organização de dados até técnicas de **Inteligência Artificial, Machine Learning e Processamento de Linguagem Natural (NLP)**.

A proposta é demonstrar como diferentes tipos de dados podem ser utilizados para identificar padrões e auxiliar na análise de informações relacionadas à saúde.

> **Importante:** o projeto possui finalidade exclusivamente educacional e utiliza dados simulados. Os resultados não representam diagnóstico médico real.

---

## 👨‍💻 Integrante

**Victor Henrique de Almeida**
**RM:** 657469

---

# 🩸 FASE 1 — Batimentos de Dados

A primeira fase do projeto teve como objetivo trabalhar com diferentes tipos de dados relacionados ao contexto cardiovascular.

## 📊 Parte 1 — Dados Numéricos

### IoT & Tabela Clínica

Nesta etapa foram trabalhados dados numéricos relacionados a informações clínicas e sensores.

O objetivo foi compreender como dados estruturados podem ser organizados e utilizados para análises posteriores dentro de um sistema de Inteligência Artificial.

---

## 📝 Parte 2 — Dados Textuais

### Processamento de Linguagem Natural (NLP)

Nesta etapa foram explorados dados textuais relacionados a informações de pacientes.

A proposta foi compreender como textos podem ser processados e transformados em informações úteis para sistemas inteligentes.

---

## 🖼️ Parte 3 — Dados Visuais

### Visão Computacional

A terceira parte trabalhou com dados visuais, explorando a possibilidade de utilização de imagens médicas em soluções baseadas em Inteligência Artificial.

Essa abordagem permite futuramente utilizar técnicas de **Visão Computacional** para identificação e classificação de padrões em imagens.

---

## ⚖️ Considerações sobre Governança, Equidade e Viés nos Dados

O projeto também considera a importância da utilização responsável de dados em Inteligência Artificial.

<<<<<<< HEAD
Em aplicações relacionadas à saúde, fatores como **qualidade dos dados, representatividade, privacidade, viés e equidade** são fundamentais para evitar resultados inadequados e garantir que os modelos sejam utilizados de maneira responsável.

---

# 🧠 FASE 2 — Diagnóstico Inteligente

Na segunda fase, o projeto avançou para o processamento de **dados textuais relacionados a sintomas e situações de risco**.

O objetivo foi desenvolver uma abordagem capaz de:

* identificar sintomas presentes em frases;
* relacionar sintomas a possíveis associações existentes em uma base;
* transformar textos em representações numéricas;
* treinar um modelo de classificação;
* classificar novas frases entre **alto risco** e **baixo risco**;
* analisar algumas limitações do modelo.

---

## 🔎 Parte 1 — Mapa de Sintomas

Inicialmente foi criado um mapa relacionando sintomas a possíveis doenças ou condições associadas.

A base possui exemplos como:

| Sintoma                                 | Associação             |
| --------------------------------------- | ---------------------- |
| dor no peito / pressão no peito         | Infarto                |
| cansaço / fadiga                        | Insuficiência Cardíaca |
| falta de ar / dificuldade para respirar | Angina                 |
| palpitação / coração acelerado          | Arritmia               |
| inchaço nas pernas                      | Insuficiência Cardíaca |
| tontura                                 | Arritmia               |
| dor nas costas                          | Dor Muscular           |

Em seguida, foram analisadas **19 frases simuladas**, procurando automaticamente os sintomas cadastrados no mapa.

Por exemplo, uma frase contendo **"pressão forte no peito"** é identificada pelo sistema e relacionada à associação correspondente na base.

---

## 🤖 Parte 2 — Classificação de Risco

Na segunda parte foi utilizada uma base de frases classificadas como:

* **Alto risco**
* **Baixo risco**

Os dados foram divididos em conjuntos de treinamento e teste.

### TF-IDF

Para que o modelo pudesse trabalhar com os textos, foi utilizado o **TF-IDF (Term Frequency–Inverse Document Frequency)**.

Essa técnica transforma as palavras das frases em valores numéricos, considerando sua importância dentro dos textos.

O conjunto de treinamento gerou uma matriz com:

**12 frases × 58 características**

---

## 🧠 Regressão Logística

Após a transformação dos textos, foi utilizado um modelo de **Regressão Logística** para realizar a classificação.

O modelo foi treinado utilizando os dados de treinamento e posteriormente avaliado com o conjunto de teste.

### Resultado

A acurácia obtida foi de:

**75%**

O conjunto de teste possuía **4 frases**, sendo:

* 2 classificadas como alto risco;
* 2 classificadas como baixo risco.

O relatório de classificação também apresentou diferenças entre precisão e recall das duas classes, demonstrando que o modelo ainda possui limitações devido principalmente ao tamanho reduzido da base utilizada.

---

## 🧪 Testando Novas Frases

Depois do treinamento, foram utilizadas frases que não estavam presentes na base original.

Alguns resultados obtidos foram:

```text
"estou sentindo uma pressão muito forte no peito e falta de ar"
→ alto risco

"tenho um pequeno desconforto nas costas depois de trabalhar"
→ baixo risco

"meu coração está acelerado e estou sentindo tontura"
→ alto risco

"estou com uma dor muscular leve depois de fazer exercícios"
→ baixo risco
```

Esses testes permitiram observar como o modelo se comporta diante de novas entradas.

---

## ⚠️ Testando Frases Ambíguas

Também foram utilizadas frases ambíguas para observar as limitações do modelo.

Um exemplo foi:

```text
"meu coração está acelerado porque fiquei nervoso"
→ alto risco
```

Mesmo existindo um contexto que poderia explicar o coração acelerado, o modelo classificou a frase como **alto risco**.

Outro exemplo:

```text
"tenho uma dor nas costas muito forte desde ontem"
→ baixo risco
```

Esses resultados mostram que o modelo depende fortemente dos padrões existentes nos dados de treinamento e **não possui compreensão clínica real do contexto**.

---

## 🔍 Análise das Palavras

Também foram analisados os pesos atribuídos pelo modelo às palavras utilizadas durante a classificação.

Entre as palavras que apresentaram maiores pesos positivos estavam:

* depois
* leve
* costas
* muscular
* sentado
* dor

Enquanto algumas palavras apresentaram pesos negativos, como:

* peito
* no
* ar
* falta
* forte
* pressão

Essa análise permite observar quais características textuais influenciaram o comportamento do modelo.

---

# 📌 Tecnologias e Bibliotecas

### Python

Utilizado para desenvolvimento da análise e processamento dos dados.

### Pandas

Utilizado para leitura, organização e manipulação das bases de dados.

### Scikit-learn

Utilizado para:

* divisão dos dados;
* TF-IDF;
* Regressão Logística;
* previsões;
* cálculo da acurácia;
* relatório de classificação.

### NLP

Utilizado para trabalhar com as frases e identificar padrões relacionados aos sintomas e à classificação de risco.

---

# 🎥 Vídeo da Fase 2

A apresentação da **Fase 2 do CardioIA** está disponível no YouTube:

▶️ **[Assistir ao vídeo da Fase 2](https://youtu.be/UPm5MN1Cig0)**

---

# 🚀 Conclusão

A Fase 2 permitiu avançar da organização de dados para uma aplicação prática de **Processamento de Linguagem Natural e Machine Learning**.

O projeto passou pela identificação de sintomas em frases, associação com uma base de conhecimento, transformação de textos utilizando TF-IDF e treinamento de um modelo de Regressão Logística para classificação de risco.

O resultado de **75% de acurácia** e os testes com frases ambíguas também demonstraram a importância de utilizar bases maiores e mais representativas para desenvolver modelos mais robustos.

O CardioIA continua, assim, explorando como diferentes técnicas de Inteligência Artificial podem ser aplicadas ao contexto da saúde de forma responsável e educacional.
=======
1. **Equidade Socioeconômica e Regional:** Estudos mostram disparidades no cuidado prestado a pacientes com hipertensão e disfunções cardíacas no Brasil (com menor oferta de exames e orientações nas regiões Norte/Nordeste e em classes econômicas mais baixas). O modelo preditivo deve ser treinado prevenindo a amplificação dessas iniquidades socioeconômicas.
2. **Mitigação de Viés Demográfico:** Inclusão e calibração equilibrada de dados por idade e sexo, considerando que a manifestação da doença e prognósticos variam fortemente com o envelhecimento e a gravidade da disfunção ventricular.
3. **Privacidade e LGPD:** Todos os dados clínicos, textuais e de imagem passaram por protocolos de anonimização completa, garantindo o total respeito às diretrizes éticas e legais vigentes.

## Evolução experimental da Fase 2 — Análise textual e modelagem

Após a entrega original da Fase 2, foi realizada uma evolução experimental do projeto CardioIA, ampliando a base textual e aprofundando a análise dos modelos de classificação de risco.

### 1. Atualização do dataset

O conjunto de dados foi ampliado e revisado para melhorar a consistência dos experimentos.

- **Total de registros:** 514 frases.
- **Alto risco:** 257 frases.
- **Baixo risco:** 257 frases.
- **Origem:** dados sintéticos.
- **Arquivo:** `data/frases_risco_limpo.csv`.

Durante a preparação, foram removidos cabeçalhos repetidos e registros duplicados. Também foram adicionadas frases de baixo risco para equilibrar as classes.

### 2. Análise exploratória e similaridade textual

Foi realizada uma análise exploratória das frases, incluindo a identificação de possíveis duplicidades e similaridades textuais.

Foram identificados 17 pares de frases com similaridade igual ou superior a 0,80. Todos os pares identificados apresentavam a mesma classificação, sem conflitos entre os rótulos.

### 3. Estratégia de divisão dos dados

Para reduzir o risco de frases muito semelhantes aparecerem simultaneamente nos conjuntos de treinamento e teste, foi utilizada uma estratégia de divisão estratificada e agrupada.

- Divisão aproximada: 80% para treinamento e 20% para teste.
- Treinamento: 411 registros.
- Teste: 103 registros.
- Sobreposição de grupos entre treinamento e teste: zero.

Foi utilizada a estratégia `StratifiedGroupKFold`, com cinco divisões, embaralhamento e `random_state=42`.

### 4. Experimentos de modelagem

Foram comparadas duas configurações de representação textual utilizando TF-IDF e Regressão Logística.

| Configuração | Acurácia | Erros |
|---|---:|---:|
| Unigramas e bigramas | 99,03% | 1 |
| Unigramas, bigramas e trigramas | 100% | 0 |

O primeiro modelo apresentou um erro de classificação no conjunto de teste. O segundo modelo não apresentou erros nesse mesmo conjunto.

A inclusão de trigramas permitiu considerar sequências textuais maiores, contribuindo para a classificação das frases avaliadas.

### 5. Interpretação e limitações

Os resultados demonstram que as configurações testadas conseguiram identificar padrões presentes na base sintética utilizada.

Entretanto, é importante considerar as seguintes limitações:

- O dataset é sintético e não representa, necessariamente, a linguagem utilizada por pacientes em situações reais.
- A acurácia obtida não representa desempenho clínico.
- O resultado de 100% foi observado em uma única divisão de teste e não garante generalização para novos dados.
- O conjunto de teste foi consultado durante os experimentos exploratórios, portanto não deve ser considerado uma avaliação final totalmente independente.
- O TF-IDF representa frequências e combinações de palavras, mas não compreende integralmente o contexto semântico das frases.

### 6. Próximos passos

Como continuidade do projeto, pretende-se avançar para a integração com sensores e monitoramento de dados fisiológicos na Fase 3, mantendo a preocupação com a qualidade dos dados, a confiabilidade dos resultados e as limitações do sistema.

**Observação:** esta seção documenta uma evolução experimental posterior à entrega original da Fase 2, sem substituir ou descaracterizar os entregáveis anteriormente submetidos.
>>>>>>> c7290a0 (feat: amplia dataset e experimentos de modelagem da fase 2)
