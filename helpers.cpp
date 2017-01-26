// Helper Functions

#ifndef HELPERS
#define HELPERS
#include "variables.cpp"

//////  PTOTOTYPES

// PICKING
void drawRects(GLenum mode);
void SetupRC();
void KeyboardAction(int key, int x, int y);
void InitModels();
void DrawModel();
void BuildMenu();
void ProcessMenuSelection(int value);
void InitializeLighting();
void printControls();
void RotateCurrentObj(GLfloat x,GLfloat y,GLfloat z);
void SetPositionOfCurrentObj(GLfloat x,GLfloat y,GLfloat z);

void phase3GlutDisplay( void );

void 	CALLBACK tessBeginCB(GLenum which);
void 	CALLBACK tessEndCB();
void 	CALLBACK tessErrorCB(GLenum errorCode);
void 	CALLBACK tessVertexCB(const GLvoid *data);
void 	callDrawPolygon (int value);
void 	callSpinners (int value);
int 	ccw(struct vertex p0, struct vertex p1, struct vertex p2);
void 	changePhase (int value);
void    create3dPoints();
void 	createPoly(vertex a, vertex b);
void 	doDelete();
void 	doInsertRectangle();
void 	doMerge();
void 	doSubtract();
void    drawDoors();
void    drawWindows();
void 	drawLine (GLdouble x1, GLdouble y1, GLdouble x2, GLdouble y2);
void 	drawThickLine(struct vertex v1, struct vertex v2, int size);
void    drawWall(struct vertex v1,struct vertex v2,int wall_width,int wall_height,int which);
void    enlightMe();
void    find8Points(struct vertex v1,struct vertex v2,int wall_width,int h0, int h1,struct wall3D *which);
int 	insidePoly(struct vertex v, vector<struct vertex> &poly);
int 	intersected();
int 	lineIntersect(struct vertex v0,struct vertex v1,struct vertex v2,struct vertex v3,struct vertex *v4);
void    phase1Save();
void    phase1Load();
void    phase2Save();
void    phase2Load();
void    phase3Save();
void    phase3Load();
void 	purgePolygon();
void 	RenderText(int x, int y, char *string);
GLuint 	renderPolygon();
void 	rotateRect(int value);
void 	rotateRect(struct vertex pivot,struct fur *furniture, GLdouble angle);
void 	rotateRect(struct vertex pivot, GLdouble angle, GLint vertex_num);
void    rotateWall(struct vertex pivot,struct wall3D *one_wall, GLdouble angle);
void 	scaleRect(struct vertex pivot, GLfloat sx, GLfloat sy, GLint vertex_num); 
void 	scaleRect(int value);
void 	scaleRect(struct vertex pivot, GLfloat sx, GLfloat sy, struct fur *furniture);
void    showLightSources();
//void 	statusBar(char *str);


//// FUNCTION DEFINITIONS





//Draws the house by calling all necessary sub-functions
void DrawModel() {

	CurrentModel->Render();
}


void openDoor(int k) {
     if(doors3DAngle[k]==0)
       doors3DAngle[k]=1;
}


void closeDoor(int k) {
     if(doors3DAngle[k]==50)
       doors3DAngle[k]=51;
}



void updatePosition(double diffx, double diffy, double diffz) {
     int i, pass=1;
     struct vertex cur, next, bw, fw, t;
     
     if(freeMode==1) {
       xx0+=diffx; 
       yy0+=diffy;
       zz0+=diffz;
       xref=xx0+cos(walkDir)*5;
       yref=yy0+sin(walkDir)*5;
       zref=zz0+sin(walkDirV)*5;
       return; 
       
     }

     
     zref=80; zz0=80;     
     cur.coord[0]=xx0;
     cur.coord[1]=yy0;
     next.coord[0]=xx0+diffx*5;
     next.coord[1]=yy0+diffy*5;
     bw.coord[0]=xx0+cos(walkDir+M_PI)*50;
     bw.coord[1]=yy0+sin(walkDir+M_PI)*50;
     fw.coord[0]=xx0+cos(walkDir)*100;
     fw.coord[1]=yy0+sin(walkDir)*100;
     
     for(i=0; i<doors.size(); i++)
              if(lineIntersect(bw, fw, doors[i].points[0], doors[i].points[1], &t))
              { pass=2; openDoor(i); }
              else closeDoor(i);
     if(pass!=2)
       for(i=0; i<walls.size(); i++)
         if(lineIntersect(cur, next, walls[i].points[0], walls[i].points[1], &t))
           pass=0;
         
     if(pass) { xx0+=diffx; yy0+=diffy; }
     xref=xx0+cos(walkDir)*5;
     yref=yy0+sin(walkDir)*5;
//     printf("%lf %lf\n", xx0, yy0);
}

void GlutPassiveMotion(int x, int y ) {
     walkDir+=(mouseX-x)/100.0;
     if(freeMode) {
       walkDirV+=(mouseY-y)/100.0;
       if(walkDirV> M_PI/2) walkDirV=M_PI/2;
       if(walkDirV< -M_PI/2) walkDirV=-M_PI/2;
     }
     updatePosition(0, 0, 0);
     mouseX=x;
     mouseY=y;
     glutPostRedisplay();
}

void KeyboardAction(int key, int x, int y)
{
	if(key == 27) //i.e. escape character
		exit(0);


   if(key == GLUT_KEY_UP) { 
      updatePosition(cos(walkDir)*5, sin(walkDir)*5, sin(walkDirV)*5);
   }      
   if(key == GLUT_KEY_DOWN) { 
      updatePosition(cos(walkDir+M_PI)*5, sin(walkDir+M_PI)*5, -sin(walkDirV)*5);
   }      
   if(key == GLUT_KEY_LEFT) { 
      updatePosition(cos(walkDir+M_PI/2)*5, sin(walkDir+M_PI/2)*5, 0);
   }      
   if(key == GLUT_KEY_RIGHT) { 
      updatePosition(cos(walkDir-M_PI/2)*5, sin(walkDir-M_PI/2)*5, 0);
   }      
   

	glutPostRedisplay();
}

void BuildMenu() {

	// Create the Menu
	glutAddMenuEntry("Cem Aytar",1);
	glutAddMenuEntry("Yunus Esencayi",2);
	glutAddMenuEntry("Kaan Yasin Ceylan",3);

	glutAttachMenu(GLUT_RIGHT_BUTTON); //attach to right click
}

void ProcessMenuSelection(int value)
{

	
	CurrentModel = &model01; //load red wagon


	//reset the rotations for the newly referenced model
	xRotation = 0.0f;
	yRotation = 0.0f;
	zRotation = 0.0f;

	//reset the rotaiton of the currentmodel to its natural orientation
	CurrentModel->ResetRotation();

	phase3GlutDisplay();
}

//************************************************************************
//**********                                                    **********
//**********             Initialization Functions               **********
//**********                                                    **********
//************************************************************************

// This function does any needed initialization on the rendering
// context.
void SetupRC()
{

	//Default variable values
	CurrentModel = &model01; //default model is the red wagon
	xRotation = 0.0f; //start with no rotations applied
	yRotation = 0.0f; //start with no rotations applied
	zRotation = 0.0f; //start with no rotations applied

	glShadeModel(GL_SMOOTH);

	glEnable(GL_DEPTH_TEST);	// Hidden surface removal
	glFrontFace(GL_CCW);		// Counter clock-wise polygons face out
	//glEnable(GL_CULL_FACE);		// Do not calculate inside of objects

	InitializeLighting();

	// Black background
	glClearColor(0.3, 0.3, 0.3, 1.0); //redundant call for clarity
}
//This funciton INitializes all of the 3DS objects to the respective
	//global Object3DS instance


void setModels(char *fileName,GLfloat sScalar,GLfloat x, GLfloat y,GLfloat z, int which) {
if (which==1)
{
	CurrentModel = &model01;		
	model01.Initialize(fileName);	
	model01.SetScalar(sScalar);		
	model01.SetPosition(x, y, z);	
}
if (which==2)
{
	CurrentModel = &model02;		
	model02.Initialize(fileName);	
	model02.SetScalar(sScalar);		
	model02.SetPosition(x, y, z);
}
if (which==3)
{
	CurrentModel = &model03;		
	model03.Initialize(fileName);	
	model03.SetScalar(sScalar);		
	model03.SetPosition(x, y, z);
	model03.Rotate(90,0,0);
}
}

void RotateCurrentObj(GLfloat x,GLfloat y,GLfloat z)
{
	CurrentModel->Rotate(x,y,z);	//mevcut modeli x,y,z kadar cevir.
}

void SetPositionOfCurrentObj(GLfloat x,GLfloat y,GLfloat z)
{
	CurrentModel->SetPosition(x,y,z);	//mevcut modeli x,y,z koordinatlarina koy.
}


// This funciton initializes all lighting for the VR World
void InitializeLighting() {

enlightMe();

}	





void RenderText(int x, int y, char *string) {
int len, i;
glRasterPos2f(x, y);
len=strlen(string);
for (i = 0; i < len; i++)
	glutBitmapCharacter( GLUT_BITMAP_HELVETICA_12, string[i]);
}

int equivelent(double a, double b) {
    a=a-b;
    if(a<0.0) a=-a;
    if(a<0.05) return 1;
    return 0;
}

int cmp(const void *p1, const void *p2) {
    struct vertex *a=(struct vertex *)p1, *b=(struct vertex *)p2;
    if(!equivelent(a->coord[0], b->coord[0])) return (a->coord[0] > b->coord[0]) - (a->coord[0] < b->coord[0]);
    if(!equivelent(a->coord[1], b->coord[1])) return (a->coord[1] > b->coord[1]) - (a->coord[1] < b->coord[1]);
    if(!equivelent(a->coord[2], b->coord[2])) return (a->coord[2] > b->coord[2]) - (a->coord[2] < b->coord[2]);
    return 0;
}

void create3dPoints() {
int wall_size,i,j,k,t=0, door_number,window_number;
struct vertex liste[20];
wall_size=walls.size();
door_number=doors.size();
window_number=windows.size();
walls3D.clear();
doors3D.clear();
doors3DAngle.clear();
windows3D.clear();
minx=10000;
miny=10000;
maxx=-10000;
maxy=-10000;
for(i=0; i<wall_size; i++) {
    minx=min(minx, walls[i].points[0].coord[0]);
    maxx=max(maxx, walls[i].points[0].coord[0]);
    miny=min(miny, walls[i].points[0].coord[1]);
    maxy=max(maxy, walls[i].points[0].coord[1]);
} 

minx-=50;
miny-=50;
maxx+=50;
maxy+=50;
printf("%lf %lf %lf %lf\n", minx, maxx, miny, maxy);

for(i=0; i<wall_size; i++) 
         {
         j=0;
//         walls3D.push_back(new_3d_wall);

         liste[j++]=walls[i].points[0];        
         liste[j++]=walls[i].points[1];
         for (k=0;k<door_number;k++)
            if (i==doors[k].parent) 
                { 
                liste[j++]=doors[k].points[0];  
                liste[j++]=doors[k].points[1];      
                }

         
         for (k=0;k<window_number;k++)
            if (i==windows[k].parent) 
                { 
                liste[j++]=windows[k].points[0];  
                liste[j++]=windows[k].points[1];      
                }
        qsort(liste, j, sizeof(struct vertex), cmp);
        for(k=0; k<j; k+=2) {   
          walls3D.push_back(new_3d_wall);
          find8Points(liste[k],liste[k+1],wall_width, 0, wall_height, &walls3D[t++]);
        }
         }

         for (k=0;k<door_number;k++) {   
          walls3D.push_back(new_3d_wall);
          find8Points(doors[k].points[0],doors[k].points[1],wall_width, wall_height-40, wall_height, &walls3D[t++]);
          doors3D.push_back(new_3d_wall);
          doors3DAngle.push_back(0);
          find8Points(doors[k].points[0],doors[k].points[1],wall_width/2, 0,  wall_height-40,  &doors3D[k]);
        }
         for (k=0;k<window_number;k++) {   
          walls3D.push_back(new_3d_wall);
          find8Points(windows[k].points[0],windows[k].points[1],wall_width, 0, 50, &walls3D[t++]);
          walls3D.push_back(new_3d_wall);
          find8Points(windows[k].points[0],windows[k].points[1],wall_width, wall_height-30, wall_height, &walls3D[t++]);
          windows3D.push_back(new_3d_wall);
          find8Points(windows[k].points[0],windows[k].points[1],wall_width/5, 50, wall_height-30, &windows3D[k]);
        }
         

}


void updateDoorAngles() {
  int i;
  for(i=0; i<doors.size(); i++)
    if(doors3DAngle[i]!=0 && doors3DAngle[i]!=50) {
      doors3DAngle[i]++;
      if(doors3DAngle[i]<50)
        rotateWall(doors[i].points[0], &doors3D[i], M_PI/100);
      else if(doors3DAngle[i]<99)
        rotateWall(doors[i].points[0], &doors3D[i], -M_PI/100);
      else doors3DAngle[i]=0;
    }
}



void find8Points(struct vertex v1,struct vertex v2,int wall_width,int h0, int h1, struct wall3D* which) {
GLfloat m;
GLfloat w2=wall_width/2, h2=wall_height/2;

m=(v2.coord[1]-v1.coord[1])/(v2.coord[0]-v1.coord[0]);
if (m>0) 
{
which->points[0].coord[0]=v1.coord[0]-w2*sqrt(m*m/(m*m+1));
which->points[0].coord[1]=v1.coord[1]+w2*sqrt(1/(m*m+1));
which->points[0].coord[2]=h0;
which->points[1].coord[0]=v1.coord[0]+w2*sqrt(m*m/(m*m+1));
which->points[1].coord[1]=v1.coord[1]-w2*sqrt(1/(m*m+1));
which->points[1].coord[2]=h0;
which->points[2].coord[0]=v2.coord[0]+w2*sqrt(m*m/(m*m+1));
which->points[2].coord[1]=v2.coord[1]-w2*sqrt(1/(m*m+1));
which->points[2].coord[2]=h0;
which->points[3].coord[0]=v2.coord[0]-w2*sqrt(m*m/(m*m+1));
which->points[3].coord[1]=v2.coord[1]+w2*sqrt(1/(m*m+1));
which->points[3].coord[2]=h0;

which->points[4].coord[0]=which->points[0].coord[0];
which->points[4].coord[1]=which->points[0].coord[1];
which->points[4].coord[2]=h1;
which->points[5].coord[0]=which->points[1].coord[0];
which->points[5].coord[1]=which->points[1].coord[1];
which->points[5].coord[2]=h1;
which->points[6].coord[0]=which->points[2].coord[0];
which->points[6].coord[1]=which->points[2].coord[1];
which->points[6].coord[2]=h1;
which->points[7].coord[0]=which->points[3].coord[0];
which->points[7].coord[1]=which->points[3].coord[1];
which->points[7].coord[2]=h1;
}
else
{
which->points[0].coord[0]=v1.coord[0]+w2*sqrt(m*m/(m*m+1));
which->points[0].coord[1]=v1.coord[1]+w2*sqrt(1/(m*m+1));   
which->points[0].coord[2]=h0;
which->points[1].coord[0]=v1.coord[0]-w2*sqrt(m*m/(m*m+1));
which->points[1].coord[1]=v1.coord[1]-w2*sqrt(1/(m*m+1));
which->points[1].coord[2]=h0;
which->points[2].coord[0]=v2.coord[0]-w2*sqrt(m*m/(m*m+1));
which->points[2].coord[1]=v2.coord[1]-w2*sqrt(1/(m*m+1));
which->points[2].coord[2]=h0;
which->points[3].coord[0]=v2.coord[0]+w2*sqrt(m*m/(m*m+1));
which->points[3].coord[1]=v2.coord[1]+w2*sqrt(1/(m*m+1));
which->points[3].coord[2]=h0;

which->points[4].coord[0]=which->points[0].coord[0];
which->points[4].coord[1]=which->points[0].coord[1];
which->points[4].coord[2]=h1;
which->points[5].coord[0]=which->points[1].coord[0];
which->points[5].coord[1]=which->points[1].coord[1];
which->points[5].coord[2]=h1;
which->points[6].coord[0]=which->points[2].coord[0];
which->points[6].coord[1]=which->points[2].coord[1];
which->points[6].coord[2]=h1;
which->points[7].coord[0]=which->points[3].coord[0];
which->points[7].coord[1]=which->points[3].coord[1];
which->points[7].coord[2]=h1;
}
}



void    drawDoors()
{
int i;
int     w2=wall_width/2, h2=wall_height/2;
glColor3f(0.0,0.0,0.0);

for (i=0;i<doors.size();i++)
{
glBegin(GL_QUADS);
glVertex3d(doors[i].points[0].coord[0],doors[i].points[0].coord[1]-w2,wall_height);
glVertex3d(doors[i].points[0].coord[0],doors[i].points[0].coord[1]+w2,wall_height);
glVertex3d(doors[i].points[1].coord[0],doors[i].points[1].coord[1]+w2,wall_height);
glVertex3d(doors[i].points[1].coord[0],doors[i].points[1].coord[1]-w2,wall_height);
glEnd();    
glBegin(GL_QUADS);
glVertex3d(doors[i].points[0].coord[0],doors[i].points[0].coord[1]-w2,h2);
glVertex3d(doors[i].points[0].coord[0],doors[i].points[0].coord[1]+w2,h2);
glVertex3d(doors[i].points[1].coord[0],doors[i].points[1].coord[1]+w2,h2);
glVertex3d(doors[i].points[1].coord[0],doors[i].points[1].coord[1]-w2,h2);
glEnd();    

glBegin(GL_QUADS);
glVertex3d(doors[i].points[0].coord[0],doors[i].points[0].coord[1]-w2,wall_height);
glVertex3d(doors[i].points[0].coord[0],doors[i].points[0].coord[1]+w2,wall_height);
glVertex3d(doors[i].points[0].coord[0],doors[i].points[0].coord[1]+w2,h2);
glVertex3d(doors[i].points[0].coord[0],doors[i].points[0].coord[1]-w2,h2);
glEnd();    
glBegin(GL_QUADS);
glVertex3d(doors[i].points[1].coord[0],doors[i].points[1].coord[1]-w2,wall_height);
glVertex3d(doors[i].points[1].coord[0],doors[i].points[1].coord[1]+w2,wall_height);
glVertex3d(doors[i].points[1].coord[0],doors[i].points[1].coord[1]+w2,h2);
glVertex3d(doors[i].points[1].coord[0],doors[i].points[1].coord[1]-w2,h2);
glEnd();    

glBegin(GL_QUADS);
glVertex3d(doors[i].points[0].coord[0],doors[i].points[0].coord[1]-w2,wall_height);
glVertex3d(doors[i].points[0].coord[0],doors[i].points[0].coord[1]-w2,h2);
glVertex3d(doors[i].points[1].coord[0],doors[i].points[1].coord[1]-w2,h2);
glVertex3d(doors[i].points[1].coord[0],doors[i].points[1].coord[1]-w2,wall_height);
glEnd();    

}



        
}



void    drawWindows()
{
int i;
int     w2=wall_width/2, h2=wall_height/2;
glColor3f(1.0,1.0,1.0);

for (i=0;i<windows.size();i++)
{
glBegin(GL_QUADS);
glVertex3d(windows[i].points[0].coord[0],windows[i].points[0].coord[1]-w2,40);
glVertex3d(windows[i].points[0].coord[0],windows[i].points[0].coord[1]+w2,40);
glVertex3d(windows[i].points[1].coord[0],windows[i].points[1].coord[1]+w2,40);
glVertex3d(windows[i].points[1].coord[0],windows[i].points[1].coord[1]-w2,40);
glEnd();    
glBegin(GL_QUADS);
glVertex3d(windows[i].points[0].coord[0],windows[i].points[0].coord[1]-w2,20);
glVertex3d(windows[i].points[0].coord[0],windows[i].points[0].coord[1]+w2,20);
glVertex3d(windows[i].points[1].coord[0],windows[i].points[1].coord[1]+w2,20);
glVertex3d(windows[i].points[1].coord[0],windows[i].points[1].coord[1]-w2,20);
glEnd();    

glBegin(GL_QUADS);
glVertex3d(windows[i].points[0].coord[0],windows[i].points[0].coord[1]-w2,40);
glVertex3d(windows[i].points[0].coord[0],windows[i].points[0].coord[1]+w2,40);
glVertex3d(windows[i].points[0].coord[0],windows[i].points[0].coord[1]+w2,20);
glVertex3d(windows[i].points[0].coord[0],windows[i].points[0].coord[1]-w2,20);
glEnd();    
glBegin(GL_QUADS);
glVertex3d(windows[i].points[1].coord[0],windows[i].points[1].coord[1]-w2,40);
glVertex3d(windows[i].points[1].coord[0],windows[i].points[1].coord[1]+w2,40);
glVertex3d(windows[i].points[1].coord[0],windows[i].points[1].coord[1]+w2,20);
glVertex3d(windows[i].points[1].coord[0],windows[i].points[1].coord[1]-w2,20);
glEnd();    

glBegin(GL_QUADS);
glVertex3d(windows[i].points[0].coord[0],windows[i].points[0].coord[1]-w2,40);
glVertex3d(windows[i].points[0].coord[0],windows[i].points[0].coord[1]-w2,20);
glVertex3d(windows[i].points[1].coord[0],windows[i].points[1].coord[1]-w2,20);
glVertex3d(windows[i].points[1].coord[0],windows[i].points[1].coord[1]-w2,40);
glEnd();    

}        
}


void showLightSources(){
glColor3f(1.0,1.0,1.0);
// Light Source 1
glBegin(GL_QUADS);
glVertex3f(light0x+light_width,light0y-light_width,light0z+light_width);
glVertex3f(light0x+light_width,light0y+light_width,light0z+light_width);
glVertex3f(light0x-light_width,light0y+light_width,light0z+light_width);
glVertex3f(light0x-light_width,light0y-light_width,light0z+light_width);
glEnd();    
glBegin(GL_QUADS);
glVertex3f(light0x+light_width,light0y-light_width,light0z-light_width);
glVertex3f(light0x+light_width,light0y+light_width,light0z-light_width);
glVertex3f(light0x-light_width,light0y+light_width,light0z-light_width);
glVertex3f(light0x-light_width,light0y-light_width,light0z-light_width);
glEnd();    
glBegin(GL_QUADS);
glVertex3f(light0x+light_width,light0y-light_width,light0z+light_width);
glVertex3f(light0x+light_width,light0y+light_width,light0z+light_width);
glVertex3f(light0x+light_width,light0y+light_width,light0z-light_width);
glVertex3f(light0x+light_width,light0y-light_width,light0z-light_width);
glEnd();  
glBegin(GL_QUADS);
glVertex3f(light0x-light_width,light0y-light_width,light0z+light_width);
glVertex3f(light0x-light_width,light0y+light_width,light0z+light_width);
glVertex3f(light0x-light_width,light0y+light_width,light0z-light_width);
glVertex3f(light0x-light_width,light0y-light_width,light0z-light_width);
glEnd();  
glBegin(GL_QUADS);
glVertex3f(light0x-light_width,light0y+light_width,light0z+light_width);
glVertex3f(light0x+light_width,light0y+light_width,light0z+light_width);
glVertex3f(light0x+light_width,light0y+light_width,light0z-light_width);
glVertex3f(light0x-light_width,light0y+light_width,light0z-light_width);
glEnd();  
glBegin(GL_QUADS);
glVertex3f(light0x-light_width,light0y-light_width,light0z+light_width);
glVertex3f(light0x+light_width,light0y-light_width,light0z+light_width);
glVertex3f(light0x+light_width,light0y-light_width,light0z-light_width);
glVertex3f(light0x-light_width,light0y-light_width,light0z-light_width);
glEnd();  

// Light Source 2
glBegin(GL_QUADS);
glVertex3f(light1x+light_width,light1y-light_width,light1z+light_width);
glVertex3f(light1x+light_width,light1y+light_width,light1z+light_width);
glVertex3f(light1x-light_width,light1y+light_width,light1z+light_width);
glVertex3f(light1x-light_width,light1y-light_width,light1z+light_width);
glEnd();    
glBegin(GL_QUADS);
glVertex3f(light1x+light_width,light1y-light_width,light1z-light_width);
glVertex3f(light1x+light_width,light1y+light_width,light1z-light_width);
glVertex3f(light1x-light_width,light1y+light_width,light1z-light_width);
glVertex3f(light1x-light_width,light1y-light_width,light1z-light_width);
glEnd();    
glBegin(GL_QUADS);
glVertex3f(light1x+light_width,light1y-light_width,light1z+light_width);
glVertex3f(light1x+light_width,light1y+light_width,light1z+light_width);
glVertex3f(light1x+light_width,light1y+light_width,light1z-light_width);
glVertex3f(light1x+light_width,light1y-light_width,light1z-light_width);
glEnd();  
glBegin(GL_QUADS);
glVertex3f(light1x-light_width,light1y-light_width,light1z+light_width);
glVertex3f(light1x-light_width,light1y+light_width,light1z+light_width);
glVertex3f(light1x-light_width,light1y+light_width,light1z-light_width);
glVertex3f(light1x-light_width,light1y-light_width,light1z-light_width);
glEnd();  
glBegin(GL_QUADS);
glVertex3f(light1x-light_width,light1y+light_width,light1z+light_width);
glVertex3f(light1x+light_width,light1y+light_width,light1z+light_width);
glVertex3f(light1x+light_width,light1y+light_width,light1z-light_width);
glVertex3f(light1x-light_width,light1y+light_width,light1z-light_width);
glEnd();  
glBegin(GL_QUADS);
glVertex3f(light1x-light_width,light1y-light_width,light1z+light_width);
glVertex3f(light1x+light_width,light1y-light_width,light1z+light_width);
glVertex3f(light1x+light_width,light1y-light_width,light1z-light_width);
glVertex3f(light1x-light_width,light1y-light_width,light1z-light_width);
glEnd();  

glColor3f(1.0,1.0,0.0);
// Light Source 3
glBegin(GL_QUADS);
glVertex3f(light2x+light_width,light2y-light_width,light2z+light_width);
glVertex3f(light2x+light_width,light2y+light_width,light2z+light_width);
glVertex3f(light2x-light_width,light2y+light_width,light2z+light_width);
glVertex3f(light2x-light_width,light2y-light_width,light2z+light_width);
glEnd();    
glBegin(GL_QUADS);
glVertex3f(light2x+light_width,light2y-light_width,light2z-light_width);
glVertex3f(light2x+light_width,light2y+light_width,light2z-light_width);
glVertex3f(light2x-light_width,light2y+light_width,light2z-light_width);
glVertex3f(light2x-light_width,light2y-light_width,light2z-light_width);
glEnd();    
glBegin(GL_QUADS);
glVertex3f(light2x+light_width,light2y-light_width,light2z+light_width);
glVertex3f(light2x+light_width,light2y+light_width,light2z+light_width);
glVertex3f(light2x+light_width,light2y+light_width,light2z-light_width);
glVertex3f(light2x+light_width,light2y-light_width,light2z-light_width);
glEnd();  
glBegin(GL_QUADS);
glVertex3f(light2x-light_width,light2y-light_width,light2z+light_width);
glVertex3f(light2x-light_width,light2y+light_width,light2z+light_width);
glVertex3f(light2x-light_width,light2y+light_width,light2z-light_width);
glVertex3f(light2x-light_width,light2y-light_width,light2z-light_width);
glEnd();  
glBegin(GL_QUADS);
glVertex3f(light2x-light_width,light2y+light_width,light2z+light_width);
glVertex3f(light2x+light_width,light2y+light_width,light2z+light_width);
glVertex3f(light2x+light_width,light2y+light_width,light2z-light_width);
glVertex3f(light2x-light_width,light2y+light_width,light2z-light_width);
glEnd();  
glBegin(GL_QUADS);
glVertex3f(light2x-light_width,light2y-light_width,light2z+light_width);
glVertex3f(light2x+light_width,light2y-light_width,light2z+light_width);
glVertex3f(light2x+light_width,light2y-light_width,light2z-light_width);
glVertex3f(light2x-light_width,light2y-light_width,light2z-light_width);
glEnd();  
}




void phase1Save() {
int i;
FILE *f;
f=fopen("phase1.txt","w");
fprintf(f,"%d %d %d %d %d\n",walls.size(),my_poly.size(),doors.size(),windows.size(),furnitures.size());
for (i=0;i<walls.size();i++)
    {
    fprintf(f,"%lf %lf %lf ",walls[i].points[0].coord[0],walls[i].points[0].coord[1],walls[i].points[0].coord[2]);
    fprintf(f,"%lf %lf %lf\n",walls[i].points[1].coord[0],walls[i].points[1].coord[1],walls[i].points[1].coord[2]);
    }
fprintf(f,"\n");

for (i=0;i<my_poly.size();i++)
    fprintf(f,"%lf %lf %lf ",my_poly[i].coord[0],my_poly[i].coord[1],my_poly[i].coord[2]);
fprintf(f,"\n");
for (i=0;i<doors.size();i++)
    {
    fprintf(f,"%lf %lf %lf ",doors[i].points[0].coord[0],doors[i].points[0].coord[1],doors[i].points[0].coord[2]);
    fprintf(f,"%lf %lf %lf ",doors[i].points[1].coord[0],doors[i].points[1].coord[1],doors[i].points[1].coord[2]);
    fprintf(f,"%d ",doors[i].parent);
    
    }
fprintf(f,"\n");
for (i=0;i<windows.size();i++)
    {
    fprintf(f,"%lf %lf %lf ",windows[i].points[0].coord[0],windows[i].points[0].coord[1],windows[i].points[0].coord[2]);
    fprintf(f,"%lf %lf %lf ",windows[i].points[1].coord[0],windows[i].points[1].coord[1],windows[i].points[1].coord[2]);
    fprintf(f,"%d ",windows[i].parent);
    }
fprintf(f,"\n");
for (i=0;i<furnitures.size();i++)
    {
    int j=0;
    fprintf(f,"%d \n",furnitures[i].polygon.size());
    fprintf(f,"%d \n",furnitures[i].type);
    for (j=0;j<furnitures[i].polygon.size();j++)
        fprintf(f,"%lf %lf %lf ",furnitures[i].polygon[j].coord[0],furnitures[i].polygon[j].coord[1],furnitures[i].polygon[j].coord[2]);
    fprintf(f,"\n");
    fprintf(f,"%f %f %f \n",furnitures[i].color[0],furnitures[i].color[1],furnitures[i].color[2]);
    fprintf(f,"%c ",furnitures[i].letter);
    }

fclose(f);
}



void phase1Load() {
int i,s_walls,s_my_poly,s_doors,s_windows,s_furnitures;
FILE *f;
struct wall t_wall, t_door, t_window;
struct vertex t_poly,tmp;
struct fur t_fur;
f=fopen("phase1.txt","r");

fscanf(f,"%d %d %d %d %d",&s_walls,&s_my_poly,&s_doors,&s_windows,&s_furnitures);
t_wall.points.push_back(t_poly);
t_wall.points.push_back(tmp);
t_door.points.push_back(t_poly);
t_door.points.push_back(tmp);
t_window.points.push_back(t_poly);
t_window.points.push_back(tmp);

my_poly.clear();

for (i=s_walls;i>0;i--)
    {
    fscanf(f,"%lf %lf %lf",&(t_wall.points[0].coord[0]),&(t_wall.points[0].coord[1]),&(t_wall.points[0].coord[2]));
    fscanf(f,"%lf %lf %lf",&(t_wall.points[1].coord[0]),&(t_wall.points[1].coord[1]),&(t_wall.points[1].coord[2]));
    walls.push_back(t_wall);
    }

for (i=s_my_poly;i>0;i--)
    {
    fscanf(f,"%lf %lf %lf",&(t_poly.coord[0]),&(t_poly.coord[1]),&(t_poly.coord[2]));
    my_poly.push_back(t_poly);
    }

for (i=s_doors;i>0;i--)
    {
    fscanf(f,"%lf %lf %lf",&(t_door.points[0].coord[0]),&(t_door.points[0].coord[1]),&(t_door.points[0].coord[2]));
    fscanf(f,"%lf %lf %lf",&(t_door.points[1].coord[0]),&(t_door.points[1].coord[1]),&(t_door.points[1].coord[2]));
    fscanf(f,"%d",&(t_door.parent));
    doors.push_back(t_door);
    }

for (i=s_windows;i>0;i--)
    {
    fscanf(f,"%lf %lf %lf",&(t_window.points[0].coord[0]),&(t_window.points[0].coord[1]),&(t_window.points[0].coord[2]));
    fscanf(f,"%lf %lf %lf",&(t_window.points[1].coord[0]),&(t_window.points[1].coord[1]),&(t_window.points[1].coord[2]));
    fscanf(f,"%d",&(t_window.parent));
    windows.push_back(t_window);
    }

for (i=s_furnitures;i>0;i--)
    {
    int j;
    fscanf(f,"%d",&j);
    fscanf(f,"%d",&(t_fur.type));
    for (;j>0;j--)
        {
        fscanf(f,"%lf %lf %lf",&(tmp.coord[0]),&(tmp.coord[1]),&(tmp.coord[2]));
        t_fur.polygon.push_back(tmp);
        }
    fscanf(f,"%f %f %f",&(t_fur.color[0]),&(t_fur.color[1]),&(t_fur.color[2]));
    fscanf(f,"%c",&(t_fur.letter));
    furnitures.push_back(t_fur);
    }

fclose(f);
state=10;
}



void phase2Save() {
int i;
FILE *f;
f=fopen("phase2.txt","w");
fprintf(f,"%d %d %d %d %d %d %d\n",walls.size(),my_poly.size(),doors.size(),windows.size(),furnitures.size(),wall_width,wall_height);
for (i=0;i<walls.size();i++)
    {
    fprintf(f,"%lf %lf %lf ",walls[i].points[0].coord[0],walls[i].points[0].coord[1],walls[i].points[0].coord[2]);
    fprintf(f,"%lf %lf %lf\n",walls[i].points[1].coord[0],walls[i].points[1].coord[1],walls[i].points[1].coord[2]);
    }
fprintf(f,"\n");

for (i=0;i<my_poly.size();i++)
    fprintf(f,"%lf %lf %lf ",my_poly[i].coord[0],my_poly[i].coord[1],my_poly[i].coord[2]);
fprintf(f,"\n");
for (i=0;i<doors.size();i++)
    {
    fprintf(f,"%lf %lf %lf ",doors[i].points[0].coord[0],doors[i].points[0].coord[1],doors[i].points[0].coord[2]);
    fprintf(f,"%lf %lf %lf ",doors[i].points[1].coord[0],doors[i].points[1].coord[1],doors[i].points[1].coord[2]);
        fprintf (f,"%d ",doors[i].parent);   
     }
fprintf(f,"\n");
for (i=0;i<windows.size();i++)
    {
    fprintf(f,"%lf %lf %lf ",windows[i].points[0].coord[0],windows[i].points[0].coord[1],windows[i].points[0].coord[2]);
    fprintf(f,"%lf %lf %lf ",windows[i].points[1].coord[0],windows[i].points[1].coord[1],windows[i].points[1].coord[2]);
    fprintf (f,"%d ",windows[i].parent);
    }
fprintf(f,"\n");
for (i=0;i<furnitures.size();i++)
    {
    int j=0;
    fprintf(f,"%d \n",furnitures[i].polygon.size());
    fprintf(f,"%d \n",furnitures[i].type);
    for (j=0;j<furnitures[i].polygon.size();j++)
        fprintf(f,"%lf %lf %lf ",furnitures[i].polygon[j].coord[0],furnitures[i].polygon[j].coord[1],furnitures[i].polygon[j].coord[2]);
    fprintf(f,"\n");
    fprintf(f,"%f %f %f \n",furnitures[i].color[0],furnitures[i].color[1],furnitures[i].color[2]);
    fprintf(f,"%c ",furnitures[i].letter);
    }

fclose(f);
}



void phase2Load() {
int i,s_walls,s_my_poly,s_doors,s_windows,s_furnitures;
FILE *f;
struct wall t_wall, t_door, t_window;
struct vertex t_poly,tmp;
struct fur t_fur;
f=fopen("phase2.txt","r");

fscanf(f,"%d %d %d %d %d %d %d",&s_walls,&s_my_poly,&s_doors,&s_windows,&s_furnitures,&wall_width,&wall_height);
t_wall.points.push_back(t_poly);
t_wall.points.push_back(tmp);
t_door.points.push_back(t_poly);
t_door.points.push_back(tmp);
t_window.points.push_back(t_poly);
t_window.points.push_back(tmp);

my_poly.clear();

for (i=s_walls;i>0;i--)
    {
    fscanf(f,"%lf %lf %lf",&(t_wall.points[0].coord[0]),&(t_wall.points[0].coord[1]),&(t_wall.points[0].coord[2]));
    fscanf(f,"%lf %lf %lf",&(t_wall.points[1].coord[0]),&(t_wall.points[1].coord[1]),&(t_wall.points[1].coord[2]));
    walls.push_back(t_wall);
    }

for (i=s_my_poly;i>0;i--)
    {
    fscanf(f,"%lf %lf %lf",&(t_poly.coord[0]),&(t_poly.coord[1]),&(t_poly.coord[2]));
    my_poly.push_back(t_poly);
    }

for (i=s_doors;i>0;i--)
    {
    fscanf(f,"%lf %lf %lf",&(t_door.points[0].coord[0]),&(t_door.points[0].coord[1]),&(t_door.points[0].coord[2]));
    fscanf(f,"%lf %lf %lf",&(t_door.points[1].coord[0]),&(t_door.points[1].coord[1]),&(t_door.points[1].coord[2]));
    fscanf (f,"%d",&(t_door.parent));
    doors.push_back(t_door);
    }

for (i=s_windows;i>0;i--)
    {
    fscanf(f,"%lf %lf %lf",&(t_window.points[0].coord[0]),&(t_window.points[0].coord[1]),&(t_window.points[0].coord[2]));
    fscanf(f,"%lf %lf %lf",&(t_window.points[1].coord[0]),&(t_window.points[1].coord[1]),&(t_window.points[1].coord[2]));
    fscanf (f,"%d",&(t_window.parent));
    windows.push_back(t_window);
    }

for (i=s_furnitures;i>0;i--)
    {
    int j;
    fscanf(f,"%d",&j);
    fscanf(f,"%d",&(t_fur.type));
    for (;j>0;j--)
        {
        fscanf(f,"%lf %lf %lf",&(tmp.coord[0]),&(tmp.coord[1]),&(tmp.coord[2]));
        t_fur.polygon.push_back(tmp);
        }
    fscanf(f,"%f %f %f",&(t_fur.color[0]),&(t_fur.color[1]),&(t_fur.color[2]));
    fscanf(f,"%c",&(t_fur.letter));
    furnitures.push_back(t_fur);
    }

fclose(f);
state=10;
}



void phase3Save() {
int i;
FILE *f;
f=fopen("phase3.txt","w");
fprintf(f,"%d %d %d %d %d %d %d\n",walls.size(),my_poly.size(),doors.size(),windows.size(),furnitures.size(),wall_width,wall_height);
for (i=0;i<walls.size();i++)
    {
    fprintf(f,"%lf %lf %lf ",walls[i].points[0].coord[0],walls[i].points[0].coord[1],walls[i].points[0].coord[2]);
    fprintf(f,"%lf %lf %lf\n",walls[i].points[1].coord[0],walls[i].points[1].coord[1],walls[i].points[1].coord[2]);
    }
fprintf(f,"\n");

for (i=0;i<my_poly.size();i++)
    fprintf(f,"%lf %lf %lf ",my_poly[i].coord[0],my_poly[i].coord[1],my_poly[i].coord[2]);
fprintf(f,"\n");
for (i=0;i<doors.size();i++)
    {
    fprintf(f,"%lf %lf %lf ",doors[i].points[0].coord[0],doors[i].points[0].coord[1],doors[i].points[0].coord[2]);
    fprintf(f,"%lf %lf %lf ",doors[i].points[1].coord[0],doors[i].points[1].coord[1],doors[i].points[1].coord[2]);
    fprintf (f,"%d ",doors[i].parent);
    }
fprintf(f,"\n");
for (i=0;i<windows.size();i++)
    {
    fprintf(f,"%lf %lf %lf ",windows[i].points[0].coord[0],windows[i].points[0].coord[1],windows[i].points[0].coord[2]);
    fprintf(f,"%lf %lf %lf ",windows[i].points[1].coord[0],windows[i].points[1].coord[1],windows[i].points[1].coord[2]);
    fprintf (f,"%d ",windows[i].parent);
    }
fprintf(f,"\n");
for (i=0;i<furnitures.size();i++)
    {
    int j=0;
    fprintf(f,"%d \n",furnitures[i].polygon.size());
    fprintf(f,"%d \n",furnitures[i].type);
    for (j=0;j<furnitures[i].polygon.size();j++)
        fprintf(f,"%lf %lf %lf ",furnitures[i].polygon[j].coord[0],furnitures[i].polygon[j].coord[1],furnitures[i].polygon[j].coord[2]);
    fprintf(f,"\n");
    fprintf(f,"%f %f %f \n",furnitures[i].color[0],furnitures[i].color[1],furnitures[i].color[2]);
    fprintf(f,"%c ",furnitures[i].letter);
    }
fprintf(f,"\n\n\n\n\n");
/////////////////////////////////////////////////////

fprintf (f,"%f %f %f %f %f %f %f %f %f %f %f %f ",xx0,yy0,zz0,xref,yref,zref,vx,vy,vz,walkDir,walkDirV,freeMode);
fprintf (f,"%d %d %d %d %d %d %d %d ",wall_width,wall_height,inside,mouseX, mouseY,model_num,model_dir,cati_goster);
fprintf (f,"%f %f %f %f %f %f %f %f %f %f ",uzunluk,light0x,light0y,light0z,light1x,light1y,light1z,light2x,light2y,light2z);
fprintf (f,"%f %f %f %f %f %f %f %f %f ",atten0_cons,atten0_lin,atten0_quad,atten1_cons,atten1_lin,atten1_quad,atten2_cons,atten2_lin,atten2_quad);
fprintf (f,"%f %f %f %f %f ",spot_angle, spot_exp, spot_x, spot_y, spot_z);
fprintf (f,"%f %f %f %f %f %f %f %f %f ",amb0_r,amb0_g,amb0_b,amb1_r,amb1_g,amb1_b,amb2_r,amb2_g,amb2_b);
fprintf (f,"%f %f %f %f %f %f %f %f %f ",dif0_r,dif0_g,dif0_b,dif1_r,dif1_g,dif1_b,dif2_r,dif2_g,dif2_b);
fprintf (f,"%f %f %f %f %f %f %f %f ",tex1_x1,tex1_x2,tex1_y1,tex1_y2,tex2_x1,tex2_x2,tex2_y1,tex2_y2);
fprintf (f,"%f %f %f %f %f ",minx, miny, maxx, maxy,xyzRotationAngle);
fprintf (f,"%s %s %s ",fileName1,fileName2,fileName3);
fprintf (f,"%f %f %f %f %f ",sc1,sc2,sc3,light_width,shine);
fprintf (f,"%f %f %f %f %f %f %f %f %f ",model1x,model1y,model1z,model2x,model2y,model2z,model3x,model3y,model3z);
fprintf (f,"%f %f %f ",xRotation,yRotation,zRotation);
fprintf (f,"%f %f %f %f %f %f %f %f %f ",rotx0,roty0,rotz0,rotx1,roty1,rotz1,rotx2,roty2,rotz2);
fprintf (f,"%s %s ",texture_name,wall_top_texture);

fclose(f);

}



void phase3Load() {
int i,s_walls,s_my_poly,s_doors,s_windows,s_furnitures;
FILE *f;
struct wall t_wall, t_door, t_window;
struct vertex t_poly,tmp;
struct fur t_fur;
f=fopen("phase3.txt","r");

fscanf(f,"%d %d %d %d %d %d %d",&s_walls,&s_my_poly,&s_doors,&s_windows,&s_furnitures,&wall_width,&wall_height);
t_wall.points.push_back(t_poly);
t_wall.points.push_back(tmp);
t_door.points.push_back(t_poly);
t_door.points.push_back(tmp);
t_window.points.push_back(t_poly);
t_window.points.push_back(tmp);

my_poly.clear();

for (i=s_walls;i>0;i--)
    {
    fscanf(f,"%lf %lf %lf",&(t_wall.points[0].coord[0]),&(t_wall.points[0].coord[1]),&(t_wall.points[0].coord[2]));
    fscanf(f,"%lf %lf %lf",&(t_wall.points[1].coord[0]),&(t_wall.points[1].coord[1]),&(t_wall.points[1].coord[2]));
    walls.push_back(t_wall);
    }

for (i=s_my_poly;i>0;i--)
    {
    fscanf(f,"%lf %lf %lf",&(t_poly.coord[0]),&(t_poly.coord[1]),&(t_poly.coord[2]));
    my_poly.push_back(t_poly);
    }

for (i=s_doors;i>0;i--)
    {
    fscanf(f,"%lf %lf %lf",&(t_door.points[0].coord[0]),&(t_door.points[0].coord[1]),&(t_door.points[0].coord[2]));
    fscanf(f,"%lf %lf %lf",&(t_door.points[1].coord[0]),&(t_door.points[1].coord[1]),&(t_door.points[1].coord[2]));
    fscanf (f,"%d",&(t_door.parent));
    doors.push_back(t_door);
    }

for (i=s_windows;i>0;i--)
    {
    fscanf(f,"%lf %lf %lf",&(t_window.points[0].coord[0]),&(t_window.points[0].coord[1]),&(t_window.points[0].coord[2]));
    fscanf(f,"%lf %lf %lf",&(t_window.points[1].coord[0]),&(t_window.points[1].coord[1]),&(t_window.points[1].coord[2]));
    fscanf (f,"%d",&(t_window.parent));
    windows.push_back(t_window);
    }

for (i=s_furnitures;i>0;i--)
    {
    int j;
    fscanf(f,"%d",&j);
    fscanf(f,"%d",&(t_fur.type));
    for (;j>0;j--)
        {
        fscanf(f,"%lf %lf %lf",&(tmp.coord[0]),&(tmp.coord[1]),&(tmp.coord[2]));
        t_fur.polygon.push_back(tmp);
        }
    fscanf(f,"%f %f %f",&(t_fur.color[0]),&(t_fur.color[1]),&(t_fur.color[2]));
    fscanf(f,"%c",&(t_fur.letter));
    furnitures.push_back(t_fur);
    }


//////////////////////////

fscanf (f,"%f %f %f %f %f %f %f %f %f %f %f %f",&xx0,&yy0,&zz0,&xref,&yref,&zref,&vx,&vy,&vz,&walkDir,&walkDirV,&freeMode);
fscanf (f,"%d %d %d %d %d %d %d %d",&wall_width,&wall_height,&inside,&mouseX,&mouseY,&model_num,&model_dir,&cati_goster);
fscanf (f,"%f %f %f %f %f %f %f %f %f %f",&uzunluk,&light0x,&light0y,&light0z,&light1x,&light1y,&light1z,&light2x,&light2y,&light2z);
fscanf (f,"%f %f %f %f %f %f %f %f %f",&atten0_cons,&atten0_lin,&atten0_quad,&atten1_cons,&atten1_lin,&atten1_quad,&atten2_cons,&atten2_lin,&atten2_quad);
fscanf (f,"%f %f %f %f %f",&spot_angle,&spot_exp,&spot_x,&spot_y,&spot_z);
fscanf (f,"%f %f %f %f %f %f %f %f %f",&amb0_r,&amb0_g,&amb0_b,&amb1_r,&amb1_g,&amb1_b,&amb2_r,&amb2_g,&amb2_b);
fscanf (f,"%f %f %f %f %f %f %f %f %f",&dif0_r,&dif0_g,&dif0_b,&dif1_r,&dif1_g,&dif1_b,&dif2_r,&dif2_g,&dif2_b);
fscanf (f,"%f %f %f %f %f %f %f %f",&tex1_x1,&tex1_x2,&tex1_y1,&tex1_y2,&tex2_x1,&tex2_x2,&tex2_y1,&tex2_y2);
fscanf (f,"%f %f %f %f %f",&minx,&miny,&maxx,&maxy,&xyzRotationAngle);
fscanf (f,"%s %s %s",fileName1,fileName2,fileName3);
fscanf (f,"%f %f %f %f %f",&sc1,&sc2,&sc3,&light_width,&shine);
fscanf (f,"%f %f %f %f %f %f %f %f %f",&model1x,&model1y,&model1z,&model2x,&model2y,&model2z,&model3x,&model3y,&model3z);
fscanf (f,"%f %f %f",&xRotation,&yRotation,&zRotation);
fscanf (f,"%f %f %f %f %f %f %f %f %f",&rotx0,&roty0,&rotz0,&rotx1,&roty1,&rotz1,&rotx2,&roty2,&rotz2);
fscanf (f,"%s %s",texture_name,wall_top_texture);

fclose(f);

state=10;
create3dPoints();  
enlightMe();  
updateDoorAngles();  
   if ( glutGetWindow() != phase3_window) 
    glutSetWindow(phase3_window);  
updatePosition(0,0,0);
CurrentModel = &model01; 
CurrentModel->Rotate(rotx0,roty0,rotz0); 
CurrentModel->SetPosition(model1x,model1y,model1z);
CurrentModel->SetScalar(sc1);
CurrentModel = &model02; 
CurrentModel->Rotate(rotx1,roty1,rotz1); 
CurrentModel->SetPosition(model2x,model2y,model2z);
CurrentModel->SetScalar(sc2);
CurrentModel = &model03; 
CurrentModel->Rotate(rotx2,roty2,rotz2); 
CurrentModel->SetPosition(model3x,model3y,model3z);
CurrentModel->SetScalar(sc3);

}



void drawLine (GLdouble x1, GLdouble y1, GLdouble x2, GLdouble y2) {
   glBegin (GL_LINES);
   glVertex2f (x1, y1);
   glVertex2f (x2, y2);
   glEnd ();
}




void enlightMe()
{

    GLfloat ambience0[] = {amb0_r, amb0_g, amb0_b, 1.0};
    GLfloat ambience1[] = {amb1_r, amb1_g, amb1_b, 1.0};
    GLfloat ambience2[] = {amb2_r, amb2_g, amb2_b, 1.0};
	GLfloat diffuse0[] = {dif0_r, dif0_g, dif0_b, 1.0};
	GLfloat diffuse1[] = {dif1_r, dif1_g, dif1_b, 1.0};
	GLfloat diffuse2[] = {dif2_r, dif2_g, dif2_b, 1.0};

    GLfloat white[] = { 1.0 , 1.0 , 1.0 , 1.0  };
    GLfloat specularColor[] = { 1.0 , 1.0 , 1.0 };

    GLfloat direction0[] = { light0x, light0y, light0z, 0.0};
    GLfloat direction1[] = { light1x, light1y, light1z, 1.0};
    GLfloat direction2[] = { light2x, light2y, light2z, 1.0};
    GLfloat spot_direction[] = { spot_x, spot_y, spot_z };

    glLightfv(GL_LIGHT0, GL_AMBIENT, ambience0 );
	
    glLightfv(GL_LIGHT1, GL_DIFFUSE, diffuse1 );
	glLightfv(GL_LIGHT2, GL_SPECULAR, white);
	glLightfv(GL_LIGHT2, GL_DIFFUSE, white);

    glLightf(GL_LIGHT0, GL_CONSTANT_ATTENUATION, atten0_cons);
    glLightf(GL_LIGHT0, GL_LINEAR_ATTENUATION, atten0_lin);
    glLightf(GL_LIGHT0, GL_QUADRATIC_ATTENUATION, atten0_quad);	
    glLightf(GL_LIGHT1, GL_CONSTANT_ATTENUATION, atten1_cons);
    glLightf(GL_LIGHT1, GL_LINEAR_ATTENUATION, atten1_lin);
    glLightf(GL_LIGHT1, GL_QUADRATIC_ATTENUATION, atten1_quad);	
    glLightf(GL_LIGHT2, GL_CONSTANT_ATTENUATION, atten2_cons);
    glLightf(GL_LIGHT2, GL_LINEAR_ATTENUATION, atten2_lin);
    glLightf(GL_LIGHT2, GL_QUADRATIC_ATTENUATION, atten2_quad);	

    glLightf (GL_LIGHT2, GL_SPOT_CUTOFF, spot_angle);
    glLightfv(GL_LIGHT2, GL_SPOT_DIRECTION, spot_direction);
    glLightf (GL_LIGHT2, GL_SPOT_EXPONENT, spot_exp);
        
    glLightfv(GL_LIGHT0, GL_POSITION, direction0 );
    glLightfv(GL_LIGHT1, GL_POSITION, direction1 );
	glLightfv(GL_LIGHT2, GL_POSITION, direction2 );
	
    glEnable(GL_COLOR_MATERIAL); 
	glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, specularColor);
	glMaterialfv(GL_FRONT_AND_BACK, GL_SHININESS, &shine);
    glMaterialfv(GL_FRONT, GL_AMBIENT, white);


  glEnable(GL_LIGHTING);
  glEnable(GL_LIGHT0);   
  glEnable(GL_LIGHT1);
  glEnable(GL_LIGHT2);

  glEnable(GL_DEPTH_TEST); 
  glShadeModel(GL_FLAT);   
}



void    drawWall(struct vertex v1,struct vertex v2,int wall_width,int wall_height,int which)
{
int i;
GLfloat a1_l,a1_r,b1_l,b1_r,a2_l,a2_r,b2_l,b2_r;
GLdouble tan,ang;
int     w2=wall_width/2, h2=wall_height/2;

tan=(v2.coord[1]-v1.coord[1])/(v2.coord[0]-v1.coord[0]);
ang=atan(tan);
uzunluk=sqrt((v2.coord[1]-v1.coord[1])*(v2.coord[1]-v1.coord[1]) + (v2.coord[0]-v1.coord[0])*(v2.coord[0]-v1.coord[0]));


if ((v2.coord[1]-v1.coord[1])/(v2.coord[0]-v1.coord[0])>1.0 || (v2.coord[1]-v1.coord[1])/(v2.coord[0]-v1.coord[0])<-1.0)
{
a1_l=v1.coord[0]-w2;
a1_r=v1.coord[0]+w2;
b1_l=v1.coord[1];
b1_r=v1.coord[1];

a2_l=v2.coord[0]-w2;
a2_r=v2.coord[0]+w2;
b2_l=v2.coord[1];
b2_r=v2.coord[1];
}
else
{
a1_l=v1.coord[0];
a1_r=v1.coord[0];
b1_l=v1.coord[1]-w2;
b1_r=v1.coord[1]+w2;

a2_l=v2.coord[0];
a2_r=v2.coord[0];
b2_l=v2.coord[1]-w2;
b2_r=v2.coord[1]+w2;
}





// Yanal Alanlar
glColor3f(1.0,0.0,0.0);
glBegin(GL_QUADS);
glVertex3f(a1_l,b1_l,0);
glVertex3f(a1_l,b1_l,wall_height);
glVertex3f(a2_l,b2_l,wall_height);
glVertex3f(a2_l,b2_l,0);
glEnd();      
glBegin(GL_QUADS);
glVertex3f(a1_r,b1_r,0);
glVertex3f(a1_r,b1_r,wall_height);
glVertex3f(a2_r,b2_r,wall_height);
glVertex3f(a2_r,b2_r,0);      
glEnd();      

// Ust ve Alt Alanlar

glColor3f(0.0,0.0,1.0);
glBegin(GL_QUADS);
glVertex3f(a1_l,b1_l,0);
glVertex3f(a1_r,b1_r,0);
glVertex3f(a2_r,b2_r,0);
glVertex3f(a2_l,b2_l,0);
glEnd();   

drawWindows();
drawDoors();

}


/*
void statusBar(char *str) {
int i;
char koordinat[20];
float tmp,tmp2;
glColor4f( 0.92, 0.92, 0.95, 1.0 );

glBegin(GL_POLYGON);
for (i=0;i<4;i++)
   		glVertex3dv(status_poly[i].coord);  
glEnd();   

glColor4f( 0.4, 0.4, 0.4 , 0.7 );
drawThickLine(status_poly[0], status_poly[1], 1);

glColor4f( 0.0, 0.0, 0.0, 1.0 );
RenderText(5, height-5,str);  
RenderText(width-620, height-5,"Selected Area : ");  
tmp=mouse.coord[0]-bdown.coord[0];
if (tmp<0) tmp=-1*tmp;
tmp2=mouse.coord[1]-bdown.coord[1];
if (tmp2<0) tmp2=-1*tmp2;
sprintf(koordinat,"%fx%f",tmp,tmp2);  
RenderText(width-530, height-5,koordinat); 
}
*/


void doMerge() {
     int a, b, c, d, i;
     int r1, r2, doBreak=0, firstLine;
     struct vertex int_point, cur;
     int_point.coord[2]=0;
     
     new_poly.clear();


     doBreak=0;
     for(a=0; a<my_poly.size() && !doBreak; a++) {
         b=(a+1)%my_poly.size();
         for(c=0; c<4 && !doBreak; c++) {
                  d=(c+1)%4;
                  if(lineIntersect(my_poly[a], my_poly[b], my_rect[c], my_rect[d], &int_point)
                    && ccw(my_poly[b], int_point, my_rect[d])==1) 
                  { firstLine=b; doBreak=1; break; }
         }
     }
     doBreak=0;
     memcpy(&cur, &int_point, sizeof(struct vertex));
     while(!doBreak) {
          new_poly.push_back(cur);
          for(a=0; a<my_poly.size(); a++) {
                   b=(a+1)%my_poly.size();
                   if(lineIntersect(my_poly[a], my_poly[b], cur, my_rect[d], &int_point)
                    && ccw(my_rect[d], int_point, my_poly[b])==1) 
                  { doBreak=1; break; }
          }
          memcpy(&cur, &my_rect[d], sizeof(struct vertex));
          d=(d+1)%4;
    }    
    new_poly.push_back(int_point);
    new_poly.push_back(my_poly[b]);
     
    for(i=0; i<my_poly.size(); i++) {
             b=(b+1)%my_poly.size();
             if(b==firstLine) break;
             new_poly.push_back(my_poly[b]);
    }
     my_poly=new_poly;
     doDelete();
     purgePolygon();
}



void doDelete() {
     int i;
     for(i=0; i<4; i++)
              my_rect[i].coord[0]=my_rect[i].coord[1]=0;
}



void doSubtract() {
     int a, b, c, d, i, k=0;
     int r1, r2, doBreak=0, firstLine;
     struct vertex int_point, cur;
     int_point.coord[2]=0;
     new_poly.clear();

     doBreak=0;
     for(a=0; a<my_poly.size() && !doBreak; a++) {
         b=(a+1)%my_poly.size();
         for(c=0; c<4 && !doBreak; c++) {
                  d=(c+3)%4;
                  if(lineIntersect(my_poly[a], my_poly[b], my_rect[c], my_rect[d], &int_point)
                    && ccw(my_poly[b], int_point, my_rect[d])==-1) 
                  { firstLine=b; doBreak=1; break; }
         }
     }
     doBreak=0;
     memcpy(&cur, &int_point, sizeof(struct vertex));
     while(!doBreak) {
          new_poly.push_back(cur);
          for(a=0; a<my_poly.size(); a++) {
                   b=(a+1)%my_poly.size();
                   if(lineIntersect(my_poly[a], my_poly[b], cur, my_rect[d], &int_point)
                    && ccw(my_rect[d], int_point, my_poly[b])==-1) 
                  { doBreak=1; break; }
          }
          memcpy(&cur, &my_rect[d], sizeof(struct vertex));
          d=(d+3)%4;
    }    
    new_poly.push_back(int_point);
    new_poly.push_back(my_poly[b]);
    for(i=0; i<my_poly.size(); i++) {
             b=(b+1)%my_poly.size();
             if(b==firstLine) break;
             new_poly.push_back(my_poly[b]);
    }
    my_poly[0].coord[0]=0;
    my_poly=new_poly;
    doDelete();
     purgePolygon();
}



void rotateRect(int value) {
    struct vertex den;
    den.coord[0]=(my_rect[0].coord[0]+my_rect[2].coord[0])/2;
	den.coord[1]=(my_rect[0].coord[1]+my_rect[2].coord[1])/2;
	den.coord[2]=0.0;
	rotateRect(den, rotate_value , 4);
	trans_type = 0;
}



void rotateRect(struct vertex pivot,struct fur *furniture, GLdouble angle)
{
int vertex_num=furniture->polygon.size();
vector<struct vertex> tmp(vertex_num);
int 		i;
angle=angle*DEG2RAD;

for (i=0;i<vertex_num;i++)
	{
	tmp[i].coord[0] = pivot.coord[0] + (furniture->polygon[i].coord[0]-pivot.coord[0])*cos(angle) 
                      - (furniture->polygon[i].coord[1]-pivot.coord[1])*sin(angle);
	tmp[i].coord[1] = pivot.coord[1] + (furniture->polygon[i].coord[0]-pivot.coord[0])*sin(angle) 
                      + (furniture->polygon[i].coord[1]-pivot.coord[1])*cos(angle);
	}

for (i=0;i<vertex_num;i++)
	{
	furniture->polygon[i].coord[0]=tmp[i].coord[0];
	furniture->polygon[i].coord[1]=tmp[i].coord[1];
	}
}



void rotateWall(struct vertex pivot,struct wall3D *one_wall, GLdouble angle)
{
int vertex_num=8;
vector<struct vertex> tmp(vertex_num);
int 		i;

for (i=0;i<vertex_num;i++)
	{
	tmp[i].coord[0] = pivot.coord[0] + (one_wall->points[i].coord[0]-pivot.coord[0])*cos(angle) 
                      - (one_wall->points[i].coord[1]-pivot.coord[1])*sin(angle);
	tmp[i].coord[1] = pivot.coord[1] + (one_wall->points[i].coord[0]-pivot.coord[0])*sin(angle) 
                      + (one_wall->points[i].coord[1]-pivot.coord[1])*cos(angle);
	}

for (i=0;i<vertex_num/2;i++)
	{
	one_wall->points[i].coord[0]=tmp[i].coord[0];
	one_wall->points[i].coord[1]=tmp[i].coord[1];
//	one_wall->points[i].coord[2]=0;
	}
for (;i<vertex_num;i++)
	{
	one_wall->points[i].coord[0]=tmp[i].coord[0];
	one_wall->points[i].coord[1]=tmp[i].coord[1];
//	one_wall->points[i].coord[2]=wall_height;
	}

}



void rotateRect(struct vertex pivot, GLdouble angle, GLint vertex_num)
{
vector<struct vertex> tmp(4);
int 		i;
angle=angle*DEG2RAD;

for (i=0;i<vertex_num;i++)
	{
	tmp[i].coord[0] = pivot.coord[0] + (my_rect[i].coord[0]-pivot.coord[0])*cos(angle) 
                      - (my_rect[i].coord[1]-pivot.coord[1])*sin(angle);
	tmp[i].coord[1] = pivot.coord[1] + (my_rect[i].coord[0]-pivot.coord[0])*sin(angle) 
                      + (my_rect[i].coord[1]-pivot.coord[1])*cos(angle);
	}

for (i=0;i<vertex_num;i++)
	{
	my_rect[i].coord[0]=tmp[i].coord[0];
	my_rect[i].coord[1]=tmp[i].coord[1];
	}
}



void doInsertRectangle() {
     state=2;
}



void scaleRect(struct vertex pivot, GLfloat sx, GLfloat sy, GLint vertex_num) {
vector<struct vertex> tmp(4);
int i;

for (i=0;i<vertex_num;i++)
	{
	tmp[i].coord[0] = my_rect[i].coord[0]*sx + pivot.coord[0]*(1-sx);
	tmp[i].coord[1] = my_rect[i].coord[1]*sy + pivot.coord[1]*(1-sy);
	}

for (i=0;i<vertex_num;i++)
	{
	my_rect[i].coord[0]=tmp[i].coord[0];
	my_rect[i].coord[1]=tmp[i].coord[1];
	}
}



void scaleRect(int value) {
    struct vertex den;
	den.coord[0]=(my_rect[0].coord[0]+my_rect[2].coord[0])/2;
	den.coord[1]=(my_rect[0].coord[1]+my_rect[2].coord[1])/2;
	den.coord[2]=0.0;
	scaleRect(den,scale_value,scale_value, 4);
	trans_type=0;
}



void scaleRect(struct vertex pivot, GLfloat sx, GLfloat sy, struct fur *furniture) {
int i,vertex_num=furniture->polygon.size();
vector<struct vertex> tmp(vertex_num);

for (i=0;i<vertex_num;i++)
	{
	tmp[i].coord[0] = furniture->polygon[i].coord[0]*sx + pivot.coord[0]*(1-sx);
	tmp[i].coord[1] = furniture->polygon[i].coord[1]*sy + pivot.coord[1]*(1-sy);
	}

for (i=0;i<vertex_num;i++)
	{
	furniture->polygon[i].coord[0]=tmp[i].coord[0];
	furniture->polygon[i].coord[1]=tmp[i].coord[1];
	}
}



void purgePolygon() {
     struct wall w;
     int a, b;
     walls.clear();
     for(a=0; a<my_poly.size(); a++) {
              b=(a+1)%my_poly.size();
              w.points.clear();
              w.points.push_back(my_poly[a]);
              w.points.push_back(my_poly[b]);
              walls.push_back(w);
     }
}



void callDrawPolygon (int value) {
 if (value==2) doMerge();
 if (value==3) doSubtract();
 if (value==5) rotateRect(value);
 if (value==6) scaleRect(value);
 if (value==7 &&  !state) doInsertRectangle();
 if (value==9) doDelete();
 if (value==10) { state=10; panel1->disable(); panelindoor->enable();}
 if (value==14) { state=11; new_wall.points.clear(); }
 if (value==11) { state=12; }
 if (value==12) { state=13; }
 if (value==50) { state=14; }
 if (value==20) { phase1Save(); }
 if (value==21) { phase1Load(); }
 if (value==100) { phase2Save(); }
 if (value==101) { phase2Load(); }
 if (value==200) { phase3Save(); }
 if (value==201) { phase3Load(); }
 if (value==400) { xx0=width/2; yy0=height/2; zz0=-10; xref=0; yref=height/3; zref=-20; vx=0; vy=0; vz=-1; inside=1; }
 if (value==401) { xx0=width/2; yy0=height/2; zz0=-300; xref=width/2; yref=height/2; zref=0; vx=0; vy=-1; vz=0; inside=0;}
 if (value==202) { strcpy(texture_name,texture_panel1->get_text()); } 
 if (value==203) { strcpy(wall_top_texture,texture_panel2->get_text()); } 
}



void callSpinners (int value){

}



int insidePoly(struct vertex v, vector<struct vertex> &poly) {
    int i, count=0, b;
    struct vertex v1, dummy, a;
    v1.coord[0]=v1.coord[1]=0;
    for(i=0; i<poly.size(); i++) {
             b=(i==poly.size()-1)?0:(i+1);
             if(lineIntersect(v1,v, poly[i], poly[b], &dummy)) count++;
    }
    return count%2;
}



void createPoly(vertex a, vertex b) {
     struct vertex v;
     int  i;
     double t,p, q, r, s;
     new_fur.polygon.clear();
     if(fur_type==0) {
       v.coord[0]=a.coord[0]+(b.coord[0]-a.coord[0])/2;
       v.coord[1]=a.coord[1];
       new_fur.polygon.push_back(v);
       v.coord[0]=a.coord[0];
       v.coord[1]=b.coord[1];
       new_fur.polygon.push_back(v);
       new_fur.polygon.push_back(b);
    }
     if(fur_type==1) {
       new_fur.polygon.push_back(a);
       v.coord[0]=b.coord[0];
       v.coord[1]=a.coord[1];
       new_fur.polygon.push_back(v);
       new_fur.polygon.push_back(b);
       v.coord[0]=a.coord[0];
       v.coord[1]=b.coord[1];
       new_fur.polygon.push_back(v);
    }
    if(fur_type==2) {
      p=(a.coord[0]+b.coord[0])/2; q=(a.coord[1]+b.coord[1])/2; 
      r=(b.coord[0]-a.coord[0])/2; s=(b.coord[1]-a.coord[1])/2;
      t=M_PI*2.0/50.0;
      for(i=0; i<50; i++) {
               v.coord[0]=p+cos(i*t)*r;
               v.coord[1]=q+sin(i*t)*s;
               new_fur.polygon.push_back(v);
      }
    }
}



int intersected() {
    int i, a, b;
    struct vertex int_point;
  for(i=0; i<walls.size(); i++) {
    for(a=0; a<(*holding_object).size(); a++)  {
             b=(a+1)%(*holding_object).size();
             if(lineIntersect(walls[i].points[0], walls[i].points[1], (*holding_object)[a], (*holding_object)[b], &int_point))
                                                  return 1;
    }             
  }
  return 0;
}



int ccw(struct vertex p0, struct vertex p1, struct vertex p2) {
    int dx1, dx2, dy1, dy2;
    dx1=(int)p1.coord[0]-(int)p0.coord[0]; dy1=(int)p1.coord[1]-(int)p0.coord[1];
    dx2=(int)p2.coord[0]-(int)p0.coord[0]; dy2=(int)p2.coord[1]-(int)p0.coord[1];
    if(dx1*dy2>dy1*dx2) return +1;
    if(dx1*dy2<dy1*dx2) return -1;
    if((dx1*dx2<0) || (dy1*dy2<0)) return -1;
    if((dx1*dx1+dy1*dy1) < (dx2*dx2+dy2*dy2)) return +1;
    return 0;
}



int lineIntersect(struct vertex v0,struct vertex v1,struct vertex v2,struct vertex v3,struct vertex *v4) {
float a1,b1,c1, a2,b2,c2, det_inv, m1,m2;  

if ((v1.coord[0]-v0.coord[0])!=0)
   m1 = (v1.coord[1]-v0.coord[1])/(v1.coord[0]-v0.coord[0]);
else
   m1 = (float)1e+10;
if ((v3.coord[0]-v2.coord[0])!=0)
   m2 = (v3.coord[1]-v2.coord[1])/(v3.coord[0]-v2.coord[0]);
else
   m2 = (float)1e+10;

a1 = m1;
a2 = m2;
b1 = -1;
b2 = -1;
c1 = (v0.coord[1]-m1*v0.coord[0]);
c2 = (v2.coord[1]-m2*v2.coord[0]);
det_inv = 1/(a1*b2 - a2*b1);

v4->coord[0]=((b1*c2 - b2*c1)*det_inv);
v4->coord[1]=((a2*c1 - a1*c2)*det_inv);

return ((ccw(v0, v1, v2)
        *ccw(v0, v1, v3)) <=0)
     &&((ccw(v2, v3, v0)
        *ccw(v2, v3, v1)) <=0);
}



void drawThickLine(struct vertex v1, struct vertex v2, int size) {
     int i, j;
     for(i=-size; i<size+1; i++)
          for(j=-size; j<size+1; j++)
                    drawLine(v1.coord[0]+i, v1.coord[1]+j, v2.coord[0]+i, v2.coord[1]+j);
     }

	 

GLuint renderPolygon() {
int i;
GLuint list_id = glGenLists(1);  
GLUtesselator *tobj = gluNewTess(); 

gluTessCallback(tobj, GLU_TESS_BEGIN, (TessFuncPtr)tessBeginCB);
gluTessCallback(tobj, GLU_TESS_END, (TessFuncPtr)tessEndCB);
gluTessCallback(tobj, GLU_TESS_ERROR, (TessFuncPtr)tessErrorCB);
gluTessCallback(tobj, GLU_TESS_VERTEX, (TessFuncPtr)tessVertexCB);

glNewList(list_id, GL_COMPILE);
glColor4f( 1.0, 1.0, 1.0 , 1.0);
	gluTessBeginPolygon(tobj, 0);                   
		gluTessBeginContour(tobj);
			for (i=0;i<my_poly.size();i++)
				gluTessVertex(tobj, my_poly[i].coord, my_poly[i].coord);
		gluTessEndContour(tobj);
	gluTessEndPolygon(tobj);
glEndList();

	gluDeleteTess(tobj);        

return list_id;     
}


///////////////////////////////////////////////////////////////////////////////
// GLU_TESS CALLBACKS
///////////////////////////////////////////////////////////////////////////////
void CALLBACK tessBeginCB(GLenum which)
{ glBegin(which); }


void CALLBACK tessEndCB()
{ glEnd(); }


void CALLBACK tessVertexCB(const GLvoid *data)
{ 
const GLdouble *ptr = (const GLdouble*)data;
glVertex3dv(ptr);
}


void CALLBACK tessErrorCB(GLenum errorCode)
{
const GLubyte *errorStr;
errorStr = gluErrorString(errorCode);
cerr << "[ERROR]: " << errorStr << endl;
}	
	
	
#endif
