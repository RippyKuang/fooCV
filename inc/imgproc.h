/*
 * imgproc.h
 *
 *  Created on: 2023年4月29日
 *      Author: Kuang
 */

#ifndef INC_IMGPROC_H_
#define INC_IMGPROC_H_

#include <imgconf.h>
#include <math.h>
#define FLOAT32 sizeof(float)
#define U8 sizeof(unsigned char)
#define INT32 sizeof(unsigned int)
#pragma  pack(1)
void BGR2GRAY(IMG *img) ;
void conv(IMG *_img, float *kernel, int size,char padding);
void f32_conv(F32_IMG *_img, float *kernel, int size, char padding);
F32_IMG** DoG(F32_IMG** img,float sigma,int n);
IMG* F32toU8(F32_IMG* img);
void norm(F32_IMG* img);
F32_IMG* U8toF32(IMG* img);
void* sub_sample(void* _img,int type);
void subIMG(void* img1,void* img2,int type);
void gaussian_blur(void* img,int size,float sigma,char type);
void*  imgcpy(void* src,int type);
void  freeIMG(void* img);

#endif /* INC_IMGPROC_H_ */
