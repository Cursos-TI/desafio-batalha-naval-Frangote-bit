#include <stdio.h>

#define TAMANHO_TABULEIRO 10
#define TAMANHO_NAVIO 3
#define MAR_AGUA 0
#define NAVIO 3

// Função para verificar se é possível posicionar um navio em certa direção
int pode_posicionar(int tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO], int linha, int coluna, int delta_linha, int delta_coluna) {
    for (int i = 0; i < TAMANHO_NAVIO; i++) {
        int l = linha + i * delta_linha;
        int c = coluna + i * delta_coluna;
        if (l < 0 || l >= TAMANHO_TABULEIRO || c < 0 || c >= TAMANHO_TABULEIRO)
            return 0; // Fora dos limites
        if (tabuleiro[l][c] != MAR_AGUA)
            return 0; // Já ocupado
    }
    return 1; // Pode posicionar
}

// Função para posicionar o navio no tabuleiro
void posicionar_navio(int tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO], int linha, int coluna, int delta_linha, int delta_coluna) {
    for (int i = 0; i < TAMANHO_NAVIO; i++) {
        int l = linha + i * delta_linha;
        int c = coluna + i * delta_coluna;
        tabuleiro[l][c] = NAVIO;
    }
}

int main() {
    int tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO];

    // Inicializa o tabuleiro com água
    for (int i = 0; i < TAMANHO_TABULEIRO; i++) {
        for (int j = 0; j < TAMANHO_TABULEIRO; j++) {
            tabuleiro[i][j] = MAR_AGUA;
        }
    }

    // ---- POSICIONAMENTO DOS NAVIOS ----

    // 1º Navio: Horizontal (linha 1, coluna 2)
    int l1 = 1, c1 = 2;
    if (pode_posicionar(tabuleiro, l1, c1, 0, 1)) {
        posicionar_navio(tabuleiro, l1, c1, 0, 1);
    }

    // 2º Navio: Vertical (linha 4, coluna 6)
    int l2 = 4, c2 = 6;
    if (pode_posicionar(tabuleiro, l2, c2, 1, 0)) {
        posicionar_navio(tabuleiro, l2, c2, 1, 0);
    }

    // 3º Navio: Diagonal ↘ (linha 0, coluna 0)
    int l3 = 0, c3 = 0;
    if (pode_posicionar(tabuleiro, l3, c3, 1, 1)) {
        posicionar_navio(tabuleiro, l3, c3, 1, 1);
    }

    // 4º Navio: Diagonal ↙ (linha 2, coluna 7)
    int l4 = 2, c4 = 7;
    if (pode_posicionar(tabuleiro, l4, c4, 1, -1)) {
        posicionar_navio(tabuleiro, l4, c4, 1, -1);
    }

    // ---- EXIBIÇÃO DO TABULEIRO ----
    printf("Tabuleiro Batalha Naval (0 = água, 3 = navio):\n\n");

    for (int i = 0; i < TAMANHO_TABULEIRO; i++) {
        for (int j = 0; j < TAMANHO_TABULEIRO; j++) {
            printf("%d ", tabuleiro[i][j]);
        }
        printf("\n");
    }

    return 0;
}