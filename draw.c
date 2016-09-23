#include <GL/glut.h>
#include "draw.h"

float diffuse[4][4] = {
	{ 0.5, 0.0, 0.0, 1.0 },//服や生地の布
	{ 0.5, 0.46, 0.37, 1.0 },//肌
	{ 0.27, 0.12, 0.0, 1.0 },//木
	{ 0.5, 0.5, 0.5, 0.5 }//袋の布
};

float specular[4][4] = {
	{ 0.0, 0.0, 0.0, 1.0 },//服や生地の布
	{ 0.0, 0.0, 0.0, 1.0 },//肌
	{ 0.1, 0.1, 0.1, 1.0 },//木
	{ 0.0, 0.0, 0.0, 1.0 }//袋の布
};

float ambient[4][4] =
{ { 1.0, 0.0, 0.0, 1.0 },//服や生地の布
{ 1.0, 0.93, 0.75, 1.0 },//肌
{ 0.54, 0.23, 0.0, 1.0 },//木
{ 1.0, 1.0, 1.0, 1.0 }//袋の布
};

float shininess[4] = { 50.0, 30.0, 12.8, 50.0 };

void drawSanta(Chara p){
	glPushMatrix();
	glScaled(0.6, 0.6, 0.6);
#if 1
	/*body*/
	glPushMatrix();

	glMaterialfv(GL_FRONT, GL_DIFFUSE, diffuse[0]);
	glMaterialfv(GL_FRONT, GL_SPECULAR, specular[0]);
	glMaterialfv(GL_FRONT, GL_AMBIENT, ambient[0]);
	glMaterialf(GL_FRONT, GL_SHININESS, shininess[0]);

	glColor3d(1.0, 0.0, 0.0);
	glTranslated(p.pos.x, p.pos.y, p.pos.z);
	glRotated(-90.0, 1.0, 0.0, 0.0);
	glutSolidCone(0.3, 1.0, 8, 8);
	glPopMatrix();

	/*hat*/
	glPushMatrix();
	glColor3d(1.0, 0.0, 0.0);
	glTranslated(p.pos.x, p.pos.y + 1.2, p.pos.z);
	glRotated(-90.0, 1.0, 0.0, 0.0);
	glutSolidCone(0.25, 0.4, 8, 5);
	glPopMatrix();

	/*head*/
	glPushMatrix();

	glMaterialfv(GL_FRONT, GL_DIFFUSE, diffuse[1]);
	glMaterialfv(GL_FRONT, GL_SPECULAR, specular[1]);
	glMaterialfv(GL_FRONT, GL_AMBIENT, ambient[1]);
	glMaterialf(GL_FRONT, GL_SHININESS, shininess[1]);

	glColor3d(1.0, 0.94, 0.78);
	glTranslated(p.pos.x, p.pos.y + 1.0, p.pos.z);
	glutSolidSphere(0.25, 10, 10);
	glPopMatrix();
#endif
	/*sled*/
	glPushMatrix();

	glMaterialfv(GL_FRONT, GL_DIFFUSE, diffuse[2]);
	glMaterialfv(GL_FRONT, GL_SPECULAR, specular[2]);
	glMaterialfv(GL_FRONT, GL_AMBIENT, ambient[2]);
	glMaterialf(GL_FRONT, GL_SHININESS, shininess[2]);

	glColor3d(0.65, 0.16, 0.16);
	glTranslated(p.pos.x, p.pos.y, p.pos.z);
	glScaled(2.0, 0.5, 1.0);
	glRotated(p.direction, 0.0, 1.0, 0.0);
	glutSolidCube(1.0);
	glPopMatrix();
#if 1
	/*bag*/
	glPushMatrix();
	glMaterialfv(GL_FRONT, GL_DIFFUSE, diffuse[3]);
	glMaterialfv(GL_FRONT, GL_SPECULAR, specular[3]);
	glMaterialfv(GL_FRONT, GL_AMBIENT, ambient[3]);
	glMaterialf(GL_FRONT, GL_SHININESS, shininess[3]);

	glColor3d(1.0, 1.0, 1.0);
	glTranslated(p.pos.x - 0.5, p.pos.y + 0.5, p.pos.z);
	glutSolidSphere(0.5, 12, 12);
	glPopMatrix();
#endif
	glPopMatrix();
}

void drawPresent(Chara p){
	if (p.isDrawing == 0){
#if 1
		glPushMatrix();
		//0.6倍になった座標で計算していた！うっわああ
		glMaterialfv(GL_FRONT, GL_DIFFUSE, diffuse[0]);
		glMaterialfv(GL_FRONT, GL_SPECULAR, specular[0]);
		glMaterialfv(GL_FRONT, GL_AMBIENT, ambient[0]);
		glMaterialf(GL_FRONT, GL_SHININESS, shininess[0]);

		glColor3d(1.0, 0.94, 0.78);
		glScaled(PRESENT_SIZE_RATIO, PRESENT_SIZE_RATIO, PRESENT_SIZE_RATIO);
		glTranslated(p.pos.x, p.pos.y, p.pos.z);
		glutSolidCube(PRESENT_SIZE_RATIO);

		glPopMatrix();
#endif
		glPushMatrix();
		glScaled(PRESENT_SIZE_RATIO, PRESENT_SIZE_RATIO, PRESENT_SIZE_RATIO);
		glColor3d(1.0, 1.0, 1.0);
		glTranslated(p.pos.x, p.pos.y, p.pos.z);
		glutWireSphere(p.col.radius, 4, 4);
		glPopMatrix();
	}
}

void drawGround(){
#if 1
	glBegin(GL_QUAD_STRIP);
	glPushMatrix();
	glColor3d(0.93, 0.93, 0.93);
	glVertex3d(-100.0,-1.665, -100.0);
	glVertex3d(-100.0, -1.665, 100.0);
	glVertex3d(100.0, -1.665, -100.0);
	glVertex3d(100.0, -1.665, 100.0);
	glEnd();
	glPopMatrix();

	glPushMatrix();
	glBegin(GL_QUAD_STRIP);
	glColor3d(0.42, 0.42, 0.42);
	glVertex3d(-100.0, -1.664, -2.0);
	glVertex3d(-100.0, -1.664, 1.0);
	glVertex3d(100.0, -1.664, -2.0);
	glVertex3d(100.0, -1.664,1.0);
	glEnd();
	glPopMatrix();


	glPushMatrix();
	glColor3d(0.86, 0.86, 0.86);
	for (int i = 0; i < 3; i++){
		glPushMatrix();
		glBegin(GL_QUAD_STRIP);
		glVertex3d(i * 4 - 6, -1.663, -0.65);
		glVertex3d(i * 4 - 6, -1.663, -0.45);
		glVertex3d(i * 4 - 3, -1.663, -0.65);
		glVertex3d(i * 4 - 3, -1.663, -0.45);
		glEnd();
		glPopMatrix();
	}
	glPopMatrix();

#endif
}

void drawChildrenDetail(Children p){
	glPushMatrix();
	glScaled(CHILDREN_SIZE_RATIO,CHILDREN_SIZE_RATIO,CHILDREN_SIZE_RATIO);

#if 1
	/*body*/
	glPushMatrix();

	glMaterialfv(GL_FRONT, GL_DIFFUSE, diffuse[0]);
	glMaterialfv(GL_FRONT, GL_SPECULAR, specular[0]);
	glMaterialfv(GL_FRONT, GL_AMBIENT, ambient[0]);
	glMaterialf(GL_FRONT, GL_SHININESS, shininess[0]);

	glColor3d(1.0, 0.0, 0.0);
	glTranslated(p.chara.pos.x, p.chara.pos.y, p.chara.pos.z);
	glRotated(-90.0, 1.0, 0.0, 0.0);
	glutSolidCone(0.3, 1.0, 8, 8);
	glPopMatrix();

	/*hat*/
	glPushMatrix();
	glColor3d(1.0, 0.0, 0.0);
	glTranslated(p.chara.pos.x, p.chara.pos.y + 1.2, p.chara.pos.z);
	glRotated(-90.0, 1.0, 0.0, 0.0);
	glutSolidCone(0.25, 0.4, 8, 6);
	glPopMatrix();

	/*head*/
	glPushMatrix();

	glMaterialfv(GL_FRONT, GL_DIFFUSE, diffuse[1]);
	glMaterialfv(GL_FRONT, GL_SPECULAR, specular[1]);
	glMaterialfv(GL_FRONT, GL_AMBIENT, ambient[1]);
	glMaterialf(GL_FRONT, GL_SHININESS, shininess[1]);

	glColor3d(1.0, 0.94, 0.78);
	glTranslated(p.chara.pos.x, p.chara.pos.y + 1.0, p.chara.pos.z);
	glutSolidSphere(0.25, 10, 10);
	glPopMatrix();
#endif
#if 0
	glPushMatrix();
	glTranslated(p.chara.pos.x,p.chara.pos.y,p.chara.pos.z);
	glutWireSphere(p.chara.col.radius, 4, 4);
	glPopMatrix();
#endif
	glPopMatrix();
}

void drawChildren(Children *c, int now_array_num){
	glPushMatrix();

	for (int i = 0; i < now_array_num; i++){
		if (c[i].chara.isDrawing == 0){
			drawChildrenDetail(c[i]);
		}
	}

	glPopMatrix();
}

void drawHouse(){
	glPushMatrix();

	glMaterialfv(GL_FRONT, GL_DIFFUSE, diffuse[2]);
	glMaterialfv(GL_FRONT, GL_SPECULAR, specular[2]);
	glMaterialfv(GL_FRONT, GL_AMBIENT, ambient[2]);
	glMaterialf(GL_FRONT, GL_SHININESS, shininess[2]);

	glColor3d(1.0, 0.94, 0.78);
	glTranslated(0, -1.0, -8.0);
	glutSolidCube(5.0);

	glPopMatrix();
}

void drawUI(Santa s, int now_rank, int now_array_num){

	glColor3d(1.0, 0.94, 0.0);
	for (int i = 0; i < s.havingPresent; i++){
		glPushMatrix();
/*		glTranslated(i*0.5 - 2.5, 1.8, -0.5);
		glutSolidCube(0.3);*/
		drawSquare(i * 10 - 100, -40, i * 10 - 90, -30, 0);
		glPopMatrix();
	}

#if 1
	glColor3d(0.0, 1.0, 0.0);
	for (int i = 0; i < now_array_num; i++){
		glPushMatrix();
		//glTranslated(i*0.5 - 2.5, 1.4, -0.5);
		if (i < s.passedPresentNum){
			//glutSolidCube(0.3);
			drawSquare(i * 10 - 100, -25, i * 10 - 90, -15, 0);
		}
		else{
			//glutWireCube(0.3);
			drawSquare(i * 10 - 100, -25, i * 10 - 90, -15, 1);
		}
		glPopMatrix();
	}

	/*周回ポイント*/
	glColor3d(0.0, 0.0, 1.0);
	for (int i = 0; i < now_rank / 10; i++){
		glPushMatrix();
		//glTranslated(i*0.5 - 2.5, 0.85, -0.5);
		//glutSolidCube(0.6);
		drawSquare(i * 10 - 100, 5, i * 10 - 95, 10, 0);
		glPopMatrix();
	}

	glColor3d(0.0, 0.0, 0.7);
	for (int i = 0; i < now_rank % 10; i++){
		glPushMatrix();
		//glTranslated((i*0.5 - 2.5) + (now_rank / 10)*0.5, 1.0, -0.5);
		//glutSolidCube(0.3);
		drawSquare(i * 10 - 100, -10, i * 10 - 90, 0, 0);
		glPopMatrix();
	}

#endif
}

void drawSquare(double x1, double y1, double x2, double y2,int mode){
	glBegin((mode == 0) ? GL_QUADS : GL_LINE_LOOP);
	glVertex2d(x1, y1);
	glVertex2d(x2, y1);
	glVertex2d(x2, y2);
	glVertex2d(x1, y2);
	glEnd();
}