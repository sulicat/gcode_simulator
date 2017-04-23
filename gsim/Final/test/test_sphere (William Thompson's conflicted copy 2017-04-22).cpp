#include <stdio.h>
#include <iostream>
#include <GL/glut.h>

int window_width = 1200;
int window_height = 1200;
float background_R = 0;
float background_G = 0;
float background_B = 0;
int frame_delay = 10;


void render(int);

void init_glut( void ){
	glClearColor( background_R, background_G, background_B, 1.0 );
	glViewport( 0.0, 0.0, window_width, window_height );
	glutInitDisplayMode(GLUT_RGBA);	
	glMatrixMode( GL_PROJECTION );
	glLoadIdentity();	
	
	glOrtho( 0.0, window_width, window_height, 0.0, 1.0, -1.0 );

	glMatrixMode( GL_MODELVIEW );
	glLoadIdentity();
}

void resize_callback( int x, int y ){
	window_width = x;
	window_height = y;
	init_glut();
}

void display_callback( void ){
	glClearColor( background_R, background_G, background_G, 1.0 );
	glClear( GL_COLOR_BUFFER_BIT );
	glutSwapBuffers();	
	glutTimerFunc( frame_delay, render, 0  );
}


void render(int){
	glutSwapBuffers();
	glutTimerFunc( frame_delay, render, 0  );
}


int main( int argc, char * * argv ){
	
	glutInit( &argc, argv );
	glutInitWindowSize( window_width, window_height );
	glutInitWindowPosition( 0, 0 );
	glutInitDisplayMode( GLUT_DOUBLE );
	glutCreateWindow( "StuSurf" );

	init_glut( );	
	glutDisplayFunc( display_callback );
	glutReshapeFunc( resize_callback );	
	
	

	return 0;
}