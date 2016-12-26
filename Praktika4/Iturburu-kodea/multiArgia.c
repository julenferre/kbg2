#include "definitions.h"
#include <GL/glut.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <stdio.h>
#include <math.h> /* cos eta sin */
#include "multiMatrix.h"
#include "matrizeak.h"

extern GLdouble _window_ratio;
extern GLdouble _ortho_x_min,_ortho_x_max;
extern GLdouble _ortho_y_min,_ortho_y_max;
extern GLdouble _ortho_z_min,_ortho_z_max;

extern object3d *_first_object;
extern object3d *_selected_object;

argia * argia1;

int enable1 = 0;
int argiak_piztu= 1;
char argia_mota = 'b';							//Orto,objektu-kamera,ibiltaria
char argia_tmota= '\0';							//Biratu edo mugitu
char argia_tardatza = '\0';						//X,Y,Z
char argia_tnorabidea = '\0';					//+,-
extern char transf_helburua;
 int i;

//transformazio matrizeak
extern GLdouble  * trasX;
extern GLdouble  * trasY;
extern GLdouble  * trasZ;
extern GLdouble  * trasXn;
extern GLdouble  * trasYn;
extern GLdouble  * trasZn;

//biraketa matrizeak
extern GLdouble  * biraX;
extern GLdouble  * biraY;
extern GLdouble  * biraZ;    
extern GLdouble  * biraXn;
extern GLdouble  * biraYn;    
extern GLdouble  * biraZn;


void argia_mota_aldatu(){
    switch(argia1->mota){
        case 'b':
                argia1->mota = 'e';
                printf("Argi mota: %c (b: bonbila, e: eguzkia, f: fokoa)\n",argia1->mota);
                break;
        case 'e':
                 argia1->mota = 'f';
                 printf("Argi mota: %c (b: bonbila, e: eguzkia, f: fokoa)\n",argia1->mota);
                break;
        case 'f': 
                 argia1->mota = 'b';
                 printf("Argi mota: %c (b: bonbila, e: eguzkia, f: fokoa)\n",argia1->mota);
                break;
        default: break;
    }
	
}

void pilanGehituA(GLdouble *matrix_aux){
    pila *pila_aux = (pila *) malloc(sizeof(pila));
    pila_aux->matrix= matrix_aux;

        pila_aux->next = argia1->aldaketaPila;
        argia1->aldaketaPila = pila_aux;
        argia1->num_aldaketak += 1;
    
}

void ArgaldaketaDesegin(){
    if(argia1->num_aldaketak>0){
        pila *first_matrix;
        first_matrix = argia1->aldaketaPila->next;
        argia1->aldaketaPila = 0;
        argia1->aldaketaPila = first_matrix;
        //argia1->matrix = first_matrix->matrix;
        argia1->num_aldaketak-=1;
        printf("Objektuaren aldaketak desegin dira\n");}
    else{
        printf("Ezin dira aldaketa gehiagorik desegin\n");}
}//aldaketaDesegin


void argiak_init(){

 GLdouble* ident = malloc (sizeof ( GLdouble )*16);
    ident [0]=1; ident [4]=0; ident [8] =0; ident [12]=0;
    ident [1]=0; ident [5]=1; ident [9] =0; ident [13]=0;
    ident [2]=0; ident [6]=0; ident [10]=1; ident [14]=0;
    ident [3]=0; ident [7]=0; ident [11]=0; ident [15]=1;

    GLdouble* lag = malloc ( sizeof ( GLdouble )*16);
    lag [0]=1; lag [4]=0; lag [8] =0; lag [12]=0;
    lag [1]=0; lag [5]=1; lag [9] =0; lag [13]=0;
    lag [2]=0; lag [6]=0; lag [10]=1; lag [14]=4;
    lag [3]=0; lag [7]=0; lag [11]=0; lag [15]=1;

 argia1 = (argia *)malloc(sizeof(argia));

 argia1 -> mota = 'b';

 argia1->neguzki = (GLfloat *) malloc(sizeof(GLfloat)*4);
 argia1->neguzki[0]= 0.0f;
 argia1->neguzki[1]= 1.0f;
 argia1->neguzki[2]= 0.0f;
 argia1->neguzki[3]= 0.0f;

 argia1->bonb_kokapena = (GLfloat *) malloc(sizeof(GLfloat)*4);
 argia1->bonb_kokapena[0]= 0.0f;
 argia1->bonb_kokapena[1]= 4.0f;
 argia1->bonb_kokapena[2]= 0.0f;
 argia1->bonb_kokapena[3]= 1.0f;

 argia1 -> foko_ang = 30.0f;

 argia1-> aldaketaPila = (pila*) malloc(sizeof(pila));
 argia1 -> aldaketaPila ->matrix= mult(ident,lag);
 argia1 -> aldaketaPila-> next = NULL;

}

void fokoaMugitu(){


}

void fokoaBiratu(){



}

void eguzkiaBiratu(){

      GLdouble *matBerria;

    switch (argia_tardatza) {
        case 'X':
            if (argia_tnorabidea == '+') {
                printf("Eguzkiaren biraketa: +X\n");
                if (transf_helburua == 'l')
                    matBerria = mult(argia1->aldaketaPila->matrix, biraX);
                else if (transf_helburua == 'g')
                    matBerria = mult(biraX, argia1->aldaketaPila->matrix);
            } else {
                printf("Eguzkiaren biraketa: -X\n");
                if (transf_helburua == 'l')
                    matBerria = mult(argia1->aldaketaPila->matrix, biraXn);
                else if (transf_helburua == 'g')
                    matBerria = mult(biraXn, argia1->aldaketaPila->matrix);
            }
            pilanGehituA(matBerria);
            break;

        case 'Y':
            if (argia_tnorabidea == '+') {
                printf("Eguzkiaren biraketa: +Y\n");
                if (transf_helburua == 'l')
                    matBerria = mult(argia1->aldaketaPila->matrix, biraY);
                else if (transf_helburua == 'g')
                    matBerria = mult(biraY, argia1->aldaketaPila->matrix);
            } else {
                printf("Eguzkiaren biraketa: -Y\n");
                if (transf_helburua == 'l')
                    matBerria = mult(argia1->aldaketaPila->matrix, biraYn);
                else if (transf_helburua == 'g')
                    matBerria = mult(biraYn, argia1->aldaketaPila->matrix);
            }
            pilanGehituA(matBerria);
            break;

        case 'Z':
            if (argia_tnorabidea == '+') {
                printf("Eguzkiaren biraketa: +Z\n");
                if (transf_helburua == 'l')
                    matBerria = mult(argia1->aldaketaPila->matrix, biraZ);
                else if (transf_helburua == 'g')
                    matBerria = mult(biraZ, argia1->aldaketaPila->matrix);
            } else {
                printf("Eguzkiaren biraketa: -Z\n");
                if (transf_helburua == 'l')
                    matBerria = mult(argia1->aldaketaPila->matrix, biraZn);
                else if (transf_helburua == 'g')
                    matBerria = mult(biraZn, argia1->aldaketaPila->matrix);
            }
            pilanGehituA(matBerria);
            break;
    }
   
    for(i = 0; i < 16; i++){
        printf("%f ",argia1->aldaketaPila->matrix[i]);
        if(i==3 || i==7 || i==11) printf("\n");
    }
    printf("\n");


}

void bonbilaMugitu(){
   
    for(i = 0; i < 16; i++){
        printf("%f ",argia1->aldaketaPila->matrix[i]);
        if(i==3 || i==7 || i==11) printf("\n");
    }
    printf("\n");

    GLdouble *matBerria;

    switch (argia_tardatza) {
        case 'X':
            if (argia_tnorabidea == '+') {
                printf("Bonbilaren traslazioa: +X\n");
                if (transf_helburua == 'l') {
                    matBerria = mult(argia1->aldaketaPila->matrix, trasX);
                }
                else if (transf_helburua == 'g'){
                    matBerria = mult(trasX, argia1->aldaketaPila->matrix);
                }
            } else {
                printf("Bonbilaren traslazioa: -X\n");
                if (transf_helburua == 'l')
                    matBerria = mult(argia1->aldaketaPila->matrix, trasXn);
                else if (transf_helburua == 'g')
                    matBerria = mult(trasXn, argia1->aldaketaPila->matrix);
            }
            pilanGehituA(matBerria);
            break;

        case 'Y':
            if (argia_tnorabidea == '+') {
                printf("Bonbilaren traslazioa: +Y\n");
                if (transf_helburua == 'l')
                    matBerria = mult(argia1->aldaketaPila->matrix, trasY);
                else if (transf_helburua == 'g')
                    matBerria = mult(trasY, argia1->aldaketaPila->matrix);
            } else {
                printf("Bonbilaren traslazioa: -Y\n");
                if (transf_helburua == 'l')
                    matBerria = mult(argia1->aldaketaPila->matrix, trasYn);
                else if (transf_helburua == 'g')
                    matBerria = mult(trasYn, argia1->aldaketaPila->matrix);
            }
            pilanGehituA(matBerria);
            break;

        case 'Z':
            if (argia_tnorabidea == '+') {
                printf("Bonbilaren traslazioa: +Z\n");
                if (transf_helburua == 'l')
                    matBerria = mult(argia1->aldaketaPila->matrix, trasZ);
                else if (transf_helburua == 'g')
                    matBerria = mult(trasZ, argia1->aldaketaPila->matrix);
            } else {
                printf("Bonbilaren traslazioa: -Z\n");
                if (transf_helburua == 'l')
                    matBerria = mult(argia1->aldaketaPila->matrix, trasZn);
                else if (transf_helburua == 'g')
                    matBerria = mult(trasZn, argia1->aldaketaPila->matrix);
            }
            pilanGehituA(matBerria);
            break;
    }


}