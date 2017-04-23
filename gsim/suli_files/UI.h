#pragma	once
#include "GL/glut.h"
#include "../GCODE/GCODE.h"

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


// to poulize empty callbacks
void blank(){}

// point class....
//	stores the colors of what is displayed. Just a point in 3D space
class POINT2D{
public:
	float x;
	float y;
	
	float R;
	float G;
	float B;
	
	// constructors
	POINT2D(){
		x = 0;
		y = 0;
		R = 0;
		G = 0;
		B = 0;
	}

	POINT2D( float _x, float _y ){
		x = _x;
		y = _y;
		R = 0;
		G = 1;
		B = 0;
	}

	POINT2D( float _x, float _y, int red, int green, int blue ){
		x = _x;
		y = _y;
		R = (float)red/255;
		G = (float)green/255;
		B = (float)blue/255;
	}

	// methods
	void set_color( int red, int green, int blue ){
		R = (float)red/255;
		G = (float)green/255;
		B = (float)blue/255;	
	}

	void set_pos(float _x, float _y){
		x = _x;
		y = _y;
	}
};



// Line Class
//	Has 2 POINT2Ds 
//	represents a line drawn in 3D space. Could be used for a variety of tools.

class LINE{
public:

	POINT2D point_one;
	POINT2D point_two;
	int width;

	void set_width( int w ){
		width = w;
	}

	LINE(){
		width = 1;
		point_one = POINT2D( 0, 0 );
		point_two = POINT2D( 0, 0 );
	}


	LINE( POINT2D p1, POINT2D p2 ){
		point_two = p1;
		point_two = p2;
	}

	LINE( int _x, int _y, int _x2, int _y2 ){
		point_one = POINT2D( _x, _y );
		point_two = POINT2D( _x2, _y2 );
	}

	void set_color( int _r, int _g, int _b ){
		point_one.set_color( _r, _g, _b );
		point_two.set_color( _r, _g, _b );
	}

	void draw(){
		glLineWidth( width );
		glBegin( GL_LINES );
			glColor3f( point_one.R, point_one.G, point_one.B );
			glVertex3f( point_one.x, point_one.y, 0.0 );
			glColor3f( point_two.R, point_two.G, point_two.B );
			glVertex3f( point_two.x, point_two.y, 0.0 );
		glEnd();
	}

};


// Functionality Class...
//	This represents an ability that a higher level object could posses. Such as running a script on press or changing the state of the program
//	Will be used with buttons and sliders for example.... can be extended and you can add custom functionality

class FUNCTIONALITY{
public:
	std::string type;
	std::string name;
	std::string command;
	int ID;

	FUNCTIONALITY(){
		type = "none";
		name = " un-named";
		command = "echo 'pressed un-named button'";
	}

	FUNCTIONALITY( std::string t ){
		if( t == FUNCTIONALITY_TYPE_REG || t == FUNCTIONALITY_LINUX_COMMAND ){

		}

	}


};





// AN ABSTRACT BASE CLASS.... ALL THE GET_INPUTS EXTEND THIS
// Must have:
//	void render
// 	void draw
//	void mouse_move
//	void mouse_move_press
// 	void mouse_press
//	void add_functionality
class GET_INPUT{
public:
	int type;
	float x;
	float y;
	float width;
	float height;

	int R;
	int G;
	int B;

	LINE * lines;
	int lines_len;

	int line_width_create;
	int line_R;
	int line_G;
	int line_B;

	float last_x;
	float last_y;

	int step_rate;
	int curren_step;

	virtual void render(){

	}

	virtual void  draw(){

	}

	virtual void mouse_move( int _x, int _y ){

	}

	virtual void mouse_move_press( int _x, int _y ){

	}

	virtual void mouse_press( int _button, int _state, int _x, int _y ){

	}

	virtual void set_type( int t ){

	}



};




// Button Class....
//	This is one of the inputs, the higher level objects can posses a button object or multiple button objects. They can all be displayed when requested. 
//	This buttons class can be presses and would in turn posses a Functionality or multiple Functionalities depending on what is needed.

class BUTTON{
public:
	int type;
	std::string title;
	bool has_hover;
	bool has_left_press;
	bool has_right_press;
	bool has_middle_press;


	BUTTON(){
		has_hover = false;
		has_middle_press = false;
		has_right_press = false;
		has_left_press = false;
		type = BUTTON_REG;
	}


	BUTTON( std::string t ){
		
	}

	void render(){
		
	}

	void mouse_move( int _x, int _y ){

	}

	void mouse_move_press( int _x, int _y ){

	}

	void mouse_press( int button, int state, int _x, int _y ){
	
	}


	void set_type( int t ){

	}

};



// DRAW_AREA class...
//	This is another type of input. It will have an array of lines that the user draws. 
//	will accept input depending on mouse location.
class DRAW_AREA{
public:
	float x;
	float y;
	float width;
	float height;

	int R;
	int G;
	int B;

	LINE * lines;
	int lines_len;

	int line_width_create;
	int line_R;
	int line_G;
	int line_B;

	float last_x;
	float last_y;

	int step_rate;
	int curren_step;

	int current_press_state;

	void start_vals(){
		R = 255;
		G = 0;
		B = 0;
		curren_step = 0;
		step_rate = 3;
		lines_len = 0;
		line_width_create = 2;
		line_R = 0;
		line_G = 0;
		line_B = 0;
		current_press_state = 0;
	}

	DRAW_AREA(){
		x = 0;
		y = 0;
		width = 100;
		height = 100;
		start_vals();
	}

	DRAW_AREA( float _x, float _y, float _width, float _height ){
		x = _x;
		y = _y;
		width = _width;
		height = _height;
		start_vals();
	}

	void set_color( int _r, int _g, int _b ){
		R = _r;
		G = _g;
		B = _b;
	}

	void set_size( float _w, float _h ){
		width = _w;
		height = _h;
	}

	void set_pos( float _x, float _y ){
		x = _x;
		y = _y;
	}

	void set_create_line_color( int _r, int _g, int _b ){
		line_R = _r;
		line_G = _g;
		line_B = _b;
	}

	void add_line( float _x, float _y, float _x2, float _y2 ){

		// add line to array
		LINE * temp = new LINE[ lines_len + 1 ];
		std::copy( lines, lines + lines_len, temp );
		lines = temp;
		lines_len += 1;


		lines[ lines_len - 1 ] = LINE( _x, _y, _x2, _y2 );
		lines[ lines_len - 1 ].set_width( line_width_create );
		lines[ lines_len - 1 ].set_color( line_R, line_G, line_B );
		//std::cout << "added line to draw area \n";

	}


	void set_create_line_width( int _lw ){
		line_width_create = _lw;
	}

	void render(){

		if( lines_len == 0 || lines_len != 0 ){
			glColor3f( (float)R/255, (float)G/255, (float)B/255 );
			glBegin( GL_QUADS );
				glVertex3f( x, y, 0.0 );
				glVertex3f( x + width, y, 0.0 );
				glVertex3f( x + width, y + height, 0.0 );
				glVertex3f( x, y + height, 0.0 );
			glEnd();
		}

		for( int i = 0; i < lines_len; i++ ){
			lines[ i ].draw();
		}

	}

	void mouse_move( int _x, int _y ){

	}

	void mouse_move_press( int _x, int _y ){
		if( current_press_state == 0 ){
			if( curren_step == step_rate ){
				add_line( last_x, last_y, _x, _y );
				last_x = _x;
				last_y = _y;
				curren_step = 0;
			}else{
				curren_step += 1;
			}
		}
	}

	void mouse_press( int button, int state, int _x, int _y ){
		last_x = _x;
		last_y = _y;
		current_press_state = state;
	}

};



struct IMAGE_INFO{
	int start;
	int end;
	char * name;
	int value;


	IMAGE_INFO( ){
		start = 0;
		end = 0;
		name = NULL;
		value = 0;
	}	

	IMAGE_INFO( int s, int e, char * n, int val ){
		start = s;
		end = e;
		name = ( char * )n;
		value = val;
	}
};



 

class IMAGE{
public:
	int x;
	int y;
	int width;
	int height; 
	int pixel_offset;
	int image_width;
	int image_height;
	int compression;
	int image_size;
	int bits_per_pixel;
	char * image_path;
	size_t size;

	unsigned char * texDat;
	GLuint tex;
	int type;

	unsigned char * texDat_hover;
	GLuint tex_hover;
	int type_hover;	

	IMAGE_INFO * other_data;
	int other_data_len;

	IMAGE_INFO * other_data_hover;
	int other_data_hover_len;

	void (*click_callback)(void);


	void setup_other_data(){
		
		IMAGE_INFO other_data_temp[] = { 	IMAGE_INFO( 0,   2, 		(char*) "signature",   				-9999 ),	//0
											IMAGE_INFO( 2,   6, 		(char*) "file size",   				-9999 ),	//1
											IMAGE_INFO( 6,   10, 		(char*) "reserved",   				-9999 ),	//2
											IMAGE_INFO( 10,  14, 		(char*) "offset to array", 			-9999 ),	//3
											IMAGE_INFO( 14,  18, 		(char*) "dip_header",  				-9999 ),	//4
											IMAGE_INFO( 18,  22, 		(char*) "width",	    			-9999 ),	//5
											IMAGE_INFO( 22,  26, 		(char*) "height", 	   				-9999 ),
											IMAGE_INFO( 26,  28, 		(char*) "planes", 	   				-9999 ),
											IMAGE_INFO( 28,  30, 		(char*) "bits per pixel", 	   		-9999 ),
											IMAGE_INFO( 30,  34, 		(char*) "compression",	 	   		-9999 ),	
											IMAGE_INFO( 34,  38, 		(char*) "image size",	 	   		-9999 ),	//10
											IMAGE_INFO( 38,  42,	 	(char*) "X pixels per meter",  		-9999 ),
											IMAGE_INFO( 42,  46, 		(char*) "Y pixels per meter", 		-9999 ),
											IMAGE_INFO( 46,  50, 		(char*) "Colors in color table", 	-9999 ),
											IMAGE_INFO( 50,  54, 		(char*) "Important Color Count", 	-9999 ),
											IMAGE_INFO( 54,  58, 		(char*) "red chanel bitmask", 		-9999 ),	//15
											IMAGE_INFO( 58,  62, 		(char*) "blue chanel bitmask", 		-9999 ),
											IMAGE_INFO( 62,  66, 		(char*) "green chanel bitmask", 	-9999 ),
											IMAGE_INFO( 66,  70, 		(char*) "alpha chanel bitmask",		-9999 ),
											IMAGE_INFO( 70,  74, 		(char*) "color space type", 		-9999 ),
											IMAGE_INFO( 74,  78, 		(char*) "color space enpoints",		-9999 ),	//20
											IMAGE_INFO( 78,  82, 		(char*) "gamma for red chanel", 	-9999 ),
											IMAGE_INFO( 82,  86, 		(char*) "gamma for green chanel", 	-9999 ),
											IMAGE_INFO( 86,  90, 		(char*) "gamma for blue chanel", 	-9999 ),
											IMAGE_INFO( 90,  94, 		(char*) "intent",				 	-9999 ),
											IMAGE_INFO( 94,  98, 		(char*) "ICC profile data",	 		-9999 ),	//25
											IMAGE_INFO( 98,  102, 		(char*) "ICC profile size", 		-9999 ),
											IMAGE_INFO( 102, 104, 		(char*) "reserved", 				-9999 )
									};

		other_data = other_data_temp;							
		type = IMAGE_TYPE_RGB;
		other_data_len = 27;
		other_data = new IMAGE_INFO[ other_data_len ];

		std::copy( other_data_temp, other_data_temp + other_data_len, other_data );

		x = 0;
		y = 0;
		width = 100;
		height = 100;
		click_callback = blank;
	}

	// no path... cannot load image until there is path.
	IMAGE(){
		image_path = NULL;
		setup_other_data();
	}

	// create image with a path
	IMAGE( char * p ){
		image_path = p;
		setup_other_data(); 	
	}

	// set the path.
	void set_path( char * p ){
		image_path = p;
	}

	void set_type( int t ){
		type = t;
	}

	void set_pos( int _x, int _y ){
		x = _x;
		y = _y;
	}

	void set_size( int _w, int _h ){
		width = _w;
		height = _h;
	}

	// will load all the data into this image object so that they can later be used.
	//	first read the file and store all the relevant information into the other data array
	//	then it will attampt to load 
	void load(){
		// check if the path exists
		if( image_path != NULL ){
			std::ifstream f;

			// open file
			f.open( image_path, std::ios::in | std::ios::binary  );
			char * file = 0;

			// find the end and size of the file
			f.seekg( 0, std::ios::end );
			size = f.tellg();
			std::cout << "size: " << size << "\n";
			f.seekg( 0, std::ios::beg );

			// read the file and store it in a char array
			file = new char[ size + 1 ];
			f.read( file, size );
			file[ size ] = '\0';
		

			// load the contents into "other_data"
			//int * temp = new int[1];
			unsigned char * temp = new unsigned char[4];
			for( int i = 0; i < size; i++ ){
				for( int c = 0; c < other_data_len; c++ ){

					if( i == other_data[ c ].start ){
						std::copy( file + other_data[c].start, file + other_data[c].end, temp );
						other_data[c].value = *(temp+3) << 24 | *(temp+2) << 16 | *(temp+1) << 8 | *temp;
						
						std::cout << std::dec << other_data[c].name << " : " << other_data[c].value << "\n";
						i = other_data[ c ].end-1;
					}
				}
			}


			
			pixel_offset 	= (unsigned int) (other_data[ 3 ].value);
			std::cout << "pixel_offset: " << pixel_offset << "\n";

			image_width 	= (unsigned int) (other_data[ 5 ].value);
			std::cout << "width: " << image_width << "\n";
				
			image_height 	= (unsigned int) (other_data[ 6 ].value);
			std::cout << "height: " << image_height << "\n";

			bits_per_pixel 	= (unsigned int) (other_data[ 8 ].value);
			std::cout << "bpp: " << bits_per_pixel << "\n";

			unsigned char * image_data;
			texDat = new unsigned char[ image_width * image_height * 3 ];



			if( bits_per_pixel == 24 ){ 
				texDat = new unsigned char[ image_width * image_height * 3 ];
				image_data = new unsigned char[ image_width * image_height * 3 ];

				for( int i = 0; i < (image_width * image_height * 3); i++ ){

					image_data[ i ] 	= 	(unsigned char)file[ pixel_offset + i + 2 ] ;		// R
					image_data[ i+1 ] 	= 	(unsigned char)file[ pixel_offset + i + 1] ;		// G
					image_data[ i+2 ] 	= 	(unsigned char)file[ pixel_offset + i ] ;			// B
									
					i += 2;
				}

				glEnable(GL_BLEND);
				glBlendFunc( GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA ); 
				glGenTextures(1, &tex);
				glBindTexture(GL_TEXTURE_2D, tex);
			    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
			    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
			   	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, image_width, image_height, 0, GL_RGB, GL_UNSIGNED_BYTE, texDat); 



			}else if( bits_per_pixel == 32 ){
				texDat = new unsigned char[ image_width * image_height * 4 ];
				image_data = new unsigned char[ image_width * image_height * 4 ];

				for( int i = 0; i < (image_width * image_height * 4); i++ ){					
					
					image_data[ i ] 	= 	(unsigned char)file[ pixel_offset + i + 3 ] ;		// R
					image_data[ i+1 ] 	= 	(unsigned char)file[ pixel_offset + i + 2 ] ;		// G
					image_data[ i+2 ] 	= 	(unsigned char)file[ pixel_offset + i + 1 ] ;		// B
					image_data[ i+3 ] 	= 	(unsigned char)file[ pixel_offset + i  ] ;			// A
									
					i += 3;
				}

				glEnable(GL_BLEND);
				glBlendFunc( GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA ); 
				glGenTextures(1, &tex);
				glBindTexture(GL_TEXTURE_2D, tex);
			    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
			    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
			   	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, image_width, image_height, 0, GL_RGB, GL_UNSIGNED_BYTE, texDat);

			}else{



			}

			texDat = image_data;

		    glBindTexture(GL_TEXTURE_2D, 0);
		    glEnable(GL_TEXTURE_2D);
	  




		}else{
			std::cout << "there is no file path specified for IMAGE object, could not load \n";
		}




	}

	void draw(){

		if( bits_per_pixel == 24 ){

			glBindTexture(GL_TEXTURE_2D, tex);
		    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
		    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
		    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, image_width, image_height, 0, GL_RGB, GL_UNSIGNED_BYTE, texDat); 
		    glBindTexture(GL_TEXTURE_2D, 0);

		    glBindTexture(GL_TEXTURE_2D, tex);

		}else if( bits_per_pixel == 32 ){
			glBindTexture(GL_TEXTURE_2D, tex);
		    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
		    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
		    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, image_width, image_height, 0, GL_RGBA, GL_UNSIGNED_BYTE, texDat); 
		    glBindTexture(GL_TEXTURE_2D, 0);

		    glBindTexture(GL_TEXTURE_2D, tex);

		}


		glColor3f(1,1,1);
	    glBegin(GL_QUADS);
	    	glTexCoord2f(0, 0); glVertex2f(x, y + height);
	    	glTexCoord2f(0, 1); glVertex2f(x, y );
		    glTexCoord2f(1, 1); glVertex2f(x + width, y);
		    glTexCoord2f(1, 0); glVertex2f(x + width, y + height);
	    glEnd();

	}


	void render(){
		if( bits_per_pixel == 24 ){

			glBindTexture(GL_TEXTURE_2D, tex);
		    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
		    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
		    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, image_width, image_height, 0, GL_RGB, GL_UNSIGNED_BYTE, texDat); 

		}else if( bits_per_pixel == 32 ){
			glBindTexture(GL_TEXTURE_2D, tex);
		    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
		    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
		    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, image_width, image_height, 0, GL_RGBA, GL_UNSIGNED_BYTE, texDat); 
		}


		glColor3f(1,1,1);
	    glBegin(GL_QUADS);
	    	glTexCoord2f(0, 0); glVertex2f(x, y + height);
	    	glTexCoord2f(0, 1); glVertex2f(x, y );
		    glTexCoord2f(1, 1); glVertex2f(x + width, y);
		    glTexCoord2f(1, 0); glVertex2f(x + width, y + height);
	    glEnd();
	
	    glBindTexture(GL_TEXTURE_2D, 0);
		
	}


	void mouse_press( int _state, int _button, int _x, int _y ){
		click_callback();
	}

	void mouse_move( int _x, int _y ){
		//std::cout << "I see a mouse \n";
	}

	void add_click_callback( void(*_callback)(void)){
		click_callback = _callback;
	}


};



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
//	    glScalef(1.0,1.0,1.0);
	    glutSolidSphere(radius,20,20);

	    glTranslatef( -x, -y, -z);
	
		

	}

};



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


// SCREEN class ...
//	The main display class of this program. A screen will contain a compilations of buttons, lines, sliders.... which can each have functionalities to do differnet things.
//	Screens will have a Background color that is the backfround color displayed.
//	A screen represents 1 state of the program.... for example, the login window is a Screen, then when you login, the displayed screen changes to a different one, with different buttons and sliders etc...

class SCREEN{
public:
	BUTTON * buttons;
	int buttons_len;

	DRAW_AREA * draw_areas;
	int draw_areas_len;

	IMAGE * images;
	int images_len;

	SIMULATION simulation;

	std::string title;

	int R;
	int G;
	int B;
	int ID;

	int mouse_x;
	int mouse_y;


	void start_vals(){
		R = 0;
		G = 0;
		B = 0;
		mouse_x = 0;
		mouse_y = 0;
		
		draw_areas_len = 0;
		buttons_len = 0;
		images_len = 0;
		simulation = SIMULATION();
	}

	SCREEN(){
		title = "un-named screen";
		start_vals();
	}

	SCREEN( std::string t ){
		title = t;
		start_vals();
	}


	// add functions... one for every type of variable.

	void add( DRAW_AREA d ){
		DRAW_AREA * temp = new DRAW_AREA[ draw_areas_len + 1 ];
		std::copy( draw_areas, draw_areas + draw_areas_len, temp ); 
		draw_areas = temp;
		draw_areas_len += 1;

		draw_areas[ draw_areas_len - 1 ] = d;
	}

	void add( BUTTON b ){
		BUTTON * temp = new BUTTON[ buttons_len + 1 ];
		std::copy( buttons, buttons + buttons_len, temp );
		buttons = temp;
		buttons_len += 1;

		buttons[ buttons_len - 1] = b;
	}

	void add( IMAGE p ){
		IMAGE * temp = new IMAGE[ images_len + 1 ];
		std::copy( images, images + images_len, temp );
		images = temp;
		images_len += 1;

		images[ images_len - 1 ] = p;
	}

	void import_bmp( std::string p ){
		
	}

	void add( PARTICLE p1 ){
		simulation.add_particle(p1);
	}



	// render function
	//	called every frame
	void render(){
		// draw areas
		for( int i = 0; i < draw_areas_len; i++ ){
			draw_areas[ i ].render();
		}

		// buttons
		for( int i = 0; i < buttons_len; i++ ){
			buttons[ i ].render();
		}

		// images
		for( int i = 0; i < images_len; i++ ){
			images[ i ].render();
		}

		simulation.render();
	}

	// update function
	void update(){

	}

	void add_buttons( BUTTON * b ){
		buttons = b;
	}

	void set_color( int red, int green, int blue ){
		R = red;
		G = green;
		B = blue;
	}

	void mouse_press( int _state, int _button, int _x, int _y ){
		for( int i = 0; i < draw_areas_len; i++ ){
			if( check_inside( draw_areas[i].x, draw_areas[i].y, draw_areas[i].width, draw_areas[i].height, _x, _y ) )
				draw_areas[i].mouse_press( _state, _button, _x, _y );	
		}

		for( int i = 0; i < images_len; i++ ){
			if( check_inside( images[i].x, images[i].y, images[i].width, images[i].height, _x, _y ) ){
				images[i].mouse_press( _state, _button, _x, _y );
			}
		}
	}

	void mouse_move_press(  int _x, int _y ){
		for( int i = 0; i < draw_areas_len; i++ ){
			if( check_inside( draw_areas[i].x, draw_areas[i].y, draw_areas[i].width, draw_areas[i].height, _x, _y ) )
				draw_areas[i].mouse_move_press( _x, _y );	
		}	
		mouse_x = _x;
		mouse_y = _y;

	}

	void mouse_move( int _x, int _y ){
		for( int i = 0; i < draw_areas_len; i++ ){
			if( check_inside( draw_areas[i].x, draw_areas[i].y, draw_areas[i].width, draw_areas[i].height, _x, _y ) )
				draw_areas[i].mouse_move( _x, _y );	
		}

		for( int i = 0; i < images_len; i++ ){
			if( check_inside( images[i].x, images[i].y, images[i].width, images[i].height, _x, _y ) ){
				images[i].mouse_move( _x, _y );
			}
		}

		mouse_x = _x;
		mouse_y = _y;
	}

};



// Window class...
//	A final abstraction that represents a collections of screens. This is the object that all screens are added to,
//	Will keep track of which screen to use. 
// 	Will display the screens as needed and send input commands to said screen.
// 	This is the class you start the program with after initializing opengl.

class WINDOW{
public:
	std::string title;
	SCREEN * screens;
	int screens_len;
	int current_screen;

	bool is_fullscreen;

	WINDOW(){
		title = "un-named window";
		screens_len = 0;
		current_screen = 0;
		is_fullscreen = false;
	}

	WINDOW( std::string t ){
		title = t;
		screens_len = 0;
		current_screen = 0;
		is_fullscreen = false;
	}

	WINDOW( std::string t, bool f ){
		title = t;
		screens_len = 0;
		current_screen = 0;
		is_fullscreen = f;
	}

	void set_fullscreen( bool t ){
		is_fullscreen = t;
		if( t == true )
			glutFullScreen();
	}

	void add_screens(  ){
	}

	void set_current_screen( int _i ){
		current_screen = _i;
	}

	void set_current_screen( std::string _n ){
		for( int i = 0; i < screens_len; i++ ){
			if( screens[ i ].title == _n ){
				current_screen = i;
				break;
			}
		}
	}

	void add_screen( SCREEN _s ){
		SCREEN * temp = new SCREEN[ screens_len + 1 ];
		std::copy( screens, screens + screens_len, temp );
		screens = temp;
		screens_len += 1;

		screens[ screens_len - 1 ] = _s;
		current_screen = screens_len - 1;

	}

	void mouse_press( int _button, int _state, int _x, int _y ){
		std::cout << "WINDOW --- button: " << _button << " state: " << _state << " x: " << _x << " y: " << _y  << " TOTAL SCREENS: " << screens_len << "\n";		
		screens[ current_screen ].mouse_press( _button, _state, _x, _y );
	}

	void mouse_move( int _x, int _y ){
		screens[ current_screen ].mouse_move( _x, _y );
	}

	void mouse_move_press( int _x, int _y ){
		screens[ current_screen ].mouse_move_press( _x, _y );
	}

	void render(){
		screens[ current_screen ].render();	
		glutSwapBuffers();
	}


};









// GLOBALS
WINDOW window;

int window_width = 2000;
int window_height = 1100;
int frame_delay = 10;
float background_R = 0.0;
float background_G = 0.0;
float background_B = 0.0;
int step_rate = 1;

float last_x = 0;
float last_y = 0;
int current_step = 0;

char * path_to_gcode = (char *) "";


PARTICLE p1 = PARTICLE( 100, 100, 100, 10 );

// FUNCTIONS
void init_glut( void ){
	glClearColor( background_R, background_G, background_B, 1.0 );
	glViewport( 0.0, 0.0, window_width, window_height );
	glutInitDisplayMode(GLUT_RGBA);	
	glMatrixMode( GL_PROJECTION );
	glLoadIdentity();
	
	glOrtho( 0.0, window_width, window_height, 0.0, 20.0, -20.0 );

	glMatrixMode( GL_MODELVIEW );
	glLoadIdentity();
}




// TEST FUNCTION
/* 
void add_line( float _x, float _y, float _x2, float _y2 ){
		LINE * temp = new LINE[ lines_len + 1 ];
		std::copy( lines, lines + lines_len, temp );
		lines = temp;
		lines_len += 1;
		lines[ lines_len - 1 ] = LINE( _x, _y, _x2, _y2 );
}
*/


// funciton to help check for collisions.
bool check_inside( int x, int y, int w, int h, int x2, int y2 ){
	if( x < x2 && x + w > x2 && y < y2 && y + h > y2 ){
		return true;
	}return false;
}


// callbacks
void mouse_press_callback( int button, int state, int x, int y){
	window.mouse_press( button, state, x, y );
}

void mouse_move_callback( int _x, int _y ){
	window.mouse_move( _x, _y );	
}

void resize_callback( int x, int y ){
	window_width = x;
	window_height = y;
	init_glut();
}


void active_mouse_move_callback( int x, int y ){
	window.mouse_move_press( x, y );
}


void display_callback( void ){
	glClearColor( background_R, background_G, background_G, 1.0 );
	glClear( GL_COLOR_BUFFER_BIT );

	if( window.is_fullscreen == true ){
		glutFullScreen();
	}

	glutSwapBuffers();	
	glutTimerFunc( frame_delay, render, 0  );
}


void render( int a ){
	glClear(GL_COLOR_BUFFER_BIT);
	window.render();
	glutTimerFunc( frame_delay, render, 0  );

}



// **************************************************************************************************************************************************** //

void press_gcode_select(){
	std::cout << "time to select gcode\n";
}

void start_simulation(){
	window.set_current_screen(1);
	//std::cout << "hello\n";
}

void return_home(){
	window.set_current_screen( 0 );
}


// **************************************************************************************************************************************************** //
