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

int step, distance, edge;
float angle_X, angle_Y, angle_Z;
int offset_X, offset_Y, offset_Z;
int border_X, border_Y, border_Z;


void Start(int x, int y, int _step, int _distance, int _edge);
void loop();
void InitCube3D();
void InitProgection();
void Draw();

int main()
{
	Start(800, 600, 2, 25, 3);
	loop();
}

void loop()
{
	int key;
	while(key != ESC)
	{
		switch (key)
		{
			case LEFT: 	if(offset_X - step > -border_X)
							offset_X = offset_X - step;
						break;
			case RIGHT: if(offset_X + step < border_X)
							offset_X = offset_X + step;
						break;
			case UP: 	if(offset_Y - step > -border_Y)
							offset_Y = offset_Y - step;
						break;
			case DOWN: 	if(offset_Y + step < border_Y)
							offset_Y = offset_Y + step;
						break;
			case RSZM: 	if(offset_Z - step > -10)
							offset_Z = offset_Z - step;
						break;
			case RSZP: 	if(offset_Z + step < 10)
							offset_Z = offset_Z + step;
						break;
			case ROTX: 	angle_X = angle_X + 10;
						break;
			case ROTY: 	angle_Y = angle_Y + 10;
						break;
			case ROTZ: 	angle_Z = angle_Z + 10;
						break;
		}
		InitCube3D();
		InitProgection();
		Draw();
		key = getch();
		delay(10);
	}
}

void Start(int x, int y, int _step, int _distance, int _edge)
{
	initwindow(x, y);
	step = _step;
	distance = _distance;
	edge = _edge;
	
	offset_X = 0; offset_Y = 0; offset_Z = 0;
	angle_X = 0; angle_Y = 0; angle_Z = 0;
	

	
	border_X = getmaxx() / (2 * (distance + edge));
	border_Y = getmaxy() / (2 * (distance + edge));
	
	setbkcolor(15);
	setcolor(0);
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
}
void InitCube3D()
{
	for(int i = 0; i < Cube_length; i++)
	{
		Data[i].x = Cube[i].x;
		Data[i].y = Cube[i].y;
		Data[i].z = Cube[i].z;
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
		Data[i].z = Data[i].z + offset_Z;
	}
}


void InitProgection()
{
	float tempz;
	for(int i = 0; i < Cube_length; i++)
	{
		tempz = (getmaxy()/2) / (distance + Data[i].z);
		Prog[i].x = Data[i].x * tempz + (getmaxx()/2);
		Prog[i].y = Data[i].y * tempz + (getmaxy()/2);
	}

}

void Draw()
{
	cleardevice();
	for(int i = 0; i < Ribs_length; i++)
	{
		setcolor(0);
		line(Prog[ribs[i][0]].x, Prog[ribs[i][0]].y, Prog[ribs[i][1]].x, Prog[ribs[i][1]].y);	
	}
}
