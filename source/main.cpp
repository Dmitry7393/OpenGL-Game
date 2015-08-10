#include "Draw_Scene.h"
#include "Animate.h"
#include <iostream>
using namespace std;
bool allow_move_right = true;
bool allow_move_left = true;
bool allow_move_up = true;
bool allow_move_down = true;
float first_player_x;
float first_player_y;
float first_player_z;

bool collision();
void start_level()  
{
	player_x = start_x;  //0.0f;   
 	player_y = start_y;  //11.0f; 
 	player_z = start_z;  // 2.0f;
	speed_jump = 0.0f;
	g2 = 0.01f;			//init
}
bool end_game()
{
	if(player_x >= b[count_block-1].get_blockx1() && player_x <= b[count_block-1].get_blockx2() &&
	player_z >= b[count_block-1].get_blockz2()+0.5f && player_z <= b[count_block-1].get_blockz1() &&  
	player_y >= ground_level+1.5f && player_y <= ground_level+1.5f+1.5f)
	{
		return true;
	}
	return false;
}
void next_level()
{
	level_number++;
	char str[24];
	char temp_str[6] = ""; 
	strcpy(str, "");
	strcat(str, "Data/level/level");
	strcat(str, itoa(level_number, temp_str, 10));
	strcat(str, ".txt");
	MessageBox(NULL,"FINISH","Win!",MB_OK);  
    start_level();
	create_level();
	//ReSizeGLScene(940, 580); ?
}
int collision_with_block()
{
	for(int i = 0; i < count_block; i++)
	{
		if(b[i].trampoline == true)
		{
			if(player_x >= b[i].get_blockx1() && player_x <= b[i].get_blockx2() &&
				player_z >= b[i].get_blockz2()+0.5f && player_z <= b[i].get_blockz1()+0.5f &&
				player_y >= ground_level+1.5f && player_y <= ground_level+1.5f+1.0f)  //на нужной высоте 
			{      //
				return 2;
			}
		}
		else  //simple block
		{
			if(player_x >= b[i].get_blockx1() && player_x <= b[i].get_blockx2() &&
				player_z >= b[i].get_blockz2()+0.5f && player_z <= b[i].get_blockz1() &&   //+0.5f
				player_y >= ground_level+1.5f && player_y <= ground_level+1.5f+1.5f)  //на нужной высоте  
			{
				return 1;
			}
		}
	}
	if(collision() == true)
	{
		if(player_x > b[number_platform].get_blockx2())
		{
			player_x += 0.5f;
		}
		if(player_x < b[number_platform].get_blockx1())
		{
			player_x -= 0.5f;
		}
		if(player_z < b[number_platform].get_blockz2())  //original -  b[number_platform].get_blockz1()) 
		{
			if(player_flight == true)
			player_z += 0.5f;
			else  	player_z -= 0.5f;  //-
		}
		if(player_z > b[number_platform].get_blockz1())  //original- b[number_platform].get_blockz2())
		{
			if(player_flight == true)
			player_z -= 0.5f;
			else  player_z += 0.5f;  //+
		}
	}
	return 0;
}
/*bool collision_with_trampoline() //проверяется, над какой платформой находится игрок 
{
	for(int i = 0; i < count_block; i++) //цикл по всем платформам
	{
		if(b[i].trampoline == true)
		{
			if(player_x >= b[i].get_blockx1() && player_x <= b[i].get_blockx2() &&
				player_z >= b[i].get_blockz2() && player_z <= b[i].get_blockz1()+0.5f &&
				player_y >= ground_level+1.5f && player_y <= ground_level+1.5f+1.0f)  //на нужной высоте 
			{
				return true;
			}
		}
	} 
	return false;
}*/
void change_ground_level() //определение уровня земли
{
	for(int i = 0; i < count_block; i++)
	{
		if(player_x >= b[i].get_blockx1()-1.5f && player_x <= b[i].get_blockx2()+1.5f && 
		   player_z >= b[i].get_blockz2()-1.5f && player_z <= b[i].get_blockz1()+1.5f &&
		   player_y >= b[i].get_blocky2() )
		//   player_y >= b[i].get_blocky1() && player_y <= b[i].get_blocky2()+0.5f)
		{
			ground_level = b[i].get_blocky2();
			if(collision_with_block() == 1)   //_with_block
			number_platform = i;
		}
	}
}
bool collision_with_box(float px, float py, float pz, float cx1, float cx2, float cy1, float cy2, float cz1, float cz2)
{
	float nx = px, ny = py, nz = pz;
	if (nx < cx1) nx = cx1;
	if (nx > cx2) nx = cx2;
	if (ny < cy1) ny = cy1;
	if (ny > cy2) ny = cy2;
	if (nz < cz1) nz = cz1;
	if (nz > cz2) nz = cz2;
	float dx = player_x - nx, dy = player_y - ny, dz = player_z - nz;
	return dx * dx + dy * dy + dz * dz <= 1.5f * 1.5f;
}
bool collision()
{
	for(int i = 0; i < count_block; i++)
	{
		if(collision_with_box(player_x, player_y, player_z, b[i].get_blockx1(), b[i].get_blockx2(),
                                                            b[i].get_blocky1(), b[i].get_blocky2(),
                                                            b[i].get_blockz2(), b[i].get_blockz1()) == true)
		{
			return true;
		}
	}
	return false;
}
int move_platform() //если платформа движется
{
	for(int i = 0; i < count_block; i++)  //цикл по всем платформам
	{
		if(player_x >= b[i].get_blockx1() && player_x <= b[i].get_blockx2() && 
		   player_z >= b[i].get_blockz2() && player_z <= b[i].get_blockz1() )
		{
			 return i;
		}
	} 
	return 0;
}
int WINAPI WinMain(	HINSTANCE	hInstance,		
					HINSTANCE	hPrevInstance,	
					LPSTR		lpCmdLine,	
					int			nCmdShow)
{
	MSG		msg;							
	BOOL	done=FALSE;								// Bool Variable To Exit Loop
		fullscreen=FALSE;			
	// Create OpenGL Window
	if (!CreateGLWindow("OpenGL Game",940,580,16,fullscreen))
	{
		return 0;									
	}
	ReSizeGLScene(940, 580);
	while(!done)									// Loop That Runs While done=FALSE
	{
		if (PeekMessage(&msg,NULL,0,0,PM_REMOVE))	
		{
			if (msg.message==WM_QUIT)				
			{
				done=TRUE;						
			}
			else								
			{
				TranslateMessage(&msg);				
				DispatchMessage(&msg);				
			}
		}
		else										
		{
			if(AnimateNextFrame(60))	// Make sure we only animate 60 FPS
			{
			     if(player_y <= -95.0f)  //restart game
                 {
                      start_level();
                 }
				 if(end_game() == true) next_level();
				 change_ground_level(); //1
				if(player_flight == false)  //шарик не в полете - выполняется
                 {
                      if(collision_with_block() == 0 )   //&& collision() == false
                      {
                           player_y -= (0.3f + g2);  //fall down
						   g2 += 0.01f;
                      }
				 }
				 collision_with_block() ;///new
					   if(collision_with_block() == 2)
					   {
						  speed_jump = 1.5f;
						  g2 = 0.01f; //init
						  player_flight = true;
					   }
					change_ground_level();  //2
				if(player_flight == true)
                 {
                        player_y += speed_jump;
                        speed_jump -= 0.03f;
						 if(collision_with_block() == 1)
						{
							//MessageBox(NULL,"b","Ok!",MB_OK);
							player_flight = false;
					    }

                  }
				first_player_x = player_x;  //координаты игрока до передвижения
				first_player_z = player_z;
				//Движение кубиков
				for(int i = 0; i < count_block; i++)
				{
					b[i].move_x();
					b[i].move_y();
					b[i].move_z();
				}
				 //Движущийся куб двигает шарик в соответственном направлении
				 for(int i = 0; i < count_block; i++)
				 {
					 if(collision_with_box(player_x, player_y, player_z, b[i].get_blockx1(), b[i].get_blockx2(),
                                                                         b[i].get_blocky1(), b[i].get_blocky2(),
                                                                         b[i].get_blockz2(), b[i].get_blockz1()) == true)
					 {
							player_x += b[i].direction_x;
							player_y += b[i].direction_y;
							player_z += b[i].direction_z;
					 }
				 }
				 //Движение игрока вместе с платформой
				for(int i = 0; i < count_block; i++)
				{
					  if(move_platform() == i)
					  {
							 player_x += b[move_platform()].direction_x;
							 player_y += b[move_platform()].direction_y;
							 player_z += b[move_platform()].direction_z;
					  }
				}
				if(GetAsyncKeyState('W'))
				{
					if(allow_move_up == true)
					{
					player_z -= speed;  //+a
					rotate_x -= 1.9f;
					}
				}
				if(GetAsyncKeyState('S'))
				{
					if(allow_move_down == true)
					{
						 player_z += speed;
						 rotate_x += 1.9f;
					}
				}
				if(GetAsyncKeyState('D'))
				{
					if(allow_move_right == true)
					{
						player_x += speed;
						rotate_z -= 1.9f;
					}
				}
			
				if(GetAsyncKeyState('A'))
				{
					if(allow_move_left == true)
					{
						player_x -= speed;
						rotate_z += 1.9f;
					}
				}	
				if(GetAsyncKeyState(VK_ESCAPE))
				{
					done = true;
				}
				if(GetAsyncKeyState(VK_SPACE))  //
				{
					if(collision_with_block() == 1 && player_y >= ground_level)
					{
						if(player_flight == false)
						{
							   player_flight = true;
							   speed_jump = 0.9f;
						}
					}
				}
				for(int i = 0; i < count_block; i++)
				{
					if(collision_with_box(player_x, player_y, player_z, b[i].get_blockx1(), b[i].get_blockx2(),
																		b[i].get_blocky1(), b[i].get_blocky2(), 
																		b[i].get_blockz2(), b[i].get_blockz1()) == true)
					{
						//SetWindowText(hWnd,"collision __-");
						if(player_x < first_player_x) 
						{
							if(b[i].move_by_player == false)
							player_x = player_x + speed + 0.3f;    // player_x += 1.1f;  //f-player_x += speed;  
							else
							b[i].move_by_player_x(-speed); 
						}
						if(player_z < first_player_z)
						{
							if(b[i].move_by_player == false)
							player_z += speed;
							else
							b[i].move_by_player_z(-speed); 
						}
						if(player_z > first_player_z)
						{
							if(b[i].move_by_player == false)
							player_z -= speed;
							else
							b[i].move_by_player_z(speed); 
						}
						if(player_x > first_player_x) 
						{  
							if(b[i].move_by_player == false) player_x = player_x - speed + b[i].direction_x;
						//	player_x -= speed; 
							else
							b[i].move_by_player_x(speed); 
						};
					}
				}
				DrawGLScene();						// Render the scene every frame
				SwapBuffers(hDC);	
				if (keys[VK_F1])					
				{
					keys[VK_F1]=FALSE;			
					KillGLWindow();					
					fullscreen=!fullscreen;			
					// Recreate OpenGL Window
					if (!CreateGLWindow("OpenGL game",940,580,16,fullscreen))
					{
						return 0;			
					}
				}
			}
		}
	}
	// Shutdown
	KillGLWindow();									// Kill The Window
	return (msg.wParam);							// Exit The Program
}
