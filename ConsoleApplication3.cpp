// ConsoleApplication3.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "lodepng.h"
#include "ConsoleApplication3.h"
#include <math.h>
#include <algorithm>

//Uses "Dawnbringer 16" Color pallet! 
RGB DB16[] = {
	{20 , 12 ,28	 },
	{68 , 36 ,52	 },
	{48 , 52 ,109 },
	{78 , 74 ,78 }	 ,
	{133, 76 ,48 }	 ,
	{52 , 101, 36 }  ,
	{208, 70 ,72	 }  ,
	{117, 113, 97}  ,
	{89 , 125, 206} ,
	{210, 125, 44 }  ,
	{133, 149, 161} ,
	{109, 170, 44}  ,
	{210, 170, 153} ,
	{109, 194, 202} ,
	{218, 212, 94 }  ,
	{222, 238, 214}
};

using namespace lodepng;
using namespace std;

int main()
{
	img a;

	lodepng::decode(a.p, a.w, a.h, "C:\\o\\in.png", LCT_RGB); //8bpp R,G,B 
	
	dither(&a, BAYER, DB16);

	lodepng::encode("C:\\o\\out.png", a.p, a.w, a.h, LCT_RGB);
	return 0;

}

img gen()
{
	img i;
	i.h = 512;
	i.w = 512;
	i.p = std::vector<u8>(512 * 512 * 3);

	for (int y = 0; y < 512; y++)
		for (int x = 0; x < 512; x++)
		{
			i.p[3 * 512 * y + x * 3] = x % 512 ^ y % 512;
			i.p[(3 * 512 * y + x * 3) + 1] = x % 512 ^ y % 256;
			i.p[(3 * 512 * y + x * 3) + 2] = x % 128 ^ y % 128;
		}
	return i;
}



void GetNearest(RGB* i, RGB P[]);
void GetBayer(RGB* i, double bi,RGB P[]);

double ColourDistance(RGB e1, RGB e2)
{
	long rmean = ((long)e1.r + (long)e2.r) / 2;
	long r = (long)e1.r - (long)e2.r;
	long g = (long)e1.g - (long)e2.g;
	long b = (long)e1.b - (long)e2.b;
	return (((512 + rmean)*r*r) >> 8) + 4 * g*g + (((767 - rmean)*b*b) >> 8);
}

void dither(img* a, bayer bi, RGB P[])
{
	for (int y = 0; y < a->h; y++)
	{
		for (int x = 0; x < a->w; x++)
		{
			int offset = ((3 * a->w*y) + 3 * x);

			RGB* c = (RGB*)&(a->p[offset]);
			GetBayer(c, BAYER[x%BAYER_SIZE][y%BAYER_SIZE],P);
			GetNearest(c, P);

		}
	}
}

void GetBayer(RGB* i, double bi, RGB P[])
{
	double b = bi*(255/17);
	i->r += b;
	i->g += b;
	i->b += b;
}

void GetNearest(RGB* i, RGB P[])
{
	double score; int idx = 0;
	for (int x = 0; x < 16; x++)
	{
		double s = ColourDistance(*i, P[x]);
		if (x == 0)
			score = s;
		else
			score = (s < score) ? s : score;
		idx = score == s ? x : idx;
	}
	*i = P[idx];
}
