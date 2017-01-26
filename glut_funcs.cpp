// Special GLUT Functions

#ifndef GLUTFUNCS
#define GLUTFUNCS
#include "helpers.cpp"
#include "BMPLoader.h"

// Prototypes - According to their order
void 	phase1GlutDisplay(void);
void 	phase1GlutMotion(int x, int y);
void 	phase1GlutMouse(int button, int button_state, int x, int y );
void 	phase1GlutIdle(void);
void 	phase1GlutKeyboard(unsigned char Key, int x, int y);

void 	phase2GlutDisplay(void);
void 	phase2GlutMotion(int x, int y);
void 	phase2GlutMouse(int button, int button_state, int x, int y );
void 	phase2GlutIdle(void);
void 	phase2GlutKeyboard(unsigned char Key, int x, int y);

void 	phase3GlutDisplay(void);
void 	phase3GlutMotion(int x, int y);
void 	phase3GlutMouse(int button, int button_state, int x, int y );
void 	phase3GlutIdle(void);
void 	phase3GlutKeyboard(unsigned char Key, int x, int y);



/***************************************** myGlutDisplay() *****************/
void phase1GlutDisplay( void )
{
int i, j, c, d;  
GLdouble a,b;
struct vertex den, int_point, t;
  
   
timestamp++;  
glClearColor( 0.9f, 0.9f, 0.9f, 1.0f );
glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );

list1=renderPolygon();
glCallList(list1);

// Draw rectangle
glColor4f( 0.0, 0.4, 0.8, (sin(timestamp/40.0)+3)*0.2);
glBegin(GL_POLYGON);
for (i=0;i<4;i++)
   		glVertex3dv(my_rect[i].coord);  
glEnd();
glColor4f( 0.5, 0.5, 0.5, 1.0 );
   		

// Draw Walls
glColor4f(0.0, 0.0, 0.0, 1.0);
for(i=0; i<walls.size(); i++) 
        drawThickLine(walls[i].points[0], walls[i].points[1], WALL_SIZE);
glColor4f(0.8, 0.7, 0.7, 1.0);
for(i=0; i<walls.size(); i++) 
        drawThickLine(walls[i].points[0], walls[i].points[1], WALL_SIZE-1);

// Draw Doors
glColor4f(0.0, 0.0, 0.0, 1.0);
for(i=0; i<doors.size(); i++) 
        drawThickLine(doors[i].points[0], doors[i].points[1], WALL_SIZE);
glColor4f(0.6, 0.3, 0.2, 1.0);
for(i=0; i<doors.size(); i++) 
        drawThickLine(doors[i].points[0], doors[i].points[1], WALL_SIZE-1);

// Draw Windows
glColor4f(0.0, 0.0, 0.0, 1.0);
for(i=0; i<windows.size(); i++) 
        drawThickLine(windows[i].points[0], windows[i].points[1], WALL_SIZE);
glColor4f(0.3, 0.7, 1.0, 1.0);
for(i=0; i<windows.size(); i++) 
        drawThickLine(windows[i].points[0], windows[i].points[1], WALL_SIZE-1);

char str[2];
str[1]=0;

for (i=0;i<furnitures.size();i++)
{
glColor4f(furnitures[i].color[0], furnitures[i].color[1], furnitures[i].color[2], 1.0);
str[0]=furnitures[i].letter;
    glBegin(GL_POLYGON);
    a=b=0;
    for (j=0;j<furnitures[i].polygon.size();j++) {
        glVertex3dv(furnitures[i].polygon[j].coord);  
        a+=furnitures[i].polygon[j].coord[0];
        b+=furnitures[i].polygon[j].coord[1];
    }
    a/=furnitures[i].polygon.size();
    b/=furnitures[i].polygon.size();
    glEnd();

    glColor4f(1.0-furnitures[i].color[0], 1.0-furnitures[i].color[1], 1.0-furnitures[i].color[2], 1.0);
    RenderText((int)a, (int)b+4, str);         
}

if(new_fur.polygon.size()) {
glColor4f(new_fur.color[0], new_fur.color[1], new_fur.color[2], 1.0);
str[0]=new_fur.letter;
    glBegin(GL_POLYGON);
    a=b=0;
    for (j=0;j<new_fur.polygon.size();j++) {
        glVertex3dv(new_fur.polygon[j].coord);  
        a+=new_fur.polygon[j].coord[0];
        b+=new_fur.polygon[j].coord[1];
    }
    a/=new_fur.polygon.size();
    b/=new_fur.polygon.size();
    glEnd();

    glColor4f(1.0-new_fur.color[0], 1.0-new_fur.color[1], 1.0-new_fur.color[2], 1.0);
    RenderText((int)a, (int)b+4, str);         
    
}

if(state==11 || state==12 || state==13) // Insert Wall
{
  glColor4f(0.3, 0.2, 0.2, (sin(timestamp/40.0)+2)*0.05);
  if(state==11)
    drawThickLine(bdown, mouse, WALL_SIZE);
  if(new_wall.points.size()>=2) {
    glColor4f(0.0, 0.0, 0.0, (sin(timestamp/40.0)+2)*0.5);
    drawThickLine(new_wall.points[0], new_wall.points[1], WALL_SIZE);
    glColor4f(1.0, 0.5, 0.0, (sin(timestamp/40.0)+2)*0.5);
    drawThickLine(new_wall.points[0], new_wall.points[1], WALL_SIZE-1);
  }  
}


// Draw Grid
if(show_grid) {
glColor4f(0.0, 0.0, 0.0, 0.3);
for(i=grid_size-1; i<width; i+=grid_size) 
                   drawLine(i, 0, i, height);
for(i=grid_size-1; i<height; i+=grid_size) 
                   drawLine(0, i, width, i);
}

glFlush();
glutSwapBuffers(); 
}




void phase1GlutMotion(int x, int y )
{
int i, a, b;
struct vertex int_point;
vector<struct vertex> tmp(4);

if(state!=3) {
my_rect[0].coord[0]=min(x, bdown_x);   
my_rect[0].coord[1]=min(y, bdown_y);            
my_rect[1].coord[0]=max(x, bdown_x);            
my_rect[1].coord[1]=min(y, bdown_y);            
my_rect[2].coord[0]=max(x, bdown_x);            
my_rect[2].coord[1]=max(y, bdown_y);            
my_rect[3].coord[0]=min(x, bdown_x);            
my_rect[3].coord[1]=max(y, bdown_y);   
}

mouse_x=x;
mouse_y=y;

mouse.coord[0]=x;
mouse.coord[1]=y;
mouse.coord[2]=0;

if(state==11) {
  new_wall.points.clear();
  for(i=0; i<walls.size(); i++) {
    if(lineIntersect(walls[i].points[0], walls[i].points[1], mouse, bdown, &int_point))
      new_wall.points.push_back(int_point);
  }
  doDelete();
}
else if (state==15 ) // Move Furniture
{
  for(i=0; i<holding_object->size(); i++)       {         
           (*holding_object)[i].coord[0]+=x-bdown_x;
           (*holding_object)[i].coord[1]+=y-bdown_y;
  }
  if(intersected()) 
    for(i=0; i<holding_object->size(); i++)       {         
             (*holding_object)[i].coord[0]-=x-bdown_x;
             (*holding_object)[i].coord[1]-=y-bdown_y;
    }
  bdown_x=x;
  bdown_y=y;
  doDelete();
 
}   

else if(state==12 || state==13) {
   for(i=0; i<walls.size(); i++) {
    new_wall.points.clear();
    for(a=0; a<4; a++) {
             b=(a+1)%4;
             if(lineIntersect(walls[i].points[0], walls[i].points[1], my_rect[a], my_rect[b], &int_point)) {
                   new_wall.points.push_back(int_point);
                   new_wall.parent=i;
             }
    }
    if(new_wall.points.size()>0) break;
  }
}

else if (state==14)
{
    new_fur.letter=letter[0];
    new_fur.type=fur_type;
    
    new_fur.color[0]=red_value;
    new_fur.color[1]=green_value;
    new_fur.color[2]=blue_value;
    createPoly(bdown, mouse);
    doDelete();
}


else if (state==1)
   {
   my_poly=my_rect;
    purgePolygon();
    doDelete();
  }
   
else if (state==2 ) // Draw rectangle for merge
   {
   }

else if (state==3 ) // Move Polygon
{
  for(i=0; i<holding_object->size(); i++)       {         
           (*holding_object)[i].coord[0]+=x-bdown_x;
           (*holding_object)[i].coord[1]+=y-bdown_y;
  }
  bdown_x=x;
  bdown_y=y;
  purgePolygon();
}   
else doDelete();

  glutPostRedisplay(); 
}




void phase1GlutMouse(int button, int button_state, int x, int y )
{
int i;

bdown.coord[0]=x;
bdown.coord[1]=y;
bdown.coord[2]=0;
mouse=bdown;

bdown_x=x; bdown_y=y;

  if (trans_type==3 && button == GLUT_LEFT_BUTTON && button_state == GLUT_DOWN)
  {
  float tr_x=x-my_rect[i].coord[0],tr_y=y-my_rect[i].coord[1];
  for (i=0;i<4;i++)
		{
		my_rect[i].coord[0] = my_rect[i].coord[0] + tr_x;
		my_rect[i].coord[1] = my_rect[i].coord[1] + tr_y;
		}
	trans_type=0;                  
  }

  if ( button == GLUT_LEFT_BUTTON && button_state == GLUT_DOWN && state==0) {
       if(insidePoly(bdown, my_poly)) { state=3; holding_object=&my_poly; }
       if(insidePoly(bdown, my_rect)) { state=3; holding_object=&my_rect; }
     }

  if (button==GLUT_LEFT_BUTTON && button_state==GLUT_UP && state<10)
  {
    state=0;
  }

  if (button==GLUT_LEFT_BUTTON && button_state==GLUT_UP && state==11) {
    state=10;
    if(new_wall.points.size()>1) walls.push_back(new_wall);
    new_wall.points.clear();
  }

  if (button==GLUT_LEFT_BUTTON && button_state==GLUT_UP && state==12) {
    state=10;
    if(new_wall.points.size()>1) doors.push_back(new_wall);
    new_wall.points.clear();
    doDelete();
  }

  if (button==GLUT_LEFT_BUTTON && button_state==GLUT_UP && state==13) {
    state=10;
    if(new_wall.points.size()>1) windows.push_back(new_wall);
    new_wall.points.clear();
    doDelete();
  }

  if (button==GLUT_LEFT_BUTTON && button_state==GLUT_UP && state==14) {
    state=10;
    furnitures.push_back(new_fur);
    new_fur.polygon.clear();
    doDelete();
  }
                               
  if ( button == GLUT_LEFT_BUTTON && button_state == GLUT_DOWN && state==10) {
       for(i=0; i<furnitures.size(); i++) 
            if(insidePoly(bdown, furnitures[i].polygon)) 
            { state=15; holding_object=&furnitures[i].polygon; }
     }
  if (button==GLUT_LEFT_BUTTON && button_state==GLUT_UP && state>=10)
  {
    state=10;
  }

glutPostRedisplay(); 
}




void phase1GlutIdle( void )
{
    if ( glutGetWindow() != phase1_window) 
    glutSetWindow(phase1_window);  
   glutPostRedisplay();
}




void phase1GlutKeyboard(unsigned char Key, int x, int y)
{
  switch(Key)
  {
  case 27: 
  case 'q':
    exit(0);
    break;
  };
  
  glutPostRedisplay();
}



//////////////////////
// Phase 2 //////////
/////////////////////

void phase2GlutDisplay( void )
{
int i,wall_size;
glClearColor( 0.9f, 0.9f, 0.9f, 1.0f );
glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );

/*
glColor3f(1.0,0.5,0.0);
glBegin(GL_QUADS);
glVertex3f(-90,-90,0);
glVertex3f(-90,700,0);
glVertex3f(800,700,0);
glVertex3f(800,-90,0);
glEnd();     
*/


// Draw Walls
wall_size=walls.size();

for(i=0; i<wall_size; i++) 
         {
         drawWall(walls[i].points[0],walls[i].points[1],wall_width,wall_height,i);
         }


  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
  gluLookAt(xx0, yy0, zz0, xref, yref, zref, vx, vy, vz);   

if (inside)
{
zz0=-5; vx=0; vy=0; vz=-1;
}

glFlush();
glutSwapBuffers(); 
glutPostRedisplay(); 
}





void phase2GlutMotion(int x, int y )
{


glutPostRedisplay(); 
}




void phase2GlutMouse(int button, int button_state, int x, int y )
{
glutPostRedisplay(); 
}




void phase2GlutIdle( void )
{ 
 if ( glutGetWindow() != phase2_window) 
    glutSetWindow(phase2_window);  

glutPostRedisplay();
}




void phase2GlutKeyboard(unsigned char Key, int x, int y)
{
  switch(Key)
  {
  case 'e':
    xx0=xx0+5;
    break;
  case 'd':
    xx0=xx0-5;
    break;
  case 'r':
    yy0=yy0+5;
    break;
  case 'f':
    yy0=yy0-5;
    break;
  case 't':
    zz0=zz0+5;
    break;
  case 'g':
    zz0=zz0-5;
    break;
  case 'z':
    xref=xref+5;
    break;
  case 'x':
    xref=xref-5;
    break;
  case 'c':
    yref=yref+5;
    break;
  case 'v':
    yref=yref-5;
    break;
  case 'b':
    zref=zref+5;
    break;
  case 'n':
    zref=zref-5;
    break;
  };  
glutPostRedisplay();
}



//////////////////////
// Phase 3 //////////
/////////////////////


void phase3GlutDisplay( void )
{
int wall_size,i;
wall_size=walls3D.size();

glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
   
enlightMe();
showLightSources();
glColor3f(1.0,1.0,1.0);

BMPClass bmp2;
BMPLoad(texture_name,bmp2);
	
	glEnable(GL_TEXTURE_2D);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
	glTexImage2D(GL_TEXTURE_2D,0,3,bmp2.width,bmp2.height,0,GL_RGB,GL_UNSIGNED_BYTE,bmp2.bytes);

for (i=0;i<wall_size;i++)
{
// Yanal Alanlar
glBegin(GL_QUADS);
glTexCoord2f(tex1_x1,tex1_y1);	glVertex3dv(walls3D[i].points[0].coord);
glTexCoord2f(tex1_x2,tex1_y1);	glVertex3dv(walls3D[i].points[3].coord);
glTexCoord2f(tex1_x2,tex1_y2);	glVertex3dv(walls3D[i].points[7].coord);
glTexCoord2f(tex1_x1,tex1_y2);	glVertex3dv(walls3D[i].points[4].coord);
glEnd();      
glBegin(GL_QUADS);
glTexCoord2f(tex1_x1,tex1_y1);	glVertex3dv(walls3D[i].points[1].coord);
glTexCoord2f(tex1_x2,tex1_y1);	glVertex3dv(walls3D[i].points[2].coord);
glTexCoord2f(tex1_x2,tex1_y2);	glVertex3dv(walls3D[i].points[6].coord);
glTexCoord2f(tex1_x1,tex1_y2);	glVertex3dv(walls3D[i].points[5].coord);
glEnd();      

// Duvar genisliginin yandan goruntulenmesi
glBegin(GL_QUADS);
glTexCoord2f(tex1_x1,tex1_y1);	glVertex3dv(walls3D[i].points[0].coord);
glTexCoord2f(tex1_x2,tex1_y1);	glVertex3dv(walls3D[i].points[1].coord);
glTexCoord2f(tex1_x2,tex1_y2);	glVertex3dv(walls3D[i].points[5].coord);
glTexCoord2f(tex1_x1,tex1_y2);	glVertex3dv(walls3D[i].points[4].coord);
glEnd();
glBegin(GL_QUADS);
glTexCoord2f(tex1_x1,tex1_y1);	glVertex3dv(walls3D[i].points[2].coord);
glTexCoord2f(tex1_x2,tex1_y1);	glVertex3dv(walls3D[i].points[3].coord);
glTexCoord2f(tex1_x2,tex1_y2);	glVertex3dv(walls3D[i].points[7].coord);
glTexCoord2f(tex1_x1,tex1_y2);	glVertex3dv(walls3D[i].points[6].coord);
glEnd();    
}
glDisable(GL_TEXTURE_2D);


// Cati
if (cati_goster) {
BMPClass bmp8;
BMPLoad(wall_top_texture,bmp8);
	
glEnable(GL_TEXTURE_2D);
glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
glTexImage2D(GL_TEXTURE_2D,0,3,bmp8.width,bmp8.height,0,GL_RGB,GL_UNSIGNED_BYTE,bmp8.bytes);

glBegin(GL_TRIANGLES);
glTexCoord2f(tex1_x1,tex1_y1);	glVertex3d(minx, miny, wall_height);
glTexCoord2f(tex1_x2,tex1_y1);	glVertex3d(minx, maxy, wall_height);
glTexCoord2f(tex1_x2,tex1_y2);	glVertex3d(minx+50, (maxy+miny)/2, wall_height+100);
glEnd();      
glBegin(GL_TRIANGLES);
glTexCoord2f(tex1_x1,tex1_y1);	glVertex3d(maxx, miny, wall_height);
glTexCoord2f(tex1_x2,tex1_y1);	glVertex3d(maxx, maxy, wall_height);
glTexCoord2f(tex1_x2,tex1_y2);	glVertex3d(maxx-50, (maxy+miny)/2, wall_height+100);
glEnd();      
glBegin(GL_QUADS);
glTexCoord2f(tex1_x1,tex1_y1);	glVertex3d(minx, miny, wall_height);
glTexCoord2f(tex1_x2,tex1_y1);	glVertex3d(maxx, miny, wall_height);
glTexCoord2f(tex1_x2,tex1_y2);	glVertex3d(maxx-50, (maxy+miny)/2, wall_height+100);
glTexCoord2f(tex1_x1,tex1_y2);	glVertex3d(minx+50, (maxy+miny)/2, wall_height+100);
glEnd();      
glBegin(GL_QUADS);
glTexCoord2f(tex1_x1,tex1_y1);	glVertex3d(minx, maxy, wall_height);
glTexCoord2f(tex1_x2,tex1_y1);	glVertex3d(maxx, maxy, wall_height);
glTexCoord2f(tex1_x2,tex1_y2);	glVertex3d(maxx-50, (maxy+miny)/2, wall_height+100);
glTexCoord2f(tex1_x1,tex1_y2);	glVertex3d(minx+50, (maxy+miny)/2, wall_height+100);
glEnd();      
glBegin(GL_QUADS);
glTexCoord2f(tex1_x1,tex1_y1);	glVertex3d(minx, miny, wall_height);
glTexCoord2f(tex1_x2,tex1_y1);	glVertex3d(minx, maxy, wall_height);
glTexCoord2f(tex1_x2,tex1_y2);	glVertex3d(maxx, maxy, wall_height);
glTexCoord2f(tex1_x1,tex1_y2);	glVertex3d(maxx, miny, wall_height);
glEnd();      

glDisable(GL_TEXTURE_2D);
}

// Zemin

BMPClass bmp9;
BMPLoad("zemin.bmp",bmp9);
	
glEnable(GL_TEXTURE_2D);
glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
glTexImage2D(GL_TEXTURE_2D,0,3,bmp9.width,bmp9.height,0,GL_RGB,GL_UNSIGNED_BYTE,bmp9.bytes);

glBegin(GL_QUADS);
glTexCoord2f(0.1,0.9);	glVertex3d(-1000, -1000, 0);
glTexCoord2f(0.1,0.1);	glVertex3d(-1000,  1000, 0);
glTexCoord2f(0.9,0.1);	glVertex3d( 1000,  1000, 0);
glTexCoord2f(0.9,0.9);	glVertex3d( 1000, -1000, 0);
glEnd();      

glDisable(GL_TEXTURE_2D);




BMPClass bmp6;
BMPLoad("door.bmp",bmp6);
	
	glEnable(GL_TEXTURE_2D);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
	glTexImage2D(GL_TEXTURE_2D,0,3,bmp6.width,bmp6.height,0,GL_RGB,GL_UNSIGNED_BYTE,bmp6.bytes);

int t;
for (i=0;i<doors3D.size();i++)
{
// DOORS
glBegin(GL_QUADS);
glTexCoord2f(tex1_x1,tex1_y1);	glVertex3dv(doors3D[i].points[0].coord);
glTexCoord2f(tex1_x2,tex1_y1);	glVertex3dv(doors3D[i].points[3].coord);
glTexCoord2f(tex1_x2,tex1_y2);	glVertex3dv(doors3D[i].points[7].coord);
glTexCoord2f(tex1_x1,tex1_y2);	glVertex3dv(doors3D[i].points[4].coord);
glEnd();      
glBegin(GL_QUADS);
glTexCoord2f(tex1_x1,tex1_y1);	glVertex3dv(doors3D[i].points[1].coord);
glTexCoord2f(tex1_x2,tex1_y1);	glVertex3dv(doors3D[i].points[2].coord);
glTexCoord2f(tex1_x2,tex1_y2);	glVertex3dv(doors3D[i].points[6].coord);
glTexCoord2f(tex1_x1,tex1_y2);	glVertex3dv(doors3D[i].points[5].coord);
glEnd();      

glBegin(GL_QUADS);
glTexCoord2f(tex1_x1,tex1_y1);	glVertex3dv(doors3D[i].points[0].coord);
glTexCoord2f(tex1_x2,tex1_y1);	glVertex3dv(doors3D[i].points[1].coord);
glTexCoord2f(tex1_x2,tex1_y2);	glVertex3dv(doors3D[i].points[5].coord);
glTexCoord2f(tex1_x1,tex1_y2);	glVertex3dv(doors3D[i].points[4].coord);
glEnd();
glBegin(GL_QUADS);
glTexCoord2f(tex1_x1,tex1_y1);	glVertex3dv(doors3D[i].points[2].coord);
glTexCoord2f(tex1_x2,tex1_y1);	glVertex3dv(doors3D[i].points[3].coord);
glTexCoord2f(tex1_x2,tex1_y2);	glVertex3dv(doors3D[i].points[7].coord);
glTexCoord2f(tex1_x1,tex1_y2);	glVertex3dv(doors3D[i].points[6].coord);
glEnd();    
glBegin(GL_QUADS);
glTexCoord2f(tex2_x1,tex2_y1);  glVertex3dv(doors3D[i].points[4].coord);
glTexCoord2f(tex2_x2,tex2_y1);  glVertex3dv(doors3D[i].points[5].coord);
glTexCoord2f(tex2_x2,tex2_y2);	glVertex3dv(doors3D[i].points[6].coord);
glTexCoord2f(tex2_x1,tex2_y2);	glVertex3dv(doors3D[i].points[7].coord);
glEnd();   

}
glDisable(GL_TEXTURE_2D);






BMPClass bmp;
BMPLoad(wall_top_texture,bmp);
	glEnable(GL_TEXTURE_2D);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
	glTexImage2D(GL_TEXTURE_2D,0,3,bmp.width,bmp.height,0,GL_RGB,GL_UNSIGNED_BYTE,bmp.bytes);

for (i=0;i<wall_size;i++)
{
// Ust ve Alt Alanlar
glBegin(GL_QUADS);
glTexCoord2f(tex2_x1,tex2_y1);  glVertex3dv(walls3D[i].points[4].coord);
glTexCoord2f(tex2_x2,tex2_y1);  glVertex3dv(walls3D[i].points[5].coord);
glTexCoord2f(tex2_x2,tex2_y2);	glVertex3dv(walls3D[i].points[6].coord);
glTexCoord2f(tex2_x1,tex2_y2);	glVertex3dv(walls3D[i].points[7].coord);
glEnd();   
glBegin(GL_QUADS);
glTexCoord2f(tex2_x1,tex2_y1);  glVertex3dv(walls3D[i].points[0].coord);
glTexCoord2f(tex2_x2,tex2_y1);  glVertex3dv(walls3D[i].points[1].coord);
glTexCoord2f(tex2_x2,tex2_y2);	glVertex3dv(walls3D[i].points[2].coord);
glTexCoord2f(tex2_x1,tex2_y2);	glVertex3dv(walls3D[i].points[3].coord);
glEnd();   

}

glDisable(GL_TEXTURE_2D);




// 3D Model - 1
CurrentModel = &model01;
BMPClass bmp3;
BMPLoad("pleaf.bmp",bmp3);
	
	glEnable(GL_TEXTURE_2D);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
	glTexImage2D(GL_TEXTURE_2D,0,3,bmp3.width,bmp3.height,0,GL_RGB,GL_UNSIGNED_BYTE,bmp3.bytes);

glDisable(GL_TEXTURE_2D);

glEnable(GL_CULL_FACE);
DrawModel();
glDisable(GL_CULL_FACE);


// 3D Model - 2
CurrentModel = &model02;
BMPClass bmp4;
BMPLoad("flower.bmp",bmp4);
	
	glEnable(GL_TEXTURE_2D);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
	glTexImage2D(GL_TEXTURE_2D,0,3,bmp4.width,bmp4.height,0,GL_RGB,GL_UNSIGNED_BYTE,bmp4.bytes);

glDisable(GL_TEXTURE_2D);

glEnable(GL_CULL_FACE);
DrawModel();
glDisable(GL_CULL_FACE);


// 3D Model - 3
CurrentModel = &model03;
BMPClass bmp5;
BMPLoad("hopiin.bmp",bmp5);
	
	glEnable(GL_TEXTURE_2D);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
	glTexImage2D(GL_TEXTURE_2D,0,3,bmp5.width,bmp5.height,0,GL_RGB,GL_UNSIGNED_BYTE,bmp5.bytes);

glDisable(GL_TEXTURE_2D);

glEnable(GL_CULL_FACE);
DrawModel();
glDisable(GL_CULL_FACE);




  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
  gluLookAt(xx0, yy0, zz0, xref, yref, zref, vx, vy, vz);  


glutSwapBuffers();
}




void phase3GlutMotion(int x, int y )
{

glutPostRedisplay(); 
}




void phase3GlutMouse(int button, int button_state, int x, int y )
{

glutPostRedisplay(); 
}




void phase3GlutIdle( void ) {
    updateDoorAngles();   
   if ( glutGetWindow() != phase3_window) 
    glutSetWindow(phase3_window);  

  glutPostRedisplay();
}




void phase3GlutKeyboard(unsigned char Key, int x, int y)
{
  switch(Key)
  {
    case 'w':
         freeMode=1-freeMode;
         if(!freeMode) walkDirV=0;
         updatePosition(0,0,0);
         break;

    case 'c':
         if (cati_goster) cati_goster=0;
         else cati_goster=1;
         break;
         
  case 'e':

        if (model_num==0) 
        {
        CurrentModel = &model01; 
        if (model_dir==0) CurrentModel->Rotate(++rotx0,roty0,rotz0);       
        if (model_dir==1) CurrentModel->Rotate(rotx0,++roty0,rotz0);   
        if (model_dir==2) CurrentModel->Rotate(rotx0,roty0,++rotz0);   
        }

        if (model_num==1) 
        {
        CurrentModel = &model02; 
        if (model_dir==0) CurrentModel->Rotate(++rotx1,roty1,rotz1);       
        if (model_dir==1) CurrentModel->Rotate(rotx1,++roty1,rotz1);   
        if (model_dir==2) CurrentModel->Rotate(rotx1,roty1,++rotz1);   
        }

        if (model_num==2) 
        {
        CurrentModel = &model03; 
        if (model_dir==0) CurrentModel->Rotate(++rotx2,roty2,rotz2);       
        if (model_dir==1) CurrentModel->Rotate(rotx2,++roty2,rotz2);   
        if (model_dir==2) CurrentModel->Rotate(rotx2,roty2,++rotz2);   
        }
   
   break;
  case 'd':

        if (model_num==0) 
        {
        CurrentModel = &model01; 
        if (model_dir==0) CurrentModel->Rotate(--rotx0,roty0,rotz0);       
        if (model_dir==1) CurrentModel->Rotate(rotx0,--roty0,rotz0);   
        if (model_dir==2) CurrentModel->Rotate(rotx0,roty0,--rotz0);   
        }

        if (model_num==1) 
        {
        CurrentModel = &model02; 
        if (model_dir==0) CurrentModel->Rotate(--rotx1,roty1,rotz1);       
        if (model_dir==1) CurrentModel->Rotate(rotx1,--roty1,rotz1);   
        if (model_dir==2) CurrentModel->Rotate(rotx1,roty1,--rotz1);   
        }

        if (model_num==2) 
        {
        CurrentModel = &model03; 
        if (model_dir==0) CurrentModel->Rotate(--rotx2,roty2,rotz2);       
        if (model_dir==1) CurrentModel->Rotate(rotx2,--roty2,rotz2);   
        if (model_dir==2) CurrentModel->Rotate(rotx2,roty2,--rotz2);   
        }

    break;
  case 'r':

        if (model_num==0) 
        {
        CurrentModel = &model01; 
        if (model_dir==0) CurrentModel->SetPosition(model1x++,model1y,model1z);
        if (model_dir==1) CurrentModel->SetPosition(model1x,model1y++,model1z);
        if (model_dir==2) CurrentModel->SetPosition(model1x,model1y,model1z++);
        }
        if (model_num==1) 
        {
        CurrentModel = &model02; 
        if (model_dir==0) CurrentModel->SetPosition(model2x++,model2y,model2z);
        if (model_dir==1) CurrentModel->SetPosition(model2x,model2y++,model2z);
        if (model_dir==2) CurrentModel->SetPosition(model2x,model2y,model2z++);
        }
        if (model_num==2) 
        {
        CurrentModel = &model03; 
        if (model_dir==0) CurrentModel->SetPosition(model3x++,model3y,model3z);
        if (model_dir==1) CurrentModel->SetPosition(model3x,model3y++,model3z);
        if (model_dir==2) CurrentModel->SetPosition(model3x,model3y,model3z++);
        }

    break;
  case 'f':

        if (model_num==0) 
        {
        CurrentModel = &model01; 
        if (model_dir==0) CurrentModel->SetPosition(model1x--,model1y,model1z);
        if (model_dir==1) CurrentModel->SetPosition(model1x,model1y--,model1z);
        if (model_dir==2) CurrentModel->SetPosition(model1x,model1y,model1z--);
        }
        if (model_num==1) 
        {
        CurrentModel = &model02; 
        if (model_dir==0) CurrentModel->SetPosition(model2x--,model2y,model2z);
        if (model_dir==1) CurrentModel->SetPosition(model2x,model2y--,model2z);
        if (model_dir==2) CurrentModel->SetPosition(model2x,model2y,model2z--);
        }
        if (model_num==2) 
        {
        CurrentModel = &model03; 
        if (model_dir==0) CurrentModel->SetPosition(model3x--,model3y,model3z);
        if (model_dir==1) CurrentModel->SetPosition(model3x,model3y--,model3z);
        if (model_dir==2) CurrentModel->SetPosition(model3x,model3y,model3z--);
        }

    break;
  case 't':

        if (model_num==0) 
        {
        CurrentModel = &model01; 
        CurrentModel->SetScalar(sc1+=0.1);       
        }

        if (model_num==1) 
        {
        CurrentModel = &model02; 
        CurrentModel->SetScalar(sc2+=0.1);       
        }

        if (model_num==2) 
        {
        CurrentModel = &model03; 
        CurrentModel->SetScalar(sc3+=0.1);       
        }

    break;
  case 'g':

        if (model_num==0) 
        {
        CurrentModel = &model01; 
        CurrentModel->SetScalar(sc1-=0.1);       
        }

        if (model_num==1) 
        {
        CurrentModel = &model02; 
        CurrentModel->SetScalar(sc2-=0.1);       
        }

        if (model_num==2) 
        {
        CurrentModel = &model03; 
        CurrentModel->SetScalar(sc3-=0.1);       
        }

    break;
  };  
  glutPostRedisplay();
}



#endif
