#!/bin/bash

SRC="jogo_tigrinho.c"
BIN="jogo"
INCLUDES="-I/opt/homebrew/include"
LIBS="-L/opt/homebrew/lib -lraylib -framework OpenGL -framework Cocoa -framework IOKit"

echo "Compilando $SRC..."
gcc -Wall $SRC -o $BIN $INCLUDES $LIBS

if [ $? -eq 0 ]; then
  echo "✅ Compilado com sucesso! Iniciando o jogo..."
  ./$BIN
else
  echo "❌ Erro na compilação!"
fi
