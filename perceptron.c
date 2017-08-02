/*
    Unfortunate scenes using C language;
    Attempt to implement ANN Perceptron;
*/

#include <stdlib.h>
#include <time.h>

#define LIMIAR -1
#define TAXA_APRENDIZADO 0.1
#define EPOCAS 1000
#define NUMERO_AMOSTRAS 4
#define NUMERO_ATRIBUTOS 3


typedef struct perceptron {
    float amostras[NUMERO_AMOSTRAS][NUMERO_ATRIBUTOS + 1];
    float saidas[NUMERO_AMOSTRAS];
    float pesos[NUMERO_ATRIBUTOS + 1];
}perceptron;

perceptron *cria();
perceptron *treino(perceptron *p);
void exibe(perceptron *p);
int sinal(float u);
void teste(perceptron *p);

int main(){
    perceptron *p = cria();
    p = treino(p);
    teste(p);
    //exibe(p);

    return EXIT_SUCCESS;
}

perceptron *cria(){

    perceptron *p = (perceptron*)malloc(sizeof(perceptron));

    float sequencia[] = {0.1, 0.4, 0.7, 0.3, 0.7, 0.2, 0.6, 0.9, 0.8, 0.5, 0.7, 0.1};
    int saida[] = {1, -1, -1, 1};

    int i, j, l = 0;
    i = j = l;

    printf("%d\n",  NUMERO_AMOSTRAS);

    for (i = 0; i < NUMERO_AMOSTRAS; i++){
        for (j = 1; j <= NUMERO_ATRIBUTOS; j++){
            p->amostras[i][j] = sequencia[l];
            l++;
        }
        p->pesos[i] = saida[i];
    }

    return p;
}

void exibe(perceptron *p){
    int i, j, l = 0;
    for (i = 0; i < NUMERO_AMOSTRAS; i++){
        for (j = 0; j < NUMERO_ATRIBUTOS; j++){
            printf("amostra[%d][%d] = %f ", i,j,p->amostras[i][j]);
        }
        printf("\n");
    }
}

perceptron *treino(perceptron *p){
    int i = 0, j = 0;
    srand( (unsigned)time(NULL) );

    for (i = 0; i < NUMERO_AMOSTRAS; i++)
        p->amostras[i][0] = -1;

    for (i = 0; i <= NUMERO_ATRIBUTOS; i++){
        if (i == 0)
            p->pesos[i] = LIMIAR;
        else
            p->pesos[i] = ((float)rand()/(float)(RAND_MAX)) * 1;
    }

    for (i = 0; i < NUMERO_AMOSTRAS; i++){
        for (j = 0; j <= NUMERO_ATRIBUTOS; j++){
            printf("%f ", p->amostras[i][j]);
        }
        printf("\n");
    }

    printf("\n");



    for (j = 0; j <= NUMERO_ATRIBUTOS; j++){
        printf("%f ", p->pesos[j]);
    }

    int n_epocas = 0;

    while(1 == 1){
        int erro = 0;

        for (i = 0; i < NUMERO_AMOSTRAS; i++){
            float u = 0;
            for (j = 0; j <= NUMERO_ATRIBUTOS; j++){
                u += p->pesos[j] * p->amostras[i][j];
            }
            int y = sinal(u);

            if(y != p->saidas[i]){
                float erro_aux = p->saidas[i] - y;
                for (j = 0; j <= NUMERO_ATRIBUTOS; j++){
                    p->pesos[j] = p->pesos[j] + TAXA_APRENDIZADO * erro_aux * p->amostras[i][j];
                }
                erro = 1;
            }
        }
        n_epocas++;
        if(erro == 0 || n_epocas > EPOCAS){
            printf("Paor");
            break;
        }
    }
    printf("Pesos: \n");
    for (j = 0; j <= NUMERO_ATRIBUTOS; j++){
        printf("%f ", p->pesos[j]);
    }
    printf("\nEpocas: %d", n_epocas);
    return p;
}

int sinal(float u){
    if(u >= 0)
        return 1;
    return -1;
}

void teste(perceptron *p){
    float sequencia[] = {0.3, 0.7, 0.2};
    int i = 0;
    float u = 0;
    printf("\n%f\n", p->pesos[1]);
    for (i = 0; i <= NUMERO_ATRIBUTOS; i++){
        if(i == 0)
            u += p->pesos[i] * -1;
        else
            u += p->pesos[i] * sequencia[i-1];
    }
    int y = sinal(u);
    printf("Classe: %d", y);

}
