/*
 * paint.c
 *
 *  Created on: 2023年6月30日
 *      Author: rippy
 */

#include "paint.h"

void  setBit(IMG* img,int x,int y,COLOR* c){
    	unsigned char* data=img->data;
    	for(int i=0;i<img->chl;i++)
    	data[(y*img->w+x)*img->chl+i]=c->c[i];
}
void draw_circle(IMG* img,int x,int y, int r,COLOR* c){
		for(double d=0;d<2*3.1416;d+=0.01){
			setBit(img,x+floor((double)x*cos(d)),y+floor((double)y*sin(d)),c);
		}

}
