#include "Block.h"
#include  "Init_window.h"
#include <stdio.h>
#include <fstream>

using namespace std;
float	player_x;  
float 	player_y;
float 	player_z;
float   start_x, start_y, start_z;
float rotate_x = 0.3;
float rotate_z = 0.3;
int number_platform;
float speed = 0.3f;
float speed_jump = 0.9f;
bool player_flight = false;
float g = 0.01f;
float g2 = 0.01f;
float ground_level = 0.0f;
int count_block = 0;
int view = 0;
Block b[10];
int level_number = 1;
void Draw_cube()
{
glBegin(GL_QUADS);	
		glTexCoord2f(0.0f, 0.0f);   glVertex3f( 0.0f, 0.0f, 0.0f);	 //1 - передн€€ грань
		glTexCoord2f(1.0f, 0.0f);  	glVertex3f( 0.0f, 1.0f, 0.0f);	
		glTexCoord2f(1.0f, 1.0f);   glVertex3f( 1.0f, 1.0f, 0.0f);				
		glTexCoord2f(0.0f, 1.0f); 	glVertex3f( 1.0f, 0.0f, 0.0f);
		glTexCoord2f(0.0f, 0.0f);   glVertex3f( 0.0f, 0.0f, -1.0f);  //2 - лева€ бокова€ грань
		glTexCoord2f(1.0f, 0.0f);  	glVertex3f( 0.0f, 1.0f, -1.0f);	
		glTexCoord2f(1.0f, 1.0f);   glVertex3f( 0.0f, 1.0f, 0.0f);				
		glTexCoord2f(0.0f, 1.0f); 	glVertex3f( 0.0f, 0.0f, 0.0f);
		glTexCoord2f(0.0f, 0.0f);   glVertex3f( 1.0f, 0.0f, -1.0f);	 //3 - задн€€ бокова€ грань
		glTexCoord2f(1.0f, 0.0f);  	glVertex3f( 1.0f, 1.0f, -1.0f);	
		glTexCoord2f(1.0f, 1.0f);   glVertex3f( 0.0f, 1.0f, -1.0f);				
		glTexCoord2f(0.0f, 1.0f); 	glVertex3f( 0.0f, 0.0f, -1.0f);
		glTexCoord2f(0.0f, 0.0f);   glVertex3f( 1.0f, 0.0f, 0.0f);	 //4 - права€ бокова€ грань
		glTexCoord2f(1.0f, 0.0f);  	glVertex3f( 1.0f, 1.0f, 0.0f);	
		glTexCoord2f(1.0f, 1.0f);   glVertex3f( 1.0f, 1.0f, -1.0f);				
		glTexCoord2f(0.0f, 1.0f); 	glVertex3f( 1.0f, 0.0f, -1.0f);
		glTexCoord2f(0.0f, 0.0f);   glVertex3f( 0.0f, 1.0f,  0.0f);	 //5 - верхн€€ грань
		glTexCoord2f(1.0f, 0.0f);  	glVertex3f(	0.0f, 1.0f, -1.0f);	
		glTexCoord2f(1.0f, 1.0f);   glVertex3f( 1.0f, 1.0f, -1.0f);				
		glTexCoord2f(0.0f, 1.0f); 	glVertex3f( 1.0f, 1.0f, 0.0f);
		glTexCoord2f(0.0f, 0.0f);   glVertex3f( 0.0f, 0.0f, 0.0f);	 //6 - нижн€€ грань
		glTexCoord2f(1.0f, 0.0f);  	glVertex3f(	0.0f, 0.0f, -1.0f);	
		glTexCoord2f(1.0f, 1.0f);   glVertex3f( 1.0f, 0.0f, -1.0f);				
		glTexCoord2f(0.0f, 1.0f); 	glVertex3f( 1.0f, 0.0f, 0.0f);
	glEnd();	
}