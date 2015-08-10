class Block
{
private:
	float scale_x;  float scale_y;   float scale_z;
	float block_x1; float block_y1;  float block_z2;
	float block_x2; float block_y2;  float block_z1; 
////////////////////////////////////////////////////
	float x_start;   float x_finish;
	float y_start;   float y_finish;
	float z_start;   float z_finish;
public:
	float direction_x;
	float direction_y;
	float direction_z;

	bool move_by_player;
	bool trampoline;
	bool simple_block;
	void calculate()
	{
		block_x2 = block_x1 + scale_x;
		block_y2 = block_y1 + scale_y;
		block_z1 = block_z2 - scale_z;  //z1 < z2
	}
	Block() 
	{
		 move_by_player = false;
		 direction_x = 0.0f; 
		 direction_y = 0.0f; 
		 direction_z = 0.0f; 
	}
	void create(float cx, float cy, float cz, float sx, float sy, float sz, char ch)
	{
		block_x1 = cx;
		block_y1 = cy;
		block_z2 = cz;

		scale_x = sx;
		scale_y = sy;
		scale_z = sz;
		calculate();
		if(ch == 's') simple_block = true;
		if(ch == 't') trampoline = true;
		if(ch == 'p') move_by_player = true;
	}

	float get_blockx1() { return block_x1; }
	float get_blocky1() { return block_y1; }
	float get_blockz1() { return block_z2; }

	float get_blockx2() { return block_x2; }
	float get_blocky2() { return block_y2; }
	float get_blockz2() { return block_z1; }

	float get_scale_x() { return scale_x; }
	float get_scale_y() { return scale_y; }
	float get_scale_z() { return scale_z; }
	void move_x()  //float x_start, float x_finish
	{
		if(block_x2 >= x_finish || block_x1 <= x_start) direction_x = -direction_x; //=
		block_x1 += direction_x;
	}
	void move_z()   //float z_start, float z_finish
	{
		if(block_z2 >= z_finish || block_z1 <= z_start) direction_z = -direction_z;
		block_z2 += direction_z;
	}
	void move_y()   // float y_start, float y_finish
	{
		if(block_y2 > y_finish || block_y1 < y_start) direction_y = -direction_y;
		block_y1 += direction_y;
	}
	void move_by_player_x(float speed)
	{
		 block_x1 += speed;
	}
	void move_by_player_z(float speed)
	{
		block_z2 += speed;
	}
	void set_move_x(float x1, float x2, float speed)
	{
		x_start = x1;
		x_finish = x2;
		direction_x = speed;
	}
	void set_move_y(float y1, float y2, float speed)
	{
		y_start = y1;
		y_finish = y2;
		direction_y = speed;
	}
	void set_move_z(float z1, float z2, float speed)
	{
		z_start = z1;
		z_finish = z2;
		direction_z = speed;
	}
};
