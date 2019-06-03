#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <string.h>
#include "lista.h"

void verTamanho(Lista *l3);

void preenche(Lista *l, int dist) {
	while (dist > 0) {
		inserir_primeiro(l, 0);
		dist--;
	}
}

void soma(Lista *l1, Lista *l2, Lista *l3) {
	int i, dist, tam1 = tamanho(l1), tam2 = tamanho(l2);
	
	if(tam1 > tam2) {
		dist = tam1 - tam2;
		preenche(l2, dist);
	}
	else {
		dist = tam2 - tam1;
		preenche(l1, dist);
		tam1+= dist;
	}
	for(i = tam1-1; i>=0; i--) {
		inserir_primeiro(l3, ler_pos(l1, i) + ler_pos(l2, i));
	}
	verTamanho(l3);
}

//void mult(Lista *l1. Lista *l2, Lista *l3) {
	
//}

void verTamanho(Lista *l3) {
	int i;
	for(i = tamanho(l3)-1; i >= 0; i--) {
		if(ler_pos(l3, i) >= 10) {
			escrever_pos(l3, i, ler_pos(l3, i)-10);
			if(ler_pos(l3, i-1) != -1) {
				escrever_pos(l3, i-1, ler_pos(l3, i-1)+1);
			}
			else {
				inserir_primeiro(l3, 1);
			}
		}	
	}
}

void converteAscii(Lista *l) {
	int i, j = 48, count = 0, tam = tamanho(l);
	for(i=0; i<tam; i++) {
		if(ler_pos(l, i) < 48 || ler_pos(l, i) > 57) {
			printf("Número inválido na posição %d\n", i);
			remover_pos(l, i);
			tam--;
		}
		while(j < ler_pos(l, i)) {
			count++;
			j++;
		}	
		escrever_pos(l, i, count);
		j = 48;
		count = 0;
	}
}
int main(int argc, char *argv[]) {
	setlocale(LC_ALL, "Portuguese");
	Lista *l1 = criar();
	Lista *l2 = criar();
	Lista *l3 = criar();
	int i, tamx, tamy, op;
	char x[100], y[100];
	
	printf("Digite o primeiro número\n");
	gets(x);
	tamx = strlen(x);
	for(i=0; i<tamx; i++) {
		inserir_ultimo(l1, x[i]);	
	}
	imprimir(l1);
	converteAscii(l1);
	
	fflush(stdin);
	printf("Digite o segundo número\n");
	gets(y);
	tamy = strlen(y);
	for(i=0; i<tamy; i++) {
		inserir_ultimo(l2, y[i]);	
	}
	converteAscii(l2);
	
	printf("Escolha a operação:\n\t1 para soma\n\t");
	scanf("%d", &op);
	
	switch(op) {
		case 1:
			soma(l1, l2, l3);
			break;
	}
	
	printf("\nResultado da operação é: ");
	imprimir(l3);

	destruir(l1);
	destruir(l2);
	destruir(l3);
	system("pause");
	return 0;
}
