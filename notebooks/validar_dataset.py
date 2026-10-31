
import pandas as pd
from pathlib import Path

# Localiza a pasta principal do projeto
pasta_projeto = Path(__file__).resolve().parent.parent

# Caminho do dataset
arquivo = pasta_projeto / "data" / "frases_risco_limpo.csv"# Carrega o CSV
df = pd.read_csv(arquivo)

print("\n===== VALIDACAO DO DATASET CARDIOIA =====")

# 1. Estrutura
print("\n1. COLUNAS:")
print(df.columns.tolist())

# 2. Quantidade de registros
print("\n2. TOTAL DE FRASES:")
print(len(df))

# 3. Distribuição das classes
print("\n3. DISTRIBUICAO DAS CLASSES:")
print(df["situacao"].value_counts())

# 4. Distribuição da origem
print("\n4. ORIGEM DOS DADOS:")
print(df["origem"].value_counts())

# 5. Valores vazios
print("\n5. VALORES VAZIOS:")
print(df.isnull().sum())

# 6. Frases duplicadas
print("\n6. FRASES DUPLICADAS:")
print(df["frase"].duplicated().sum())

# 7. Rótulos inválidos
rotulos_validos = ["alto risco", "baixo risco"]

rotulos_invalidos = df[
    ~df["situacao"].isin(rotulos_validos)
]

print("\n7. ROTULOS INVALIDOS:")
print(len(rotulos_invalidos))

# 8. Verificação final
colunas_esperadas = ["frase", "situacao", "origem"]

total_alto = (df["situacao"] == "alto risco").sum()
total_baixo = (df["situacao"] == "baixo risco").sum()

aprovado = (
    len(df) == 514
    and df.columns.tolist() == colunas_esperadas
    and total_alto == 257
    and total_baixo == 257
    and df.isnull().sum().sum() == 0
    and df["frase"].duplicated().sum() == 0
    and len(rotulos_invalidos) == 0
)

print("\n===== RESULTADO FINAL =====")

if aprovado:
    print("DATASET APROVADO NA VALIDACAO INICIAL!")
else:
    print("ATENCAO: existem itens que precisam ser revisados.")

print(f"\nArquivo analisado: {arquivo}")


print("\n===== INVESTIGACAO DOS PROBLEMAS =====")

# Localizar cabeçalhos repetidos
cabecalhos = df[
    (df["frase"] == "frase") |
    (df["situacao"] == "situacao") |
    (df["origem"] == "origem")
]

print("\nLINHAS DE CABECALHO REPETIDAS:")
print(cabecalhos.to_string())

# Mostrar frases duplicadas
duplicadas = df[
    df["frase"].duplicated(keep=False)
].sort_values("frase")

print("\nFRASES DUPLICADAS:")
print(duplicadas.to_string(index=False))

