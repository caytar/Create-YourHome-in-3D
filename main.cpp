#include "glut_funcs.cpp"


void 	changePhase (int value) {
if (phase==0)   
   {
  glDisable(GL_LIGHTING);
  glutSetWindow(phase2_window);
  glutHideWindow();
  glutSetWindow(phase3_window);
  glutHideWindow();  
  glutSetWindow(phase1_window);  
  glutShowWindow(); 
  glui_phase3->hide();
  glui_phase2->hide(); 
  glui->show();


   }    
         
if (phase==1)  
   {
  glDisable(GL_LIGHTING);
  glutSetWindow(phase1_window);
  glutHideWindow();
  glutSetWindow(phase3_window);
  glutHideWindow();         
  glutSetWindow(phase2_window);  
  glutShowWindow(); 
  glui->hide();
  glui_phase3->hide(); 
  glui_phase2->show();
   }            
if (phase==2)  
   {
  glutSetWindow(phase1_window);
  glutHideWindow();
  glutSetWindow(phase2_window);
  glutHideWindow();      
  glutSetWindow(phase3_window); 
  glutShowWindow();   
  glui->hide();      
  glui_phase2->hide();  
  glui_phase3->show();   
   
  create3dPoints();            
  enlightMe();        
           
  }   
}         
 
/**************************************** main() ********************/
int main(int argc, char* argv[])
{     
int i;

    origin.coord[0]=origin.coord[1]=0;
	
	letter[1]=0;
	
    status_poly[0].coord[0]=0;
    status_poly[0].coord[1]=height-20;
    status_poly[1].coord[0]=width;
    status_poly[1].coord[1]=height-20;
    status_poly[2].coord[0]=width; 
    status_poly[2].coord[1]=height;
    status_poly[3].coord[0]=0;
    status_poly[3].coord[1]=height;

    strcpy(texture_name,"wall0.bmp"); 
    strcpy(wall_top_texture,"wall1.bmp");  


	GLfloat sc,x,y,z;   
strcpy(fileName1,"POTTERY.3DS"); 	
sc1 = 10.0f;				
model1x = 220;				
model1y = 300;
model1z = 5; 

strcpy(fileName2,"PLANT.3DS"); 
sc2 = 1.0f;			  	
model2x = 400;				
model2y = 400;
model2z = 5; 

strcpy(fileName3,"WAGON.3DS"); 
sc3 = 0.5f;			  	
model3x = 700;				
model3y = 700;  
model3z = 46; 



// Phase 1 Window
  glutInit(&argc, argv);
  glutInitDisplayMode( GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH );
  glutInitWindowPosition(100,110);
  glutInitWindowSize(width,height);
  phase1_window = glutCreateWindow( "Phase 1 - (e1347160 - e1347459)");
  glViewport(0,0,width,height);
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  gluOrtho2D(0.0,width,height,0.0);
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();  
  glutDisplayFunc(phase1GlutDisplay );
  glutKeyboardFunc( phase1GlutKeyboard );
  glutMotionFunc( phase1GlutMotion );
  glutMouseFunc( phase1GlutMouse );
  glutIdleFunc(phase1GlutIdle);

 

// Phase 2 Window

  glutInitDisplayMode( GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH );
  glutInitWindowPosition(100,110);
  glutInitWindowSize(width,height);
  phase2_window = glutCreateWindow( "Phase2 :: KEYS: x0(ED) - y0(RF) - z0(TG)  ||  xref(ZX) - yref(CV) - zref(BN)");
  
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  gluPerspective(angle, ratio, dnear, dfar);

  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
  gluLookAt(xx0, yy0, zz0, xref, yref, zref, vx, vy, vz);   
          
  glutDisplayFunc( phase2GlutDisplay );          
  glutKeyboardFunc( phase2GlutKeyboard );                    
  glutMotionFunc( phase2GlutMotion );
  glutMouseFunc( phase2GlutMouse );
  glutIdleFunc(phase2GlutIdle);
  glutSetWindow(phase2_window);    
  glutHideWindow();  
        
 
// Phase 3 Window

	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH );
    glutInitWindowPosition(100,110); 
    glutInitWindowSize(width,height);
    phase3_window =	glutCreateWindow("Phase3->KEYS: Rotate(ED) - Translate(RF) - Scale(TG)");

setModels(fileName1,sc1,model1x,model1y,model1z,1); 
setModels(fileName2,sc2,model2x,model2y,model2z,2); 
setModels(fileName3,sc3,model3x,model3y,model3z,3); 


  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  gluPerspective(angle, ratio, dnear, dfar);

  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
  gluLookAt(xx0, yy0, zz0, xref, yref, zref, vx, vy, vz);      

	glutCreateMenu(ProcessMenuSelection);
	BuildMenu();
	glutSpecialFunc(KeyboardAction);    
	glutDisplayFunc(phase3GlutDisplay); 
    glutKeyboardFunc( phase3GlutKeyboard );
    glutMotionFunc( phase3GlutMotion );
    glutPassiveMotionFunc( GlutPassiveMotion );
    glutMouseFunc( phase3GlutMouse ); 
    glutIdleFunc(phase3GlutIdle);    
 
CurrentModel = &model01; 
RotateCurrentObj(90.0f,0.0f,0.0f); 
SetupRC();       
CurrentModel = &model02;
RotateCurrentObj(90.0f,0.0f,0.0f); 
SetupRC();        
CurrentModel = &model03;
RotateCurrentObj(90.0f,0.0f,0.0f); 
SetupRC();   
    
   

	//SetPositionOfCurrentObj(10.0f,-10.0f,10.0f);	//mevcut objenin (model01 global modeli) nereye konulacagi (degistirip deneyebilirsiniz)

	//RotateCurrentObj(90.0f,0.0f,0.0f);						//mevcut objenin (model01 global modeli) hangi eksen etrafinda 
																				//	ne kadar dondurulecegi (degistirip deneyebilirsiniz)
    


    glutSetWindow(phase3_window); 
    glutHideWindow();
    glutSetWindow(phase1_window);    
    glutShowWindow();

    list1 = renderPolygon ();   
  
GLUI_Master.set_glutKeyboardFunc( phase1GlutKeyboard );
GLUI_Master.set_glutMouseFunc( phase1GlutMouse );  

glui_phases = GLUI_Master.create_glui("Phases",0, 100, 10);
GLUI_RadioGroup *phase_radio = glui_phases->add_radiogroup(&phase,1,changePhase);
glui_phases->add_radiobutton_to_group(phase_radio, "Phase 1" );
glui_phases->add_radiobutton_to_group(phase_radio, "Phase 2" );
glui_phases->add_radiobutton_to_group(phase_radio, "Phase 3" ); 

glui_phase2 = GLUI_Master.create_glui("Phase 2 Controls",0, 810, 10);
GLUI_Panel *ph2_panel = glui_phase2->add_panel ( "Data" ); 
glui_phase2->add_button_to_panel(ph2_panel, "Save", 100 , callDrawPolygon );
glui_phase2->add_column_to_panel(ph2_panel,false);
glui_phase2->add_button_to_panel(ph2_panel,"Load", 101 , callDrawPolygon );
GLUI_Panel *ph2_dims = glui_phase2->add_panel ("Wall Dimensions" );
GLUI_Spinner *wall_w = glui_phase2->add_spinner_to_panel( ph2_dims , "Width:",GLUI_SPINNER_INT, &wall_width , 100 , callSpinners);
wall_w->set_int_limits(3, 50);
glui_phase2->add_column_to_panel(ph2_dims,false);
GLUI_Spinner *wall_h = glui_phase2->add_spinner_to_panel( ph2_dims , "Height:",GLUI_SPINNER_INT, &wall_height , 101 , callSpinners);
wall_h->set_int_limits(10, 200);
glui_phase2->add_button("Go Inside", 400 , callDrawPolygon );
glui_phase2->add_button("Go Outside", 401 , callDrawPolygon );
glui_phase2->hide();

glui_phase3 = GLUI_Master.create_glui("Phase 3 Controls",0, 810, 10);
GLUI_Panel *ph3_panel = glui_phase3->add_panel ( "Data" ); 
glui_phase3->add_button_to_panel(ph3_panel, "Save", 200 , callDrawPolygon );
glui_phase3->add_column_to_panel(ph3_panel,false);
glui_phase3->add_button_to_panel(ph3_panel,"Load", 201 , callDrawPolygon );

GLUI_Rollout *ph3_light0 = glui_phase3->add_rollout("Light-0",false ); 
GLUI_Panel *ph3_light01 = glui_phase3->add_panel_to_panel ( ph3_light0,"" ); 
GLUI_Spinner *l0_x = glui_phase3->add_spinner_to_panel( ph3_light01 , "x:",GLUI_SPINNER_FLOAT, &light0x , 2 , callSpinners);
l0_x->set_float_limits(-1000.0, 1000.0);
GLUI_Spinner *l0_y = glui_phase3->add_spinner_to_panel( ph3_light01 , "y:",GLUI_SPINNER_FLOAT, &light0y , 2 , callSpinners);
l0_y->set_float_limits(-1000.0, 1000.0);
GLUI_Spinner *l0_z = glui_phase3->add_spinner_to_panel( ph3_light01 , "z:",GLUI_SPINNER_FLOAT, &light0z , 2 , callSpinners);
l0_z->set_float_limits(-1000.0, 1000.0);
glui_phase3->add_column_to_panel(ph3_light01,false); 
GLUI_Spinner *att0_cons = glui_phase3->add_spinner_to_panel( ph3_light01 , "Attenuation Cons:",GLUI_SPINNER_FLOAT, &atten0_cons , 2 , callSpinners);
att0_cons->set_float_limits(0.0, 100.0);
GLUI_Spinner *att0_lin = glui_phase3->add_spinner_to_panel( ph3_light01 , "Attenuation Lin:",GLUI_SPINNER_FLOAT, &atten0_lin , 2 , callSpinners);
att0_lin->set_float_limits(0.0, 100.0);
GLUI_Spinner *att0_quad = glui_phase3->add_spinner_to_panel( ph3_light01 , "Attenuation Quad:",GLUI_SPINNER_FLOAT, &atten0_quad , 2 , callSpinners);
att0_quad->set_float_limits(0.0, 50.0);

GLUI_Panel *ph3_light02 = glui_phase3->add_panel_to_panel ( ph3_light0,"" ); 
GLUI_Spinner *ambi0_x = glui_phase3->add_spinner_to_panel( ph3_light02 , "Ambience R:",GLUI_SPINNER_FLOAT, &amb0_r , 2 , callSpinners);
ambi0_x->set_float_limits(0.0, 1.0);
GLUI_Spinner *ambi0_y = glui_phase3->add_spinner_to_panel( ph3_light02 , "Ambience G:",GLUI_SPINNER_FLOAT, &amb0_g , 2 , callSpinners);
ambi0_y->set_float_limits(0.0, 1.0);
GLUI_Spinner *ambi0_z = glui_phase3->add_spinner_to_panel( ph3_light02 , "Ambience Z:",GLUI_SPINNER_FLOAT, &amb0_b , 2 , callSpinners);
ambi0_z->set_float_limits(0.0, 1.0);
/*
glui_phase3->add_column_to_panel(ph3_light02,false); 
GLUI_Spinner *diff0_cons = glui_phase3->add_spinner_to_panel( ph3_light02 , "Diffuse R:",GLUI_SPINNER_FLOAT, &dif0_r , 2 , callSpinners);
diff0_cons->set_float_limits(0.0, 1.0);
GLUI_Spinner *diff0_lin = glui_phase3->add_spinner_to_panel( ph3_light02 , "Diffuse G:",GLUI_SPINNER_FLOAT, &dif0_g , 2 , callSpinners);
diff0_lin->set_float_limits(0.0, 1.0);
GLUI_Spinner *diff0_quad = glui_phase3->add_spinner_to_panel( ph3_light02 , "Diffuse B:",GLUI_SPINNER_FLOAT, &dif0_b , 2 , callSpinners);
diff0_quad->set_float_limits(0.0, 1.0);
*/

GLUI_Rollout *ph3_light1 = glui_phase3->add_rollout("Light-1",false ); 
GLUI_Panel *ph3_light11 = glui_phase3->add_panel_to_panel ( ph3_light1,"" ); 
GLUI_Spinner *l1_x = glui_phase3->add_spinner_to_panel( ph3_light11 , "x:",GLUI_SPINNER_FLOAT, &light1x , 2 , callSpinners);
l1_x->set_float_limits(-1000.0, 1000.0);
GLUI_Spinner *l1_y = glui_phase3->add_spinner_to_panel( ph3_light11 , "y:",GLUI_SPINNER_FLOAT, &light1y , 2 , callSpinners);
l1_y->set_float_limits(-1000.0, 1000.0);
GLUI_Spinner *l1_z = glui_phase3->add_spinner_to_panel( ph3_light11 , "z:",GLUI_SPINNER_FLOAT, &light1z , 2 , callSpinners);
l1_z->set_float_limits(-1000.0, 1000.0);
glui_phase3->add_column_to_panel(ph3_light11,false); 
GLUI_Spinner *att1_cons = glui_phase3->add_spinner_to_panel( ph3_light11 , "Attenuation Cons:",GLUI_SPINNER_FLOAT, &atten1_cons , 2 , callSpinners);
att1_cons->set_float_limits(0.0, 100.0);
GLUI_Spinner *att1_lin = glui_phase3->add_spinner_to_panel( ph3_light11 , "Attenuation Lin:",GLUI_SPINNER_FLOAT, &atten1_lin , 2 , callSpinners);
att1_lin->set_float_limits(0.0, 100.0);
GLUI_Spinner *att1_quad = glui_phase3->add_spinner_to_panel( ph3_light11 , "Attenuation Quad:",GLUI_SPINNER_FLOAT, &atten1_quad , 2 , callSpinners);
att1_quad->set_float_limits(0.0, 50.0);
 
GLUI_Panel *ph3_light12 = glui_phase3->add_panel_to_panel ( ph3_light1,"" ); 
/*
GLUI_Spinner *ambi1_x = glui_phase3->add_spinner_to_panel( ph3_light12 , "Ambience R:",GLUI_SPINNER_FLOAT, &amb1_r , 2 , callSpinners);
ambi1_x->set_float_limits(0.0, 1.0);
GLUI_Spinner *ambi1_y = glui_phase3->add_spinner_to_panel( ph3_light12 , "Ambience G:",GLUI_SPINNER_FLOAT, &amb1_g , 2 , callSpinners);
ambi1_y->set_float_limits(0.0, 1.0);
GLUI_Spinner *ambi1_z = glui_phase3->add_spinner_to_panel( ph3_light12 , "Ambience Z:",GLUI_SPINNER_FLOAT, &amb1_b , 2 , callSpinners);
ambi1_z->set_float_limits(0.0, 1.0);
glui_phase3->add_column_to_panel(ph3_light12,false); 
*/
GLUI_Spinner *diff1_cons = glui_phase3->add_spinner_to_panel( ph3_light12 , "Diffuse R:",GLUI_SPINNER_FLOAT, &dif1_r , 2 , callSpinners);
diff1_cons->set_float_limits(0.0, 1.0);
GLUI_Spinner *diff1_lin = glui_phase3->add_spinner_to_panel( ph3_light12 , "Diffuse G:",GLUI_SPINNER_FLOAT, &dif1_g , 2 , callSpinners);
diff1_lin->set_float_limits(0.0, 1.0);
GLUI_Spinner *diff1_quad = glui_phase3->add_spinner_to_panel( ph3_light12 , "Diffuse B:",GLUI_SPINNER_FLOAT, &dif1_b , 2 , callSpinners);
diff1_quad->set_float_limits(0.0, 1.0);



GLUI_Rollout *ph3_light2 = glui_phase3->add_rollout("Light-2 (SPOT)",false ); 
GLUI_Panel *ph3_light21 = glui_phase3->add_panel_to_panel ( ph3_light2,"" ); 
GLUI_Spinner *l2_x = glui_phase3->add_spinner_to_panel( ph3_light21 , "x:",GLUI_SPINNER_FLOAT, &light2x , 2 , callSpinners);
l2_x->set_float_limits(-1000.0, 1000.0);
GLUI_Spinner *l2_y = glui_phase3->add_spinner_to_panel( ph3_light21 , "y:",GLUI_SPINNER_FLOAT, &light2y , 2 , callSpinners);
l2_y->set_float_limits(-1000.0, 1000.0);
GLUI_Spinner *l2_z = glui_phase3->add_spinner_to_panel( ph3_light21 , "z:",GLUI_SPINNER_FLOAT, &light2z , 2 , callSpinners);
l2_z->set_float_limits(-1000.0, 1000.0);
glui_phase3->add_column_to_panel(ph3_light21,false); 
GLUI_Spinner *att2_cons = glui_phase3->add_spinner_to_panel( ph3_light21 , "Attenuation Cons:",GLUI_SPINNER_FLOAT, &atten2_cons , 2 , callSpinners);
att2_cons->set_float_limits(0.0, 100.0);
GLUI_Spinner *att2_lin = glui_phase3->add_spinner_to_panel( ph3_light21 , "Attenuation Lin:",GLUI_SPINNER_FLOAT, &atten2_lin , 2 , callSpinners);
att2_lin->set_float_limits(0.0, 100.0);
GLUI_Spinner *att2_quad = glui_phase3->add_spinner_to_panel( ph3_light21 , "Attenuation Quad:",GLUI_SPINNER_FLOAT, &atten2_quad , 2 , callSpinners);
att2_quad->set_float_limits(0.0, 50.0);
/* 
GLUI_Panel *ph3_light22 = glui_phase3->add_panel_to_panel ( ph3_light2,"" ); 
GLUI_Spinner *ambi2_x = glui_phase3->add_spinner_to_panel( ph3_light22 , "Ambience R:",GLUI_SPINNER_FLOAT, &amb2_r , 2 , callSpinners);
ambi2_x->set_float_limits(0.0, 1.0);
GLUI_Spinner *ambi2_y = glui_phase3->add_spinner_to_panel( ph3_light22 , "Ambience G:",GLUI_SPINNER_FLOAT, &amb2_g , 2 , callSpinners);
ambi2_y->set_float_limits(0.0, 1.0);
GLUI_Spinner *ambi2_z = glui_phase3->add_spinner_to_panel( ph3_light22 , "Ambience Z:",GLUI_SPINNER_FLOAT, &amb2_b , 2 , callSpinners);
ambi2_z->set_float_limits(0.0, 1.0);
glui_phase3->add_column_to_panel(ph3_light22,false); 
GLUI_Spinner *diff2_cons = glui_phase3->add_spinner_to_panel( ph3_light22 , "Diffuse R:",GLUI_SPINNER_FLOAT, &dif2_r , 2 , callSpinners);
diff2_cons->set_float_limits(0.0, 1.0);
GLUI_Spinner *diff2_lin = glui_phase3->add_spinner_to_panel( ph3_light22 , "Diffuse G:",GLUI_SPINNER_FLOAT, &dif2_g , 2 , callSpinners);
diff2_lin->set_float_limits(0.0, 1.0);
GLUI_Spinner *diff2_quad = glui_phase3->add_spinner_to_panel( ph3_light22 , "Diffuse B:",GLUI_SPINNER_FLOAT, &dif2_b , 2 , callSpinners);
diff2_quad->set_float_limits(0.0, 1.0);
*/ 
GLUI_Panel *ph3_light23 = glui_phase3->add_panel_to_panel ( ph3_light2,"" ); 
GLUI_Spinner *sp_x = glui_phase3->add_spinner_to_panel( ph3_light23 , "Direction-x:",GLUI_SPINNER_FLOAT, &spot_x , 2 , callSpinners);
sp_x->set_float_limits(-1.0, 1.0);
GLUI_Spinner *sp_y = glui_phase3->add_spinner_to_panel( ph3_light23 , "Direction-y:",GLUI_SPINNER_FLOAT, &spot_y , 2 , callSpinners);
sp_y->set_float_limits(-1.0, 1.0);
GLUI_Spinner *sp_z = glui_phase3->add_spinner_to_panel( ph3_light23 , "Direction-z:",GLUI_SPINNER_FLOAT, &spot_z , 2 , callSpinners);
sp_z->set_float_limits(-1.0, 1.0);
glui_phase3->add_column_to_panel(ph3_light23,false); 
GLUI_Spinner *sp_exp = glui_phase3->add_spinner_to_panel( ph3_light23 , "Exponential:",GLUI_SPINNER_FLOAT, &spot_exp , 2 , callSpinners);
sp_exp->set_float_limits(0.0, 10.0);
GLUI_Spinner *sp_ang = glui_phase3->add_spinner_to_panel( ph3_light23 , "Angle:",GLUI_SPINNER_FLOAT, &spot_angle , 2 , callSpinners);
sp_ang->set_float_limits(0.0, 120.0);


GLUI_Rollout *ph3_textures = glui_phase3->add_rollout("Textures",false ); 
GLUI_Panel *ph3_textures1 = glui_phase3->add_panel_to_panel (ph3_textures, "Texture of Wall" ); 
GLUI_Spinner *t1_x1 = glui_phase3->add_spinner_to_panel( ph3_textures1 , "x1:",GLUI_SPINNER_FLOAT, &tex1_x1 , 2 , callSpinners);
t1_x1->set_float_limits(0.0, 1.0);
GLUI_Spinner *t1_y1 = glui_phase3->add_spinner_to_panel( ph3_textures1 , "y1:",GLUI_SPINNER_FLOAT, &tex1_y1 , 2 , callSpinners);
t1_y1->set_float_limits(0.0, 1.0);
GLUI_Spinner *t1_x2 = glui_phase3->add_spinner_to_panel( ph3_textures1 , "x2:",GLUI_SPINNER_FLOAT, &tex1_x2 , 2 , callSpinners);
t1_x2->set_float_limits(0.0, 1.0);
GLUI_Spinner *t1_y2 = glui_phase3->add_spinner_to_panel( ph3_textures1 , "y2:",GLUI_SPINNER_FLOAT, &tex1_y2 , 2 , callSpinners);
t1_y2->set_float_limits(0.0, 1.0);
glui_phase3->add_column_to_panel(ph3_textures1,false);
texture_panel1=glui_phase3->add_edittext_to_panel(ph3_textures1,"File Name:",GLUI_EDITTEXT_TEXT,tex_str,-101,callDrawPolygon); 
glui_phase3->add_button_to_panel(ph3_textures1, "Import", 202 , callDrawPolygon );
GLUI_Panel *ph3_textures2 = glui_phase3->add_panel_to_panel (ph3_textures, "Texture of Ceiling" );   
GLUI_Spinner *t2_x1 = glui_phase3->add_spinner_to_panel( ph3_textures2 , "x1:",GLUI_SPINNER_FLOAT, &tex2_x1 , 2 , callSpinners);
t2_x1->set_float_limits(0.0, 1.0);
GLUI_Spinner *t2_y1 = glui_phase3->add_spinner_to_panel( ph3_textures2 , "y1:",GLUI_SPINNER_FLOAT, &tex2_y1 , 2 , callSpinners);
t2_y1->set_float_limits(0.0, 1.0);
GLUI_Spinner *t2_x2 = glui_phase3->add_spinner_to_panel( ph3_textures2 , "x2:",GLUI_SPINNER_FLOAT, &tex2_x2 , 2 , callSpinners);
t2_x2->set_float_limits(0.0, 1.0);
GLUI_Spinner *t2_y2 = glui_phase3->add_spinner_to_panel( ph3_textures2 , "y2:",GLUI_SPINNER_FLOAT, &tex2_y2 , 2 , callSpinners);
t2_y2->set_float_limits(0.0, 1.0);
glui_phase3->add_column_to_panel(ph3_textures2,false);
texture_panel2=glui_phase3->add_edittext_to_panel(ph3_textures2,"File Name:",GLUI_EDITTEXT_TEXT,tex2_str,-100,callDrawPolygon); 
glui_phase3->add_button_to_panel(ph3_textures2, "Import", 203 , callDrawPolygon ); 
          



GLUI_Rollout *ph3_3dmodels = glui_phase3->add_rollout("3D Models",false ); 
  GLUI_RadioGroup *group3d = glui_phase3->add_radiogroup_to_panel(ph3_3dmodels,&model_num,700,callDrawPolygon);
  glui_phase3->add_radiobutton_to_group( group3d, "Pottery" );
  glui_phase3->add_radiobutton_to_group( group3d, "Plant" );
  glui_phase3->add_radiobutton_to_group( group3d, "Wagon" );

glui_phase3->add_column_to_panel(ph3_3dmodels,false);
  GLUI_RadioGroup *group3dd = glui_phase3->add_radiogroup_to_panel(ph3_3dmodels,&model_dir,701,callDrawPolygon);
  glui_phase3->add_radiobutton_to_group( group3dd, "X" );
  glui_phase3->add_radiobutton_to_group( group3dd, "Y" );
  glui_phase3->add_radiobutton_to_group( group3dd, "Z" );

glui_phase3->hide();       
  
  glui = GLUI_Master.create_glui("Phase 1 Controls",0, 810, 10);
  GLUI_Panel *paneldata = glui->add_panel ( "Data" ); 
  glui->add_button_to_panel(paneldata, "Save", 20 , callDrawPolygon );
  glui->add_column_to_panel(paneldata,false);
  glui->add_button_to_panel(paneldata,"Load", 21 , callDrawPolygon );
  GLUI_Panel *panel0 = glui->add_panel ( "Grid" ); 
  GLUI_Spinner *grid_spinner = glui->add_spinner_to_panel(panel0,"Size",GLUI_SPINNER_INT, &grid_size , 3 , callSpinners);
  grid_spinner->set_int_limits(5, 30);
  glui->add_column_to_panel(panel0,true);
  glui->add_checkbox_to_panel(panel0, "Show", &show_grid, -1, callDrawPolygon);
  panelroom = glui->add_rollout("Room Design (Step 1)", 1);
  panel1 = glui->add_panel_to_panel (panelroom, "Rectangle" );
  GLUI_Panel *panelinsert = glui->add_panel_to_panel (panel1, "Add/Remove" ); 
  glui->add_button_to_panel(panelinsert, "Insert", 7 , callDrawPolygon );
  glui->add_column_to_panel(panelinsert,false);
  glui->add_button_to_panel(panelinsert,"Delete", 9 , callDrawPolygon );
  GLUI_Panel *panelex = glui->add_panel_to_panel (panel1, "Actions" );
  glui->add_button_to_panel(panelex, "Merge", 2 , callDrawPolygon );  
  glui->add_column_to_panel(panelex,false);
  glui->add_button_to_panel(panelex, "Subtract", 3 , callDrawPolygon );
  GLUI_Panel *panelr = glui->add_panel_to_panel (panel1, "Rotate" );
  GLUI_Spinner *rotate_spinner = glui->add_spinner_to_panel( panelr , "",GLUI_SPINNER_INT, &rotate_value , 1 , callSpinners);
  rotate_spinner->set_int_limits(0, 360);
  glui->add_column_to_panel(panelr,false);
  glui->add_button_to_panel(panelr, "Rotate", 5 , callDrawPolygon );
  GLUI_Panel *panels = glui->add_panel_to_panel (panel1, "Scale" );
  GLUI_Spinner *scale_spinner = glui->add_spinner_to_panel( panels , "",GLUI_SPINNER_FLOAT, &scale_value , 2 , callSpinners);
  scale_spinner->set_float_limits(0.1, 10.0);
  glui->add_column_to_panel(panels,false);
  glui->add_button_to_panel(panels, "Scale", 6 , callDrawPolygon );
  GLUI_Button *dene = glui->add_button_to_panel(panelroom, "DONE", 10 , callDrawPolygon );
  panelindoor = glui->add_rollout("Indoor Design (Step 2)", 1);  
  panelindoor->disable();
  GLUI_Panel *panel3 = glui->add_panel_to_panel (panelindoor, "Insert Indoor Elements" );
  glui->add_button_to_panel(panel3, "Wall", 14 , callDrawPolygon );
  glui->add_column_to_panel(panel3,false);
  glui->add_button_to_panel(panel3, "Door", 11 , callDrawPolygon );
  glui->add_column_to_panel(panel3,false);  
  glui->add_button_to_panel(panel3, "Window", 12 , callDrawPolygon );
  glui->add_column_to_panel(panel3,false);
  GLUI_Panel *panel4 = glui->add_panel_to_panel (panelindoor, "Furniture" );
  GLUI_Panel *panel5 = glui->add_panel_to_panel (panel4, "Color" );
  GLUI_Spinner *red_spinner = glui->add_spinner_to_panel(panel5,"Red",GLUI_SPINNER_FLOAT,&red_value,4,callSpinners);
  red_spinner->set_float_limits(0.0, 1.0);
  GLUI_Spinner *green_spinner = glui->add_spinner_to_panel(panel5,"Green",GLUI_SPINNER_FLOAT,&green_value,5,callSpinners);
  green_spinner->set_float_limits(0.0, 1.0);
  GLUI_Spinner *blue_spinner = glui->add_spinner_to_panel(panel5,"Blue",GLUI_SPINNER_FLOAT,&blue_value,6,callSpinners);
  blue_spinner->set_float_limits(0.0, 1.0);
  glui->add_column_to_panel(panel4,false);
  GLUI_Panel *panel6 = glui->add_panel_to_panel (panel4, "Type" );
  GLUI_RadioGroup *group2 = glui->add_radiogroup_to_panel(panel6,&fur_type,31,callDrawPolygon);
  glui->add_radiobutton_to_group( group2, "Triangle" );
  glui->add_radiobutton_to_group( group2, "Rectangle" );
  glui->add_radiobutton_to_group( group2, "Circle" );
  glui->add_button_to_panel(panel6, "Insert", 50 , callDrawPolygon );
   
  glui->set_main_gfx_window( phase1_window ); 
  glui_phases->set_main_gfx_window( phase1_window );
  glui_phase2->set_main_gfx_window( phase2_window ); 
  glui_phase3->set_main_gfx_window( phase3_window );
  GLUI_Master.set_glutIdleFunc( phase3GlutIdle ); 
  glutMainLoop();
} 

