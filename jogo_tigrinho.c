
#include "raylib.h"
#include <stdlib.h>
#include <time.h>
#include <stdio.h>

#define LARGURA_TELA 800
#define ALTURA_TELA 450
#define POSICAO_CHAO (ALTURA_TELA - 130)
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
float velocidade_jogo = 3.0f;
int dificuldade = 1;
int mapa[LINHAS][COLUNAS];

void inicializar_jogo();
void atualizar_tigrinho();
void criar_obstaculo();
void atualizar_obstaculos();
int verificar_colisao();
void atualizar_dificuldade();
void desenhar_tigrinho_pixelado(int x, int y, int abaixado) {
    int pixel = 3;
    int offsetY = abaixado ? 20 : 0;
    int altura = abaixado ? 20 : 40;

    Color orange = ORANGE;
    Color preto = BLACK;
    Color bege = BEIGE;
    Color branco = WHITE;
    Color amarelo = YELLOW;

    // Corpo do Tigrinho
    DrawRectangle(x, y + offsetY, 40, altura, orange);

    // Orelhas (somente em pé)
    if (!abaixado) {
        DrawRectangle(x + 4, y + offsetY, pixel * 2, pixel * 2, orange);
        DrawRectangle(x + 32, y + offsetY, pixel * 2, pixel * 2, orange);
    }

    // Olhos brancos com pupilas pretas
    DrawRectangle(x + 10, y + offsetY + 6, pixel * 2, pixel * 2, branco);
    DrawRectangle(x + 26, y + offsetY + 6, pixel * 2, pixel * 2, branco);
    DrawRectangle(x + 11, y + offsetY + 7, pixel, pixel, preto);
    DrawRectangle(x + 27, y + offsetY + 7, pixel, pixel, preto);

    // Listras frontais
    DrawRectangle(x + 18, y + offsetY + 4, pixel, pixel, preto);
    DrawRectangle(x + 18, y + offsetY + 10, pixel, pixel, preto);

    // Pintas laterais
    DrawRectangle(x + 5, y + offsetY + 14, pixel, pixel, preto);
    DrawRectangle(x + 32, y + offsetY + 14, pixel, pixel, preto);

    // Bigodes laterais
    DrawRectangle(x + 3, y + offsetY + 18, pixel * 2, pixel, preto);
    DrawRectangle(x + 35, y + offsetY + 18, pixel * 2, pixel, preto);

    // Focinho bege com nariz preto
    DrawRectangle(x + 16, y + offsetY + 18, pixel * 2, pixel * 2, bege);
    DrawRectangle(x + 18, y + offsetY + 20, pixel, pixel, preto);

    // Dentes triangulares brancos
    DrawTriangle((Vector2){x + 16.0f, y + offsetY + 24.0f},
                 (Vector2){x + 17.5f, y + offsetY + 28.0f},
                 (Vector2){x + 19.0f, y + offsetY + 24.0f}, branco);

    DrawTriangle((Vector2){x + 21.0f, y + offsetY + 24.0f},
                 (Vector2){x + 22.5f, y + offsetY + 28.0f},
                 (Vector2){x + 24.0f, y + offsetY + 24.0f}, branco);
}

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
    velocidade_jogo = 3.5f;
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
}

void criar_obstaculo() {
    int chance = 35 - dificuldade * 3;
    if (chance < 10) chance = 10;

    int espaco_minimo_entre_obstaculos = 200;
    int largura_obstaculo = 20;

    Obstaculo *ultimo = NULL;
    for (Obstaculo *o = lista; o != NULL; o = o->prox) {
        ultimo = o;
    }

    int posicao_ultimo_obstaculo = (ultimo != NULL) ? ultimo->x : 0;

    if (LARGURA_TELA - posicao_ultimo_obstaculo > espaco_minimo_entre_obstaculos / 2 + largura_obstaculo) {
        if (GetRandomValue(0, chance) == 0) {
            int pode_criar = 1;
            for (Obstaculo *o = lista; o != NULL; o = o->prox) {
                if (abs(o->x - LARGURA_TELA) < espaco_minimo_entre_obstaculos + largura_obstaculo) {
                    pode_criar = 0;
                    break;
                }
            }

            if (pode_criar) {
                Obstaculo *novo = (Obstaculo *)malloc(sizeof(Obstaculo));
                novo->x = LARGURA_TELA;
                novo->prox = lista;

                if (GetRandomValue(0, 9) < 3 + dificuldade) {
                    novo->tipo = 'G';
                    novo->y = POSICAO_CHAO - 30;
                } else {
                    novo->tipo = 'A';
                    novo->y = POSICAO_CHAO;
                }

                lista = novo;
            }
        }
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
        if (o->x < tigrinho->x + 40 && o->x + 20 > tigrinho->x) {
            if (o->tipo == 'A' && !tigrinho->pulando && tigrinho->y == POSICAO_CHAO) {
                return 1;
            } else if (o->tipo == 'G' && !tigrinho->abaixado) {
                if (tigrinho->y < o->y + 40) {
                    return 1;
                }
            }
        }
    }
    return 0;
}

void atualizar_dificuldade() {
    int nova_dificuldade = 1 + (pontuacao / 1000);
    if (nova_dificuldade > dificuldade) {
        dificuldade = nova_dificuldade;
        velocidade_jogo += 0.5f;
        if (velocidade_jogo > 15.0f) velocidade_jogo = 15.0f;
    }
}

int main() {
    InitWindow(LARGURA_TELA, ALTURA_TELA, "Jogo do Tigrinho com Raylib");
    SetTargetFPS(60);
    srand(time(NULL));

    Texture2D fundo = LoadTexture("fundomesmo.png");

    while (!WindowShouldClose()) {
        inicializar_jogo();

        while (!WindowShouldClose() && !game_over) {
            if (IsKeyPressed(KEY_SPACE) && !tigrinho->pulando && !tigrinho->abaixado && tigrinho->y == POSICAO_CHAO) {
                tigrinho->pulando = 1;
                tigrinho->tempo_pulo = 0;
            }
            if (IsKeyDown(KEY_DOWN) && !tigrinho->pulando && tigrinho->y == POSICAO_CHAO) {
                tigrinho->abaixado = 1;
            } else if (!IsKeyDown(KEY_DOWN)) {
                tigrinho->abaixado = 0;
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
            DrawTexture(fundo, 0, 0, WHITE);

            DrawText("Jogo do Tigrinho", 20, 20, 20, DARKBLUE);
            DrawText(TextFormat("Pontuacao: %d", pontuacao), 20, 50, 20, BLACK);
            DrawText(TextFormat("Recorde: %d", recorde), 20, 75, 20, GRAY);
            DrawText(TextFormat("Dificuldade: %d", dificuldade), 20, 100, 20, GRAY);
            DrawText(TextFormat("Velocidade: %.1f", velocidade_jogo), 20, 125, 20, GRAY);

            desenhar_tigrinho_pixelado(tigrinho->x, tigrinho->y, tigrinho->abaixado);

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
            DrawTexture(fundo, 0, 0, WHITE);

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
