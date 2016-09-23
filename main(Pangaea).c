#include <stdlib.h>
#include <GL/glut.h>
#include <math.h>
#include <stdio.h>

#define KEY_ESC 27
#define PI 3.14159265359
#define imageWidth		128
#define imageHeight		128

typedef struct{
	double x;
	double y;
	double z;
}Pos;

typedef struct{
	double radius;
	Pos pos;
} Collision;

typedef struct{
	Pos pos;
	double direction;
	double frame;
	int isDrawing;	//0:true,1:false
	Collision col;
} Chara;

Chara santa;
Chara present;
Chara *children;




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

double theta = 0.0;
double thetaY = 0.0;
double thetaM = 0.0;

int rand_max = 8;

int now_array_num = 2;
int now_rank = 1;

//キーボードイベント
void myKeyboard(unsigned char key, int x, int y){
	if (key == KEY_ESC)
		exit(0);
}

void mySkey(unsigned char key, int x, int y){
	if (key ==GLUT_KEY_DOWN && present.isDrawing == 1){
		present.pos.x = santa.pos.x;
		present.pos.y = santa.pos.y;
		present.isDrawing = 0;
	}
	glutPostRedisplay();
}

double setChildrenCoord(int children_number){
	return (double)(rand() % rand_max + 1) - 4.0;
}

void increaseChildren(Chara **c, int num_p){

	if (NULL == (*c = (Chara*)malloc(num_p*sizeof(Chara)))){
		exit(EXIT_FAILURE);
	}

	srand((int)time(NULL));
	for (int i = 0; i < num_p; i++){
		(*c + i)->pos.x = setChildrenCoord(num_p);
		(*c + i)->pos.y = -4.0;
		(*c + i)->pos.z = 0.0;
		(*c + i)->isDrawing = 0;
	}
}

void deleteChildrenArray(){
	free(children);
}

int isChildrenGotPresent(Collision a,Collision b){
	Pos distance;
	distance.x = (a.pos.x - b.pos.x)*(a.pos.x - b.pos.x);
	distance.y = (a.pos.y - b.pos.y)*(a.pos.y - b.pos.y);
	distance.z = (a.pos.z - b.pos.z)*(a.pos.z - b.pos.z);

	//接触した！
	if (sqrt(distance.x + distance.y + distance.z) <= a.radius + b.radius){
		return 0;
	}
	return 1;
}


void drawSanta(double _x,double _y,double _z,double _d){
	glPushMatrix();
	glScaled(0.6, 0.6, 0.6);

	/*body*/
	glPushMatrix();

	glMaterialfv(GL_FRONT, GL_DIFFUSE, diffuse[0]);
	glMaterialfv(GL_FRONT, GL_SPECULAR, specular[0]);
	glMaterialfv(GL_FRONT, GL_AMBIENT, ambient[0]);
	glMaterialf(GL_FRONT, GL_SHININESS, shininess[0]);

	glColor3d(1.0, 0.0, 0.0);
	glTranslated(_x, _y, _z);
	glRotated(-90.0, 1.0, 0.0, 0.0);
	glutSolidCone(0.3, 1.0, 20, 20);
	glPopMatrix();

	/*hat*/
	glPushMatrix();
	glColor3d(1.0, 0.0, 0.0);
	glTranslated(_x, _y + 1.2, _z);
	glRotated(-90.0, 1.0, 0.0, 0.0);
	glutSolidCone(0.25, 0.4, 16, 10);
	glPopMatrix();

	/*head*/
	glPushMatrix();

	glMaterialfv(GL_FRONT, GL_DIFFUSE, diffuse[1]);
	glMaterialfv(GL_FRONT, GL_SPECULAR, specular[1]);
	glMaterialfv(GL_FRONT, GL_AMBIENT, ambient[1]);
	glMaterialf(GL_FRONT, GL_SHININESS, shininess[1]);

	glColor3d(1.0, 0.94, 0.78);
	glTranslated(_x, _y + 1.0, _z);
	glutSolidSphere(0.25, 10, 10);
	glPopMatrix();

	/*sled*/
	glPushMatrix();

	glMaterialfv(GL_FRONT, GL_DIFFUSE, diffuse[2]);
	glMaterialfv(GL_FRONT, GL_SPECULAR, specular[2]);
	glMaterialfv(GL_FRONT, GL_AMBIENT, ambient[2]);
	glMaterialf(GL_FRONT, GL_SHININESS, shininess[2]);

	glColor3d(0.65, 0.16, 0.16);
	glTranslated(_x, _y, _z);
	glScaled(2.0, 0.5, 1.0);
	glRotated(_d, 0.0, 1.0, 0.0);
	glutSolidCube(1.0);
	glPopMatrix();

	/*bag*/
	glPushMatrix();
	glMaterialfv(GL_FRONT, GL_DIFFUSE, diffuse[3]);
	glMaterialfv(GL_FRONT, GL_SPECULAR, specular[3]);
	glMaterialfv(GL_FRONT, GL_AMBIENT, ambient[3]);
	glMaterialf(GL_FRONT, GL_SHININESS, shininess[3]);

	glColor3d(1.0, 1.0, 1.0);
	glTranslated(_x - 0.5, _y + 0.5, _z);
	glutSolidSphere(0.5, 16, 16);
	glPopMatrix();

	glPopMatrix();
}

void drawPresent(double _x, double _y, double _z, double _d){
	if (present.isDrawing == 0){
		glPushMatrix();
		glScaled(0.6, 0.6, 0.6);

		glMaterialfv(GL_FRONT, GL_DIFFUSE, diffuse[0]);
		glMaterialfv(GL_FRONT, GL_SPECULAR, specular[0]);
		glMaterialfv(GL_FRONT, GL_AMBIENT, ambient[0]);
		glMaterialf(GL_FRONT, GL_SHININESS, shininess[0]);

		glColor3d(1.0, 0.94, 0.78);
		glTranslated(_x, _y, _z);
		glutSolidCube(0.6);

		glPopMatrix();
	}
}

void drawGround(){
	glPushMatrix();
	//glTranslated(0.0, -5.0, 0.0);
	glBegin(GL_QUAD_STRIP);
	glColor3d(0.93, 0.93, 0.93);
	glVertex3d(-100.0, -5.0, -100.0);
	glVertex3d(-100.0, -5.0, 100.0);
	glVertex3d(100.0, -5.0, -100.0);
	glVertex3d(100.0, -5.0, 100.0);
	glEnd();
	glPopMatrix();
}

void drawChildrenDetail(double _x, double _y, double _z){
	glPushMatrix();
	glScaled(0.35, 0.35, 0.35);

	/*body*/
	glPushMatrix();

	glMaterialfv(GL_FRONT, GL_DIFFUSE, diffuse[0]);
	glMaterialfv(GL_FRONT, GL_SPECULAR, specular[0]);
	glMaterialfv(GL_FRONT, GL_AMBIENT, ambient[0]);
	glMaterialf(GL_FRONT, GL_SHININESS, shininess[0]);

	glColor3d(1.0, 0.0, 0.0);
	glTranslated(_x, _y, _z);
	glRotated(-90.0, 1.0, 0.0, 0.0);
	glutSolidCone(0.3, 1.0, 20, 20);
	glPopMatrix();

	/*hat*/
	glPushMatrix();
	glColor3d(1.0, 0.0, 0.0);
	glTranslated(_x, _y + 1.2, _z);
	glRotated(-90.0, 1.0, 0.0, 0.0);
	glutSolidCone(0.25, 0.4, 16, 10);
	glPopMatrix();

	/*head*/
	glPushMatrix();

	glMaterialfv(GL_FRONT, GL_DIFFUSE, diffuse[1]);
	glMaterialfv(GL_FRONT, GL_SPECULAR, specular[1]);
	glMaterialfv(GL_FRONT, GL_AMBIENT, ambient[1]);
	glMaterialf(GL_FRONT, GL_SHININESS, shininess[1]);

	glColor3d(1.0, 0.94, 0.78);
	glTranslated(_x, _y + 1.0, _z);
	glutSolidSphere(0.25, 10, 10);
	glPopMatrix();

	glPopMatrix();
}

void drawChildren(Chara *c){
	glPushMatrix();
	
	for (int i = 0; i < now_array_num; i++){
		drawChildrenDetail(c[i].pos.x, c[i].pos.y, c[i].pos.z);
	}

	glPopMatrix();
}

//描画関数
void display(void){
	int i;
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glPushMatrix();

	glEnable(GL_DEPTH_TEST);
	glShadeModel(GLU_FLAT);
	drawGround();

	glEnable(GL_LIGHTING);
	drawSanta(santa.pos.x, santa.pos.y, santa.pos.z, santa.direction);
	drawPresent(present.pos.x, present.pos.y, present.pos.z, present.direction);
	drawChildren(children);

	glDisable(GL_LIGHTING);

	glDisable(GL_DEPTH_TEST);
	glPopMatrix();
	glutSwapBuffers();
}

//初期化関数
void myInit(char *progname){
	int width = 500, height = 500;
	float aspect = (float)width / (float)height;

	santa.isDrawing = 0;
	present.isDrawing = 1;
	present.frame = 0;
	
	increaseChildren(&children, 2);

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

	glEnable(GL_LIGHT0);
}

void idleForSanta(){
	theta = fmod(theta + 0.02, 360.0);
	double rad = theta * PI / 180;
	double r = 4.0;

	santa.pos.x += 0.0005; //r * sin(rad) - 3.0;
	//santa.pos.z = r * cos(rad);

	if (santa.pos.x >= 7.0){
		santa.pos.x = -7.0;
	}

	thetaY = fmod(thetaY + 0.02, 360.0);
	rad = thetaY*PI / 45.0;
	santa.pos.y = sin(rad);
}

void idleForPresent(){
	if (present.isDrawing == 0){
		present.frame += 0.001;
		double rad =  150.0 * PI / 180.0;

		double c = cos(rad);
		double s = sin(rad);

		double acce_x = 3 * c * present.frame;
		double acce_y = 3 * s * present.frame - ((9.8*present.frame*present.frame)/2);

		present.pos.x += acce_x * 0.001;
		present.pos.y += acce_y * 0.001;

		if (present.pos.y <= -10.0){
			present.frame = 0;
			present.isDrawing = 1;
		}
	}

	present.col.pos = present.pos;
}

void moveChildren(){

}

void idleForChildren(){
	for (int i = 0; i < now_array_num; i++){
		if (now_rank >= 5){
			moveChildren();
		}

		if (isChildrenGotPresent(present.col, children[i].col)){

		}

	}
}

void idle(){

	idleForSanta();
	idleForPresent();
	idleForChildren();

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
