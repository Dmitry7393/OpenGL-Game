#ifndef DRW
#define DRW
#include "Draw_cube.h"
GLuint texture[11];
const float h = 3.0f;
char st[32];
float cube_a, cube_b, cube_c;
GLvoid ReSizeGLScene(GLsizei width, GLsizei height);
void create_level();
void renderSphere( float cx, float cy, float cz, float r, int p );
//void loadTexture(void);
AUX_RGBImageRec *LoadBMP(char *Filename);
int LoadGLTextures(int i, char *name_texture);
GLvoid BuildFont(GLvoid);
GLvoid glPrint(const char *fmt, float ) ;
void Draw_text(char *text, float x, float y, float z);
GLvoid glPrint(const char *fmt, float t2) ;
// Here's Where We Do All The Drawing
int DrawGLScene(GLvoid)	
{
    glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
    glMatrixMode( GL_MODELVIEW );
	glLoadIdentity();
	//debug
	//TextOut(hDC,20,80,itoa(  player_x, st, 10),  3);
	//TextOut(hDC,20,100,itoa( player_y, st, 10), 3);
	//TextOut(hDC,20,120 ,itoa(player_z, st, 10),3);
	//TextOut(hDC,20,170 ,itoa(ground_level, st, 10),3);
	//TextOut(hDC,20,210 ,itoa(number_platform, st, 10),3);
	//TextOut(hDC,20,250 ,itoa(count_block, st, 10),3);
	if(view == 0)
	{
		gluLookAt(player_x+2.0f, player_y+9.0f, player_z+20.0f,
				  player_x, player_y, player_z, 
			      0, 1, 0);	
	}
	else
	{
			gluLookAt(-30.0f, 50.0f, 50.0f,
				      player_x+20, player_y+15, player_z, 
					  0, 1, 0);
	}
    if( g_bRenderInWireFrame == true )
        glPolygonMode( GL_FRONT_AND_BACK, GL_LINE );
    else
        glPolygonMode( GL_FRONT_AND_BACK, GL_FILL );

    if( g_bUseLighting == true )
        glEnable( GL_LIGHTING );
    else
        glDisable( GL_LIGHTING );

		glBindTexture(GL_TEXTURE_2D, texture[0]);	        
   glPushMatrix();   
			glTranslatef(player_x, player_y, player_z);
			glRotatef( rotate_z, 0, 0, 1);
			glRotatef( rotate_x, 1, 0, 0 ); 
			renderSphere( 0.0f, 0.0f, 0.0f, 1.5f, g_nPrecision );		
    glPopMatrix();
		///Draw fon 
	//left
		glBindTexture(GL_TEXTURE_2D, texture[5]);
	glBegin(GL_QUADS);	
			glTexCoord2f(0.0f, 0.0f);   glVertex3f(-100.0f, -100.0f,  80.0f);  ///
			glTexCoord2f(1.0f, 0.0f);  	glVertex3f(-100.0f,  100.0f,  80.0f);
			glTexCoord2f(1.0f, 1.0f);   glVertex3f(-100.0f,  100.0f,  -80.0f);			
			glTexCoord2f(0.0f, 1.0f);   glVertex3f(-100.0f,  -100.0f,  -80.0f);	
	glEnd();
	//front
	glBindTexture(GL_TEXTURE_2D, texture[6]);
	glBegin(GL_QUADS);	
			glTexCoord2f(0.0f, 0.0f);   glVertex3f(-100.0f, -100.0f,  -80.0f);
			glTexCoord2f(1.0f, 0.0f);  	 glVertex3f(100.0f,  -100.0f,-80.0f);
			glTexCoord2f(1.0f, 1.0f);   glVertex3f(100.0f,  100.0f,	 -80.0f);			
			glTexCoord2f(0.0f, 1.0f);   glVertex3f(-100.0f,  100.0f,  -80.0f);
	glEnd();
	//right
		glBindTexture(GL_TEXTURE_2D, texture[7]);
	glBegin(GL_QUADS);	
			glTexCoord2f(0.0f, 0.0f);   glVertex3f(100.0f, -100.0f,  -80.0f);
			glTexCoord2f(0.0f, 1.0f);  	 glVertex3f(100.0f,  100.0f,  -80.0f);
			glTexCoord2f(1.0f, 1.0f);   glVertex3f(100.0f,  100.0f,	 240.0f);			
			glTexCoord2f(1.0f, 0.0f);   glVertex3f(100.0f,  -100.0f,  240.0f);
	glEnd();
		glBindTexture(GL_TEXTURE_2D, texture[8]);
		//down
	glBegin(GL_QUADS);	
			glTexCoord2f(0.0f, 0.0f);   glVertex3f(-100.0f, -100.0f,  120.0f);
			glTexCoord2f(0.0f, 1.0f);  	glVertex3f(-100.0f,  -100.0f,  -80.0f);
			glTexCoord2f(1.0f, 1.0f);   glVertex3f(100.0f,   -100.0f,	 -80.0f);			
			glTexCoord2f(1.0f, 0.0f);   glVertex3f(100.0f,  -100.0f,  240.0f);
	glEnd();
	//up
	glBindTexture(GL_TEXTURE_2D, texture[9]);
	glBegin(GL_QUADS);	
			glTexCoord2f(0.0f, 0.0f);   glVertex3f(-100.0f, 100.0f,  -80.0f);
			glTexCoord2f(1.0f, 0.0f);  	glVertex3f(-100.0f, 100.0f,   80.0f);
			glTexCoord2f(1.0f, 1.0f);   glVertex3f(100.0f,  100.0f,	  80.0f);			
			glTexCoord2f(0.0f, 1.0f);   glVertex3f(100.0f,  100.0f,  -80.0f);
	glEnd();
	//game map
		for(int i = 0; i < count_block-1; i++)
		{	
			if(b[i].simple_block == true || b[i].move_by_player == true)
			{
			glPushMatrix();  
				glBindTexture(GL_TEXTURE_2D, texture[1]);
				glTranslatef(b[i].get_blockx1(), b[i].get_blocky1(), b[i].get_blockz1()); 
				glScalef(b[i].get_scale_x(), b[i].get_scale_y(), b[i].get_scale_z());
				b[i].calculate(); 
				Draw_cube();
			glPopMatrix();
			}
		}   	
	for(int i = 0; i < count_block-1; i++)
		{	
			if(b[i].trampoline == true)
			{
				glPushMatrix();  
					glBindTexture(GL_TEXTURE_2D, texture[4]);
					glTranslatef(b[i].get_blockx1(), b[i].get_blocky1(), b[i].get_blockz1()); 
					glScalef(b[i].get_scale_x(), b[i].get_scale_y(), b[i].get_scale_z());
					b[i].calculate(); 
					Draw_cube();
				glPopMatrix();
			}
		} 
	Draw_text("Level: " , -1.5f,1.1f,-3.0f);
	Draw_text(itoa(level_number, st, 10), -1.1f,1.1f,-3.0f);
	//Draw_text(itoa(player_x, st, 10), -1.5f,1.0f,-3.0f);
	//Draw_text(itoa(player_y, st, 10), -1.2f,1.0f,-3.0f);
	//Draw_text(itoa(player_z, st, 10), -0.9f,1.0f,-3.0f);
	return TRUE;
}
void Draw_text(char *text, float x, float y, float z)
{
	glPushMatrix();
		glLoadIdentity();	
		glTranslatef( x,  y,  z);
	    glColor3f(1.0f*float(cos(cnt1)),1.0f*float(sin(cnt2)),1.0f-0.5f*float(cos(cnt1+cnt2)));
		//glColor3f(0.0f, 1.0f, 1.0f);
	    glRasterPos2f(-0.45f+0.05f*float(cos(cnt1)), 0.35f*float(sin(cnt2)));
	    glPrint(text, cnt1);  // Print GL Text To The Screen
	glPopMatrix();
}
int InitGL(GLvoid)										
{
	glShadeModel(GL_SMOOTH);							
	glClearColor(0.0f, 0.0f, 0.0f, 0.5f);				
	glClearDepth(1.0f);									
	glEnable(GL_DEPTH_TEST);							
	glDepthFunc(GL_LEQUAL);						
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);	
   GLuint PixelFormat;
	PIXELFORMATDESCRIPTOR pfd;
	memset(&pfd, 0, sizeof(PIXELFORMATDESCRIPTOR));

    pfd.nSize      = sizeof(PIXELFORMATDESCRIPTOR);
    pfd.nVersion   = 1;
    pfd.dwFlags    = PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER;
    pfd.iPixelType = PFD_TYPE_RGBA;
    pfd.cColorBits = 16;
    pfd.cDepthBits = 16;
	
	hDC = GetDC( hWnd );
	PixelFormat = ChoosePixelFormat( hDC, &pfd );
	SetPixelFormat( hDC, PixelFormat, &pfd );
	hRC = wglCreateContext( hDC );
	wglMakeCurrent( hDC, hRC );

	glClearColor( 0.0f, 0.0f, 0.0f, 1.0f );
	glEnable( GL_TEXTURE_2D );
	glEnable( GL_DEPTH_TEST );

	glMatrixMode( GL_PROJECTION );
	glLoadIdentity();
	gluPerspective( 45.0f, 940.0f / 580.0f, 0.1f, 100.0f );

    // Setup lighting
    glEnable( GL_LIGHTING );
    glEnable( GL_LIGHT0 );

    float fAmbientColor[] = { 1.0f, 1.0f, 1.0f, 1.0f};
    glLightfv( GL_LIGHT0, GL_AMBIENT, fAmbientColor );

    float fDiffuseColor[] = { 1.0f, 1.0f, 1.0f, 1.0f };
    glLightfv( GL_LIGHT0, GL_DIFFUSE, fDiffuseColor );

    float fSpecularColor[] = { 0.0f, 0.0f, 0.0f, 1.0f };
    glLightfv( GL_LIGHT0, GL_SPECULAR, fSpecularColor );

    float fPosition[] = { 1.0f, 1.0f, 1.0f, 0.0f };
    glLightfv( GL_LIGHT0, GL_POSITION, fPosition );

    GLfloat ambient_lightModel[] = { 1.0f, 1.0f, 1.0f, 1.0f };
    glLightModelfv( GL_LIGHT_MODEL_AMBIENT, ambient_lightModel );
   ///////////////////////////////////////////////////////////////////////////////
	if(!LoadGLTextures(0, "Data/player_wood.bmp"))
		return FALSE;
	if(!LoadGLTextures(1, "Data/stone.bmp"))
		return FALSE;
	//if(!LoadGLTextures(2, "back2.bmp"))
	//	return FALSE;
	//if(!LoadGLTextures(3, "fon2.bmp"))
	//	return FALSE;
	if(!LoadGLTextures(4, "Data/trampoline.bmp"))
		return FALSE;
	if(!LoadGLTextures(5, "Data/skybox2/left.bmp"))  //skybox1/left.bmp
		return FALSE;
	if(!LoadGLTextures(6, "Data/skybox2/front.bmp"))  //Data/skybox1/front.bmp
		return FALSE;
	if(!LoadGLTextures(7, "Data/skybox2/right.bmp"))  //Data/skybox1/right.bmp
		return FALSE;
	if(!LoadGLTextures(8, "Data/skybox2/down.bmp"))  //Data/skybox1/down.bmp
		return FALSE;
	if(!LoadGLTextures(9, "Data/skybox2/up.bmp"))   //Data/skybox1/up.bmp
		return FALSE;
	create_level();
	 BuildFont();
	return TRUE;	
}
void create_level()
{
	ifstream F;
	char str[24];
	count_block = 0;
	char temp_str[6] = ""; 
	strcpy(str, "");
	strcat(str, "Data/level/level");
	strcat(str, itoa(level_number, temp_str, 10));
	strcat(str, ".txt");
	F.open(str, ios::in);
	float start, finish, sp;
	float cx, cy, cz, scale_x, scale_y, scale_z;
	char ch;  char type;
	bool read_koord_player = false;
	if(F)
	{
		while (!F.eof())
		{
			if(read_koord_player == false)
			{
				F >> start_x; F >> start_y; F >> start_z;
				read_koord_player = true;
			}
			F >> type;
			if(type == 'A')  //простой блок
			{
				F >> cx; F >> cy; F >> cz;
				F >> scale_x; F >> scale_y; F >> scale_z;
				F >> ch;
				b[count_block].create(cx, cy, cz, scale_x, scale_y, scale_z, ch);
				count_block++;
			}
			if(type == 'B')  //блок движется по оси Х
			{
				F >> cx; F >> cy; F >> cz;
				F >> scale_x; F >> scale_y; F >> scale_z;
				F >> ch;
				F >> start; F >> finish; F >> sp;
				b[count_block].create(cx, cy, cz, scale_x, scale_y, scale_z, ch);
				b[count_block].set_move_x(start, finish, sp);
				count_block++;
			}
			if(type == 'C')  //блок движется по оси Y
			{
				F >> cx; F >> cy; F >> cz;
				F >> scale_x; F >> scale_y; F >> scale_z;
				F >> ch;
				F >> start; F >> finish; F >> sp;
				b[count_block].create(cx, cy, cz, scale_x, scale_y, scale_z, ch);
				b[count_block].set_move_y(start, finish, sp);
				count_block++;
			}
			if(type == 'D')   //блок движется по оси Z
			{
				F >> cx; F >> cy; F >> cz;
				F >> scale_x; F >> scale_y; F >> scale_z;
				F >> ch;
				F >> start; F >> finish; F >> sp;
				b[count_block].create(cx, cy, cz, scale_x, scale_y, scale_z, ch);
				b[count_block].set_move_z(start, finish, sp);
				count_block++;
			}
		}
		F.close();
	}
	else MessageBox(NULL,"File not found","Ok!",MB_OK);
	player_x = start_x;  
 	player_y = start_y;
 	player_z = start_z; 
}
GLvoid ReSizeGLScene(GLsizei width, GLsizei height)		// Resize And Initialize The GL Window
{
	if (height==0)										// Prevent A Divide By Zero By
	{
		height=1;										// Making Height Equal One
	}

	glViewport(0,0,width,height);						// Reset The Current Viewport

	glMatrixMode(GL_PROJECTION);						// Select The Projection Matrix
	glLoadIdentity();									// Reset The Projection Matrix

	// Calculate The Aspect Ratio Of The Window
	gluPerspective(45.0f,(GLfloat)width/(GLfloat)height,0.1f,2000.0f);

	glMatrixMode(GL_MODELVIEW);							// Select The Modelview Matrix
	glLoadIdentity();									// Reset The Modelview Matrix
}
LRESULT CALLBACK WndProc(	HWND	hWnd,			// Handle For This Window
							UINT	uMsg,			// Message For This Window
							WPARAM	wParam,			// Additional Message Information
							LPARAM	lParam)			// Additional Message Information
{
	switch (uMsg)									// Check For Windows Messages
	{
		case WM_ACTIVATE:							// Watch For Window Activate Message
		{
			if (!HIWORD(wParam))					// Check Minimization State
			{
				active=TRUE;						// Program Is Active
			}
			else
			{
				active=FALSE;						// Program Is No Longer Active
			}

			return 0;								// Return To The Message Loop
		}

		case WM_SYSCOMMAND:							// Intercept System Commands
		{
			switch (wParam)							// Check System Calls
			{
				case SC_SCREENSAVE:					// Screensaver Trying To Start?
				case SC_MONITORPOWER:				// Monitor Trying To Enter Powersave?
				return 0;							// Prevent From Happening
			}
			break;									// Exit
		}

		case WM_CLOSE:								// Did We Receive A Close Message?
		{
			PostQuitMessage(0);						// Send A Quit Message
			return 0;								// Jump Back
		}
		case WM_KEYUP:
		  switch(wParam)
		  {
		  case VK_UP:
			   break;
		  case VK_DOWN:
			   break;
		 case VK_RIGHT:
			   break;
		 case VK_LEFT:
			   break;
		 case VK_TAB:
			 view = 0;
			 break;
		  }
			break;
		
		case WM_KEYDOWN:							// Is A Key Being Held Down?
			switch(wParam)
			{
				/*case 'W':
					g_Camera.MoveCamera(kSpeed);
				break;
				case 'S':
					g_Camera.MoveCamera(-kSpeed);
				break;
				case 'D':
					g_Camera.RotateView(-kSpeed, 0, 1, 0);
				break;
				case 'A':
					g_Camera.RotateView(kSpeed, 0, 1, 0);
				break;
				case 'Z':
					g_Camera.m_vPosition.y -= 0.3f;
					g_Camera.m_vView.y -= 0.3f;
				break;
				case 'C':
					g_Camera.m_vPosition.y += 0.3f;
					g_Camera.m_vView.y += 0.3f;
				break;*/
				case 'M':
					break;
				case VK_TAB:
					view = 1;
					break;
				/*case VK_SPACE:

					break;*/
			}
		 break;

	/*	case WM_KEYUP:								// Has A Key Been Released?
		{
			keys[wParam] = FALSE;					// If So, Mark It As FALSE
			return 0;								// Jump Back
		}*/

		case WM_SIZE:								// Resize The OpenGL Window
		{
			ReSizeGLScene(LOWORD(lParam),HIWORD(lParam));  // LoWord=Width, HiWord=Height
			return 0;								// Jump Back
		}

	}

	// Pass All Unhandled Messages To DefWindowProc
	return DefWindowProc(hWnd,uMsg,wParam,lParam);
}
void renderSphere( float cx, float cy, float cz, float r, int p )
{
    const float PI     = 3.14159265358979f;
    const float TWOPI  = 6.28318530717958f;
    const float PIDIV2 = 1.57079632679489f;

    float theta1 = 0.0;
    float theta2 = 0.0;
    float theta3 = 0.0;

    float ex = 0.0f;
    float ey = 0.0f;
    float ez = 0.0f;

    float px = 0.0f;
    float py = 0.0f;
    float pz = 0.0f;

    // Disallow a negative number for radius.
    if( r < 0 )
        r = -r;

    // Disallow a negative number for precision.
    if( p < 0 )
        p = -p;

    // If the sphere is too small, just render a OpenGL point instead.
    if( p < 4 || r <= 0 ) 
    {
        glBegin( GL_POINTS );
        glVertex3f( cx, cy, cz );
        glEnd();
        return;
    }

    for( int i = 0; i < p/2; ++i )
    {
        theta1 = i * TWOPI / p - PIDIV2;
        theta2 = (i + 1) * TWOPI / p - PIDIV2;

        glBegin( GL_TRIANGLE_STRIP );
        {
            for( int j = 0; j <= p; ++j )
            {
                theta3 = j * TWOPI / p;

                ex = cosf(theta2) * cosf(theta3);
                ey = sinf(theta2);
                ez = cosf(theta2) * sinf(theta3);
                px = cx + r * ex;
                py = cy + r * ey;
                pz = cz + r * ez;

                glNormal3f( ex, ey, ez );
                glTexCoord2f( -(j/(float)p) , 2*(i+1)/(float)p );
                glVertex3f( px, py, pz );

                ex = cosf(theta1) * cosf(theta3);
                ey = sinf(theta1);
                ez = cosf(theta1) * sinf(theta3);
                px = cx + r * ex;
                py = cy + r * ey;
                pz = cz + r * ez;

                glNormal3f( ex, ey, ez );
                glTexCoord2f( -(j/(float)p), 2*i/(float)p );
                glVertex3f( px, py, pz );
            }
        }
        glEnd();
    }
}
AUX_RGBImageRec *LoadBMP(char *Filename)
{
	FILE *File = NULL;
	if(!Filename) return NULL;
	File = fopen(Filename, "r");
	if(File)
	{
		fclose(File);
		return auxDIBImageLoad(Filename);
	}
	return NULL;
}

int LoadGLTextures(int i, char *name_texture)	//i=0			// Load Bitmaps And Convert To Textures
{
	int Status=FALSE;								
	AUX_RGBImageRec *TextureImage[1];					// Create Storage Space For The Texture
	memset(TextureImage,0,sizeof(void *)*1);           	// Set The Pointer To NULL
	// Load The Bitmap, Check For Errors, If Bitmap's Not Found Quit
	if (TextureImage[0]=LoadBMP(name_texture))
	{
		Status=TRUE;								
		glGenTextures(1, &texture[i]);					// Create The Texture
		// Typical Texture Generation Using Data From The Bitmap
		glBindTexture(GL_TEXTURE_2D, texture[i]);
		glTexImage2D(GL_TEXTURE_2D, 0, 3, TextureImage[0]->sizeX, TextureImage[0]->sizeY, 0, GL_RGB, GL_UNSIGNED_BYTE, TextureImage[0]->data);
		glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
	}
	if (TextureImage[0])									// If Texture Exists
	{
		if (TextureImage[0]->data)							// If Texture Image Exists
		{
			free(TextureImage[0]->data);					// Free The Texture Image Memory
		}
		free(TextureImage[0]);								// Free The Image Structure
	}
	return Status;										// Return The Status
}
GLvoid BuildFont(GLvoid)                    // Build Our Bitmap Font
{
    HFONT   font;                       // Windows Font ID
    HFONT   oldfont;                    // Used For Good House Keeping
 
    base = glGenLists(96);                  // Storage For 96 Characters ( NEW )
	font = CreateFont(  -24, 0, 0, 0, FW_BOLD, FALSE, FALSE, FALSE, ANSI_CHARSET,   OUT_TT_PRECIS,
					CLIP_DEFAULT_PRECIS, ANTIALIASED_QUALITY, FF_DONTCARE|DEFAULT_PITCH, "Courier New");  
	 oldfont = (HFONT)SelectObject(hDC, font);       // Selects The Font We Want
    wglUseFontBitmaps(hDC, 32, 96, base);           // Builds 96 Characters Starting At Character 32
    SelectObject(hDC, oldfont);             // Selects The Font We Want
    DeleteObject(font);                 // Delete The Font
}
GLvoid KillFont(GLvoid)                     // Delete The Font List
{
    glDeleteLists(base, 96);                // Delete All 96 Characters ( NEW )
}
GLvoid glPrint(const char *fmt, float t2)                // Custom GL "Print" Routine
{
	char        text[256];         
	va_list     ap;                 // Pointer To List Of Arguments
	if (fmt == NULL)            
    return;                
	va_start(ap, fmt);                  // Parses The String For Variables
    vsprintf(text, fmt, ap);                // And Converts Symbols To Actual Numbers
	va_end(ap);                     // Results Are Stored In Text
	glPushAttrib(GL_LIST_BIT);              // Pushes The Display List Bits     ( NEW )
	glListBase(base - 32);                  // Sets The Base Character to 32    ( NEW )
	   glCallLists(strlen(text), GL_UNSIGNED_BYTE, text);  // Draws The Display List Text  ( NEW )
    glPopAttrib();                      // Pops The Display List Bits   ( NEW )
}
#endif
