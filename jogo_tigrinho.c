#include "raylib.h"
#include <stdlib.h>
#include <time.h>
#include <stdio.h>

#define LARGURA_TELA 800
#define ALTURA_TELA 450
#define POSICAO_CHAO (ALTURA_TELA - 80)
#define TIGRINHO_X 100
#define ALTURA_PULO 80
#define DURACAO_PULO 20
#define DURACAO_ABAIXADO 10
#define LINHAS 3
#define COLUNAS 80

typedef struct Obstaculo {
    int x, y;
    char tipo;
    struct Obstaculo *prox;
} Obstaculo;

typedef struct {
    int x, y;
    int pulando;
    int abaixado;
    int tempo_pulo;
    int tempo_abaixado;
} Tigrinho;

Tigrinho *tigrinho;
Obstaculo *lista = NULL;
int pontuacao = 0;
int recorde = 0;
int game_over = 0;
int velocidade_jogo = 6;
int dificuldade = 1;
int mapa[LINHAS][COLUNAS];

void inicializar_jogo() {
    tigrinho = (Tigrinho *)malloc(sizeof(Tigrinho));
    tigrinho->x = TIGRINHO_X;
    tigrinho->y = POSICAO_CHAO;
    tigrinho->pulando = 0;
    tigrinho->abaixado = 0;
    tigrinho->tempo_pulo = 0;
    tigrinho->tempo_abaixado = 0;

    while (lista != NULL) {
        Obstaculo *tmp = lista;
        lista = lista->prox;
        free(tmp);
    }

    pontuacao = 0;
    game_over = 0;
    velocidade_jogo = 6;
    dificuldade = 1;

    FILE *arq = fopen("recorde.txt", "r");
    if (arq) { fscanf(arq, "%d", &recorde); fclose(arq); } else recorde = 0;

    for (int i = 0; i < LINHAS; i++)
        for (int j = 0; j < COLUNAS; j++)
            mapa[i][j] = 0;
}

void atualizar_tigrinho() {
    if (tigrinho->pulando) {
        tigrinho->tempo_pulo++;
        if (tigrinho->tempo_pulo <= DURACAO_PULO/2)
            tigrinho->y = POSICAO_CHAO - (ALTURA_PULO * tigrinho->tempo_pulo / (DURACAO_PULO/2));
        else if (tigrinho->tempo_pulo <= DURACAO_PULO)
            tigrinho->y = (POSICAO_CHAO - ALTURA_PULO) + ((tigrinho->tempo_pulo - DURACAO_PULO/2) * ALTURA_PULO / (DURACAO_PULO/2));
        else {
            tigrinho->pulando = 0;
            tigrinho->y = POSICAO_CHAO;
        }
    }
    if (tigrinho->abaixado) {
        tigrinho->tempo_abaixado++;
        if (tigrinho->tempo_abaixado > DURACAO_ABAIXADO) {
            tigrinho->abaixado = 0;
            tigrinho->tempo_abaixado = 0;
        }
    }
}

void criar_obstaculo() {
    int chance = 35 - dificuldade * 3;
    if (chance < 10) chance = 10;
    if (GetRandomValue(0, chance) == 0) {
        Obstaculo *novo = (Obstaculo *)malloc(sizeof(Obstaculo));
        novo->x = LARGURA_TELA;
        novo->prox = lista;

        if (GetRandomValue(0, 9) < 3 + dificuldade) {
            novo->tipo = 'G';
            novo->y = POSICAO_CHAO - 40;
        } else {
            novo->tipo = 'A';
            novo->y = POSICAO_CHAO;
        }

        lista = novo;
    }
}

void atualizar_obstaculos() {
    Obstaculo **atual = &lista;
    while (*atual != NULL) {
        (*atual)->x -= velocidade_jogo;
        if ((*atual)->x < -20) {
            Obstaculo *remover = *atual;
            *atual = remover->prox;
            free(remover);
        } else {
            atual = &(*atual)->prox;
        }
    }
}

int verificar_colisao() {
    for (Obstaculo *o = lista; o != NULL; o = o->prox) {
        if (o->x < tigrinho->x + 40 && o->x + 20 > tigrinho->x && o->y == tigrinho->y) {
            if ((o->tipo == 'A' && !tigrinho->pulando) ||
                (o->tipo == 'G' && !tigrinho->abaixado)) return 1;
        }
    }
    return 0;
}

void atualizar_dificuldade() {
    int nova = 1 + (pontuacao / 500);
    if (nova > dificuldade) {
        dificuldade = nova;
        velocidade_jogo++;
        if (velocidade_jogo > 15) velocidade_jogo = 15;
    }
}

int main() {
    InitWindow(LARGURA_TELA, ALTURA_TELA, "Jogo do Tigrinho com Raylib");
    SetTargetFPS(60);
    srand(time(NULL));

    // ⬇️ Carregar imagem de fundo do menu
    Texture2D fundo = LoadTexture("floresta.png");

    // ⬇️ Tela de menu inicial
    while (!WindowShouldClose()) {
        BeginDrawing();
        DrawTexture(fundo, 0, 0, WHITE);

        DrawText("Jogo do Tigrinho", LARGURA_TELA/2 - MeasureText("Jogo do Tigrinho", 40)/2, ALTURA_TELA/2 - 60, 40, DARKBLUE);
        DrawText("Pressione ENTER para comecar", LARGURA_TELA/2 - MeasureText("Pressione ENTER para comecar", 20)/2, ALTURA_TELA/2, 20, BLACK);

        EndDrawing();

        if (IsKeyPressed(KEY_ENTER)) break;
    }

    while (!WindowShouldClose()) {
        inicializar_jogo();

        while (!WindowShouldClose() && !game_over) {
            if (IsKeyPressed(KEY_SPACE) && !tigrinho->pulando && !tigrinho->abaixado && tigrinho->y == POSICAO_CHAO) {
                tigrinho->pulando = 1;
                tigrinho->tempo_pulo = 0;
            }
            if (IsKeyPressed(KEY_DOWN) && !tigrinho->pulando && !tigrinho->abaixado && tigrinho->y == POSICAO_CHAO) {
                tigrinho->abaixado = 1;
                tigrinho->tempo_abaixado = 0;
            }

            atualizar_tigrinho();
            criar_obstaculo();
            atualizar_obstaculos();
            pontuacao += dificuldade;
            if (verificar_colisao()) game_over = 1;
            atualizar_dificuldade();

            BeginDrawing();
            ClearBackground(RAYWHITE);

            DrawText("Jogo do Tigrinho", 20, 20, 20, DARKBLUE);
            DrawText(TextFormat("Pontuacao: %d", pontuacao), 20, 50, 20, BLACK);
            DrawText(TextFormat("Recorde: %d", recorde), 20, 75, 20, GRAY);
            DrawText(TextFormat("Dificuldade: %d", dificuldade), 20, 100, 20, GRAY);

            DrawRectangle(0, POSICAO_CHAO + 40, LARGURA_TELA, 5, DARKGRAY);

            if (tigrinho->abaixado)
                DrawRectangle(tigrinho->x, tigrinho->y + 20, 40, 20, ORANGE);
            else
                DrawRectangle(tigrinho->x, tigrinho->y, 40, 40, ORANGE);

            for (Obstaculo *o = lista; o != NULL; o = o->prox) {
                Color cor = (o->tipo == 'A') ? GREEN : DARKGREEN;
                DrawRectangle(o->x, o->y, 20, 40, cor);
            }

            EndDrawing();
        }

        if (pontuacao > recorde) {
            FILE *arq = fopen("recorde.txt", "w");
            if (arq) { fprintf(arq, "%d", pontuacao); fclose(arq); }
        }

        while (!WindowShouldClose()) {
            BeginDrawing();
            ClearBackground(RAYWHITE);

            DrawText("GAME OVER", LARGURA_TELA/2 - MeasureText("GAME OVER", 40)/2, ALTURA_TELA/2 - 40, 40, RED);
            DrawText(TextFormat("Pontuacao Final: %d", pontuacao), LARGURA_TELA/2 - MeasureText(TextFormat("Pontuacao Final: %d", pontuacao), 20)/2, ALTURA_TELA/2 + 10, 20, BLACK);

            const char *mensagem = "Pressione ENTER para jogar novamente ou ESC para sair";
            int largura_texto = MeasureText(mensagem, 20);
            DrawText(mensagem, LARGURA_TELA/2 - largura_texto/2, ALTURA_TELA/2 + 40, 20, GRAY);

            EndDrawing();

            if (IsKeyPressed(KEY_ENTER)) {
                game_over = 0;
                break;
            }
            if (IsKeyPressed(KEY_ESCAPE)) {
                UnloadTexture(fundo);
                CloseWindow();
                free(tigrinho);
                return 0;
            }
        }
    }

    UnloadTexture(fundo);
    CloseWindow();
    free(tigrinho);
    return 0;
}
