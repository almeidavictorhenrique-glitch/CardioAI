
import pandas as pd
from pathlib import Path

# Caminhos
pasta_projeto = Path(__file__).resolve().parent.parent
arquivo_original = pasta_projeto / "data" / "frases_risco_500.csv"
arquivo_limpo = pasta_projeto / "data" / "frases_risco_limpo.csv"

# Carregar arquivo original
df = pd.read_csv(arquivo_original)

print("Registros originais:", len(df))

# Remover linhas que são cabeçalhos repetidos
df = df[
    (df["frase"] != "frase") &
    (df["situacao"] != "situacao") &
    (df["origem"] != "origem")
].copy()

print("Após remover cabeçalhos:", len(df))

# Remover duplicatas exatas, mantendo a primeira ocorrência
df = df.drop_duplicates(
    subset=["frase", "situacao", "origem"],
    keep="first"
).copy()

print("Após remover duplicatas:", len(df))

# Salvar em um novo arquivo, preservando o original
df.to_csv(arquivo_limpo, index=False, encoding="utf-8-sig")

print("\nDISTRIBUIÇÃO DAS CLASSES:")
print(df["situacao"].value_counts())

print("\nTOTAL FINAL:", len(df))
print("\nArquivo limpo salvo em:", arquivo_limpo)
