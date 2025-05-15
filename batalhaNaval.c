#include <stdio.h>

#define TAMANHO_TABULEIRO 10
#define TAMANHO_NAVIO 3
#define NAVIO 3
#define AGUA 0
#define HABILIDADE 5
#define TAMANHO_HABILIDADE 5

// Imprime o tabuleiro com legenda
void exibirTabuleiro(int tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO]) {
    printf("\nTabuleiro:\n\n");
    for (int i = 0; i < TAMANHO_TABULEIRO; i++) {
        for (int j = 0; j < TAMANHO_TABULEIRO; j++) {
            if (tabuleiro[i][j] == NAVIO) printf("3 ");
            else if (tabuleiro[i][j] == HABILIDADE) printf("5 ");
            else printf("0 ");
        }
        printf("\n");
    }
}

// Cria a matriz em formato de cone (triângulo para baixo)
void criarMatrizCone(int matriz[TAMANHO_HABILIDADE][TAMANHO_HABILIDADE]) {
    for (int i = 0; i < TAMANHO_HABILIDADE; i++) {
        for (int j = 0; j < TAMANHO_HABILIDADE; j++) {
            int centro = TAMANHO_HABILIDADE / 2;
            matriz[i][j] = (j >= centro - i && j <= centro + i) ? 1 : 0;
        }
    }
}

// Cria a matriz em formato de cruz
void criarMatrizCruz(int matriz[TAMANHO_HABILIDADE][TAMANHO_HABILIDADE]) {
    int centro = TAMANHO_HABILIDADE / 2;
    for (int i = 0; i < TAMANHO_HABILIDADE; i++) {
        for (int j = 0; j < TAMANHO_HABILIDADE; j++) {
            matriz[i][j] = (i == centro || j == centro) ? 1 : 0;
        }
    }
}

// Cria a matriz em formato de octaedro (losango)
void criarMatrizOctaedro(int matriz[TAMANHO_HABILIDADE][TAMANHO_HABILIDADE]) {
    int centro = TAMANHO_HABILIDADE / 2;
    for (int i = 0; i < TAMANHO_HABILIDADE; i++) {
        for (int j = 0; j < TAMANHO_HABILIDADE; j++) {
            matriz[i][j] = (abs(i - centro) + abs(j - centro) <= centro) ? 1 : 0;
        }
    }
}

// Aplica uma matriz de habilidade no tabuleiro
void aplicarHabilidade(int tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO],
                       int habilidade[TAMANHO_HABILIDADE][TAMANHO_HABILIDADE],
                       int origemLinha, int origemColuna) {
    int offset = TAMANHO_HABILIDADE / 2;
    for (int i = 0; i < TAMANHO_HABILIDADE; i++) {
        for (int j = 0; j < TAMANHO_HABILIDADE; j++) {
            int linhaTabuleiro = origemLinha + i - offset;
            int colunaTabuleiro = origemColuna + j - offset;

            if (linhaTabuleiro >= 0 && linhaTabuleiro < TAMANHO_TABULEIRO &&
                colunaTabuleiro >= 0 && colunaTabuleiro < TAMANHO_TABULEIRO) {
                if (habilidade[i][j] == 1 && tabuleiro[linhaTabuleiro][colunaTabuleiro] != NAVIO) {
                    tabuleiro[linhaTabuleiro][colunaTabuleiro] = HABILIDADE;
                }
            }
        }
    }
}

// Posiciona um navio simples (horizontal, vertical ou diagonal)
void posicionarNavio(int tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO], int linha, int coluna, int orientacao) {
    for (int i = 0; i < TAMANHO_NAVIO; i++) {
        int l = linha, c = coluna;
        if (orientacao == 0) c += i;             // Horizontal →
        else if (orientacao == 1) l += i;        // Vertical ↓
        else if (orientacao == 2) { l += i; c += i; } // Diagonal ↘
        else if (orientacao == 3) { l += i; c -= i; } // Diagonal ↙

        if (l >= 0 && l < TAMANHO_TABULEIRO && c >= 0 && c < TAMANHO_TABULEIRO) {
            tabuleiro[l][c] = NAVIO;
        }
    }
}

int main() {
    int tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO] = {0};

    // Posicionar 4 navios
    posicionarNavio(tabuleiro, 0, 0, 0); // horizontal
    posicionarNavio(tabuleiro, 2, 5, 1); // vertical
    posicionarNavio(tabuleiro, 5, 5, 2); // diagonal ↘
    posicionarNavio(tabuleiro, 6, 2, 3); // diagonal ↙

    // Matrizes de habilidades
    int cone[TAMANHO_HABILIDADE][TAMANHO_HABILIDADE];
    int cruz[TAMANHO_HABILIDADE][TAMANHO_HABILIDADE];
    int octaedro[TAMANHO_HABILIDADE][TAMANHO_HABILIDADE];

    criarMatrizCone(cone);
    criarMatrizCruz(cruz);
    criarMatrizOctaedro(octaedro);

    // Aplicar habilidades no tabuleiro (posições centrais definidas)
    aplicarHabilidade(tabuleiro, cone, 2, 2);       // cone em (2,2)
    aplicarHabilidade(tabuleiro, cruz, 5, 8);       // cruz em (5,8)
    aplicarHabilidade(tabuleiro, octaedro, 7, 4);   // octaedro em (7,4)

    // Mostrar tabuleiro final
    exibirTabuleiro(tabuleiro);

    return 0;
}
