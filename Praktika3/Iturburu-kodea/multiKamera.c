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

char kamera_mota = 'o';							//Orto,objektu-kamera,ibiltaria
char kamera_tmota= '\0';						//Biratu edo mugitu
char kamera_tardatza = '\0';					//X,Y,Z
char kamera_tnorabidea = '\0';					//+,-

extern char transf_helburua;

/**
 * @brief Matrizeak biderkatzeko metodoa
 * @param m1 Biderkadurako ezkerreko matrizea
 * @param m2 Biderkadurako eskuineko matrizea
 * @return GLdouble motako matrizea, m1Xm2-ren emaitza
 */
GLdouble *mult(GLdouble *m1, GLdouble *m2) {
	GLdouble *result = malloc(sizeof(GLdouble) * 4 * 4);
	// @formatter:off
	result[0+4*0]=m1[0+4*0]*m2[0+4*0]+m1[0+4*1]*m2[1+4*0]+m1[0+4*2]*m2[2+4*0]+m1[0+4*3]*m2[3+4*0];
	result[1+4*0]=m1[1+4*0]*m2[0+4*0]+m1[1+4*1]*m2[1+4*0]+m1[1+4*2]*m2[2+4*0]+m1[1+4*3]*m2[3+4*0];
	result[2+4*0]=m1[2+4*0]*m2[0+4*0]+m1[2+4*1]*m2[1+4*0]+m1[2+4*2]*m2[2+4*0]+m1[2+4*3]*m2[3+4*0];
	result[3+4*0]=m1[3+4*0]*m2[0+4*0]+m1[3+4*1]*m2[1+4*0]+m1[3+4*2]*m2[2+4*0]+m1[3+4*3]*m2[3+4*0];

	result[0+4*1]=m1[0+4*0]*m2[0+4*1]+m1[0+4*1]*m2[1+4*1]+m1[0+4*2]*m2[2+4*1]+m1[0+4*3]*m2[3+4*1];
	result[1+4*1]=m1[1+4*0]*m2[0+4*1]+m1[1+4*1]*m2[1+4*1]+m1[1+4*2]*m2[2+4*1]+m1[1+4*3]*m2[3+4*1];
	result[2+4*1]=m1[2+4*0]*m2[0+4*1]+m1[2+4*1]*m2[1+4*1]+m1[2+4*2]*m2[2+4*1]+m1[2+4*3]*m2[3+4*1];
	result[3+4*1]=m1[3+4*0]*m2[0+4*1]+m1[3+4*1]*m2[1+4*1]+m1[3+4*2]*m2[2+4*1]+m1[3+4*3]*m2[3+4*1];

	result[0+4*2]=m1[0+4*0]*m2[0+4*2]+m1[0+4*1]*m2[1+4*2]+m1[0+4*2]*m2[2+4*2]+m1[0+4*3]*m2[3+4*2];
	result[1+4*2]=m1[1+4*0]*m2[0+4*2]+m1[1+4*1]*m2[1+4*2]+m1[1+4*2]*m2[2+4*2]+m1[1+4*3]*m2[3+4*2];
	result[2+4*2]=m1[2+4*0]*m2[0+4*2]+m1[2+4*1]*m2[1+4*2]+m1[2+4*2]*m2[2+4*2]+m1[2+4*3]*m2[3+4*2];
	result[3+4*2]=m1[3+4*0]*m2[0+4*2]+m1[3+4*1]*m2[1+4*2]+m1[3+4*2]*m2[2+4*2]+m1[3+4*3]*m2[3+4*2];

	result[0+4*3]=m1[0+4*0]*m2[0+4*3]+m1[0+4*1]*m2[1+4*3]+m1[0+4*2]*m2[2+4*3]+m1[0+4*3]*m2[3+4*3];
	result[1+4*3]=m1[1+4*0]*m2[0+4*3]+m1[1+4*1]*m2[1+4*3]+m1[1+4*2]*m2[2+4*3]+m1[1+4*3]*m2[3+4*3];
	result[2+4*3]=m1[2+4*0]*m2[0+4*3]+m1[2+4*1]*m2[1+4*3]+m1[2+4*2]*m2[2+4*3]+m1[2+4*3]*m2[3+4*3];
	result[3+4*3]=m1[3+4*0]*m2[0+4*3]+m1[3+4*1]*m2[1+4*3]+m1[3+4*2]*m2[2+4*3]+m1[3+4*3]*m2[3+4*3];
	// @formatter:on
	return result;
}

void traslazioa(){
	GLdouble  * trasX = malloc ( sizeof ( GLdouble )*16);
	trasX [0]=1; trasX [4]=0; trasX [8] =0; trasX [12]=KG_KAM_ABIAD_TRASL;
	trasX [1]=0; trasX [5]=1; trasX [9] =0; trasX [13]=0;
	trasX [2]=0; trasX [6]=0; trasX [10]=1; trasX [14]=0;
	trasX [3]=0; trasX [7]=0; trasX [11]=0; trasX [15]=1;

	GLdouble  * trasY = malloc ( sizeof ( GLdouble )*16);
	trasY [0]=1; trasY [4]=0; trasY [8] =0; trasY [12]=0;
	trasY [1]=0; trasY [5]=1; trasY [9] =0; trasY [13]=KG_KAM_ABIAD_TRASL;
	trasY [2]=0; trasY [6]=0; trasY [10]=1; trasY [14]=0;
	trasY [3]=0; trasY [7]=0; trasY [11]=0; trasY [15]=1;

	GLdouble  * trasZ = malloc ( sizeof ( GLdouble )*16);
	trasZ [0]=1; trasZ [4]=0; trasZ [8] =0; trasZ [12]=0;
	trasZ [1]=0; trasZ [5]=1; trasZ [9] =0; trasZ [13]=0;
	trasZ [2]=0; trasZ [6]=0; trasZ [10]=1; trasZ [14]=KG_KAM_ABIAD_TRASL;
	trasZ [3]=0; trasZ [7]=0; trasZ [11]=0; trasZ [15]=1;

	GLdouble  * trasXn = malloc ( sizeof ( GLdouble )*16);
	trasXn [0]=1; trasXn [4]=0; trasXn [8] =0; trasXn [12]=KG_KAM_ABIAD_TRASL*(-1);
	trasXn [1]=0; trasXn [5]=1; trasXn [9] =0; trasXn [13]=0;
	trasXn [2]=0; trasXn [6]=0; trasXn [10]=1; trasXn [14]=0;
	trasXn [3]=0; trasXn [7]=0; trasXn [11]=0; trasXn [15]=1;

	GLdouble  * trasYn = malloc ( sizeof ( GLdouble )*16);
	trasYn [0]=1; trasYn [4]=0; trasYn [8] =0; trasYn [12]=0;
	trasYn [1]=0; trasYn [5]=1; trasYn [9] =0; trasYn [13]=KG_KAM_ABIAD_TRASL*(-1);
	trasYn [2]=0; trasYn [6]=0; trasYn [10]=1; trasYn [14]=0;
	trasYn [3]=0; trasYn [7]=0; trasYn [11]=0; trasYn [15]=1;

	GLdouble  * trasZn = malloc ( sizeof ( GLdouble )*16);
	trasZn [0]=1; trasZn [4]=0; trasZn [8] =0; trasZn [12]=0;
	trasZn [1]=0; trasZn [5]=1; trasZn [9] =0; trasZn [13]=0;
	trasZn [2]=0; trasZn [6]=0; trasZn [10]=1; trasZn [14]=KG_KAM_ABIAD_TRASL*(-1);
	trasZn [3]=0; trasZn [7]=0; trasZn [11]=0; trasZn [15]=1;

	switch (transf_ardatza){
		case 'X':
			if(transf_norabidea=='+'){
				printf("Traslazioa: +X\n");
				_selected_object->matrix=mult(_selected_object->matrix,trasX);
			}
			else{
				printf("Traslazioa: -X\n");
				_selected_object->matrix=mult(_selected_object->matrix,trasXn);
			}
			break;

		case 'Y':
			if(transf_norabidea=='+'){
				printf("Traslazioa: +Y\n");
				_selected_object->matrix=mult(_selected_object->matrix,trasY);
			}
			else{
				printf("Traslazioa: -Y\n");
				_selected_object->matrix=mult(_selected_object->matrix,trasYn);
			}
			break;

		case 'Z':
			if(transf_norabidea=='+'){
				printf("Traslazioa: +Z\n");
				_selected_object->matrix=mult(_selected_object->matrix,trasZ);
			}
			else{
				printf("Traslazioa: -Z\n");
				_selected_object->matrix=mult(_selected_object->matrix,trasZn);
			}
			break;
	}
}//void traslazioa()

void orto_kam(){}

void obj_kam(){}

void ibil_kam(){}

void kamera_mota_aldatu(){

	if(kamera_mota == 'o') kamera_mota='k';
	else if(kamera_mota == 'k') kamera_mota='i';
	else if(kamera_mota == 'i') kamera_mota='o';

	printf("Kamera mota: %c (o: ortografikoa, k: objektu-kamera, i: ibiltaria)\n",kamera_mota);

	switch(kamera_mota){
		case 'o':
			orto_kam();
			break;

		case 'k':
			obj_kam();
			break;

		case 'i':
			ibil_kam();
			break;
	}
}
