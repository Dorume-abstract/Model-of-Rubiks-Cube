#include <graphics.h>
#include <math.h>
#include <iostream>
#define ESC 27
#define LEFT 75
#define RIGHT 77
#define UP 72
#define DOWN 80
#define ROTX 100
#define ROTY 119
#define ROTZ 97
#define RSZP 120
#define RSZM 122
#define M_PI 3.14/180

struct Points
{
	double x, y, z;
};

struct Projection
{
	int x, y;	
};
Points Cube[64];
int ribs[72][2] = {{0,3}, {0,12}, {3,15}, {12,15},
					{4,7}, {8,11}, {1,13}, {2,14},
					{0,48}, {3,51}, {12,60}, {15,63},
					{48,51}, {48,60}, {60,63}, {63,51},
					{20,23}, {24,27}, {36,39}, {40,43},
					{5,53}, {6,54}, {9,57}, {10,58},
					{16,19}, {32,35},
					{16,28}, {32,44},
					{19, 31}, {35,47},
					{28,31}, {44,47},
					{1,49}, {2,50},
					{4,52}, {8,56},
					{13,61}, {14,62},
					{7,55}, {11, 59},
					{49,61}, {50,62},
					{52,55}, {56,59}};
					
const int Cube_length = sizeof(Cube) / sizeof(Cube[0]), Ribs_length = sizeof(ribs) / sizeof(ribs[0]);

Points Data[Cube_length];
Projection Prog[Ribs_length];

int step, edge;
float angle_X, angle_Y, angle_Z;
int offset_X, offset_Y;
float Size;


void Start(int x, int y, int _step, int _edge);
void Instruction();
void loop();
void InitCube3D();
void InitProgection();
void Draw();

int main()
{
	Start(800, 600, 10, 30);
	loop();
	return 0;
}

void loop()
{
	int key;
	while(key != ESC)
	{
		switch (key)
		{
			case LEFT: 	if(getmaxx()/2 - 50 + offset_X > 0)
							offset_X = offset_X - step;
						break;
			case RIGHT: if(getmaxx()/2 - 50 - offset_X > 0)
							offset_X = offset_X + step;
						break;
			case UP: 	if(getmaxy()/2 - 50 + offset_Y > 0)
							offset_Y = offset_Y - step;
						break;
			case DOWN: 	if(getmaxy()/2 - 50 - offset_Y > 0)
							offset_Y = offset_Y + step;
						break;
			case RSZP: 	if(Size - 1 > 0)
							Size = Size - (float)1/step;
						break;
			case RSZM: 	if(Size - 1 < 4)
							Size = Size + (float)1/step;
						break;
			case ROTX: 	angle_X = angle_X + step;
						break;
			case ROTY: 	angle_Y = angle_Y + step;
						break;
			case ROTZ: 	angle_Z = angle_Z + step;
						break;
		}
		std::cout<<angle_Y<<std::endl;
		InitCube3D();
		InitProgection();
		Draw();
		key = getch();
		delay(10);
	}
	closegraph();
}

void Start(int x, int y, int _step, int _edge)
{
	initwindow(x, y);
	step = _step;
	edge = _edge;
	
	offset_X = 0; offset_Y = 0;
	Size = 2;
	angle_X = 0; angle_Y = 0; angle_Z = 0;
	
	setbkcolor(15);
	setcolor(0);
	cleardevice();
	
	int i;
	i = 0;
	for(int y = 0; y < 4; y++)
		for(int z = 0; z < 4; z++)
			for(int x = 0; x < 4; x++)
			{
				Cube[i].x = edge * x - 1.5 * edge;
				Cube[i].z = edge * z - 1.5 * edge;
				Cube[i].y = edge * y - 1.5 * edge;
				i++;
			}
			
	Instruction();
}
void InitCube3D()
{
	for(int i = 0; i < Cube_length; i++)
	{
		Data[i].x = Cube[i].x * Size;
		Data[i].y = Cube[i].y * Size;
		Data[i].z = Cube[i].z * Size;
	}
	
	double cosi = cos(angle_X * M_PI);
	double sinu = sin(angle_X * M_PI);
	for(int i = 0; i < Cube_length; i++)
	{
		double y = Data[i].y;
		double z = Data[i].z;
		Data[i].y = y * cosi - z * sinu;
		Data[i].z = z * cosi + y * sinu;
	}
	
	cosi = cos(angle_Y * M_PI);
	sinu = sin(angle_Y * M_PI);
	for(int i = 0; i < Cube_length; i++)
	{
		double x = Data[i].x;
		double z = Data[i].z;
		Data[i].x = x * cosi - z * sinu;
		Data[i].z = z * cosi + x * sinu;
	}
	
	cosi = cos(angle_Z * M_PI);
	sinu = sin(angle_Z * M_PI);
	for(int i = 0; i < Cube_length; i++)
	{
		double x = Data[i].x;
		double y = Data[i].y;
		Data[i].x = x * cosi - y * sinu;
		Data[i].y = y * cosi + x * sinu;
	}
	
	for(int i = 0; i < Cube_length; i++)
	{
		Data[i].x = Data[i].x + offset_X;
		Data[i].y = Data[i].y + offset_Y;
		Data[i].z = Data[i].z;
	}
}


void InitProgection()
{
	for(int i = 0; i < Cube_length; i++)
	{
		Prog[i].x = Data[i].x + (getmaxx()/2);
		Prog[i].y = Data[i].y + (getmaxy()/2);
	}
}

void Draw()
{
	cleardevice();
	for(int i = 0; i < Ribs_length; i++)
	{
		line(Prog[ribs[i][0]].x, Prog[ribs[i][0]].y, Prog[ribs[i][1]].x, Prog[ribs[i][1]].y);	
	}
}

void Instruction()
{
	outtextxy (getmaxx()/4, getmaxy()/2 - 20, "ўоб рухати куб≥к використовуйте стр≥лки.");
	outtextxy (getmaxx()/4, getmaxy()/2, "ўоб зм≥нювати розм≥ри маг≥чного куба натискайте Z або X.");
	outtextxy (getmaxx()/4, getmaxy()/2 + 20, "ƒл€ того щоб повернути його використовуйте W, A, D."  );
	getch();
}
