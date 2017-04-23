#include <GL/glut.h>
#include <stdlib.h>
#include <iostream>


GLdouble radius=0.1;

int window_width = 1200;
int window_height = 800;

void display(void);
void reshape(int x, int y);
 






class PARTICLE{
public:
	float x;
	float y;
	float z;
	GLdouble radius;
	float x_rotation;
	float y_rotation;
	float z_rotation;

	float R;
	float G;
	float B;

	void set_clear_vals(){
		R = 1;
		G = 0;
		B = 0;
		x_rotation = 0;
		y_rotation = 0;
		z_rotation = 0;
	}

	PARTICLE(){
		x = 0;
		y = 0;
		z = 0;
		radius = 1;
		set_clear_vals();
	}


	PARTICLE( float _x, float _y, float _z ){
		x = _x;
		y = _y;
		z = _z;
		radius = 1;
		set_clear_vals();
	}

	PARTICLE( float _x, float _y, float _z, GLdouble _r ){
		x = _x;
		y = _y;
		z = _z;
		radius = _r;
		set_clear_vals();
	}

	void set_pos( float _x, float _y, float _z ){
		x = _x;
		y = _y;
		z = _z;
	}

	void set_radius( GLdouble _r ){
		radius = _r;
	}

	void set_color( float _r, float _g, float _b ){
		R = _r;
		G = _g;
		B = _b;
	}

	void render(){
	   	glMatrixMode(GL_MODELVIEW);
	    // clear the identity matrix.
	    glLoadIdentity();
	    // traslate the draw by z = -4.0
	    // Note this when you decrease z like -8.0 the drawing will looks far , or smaller.
	    glTranslatef( x, y, z);
	    // Red color used to draw.
	    glColor3f( R, G, B ); 
	    // changing in transformation matrix.
	    // rotation about X axis
	    glRotatef(x_rotation,1.0,0.0,0.0);
	    // rotation about Y axis
	    glRotatef(y_rotation,0.0,1.0,0.0);
	    // rotation about Z axis
	    glRotatef(z_rotation,0.0,0.0,1.0);
	    // scaling transfomation 
	    glScalef(1.0,1.0,1.0);
	    glutSolidSphere(radius,20,20);

	}

};




PARTICLE patricle_1 = PARTICLE( 0.4, 1, -4, 0.1 );
PARTICLE patricle_2 = PARTICLE( 0.4, 1, -4.1, 0.1 );




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
		height = 100;
		particles_len = 0;		
	}

	SIMULATION( int _x, int _y ){
		x = _x;
		y = _y;
		width = 100;
		height = 100;
		particles_len = 0;
	}

	SIMULATION( int _x, int _y, int _width, int _height ){
		x = _x;
		y = _y;
		width = _width;
		height = _height;
	}

	void add_particle( float _x, float _y, float _z, GLdouble _r ){
		PARTICLE * temp = new PARTICLE[ particles_len + 1 ];
		std::copy( particles, particles + particles_len, temp );
		temp[ particles_len ] = PARTICLE( _x, _y, _z, _r );
		particles = temp;
		particles_len += 1;

	}

	void add_particle( PARTICLE _p ){
		PARTICLE * temp = new PARTICLE[ particles_len + 1 ];
		std::copy( particles, particles + particles_len, temp );
		temp[ particles_len ] = _p;
		particles = temp;
		particles_len += 1;

	}

	void render(){
			for( int i = 0; i < particles_len; i++ ){
				particles[i].render();
			}
	}


};


SIMULATION sim = SIMULATION();




void init_glut( void ){
	glClearColor( 0, 0, 0, 1.0 );
	glViewport( 0.0, 0.0, window_height, window_height );
	glutInitDisplayMode(GLUT_RGBA);	
	glMatrixMode( GL_PROJECTION );
	glLoadIdentity();	
	
	glOrtho( 0.0, window_width, window_height, 0.0, 100, -100.0 );

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
	
	patricle_2.set_color( 0, 1, 0);
    
	sim.add_particle( 0.0, 0, -4, 0.1 );
	sim.add_particle( patricle_1 );
	sim.add_particle( patricle_2 );

 
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutMainLoop();
    return 0;
}


void render( int a ){
	// clear the drawing buffer.
    glClear(GL_COLOR_BUFFER_BIT);


	//patricle_1.render();
	//patricle_2.render();

    sim.render();

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