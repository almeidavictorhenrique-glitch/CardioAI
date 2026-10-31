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
