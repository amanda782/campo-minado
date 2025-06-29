#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int tela[9][9];
int revelado[9][9];
int jogo_em_andamento = 1; // variável para controlar o estado do jogo
void instrucoes() {
    printf("=== CAMPO MINADO ===\n");
    printf("Bem-vindo ao jogo!\n\n");
    printf("INSTRUÇÕES:\n");
    printf("- O campo é uma grade 9x9, com 10 bombas escondidas.\n");
    printf("- Seu objetivo é revelar posições que **não** contenham bombas.\n");
    printf("- A cada jogada, você digita a linha e a coluna da posição que deseja revelar.\n");
    printf("- Se a posição contiver uma bomba, você perde o jogo.\n");
    printf("- Se não tiver bomba, o número exibido mostrará quantas bombas existem ao redor daquela posição (nas 8 posições vizinhas).\n");
    printf("- Use essas informações para deduzir onde estão as bombas e evite escolhê-las!\n\n");
    printf("Boa sorte!\n\n");

}
void inicializa_tela() {
    
    for (int i = 0; i < 9; i++) {
        for (int j = 0; j < 9; j++) {
            tela[i][j] = 0; // inicializa a tela com zeros
        }
    }
    int contador_sorteio = 0;
    while(contador_sorteio<10) {
        int sorteio_linha = rand() %9;
        int sorteio_coluna = rand() %9;
        if (tela[sorteio_linha][sorteio_coluna] != -1) { //verifica se a posição já não foi sorteada
            tela[sorteio_linha][sorteio_coluna] = -1; // marca a posição sorteada com -1
            contador_sorteio++;
        }

    }

    for(int x=0; x<9; x++){
        for(int y=0; y<9; y++) {
            int conta_bombas=0;
            if(tela[x][y] == -1)
                continue;
            for(int l=-1; l<2; l++){
                for(int c=-1; c<2; c++) {
                     if(l==0 && c==0)
                    continue; // nao executa as linhas abaixo, pula pro próximo loop
                    int linha_vizinha = x +l;
                    int coluna_vizinha = y +c;
                    if (linha_vizinha < 0 || linha_vizinha > 8 || coluna_vizinha < 0 || coluna_vizinha > 8)
                       continue; // nao tentamos acessar fora da borda da matriz
                    if(tela[linha_vizinha][coluna_vizinha] == -1) 
                        conta_bombas++;

                }
            }
        tela[x][y] = conta_bombas; // diz quantas bombas estão ao redor 
        }
    
    }
    
}

void imprimeTelaOriginal() {

    for(int x=0; x<9; x++) {
        for (int y=0; y<9; y++) {
            printf("%d ", tela[x][y]);
            if(y==8)
                printf("\n");
        }
    }
}

void revelaVizinhos(int linha, int coluna) {
    
    if (linha < 0 || linha > 8 || coluna < 0 || coluna > 8) return; // Verifica se está dentro dos limites
    
    if (revelado[linha][coluna] == 1 || tela[linha][coluna] == -1) return; // Se já foi revelado ou for uma bomba, não faz nada

    revelado[linha][coluna] = 1; // Revela a posição atual

   
    if (tela[linha][coluna] == 0) {  // Se a posição for zero, propaga a revelação para os vizinhos
        for (int l = -1; l <= 1; l++) {
            for (int c = -1; c <= 1; c++) {
                if (l == 0 && c == 0) continue; // Não verifica a própria casa
                revelaVizinhos(linha + l, coluna + c);
            }
        }
    }
}

void imprimeTelaJogador() {
    
    for (int x = 0; x < 9; x++) { // Apenas imprime a matriz já processada
        for (int y = 0; y < 9; y++) {
            if (revelado[x][y] == 1) {
                printf("%d ", tela[x][y]); // Exibe o número real da matriz tela
            } else {
                printf("X ");
            }
            if (y == 8)
                printf("\n"); // Pula para a próxima linha
        }
    }
}

void posicaoEscolhida(int linha, int coluna) {
    if (linha < 0 || linha > 8 || coluna < 0 || coluna > 8) {
        printf("Posição inválida! Tente novamente.\n\n");
        return; // Sai do void, não executa o resto
    }
    if (tela[linha][coluna] == -1) {
        printf("Você escolheu uma bomba! Fim de jogo. Veja o campo completo: \n");
        imprimeTelaOriginal();
        jogo_em_andamento = 0; // Encerra o jogo se uma bomba for escolhida
    } else {
        revelaVizinhos(linha, coluna); // Revela os vizinhos corretamente
        imprimeTelaJogador(); // Agora imprime a matriz somente uma vez
        printf("Você escolheu uma posição segura! Revele mais posições para continuar jogando.\n");
    }
}


int jogadorVenceu() {
    int casas_reveladas = 0;

    for(int i = 0; i < 9; i++) {
        for(int j = 0; j < 9; j++) {
            if(revelado[i][j] == 1 && tela[i][j] != -1) 
                casas_reveladas++;
            
        }
    }

    return casas_reveladas; 
}
int main () {
    int linha_escolhida, coluna_escolhida;
    srand(time(NULL));
    instrucoes();
    inicializa_tela();
    for(int x=0; x<9; x++) {
        for (int y=0; y<9; y++) {
            revelado[x][y] = 0; // inicializa a tela da matriz revelado com zeros
        }
    }

    while(1){

        printf("Digite a linha que deseja revelar (0-8): ");
        scanf("%d", &linha_escolhida);
        printf("Digite a coluna que deseja revelar (0-8): ");
        scanf("%d", &coluna_escolhida);
        posicaoEscolhida(linha_escolhida, coluna_escolhida);
        if(jogo_em_andamento == 0) {
            printf(" Obrigado por jogar.\n");
            break; // encerra o loop se o jogo não estiver mais em andamento

    }  
    int resultado_vitoria = jogadorVenceu();
    if(resultado_vitoria == 71) {
        printf("Parabéns! Você venceu o jogo! Veja o campo completo: \n");
        imprimeTelaOriginal();
        break; // encerra o loop se o jogador vencer
    }
    
}
    return 0;
}
