#ifndef NPRCROSSOVER_H
#define NPRCROSSOVER_H

#include <stdlib.h>

/*order crossover*/
void ox1(int c_lgth, int *ch, const int *p1, const int *p2, int f, int l);
/*partially mapped crossover*/
void pmx(int c_lgth, int *ch, const int *p1, const int *p2, int cp1, int cp2);
/*position-based crossover*/
void posx(int c_lgth, int *ch, const int *p1, const int *p2, int i_size, int *index);
/*order-based crossover*/
void ox2(int c_lgth, int *ch, const int *p1, const int *p2, int i_size, int *index);
/*cycle crossover*/
void cx(int *c_size, int *cycle, int c_lgth, int *ch, const int *p1, const int *p2, int f);

#endif