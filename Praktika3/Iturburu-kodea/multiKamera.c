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
    GLfloat  * trasGX = malloc ( sizeof ( GLfloat )*16);
    trasGX [0]=KG_KAM_ABIAD_TRASL; trasGX [4]=0; trasGX [8] =0; trasGX [12]=0;
    trasGX [1]=0; trasGX [5]=0; trasGX [9] =0; trasGX [13]=0;
    trasGX [2]=0; trasGX [6]=0; trasGX [10]=0; trasGX [14]=0;
    trasGX [3]=0; trasGX [7]=0; trasGX [11]=0; trasGX [15]=0;

    GLfloat  * trasGY = malloc ( sizeof ( GLfloat )*16);
    trasGY [0]=0; trasGY [4]=0; trasGY [8] =0; trasGY [12]=0;
    trasGY [1]=KG_KAM_ABIAD_TRASL; trasGY [5]=0; trasGY [9] =0; trasGY [13]=0;
    trasGY [2]=0; trasGY [6]=0; trasGY [10]=0; trasGY [14]=0;
    trasGY [3]=0; trasGY [7]=0; trasGY [11]=0; trasGY [15]=0;

    GLfloat  * trasGZ = malloc ( sizeof ( GLfloat )*16);
    trasGZ [0]=0; trasGZ [4]=0; trasGZ [8] =0; trasGZ [12]=0;
    trasGZ [1]=0; trasGZ [5]=0; trasGZ [9] =0; trasGZ [13]=0;
    trasGZ [2]=KG_KAM_ABIAD_TRASL; trasGZ [6]=0; trasGZ [10]=0; trasGZ [14]=0;
    trasGZ [3]=0; trasGZ [7]=0; trasGZ [11]=0; trasGZ [15]=0;

    GLfloat  * trasGXn = malloc ( sizeof ( GLfloat )*16);
    trasGXn [0]=KG_KAM_ABIAD_TRASL*(-1); trasGXn [4]=0*(-1); trasGXn [8] =0*(-1); trasGXn [12]=0;
    trasGXn [1]=0; trasGXn [5]=0; trasGXn [9] =0; trasGXn [13]=0;
    trasGXn [2]=0; trasGXn [6]=0; trasGXn [10]=0; trasGXn [14]=0;
    trasGXn [3]=0; trasGXn [7]=0; trasGXn [11]=0; trasGXn [15]=0;

    GLfloat  * trasGYn = malloc ( sizeof ( GLfloat )*16);
    trasGYn [0]=0; trasGYn [4]=0; trasGYn [8] =0; trasGYn [12]=0;
    trasGYn [1]=KG_KAM_ABIAD_TRASL*(-1); trasGYn [5]=0; trasGYn [9] =0; trasGYn [13]=0;
    trasGYn [2]=0; trasGYn [6]=0; trasGYn [10]=0; trasGYn [14]=0;
    trasGYn [3]=0; trasGYn [7]=0; trasGYn [11]=0; trasGYn [15]=0;

    GLfloat  * trasGZn = malloc ( sizeof ( GLfloat )*16);
    trasGZn [0]=0; trasGZn [4]=0; trasGZn [8] =0; trasGZn [12]=0;
    trasGZn [1]=0; trasGZn [5]=0; trasGZn [9] =0; trasGZn [13]=0;
    trasGZn [2]=KG_KAM_ABIAD_TRASL*(-1); trasGZn [6]=0; trasGZn [10]=0; trasGZn [14]=0;
    trasGZn [3]=0; trasGZn [7]=0; trasGZn [11]=0; trasGZn [15]=0;

    /********************************************************************************************/

    GLfloat  * trasLX = malloc ( sizeof ( GLfloat )*16);
    trasLX [0]=KG_KAM_ABIAD_TRASL; trasLX [4]=0; trasLX [8]=KG_KAM_ABIAD_TRASL; trasLX [12]=0;
    trasLX [1]=0; trasLX [5]=0; trasLX [9] =0; trasLX [13]=0;
    trasLX [2]=0; trasLX [6]=0; trasLX [10]=0; trasLX [14]=0;
    trasLX [3]=0; trasLX [7]=0; trasLX [11]=0; trasLX [15]=0;

    GLfloat  * trasLY = malloc ( sizeof ( GLfloat )*16);
    trasLY [0]=0; trasLY [4]=0; trasLY [8] =0; trasLY [12]=0;
    trasLY [1]=KG_KAM_ABIAD_TRASL; trasLY [5]=0; trasLY [9]=KG_KAM_ABIAD_TRASL; trasLY [13]=0;
    trasLY [2]=0; trasLY [6]=0; trasLY [10]=0; trasLY [14]=0;
    trasLY [3]=0; trasLY [7]=0; trasLY [11]=0; trasLY [15]=0;

    GLfloat  * trasLZ = malloc ( sizeof ( GLfloat )*16);
    trasLZ [0]=0; trasLZ [4]=0; trasLZ [8] =0; trasLZ [12]=0;
    trasLZ [1]=0; trasLZ [5]=0; trasLZ [9] =0; trasLZ [13]=0;
    trasLZ [2]=KG_KAM_ABIAD_TRASL; trasLZ [6]=0; trasLZ [10]=KG_KAM_ABIAD_TRASL; trasLZ [14]=0;
    trasLZ [3]=0; trasLZ [7]=0; trasLZ [11]=0; trasLZ [15]=0;

    GLfloat  * trasLXn = malloc ( sizeof ( GLfloat )*16);
    trasLXn [0]=KG_KAM_ABIAD_TRASL*(-1); trasLXn [4]=0*(-1); trasLXn [8]=KG_KAM_ABIAD_TRASL*(-1); trasLXn [12]=0;
    trasLXn [1]=0; trasLXn [5]=0; trasLXn [9] =0; trasLXn [13]=0;
    trasLXn [2]=0; trasLXn [6]=0; trasLXn [10]=0; trasLXn [14]=0;
    trasLXn [3]=0; trasLXn [7]=0; trasLXn [11]=0; trasLXn [15]=0;

    GLfloat  * trasLYn = malloc ( sizeof ( GLfloat )*16);
    trasLYn [0]=0; trasLYn [4]=0; trasLYn [8] =0; trasLYn [12]=0;
    trasLYn [1]=KG_KAM_ABIAD_TRASL*(-1); trasLYn [5]=0; trasLYn [9]=KG_KAM_ABIAD_TRASL*(-1); trasLYn [13]=0;
    trasLYn [2]=0; trasLYn [6]=0; trasLYn [10]=0; trasLYn [14]=0;
    trasLYn [3]=0; trasLYn [7]=0; trasLYn [11]=0; trasLYn [15]=0;

    GLfloat  * trasLZn = malloc ( sizeof ( GLfloat )*16);
    trasLZn [0]=0; trasLZn [4]=0; trasLZn [8] =0; trasLZn [12]=0;
    trasLZn [1]=0; trasLZn [5]=0; trasLZn [9] =0; trasLZn [13]=0;
    trasLZn [2]=KG_KAM_ABIAD_TRASL*(-1); trasLZn [6]=0; trasLZn [10]=KG_KAM_ABIAD_TRASL*(-1); trasLZn [14]=0;
    trasLZn [3]=0; trasLZn [7]=0; trasLZn [11]=0; trasLZn [15]=0;

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
                    kamera1->matrix=sum(kamera1->matrix,trasLX);
                else if(transf_helburua=='g')
                    kamera1->matrix=sum(kamera1->matrix,trasGX);
            }
            else{
                printf("Kamera traslazioa: -X\n");
                if(transf_helburua=='l')
                    kamera1->matrix=sum(kamera1->matrix,trasLXn);
                else if(transf_helburua=='g')
                    kamera1->matrix=sum(kamera1->matrix,trasGXn);
            }
            //pilanGehitu(kamera1->matrix);
            break;

        case 'Y':
            if(kamera_tnorabidea=='+'){
                printf("Kamera traslazioa: +Y\n");
                if(transf_helburua=='l')
                    kamera1->matrix=sum(kamera1->matrix,trasLY);
                else if(transf_helburua=='g')
                    kamera1->matrix=sum(kamera1->matrix,trasGY);
            }
            else{
                printf("Kamera traslazioa: -Y\n");
                if(transf_helburua=='l')
                    kamera1->matrix=sum(kamera1->matrix,trasLYn);
                else if(transf_helburua=='g')
                    kamera1->matrix=sum(kamera1->matrix,trasGYn);
            }
            //pilanGehitu(kamera1->matrix);
            break;

        case 'Z':
            if(kamera_tnorabidea=='+'){
                printf("Kamera traslazioa: +Z\n");
                if(transf_helburua=='l')
                    kamera1->matrix=sum(kamera1->matrix,trasLZ);
                else if(transf_helburua=='g')
                    kamera1->matrix=sum(kamera1->matrix,trasGZ);
            }
            else{
                printf("Kamera traslazioa: -Z\n");
                if(transf_helburua=='l')
                    kamera1->matrix=sum(kamera1->matrix,trasLZn);
                else if(transf_helburua=='g')
                    kamera1->matrix=sum(kamera1->matrix,trasGZn);
            }
            //pilanGehitu(kamera1->matrix);
            break;
    }
}//kam_mugitu

void kam_biratu(){

    GLfloat  * biraGX = malloc ( sizeof ( GLfloat )*16);
    biraGX [0]=0; biraGX [4]=0; biraGX [8] =KG_KAM_ABIAD_BIRAK; biraGX [12]=0;
    biraGX [1]=0; biraGX [5]=0; biraGX [9] =0; biraGX [13]=0;
    biraGX [2]=0; biraGX [6]=0; biraGX [10]=0; biraGX [14]=0;
    biraGX [3]=0; biraGX [7]=0; biraGX [11]=0; biraGX [15]=0;

    GLfloat  * biraGY = malloc ( sizeof ( GLfloat )*16);
    biraGY [0]=0; biraGY [4]=0; biraGY [8] =0; biraGY [12]=0;
    biraGY [1]=0; biraGY [5]=0; biraGY [9] =KG_KAM_ABIAD_BIRAK; biraGY [13]=0;
    biraGY [2]=0; biraGY [6]=0; biraGY [10]=0; biraGY [14]=0;
    biraGY [3]=0; biraGY [7]=0; biraGY [11]=0; biraGY [15]=0;

    GLfloat  * biraGZ = malloc ( sizeof ( GLfloat )*16);
    biraGZ [0]=0; biraGZ [4]=0; biraGZ [8] =0; biraGZ [12]=0;
    biraGZ [1]=0; biraGZ [5]=0; biraGZ [9] =0; biraGZ [13]=0;
    biraGZ [2]=0; biraGZ [6]=0; biraGZ [10]=KG_KAM_ABIAD_BIRAK; biraGZ [14]=0;
    biraGZ [3]=0; biraGZ [7]=0; biraGZ [11]=0; biraGZ [15]=0;

    GLfloat  * biraGXn = malloc ( sizeof ( GLfloat )*16);
    biraGXn [0]=0; biraGXn [4]=0*(-1); biraGXn [8] =KG_KAM_ABIAD_BIRAK*(-1); biraGXn [12]=0;
    biraGXn [1]=0; biraGXn [5]=0; biraGXn [9] =0; biraGXn [13]=0;
    biraGXn [2]=0; biraGXn [6]=0; biraGXn [10]=0; biraGXn [14]=0;
    biraGXn [3]=0; biraGXn [7]=0; biraGXn [11]=0; biraGXn [15]=0;

    GLfloat  * biraGYn = malloc ( sizeof ( GLfloat )*16);
    biraGYn [0]=0; biraGYn [4]=0; biraGYn [8] =0; biraGYn [12]=0;
    biraGYn [1]=0; biraGYn [5]=0; biraGYn [9] =KG_KAM_ABIAD_BIRAK*(-1); biraGYn [13]=0;
    biraGYn [2]=0; biraGYn [6]=0; biraGYn [10]=0; biraGYn [14]=0;
    biraGYn [3]=0; biraGYn [7]=0; biraGYn [11]=0; biraGYn [15]=0;

    GLfloat  * biraGZn = malloc ( sizeof ( GLfloat )*16);
    biraGZn [0]=0; biraGZn [4]=0; biraGZn [8] =0; biraGZn [12]=0;
    biraGZn [1]=0; biraGZn [5]=0; biraGZn [9] =0; biraGZn [13]=0;
    biraGZn [2]=0; biraGZn [6]=0; biraGZn [10]=KG_KAM_ABIAD_BIRAK*(-1); biraGZn [14]=0;
    biraGZn [3]=0; biraGZn [7]=0; biraGZn [11]=0; biraGZn [15]=0;

    /********************************************************************************************/

    GLfloat  * biraLX = malloc ( sizeof ( GLfloat )*16);
    biraLX [0]=0; biraLX [4]=0; biraLX [8] =KG_KAM_ABIAD_BIRAK; biraLX [12]=0;
    biraLX [1]=0; biraLX [5]=0; biraLX [9] =0; biraLX [13]=0;
    biraLX [2]=0; biraLX [6]=0; biraLX [10]=0; biraLX [14]=0;
    biraLX [3]=0; biraLX [7]=0; biraLX [11]=0; biraLX [15]=0;

    GLfloat  * biraLY = malloc ( sizeof ( GLfloat )*16);
    biraLY [0]=0; biraLY [4]=0; biraLY [8] =0; biraLY [12]=0;
    biraLY [1]=0; biraLY [5]=0; biraLY [9] =KG_KAM_ABIAD_BIRAK; biraLY [13]=0;
    biraLY [2]=0; biraLY [6]=0; biraLY [10]=0; biraLY [14]=0;
    biraLY [3]=0; biraLY [7]=0; biraLY [11]=0; biraLY [15]=0;

    GLfloat  * biraLZ = malloc ( sizeof ( GLfloat )*16);
    biraLZ [0]=0; biraLZ [4]=0; biraLZ [8] =0; biraLZ [12]=0;
    biraLZ [1]=0; biraLZ [5]=0; biraLZ [9] =0; biraLZ [13]=0;
    biraLZ [2]=0; biraLZ [6]=0; biraLZ [10]=KG_KAM_ABIAD_BIRAK; biraLZ [14]=0;
    biraLZ [3]=0; biraLZ [7]=0; biraLZ [11]=0; biraLZ [15]=0;

    GLfloat  * biraLXn = malloc ( sizeof ( GLfloat )*16);
    biraLXn [0]=0; biraLXn [4]=0; biraLXn [8] =KG_KAM_ABIAD_BIRAK*(-1); biraLXn [12]=0;
    biraLXn [1]=0; biraLXn [5]=0; biraLXn [9] =0; biraLXn [13]=0;
    biraLXn [2]=0; biraLXn [6]=0; biraLXn [10]=0; biraLXn [14]=0;
    biraLXn [3]=0; biraLXn [7]=0; biraLXn [11]=0; biraLXn [15]=0;

    GLfloat  * biraLYn = malloc ( sizeof ( GLfloat )*16);
    biraLYn [0]=0; biraLYn [4]=0; biraLYn [8] =0; biraLYn [12]=0;
    biraLYn [1]=0; biraLYn [5]=0; biraLYn [9] =KG_KAM_ABIAD_BIRAK*(-1); biraLYn [13]=0;
    biraLYn [2]=0; biraLYn [6]=0; biraLYn [10]=0; biraLYn [14]=0;
    biraLYn [3]=0; biraLYn [7]=0; biraLYn [11]=0; biraLYn [15]=0;

    GLfloat  * biraLZn = malloc ( sizeof ( GLfloat )*16);
    biraLZn [0]=0; biraLZn [4]=0; biraLZn [8] =0; biraLZn [12]=0;
    biraLZn [1]=0; biraLZn [5]=0; biraLZn [9] =0; biraLZn [13]=0;
    biraLZn [2]=0; biraLZn [6]=0; biraLZn [10]=KG_KAM_ABIAD_BIRAK*(-1); biraLZn [14]=0;
    biraLZn [3]=0; biraLZn [7]=0; biraLZn [11]=0; biraLZn [15]=0;

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
                printf("Kamera biralazioa: +X\n");
                if(transf_helburua=='l')
                    kamera1->matrix=sum(kamera1->matrix,biraLX);
                else if(transf_helburua=='g')
                    kamera1->matrix=sum(kamera1->matrix,biraGX);
            }
            else{
                printf("Kamera biralazioa: -X\n");
                if(transf_helburua=='l')
                    kamera1->matrix=sum(kamera1->matrix,biraLXn);
                else if(transf_helburua=='g')
                    kamera1->matrix=sum(kamera1->matrix,biraGXn);
            }
            //pilanGehitu(kamera1->matrix);
            break;

        case 'Y':
            if(kamera_tnorabidea=='+'){
                printf("Kamera biralazioa: +Y\n");
                if(transf_helburua=='l')
                    kamera1->matrix=sum(kamera1->matrix,biraLY);
                else if(transf_helburua=='g')
                    kamera1->matrix=sum(kamera1->matrix,biraGY);
            }
            else{
                printf("Kamera biralazioa: -Y\n");
                if(transf_helburua=='l')
                    kamera1->matrix=sum(kamera1->matrix,biraLYn);
                else if(transf_helburua=='g')
                    kamera1->matrix=sum(kamera1->matrix,biraGYn);
            }
            //pilanGehitu(kamera1->matrix);
            break;

        case 'Z':
            if(kamera_tnorabidea=='+'){
                printf("Kamera biralazioa: +Z\n");
                if(transf_helburua=='l')
                    kamera1->matrix=sum(kamera1->matrix,biraLZ);
                else if(transf_helburua=='g')
                    kamera1->matrix=sum(kamera1->matrix,biraGZ);
            }
            else{
                printf("Kamera biralazioa: -Z\n");
                if(transf_helburua=='l')
                    kamera1->matrix=sum(kamera1->matrix,biraLZn);
                else if(transf_helburua=='g')
                    kamera1->matrix=sum(kamera1->matrix,biraGZn);
            }
            //pilanGehitu(kamera1->matrix);
            break;
    }
    
}//kam_biratu
