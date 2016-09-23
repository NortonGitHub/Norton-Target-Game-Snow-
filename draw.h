#ifndef draw_h
#define draw_h
#include "Structs.h"

void display(void);

void drawSanta(Chara p);
void drawPresent(Chara p);
void drawGround();
void drawChildrenDetail(Chara p);
void drawChildren(Children *c, int now_array_num);
void drawHouse();
void drawTree();

void drawUI(Santa s, int now_rank, int now_array_num);

void drawSquare(double x1, double y1, double x2, double y2, int mode);

#endif