#include "gfx_3d.h"
#include "gfx_2d.h"
#include "stm32f10x_conf.h"
#include "math.h"

int cnt = 0;

int brightness_3d = 200;

uint32_t polygon_buffer_next_ID = 1;
uint16_t polygon_buffer_next_entry = 0;

const int cubecount = 1;

vector rotation[cubecount];



polygon polygon_buffer[13];

vertice activevertice;

obj3D_Box cube[cubecount];
Camera cam1;

point vertice_to_point(vertice vertice)
{
  point point;
  point.x = vertice.x * 10000 / vertice.z;
  point.y = vertice.y * 10000 / vertice.z;
  return point;
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

void drawpolygon(polygon polygon, float zoomlevel, int width, int height)
{
    point point1 = vertice_to_point(polygon.vertice1);
    point point2 = vertice_to_point(polygon.vertice2);
    point point3 = vertice_to_point(polygon.vertice3);

    point1.x = floorf(point1.x / zoomlevel + width / 2);
    point2.x = floorf(point2.x / zoomlevel + width / 2);
    point3.x = floorf(point3.x / zoomlevel + width / 2);

    point1.y = floorf(point1.y / zoomlevel + height / 2);
    point2.y = floorf(point2.y / zoomlevel + height / 2);
    point3.y = floorf(point3.y / zoomlevel + height / 2);

    gfx_2d_fill_triangle(point1, point2, point3, polygon.color);
}

    
      
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
      
#define polyCount 12
obj3D_Box::obj3D_Box()
{
    ID = 0;
    reset();
}
void obj3D_Box::reset()
{
    hide();
    center.x = 0;
    center.y = 0;
    center.z = 0;
    dimension.x = 1;
    dimension.y = 1;
    dimension.z = 1;
    rotation.x = 0;
    rotation.y = 0;
    rotation.z = 0;
    for(int i = 0; i < 6; i++)
    {
        color_arr[i] = 0;
    }
}
obj3D_Box::~obj3D_Box()
{
    this -> hide();
}
void obj3D_Box::hide()
{
    if(ID != 0)
    {
        int i = 0;
        while(polygon_buffer[i].unique_ID != ID)
        {
            i ++;
        }
        while(i + polyCount < polygon_buffer_next_entry)
        {
            polygon_buffer[i] = polygon_buffer[i + polyCount];
            i++;
        }
        polygon_buffer_next_entry -= polyCount;
        ID = 0;
    }
}
void obj3D_Box::show()
{
    if(ID == 0)
    {
        ID = polygon_buffer_next_ID;
        polygon_buffer_next_ID ++;
        for(int i = polygon_buffer_next_entry; i < polygon_buffer_next_entry + polyCount; i++)
        {
            polygon_buffer[i].unique_ID = ID;
        }
        polygon_buffer_next_entry += polyCount;
        update();
    }
}
void obj3D_Box::rotate(vector rotate)
{
    rotation.x += rotate.x;
    rotation.y += rotate.y;
    rotation.z += rotate.z;
}
void obj3D_Box::move(vector move)
{
    center.x += move.x;
    center.y += move.y;
    center.z += move.z;
}
void obj3D_Box::scale(vector factor)
{
    dimension.x *= factor.x;
    dimension.y *= factor.y;
    dimension.z *= factor.z;
}
void obj3D_Box::resize(vector newsize)
{
    dimension.x = newsize.x;
    dimension.y = newsize.y;
    dimension.z = newsize.z;
}
void obj3D_Box::color(uint8_t newcolor)
{
    for(int i = 0; i < 6; i++)
    {
        color_arr[i] = newcolor;
    }
}
void obj3D_Box::color(uint8_t newcolor[6])
{
    for(int i = 0; i < 6; i++)
    {
        color_arr[i] = newcolor[i];
    }
}
void obj3D_Box::update()
{
    if(ID != 0)
    {
        int i = 0;
        while(polygon_buffer[i].unique_ID != ID)
        {
            i ++;
        }
        vertice vertices[8];
        float dimension_x = 0.5 * dimension.x;
        float dimension_y = 0.5 * dimension.y;
        float dimension_z = 0.5 * dimension.z;
        float minus_dimension_x = -0.5 * dimension.x;
        float minus_dimension_y = -0.5 * dimension.y;
        float minus_dimension_z = -0.5 * dimension.z;
        vertices[0].x = dimension_x;
        vertices[0].y = minus_dimension_y;
        vertices[0].z = dimension_z;
        vertices[1].x = dimension_x;
        vertices[1].y = dimension_y;
        vertices[1].z = dimension_z;
        vertices[2].x = minus_dimension_x;
        vertices[2].y = dimension_y;
        vertices[2].z = dimension_z;
        vertices[3].x = minus_dimension_x;
        vertices[3].y = minus_dimension_y;
        vertices[3].z = dimension_z;
        vertices[4].x = dimension_x;
        vertices[4].y = minus_dimension_y;
        vertices[4].z = minus_dimension_z;
        vertices[5].x = dimension_x;
        vertices[5].y = dimension_y;
        vertices[5].z = minus_dimension_z;
        vertices[6].x = minus_dimension_x;
        vertices[6].y = dimension_y;
        vertices[6].z = minus_dimension_z;
        vertices[7].x = minus_dimension_x;
        vertices[7].y = minus_dimension_y;
        vertices[7].z = minus_dimension_z;
        
        //rotate & move to center pos

        float sinangle_x = sin(rotation.x * 0.0174532925);
        float cosangle_x = cos(rotation.x * 0.0174532925);
        float sinangle_y = sin(rotation.y * 0.0174532925);
        float cosangle_y = cos(rotation.y * 0.0174532925);
        float sinangle_z = sin(rotation.z * 0.0174532925);
        float cosangle_z = cos(rotation.z * 0.0174532925);
        
        for(int i = 0; i < 8; i++)
        {
            float x = vertices[i].x * (cosangle_y * cosangle_z) + vertices[i].y * (cosangle_z * sinangle_x * sinangle_y - cosangle_x * sinangle_z) + vertices[i].z * (cosangle_x * cosangle_z * sinangle_y + sinangle_x * sinangle_z);
            float y = vertices[i].x * (cosangle_y * sinangle_z) + vertices[i].y * (cosangle_x * cosangle_z + sinangle_x * sinangle_y * sinangle_z) + vertices[i].z * (-cosangle_z * sinangle_x + cosangle_x * sinangle_y * sinangle_z);
            float z = vertices[i].x * (-sinangle_y) + vertices[i].y * (cosangle_y * sinangle_x) + vertices[i].z * (cosangle_x * cosangle_y);
            vertices[i].x = x + center.x;
            vertices[i].y = y + center.y;
            vertices[i].z = z + center.z;
        }

        polygon_buffer[i].vertice1 = vertices[0];
        polygon_buffer[i].vertice2 = vertices[2];
        polygon_buffer[i].vertice3 = vertices[1];
        polygon_buffer[i].color = color_arr[0];
        i++;
        polygon_buffer[i].vertice1 = vertices[0];
        polygon_buffer[i].vertice2 = vertices[2];
        polygon_buffer[i].vertice3 = vertices[3];
        polygon_buffer[i].color = color_arr[0];
        i++;
        polygon_buffer[i].vertice1 = vertices[4];
        polygon_buffer[i].vertice2 = vertices[6];
        polygon_buffer[i].vertice3 = vertices[5];
        polygon_buffer[i].color = color_arr[1];
        i++;
        polygon_buffer[i].vertice1 = vertices[4];
        polygon_buffer[i].vertice2 = vertices[6];
        polygon_buffer[i].vertice3 = vertices[7];
        polygon_buffer[i].color = color_arr[1];
        i++;
        polygon_buffer[i].vertice1 = vertices[3];
        polygon_buffer[i].vertice2 = vertices[6];
        polygon_buffer[i].vertice3 = vertices[2];
        polygon_buffer[i].color = color_arr[2];
        i++;
        polygon_buffer[i].vertice1 = vertices[3];
        polygon_buffer[i].vertice2 = vertices[6];
        polygon_buffer[i].vertice3 = vertices[7];
        polygon_buffer[i].color = color_arr[2];
        i++;
        polygon_buffer[i].vertice1 = vertices[2];
        polygon_buffer[i].vertice2 = vertices[5];
        polygon_buffer[i].vertice3 = vertices[6];
        polygon_buffer[i].color = color_arr[3];
        i++;
        polygon_buffer[i].vertice1 = vertices[2];
        polygon_buffer[i].vertice2 = vertices[5];
        polygon_buffer[i].vertice3 = vertices[1];
        polygon_buffer[i].color = color_arr[3];
        i++;
        polygon_buffer[i].vertice1 = vertices[1];
        polygon_buffer[i].vertice2 = vertices[0];
        polygon_buffer[i].vertice3 = vertices[4];
        polygon_buffer[i].color = color_arr[4];
        i++;
        polygon_buffer[i].vertice1 = vertices[1];
        polygon_buffer[i].vertice2 = vertices[4];
        polygon_buffer[i].vertice3 = vertices[5];
        polygon_buffer[i].color = color_arr[4];
        i++;
        polygon_buffer[i].vertice1 = vertices[0];
        polygon_buffer[i].vertice2 = vertices[7];
        polygon_buffer[i].vertice3 = vertices[3];
        polygon_buffer[i].color = color_arr[5];
        i++;
        polygon_buffer[i].vertice1 = vertices[0];
        polygon_buffer[i].vertice2 = vertices[7];
        polygon_buffer[i].vertice3 = vertices[4];
        polygon_buffer[i].color = color_arr[5];
    }
}

Camera::Camera()
{
    reset();
}
Camera::~Camera()
{
    
}
void Camera::reset()
{
    frameheight = 64;
    framewidth = 96;
    zoomlevel = 60;
    center.x = 0;
    center.y = 0;
    center.z = 0;
    rotation.x = 0;
    rotation.y = 0;
    rotation.z = 0;
}
void Camera::resolution(int width, int height)
{
    framewidth = width;
    frameheight = height;
}
void Camera::zoom(float zoom)
{
    zoomlevel = zoom;
}
void Camera::rotate(vector rotate)
{
    rotation.x += rotate.x;
    rotation.y += rotate.y;
    rotation.z += rotate.z;
}
void Camera::move(vector move)
{
    center.x += move.x;
    center.y += move.y;
    center.z += move.z;
}
void Camera::render(uint8_t *output)
{
    gfx_2d_clear();


    float a[polygon_buffer_next_entry];
    int b[polygon_buffer_next_entry];
    
    for(int i = 0; i < polygon_buffer_next_entry; i++)
    {
        float sinangle_x = sin(rotation.x * 0.0174532925);
        float cosangle_x = cos(rotation.x * 0.0174532925);
        float sinangle_y = sin(rotation.y * 0.0174532925);
        float cosangle_y = cos(rotation.y * 0.0174532925);
        float sinangle_z = sin(rotation.z * 0.0174532925);
        float cosangle_z = cos(rotation.z * 0.0174532925);

        vertice vertices[3];
        vertices[0] = polygon_buffer[i].vertice1;
        vertices[1] = polygon_buffer[i].vertice2;
        vertices[2] = polygon_buffer[i].vertice3;
        for(int j = 0; j < 3; j++)
        {
            float x = vertices[j].x * (cosangle_y * cosangle_z) + vertices[j].y * (cosangle_z * sinangle_x * sinangle_y - cosangle_x * sinangle_z) + vertices[j].z * (cosangle_x * cosangle_z * sinangle_y + sinangle_x * sinangle_z);
            float y = vertices[j].x * (cosangle_y * sinangle_z) + vertices[j].y * (cosangle_x * cosangle_z + sinangle_x * sinangle_y * sinangle_z) + vertices[j].z * (-cosangle_z * sinangle_x + cosangle_x * sinangle_y * sinangle_z);
            float z = vertices[j].x * (-sinangle_y) + vertices[j].y * (cosangle_y * sinangle_x) + vertices[j].z * (cosangle_x * cosangle_y);
            vertices[j].x = x - center.x;
            vertices[j].y = y - center.y;
            vertices[j].z = z - center.z;
        }
        polygon_buffer[i].vertice1 = vertices[0];
        polygon_buffer[i].vertice2 = vertices[1];
        polygon_buffer[i].vertice3 = vertices[2];
    }
    

    for(int i = 0; i < polygon_buffer_next_entry; i++)
    {
        a[i] = polygon_buffer[i].vertice1.z;
        a[i] += polygon_buffer[i].vertice2.z;
        a[i] += polygon_buffer[i].vertice3.z;
    }
    for(int i = 0; i < polygon_buffer_next_entry; i++)
    {
        b[i] = i;
    }
    BubbleSort(a,b,polygon_buffer_next_entry);
    
    for(int i = 0; i < polygon_buffer_next_entry; i++)
    {
        drawpolygon(polygon_buffer[b[i]], zoomlevel, framewidth, frameheight);
    }
}



void gfx3dsetup()
{
    
    vector vector1 = {0,0,-500};
    vector vector2 = {100,100,100};
    for(int i = 0; i < 2; i++)
    {
        cube[i].move(vector1);
        cube[i].resize(vector2);
        cube[i].show();
    }
}


void gfx3dperiodic()
{
    //clear zbuffer

    if(cnt <= 0 | cnt > 100)
    {
        cnt = 100;
        for(int i = 0; i < cubecount; i++)
        {
             rotation[i].x = rand() % 10;
             rotation[i].y = rand() % 10;
             rotation[i].z = rand() % 10;
             cube[i].dimension.x = rand() % 50 + 50;
             cube[i].dimension.y = rand() % 50 + 50;
             cube[i].dimension.z = rand() % 50 + 50;
             cube[i].center.z = rand() % 500 - 1000;
             cube[i].center.x = rand() % 200 - 100;
             cube[i].center.y = rand() % 200 - 100;

             uint8_t temp = rand() % 200;
             cube[i].color(temp);
             //cube[i].color_edge(1);

        }
    }
    for(int i = 0; i < cubecount; i++)
    {
        cube[i].rotate(rotation[i]);
        cube[i].update();
    }
    uint8_t x;

    cam1.render(&x);
    cnt --;
}