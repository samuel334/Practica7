#include "nprcrossover.h"

/*funcion auxiliar para comparar dos enteros*/
int cmp(const void *a, const void *b){
	return (*(int *)a - *(int *)b);
}

/*order crossover*/
void ox1(int c_lgth, int *ch, const int *p1, const int *p2, int f, int l){
	if(f<0 || f>=c_lgth || l<0 || l>=c_lgth) return;
	int i = 0, j, ind = 0, visited = 0;
	int subarray_lgth = l - f + 1;
	while(i<c_lgth){
		if(i>=f && i<=l){ 
			*(ch + i) = *(p1 + i);
		}else{
			*(ch + i) = *(p2 + ind);
			if(visited<subarray_lgth){
				for(j = 0;j<subarray_lgth;j++){
					if(*(p2 + ind)==*(p1 + f + j)){
						visited++;
						i--;
						break;
					}
				}
			}
			ind++;
		}
		i++;
	}
}
/*partially mapped crossover*/
void pmx(int c_lgth, int *ch, const int *p1, const int *p2, int cp1, int cp2){
	if(cp1==cp2 || cp1<0 || cp1>=c_lgth || cp2<=0 || cp2>c_lgth) return;
	cp2--;
	int i, j, visited = 0;
	int subarray_lgth = cp2 - cp1 + 1;
	for(i = 0;i<c_lgth;i++){
		if(i>=cp1 && i<=cp2){ 
			*(ch + i) = *(p2 + i);
		}else{
			*(ch + i) = *(p1 + i);
			if(visited<subarray_lgth){
				j = cp1;
				while(j<=cp2){
					if(*(ch + i)==*(p2 + j)){
						*(ch + i) = *(p1 + j);
						visited++;
						j = cp1;
						continue;
					}
					j++;
				}
			}
		}
	}
}
/*position-based crossover*/
void posx(int c_lgth, int *ch, const int *p1, const int *p2, int i_size, int *index){
	int i = 0, j, ind = 0, visited = 0, curr = 0;
	qsort(index, i_size, sizeof(int), cmp);
	while(i<c_lgth){
		if(curr<i_size && i==index[curr]){ 
			*(ch + i) = *(p1 + i);
			curr++;
		}else{
			*(ch + i) = *(p2 + ind);
			if(visited<i_size){
				for(j = 0;j<i_size;j++){
					if(*(p2 + ind)==*(p1 + index[j])){
						visited++;
						i--;
						break;
					}
				}
			}
			ind++;
		}
		i++;
	}
}
/*order-based crossover*/
void ox2(int c_lgth, int *ch, const int *p1, const int *p2, int i_size, int *index){
	int i = 0, j, curr = 0;
	qsort(index, i_size, sizeof(int), cmp);
	for(i = 0;i<c_lgth;i++){
		*(ch + i) = *(p2 + i);
		if(curr<i_size){
			for(j = 0;j<i_size;j++){
				if(*(p2 + i)==*(p1 + index[j])){
					*(ch + i) = *(p1 + index[curr]);
					curr++;
					break;
				}
			}
		}
	}
}
/*cycle crossover*/
void cx(int *c_size, int *cycle, int c_lgth, int *ch, const int *p1, const int *p2, int f){
	int index[c_lgth];
	int i = f + 1, curr = 0, srch = *(p2 + f);
	cycle[curr] = *(p1 + f);
	index[curr++] = f;
	while(srch!=*(p1 + f)){
		if(*(p1 + i)==srch){
			cycle[curr] = srch;
			index[curr++] = i;
			srch = *(p2 + i);
		}
		i = ( i==(c_lgth - 1) ? 0 : (i + 1) );
	}
	*c_size = curr;
	qsort(index, curr, sizeof(int), cmp);
	curr = 0;
	for(i = 0;i<c_lgth;i++){
		if(i==index[curr]){
			*(ch + i) = *(p1 + i);
			curr++;
		}else{
			*(ch + i) = *(p2 + i);
		}
	}
}
