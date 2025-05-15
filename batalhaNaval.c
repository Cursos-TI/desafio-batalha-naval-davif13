#include <stdio.h>

// Define o tamanho do tabuleiro e dos navios
#define TAMANHO_TABULEIRO 10
#define TAMANHO_NAVIO 3
#define AGUA 0
#define NAVIO 3

// Função para exibir o tabuleiro
void exibirTabuleiro(int tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO]) {
    printf("Tabuleiro:\n\n");
    for (int i = 0; i < TAMANHO_TABULEIRO; i++) {
        for (int j = 0; j < TAMANHO_TABULEIRO; j++) {
            printf("%d ", tabuleiro[i][j]);
        }
        printf("\n");
    }
}

// Função para verificar se o navio cabe e não sobrepõe outro navio
int podePosicionarNavio(int tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO], int linha, int coluna, int orientacao) {
    // orientacao: 0 = horizontal, 1 = vertical

    for (int i = 0; i < TAMANHO_NAVIO; i++) {
        int l = linha + (orientacao == 1 ? i : 0);
        int c = coluna + (orientacao == 0 ? i : 0);

        // Verifica se está fora dos limites do tabuleiro
        if (l >= TAMANHO_TABULEIRO || c >= TAMANHO_TABULEIRO) {
            return 0;
        }

        // Verifica se já tem outro navio na posição
        if (tabuleiro[l][c] == NAVIO) {
            return 0;
        }
    }
    return 1;
}

// Função para posicionar o navio no tabuleiro
void posicionarNavio(int tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO], int linha, int coluna, int orientacao) {
    for (int i = 0; i < TAMANHO_NAVIO; i++) {
        int l = linha + (orientacao == 1 ? i : 0);
        int c = coluna + (orientacao == 0 ? i : 0);
        tabuleiro[l][c] = NAVIO;
    }
}

int main() {
    // Inicializa o tabuleiro com 0 (água)
    int tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO] = {0};

    // Coordenadas dos navios definidas diretamente no código
    int linha_navio_horizontal = 2;
    int coluna_navio_horizontal = 3;

    int linha_navio_vertical = 5;
    int coluna_navio_vertical = 7;

    // Verifica se é possível posicionar os navios
    if (podePosicionarNavio(tabuleiro, linha_navio_horizontal, coluna_navio_horizontal, 0)) {
        posicionarNavio(tabuleiro, linha_navio_horizontal, coluna_navio_horizontal, 0); // horizontal
    } else {
        printf("Erro: não foi possível posicionar o navio horizontal.\n");
        return 1;
    }

    if (podePosicionarNavio(tabuleiro, linha_navio_vertical, coluna_navio_vertical, 1)) {
        posicionarNavio(tabuleiro, linha_navio_vertical, coluna_navio_vertical, 1); // vertical
    } else {
        printf("Erro: não foi possível posicionar o navio vertical.\n");
        return 1;
    }

    // Exibe o tabuleiro final
    exibirTabuleiro(tabuleiro);

    return 0;
}
