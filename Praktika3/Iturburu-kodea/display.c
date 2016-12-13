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

kamera kamera1;
extern char kamera_mota;

void camera_init(){
    /*Kamera hasiarazten da*/
    kamera1.eyeX = 0.0f;
    kamera1.eyeY = 0.0f;
    kamera1.eyeZ = 1.0f;
    kamera1.centerX = 0.0f;
    kamera1.centerY = 0.0f;
    kamera1.centerZ = -1.0f;
    kamera1.upX = 0.0f;
    kamera1.upY = 1.0f;
    kamera1.upZ = 1.0f;
    kamera1.angelua = 0.0f;
    kamera1.n = 0.1f;
    kamera1.f = 1000.0f;
    kamera1.birak = 0.0f;

    /*Kameraren matrizea hasiarazten da*/
    kamera1->matrix = malloc ( sizeof ( GLdouble )*16);
    kamera1->matrix[0]=kamera1.eyeX; kamera1->matrix[4]=kamera1.upX; kamera1->matrix[8]=kamera1.centerX; kamera1->matrix[12]=0;
    kamera1->matrix[1]=kamera1.eyeY; kamera1->matrix[5]=kamera1.upY; kamera1->matrix[9]=kamera1.centerY; kamera1->matrix[13]=0;
    kamera1->matrix[2]=kamera1.eyeZ; kamera1->matrix[6]=kamera1.upZ; kamera1->matrix[10]=kamera1.centerZ;kamera1->matrix[14]=0;
    kamera1->matrix[3]=0;            kamera1->matrix[7]=0;           kamera1->matrix[11]=0;              kamera1->matrix[15]=1;

}

/**
 * @brief Function to draw the axes
 */
void draw_axes()
{
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
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    GLdouble he = (_ortho_x_max - _ortho_x_min) / _window_ratio;
    GLdouble wd = (_ortho_y_max - _ortho_y_min) * _window_ratio;

    switch (kamera_mota) {
        case 'o':
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
            gluPerspective((GLfloat)kamera1.angelua, (GLfloat)(wd / he), (GLfloat)kamera1.n, (GLfloat)kamera1.f);

            gluLookAt(kamera1.eyeX,                 kamera1.eyeY,                 kamera1.eyeZ,
                      kamera1.eyeX+kamera1.centerX, kamera1.eyeY+kamera1.centerY, kamera1.eyeZ+kamera1.centerZ,
                      kamera1.upX,                  kamera1.upY,                  kamera1.upZ);
            break;
        case 'i':
            gluPerspective((GLfloat)kamera1.angelua, (GLfloat)(wd / he), (GLfloat)kamera1.n, (GLfloat)kamera1.f);

            gluLookAt(kamera1.eyeX,                 1.0f, kamera1.eyeZ,
                      kamera1.eyeX+kamera1.centerX, 1.0f, kamera1.eyeZ+kamera1.centerZ,
                      0.0f,                         1.0f, 0.0f);
            break;
    }

    /* Now we start drawing the object */
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    /*First, we draw the axes*/
    draw_axes();

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
