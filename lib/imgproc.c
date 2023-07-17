/*
 * imgproc.c
 *
 *  Created on: 2023年4月29日
 *      Author: Kuang
 */

#include "imgproc.h"
#include "imgconf.h"
#include "paint.h"
#define PI 3.1415926
#define E 2.718281828459045
void BGR2GRAY(IMG *img) {
	unsigned char *graydata = (unsigned char*) malloc(
			sizeof(unsigned char) * img->w * img->h);
	for (int i = 0; i < img->h; i++)
		for (int j = 0; j < img->w; j++)
			graydata[i * img->w + j] = (unsigned char) (0.114
					* (float) img->data[(i * img->w + j) * 3]
					+ 0.578 * (float) img->data[(i * img->w + j) * 3 + 1]
					+ 0.299 * (float) img->data[(i * img->w + j) * 3 + 2]);



	free(img->data);
	img->data = graydata;
	img->chl = 1;
}
void conv(IMG *_img, float *kernel, int size, char padding) {
	if(size%2==0){
				printf("用奇数，傻逼\n");
				return;
	}
	unsigned char *srcimg = _img->data;
	if (padding == 1) {
		int w = _img->w;
		int h = _img->h;
		int dim = _img->chl;
		unsigned char *img = (unsigned char*) malloc(
				sizeof(unsigned char) * w * h * dim);
		int index = 0;
		for (int y = 0; y < h; y++) {
			for (int x = 0; x < w; x++) {
				for (int d = 0; d < dim; d++) {
					float res = 0;
					for (int i = -(size - 1) / 2; i < (size - 1) / 2 + 1; i++) {
						for (int j = -(size - 1) / 2; j < (size - 1) / 2 + 1;
								j++) {
							if (((y + i) * w + (x + j)) * dim + d
									> w * h * dim - 1
									|| ((y + i) * w + (x + j)) * dim + d < 0)
								res += 0;
							else
								res += (float) srcimg[((y + i) * w + (x + j))
										* dim + d]
										* kernel[(i + (size - 1) / 2) * size + j
													+ (size - 1) / 2];
						}
					}
					if (res < 0)
						res = -res;
					index++;
					img[(y * w + x) * dim + d] = (int) res;

				}
			}
		}
		_img->data = img;
		free(srcimg);
	} else {
		int w = _img->w;
		int h = _img->h;
		int dim = _img->chl;

		unsigned char *img = (unsigned char*) malloc(
				sizeof(unsigned char) * (_img->w - size + 1)
						* (_img->h - size + 1) * dim);

		int index = 0;
		for (int y = (size - 1) / 2; y < h - (size - 1) / 2; y++) {
			for (int x = (size - 1) / 2; x < w - (size - 1) / 2; x++) {
				for (int d = 0; d < dim; d++) {
					float res = 0;
					for (int i = -(size - 1) / 2; i < (size - 1) / 2 + 1; i++)
						for (int j = -(size - 1) / 2; j < (size - 1) / 2 + 1;
								j++)
							res += (float) srcimg[((y + i) * w + (x + j)) * dim
									+ d]
									* kernel[(i + (size - 1) / 2) * size + j
											+ (size - 1) / 2];

					if (res < 0)
						res = -res;

					img[index] = (unsigned char) res;
					index++;
				}

			}

		}
		_img->data = img;
		_img->w = _img->w - size + 1;
		_img->h = _img->h - size + 1;

		free(srcimg);

	}
}
void  freeIMG(void* img){
	free(((IMG*)img)->data);
	free((IMG*)img);
}
void f32_conv(F32_IMG *_img, float *kernel, int size, char padding) {
	if(size%2==0){
				printf("用奇数，傻逼\n");
				return;
	}
	float *srcimg = _img->data;
	if (padding == 1) {
		int w = _img->w;
		int h = _img->h;
		int dim = _img->chl;
		float *img = (float*) malloc(
				sizeof(float) * w * h * dim);

		int index = 0;
		for (int y = 0; y < h; y++) {
			for (int x = 0; x < w; x++) {
				for (int d = 0; d < dim; d++) {
					float res = 0;
					for (int i = -(size - 1) / 2; i < (size - 1) / 2 + 1; i++) {
						for (int j = -(size - 1) / 2; j < (size - 1) / 2 + 1;
								j++) {
							if (((y + i) * w + (x + j)) * dim + d
									> w * h * dim - 1
									|| ((y + i) * w + (x + j)) * dim + d < 0)
								res += 0;
							else{
								res +=  srcimg[((y + i) * w + (x + j))
											* dim + d]
											* kernel[size*((size - 1) / 2+i)+(size - 1) / 2+j];

							}

						}
					}

					if (res < 0)
						res = -res;
					index++;
					img[(y * w + x) * dim + d] =  res;

				}
			}
		}
		_img->data = img;
		free(srcimg);
	} else {
		int w = _img->w;
		int h = _img->h;
		int dim = _img->chl;

		float*img = (float*) malloc(
				sizeof(float) * (_img->w - size + 1)
						* (_img->h - size + 1) * dim);

		int index = 0;
		for (int y = (size - 1) / 2; y < h - (size - 1) / 2; y++) {
			for (int x = (size - 1) / 2; x < w - (size - 1) / 2; x++) {
				for (int d = 0; d < dim; d++) {
					float res = 0;
					for (int i = -(size - 1) / 2; i < (size - 1) / 2 + 1; i++)
						for (int j = -(size - 1) / 2; j < (size - 1) / 2 + 1;
								j++)
							res += srcimg[((y + i) * w + (x + j)) * dim
											+ d]
											* kernel[(i + (size - 1) / 2) * size + j
													+ (size - 1) / 2];

					if (res < 0)
						res = -res;

					img[index] = res;
					index++;
				}

			}

		}
		_img->data = img;
		_img->w = _img->w - size + 1;
		_img->h = _img->h - size + 1;

		free(srcimg);

	}
}
void*  imgcpy(void* src,int type){
	IMG* dst=(IMG*)malloc(sizeof(IMG));
	int chl,w,h;
	memcpy(&w,src,INT32);
	memcpy(&h,src+INT32,INT32);
	memcpy(&chl,src+2*INT32,INT32);
	dst->chl=chl;
	dst->w=w;
	dst->h=h;
	unsigned char* dst_data=(unsigned char*)malloc(type*chl*w*h);
	memcpy(dst_data,(((IMG*)src)->data),type*chl*w*h);
	dst->data=dst_data;
	return dst;
}


void gaussian_blur(void* img,int size,float sigma,char type){
		if(size%2==0){
			printf("用奇数，傻逼\n");
			return;
		}

	    float* kernel=(float*)malloc(sizeof(float)*size*size);
		for (int y=0;y<size;y++)
			for(int x=0;x<size;x++){
				kernel[x+y*size]=(1/(2*PI*sigma*sigma))*exp(-((x-size/2)*(x-size/2)+(y-size/2)*(y-size/2))/(2*sigma*sigma));

			}
		if(type==FLOAT32)
	    f32_conv(img, kernel,size, 1);
		else
			conv(img, kernel,size, 1);
		free(kernel);
}

void subIMG(void* img1,void* img2,int type){   //img1-img2
	if(type==FLOAT32){
		F32_IMG* f32_img1=(F32_IMG*)(img1);
		F32_IMG* f32_img2=(F32_IMG*)(img2);
		for(int x=0;x<f32_img1->w*f32_img1->h*f32_img1->chl;x++)
			f32_img1->data[x]=f32_img1->data[x]-f32_img2->data[x];
	}else{
		IMG* img1=(IMG*)(img1);
		IMG* img2=(IMG*)(img2);
		for(int x=0;x<img1->w*img1->h*img1->chl;x++)
		    img1->data[x]=img1->data[x]-img2->data[x];
	}
}


void* sub_sample(void* _img,int type){
	IMG* sub_IMG=(IMG*)malloc(sizeof(IMG));
	IMG* img=(IMG*)(_img);
	sub_IMG->chl=img->chl;
	sub_IMG->h=(img->h+1)/2;
	sub_IMG->w=(img->w+1)/2;

	unsigned char* data=(unsigned char*)malloc(type*sub_IMG->w*sub_IMG->h*img->chl);
	int index=0;
	int a,b;
	for(a=0;a<img->h;a+=2)
		for( b=0;b<img->w;b+=2){
			for(int c=0;c<img->chl;c++)
				memcpy(data+type*(index+c),img->data+((b+a*img->w)*img->chl+c)*type,type);
			index+=img->chl;

		}
	sub_IMG->data=data;
	return sub_IMG;
}
void norm(F32_IMG* img){
	printf("%d\n",img->chl);
	for(int c=0;c<img->chl;c++){
	int max=-999,min=999;
	for(int x=c;x<img->w*img->h*img->chl;x+=img->chl){
		if(img->data[x]>max) max=img->data[x];
		if(img->data[x]<min) min=img->data[x];
	}
	for(int x=c;x<img->w*img->h*img->chl;x+=img->chl)
		img->data[x]=255*(img->data[x]-min)/(max-min);
	}
}
F32_IMG* U8toF32(IMG* img){
	F32_IMG* f32=(F32_IMG*)malloc(sizeof(F32_IMG));
	float* f32_data=(float*)malloc(sizeof(float)*img->chl*img->w*img->h);
	for(int x=0;x<img->chl*img->w*img->h;x++)
		f32_data[x]=(float)img->data[x];

	f32->chl=img->chl;
	f32->w=img->w;
	f32->h=img->h;
	f32->data=f32_data;
	return f32;
}

IMG* F32toU8(F32_IMG* img){
	norm(img);
	IMG* u8=(IMG*)malloc(sizeof(IMG));
	unsigned char* u8_data=(unsigned char*)malloc(sizeof(unsigned char)*img->chl*img->w*img->h);
	for(int x=0;x<img->chl*img->w*img->h;x++){
		u8_data[x]=floor(img->data[x]);
	}
	u8->chl=img->chl;
	u8->w=img->w;
	u8->h=img->h;
	u8->data=u8_data;
	return u8;
}
F32_IMG** DoG(F32_IMG** img,float sigma,int n){
	F32_IMG** oct=(F32_IMG**)malloc(sizeof(F32_IMG*)*n);
	F32_IMG* i1=imgcpy(*img, FLOAT32);
	gaussian_blur(i1, 9, sigma, FLOAT32);
	for(int x=0;x<n;x++){
		F32_IMG* i2=imgcpy(i1, FLOAT32);
		gaussian_blur(i2, 9, sigma*pow(2,1/(n-2)), FLOAT32);
		sigma=sigma*pow(2,1/(n-2));
		F32_IMG* i3=imgcpy(i2, FLOAT32);
		subIMG(i3, i1,FLOAT32);
		oct[x]=i3;
		freeIMG(i1);
		i1=i2;
		if(x==n-3)
			*img=sub_sample(i2, FLOAT32);


	}
	return oct;

}

void find_extremum(int oct, int inter,IMG* img){
		IMG* grayimg=imgcpy(img, U8);
		BGR2GRAY(grayimg);
		COLOR red;
	        unsigned char c[3];
			c[0]=0;
			c[1]=0;
			c[2]=255;
			red.c=c;
		F32_IMG* f32_grayimg=U8toF32(grayimg);
		for(int i=0;i<oct;i++){
		F32_IMG** oct1 =DoG(&f32_grayimg, 1.6, inter);
		for (int x=0;x<inter;x++) norm(oct1[x]);
		for(int z=1;z<inter-1;z++){
			for(int x=inter; x<oct1[z]->w-inter;x++){
				for(int y=inter; y<oct1[z]->h-inter;y++){
					for(int a=-1;a<2;a++)
						for( int b=-1;b<2;b++)
						if((oct1[z]->data[oct1[z]->w*y+x]<=oct1[z-1]->data[oct1[z-1]->w*(y+a)+x+b]))
							goto min;

					for(int a=-1;a<2;a++)
						for( int b=-1;b<2;b++)
						if((oct1[z]->data[oct1[z]->w*y+x]<=oct1[z+1]->data[oct1[z+1]->w*(y+a)+x+b]))
							goto min;
					for(int a=-1;a<=1;a+=2)
						for( int b=-1;b<=1;b+=2)
						if((oct1[z]->data[oct1[z]->w*y+x]<=oct1[z]->data[oct1[z]->w*(y+a)+x+b]))
							goto min;
					draw_circle(img, x*(i+1), y*(i+1), 5, &red);

					goto end;
					min:;
					for(int a=-1;a<2;a++)
						for( int b=-1;b<2;b++)
						if((oct1[z]->data[oct1[z]->w*y+x]>=oct1[z-1]->data[oct1[z-1]->w*(y+a)+x+b]))
							goto end;

				   for(int a=-1;a<2;a++)
						for( int b=-1;b<2;b++)
						if((oct1[z]->data[oct1[z]->w*y+x]>=oct1[z+1]->data[oct1[z+1]->w*(y+a)+x+b]))
							goto end;
				  for(int a=-1;a<=1;a+=2)
						for( int b=-1;b<=1;b+=2)
						if((oct1[z]->data[oct1[z]->w*y+x]>=oct1[z]->data[oct1[z]->w*(y+a)+x+b]))
							goto end;
					draw_circle(img, x*(i+1), y*(i+1), 5, &red);

				    end:;
				}
			}
		}
		}
		saveBMPIMG("/home/rippy/workspace/LiteCV/src/extremum.bmp", img, 0);
}
