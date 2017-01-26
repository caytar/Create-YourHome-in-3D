#include <vector>
#include <iostream>
#include <string>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <glut.h>
#include "glui.h"
#include "Object3DS.h"

#define min(a, b) (((a)<(b))?(a):(b))
#define max(a, b) (((a)>(b))?(a):(b))
#define DEG2RAD M_PI/180.0
#define RAD2DEG 180.0/M_PI
#define WALL_SIZE 4

/* Selection Buffer */
#define SelBufferSize 512
/* Picking Stuff */
#define RENDER					1
#define SELECT					2
#define BUFSIZE 1024

#ifndef CALLBACK
#define CALLBACK
#endif

typedef void (*TessFuncPtr)();

using namespace std;


