import pandas as pd
from pathlib import Path

# Localizar o projeto
pasta_projeto = Path(__file__).resolve().parent.parent
arquivo = pasta_projeto / "data" / "frases_risco_limpo.csv"

# Carregar dataset
df = pd.read_csv(arquivo)

# Verificar possíveis problemas
problemas = []

for indice, frase in enumerate(df["frase"], start=2):

    texto = str(frase)

    # Espaços duplicados
    if "  " in texto:
        problemas.append({
            "linha": indice,
            "frase": texto,
            "problema": "Espaços duplicados"
        })

    # Espaço ausente após pontuação
    if any(p in texto for p in [".", ",", ";", ":"]):
        for pontuacao in [".", ",", ";", ":"]:
            if pontuacao in texto:
                posicao = texto.find(pontuacao)
                if posicao + 1 < len(texto) and texto[posicao + 1].isalpha():
                    problemas.append({
                        "linha": indice,
                        "frase": texto,
                        "problema": f"Possível espaço ausente após '{pontuacao}'"
                    })
                    break

    # Espaços no início ou final
    if texto != texto.strip():
        problemas.append({
            "linha": indice,
            "frase": texto,
            "problema": "Espaço no início ou final"
        })

# Gerar relatório
relatorio = pd.DataFrame(problemas)

saida = pasta_projeto / "data" / "relatorio_revisao_textual.csv"

relatorio.to_csv(saida, index=False, encoding="utf-8-sig")

print("\n===== REVISAO TEXTUAL =====")
print("Total de frases:", len(df))
print("Possíveis problemas encontrados:", len(relatorio))

if not relatorio.empty:
    print("\nProblemas identificados:")
    print(relatorio.to_string(index=False))
else:
    print("Nenhum problema de formatação identificado.")

print("\nRelatório salvo em:", saida)
