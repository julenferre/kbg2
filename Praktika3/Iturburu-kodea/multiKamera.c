#include "definitions.h"
#include <GL/glut.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <stdio.h>
#include <math.h> /** cos eta sin **/

/** EXTERNAL VARIABLES **/

extern GLdouble _window_ratio;
extern GLdouble _ortho_x_min,_ortho_x_max;
extern GLdouble _ortho_y_min,_ortho_y_max;
extern GLdouble _ortho_z_min,_ortho_z_max;

extern object3d *_first_object;
extern object3d *_selected_object;

/** GLOBAL VARIABLES **/

extern object3d * trans_obj;                    /*Transformazioa jasango duen objektua*/

char kamera_mota = 'o';				//Orto,objektu-kamera,ibiltaria 			
char kamera_tmota= '\0';			//Biratu edo mugitu
char kamera_tardatza = '\0';			//X,Y,Z
char kamera_tnorabidea = '\0';			//+,-

extern char transf_helburua;

void orto_kam(){}

void obj_kam(){}

void ibil_kam(){}

void kamera_mota_aldatu(){

	if(kamera_mota == 'o') kamera_mota='b';
	else if(kamera_mota == 'b') kamera_mota='i';
	else if(kamera_mota == 'i') kamera_mota='o';

	switch(kamera_mota){

	case 'o':orto_kam(); 
		 break;

	case 'b':obj_kam(); 
      		 break;
	
	case 'i':ibil_kam(); 
		 break;


	}



}
