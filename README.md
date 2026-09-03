# 🫀 CardioIA — A Nova Era da Cardiologia Inteligente
> **FIAP — Curso de Inteligência Artificial**  
> **Fase 1:** Batimentos de Dados  

---

## 📋 Sobre o Projeto

O **CardioIA** é uma plataforma digital inteligente idealizada para simular um ecossistema cardiomédico moderno. O projeto visa integrar Machine Learning, Processamento de Linguagem Natural (NLP), Visão Computacional (VC) e IoT para suportar a triagem clínica, apoio ao diagnóstico, monitoramento remoto de pacientes e estratificação preditiva de risco cardiovascular.

Nesta **Fase 1 – Batimentos de Dados**, o objetivo é construir e documentar a infraestrutura e a governança inicial de dados numéricos, textuais e visuais do projeto.

👥 **Integrante:**
- Victor Henrique de Almeida — RM: 657469

---

## 📊 Parte 1 – Dados Numéricos (IoT & Tabela Clínica)

* **Link para o dataset completo:** [Acessar Dataset no Google Drive](https://drive.google.com/drive/folders/1espZJq5dX2Z-ZOFa7JLdZH13n8hVgt7O?usp=sharing)

### Descrição dos Dados
O conjunto de dados numéricos e de sensoriamento clínico contém **303 registros** de pacientes com **14 variáveis** (atributos clínicos e demográficos).

* **Origem dos Dados:** *UCI Machine Learning Repository - Heart Disease Dataset (Subconjunto de Cleveland)*.
* **Governança e LGPD:** A base passou por processo rigoroso de anonimização, eliminando qualquer dado de identificação pessoal (*PII - Personally Identifiable Information*)[cite: 5].
* **Distribuição da Variável Alvo (`target`):**
  * **Variável Binária (`target_binary`):** **164 pacientes saudáveis (54.1%)** e **139 pacientes diagnosticados com doença cardíaca (45.9%)**.
* **Qualidade e Limpeza de Dados:** A base apresenta apenas 6 valores ausentes (4 em `ca` e 2 em `thal`), tratados via imputação pela moda estatística (`ca = 0.0` e `thal = 3.0`).

### Variáveis Mais Relevantes e Justificativa Clínica

1. **Frequência Cardíaca Máxima Atingida (`thalach`):** Variável de destaque para monitoramento contínuo via dispositivos IoT/wearables. Permite identificar estresse miocárdico e cronotropismo inadequado em tempo real[cite: 4].
2. **Pressão Arterial em Repouso (`trestbps`):** A Hipertensão Arterial (HA) é uma Doença Crônica Não Transmissível (DCNT) fundamental para a estimativa de risco cardiovascular e disfunção endotelial[cite: 5].
3. **Depressão de ST Induzida por Exercício (`oldpeak`) & Angina (`exang`):** Indicadores eletrocardiográficos diretos de isquemia miocárdica e sofrimento do tecido cardíaco sob esforço[cite: 4].
4. **Número de Vasos Principais Coloridos por Fluoroscopia (`ca`):** Reflete o grau de acometimento anatômico e aterosclerose coronariana[cite: 4].
5. **Idade (`age`) e Sexo (`sex`):** Variáveis demográficas de relevância crítica; o envelhecimento populacional e as diferenças de sexo influenciam diretamente a incidência de Insuficiência Cardíaca (IC) e HA[cite: 4, 5].

---

## 📝 Parte 2 – Dados Textuais (NLP)

Os arquivos em texto bruto para treinamento e extração em linguagem natural encontram-se disponíveis em : https://drive.google.com/drive/folders/1TQCcfs491hN-YBmndVq4uAwhV0fbjWl9?usp=sharing

*Revisão Fisiopatológica e Manejo Clínico/Cirúrgico da Insuficiência Cardíaca (InCor / USP)*
*Análise da Adequação do Cuidado à Hipertensão Arterial no SUS e Rede Privada (PNS 2013–2019)*

### Exploração por Algoritmos de Processamento de Linguagem Natural (NLP)

* **Reconhecimento e Extração de Entidades Nomeadas (NER):** Mapeamento automático de termos da literatura e prontuários médicos (ex: *fração de ejeção, dispneia, remodelamento ventricular, inibidores da ECA, digital, diuréticos*) para alimentar bases do conhecimento cardiológico.
* **Sistemas de Apoio à Decisão e Sumarização Clínica:** Mineração de artigos científicos e diretrizes do SUS para automatizar recomendações de acompanhamento e suporte à prescrição clínica.
* **Análise de Sentimentos e Sintomatologia:** Processamento de relatos de pacientes sobre sintomas subjetivos e impacto na qualidade de vida (como fadiga e limitação funcional de classes New York Heart Association).

---

## 👁️ Parte 3 – Dados Visuais (Visão Computacional)

* **Link para o conjunto de imagens:** [Acessar Imagens no Google Drive](https://drive.google.com/drive/folders/1khYUNi0oGlA9sod2gkB6wFPD_6K9Vfoy?usp=sharing)

### Descrição das Imagens
O repositório visual é composto por **1.684 imagens** médicas relativas a exames de **Eletrocardiogramas (ECG)** e **Raio-X de Tórax**. A base apresenta uma amostragem altamente equilibrada e estatisticamente robusta para o treinamento de modelos de deep learning:

* **Imagens de exames sem alterações (Normais):** 858 imagens (50,95%)
* **Imagens de exames com alterações (Patologias):** 826 imagens (49,05%)

### Aplicação de Visão Computacional na Saúde

* **Classificação de Padrões Isquêmicos e Estruturais:** Utilização de Redes Neurais Convolucionais (CNNs) para automatizar a diferenciação entre exames saudáveis e patológicos, identificando cardiomegalia em Raio-X de Tórax e desvios de segmento ST ou arritmias em ECGs.
* **Segmentação Anatômica:** Delimitação da silhueta cardíaca e grandes vasos para cálculo automatizado do índice cardiotorácico.
* **Triagem Pré-Diagnóstica Hospitalar:** O equilíbrio do dataset permite treinar classificadores binários confiáveis para sinalizar exames alterados e priorizá-los automaticamente na fila do especialista.

---

## ⚖️ Considerações sobre Governança, Equidade e Viés nos Dados

Com base na literatura técnica e epidemiológica analisada:

1. **Equidade Socioeconômica e Regional:** Estudos mostram disparidades no cuidado prestado a pacientes com hipertensão e disfunções cardíacas no Brasil (com menor oferta de exames e orientações nas regiões Norte/Nordeste e em classes econômicas mais baixas). O modelo preditivo deve ser treinado prevenindo a amplificação dessas iniquidades socioeconômicas.
2. **Mitigação de Viés Demográfico:** Inclusão e calibração equilibrada de dados por idade e sexo, considerando que a manifestação da doença e prognósticos variam fortemente com o envelhecimento e a gravidade da disfunção ventricular.
3. **Privacidade e LGPD:** Todos os dados clínicos, textuais e de imagem passaram por protocolos de anonimização completa, garantindo o total respeito às diretrizes éticas e legais vigentes.
