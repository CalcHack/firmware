#include "gfx_3d.h"
#include "gfx_2d.h"
#include "stm32f10x_conf.h"
#include "math.h"


int zoomlevel = 60;
int brightness_3d = 200;

#define shape_cube

Scene scene1;


vertice activevertice;

#ifdef shape_cube

   int polygoncount = 12;

    polygon polygon_arr[12] = {
    {{50,50,50},{-50,50,50},{50,50,-50},0},
    {{-50,50,50},{50,50,-50},{-50,50,-50},63},
    {{50,-50,50},{-50,-50,50},{50,-50,-50},0},
    {{-50,-50,50},{50,-50,-50},{-50,-50,-50},63},
    {{50,50,50},{50,50,-50},{50,-50,50},63},
    {{50,-50,50},{50,50,-50},{50,-50,-50},126},
    {{-50,50,50},{-50,50,-50},{-50,-50,50},63},
    {{-50,-50,50},{-50,50,-50},{-50,-50,-50},126},
    {{50,50,50},{-50,50,50},{50,-50,50},126},
    {{-50,50,50},{50,-50,50},{-50,-50,50},189},
    {{-50,50,-50},{50,50,-50},{-50,-50,-50},126},
    {{50,50,-50},{-50,-50,-50},{50,-50,-50},189}};
      
//      polygon polygon_arr[24] = {
//    {{-10,20,20},{-50,20,20},{-10,20,-20},0},
//    {{-50,20,20},{-10,20,-20},{-50,20,-20},63},
//    {{-10,-20,20},{-50,-20,20},{-10,-20,-20},0},
//    {{-50,-20,20},{-10,-20,-20},{-50,-20,-20},63},
//    {{-10,20,20},{-10,20,-20},{-10,-20,20},63},
//    {{-10,-20,20},{-10,20,-20},{-10,-20,-20},126},
//    {{-50,20,20},{-50,20,-20},{-50,-20,20},63},
//    {{-50,-20,20},{-50,20,-20},{-50,-20,-20},126},
//    {{-10,20,20},{-50,20,20},{-10,-20,20},126},
//    {{-50,20,20},{-10,-20,20},{-50,-20,20},189},
//    {{-50,20,-20},{-10,20,-20},{-50,-20,-20},126},
//    {{-10,20,-20},{-40,-20,-20},{-10,-20,-20},189},
//    {{50,20,20},{10,20,20},{50,20,-20},0},
//    {{10,20,20},{50,20,-20},{10,20,-20},63},
//    {{50,-20,20},{10,-20,20},{50,-20,-20},0},
//    {{10,-20,20},{50,-20,-20},{10,-20,-20},63},
//    {{50,20,20},{50,20,-20},{50,-20,20},63},
//    {{50,-20,20},{50,20,-20},{50,-20,-20},126},
//    {{10,20,20},{10,20,-20},{10,-20,20},63},
//    {{10,-20,20},{10,20,-20},{10,-20,-20},126},
//    {{50,20,20},{10,20,20},{50,-20,20},126},
//    {{10,20,20},{50,-20,20},{10,-20,20},189},
//    {{10,20,-20},{50,20,-20},{10,-20,-20},126},
//    {{50,20,-20},{10,-20,-20},{50,-20,-20},189}};
      
        
#endif
#ifdef shape_pyramid
    vertice vertice1 = {50,-50,50};
    vertice vertice2 = {-50,-50,50};
    vertice vertice3 = {50,-50,-50};
    vertice vertice4 = {-50,-50,-50};
    vertice vertice5 = {0,100,0};
    vertice vertice6 = {50,-50,50};
    vertice vertice7 = {-50,-50,50};
    vertice vertice8 = {50,-50,-50}; 
#endif   

void translate(vertice *vertice_ptr, vector vector)
{
  vertice_ptr -> x += vector.x;
  vertice_ptr -> y += vector.y;
    vertice_ptr -> z += vector.z;
}

point vertice_to_point(vertice vertice)
{
  point point;
  point.x = vertice.x * 10000 / vertice.z;
  point.y = vertice.y * 10000 / vertice.z;
  return point;
}

//void rotate_x(vertice *vertice_ptr, int angle)
void rotate_x(vertice *vertice_ptr, int angle)
{
  float sinangle = sin(angle * 0.0174532925);
  float cosangle = cos(angle * 0.0174532925);
  float y = cosangle * (vertice_ptr -> y) - sinangle * (vertice_ptr -> z);
  vertice_ptr -> z = cosangle * (vertice_ptr -> z) + sinangle * (vertice_ptr -> y);
  vertice_ptr -> y = y;
}
void rotate_y(vertice *vertice_ptr, int angle)
{
  float sinangle = sin(angle * 0.0174532925);
  float cosangle = cos(angle * 0.0174532925);
  float x = cosangle * (vertice_ptr -> x) + sinangle * (vertice_ptr -> z);
  vertice_ptr -> z = cosangle * (vertice_ptr -> z) - sinangle * (vertice_ptr -> x);
  vertice_ptr -> x = x;
}


void gfx_3d_init()
{
  vector vector3 = {0,0,-500};
  for(int i = 0; i < polygoncount; i++)
    {
    translate(&polygon_arr[i].vertice1, vector3);
    translate(&polygon_arr[i].vertice2, vector3);
    translate(&polygon_arr[i].vertice3, vector3);
    }
}

void BubbleSort(float a[], int b[], int array_size)
{
    int i, j, temp;
    for (i = 0; i < (array_size - 1); ++i)
    {
        for (j = 0; j < array_size - 1 - i; ++j )
        {
             if (a[j] > a[j+1])
             {
                  temp = a[j+1];
                  a[j+1] = a[j];
                  a[j] = temp;
                  temp = b[j+1];
                  b[j+1] = b[j];
                  b[j] = temp;
             }
        }
    }
}   

void drawpolygon(polygon polygon)
{
    point point1 = vertice_to_point(polygon.vertice1);
    point point2 = vertice_to_point(polygon.vertice2);
    point point3 = vertice_to_point(polygon.vertice3);

    point1.x = floorf(point1.x / zoomlevel + 48);
    point2.x = floorf(point2.x / zoomlevel + 48);
    point3.x = floorf(point3.x / zoomlevel + 48);

    point1.y = floorf(point1.y / zoomlevel + 32);
    point2.y = floorf(point2.y / zoomlevel + 32);
    point3.y = floorf(point3.y / zoomlevel + 32);

    gfx_2d_fill_triangle(point1, point2, point3, polygon.color);
}

void gfx_3d_tick()
{
      vector vector3 = {0,0,500};
   
int angle;
    
    for(int i = 0; i < polygoncount; i++)
    {
    translate(&polygon_arr[i].vertice1, vector3);
    translate(&polygon_arr[i].vertice2, vector3);
    translate(&polygon_arr[i].vertice3, vector3);
    }
    
angle = 1;
    for(int i = 0; i < polygoncount; i++)
    {
    rotate_x(&polygon_arr[i].vertice1, angle);
    rotate_x(&polygon_arr[i].vertice2, angle);
    rotate_x(&polygon_arr[i].vertice3, angle);
    }
angle = 2;
    for(int i = 0; i < polygoncount; i++)
    {
    rotate_y(&polygon_arr[i].vertice1, angle);
    rotate_y(&polygon_arr[i].vertice2, angle);
    rotate_y(&polygon_arr[i].vertice3, angle);
    }

    
     vector3.z=-500;

    for(int i = 0; i < polygoncount; i++)
    {
    translate(&polygon_arr[i].vertice1, vector3);
    translate(&polygon_arr[i].vertice2, vector3);
    translate(&polygon_arr[i].vertice3, vector3);
    }
    
    float a[polygoncount];
    int b[polygoncount];

    for(int i = 0; i < polygoncount; i++)
    {
      
      
      a[i] = polygon_arr[i].vertice1.z;
      a[i] += polygon_arr[i].vertice2.z;
      a[i] += polygon_arr[i].vertice3.z;
     
    }
    for(int i = 0; i < polygoncount; i++)
    {
    b[i] = i;
    }
    BubbleSort(a,b,polygoncount);
   
    
    
    gfx_2d_clear();
	
    brightness_3d = 0;
    
    for(int i = 0; i < polygoncount; i++)
    {
    drawpolygon(polygon_arr[b[i]]);
    }
  
//    gfx_2d_line(point1.x, point1.y, point2.x, point2.y, brightness_3d);
//    gfx_2d_line(point1.x, point1.y, point3.x, point3.y, brightness_3d);
//    gfx_2d_line(point1.x, point1.y, point4.x, point4.y, brightness_3d);
//   // gfx_2d_line(point1.x, point1.y, point5.x, point5.y, brightness_3d);
//   // gfx_2d_line(point1.x, point1.y, point6.x, point6.y, brightness_3d);
//   // gfx_2d_line(point1.x, point1.y, point7.x, point7.y, brightness_3d);
//   // gfx_2d_line(point1.x, point1.y, point8.x, point8.y, brightness_3d);
//brightness_3d += 63;
//   // gfx_2d_line(point2.x, point2.y, point3.x, point3.y, brightness_3d);
//   // gfx_2d_line(point2.x, point2.y, point4.x, point4.y, brightness_3d);
//    gfx_2d_line(point2.x, point2.y, point5.x, point5.y, brightness_3d);
//   // gfx_2d_line(point2.x, point2.y, point6.x, point6.y, brightness_3d);
//    gfx_2d_line(point2.x, point2.y, point7.x, point7.y, brightness_3d);
//   // gfx_2d_line(point2.x, point2.y, point8.x, point8.y, brightness_3d);
//brightness_3d += 63;
//   // gfx_2d_line(point3.x, point3.y, point4.x, point4.y, brightness_3d);
//    gfx_2d_line(point3.x, point3.y, point5.x, point5.y, brightness_3d);
//    gfx_2d_line(point3.x, point3.y, point6.x, point6.y, brightness_3d);
//   // gfx_2d_line(point3.x, point3.y, point7.x, point7.y, brightness_3d);
//   // gfx_2d_line(point3.x, point3.y, point8.x, point8.y, brightness_3d);
//brightness_3d += 63;
//  //  gfx_2d_line(point4.x, point4.y, point5.x, point5.y, brightness_3d);
//    gfx_2d_line(point4.x, point4.y, point6.x, point6.y, brightness_3d);
//    gfx_2d_line(point4.x, point4.y, point7.x, point7.y, brightness_3d);
//  //  gfx_2d_line(point4.x, point4.y, point8.x, point8.y, brightness_3d);
//  
//   // gfx_2d_line(point5.x, point5.y, point6.x, point6.y, brightness_3d);
//   // gfx_2d_line(point5.x, point5.y, point7.x, point7.y, brightness_3d);
//    gfx_2d_line(point5.x, point5.y, point8.x, point8.y, brightness_3d);
//
//   // gfx_2d_line(point6.x, point6.y, point7.x, point7.y, brightness_3d);
//    gfx_2d_line(point6.x, point6.y, point8.x, point8.y, brightness_3d);
//
//    gfx_2d_line(point7.x, point7.y, point8.x, point8.y, brightness_3d);

/*/
    gfx_2d_line(point1.x, point1.y, point2.x, point2.y, brightness_3d);
    gfx_2d_line(point1.x, point1.y, point3.x, point3.y, brightness_3d);
    gfx_2d_line(point1.x, point1.y, point4.x, point4.y, brightness_3d);
    gfx_2d_line(point1.x, point1.y, point5.x, point5.y, brightness_3d);
    gfx_2d_line(point1.x, point1.y, point6.x, point6.y, brightness_3d);
    gfx_2d_line(point1.x, point1.y, point7.x, point7.y, brightness_3d);
    gfx_2d_line(point1.x, point1.y, point8.x, point8.y, brightness_3d);

    gfx_2d_line(point2.x, point2.y, point3.x, point3.y, brightness_3d);
    gfx_2d_line(point2.x, point2.y, point4.x, point4.y, brightness_3d);
    gfx_2d_line(point2.x, point2.y, point5.x, point5.y, brightness_3d);
    gfx_2d_line(point2.x, point2.y, point6.x, point6.y, brightness_3d);
    gfx_2d_line(point2.x, point2.y, point7.x, point7.y, brightness_3d);
    gfx_2d_line(point2.x, point2.y, point8.x, point8.y, brightness_3d);

    gfx_2d_line(point3.x, point3.y, point4.x, point4.y, brightness_3d);
    gfx_2d_line(point3.x, point3.y, point5.x, point5.y, brightness_3d);
    gfx_2d_line(point3.x, point3.y, point6.x, point6.y, brightness_3d);
    gfx_2d_line(point3.x, point3.y, point7.x, point7.y, brightness_3d);
    gfx_2d_line(point3.x, point3.y, point8.x, point8.y, brightness_3d);

    gfx_2d_line(point4.x, point4.y, point5.x, point5.y, brightness_3d);
    gfx_2d_line(point4.x, point4.y, point6.x, point6.y, brightness_3d);
    gfx_2d_line(point4.x, point4.y, point7.x, point7.y, brightness_3d);
    gfx_2d_line(point4.x, point4.y, point8.x, point8.y, brightness_3d);

    gfx_2d_line(point5.x, point5.y, point6.x, point6.y, brightness_3d);
    gfx_2d_line(point5.x, point5.y, point7.x, point7.y, brightness_3d);
    gfx_2d_line(point5.x, point5.y, point8.x, point8.y, brightness_3d);

    gfx_2d_line(point6.x, point6.y, point7.x, point7.y, brightness_3d);
    gfx_2d_line(point6.x, point6.y, point8.x, point8.y, brightness_3d);

    gfx_2d_line(point7.x, point7.y, point8.x, point8.y, brightness_3d);
	*/



}