
import pandas as pd
from pathlib import Path
from sklearn.feature_extraction.text import TfidfVectorizer
from sklearn.metrics.pairwise import cosine_similarity

# Caminhos
pasta_projeto = Path(__file__).resolve().parent.parent
arquivo = pasta_projeto / "data" / "frases_risco_limpo.csv"

# Carregar dataset
df = pd.read_csv(arquivo)

# Preparar frases
frases = df["frase"].astype(str).tolist()

# Transformar textos em vetores TF-IDF
vetorizador = TfidfVectorizer(
    lowercase=True,
    strip_accents="unicode",
    ngram_range=(1, 2)
)

matriz = vetorizador.fit_transform(frases)

# Calcular similaridade entre todas as frases
similaridades = cosine_similarity(matriz)

# Analisar apenas pares diferentes
resultados = []

for i in range(len(frases)):
    for j in range(i + 1, len(frases)):
        score = similaridades[i, j]

        if score >= 0.80:
            resultados.append({
                "frase_1": frases[i],
                "classe_1": df.iloc[i]["situacao"],
                "frase_2": frases[j],
                "classe_2": df.iloc[j]["situacao"],
                "similaridade": round(float(score), 4)
            })

# Organizar resultados
resultado_df = pd.DataFrame(resultados)

if not resultado_df.empty:
    resultado_df = resultado_df.sort_values(
        by="similaridade",
        ascending=False
    )

# Salvar relatório
saida = pasta_projeto / "data" / "relatorio_similaridade.csv"

resultado_df.to_csv(
    saida,
    index=False,
    encoding="utf-8-sig"
)

# Exibir resumo
print("\n===== ANALISE DE SIMILARIDADE =====")

print("Total de frases:", len(frases))
print("Pares com similaridade >= 0.80:", len(resultado_df))

if not resultado_df.empty:

    mesma_classe = (
        resultado_df["classe_1"] ==
        resultado_df["classe_2"]
    ).sum()

    classes_diferentes = len(resultado_df) - mesma_classe

    print("Pares da mesma classe:", mesma_classe)
    print("Pares de classes diferentes:", classes_diferentes)

    print("\n10 PARES MAIS SEMELHANTES:")
    print(resultado_df.head(10).to_string(index=False))

else:
    print("Nenhum par atingiu o limite de 0.80.")

print("\nRelatorio salvo em:", saida)
