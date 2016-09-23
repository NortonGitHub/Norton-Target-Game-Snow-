#include <stdlib.h>
#include <GL/glut.h>
#include <math.h>
#include <time.h>
#include "idle.h"

#define PI 3.14159265359
#define RAND_Coor_X_MAX 8

int array_num_sequence[9] = { 1, 2, 3, 4, 1, 2, 3, 4, 5 };

void myInitIdle(){
	increaseChildren(&children, array_num_sequence[7]);

	theta = 0;
	santa.passedPresentNum = 0;

	input_key = NOT;

	santa.chara.isDrawing = 0;
	santa.havingPresent = 5;
	santa.testFlag = 0;
	present.isDrawing = 1;
	present.frame = 0;
	present.pos.x = 0.0;
	present.pos.y = 0.0;
	present.pos.z = 0.0;
	present.col.radius = 0.3;
	present.onGroundTimer = 0;
	present.throwAngle = 0.0;
}

void increaseChildren(Children **c, int num_p){
	if (NULL == (*c = (Children*)malloc(num_p*sizeof(Children)))){
		exit(EXIT_FAILURE);
	}

	double nearestZero = 10.0;
	double temp_x = 0.0;

	srand((int)time(NULL));
	for (int i = 0; i < num_p; i++){
		(*c + i)->chara.pos.x = setChildrenCoord(num_p);
		(*c + i)->chara.pos.y = -4.0;
		(*c + i)->chara.pos.z = 0.0;
		(*c + i)->chara.isDrawing = 0;
		(*c + i)->_nowMode = COME;
		(*c + i)->chara.col.radius = 0.3;
		(*c + i)->theta_x = (double)(rand() % 360);
		(*c + i)->theta_y = 0.0;
		(*c + i)->chara.frame = 0;
		temp_x = (*c + i)->chara.pos.x;
		if (temp_x*temp_x < nearestZero * nearestZero){
			nearestZero = temp_x;
		}
	}

	for (int i = 0; i < num_p - 1; i++){
		for (int j = i + 1; j < num_p; j++){
			if (isOverlappedOtherChild(*(*c + i), *(*c + j) )== 0){
				(*c + i)->chara.pos.x += (0 == (rand() % 2) ? -1 : 1)*0.5;
			}
		}
	}

}

void idleForSanta(){

	santa.chara.pos.x += 0.0005; 

	if (santa.chara.pos.x >= 7.0){
		santa.chara.pos.x = -7.0;
	}

	double rad = theta * PI / 180;
	double r = 4.0;
	theta = fmod(theta + 0.02, 360.0);
	rad = theta*PI / 45.0;
	santa.chara.pos.y = sin(rad);
}

void idleForPresent(){
	if (present.isDrawing == 0){
		if (present.onGroundTimer == 0){
			present.frame += 0.001;
			double rad = present.throwAngle * PI / 180.0;

			double c = cos(rad);
			double s = sin(rad);

			double acce_x = 3 * c * present.frame;
			double acce_y = 3 * s * present.frame - ((9.8*present.frame*present.frame) / 2);

			present.pos.x += acce_x * 0.001*PRESENT_SIZE_RATIO;
			present.pos.y += acce_y * 0.001*PRESENT_SIZE_RATIO;

			if (present.pos.y <= -2.5){
				present.onGroundTimer = 1;
			}
		}
		else{
			present.onGroundTimer++;
			if (present.onGroundTimer >= 1000){
				present.onGroundTimer = 0;
				present.frame = 0;
				present.isDrawing = 1;
				santa.havingPresent--;
			}
		}
	}
}

void moveChildren(Children *c){
	double rad = c->theta_x * PI / 180;
	c->theta_x = fmod(c->theta_x + 0.02, 360.0);
	rad = c->theta_x*PI / 45.0;
	c->chara.pos.x = sin(rad);

	//rad = c->theta_y * PI / 180;
	//c->theta_y = fmod(c->theta_y + 0.02, 360.0);
	//rad = c->theta_y*PI / 45.0;
	//c->chara.pos.y -= cos(rad);
	//int f = c->chara.frame;

	//c->chara.pos.y =
	//	((sqrt(2.000 * 9.8 * 0.3)*f - 0.500 * 9.8*f*f));//yÀ•W‚ðŒvŽZ
	//c->chara.frame++;
}

void idleForChildren(int *now_array_num, int now_rank){
	for (int i = 0; i < *now_array_num; i++){
		if (now_rank >= 5 && now_rank <= 8){
			moveChildren(&children[i]);
		}

		if (present.isDrawing == 0 && present.onGroundTimer == 0){
			Chara c = children[i].chara;

			if (isChildrenGotPresent(present, c) == 0){
				children[i].chara.isDrawing = 1;
				double _x = children[i].chara.pos.x;
				present.frame = 0;
				present.isDrawing = 1;
				santa.passedPresentNum++;
				santa.havingPresent--;
				break;
			}
		}
	}
}


void idleDetermineLevel(int *now_array_num, int *now_rank){
	if (santa.passedPresentNum >= *now_array_num){
		*now_rank = (*now_rank == 9) ? 1 : *now_rank + 1;
		int n = (*now_rank % 10 <= 0) ? 1 : *now_rank % 10;
		*now_array_num = array_num_sequence[n - 1];
		santa.passedPresentNum = 0;
		santa.havingPresent = 5;
		free(children);
		increaseChildren(&children, *now_array_num);
	}
}

void idleGameOver(int *now_array_num, int *now_rank){
	if (santa.havingPresent <= 0){
		*now_array_num = 1;
		*now_rank = 1;
		free(children);
		myInitIdle();
	}
}

int isChildrenGotPresent(Chara a, Chara b){
	Pos distance;
	double present_x = a.pos.x*PRESENT_SIZE_RATIO;
	double present_y = a.pos.y*PRESENT_SIZE_RATIO;
	double present_z = a.pos.z*PRESENT_SIZE_RATIO;
	double present_rad = a.col.radius*PRESENT_SIZE_RATIO;
	double child_x = b.pos.x*CHILDREN_SIZE_RATIO;
	double child_y = b.pos.y*CHILDREN_SIZE_RATIO;
	double child_z = b.pos.z*CHILDREN_SIZE_RATIO;
	double child_rad = b.col.radius*CHILDREN_SIZE_RATIO;

	distance.x = (present_x - child_x)*(present_x - child_x);
	distance.y = (present_y - child_y)*(present_y - child_y);
	distance.z = (present_z - child_z)*(present_z - child_z);
	
	//ÚG‚µ‚½”»’è
	if (sqrt(distance.x + distance.y + distance.z) <= (present_rad + child_rad)){
		return 0;
	}
	return 1;
}

int isOverlappedOtherChild(Children a, Children b){
	Pos distance;
	double A_x = a.chara.pos.x*CHILDREN_SIZE_RATIO;
	double A_y = a.chara.pos.y*CHILDREN_SIZE_RATIO;
	double A_z = a.chara.pos.z*CHILDREN_SIZE_RATIO;
	double A_rad = a.chara.col.radius*CHILDREN_SIZE_RATIO;
	double B_x = b.chara.pos.x*CHILDREN_SIZE_RATIO;
	double B_y = b.chara.pos.y*CHILDREN_SIZE_RATIO;
	double B_z = b.chara.pos.z*CHILDREN_SIZE_RATIO;
	double B_rad = b.chara.col.radius*CHILDREN_SIZE_RATIO;

	distance.x = (A_x - B_x)*(A_x - B_x);
	distance.y = (A_y - B_y)*(A_y - B_y);
	distance.z = (A_z - B_z)*(A_z - B_z);

	//ÚG‚µ‚½”»’è
	if (sqrt(distance.x + distance.y + distance.z) <= (A_rad + B_rad)){
		return 0;
	}
	return 1;
}


double setChildrenCoord(int children_number){
	return (double)(rand() % RAND_Coor_X_MAX + 1) - 4.0;
}
