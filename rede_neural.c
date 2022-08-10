//Programa que simula uma rede neural monocamada!!!
//Tá meio capenga ainda... Vou corrigir isso melhor!!!!

#include <stdio.h>
#include <math.h>

#define ENTRADA 4
#define SAIDA 2

int main()

{
	float x[ENTRADA], t[SAIDA], erro[SAIDA], y[SAIDA], w[ENTRADA], net[ENTRADA], eta;
	int i = 0, j = 0, k = 0;
	for (i=0;i<ENTRADA;i++)
	{
		printf("\nValor da entrada %d: ",i+1);
		scanf("%f",&x[i]);
		w[i] = 0.0;         //Pesos das sinapses em valor inicial zero!!!
	}	
	for (j=0;j<SAIDA;j++)
	{	
		printf("\nNível desejado %d: ",j+1);
		scanf("%f",&t[j]);
	}
	printf("\nDigite a taxa de aprendizado: ");
	scanf("%f",&eta);
	for (i=0;i<ENTRADA;i++)
	{
		net[i] = 0;
		net[i] = x[i]*w[i] + net[i];  //Obtém valor da rede antes de passar pela função de transferência.
	}
	for (j = 0;j<SAIDA;j++)
	{
		y[j] = 1/(1+exp(-net[j])); //Calcula o erro inicial!!!!
		erro[j] = t[j] - y[j];
		printf("\nErro %d: %.3f",j+1,sqrt(erro[j]*erro[j]));
	}
	i = 0;
	while ((erro[j]*erro[j]/2) > 0.0001)
	{
		for (j=0;j<SAIDA;j++)
		{
			for (i=0;i<ENTRADA;i++)
			{
				net[i] = x[i]*w[i];
				w[i] = w[i] + eta*(t[j]-y[j])*x[i];	
			}
				net[i] = x[i]*w[i];
				y[j] = 1/(1+exp(-net[i]));
				erro[j] = ((t[j] - y[j])*(t[j]-y[j]))/2;
		}			
	printf("\n\nPesos das sinapses são: %.3f e %.3f e %.3f Saídas: %.3f %.3f",w[0],w[1],w[2],y[0],y[1]);
	printf("Desejado: %.3f e %.3f",t[0],t[1]);	
	}
	return 0;
}
