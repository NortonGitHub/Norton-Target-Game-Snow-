#include <stdlib.h>
#include <GL/glut.h>
#if 0

GLuint load(const char *path){
	int g_width, g_height;
	unsigned char *data;


	GLuint tex;
	glGenTextures(1, &tex);

	glBindTexture(GL_TEXTURE_2D, tex);

	gluBuild2DMipmaps(GL_TEXTURE_2D, 3, g_width, g_height, GL_RGB, GL_UNSIGNED_BYTE, data);
	
	free(data);
	
	return tex;
}
#endif