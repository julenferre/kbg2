#ifndef DISPLAY_H
#define DISPLAY_H

#include "definitions.h"

void display(void);
void reshape(int width, int height);

void traslazioa(object3d *aux_obj, char ardatza_arg, char norabidea_arg);
void tamainaAldaketa(object3d *aux_obj, char ardatza_arg, char norabidea_arg);
void biraketa(object3d *aux_obj, char ardatza_arg, char norabidea_arg);

#endif // DISPLAY_H
