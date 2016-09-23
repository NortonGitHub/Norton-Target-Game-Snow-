#ifndef idle_h
#define idle_h
#include "Structs.h"

void myInitIdle();

void idleForSanta();
void idleForPresent();
void idleForChildren(int *now_array_num, int now_rank);

void idleDetermineLevel(int *now_array_num, int *now_rank);
void idleGameOver(int *now_array_num, int *now_rank);

void moveChildren(Children *c);

int isChildrenGotPresent(Chara a, Chara b);
double setChildrenCoord(int children_number);
void increaseChildren(Children **c, int num_p);

int isOverlappedOtherChild(Children a, Children c);

Santa santa;
Chara present;//main ƒg idle ‚Åˆµ‚¢‚ªˆÙ‚È‚éH
Children *children;

static double theta;

enum INPUT_KEY{
	NOT,
	LEFT,
	UP,
	RIGHT
};

enum INPUT_KEY input_key;

#endif