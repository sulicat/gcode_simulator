#include <GL/glut.h>

GLfloat xRotated, yRotated, zRotated;
GLdouble radius=0.1;

int window_width = 1200;
int window_height = 800;

void display(void);
void reshape(int x, int y);
 






class PARTICLE{
public:
	int x;
	int y;
	int z;
	GLdouble radius;
	float x_rotation;
	float y_rotation;
	float z_rotation;

	PARTICLE(){
		x = 0;
		y = 0;
		z = 0;
		radius = 1;
	}


	PARTICLE( int _x, int _y, int _z ){
		x = _x;
		y = _y;
		z = _z;
		radius = 1;
	}

	PARTICLE( int _x, int _y, int _z, int _r ){
		x = _x;
		y = _y;
		z = _z;
		radius = _r;
	}

	void set_pos( int _x, int _y, int _z ){
		x = _x;
		y = _y;
		z = _z;
	}

	void set_radius( int _r ){
		radius = _r;
	}

	void render(){
	   	glMatrixMode(GL_MODELVIEW);
    	// clear the drawing buffer.
	    glClear(GL_COLOR_BUFFER_BIT);
	    // clear the identity matrix.
	    glLoadIdentity();
	    // traslate the draw by z = -4.0
	    // Note this when you decrease z like -8.0 the drawing will looks far , or smaller.
	    glTranslatef(0.0,0.0,-5.0);
	    // Red color used to draw.
	    glColor3f(0.9, 0.3, 0.2); 
	    // changing in transformation matrix.
	    // rotation about X axis
	    glRotatef(xRotated,1.0,0.0,0.0);
	    // rotation about Y axis
	    glRotatef(yRotated,0.0,1.0,0.0);
	    // rotation about Z axis
	    glRotatef(zRotated,0.0,0.0,1.0);
	    // scaling transfomation 
	    glScalef(1.0,1.0,1.0);
	    glutSolidSphere(radius,20,20);

	}

};




PARTICLE patricle_1 = PARTICLE( 100, 100, 5, 2 );

class SIMULATION{
public:
	int x;
	int y;
	int width;
	int height;

	PARTICLE * particles;
	int particles_len;

	SIMULATION(){
		x = 0;
		y = 0;
		width = 100;
		heigh = 100;		
	}

	SIMULATION( int _x, int _y ){
		x = _x;
		y = _y;
		width = 100;
		heigh = 100;
	}

	SIMULATION( int _x, int _y, int _width, int _height ){
		x = _x;
		y = _y;
		width = _width;
		heigh = _height;
	}




};






void init_glut( void ){
	glClearColor( 0, 0, 0, 1.0 );
	glViewport( 0.0, 0.0, window_height, window_height );
	glutInitDisplayMode(GLUT_RGBA);	
	glMatrixMode( GL_PROJECTION );
	glLoadIdentity();	
	
	glOrtho( 0.0, window_width, window_height, 0.0, 1.0, -1.0 );

	glMatrixMode( GL_MODELVIEW );
	glLoadIdentity();
}


int main (int argc, char **argv)
{
 /*   glutInit(&argc, argv); 
    glutInitWindowSize(350,350);
    glutCreateWindow("Solid Sphere");
  	glutInitDisplayMode( GLUT_DOUBLE );*/

  	glutInit( &argc, argv );
	glutInitWindowSize( window_width, window_height );
	glutInitWindowPosition( 0, 0 );
	glutInitDisplayMode( GLUT_DOUBLE );
	glutCreateWindow( "StuSurf" );

	init_glut( );	

    xRotated = yRotated = zRotated = 30.0;
    xRotated=43;
    yRotated=50;
 
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutMainLoop();
    return 0;
}


void render( int a ){
/*
    glMatrixMode(GL_MODELVIEW);
    // clear the drawing buffer.
    glClear(GL_COLOR_BUFFER_BIT);
    // clear the identity matrix.
    glLoadIdentity();
    // traslate the draw by z = -4.0
    // Note this when you decrease z like -8.0 the drawing will looks far , or smaller.
    glTranslatef(0.0,0.0,-5.0);
    // Red color used to draw.
    glColor3f(0.9, 0.3, 0.2); 
    // changing in transformation matrix.
    // rotation about X axis
    glRotatef(xRotated,1.0,0.0,0.0);
    // rotation about Y axis
    glRotatef(yRotated,0.0,1.0,0.0);
    // rotation about Z axis
    glRotatef(zRotated,0.0,0.0,1.0);
    // scaling transfomation 
    glScalef(1.0,1.0,1.0);
    glutSolidSphere(radius,20,20);

    glutSwapBuffers();        

    xRotated += 1;
    yRotated -= 2;

*/

	patricle_1.render();

    glutSwapBuffers();        
	glutTimerFunc( 20, render, 0 );
}

void display(void){


    glutTimerFunc( 20, render, 0 );


}

void reshape(int x, int y)
{
    if (y == 0 || x == 0) return;   
    glMatrixMode(GL_PROJECTION);  
    glLoadIdentity(); 
    gluPerspective(39.0,(GLdouble)x/(GLdouble)y,0.6,21.0);
    glMatrixMode(GL_MODELVIEW);
    glViewport(0,0,x,y);  //Use the whole window for rendering
}