#include "nprcrossover.h"
#include <stdio.h>
#include <time.h>
#include <math.h>

void shuffle(int size, int array[size]){
	int i, j, temp;
	for(i = 0;i<(size - 1);i++){
		j = rand()%((size - 1) - i + 1) + i;
		temp = array[i];
		array[i] = array[j];
		array[j] = temp;
	}
}

void generatePopulation(int p_lgth, int c_lgth, int population[p_lgth][c_lgth]){
	int i, j, gen;
	for(i = 0;i<p_lgth;i++){
		for(j = 0;j<c_lgth;j++){
			population[i][j] = j + 1;	//fijar valor de gen de individuo i
		}
		shuffle(c_lgth, population[i]);
	}
}

/*imprime resultado en linea de comando*/
void print(int c_lgth, int cp1, int cp2, const int p1[c_lgth], const int p2[c_lgth], const int ch1[c_lgth], const int ch2[c_lgth]){
	int i;
	printf("\nP1: ");
	for(i = 0;i<c_lgth;i++) printf("%d", p1[i]);	//primer padre
	printf("\t|\tsegmento1: ");
	for(i = cp1;(i - cp1)<c_lgth;i++) (i<cp2) ? printf("%d", p1[i]) : printf(" ");;	//subcadena
	printf("\t|\tH1: ");
	for(i = 0;i<c_lgth;i++) printf("%d", ch1[i]);	//primer hijo
	printf("\nP2: ");
	for(i = 0;i<c_lgth;i++) printf("%d", p2[i]); //segundo padre
	printf("\t|\tsegmento2: ");
	for(i = cp1;(i - cp1)<c_lgth;i++) (i<cp2) ? printf("%d", p2[i]) : printf(" ");;	//subcadena
	printf("\t|\tH2: ");
	for(i = 0;i<c_lgth;i++) printf("%d", ch2[i]);	//segundo hijo
	printf("\n\n");
}

/*cruzar poblacion*/
void breeding(int p_lgth, int c_lgth, int child[p_lgth][c_lgth], const int parent[p_lgth][c_lgth]){
	int i = 0;
	int cp1, cp2; //indice inicial y final de la subcadena
	while(i<p_lgth){
		cp1 = (rand()%((c_lgth - 1) - (0) + 1)) + (0);
		cp2 = (rand()%((c_lgth) - (cp1 + 1) + 1)) + (cp1 + 1);
		pmx(c_lgth, child[i], parent[i], parent[i + 1], cp1, cp2);	//generar primer hijo
		pmx(c_lgth, child[i + 1], parent[i + 1], parent[i], cp1, cp2);	//invertir roles de padres y generar segundo hijo
		/*imprimir resultados*/
		print(c_lgth, cp1, cp2, parent[i], parent[i + 1], child[i], child[i + 1]);
		i += 2;
	}
}

int main(int argc, char *argv[]){
	if(argc!=3) exit(1);
	int p_lgth = atoi(argv[1]); //numero de individuos por generacion
	int c_lgth = atoi(argv[2]);	//tamaño de la cadena
	if(p_lgth<0 || p_lgth%2 || c_lgth<3) exit(1);
	srand(time(NULL));
	int parent[p_lgth][c_lgth], child[p_lgth][c_lgth];	//padres y descendencia
	/*generar poblacion inicial*/
	generatePopulation(p_lgth, c_lgth, parent);
	/*cruzar*/
	breeding(p_lgth, c_lgth, child, parent);
	return 1;
}
