#!/bin/bash

echo "Compilando o Jogo do Tigrinho..."
gcc jogo_tigrinho.c -o jogo \
-I/opt/homebrew/include \
-L/opt/homebrew/lib \
-lraylib -framework OpenGL -framework Cocoa -framework IOKit

if [ $? -eq 0 ]; then
  echo "✅ Compilado com sucesso! Iniciando o jogo..."
  ./jogo
else
  echo "❌ Erro na compilação!"
fi
