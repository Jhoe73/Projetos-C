#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#define N 30

typedef struct{
	int topo;
	char operacao[N];
}Pilha;

int main(){
	Pilha posfixa;
	posfixa.topo = 0;
	int i;
	char infixa[N];
	char operador[N];

	printf("Digite a operacao desejada: ");
	gets(infixa);

	int length = strlen(infixa);

	for(i = 0; i < length; i++){
		if(isdigit(infixa[i])){
			posfixa.operacao[posfixa.topo] = infixa[i];
			posfixa.topo++;
		}
		else{
			operador[i] = infixa[i];
		}
	}

	for(i = length-1; i > 0; i--){
		if(operador[i] == '+' || operador[i] == '-'){
			posfixa.operacao[posfixa.topo] = operador[i];
			posfixa.topo++;
		}
		else{
			switch(operador[i]){
				case '*':
					if(operador[i] == '+' || operador[i] == '-'){
					posfixa.operacao[posfixa.topo--];
					posfixa.operacao[posfixa.topo] = operador[i];
					posfixa.topo++;
					}
					else{
						posfixa.operacao[posfixa.topo] = operador[i];
						posfixa.topo++;
					}
					break;
				case '/':
					if(operador[i] == '+' || operador[i] == '-'){
					posfixa.operacao[posfixa.topo--];
					posfixa.operacao[posfixa.topo] = operador[i];
					posfixa.topo++;
					}
					else{
						posfixa.operacao[posfixa.topo] = operador[i];
						posfixa.topo++;
					}
					break;
					default: posfixa.operacao[posfixa.topo] = operador[i];
			}
		}
	}
	printf("Formato posfixo: ");
	puts(posfixa.operacao);
}
