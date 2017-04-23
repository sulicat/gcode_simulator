#include <stdio.h>
#include <iostream>
#include <fstream>
#include "GL/glut.h"
#include "../GCODE/GCODE.h"
#include "UI.h"

/* written by Suleiman Barakat in March 2017
	This is a tool to help me replace paper with just the tablet. */

#define FUNCTIONALITY_TYPE_REG 			"function_reg"
#define FUNCTIONALITY_LINUX_COMMAND 	"function_linux_command"

#define GET_INPUT_TYPE_DRAWAREA		1
#define BUTTON_REG 					2

#define IMAGE_TYPE_RGB 				4
#define IMAGE_TYPE_GREYSCALE 		5


void display_callback( void );
void render( int );
void init_glut( void );
void resize_callback( int, int );
void active_mouse_move_callback( int x, int y );
bool check_inside( int x, int y, int w, int h, int x2, int y2 );


// **************************************************************************************************************************************************** //



int main( int argc, char * * argv ){
	glutInit( &argc, argv );
	glutInitWindowSize( window_width, window_height );
	glutInitWindowPosition( 0, 0 );
	glutInitDisplayMode( GLUT_DOUBLE );
	glutCreateWindow( "StuSurf" );

	init_glut( );	
	glutDisplayFunc( display_callback );
	glutReshapeFunc( resize_callback );	
	glutMotionFunc( active_mouse_move_callback );
	glutPassiveMotionFunc( mouse_move_callback );
	glutMouseFunc( mouse_press_callback );

//	window.set_fullscreen( true );


	// MAIN screen

	IMAGE white_img = IMAGE( (char *)"images/white.bmp" );
	white_img.load();
	white_img.set_size( window_width, window_height );
	white_img.set_pos( 0, 0 );


	IMAGE title = IMAGE((char *)"images/title.bmp");
	title.load();
	title.set_size( 200,200 );
	title.set_pos( window_width/2 - 100, window_height/4 - 100 );


	IMAGE select_gcode_button = IMAGE((char *)"images/select_gcode_button.bmp");
	select_gcode_button.load();
	select_gcode_button.set_size( 200,100 );
	select_gcode_button.set_pos( window_width/3 - 100, window_height/1.5 - 50 );
	select_gcode_button.add_click_callback( press_gcode_select );

	IMAGE run_button = IMAGE((char *)"images/run_button.bmp");
	run_button.load();
	run_button.set_size( 200,100 );
	run_button.set_pos( 2 * window_width/3 - 100, window_height/1.5 - 50 );
	run_button.add_click_callback( start_simulation );


	SCREEN main_menu = SCREEN("Gsim");
	main_menu.add( white_img );
	main_menu.add( title );
	main_menu.add( select_gcode_button );
	main_menu.add( run_button );



	// 3D render screen

	SCREEN render = SCREEN("render");

	IMAGE home_button = IMAGE( (char *)"images/home_button.bmp" );
	home_button.load();
	home_button.set_size(150, 75);
	home_button.set_pos( window_width * 0.9 - 150, window_height * 0.05  );
	home_button.add_click_callback( return_home );


	render.add( white_img );
	render.add( home_button );

	PARTICLE p = PARTICLE( 200, 200, 10, 10 );
	PARTICLE p2 = PARTICLE( 200, 200, -10, 10 );
	p2.set_color( 0.1, 1, 0 );
	render.add( p );
	render.add( p2 );



	window.add_screen( main_menu );
	window.add_screen( render );
	window.set_current_screen( 0 );

	

	glutMainLoop();

	return 0;

}
