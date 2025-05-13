# 🐯 Jogo do Tigrinho

Um mini-jogo simples feito em **C com a biblioteca Raylib**, onde você controla um tigrinho que precisa desviar de obstáculos como árvores e galhos enquanto a dificuldade aumenta gradualmente.

---

## 🎮 Jogabilidade

- O tigrinho corre automaticamente da esquerda para a direita.
- Obstáculos surgem no caminho:
  - 🌳 Árvores — você precisa **pular**.
  - 🌿 Galhos — você precisa **abaixar**.
- A pontuação aumenta conforme você sobrevive.
- A cada 500 pontos, o jogo **aumenta a dificuldade** (mais rápido e mais obstáculos).

---

## 🕹️ Controles

- **Espaço**: Pular
- **Seta para baixo**: Abaixar
- **Q ou ESC**: Sair do jogo
- **ENTER (após Game Over)**: Jogar novamente

---

## 💾 Recorde

- O jogo salva automaticamente o recorde em um arquivo `recorde.txt` local.
- Se você bater o recorde, ele será atualizado ao final da partida.

---

## 🛠 Requisitos

- Compilador C (`gcc`, `clang`, etc.)
- [Raylib](https://www.raylib.com/) instalada no sistema

---

## 🧪 Compilação (exemplo para macOS)

```bash
gcc jogo_tigrinho.c -o jogo \
-I/opt/homebrew/include \
-L/opt/homebrew/lib \
-lraylib -framework OpenGL -framework Cocoa -framework IOKit
./jogo
