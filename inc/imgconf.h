/*
 * imgconf.h
 *
 *  Created on: 2023年4月29日
 *      Author: Kuang
 */

#ifndef INC_IMGCONF_H_
#define INC_IMGCONF_H_

#include <bits/stdint-intn.h>
#include <bits/stdint-uintn.h>
#include <bits/types/FILE.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>


//定义位图文件头结构体
typedef struct {
	uint16_t type; //位图文件的类型，必须为BM (1-2字节）
	uint32_t size; //位图文件的大小，以字节为单位（3-6字节，低位在前）
	uint16_t reserved1; //位图文件保留字，必须为0 (7-8字节）
	uint16_t reserved2; //位图文件保留字，必须为0 (9-10字节）
	uint32_t off_bits; //位图数据位置的地址偏移，即起始位置，以相对于位图（11-14字节，低位在前）
} __attribute__ ((packed)) bmp_file_header;

//定义位图信息头结构体
typedef struct {
	uint32_t size; //指这个机构的长度，为40
	int32_t width; //指定图像的宽度，单位是像素
	int32_t height; //指定图像的高度，单位是像素
	uint16_t planes; //平面数，必须为1，不用考虑
	uint16_t bit_count; //指定表示颜色是要用到的位数，常用值是1（黑白二色图），4（16色灰阶）、8（256色灰阶）和24（彩色）
	uint32_t compression; //指定位图是否压缩，有效的值是0、1、2、3、4、5
	uint32_t size_image; //指定实际的位图数据占用的字节数
	uint32_t x_pels_permeter; //指定设备的水平分辨率，每米像素数
	uint32_t y_pels_permeter; //同上，垂直分辨率
	uint32_t clr_used; //指定本图像实际用到的颜色数，如果该值为零，则用到的颜色数为2^bit_count
	uint32_t clr_important; // 指定本图象中重要的颜色数，如果该值为零，则认为所有的颜色都是重要的
} bmp_info_header;

//定义调色板结构体s
typedef struct {
	unsigned char rgbBlue; //指定蓝色强度
	unsigned char rgbGreen; //指定绿色强度
	unsigned char rgbRed; //指定红色强度
	unsigned char rgbReserved; //保留，设置为0
} RGBQUAD;

typedef struct {
	bmp_file_header *file;
	bmp_info_header *info;
	unsigned char *data;
	RGBQUAD *quad;
	unsigned int w;
	unsigned int h;
} BMPIMG;

typedef struct {
	unsigned int w;
	unsigned int h;
	unsigned int chl;
	unsigned char*  data;
} IMG;

typedef struct {
	unsigned int w;
	unsigned int h;
	unsigned int chl;
	float*  data;
} F32_IMG;


typedef struct{
	unsigned char* c;
} COLOR;
int readFileHeader(FILE *fp, bmp_file_header *bfHeader);
int readInfoHeader(FILE *fp, bmp_info_header *biHeader);
int readPalette(FILE *fp, RGBQUAD *palette, int palette_size);
int readData(FILE *fp, unsigned char *data, bmp_file_header *bfHeader,
		bmp_info_header *info);

int writeFileHeader(FILE *fp, bmp_file_header *bfHeader);
int writeInfoHeader(FILE *fp, bmp_info_header *biHeader);
int writePalette(FILE *fp, RGBQUAD *palette, int palette_size);
int writeData(FILE *fp, unsigned char *data, bmp_file_header *bfHeader,
		bmp_info_header *info);

BMPIMG* getBMPIMG(char *name, int palette_size);
IMG* getIMG(BMPIMG *bmpimg);
void saveBMPIMG(char *name, IMG *img, int palette_size);
BMPIMG* IMG2BMP(IMG* img);

#endif /* INC_IMGCONF_H_ */
