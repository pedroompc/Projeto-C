# 🐯 Jogo do Tigrinho

Um mini-jogo em C usando **Raylib**, onde você controla um tigrinho que precisa desviar de obstáculos enquanto a velocidade aumenta com a pontuação.

Ideal para praticar conceitos fundamentais de programação estruturada em C.

---

## 🎮 Jogabilidade

- O tigrinho corre automaticamente.
- Desvie de **🌳 árvores (pulando)** e **🌿 galhos (abaixando)**.
- A pontuação aumenta automaticamente conforme você sobrevive.
- A dificuldade aumenta gradualmente com o tempo.

---

## 🕹️ Controles

- **Espaço**: Pular
- **Seta para baixo**: Abaixar
- **ENTER (após Game Over)**: Jogar novamente
- **ESC**: Sair do jogo

---

## 💾 Recorde

- O jogo salva automaticamente o **recorde** no arquivo `recorde.txt`.
- Ao bater o recorde, ele será atualizado automaticamente.

---

## 🧠 Conceitos de Programação Utilizados

Este projeto foi desenvolvido para aplicar os seguintes conceitos de programação em C:

| Conceito                | Aplicação no Jogo                                 |
|------------------------|----------------------------------------------------|
| **Structs**            | Representação de `Tigrinho` e `Obstaculo`          |
| **Ponteiros**          | Manipulação do jogador (`Tigrinho*`) e lista       |
| **Alocação dinâmica**  | Criação dinâmica de obstáculos e do jogador        |
| **Listas encadeadas**  | Obstáculos são armazenados como lista ligada       |
| **Matrizes**           | Matriz `mapa[LINHAS][COLUNAS]` como estrutura de apoio |
| **Leitura/escrita de arquivos** | Salva e carrega o recorde do jogador em `recorde.txt` |

---

## 🛠 Requisitos

- Compilador C (ex: `gcc`, `clang`)
- [Raylib](https://www.raylib.com/) instalada

---

## ▶️ Compilação (macOS com Homebrew)

```bash
gcc jogo_tigrinho.c -o jogo \
-I/opt/homebrew/include \
-L/opt/homebrew/lib \
-lraylib -framework OpenGL -framework Cocoa -framework IOKit
./jogo
