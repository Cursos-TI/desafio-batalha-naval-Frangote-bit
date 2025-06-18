#include <stdio.h>

#define TAMANHO_TABULEIRO 10
#define TAMANHO_NAVIO 3
#define TAMANHO_HABILIDADE 5

#define MAR_AGUA 0
#define NAVIO 3
#define AREA_HABILIDADE 5

// Inicializa o tabuleiro com água
void inicializar_tabuleiro(int tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO]) {
    for (int i = 0; i < TAMANHO_TABULEIRO; i++)
        for (int j = 0; j < TAMANHO_TABULEIRO; j++)
            tabuleiro[i][j] = MAR_AGUA;
}

// Exibe o tabuleiro no console
void exibir_tabuleiro(int tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO]) {
    printf("Tabuleiro:\n\n");
    for (int i = 0; i < TAMANHO_TABULEIRO; i++) {
        for (int j = 0; j < TAMANHO_TABULEIRO; j++) {
            printf("%d ", tabuleiro[i][j]);
        }
        printf("\n");
    }
}

// Posiciona navios usando deslocamentos (horizontal, vertical ou diagonal)
void posicionar_navio(int tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO], int linha, int coluna, int dlinha, int dcoluna) {
    for (int i = 0; i < TAMANHO_NAVIO; i++) {
        int l = linha + i * dlinha;
        int c = coluna + i * dcoluna;
        if (l >= 0 && l < TAMANHO_TABULEIRO && c >= 0 && c < TAMANHO_TABULEIRO) {
            if (tabuleiro[l][c] == MAR_AGUA) {
                tabuleiro[l][c] = NAVIO;
            }
        }
    }
}

// Cria uma matriz de habilidade em cone (triângulo apontando para baixo)
void criar_cone(int habilidade[TAMANHO_HABILIDADE][TAMANHO_HABILIDADE]) {
    for (int i = 0; i < TAMANHO_HABILIDADE; i++) {
        for (int j = 0; j < TAMANHO_HABILIDADE; j++) {
            habilidade[i][j] = 0;
            // Expansão horizontal conforme desce
            if (j >= 2 - i && j <= 2 + i) {
                habilidade[i][j] = 1;
            }
        }
    }
}

// Cria uma matriz em cruz
void criar_cruz(int habilidade[TAMANHO_HABILIDADE][TAMANHO_HABILIDADE]) {
    for (int i = 0; i < TAMANHO_HABILIDADE; i++) {
        for (int j = 0; j < TAMANHO_HABILIDADE; j++) {
            if (i == TAMANHO_HABILIDADE / 2 || j == TAMANHO_HABILIDADE / 2) {
                habilidade[i][j] = 1;
            } else {
                habilidade[i][j] = 0;
            }
        }
    }
}

// Cria uma matriz de habilidade com forma de octaedro (losango)
void criar_octaedro(int habilidade[TAMANHO_HABILIDADE][TAMANHO_HABILIDADE]) {
    for (int i = 0; i < TAMANHO_HABILIDADE; i++) {
        for (int j = 0; j < TAMANHO_HABILIDADE; j++) {
            // Condição para formar losango
            if (abs(i - 2) + abs(j - 2) <= 2) {
                habilidade[i][j] = 1;
            } else {
                habilidade[i][j] = 0;
            }
        }
    }
}

// Aplica uma matriz de habilidade no tabuleiro, centralizada na posição (linha, coluna)
void aplicar_habilidade(int tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO],
                        int habilidade[TAMANHO_HABILIDADE][TAMANHO_HABILIDADE],
                        int linha_centro, int coluna_centro) {
    for (int i = 0; i < TAMANHO_HABILIDADE; i++) {
        for (int j = 0; j < TAMANHO_HABILIDADE; j++) {
            if (habilidade[i][j] == 1) {
                int linha_t = linha_centro + i - TAMANHO_HABILIDADE / 2;
                int coluna_t = coluna_centro + j - TAMANHO_HABILIDADE / 2;

                if (linha_t >= 0 && linha_t < TAMANHO_TABULEIRO &&
                    coluna_t >= 0 && coluna_t < TAMANHO_TABULEIRO &&
                    tabuleiro[linha_t][coluna_t] == MAR_AGUA) {
                    tabuleiro[linha_t][coluna_t] = AREA_HABILIDADE;
                }
            }
        }
    }
}

int main() {
    int tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO];
    int cone[TAMANHO_HABILIDADE][TAMANHO_HABILIDADE];
    int cruz[TAMANHO_HABILIDADE][TAMANHO_HABILIDADE];
    int octaedro[TAMANHO_HABILIDADE][TAMANHO_HABILIDADE];

    // Inicializa o tabuleiro
    inicializar_tabuleiro(tabuleiro);

    // Posiciona os navios
    posicionar_navio(tabuleiro, 1, 1, 0, 1); // Horizontal
    posicionar_navio(tabuleiro, 4, 5, 1, 0); // Vertical
    posicionar_navio(tabuleiro, 6, 1, 1, 1); // Diagonal ↘
    posicionar_navio(tabuleiro, 2, 8, 1, -1); // Diagonal ↙

    // Cria as matrizes de habilidade
    criar_cone(cone);
    criar_cruz(cruz);
    criar_octaedro(octaedro);

    // Aplica as habilidades no tabuleiro com posições fixas
    aplicar_habilidade(tabuleiro, cone, 2, 2);
    aplicar_habilidade(tabuleiro, cruz, 5, 5);
    aplicar_habilidade(tabuleiro, octaedro, 7, 7);

    // Exibe o tabuleiro final
    exibir_tabuleiro(tabuleiro);

    return 0;
}