#include <stdio.h>
#include <iostream>
#include <GL/glut.h>


void init_glut( void ){
	glClearColor( background_R, background_G, background_G, 1.0 );
	glViewport( 0.0, 0.0, window_width, window_height );
	glutInitDisplayMode(GLUT_RGBA);	
	glMatrixMode( GL_PROJECTION );
	glLoadIdentity();	
	
	glOrtho( 0.0, window_width, window_height, 0.0, 1.0, -1.0 );

	glMatrixMode( GL_MODELVIEW );
	glLoadIdentity();
}



int main( int argc, char * * argv ){
	
	

	return 0;
}