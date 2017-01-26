#ifndef VARIABLES
#define VARIABLES
#include "headers.cpp"

//////  Variable Declerations

GLUI_Panel *panelroom, *panelindoor, *panel1;
GLUI *glui_phase2, *glui, *glui_phases, *glui_phase3;
GLUI_EditText *texture_panel1,*texture_panel2;
GLuint  list1;

char    texture_name[sizeof(GLUI_String)],tex_str[sizeof(GLUI_String)],wall_top_texture[sizeof(GLUI_String)],tex2_str[sizeof(GLUI_String)];
char    str_phase[2];
int 	bdown_x, bdown_y, mouse_x, mouse_y, timestamp, phase=0;
int   	phase1_window,phase2_window,phase3_window;
int   	width=700,height=600;
int     state=1, merge_status=0;
int		rotate_value=0;
int		translate_value=0;
int     translate_value4poly=0;
float	scale_value=1.0;
float   red_value=1.0, green_value=0.5, blue_value=0.0;
int		trans_type=0;
int 	grid_size=10, show_grid;
int     fur_color,fur_type;
char    status_text[100], letter[20];
GLfloat angle=90,ratio=((float) width)/height, dnear=1,dfar=5000;
GLfloat xx0=width/2,yy0=height/2,zz0=80,xref=width/2+5,yref=height/2,zref=80,vx=0,vy=0,vz=1;
GLfloat walkDir=0.0, walkDirV=0.0, freeMode=0;
int     wall_width=15,wall_height=150;
GLfloat uzunluk;
int		inside=0;
GLfloat light0x=100.0,light0y=100.0,light0z=100.0,light1x=-380.0,light1y=263.0,light1z=80.0,light2x=-400.0,light2y=400.0,light2z=360.0;
GLfloat atten0_cons=2.0,atten0_lin=1.0,atten0_quad=0.5,atten1_cons=2.0,atten1_lin=0.4,atten1_quad=0.0,atten2_cons=0.5,atten2_lin=0.0,atten2_quad=0.0;
GLfloat spot_angle=15.0, spot_exp=2.0, spot_x=0.6, spot_y=-0.9, spot_z=-1.0;
GLfloat amb0_r=0.3,amb0_g=0.3,amb0_b=0.3,amb1_r=0.8,amb1_g=0.8,amb1_b=0.0,amb2_r=0.5,amb2_g=0.2,amb2_b=1.0;
GLfloat dif0_r=0.3,dif0_g=0.3,dif0_b=0.3,dif1_r=0.8,dif1_g=0.8,dif1_b=0.0,dif2_r=0.5,dif2_g=0.2,dif2_b=1.0;
GLfloat tex1_x1=0.5,tex1_x2=1.0,tex1_y1=1.0,tex1_y2=0.5,tex2_x1=0.5,tex2_x2=1.0,tex2_y1=1.0,tex2_y2=0.5;
int mouseX, mouseY;
GLdouble minx, miny, maxx, maxy;

GLfloat xyzRotationAngle = 5.0f;
Object3DS *CurrentModel;
char fileName1[20],fileName2[20],fileName3[20];
GLfloat sc1,sc2,sc3,model1x,model1y,model1z,model2x,model2y,model2z,model3x,model3y,model3z; 
Object3DS model01, model02, model03;
GLfloat light_width=10;
GLfloat shine = 100.0f;
GLfloat xRotation,yRotation,zRotation;
int model_num=0,model_dir=0,cati_goster=1;
GLfloat rotx0=90,roty0=0,rotz0=0,rotx1=90,roty1=0,rotz1=0,rotx2=90,roty2=0,rotz2=0;


struct vertex { GLdouble coord[3]; };
struct vertex origin, bdown, mouse;
struct vertex status_poly[4];

struct fur { 
  int type;
  vector<struct vertex> polygon;
  GLfloat color[3];
  char letter;
} new_fur;

struct wall {
       vector<struct vertex> points;
       int parent;      
} new_wall;

struct wall3D {
       struct vertex points[8];
}new_3d_wall;

vector<struct wall> walls(0);
vector<struct wall3D> walls3D(0);
vector<struct wall3D> doors3D(0);
vector<int> doors3DAngle(0);
vector<struct wall3D> windows3D(0);
vector<struct wall> doors(0);  
vector<struct wall> windows(0);

vector<struct vertex> my_poly(4);
vector<struct vertex> *holding_object;
vector<struct vertex> my_rect(4);
vector<struct vertex> new_poly(4);
vector<struct fur> furnitures(0);


#endif
