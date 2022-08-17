///Rede neural monocamada com 4 entradas e 4 saídas.
///Autor: Volnei Fontana Junior.   Data: 11/08/2022.

#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <ncurses.h>

#define ENTRADA 8
#define DIM_NET 5
#define SAIDA 4
#define TRUE 1

///Entradas e saidas -> vetores coluna!!!

///Protótipos das funções

void imprimeEntrada(float entrada[ENTRADA]);

int escolhe_funcao();

float funcao(float saida,int opcao);

void imprimeEntrada(float entrada[ENTRADA]);

void imprimeSaida(float saida[SAIDA]);

void imprimeNET(float NET[ENTRADA]);

void imprimeMatrizW(float matrizW[ENTRADA][DIM_NET]);

void imprimeTreino(float target[SAIDA][DIM_NET]);

int main()

{
    float entrada[ENTRADA], w[ENTRADA][DIM_NET], NET[SAIDA];
    float target[SAIDA][DIM_NET], erro[SAIDA], saida[SAIDA], soma = 0.0;
    float eta = 0.0, erroMedQuad = 0.0;
    int i = 0, j = 0, passos = 0;
    printf("\nValores das entradas: ");
    printf("\n");
    for (i;i<ENTRADA;i++)
    {
        scanf("%f",&entrada[i]);
    }
    for (i=0;i<ENTRADA;i++)
    {
            for (j=0;j<DIM_NET;j++)
            {
                w[i][j] = 0.0; ///Zera Matriz de pesos das sinapses.
            }
    }
    printf("\nValores dos conjuntos de treino: ");
    printf("\n");
    i = 0;
    j = 0;
    for (j=0;j<DIM_NET;j++)
    {
        for (i=0;i<ENTRADA;i++)
        {
            printf("\nConjunto de treino %d %d: ",i+1,j+1);
            scanf("\n%f",&target[i][j]);
        }
        i = 0;
    }
    imprimeEntrada(entrada);
    imprimeMatrizW(w);
    imprimeTreino(target);
    ///Calcula produto da matriz de pesos com o vetor de entrada!!!
    for (i=0;i<ENTRADA;i++)
    {
        for (j=0;j<DIM_NET;j++)
        {
            soma = w[i][j]*entrada[i] + soma;
            NET[i] = soma;
        }
            soma = 0;
    }
    imprimeNET(NET);
    ///Calculo das Saídas!!!
    int escolha = 0;
    escolha = escolhe_funcao();
    for (i=0;i<SAIDA;i++)
    {
        saida[i] = funcao(NET[i],escolha);
    }
    imprimeSaida(saida);
    ///system("cls"); //No ruindows é "cls", no Pinguim é "clear".

    ///Aqui se faz o treinamento da rede neural!!!

    printf("\nValor da taxa de treinamento da rede neural ");
    printf("\n(Lembre-se que: valores grandes, treinamento rapido,");
    printf("no entanto, erro pode tender a infinito!!!): ");
    scanf("\n%f",&eta);

    printf("\n    Matriz do conjunto de treino: \n\n");
    //printf("\nNumero de passos: ");
    //scanf("%d",&passos);
    int k = 0;
    for (j=0;j<DIM_NET;j++)
    {
        for (i=0;i<SAIDA;i++)
        {  ///Todos os pesos iniciais das sinapses são zero!!!
           erro[i] = target[i][j]-saida[i];
           erroMedQuad = 0.5*(erro[i]*erro[i]);
           //for (k;k<passos;k++)
                //Se for escolhida a função sigmóide.
                while (erroMedQuad > 0.001)
                {
                    soma = w[i][j]*entrada[i] + soma;
                    NET[i] = soma;
                    //NET[i] = w[i][j]*entrada[i];
                    w[i][j] = w[i][j] + (eta*(target[i][j]-saida[i])*entrada[i]);
                    saida[i] = funcao(NET[i],escolha);
                    erro[i] = (target[i][j]-saida[i]);
                    erroMedQuad = 0.5*(erro[i]*erro[i]);
                    printf("\n %.3f Erro: %.5f",w[i][j],erroMedQuad);
                }
        soma = 0;
        k = 0;
        }
    }
    soma = 0;
    printf("\n------Matriz apos o treino --------\n");
    imprimeMatrizW(w);
    ///Fim do treinamento da rede neural!!!
    printf("\n");
    while (TRUE)
    {
    printf("\n.......Agora com a rede neural treinada...");
    printf("\nDigite a nova entrada: ");

    ///INVESTIGAR O PORQUÊ DA REDE TREINAR, MAS TODAS AS SAÍDAS SEREM IGUAIS!!!
    for (i=0;i<ENTRADA;i++)
    {
        printf("\n");
        scanf("%f",&entrada[i]);
    }
    for (j=0;j<DIM_NET;j++)
    {
        for (i = 0;i<ENTRADA;i++)
        {
        soma = w[i][j]*entrada[i] + soma;
        //NET[i] = w[i][j]*entrada[i];
        NET[i] = soma;
        }
        soma = 0;
    }
    for (i=0;i<SAIDA;i++)
    {
        saida[i] = funcao(NET[i],escolha);
    }
    imprimeNET(NET);
    imprimeSaida(saida);
    }
    return 0;
}

int escolhe_funcao()

{
    int opcao = 0;
    printf("\n\nQual a funcao desejada (1-sigmoide / 2-degrau)");
    scanf("%d",&opcao);
    return opcao;
}

float funcao(float saida,int opcao) ///Aplica a função sigmóide!!!

{
    switch (opcao)
    {
        case 1:
            return (1/(1+exp(-saida)));
        case 2:
            if (saida >= 0.0)
            {
                return 1.0;
            }
            else
            {
                return -1.0;
            }
    }

}

void imprimeEntrada(float entrada[ENTRADA])
{
    int i = 0;
    printf("\n    Entradas sao: \n\n");
    for (i;i<ENTRADA;i++)
    {
        printf("\n%.3f ",entrada[i]);
    }
    printf("\n");
}

void imprimeSaida(float saida[SAIDA])

{
    int j = 0;
    printf("\n    Valor das saidas: \n\n");
    for (j;j<SAIDA;j++)
    {
        /*if (saida[j] >= 0.5)
        {
            saida[j] = 1.0;
        }
        else
        {
            saida[j] = 0.0;
        }*/
        printf("\n%.3f ",saida[j]);
    }
    printf("\n\n\n");
}

void imprimeNET(float NET[ENTRADA])
{
    int j = 0;
    printf("\n    Valor do produto matriz W X vetor de entrada: \n\n");
    for (j;j<ENTRADA;j++)
    {
        printf("\n%.3f ",NET[j]);
    }
    printf("\n\n\n");
}

void imprimeMatrizW(float matrizW[ENTRADA][DIM_NET])

{
    int i = 0, j = 0;
    printf("\n    Matriz de pesos: \n\n");
    for (i;i<ENTRADA;i++)
    {
        for (j=0;j<DIM_NET;j++)
        {  ///Todos os pesos das sinapses são zero!!!
           printf(" %.5f ",matrizW[i][j]);
        }
        printf("\n");
    }
    printf("\n");
}

void imprimeTreino(float target[SAIDA][DIM_NET])
{
    int i = 0, j = 0;
    printf("\n    Matriz do conjunto de treino: \n\n");
    for (i;i<ENTRADA;i++)
    {
        for (j=0;j<DIM_NET;j++)
        {  ///Todos os pesos das sinapses são zero!!!
           printf(" %.5f ",target[i][j]);
        }
        printf("\n");
    }
    printf("\n");
}
