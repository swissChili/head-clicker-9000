#pragma once

#include <raylib.h>

#define BG (Color){ 45, 42, 56, 255 }

void drwxhair();
void drwboard(Vector3 topright, int w, int h);
int drwtargets(Ray ray, Vector3 where, Vector2 targets[], int num);