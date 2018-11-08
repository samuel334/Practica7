#include "nprcrossover.h"
#include <stdio.h>
#include <time.h>

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
void print(int i_size, int index[i_size], int c_lgth, const int p1[c_lgth], const int p2[c_lgth], const int ch1[c_lgth], const int ch2[c_lgth]){
	int i;
	printf("\nP1: ");
	for(i = 0;i<c_lgth;i++) printf("%d", p1[i]);	//primer padre
	printf("\t|\tsub-cadena: ");
	for(i = 0;i<c_lgth;i++) (i<i_size) ? printf("%d", p1[index[i]]) : printf(" ") ;	//subcadena
	printf("\t|\tH1: ");
	for(i = 0;i<c_lgth;i++) printf("%d", ch1[i]);	//primer hijo
	printf("\nP2: ");
	for(i = 0;i<c_lgth;i++) printf("%d", p2[i]); //segundo padre
	printf("\t|\tsub-cadena: ");
	for(i = 0;i<c_lgth;i++) (i<i_size) ? printf("%d", p2[index[i]]) : printf(" ") ;	//subcadena
	printf("\t|\tH2: ");
	for(i = 0;i<c_lgth;i++) printf("%d", ch2[i]);	//segundo hijo
	printf("\n\n");
}

/*cruzar poblacion*/
void breeding(int p_lgth, int c_lgth, int child[p_lgth][c_lgth], const int parent[p_lgth][c_lgth]){
	int i = 0, j, aux, temp, r;
	int index[c_lgth];
	for(i = 0;i<c_lgth;i++) index[i] = i;
	i = 0;
	while(i<p_lgth){
		r = rand()%((c_lgth - 2) - (1) + 1) + (1);
		for(j = 0;j<(r - 1);j++){
			aux = rand()%((c_lgth - 1) - j + 1) + j;
			temp = index[aux];
			index[aux] = index[j];
			index[j] = temp;

		}
		ox2(c_lgth, child[i], parent[i], parent[i + 1], r, index);	//generar primer hijo
		ox2(c_lgth, child[i + 1], parent[i + 1], parent[i], r, index);	//invertir roles de padres y generar segundo hijo
		/*imprimir resultados*/
		print(r, index, c_lgth, parent[i], parent[i + 1], child[i], child[i + 1]);
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
