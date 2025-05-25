# 🐯 Jogo do Tigrinho

Um mini-jogo arcade divertido e viciante, desenvolvido em C utilizando a poderosa biblioteca **Raylib**. Controle um tigrinho corajoso em uma corrida infinita, desviando de obstáculos e testando seus reflexos enquanto a velocidade aumenta com sua pontuação!

Este projeto é uma excelente prática para consolidar conceitos fundamentais de programação estruturada em C de forma aplicada e interativa.

---

## 🎮 Jogabilidade

O Tigrinho é um jogo de corrida infinita com foco em reflexos e tempo:

-   O tigrinho corre automaticamente da esquerda para a direita da tela.
-   Desvie de **🌳 árvores (pulando)** e **🌿 galhos (abaixando)** para sobreviver.
-   A pontuação aumenta constantemente conforme você sobrevive e avança.
-   A dificuldade do jogo (velocidade dos obstáculos e frequência) aumenta gradualmente com o tempo, tornando o desafio cada vez maior.

---

## 🕹️ Controles

Mantenha o tigrinho na linha!

-   **Espaço**: Pular (evita árvores)
-   **Seta para baixo (↓)**: Abaixar (evita galhos)
-   **ENTER (após Game Over)**: Iniciar um novo jogo
-   **ESC**: Sair do jogo a qualquer momento

---

## 📊 Recorde

-   Seus melhores resultados são importantes! O jogo salva automaticamente o **recorde** (maior pontuação atingida) no arquivo `recorde.txt`.
-   Ao bater seu recorde anterior, ele será atualizado e salvo automaticamente.

---

## 🧠 Conceitos de Programação Utilizados

Este projeto foi cuidadosamente estruturado para aplicar e demonstrar os seguintes conceitos de programação em C:

| Conceito                | Aplicação no Jogo                                                |
| :---------------------- | :------------------------------------------------------------------ |
| **Structs**            | Representação de entidades do jogo como `Tigrinho` e `Obstaculo`   |
| **Ponteiros**          | Manipulação eficiente do jogador (`Tigrinho*`) e elementos da lista de obstáculos. |
| **Alocação dinâmica**  | Criação dinâmica de obstáculos (`malloc`) conforme o jogo avança e liberação de memória (`free`). |
| **Listas encadeadas**  | Obstáculos são gerenciados dinamicamente como uma lista ligada, permitindo adição e remoção eficiente. |
| **Matrizes**           | Utilização da matriz `mapa[LINHAS][COLUNAS]` (ou similar) como estrutura de apoio para lógica de colisões ou posicionamento. |
| **Leitura/escrita de arquivos** | Persistência do recorde do jogador em `recorde.txt`, demonstrando operações básicas de I/O em arquivo. |
| **Máquina de Estados (Game States)** | Gerenciamento dos diferentes estados do jogo (Menu, Jogando, Game Over) para controlar a lógica e renderização. |
| **Manipulação de Texturas** | Uso de imagens (`.png`) para renderizar gráficos mais detalhados para o tigrinho, fundo e obstáculos. |

---

## 🛠 Requisitos

Para compilar e executar o Jogo do Tigrinho, você precisará:

-   Um compilador C (como `gcc` ou `clang`).
-   A biblioteca **Raylib** instalada em seu sistema.

### Como Instalar a Raylib:

Escolha as instruções para o seu sistema operacional:

-   **Linux (Ubuntu/Debian):**
    ```bash
    sudo apt install build-essential
    sudo apt install libraylib-dev
    ```
-   **macOS (com Homebrew):**
    ```bash
    brew install raylib
    ```
-   **Windows (com MSYS2/MinGW-w64):**
    1.  Baixe e instale o MSYS2 do site oficial: [https://www.msys2.org/](https://www.msys2.org/)
    2.  Abra o terminal MSYS2 MinGW 64-bit.
    3.  Atualize os pacotes: `pacman -Syu`
    4.  Instale o compilador `gcc` e a Raylib:
        ```bash
        pacman -S mingw-w64-x86_64-gcc mingw-w64-x86_64-raylib
        ```

---

## ▶️ Como Compilar e Executar

1.  **Navegue até o diretório do projeto** no seu terminal:
    ```bash
    cd /caminho/para/seu/projeto/Jogo-do-Tigrinho
    ```
    (Substitua `/caminho/para/seu/projeto/Jogo-do-Tigrinho` pelo caminho real onde você salvou os arquivos do jogo, por exemplo, `~/Projetos/Projeto-C`)

2.  **Compile o jogo** usando o `gcc` e linkando com a Raylib. As flags de compilação podem variar ligeiramente dependendo do seu sistema operacional.

    -   **Para Linux:**
        ```bash
        gcc jogo_tigrinho.c -o jogo_tigrinho -lraylib -lm
        ```
    -   **Para macOS:**
        ```bash
        gcc jogo_tigrinho.c -o jogo_tigrinho \
        -I/opt/homebrew/include \
        -L/opt/homebrew/lib \
        -lraylib -framework OpenGL -framework Cocoa -framework IOKit
        ```
        (Se você instalou a Raylib por outro método, os caminhos `-I` e `-L` podem ser diferentes).

    -   **Para Windows (MSYS2 MinGW 64-bit):**
        ```bash
        gcc jogo_tigrinho.c -o jogo_tigrinho.exe -lraylib
        ```

3.  **Execute o jogo:**
    ```bash
    ./jogo_tigrinho
    ```
    (No Windows, pode ser `.\jogo_tigrinho.exe`)

---

## 📸 Screen

[![tigrinho_em_pe png](https://github.com/user-attachments/assets/20565df7-2d7e-4179-9b0c-68fd98460af4)](https://youtu.be/44aDXTdaGI8)



---

## 👥 Equipe de Desenvolvimento  

- **Pedro Marinho** - [pmpc@cesar.school](mailto:pmpc@cesar.school)  
- **Ramsés Cordeiro** - [rcfe@cesar.school](mailto:rcfe@cesar.school)  
- **Eduardo Malheiros** - [emlj@cesar.school](mailto:emlj@cesar.school)  
