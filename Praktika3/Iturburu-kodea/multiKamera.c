#include "definitions.h"
#include <GL/glut.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <stdio.h>
#include <math.h> /* cos eta sin */
#include "multiMatrix.h"

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

extern kamera kamera1;

void kamera_mota_aldatu(){

	if(kamera_mota == 'o') kamera_mota='k';
	else if(kamera_mota == 'k') kamera_mota='i';
	else if(kamera_mota == 'i') kamera_mota='o';

	printf("Kamera mota: %c (o: ortografikoa, k: objektu-kamera, i: ibiltaria)\n",kamera_mota);
}

void kam_mugitu(){
    glMatrixMode(GL_PROJECTION);
	switch (kamera_tardatza){
		case 'X':
			if(kamera_tnorabidea=='+'){
				printf("Kamera Traslazioa: +X\n");
                kamera1.eyeX += KG_KAM_ABIAD_TRASL * kamera1.centerX;
                kamera1.eyeZ += KG_KAM_ABIAD_TRASL * kamera1.centerZ;
                kamera1.centerX += KG_KAM_ABIAD_TRASL * kamera1.centerX;
                kamera1.centerZ += KG_KAM_ABIAD_TRASL * kamera1.centerZ;
			}
			else{
				printf("Kamera Traslazioa: -X\n");
                kamera1.eyeX -= KG_KAM_ABIAD_TRASL * kamera1.centerX;
                kamera1.eyeZ -= KG_KAM_ABIAD_TRASL * kamera1.centerZ;
                kamera1.centerX -= KG_KAM_ABIAD_TRASL * kamera1.centerX;
                kamera1.centerZ -= KG_KAM_ABIAD_TRASL * kamera1.centerZ;
			}
			break;

		case 'Y':
			if(kamera_tnorabidea=='+'){
				printf("Kamera Traslazioa: +Y\n");
                kamera1.eyeX += KG_KAM_ABIAD_TRASL * kamera1.centerX;
                kamera1.eyeY += KG_KAM_ABIAD_TRASL * kamera1.centerY;
                kamera1.centerX += KG_KAM_ABIAD_TRASL * kamera1.centerX;
                kamera1.centerY += KG_KAM_ABIAD_TRASL * kamera1.centerY;
			}
			else{
				printf("Kamera Traslazioa: -Y\n");
                kamera1.eyeX -= KG_KAM_ABIAD_TRASL * kamera1.centerX;
                kamera1.eyeY -= KG_KAM_ABIAD_TRASL * kamera1.centerY;
                kamera1.centerX -= KG_KAM_ABIAD_TRASL * kamera1.centerX;
                kamera1.centerY -= KG_KAM_ABIAD_TRASL * kamera1.centerY;
			}
			break;

		case 'Z':
			if(kamera_tnorabidea=='+'){
				printf("Kamera Traslazioa: +Z\n");
                kamera1.eyeY += KG_KAM_ABIAD_TRASL * kamera1.centerY;
                kamera1.eyeZ += KG_KAM_ABIAD_TRASL * kamera1.centerZ;
                kamera1.centerY += KG_KAM_ABIAD_TRASL * kamera1.centerY;
                kamera1.centerZ += KG_KAM_ABIAD_TRASL * kamera1.centerZ;
			}
			else{
				printf("Kamera Traslazioa: -Z\n");
                kamera1.eyeY -= KG_KAM_ABIAD_TRASL * kamera1.centerY;
                kamera1.eyeZ -= KG_KAM_ABIAD_TRASL * kamera1.centerZ;
                kamera1.centerY -= KG_KAM_ABIAD_TRASL * kamera1.centerY;
                kamera1.centerZ -= KG_KAM_ABIAD_TRASL * kamera1.centerZ;
			}
			break;
	}
    glMatrixMode(GL_MODELVIEW);
}

void kam_biratu(){
    glMatrixMode(GL_PROJECTION);
	switch (kamera_tardatza){
		case 'X':
			if(kamera_tnorabidea=='+'){
				printf("Kamera Biraketa: +X\n");
                kamera1.birak += KG_KAM_ABIAD_BIRAK;
				kamera1.centerX = sin(kamera1.birak);
				kamera1.centerZ = cos(kamera1.birak)*(-1);
			}
			else{
				printf("Kamera Biraketa: -X\n");
                kamera1.birak -= KG_KAM_ABIAD_BIRAK;
                kamera1.centerX = sin(kamera1.birak);
                kamera1.centerZ = cos(kamera1.birak)*(-1);
			}
			break;

		case 'Y':
			if(kamera_tnorabidea=='+'){
				printf("Kamera Biraketa: +Y\n");
                kamera1.birak += KG_KAM_ABIAD_BIRAK;
                kamera1.centerX = sin(kamera1.birak);
                kamera1.centerY = cos(kamera1.birak)*(-1);
			}
			else{
				printf("Kamera Biraketa: -Y\n");
                kamera1.birak -= KG_KAM_ABIAD_BIRAK;
                kamera1.centerX = sin(kamera1.birak);
                kamera1.centerY = cos(kamera1.birak)*(-1);
			}
			break;

		case 'Z':
			if(kamera_tnorabidea=='+'){
				printf("Kamera Biraketa: +Z\n");
                kamera1.birak += KG_KAM_ABIAD_BIRAK;
                kamera1.centerY = sin(kamera1.birak);
                kamera1.centerZ = cos(kamera1.birak)*(-1);
			}
			else{
				printf("Kamera Biraketa: -Z\n");
                kamera1.birak -= KG_KAM_ABIAD_BIRAK;
                kamera1.centerY = sin(kamera1.birak);
                kamera1.centerZ = cos(kamera1.birak)*(-1);
			}
			break;
	}
    glMatrixMode(GL_MODELVIEW);
}
