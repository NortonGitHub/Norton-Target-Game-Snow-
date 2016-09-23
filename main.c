#include <stdlib.h>
#include <GL/glut.h>
#include <stdio.h>
#include "main.h"
#include "idle.h"
#include "draw.h"

#define imageWidth		128
#define imageHeight		128

int now_array_num = 1;
int now_rank = 1;

//キーボードイベント
void myKeyboard(unsigned char key, int x, int y){
	if (key == KEY_ESC)
		exit(0);
}

void mySkey(unsigned char key, int x, int y){
	if (present.isDrawing == 1){
		switch (key){
		case GLUT_KEY_LEFT:
			input_key = LEFT;
			present.throwAngle = 150.0;
			break;
#if 0
		case GLUT_KEY_UP:
			input_key = UP;
			present.throwAngle = 90.0;
			break;
#endif
		case GLUT_KEY_RIGHT:
			input_key = RIGHT;
			present.throwAngle = 30.0;
			break;
		default:
			input_key = NOT;
			break;
		}

		if (input_key != NOT){
			present.pos.x = santa.chara.pos.x;
			present.pos.y = santa.chara.pos.y;
			present.isDrawing = 0;
		}
	}
	glutPostRedisplay();
}

void deleteChildrenArray(){
	free(children);
}


//描画関数
void display(void){
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	
	prepareDraw3D();
#if 1
	glEnable(GL_DEPTH_TEST);
	glShadeModel(GLU_FLAT);
	drawGround();

	glEnable(GL_LIGHTING);
	drawSanta(santa.chara);
	drawPresent(present);
	drawChildren(children, now_array_num);
	drawHouse();
	glDisable(GL_LIGHTING);
	glDisable(GL_DEPTH_TEST);
#endif

	glOrtho(0.0, imageWidth, imageHeight, 0.0, -1.0, 1.0);

	prepareDraw2D();

	drawUI(santa, now_rank, now_array_num);
	
	glutSwapBuffers();
}

//初期化関数
void myInit(char *progname){
	int width = 500, height = 500;
	float aspect = (float)width / (float)height;
		
	myInitIdle();


	glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH);
	glutInitWindowSize(500, 500);
	glutInitWindowPosition(0, 0);
	glutCreateWindow(progname);
	glClearColor(0.0, 0.0, 0.0, 1.0);
	glutKeyboardFunc(myKeyboard);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	gluPerspective(60.0, aspect, 1.0, 20.0);

	gluLookAt(0.0, 2.0, 5.0, 0.0, -1.0, 0.0, 0.0, 1.0, 0.0);
	//gluLookAt(0.0, 5.0, 0.001, 0.0, -1.0, 0.0, 0.0, 1.0, 0.0);
	//gluLookAt(4.0, -1.0, 0.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
	//gluLookAt(0.0, 0.0, 6.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
	//gluLookAt(santa.chara.pos.x, 0.0, 6.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);

	glEnable(GL_LIGHT0);
}

void idle(){

	idleForSanta();
	idleForPresent();
	idleForChildren(&now_array_num, now_rank);
	idleDetermineLevel(&now_array_num, &now_rank);
	idleGameOver(&now_array_num, &now_rank);

	glutPostRedisplay();
}

//メイン関数
int main(int argc, char *argv[]){
	glutInit(&argc, argv);
	myInit(argv[0]);
	glutSpecialFunc(mySkey);
	glutDisplayFunc(display);
	glutIdleFunc(idle);
	glutMainLoop();
	deleteChildrenArray();
	return 0;
}

void prepareDraw2D(){
	glMatrixMode(GL_PROJECTION);// 射影変換行列設定
	glPushMatrix();// 現在の射影変換行列を保存
	glOrtho(0, imageWidth, imageHeight, 0, -1, 1);// 正射影変換設定
	glMatrixMode(GL_MODELVIEW);// モデルビュー変換行列設定
	glPushMatrix();// 現在のモデルビュー行列を保存
	glLoadIdentity();// 単位行列を設定
}

void prepareDraw3D(){
	glMatrixMode(GL_PROJECTION);// 射影変換行列設定
	glPopMatrix();// 射影変換行列を復元
	glMatrixMode(GL_MODELVIEW);// モデルビュー変換行列設定
	glPopMatrix();// モデルビュー行列を復元
	glLoadIdentity();// 単位行列を設定
}
