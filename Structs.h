#ifndef structs_h
#define structs_h
#include "stdio.h"

#define CHILDREN_SIZE_RATIO 0.35
#define PRESENT_SIZE_RATIO 0.6

enum MODE{
	COME,
	WAIT,
	BACK
};

typedef struct{
	double x;
	double y;
	double z;
}Pos;

typedef struct{
	double radius;
} Collision;

typedef struct{
	Pos pos;
	double direction;
	double frame;
	int isDrawing;	//0:true,1:false
	Collision col;
	/*for present*/
	int onGroundTimer;
	double throwAngle;
} Chara;

typedef struct{
	Chara chara;
	int havingPresent;
	int testFlag;
	int passedPresentNum;
} Santa;

typedef struct{
	Chara chara;
	double theta_x;
	double theta_y;
	enum MODE _nowMode;
} Children;


#endif