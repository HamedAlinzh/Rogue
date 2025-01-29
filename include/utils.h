#ifndef UTILS_H
#define UTILS_H
#include "rogue.h"
void pathind(Position *start, Position *end);
void addposYX(int **frontier, int y, int x, int count);
int addnearby(int **frontier, int ***comefrom, int count, int y, int x);
#endif

