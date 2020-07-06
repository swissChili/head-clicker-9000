#include "drw.h"
#include <raylib.h>

void drwxhair()
{
	int w = GetScreenWidth(),
		h = GetScreenHeight();

	DrawRectangle(w/2 - 2, h/2 - 2, 4, 4, GREEN);
}

void drwboard(Vector3 topright, int w, int h)
{
	DrawCube(topright, 0.5, w, h, BG);
}

#define TH 0.1

int drwtargets(Ray ray, Vector3 where, Vector2 targets[], int num)
{
	int res = -1;

	for (int i = 0; i < num; i++)
	{
		Vector3 pos =
		{
			where.x - 2,
			targets[i].y,
			targets[i].x - 5
		};

		Vector3 a =
		{
			pos.x - TH / 2,
			pos.y - TH / 2,
			pos.z - TH / 2
		}, b =
		{
			pos.x + TH / 2,
			pos.y + TH / 2,
			pos.z + TH / 2
		};

		BoundingBox boundingbox = {
			a,
			b
		};

		Color clr = (Color){ 226, 90, 154, 255 };

		if (CheckCollisionRayBox(ray, boundingbox))
		{
			res = i;
			clr = RED;
		}

		DrawCube(pos, TH, TH, TH, clr);	
	}

	return res;
}
