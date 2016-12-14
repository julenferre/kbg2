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

extern kamera * kamera1;

GLfloat * sum(GLfloat *m1, GLfloat *m2){
    GLfloat *result = malloc(sizeof(GLfloat) * 4 * 4);
    for (int i = 0; i < 16; i++){
        result[i] = m1[i] + m2[i];
    }

    return result;
}

void kamera_mota_aldatu(){

	if(kamera_mota == 'o') kamera_mota='k';
	else if(kamera_mota == 'k') kamera_mota='i';
	else if(kamera_mota == 'i') kamera_mota='o';

	printf("Kamera mota: %c (o: ortografikoa, k: objektu-kamera, i: ibiltaria)\n",kamera_mota);
}

void kam_mugitu(){
    GLfloat  * trasX = malloc ( sizeof ( GLfloat )*16);
    trasX [0]=KG_KAM_ABIAD_TRASL; trasX [4]=0; trasX [8] =KG_KAM_ABIAD_TRASL; trasX [12]=0;
    trasX [1]=0; trasX [5]=0; trasX [9] =0; trasX [13]=0;
    trasX [2]=0; trasX [6]=0; trasX [10]=0; trasX [14]=0;
    trasX [3]=0; trasX [7]=0; trasX [11]=0; trasX [15]=0;

    GLfloat  * trasY = malloc ( sizeof ( GLfloat )*16);
    trasY [0]=0; trasY [4]=0; trasY [8] =0; trasY [12]=0;
    trasY [1]=KG_KAM_ABIAD_TRASL; trasY [5]=KG_KAM_ABIAD_TRASL; trasY [9] =KG_KAM_ABIAD_TRASL; trasY [13]=0;
    trasY [2]=0; trasY [6]=0; trasY [10]=0; trasY [14]=0;
    trasY [3]=0; trasY [7]=0; trasY [11]=0; trasY [15]=0;

    GLfloat  * trasZ = malloc ( sizeof ( GLfloat )*16);
    trasZ [0]=0; trasZ [4]=0; trasZ [8] =0; trasZ [12]=0;
    trasZ [1]=0; trasZ [5]=0; trasZ [9] =0; trasZ [13]=0;
    trasZ [2]=KG_KAM_ABIAD_TRASL; trasZ [6]=KG_KAM_ABIAD_TRASL; trasZ [10]=KG_KAM_ABIAD_TRASL; trasZ [14]=0;
    trasZ [3]=0; trasZ [7]=0; trasZ [11]=0; trasZ [15]=0;

    GLfloat  * trasXn = malloc ( sizeof ( GLfloat )*16);
    trasXn [0]=KG_KAM_ABIAD_TRASL*(-1); trasXn [4]=KG_KAM_ABIAD_TRASL*(-1); trasXn [8] =KG_KAM_ABIAD_TRASL*(-1); trasXn [12]=0;
    trasXn [1]=0; trasXn [5]=0; trasXn [9] =0; trasXn [13]=0;
    trasXn [2]=0; trasXn [6]=0; trasXn [10]=0; trasXn [14]=0;
    trasXn [3]=0; trasXn [7]=0; trasXn [11]=0; trasXn [15]=0;

    GLfloat  * trasYn = malloc ( sizeof ( GLfloat )*16);
    trasYn [0]=0; trasYn [4]=0; trasYn [8] =0; trasYn [12]=0;
    trasYn [1]=KG_KAM_ABIAD_TRASL*(-1); trasYn [5]=KG_KAM_ABIAD_TRASL*(-1); trasYn [9] =KG_KAM_ABIAD_TRASL*(-1); trasYn [13]=0;
    trasYn [2]=0; trasYn [6]=0; trasYn [10]=0; trasYn [14]=0;
    trasYn [3]=0; trasYn [7]=0; trasYn [11]=0; trasYn [15]=0;

    GLfloat  * trasZn = malloc ( sizeof ( GLfloat )*16);
    trasZn [0]=0; trasZn [4]=0; trasZn [8] =0; trasZn [12]=0;
    trasZn [1]=0; trasZn [5]=0; trasZn [9] =0; trasZn [13]=0;
    trasZn [2]=KG_KAM_ABIAD_TRASL*(-1); trasZn [6]=KG_KAM_ABIAD_TRASL*(-1); trasZn [10]=KG_KAM_ABIAD_TRASL*(-1); trasZn [14]=0;
    trasZn [3]=0; trasZn [7]=0; trasZn [11]=0; trasZn [15]=0;

    for(int i = 0; i < 16; i++){
        printf("%f ",kamera1->matrix[i]);
        if (i==3 || i==7 || i==11 || i==15){
            printf("\n");
        }
    }
    printf("\n");

    switch (kamera_tardatza){
        case 'X':
            if(kamera_tnorabidea=='+'){
                printf("Kamera traslazioa: +X\n");
                if(transf_helburua=='l')
                    kamera1->matrix=sum(kamera1->matrix,trasX);
                else if(transf_helburua=='g')
                    kamera1->matrix=sum(trasX,kamera1->matrix);
            }
            else{
                printf("Kamera traslazioa: -X\n");
                if(transf_helburua=='l')
                    kamera1->matrix=sum(kamera1->matrix,trasXn);
                else if(transf_helburua=='g')
                    kamera1->matrix=sum(trasXn,kamera1->matrix);
            }
            //pilanGehitu(kamera1->matrix);
            break;

        case 'Y':
            if(kamera_tnorabidea=='+'){
                printf("Kamera traslazioa: +Y\n");
                if(transf_helburua=='l')
                    kamera1->matrix=sum(kamera1->matrix,trasY);
                else if(transf_helburua=='g')
                    kamera1->matrix=sum(trasY,kamera1->matrix);
            }
            else{
                printf("Kamera traslazioa: -Y\n");
                if(transf_helburua=='l')
                    kamera1->matrix=sum(kamera1->matrix,trasYn);
                else if(transf_helburua=='g')
                    kamera1->matrix=sum(trasYn,kamera1->matrix);
            }
            //pilanGehitu(kamera1->matrix);
            break;

        case 'Z':
            if(kamera_tnorabidea=='+'){
                printf("Kamera traslazioa: +Z\n");
                if(transf_helburua=='l')
                    kamera1->matrix=sum(kamera1->matrix,trasZ);
                else if(transf_helburua=='g')
                    kamera1->matrix=sum(trasZ,kamera1->matrix);
            }
            else{
                printf("Kamera traslazioa: -X\n");
                if(transf_helburua=='l')
                    kamera1->matrix=sum(kamera1->matrix,trasZn);
                else if(transf_helburua=='g')
                    kamera1->matrix=sum(trasZn,kamera1->matrix);
            }
            //pilanGehitu(kamera1->matrix);
            break;
    }
}

void kam_biratu(){
    /*glMatrixMode(GL_PROJECTION);
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
    glMatrixMode(GL_MODELVIEW);*/
}
