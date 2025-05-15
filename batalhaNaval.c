#include <stdio.h>

#define TAMANHO_TABULEIRO 10
#define TAMANHO_NAVIO 3
#define AGUA 0
#define NAVIO 3

// Exibe o tabuleiro no console
void exibirTabuleiro(int tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO]) {
    printf("\nTabuleiro:\n\n");
    for (int i = 0; i < TAMANHO_TABULEIRO; i++) {
        for (int j = 0; j < TAMANHO_TABULEIRO; j++) {
            printf("%d ", tabuleiro[i][j]);
        }
        printf("\n");
    }
}

// Verifica se é possível posicionar o navio sem sair dos limites ou sobrepor
int podePosicionarNavio(int tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO], int linha, int coluna, int orientacao) {
    /*
     * Orientações:
     * 0 - Horizontal →
     * 1 - Vertical ↓
     * 2 - Diagonal principal ↘ (linha++, coluna++)
     * 3 - Diagonal secundária ↙ (linha++, coluna--)
     */

    for (int i = 0; i < TAMANHO_NAVIO; i++) {
        int l = linha, c = coluna;
        if (orientacao == 0) c += i;             // Horizontal
        else if (orientacao == 1) l += i;        // Vertical
        else if (orientacao == 2) { l += i; c += i; } // Diagonal ↘
        else if (orientacao == 3) { l += i; c -= i; } // Diagonal ↙

        // Verifica limites
        if (l < 0 || l >= TAMANHO_TABULEIRO || c < 0 || c >= TAMANHO_TABULEIRO)
            return 0;

        // Verifica sobreposição
        if (tabuleiro[l][c] == NAVIO)
            return 0;
    }

    return 1;
}

// Posiciona o navio na matriz
void posicionarNavio(int tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO], int linha, int coluna, int orientacao) {
    for (int i = 0; i < TAMANHO_NAVIO; i++) {
        int l = linha, c = coluna;
        if (orientacao == 0) c += i;             // Horizontal
        else if (orientacao == 1) l += i;        // Vertical
        else if (orientacao == 2) { l += i; c += i; } // Diagonal ↘
        else if (orientacao == 3) { l += i; c -= i; } // Diagonal ↙

        tabuleiro[l][c] = NAVIO;
    }
}

int main() {
    // Inicializa o tabuleiro com água (0)
    int tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO] = {0};

    // Definições dos navios: {linha, coluna, orientacao}
    int navios[4][3] = {
        {0, 0, 0}, // horizontal → (0)
        {2, 5, 1}, // vertical ↓ (1)
        {5, 5, 2}, // diagonal ↘ (2)
        {6, 2, 3}  // diagonal ↙ (3)
    };

    // Posiciona todos os navios
    for (int i = 0; i < 4; i++) {
        int linha = navios[i][0];
        int coluna = navios[i][1];
        int orientacao = navios[i][2];

        if (podePosicionarNavio(tabuleiro, linha, coluna, orientacao)) {
            posicionarNavio(tabuleiro, linha, coluna, orientacao);
        } else {
            printf("Erro: não foi possível posicionar o navio %d (linha %d, coluna %d, orientação %d)\n", 
                   i + 1, linha, coluna, orientacao);
        }
    }

    // Exibe o resultado final
    exibirTabuleiro(tabuleiro);

    return 0;
}
