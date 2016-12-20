/*********************************************
 * File with the functions to  				 *
 * show in the display the objects 			 *
 * ----------------------------------------- *
 * Authors: 								 *
 *  Robin Espinosa   						 *
 *	Julen Ferrero 							 *
 * Date:  November 2016                      *
 *********************************************/

#include "definitions.h"
#include <GL/glut.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <stdio.h>
#include <malloc.h>
#include <math.h> /** cos eta sin **/
#include "multiMatrix.h"
#include "multiKamera.h"

/** EXTERNAL VARIABLES **/

extern GLdouble _window_ratio;
extern GLdouble _ortho_x_min,_ortho_x_max;
extern GLdouble _ortho_y_min,_ortho_y_max;
extern GLdouble _ortho_z_min,_ortho_z_max;

extern object3d *_first_object;
extern object3d *_selected_object;

kamera * kameraO;
kamera * kameraI;
extern char kamera_mota;

void camera_init(){
    GLdouble* ident = malloc ( sizeof ( GLdouble )*16);
    ident [0]=1; ident [4]=0; ident [8] =0; ident [12]=0;
    ident [1]=0; ident [5]=1; ident [9] =0; ident [13]=0;
    ident [2]=0; ident [6]=0; ident [10]=1; ident [14]=0;
    ident [3]=0; ident [7]=0; ident [11]=0; ident [15]=1;

    GLdouble* lag = malloc ( sizeof ( GLdouble )*16);
    lag [0]=1; lag [4]=0; lag [8] =0; lag [12]=0;
    lag [1]=0; lag [5]=1; lag [9] =0; lag [13]=0;
    lag [2]=0; lag [6]=0; lag [10]=1; lag [14]=22;
    lag [3]=0; lag [7]=0; lag [11]=0; lag [15]=1;
    
    /*Objektu kamera hasiarazten da*/
    kameraO = malloc(sizeof(kameraO));

    kameraO->eye = (GLdouble*)malloc(sizeof(GLdouble)*4);
    kameraO->eye[0]=0;
    kameraO->eye[1]=0;
    kameraO->eye[2]=0;
    kameraO->eye[3]=1;

    kameraO->center = (GLdouble*)malloc(sizeof(GLdouble)*4);
    kameraO->center[0]=0;
    kameraO->center[1]=0;
    kameraO->center[2]=-10;
    kameraO->center[3]=1;

    kameraO->up = (GLdouble*)malloc(sizeof(GLdouble)*4);
    kameraO->up[0]=0;
    kameraO->up[1]=1;
    kameraO->up[2]=0;
    kameraO->up[3]=0;

    kameraO->angeluaY = 90;
    kameraO->n = 0;
    kameraO->f = 1000;

    kameraO->aldaketaPila = (pila*)malloc(sizeof(pila));
    kameraO->aldaketaPila->matrix = mult(ident,lag);
    kameraO->aldaketaPila->next   = NULL;

    /*Kamera ibiltaria hasiarazten da*/
    kameraI = malloc(sizeof(kameraI));

    kameraI->eye = (GLdouble*)malloc(sizeof(GLdouble)*4);
    kameraI->eye[0]=0;
    kameraI->eye[1]=0;
    kameraI->eye[2]=0;
    kameraI->eye[3]=1;

    kameraI->center = (GLdouble*)malloc(sizeof(GLdouble)*4);
    kameraI->center[0]=0;
    kameraI->center[1]=0;
    kameraI->center[2]=-10;
    kameraI->center[3]=1;

    kameraI->up = (GLdouble*)malloc(sizeof(GLdouble)*4);
    kameraI->up[0]=0;
    kameraI->up[1]=1;
    kameraI->up[2]=0;
    kameraI->up[3]=0;

    kameraI->angeluaY = 90;
    kameraI->n = 0;
    kameraI->f = 1000;
    kameraI->angeluaXZ = 8;

    kameraI->aldaketaPila = (pila*)malloc(sizeof(pila));
    kameraI->aldaketaPila->matrix = mult(ident,lag);
    kameraI->aldaketaPila->next   = NULL;
}

/**
 * @brief Function to draw the axes
 */
void draw_axes()
{
    glTranslatef(0.0, 0.0, 0.0);
    /*Draw X axis*/
    glColor3f(KG_COL_X_AXIS_R,KG_COL_X_AXIS_G,KG_COL_X_AXIS_B);
    glBegin(GL_LINES);
    glVertex3d(KG_MAX_DOUBLE,0,0);
    glVertex3d(-1*KG_MAX_DOUBLE,0,0);
    glEnd();
    /*Draw Y axis*/
    glColor3f(KG_COL_Y_AXIS_R,KG_COL_Y_AXIS_G,KG_COL_Y_AXIS_B);
    glBegin(GL_LINES);
    glVertex3d(0,KG_MAX_DOUBLE,0);
    glVertex3d(0,-1*KG_MAX_DOUBLE,0);
    glEnd();
    /*Draw Z axis*/
    glColor3f(KG_COL_Z_AXIS_R,KG_COL_Z_AXIS_G,KG_COL_Z_AXIS_B);
    glBegin(GL_LINES);
    glVertex3d(0,0,KG_MAX_DOUBLE);
    glVertex3d(0,0,-1*KG_MAX_DOUBLE);
    glEnd();
}


/**
 * @brief Callback reshape function. We just store the new proportions of the window
 * @param width New width of the window
 * @param height New height of the window
 */
void reshape(int width, int height) {
    /*VIEWPORT nagusia*/
    glViewport(0, 0, width, height);
    /*  Take care, the width and height are integer numbers, but the ratio is a GLdouble so, in order to avoid
     *  rounding the ratio to integer values we need to cast width and height before computing the ratio */
    _window_ratio = (GLdouble) width / (GLdouble) height;
}

/**
 * @brief Callback display function
 */
void display(void) {
    GLint v_index, v, f;
    object3d *aux_obj = _first_object;

    /* Clear the screen */
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    /* Define the projection */
    GLdouble *eye;
    GLdouble *center;
    GLdouble *up;

    GLdouble he = (_ortho_x_max - _ortho_x_min) / _window_ratio;
    GLdouble wd = (_ortho_y_max - _ortho_y_min) * _window_ratio;

    switch (kamera_mota) {
        case 'o':
            glMatrixMode(GL_PROJECTION);
            glLoadIdentity();
            /*When the window is wider than our original projection plane we extend the plane in the X axis*/
            if ((_ortho_x_max - _ortho_x_min) / (_ortho_y_max - _ortho_y_min) < _window_ratio) {
                /* Midpoint in the X axis */
                GLdouble midpt = (_ortho_x_min + _ortho_x_max) / 2;
                /*Definition of the projection*/
                glOrtho(midpt - (wd / 2), midpt + (wd / 2), _ortho_y_min, _ortho_y_max, _ortho_z_min, _ortho_z_max);
            } else {/* In the opposite situation we extend the Y axis */
                /* Midpoint in the Y axis */
                GLdouble midpt = (_ortho_y_min + _ortho_y_max) / 2;
                /*Definition of the projection*/
                glOrtho(_ortho_x_min, _ortho_x_max, midpt - (he / 2), midpt + (he / 2), _ortho_z_min, _ortho_z_max);
            }
            break;
        case 'k':
            eye = mult_vec(kameraO->aldaketaPila->matrix, kameraO->eye);
            center = mult_vec(kameraO->aldaketaPila->matrix, kameraO->center);
            up = mult_vec(kameraO->aldaketaPila->matrix, kameraO->up);

            glMatrixMode(GL_PROJECTION);
            glLoadIdentity();
            gluPerspective((GLfloat)kameraO->angeluaY, (GLfloat)(wd / he), kameraO->n, kameraO->f);
            break;
        case 'i':
            eye = mult_vec(kameraI->aldaketaPila->matrix, kameraI->eye);
            center = mult_vec(kameraI->aldaketaPila->matrix, kameraI->center);
            up = mult_vec(kameraI->aldaketaPila->matrix, kameraI->up);

            glMatrixMode(GL_PROJECTION);
            glLoadIdentity();
            gluPerspective((GLfloat)kameraI->angeluaY, (GLfloat)(wd / he), (GLfloat)kameraI->n, (GLfloat)kameraI->f);
            break;
    }

    /* Now we start drawing the object */
    glPushMatrix();
    glMatrixMode(GL_MODELVIEW);

    glLoadIdentity();
    /*Kamera kokatzen da*/
    if(kamera_mota!='o'){
        gluLookAt(eye[0],    eye[1],    eye[2],
                  center[0], center[1], center[2],
                  up[0],     up[1],     up[2]);
    }

    /*First, we draw the axes*/
    draw_axes();

    glPopMatrix();

    /*Now each of the objects in the list*/
    while (aux_obj != 0) {

        /* Select the color, depending on whether the current object is the selected one or not */
        if (aux_obj == _selected_object){
            glColor3f(KG_COL_SELECTED_R,KG_COL_SELECTED_G,KG_COL_SELECTED_B);
        }else{
            glColor3f(KG_COL_NONSELECTED_R,KG_COL_NONSELECTED_G,KG_COL_NONSELECTED_B);
        }

        /* Draw the object; for each face create a new polygon with the corresponding vertices */
        glLoadIdentity();

        /*Kamera kokatzen da*/
        if(kamera_mota!='o'){
            gluLookAt(eye[0],    eye[1],    eye[2],
                      center[0], center[1], center[2],
                      up[0],     up[1],     up[2]);
        }

        glMultMatrixd(aux_obj->matrix);

        for (f = 0; f < aux_obj->num_faces; f++) {
            glBegin(GL_POLYGON);
            for (v = 0; v < aux_obj->face_table[f].num_vertices; v++) {
                v_index = aux_obj->face_table[f].vertex_table[v];
                glVertex3d(aux_obj->vertex_table[v_index].coord.x,
                           aux_obj->vertex_table[v_index].coord.y,
                           aux_obj->vertex_table[v_index].coord.z);

            }
            glEnd();
        }
        aux_obj = aux_obj->next;
    }
    /*Do the actual drawing*/
    glFlush();
}
