/*
 * imgconf.c
 *
 *  Created on: 2023年4月29日
 *      Author: Kuang
 *      七月五日更新： 修复了无法正常读取奇数宽度的图片问题
 */

#include "imgconf.h"



int readFileHeader(FILE *fp, bmp_file_header *bfHeader) {
	fseek(fp, 0, SEEK_SET);
	fread(bfHeader, sizeof(bmp_file_header), 1, fp);
	return 0;
}

int readInfoHeader(FILE *fp, bmp_info_header *biHeader) {
	fseek(fp, 14, SEEK_SET);
	fread(biHeader, sizeof(bmp_info_header), 1, fp);
	return 0;
}

int readPalette(FILE *fp, RGBQUAD *palette, int palette_size) {
	fseek(fp, 54, SEEK_SET);
	fread(palette, sizeof(RGBQUAD), palette_size, fp);
	return 0;
}

int readData(FILE *fp, unsigned char *data, bmp_file_header *bfHeader,
		bmp_info_header *info) {
	fseek(fp, bfHeader->off_bits, SEEK_SET);
	fread(data, sizeof(unsigned char), info->size_image, fp);
	return 0;
}

int writeFileHeader(FILE *fp, bmp_file_header *bfHeader) {
	fseek(fp, 0, SEEK_SET);
	fwrite(bfHeader, sizeof(bmp_file_header), 1, fp);
	return 0;
}

int writeInfoHeader(FILE *fp, bmp_info_header *biHeader) {
	fseek(fp, 14, SEEK_SET);
	fwrite(biHeader, sizeof(bmp_info_header), 1, fp);
	return 0;
}

int writePalette(FILE *fp, RGBQUAD *palette, int palette_size) {
	fseek(fp, 54, SEEK_SET);
	fwrite(palette, sizeof(RGBQUAD), palette_size, fp);
	return 0;
}

int writeData(FILE *fp, unsigned char *data, bmp_file_header *bfHeader,
		bmp_info_header *info) {
	fseek(fp, bfHeader->off_bits, SEEK_SET);
	fwrite(data, sizeof(unsigned char), info->size_image, fp);
	return 0;
}

BMPIMG* getBMPIMG(char *name, int palette_size) {
	BMPIMG *img = (BMPIMG*) malloc(sizeof(BMPIMG));
	FILE *fp = fopen(name, "r");
	if(fp==NULL) {
			printf("没打开文件，傻逼");
			return (BMPIMG*)NULL;
	}
	img->file = (bmp_file_header*) malloc(sizeof(bmp_file_header));
	img->info = (bmp_info_header*) malloc(sizeof(bmp_info_header));
	img->quad = (RGBQUAD*) malloc(sizeof(RGBQUAD));
	readFileHeader(fp, img->file);
	readInfoHeader(fp, img->info);
	readPalette(fp, img->quad, palette_size);
	img->data = (unsigned char*) malloc(
			sizeof(unsigned char) * img->info->size_image);
	readData(fp, img->data, img->file, img->info);
	img->w = img->info->width;
	img->h = img->info->height;
	return img;
}
IMG* getIMG( BMPIMG *bmpimg){
	int realRowSize =(bmpimg->info->bit_count*bmpimg->w+31)/32*4;
	int chl=bmpimg->info->bit_count/8;
	unsigned char* data = (unsigned char*) malloc(
				sizeof(unsigned char) * bmpimg->h *bmpimg->w*chl);

	int index=0;
		for(int h=0;h<bmpimg->h;h++){
			for(int w=0;w<bmpimg->w*chl;w++){
			data[index]=bmpimg->data[h*realRowSize+w];
				index++;
			}
		}
	IMG* img=(IMG*)malloc(sizeof(IMG));
	img->data=data;
	img->w=bmpimg->w;
	img->h=bmpimg->h;
	img->chl=chl;
	return img;

}
BMPIMG* IMG2BMP(IMG* img){
	int nofQUAD;
	if(img->chl==1){
		nofQUAD=256;
	}else{
		nofQUAD=0;
	}
	int realRowSize=(img->chl*8*img->w+31)/32*4;

	unsigned char *_img = (unsigned char*) malloc(sizeof(unsigned char) * realRowSize * (img->h) * img->chl);
	int index=0;
	for(int h=0;h<img->h;h++){
		for(int w=0;w<img->w*img->chl;w++){
			_img[index]=img->data[h*img->w*img->chl+w];
			index++;
		}

		for(int w=img->w*img->chl;w<realRowSize;w++){
			_img[index]=0;
			index++;
		}

	}

	BMPIMG *bmp = (BMPIMG*) malloc(sizeof(BMPIMG));
	bmp->file = (bmp_file_header*) malloc(sizeof(bmp_file_header));
	bmp->info = (bmp_info_header*) malloc(sizeof(bmp_info_header));
	bmp->quad = (RGBQUAD*) malloc(sizeof(RGBQUAD)*nofQUAD);
    bmp->file->type=19778;
    bmp->file->size=sizeof(bmp_file_header)+sizeof(bmp_info_header)+sizeof(RGBQUAD)*nofQUAD+sizeof(unsigned char)*img->w*img->h*img->chl;
    bmp->file->off_bits=sizeof(bmp_file_header)+sizeof(bmp_info_header)+sizeof(RGBQUAD)*nofQUAD;
    bmp->file->reserved1=0;
    bmp->file->reserved2=0;
    bmp->info->compression=0;
    bmp->info->size=40;
    bmp->info->width=img->w;
    bmp->info->height=img->h;
    bmp->info->planes=1;
    bmp->info->bit_count=8*img->chl;
    bmp->info->size_image=sizeof(unsigned char)*realRowSize*img->h;
    bmp->info->x_pels_permeter=0;
    bmp->info->y_pels_permeter=0;
    bmp->info->clr_important=0;
    bmp->info->clr_used=0;
    bmp->data=_img;
    bmp->h=img->h;
    bmp->w=img->w;
    for (int i = 0; i < nofQUAD; i++){
    	bmp->quad[i].rgbBlue = bmp->quad[i].rgbGreen = bmp->quad[i].rgbRed = i;
    }

	return bmp;
}
void saveBMPIMG(char *name, IMG *_img, int palette_size) {
	BMPIMG* img=IMG2BMP(_img);
	FILE *p = fopen(name, "wb");
	if(p==NULL)
		printf("没打开文件，傻逼");

	writeFileHeader(p, img->file);
	writeInfoHeader(p, img->info);
	writePalette(p, img->quad, palette_size);
	writeData(p, img->data, img->file, img->info);
}



