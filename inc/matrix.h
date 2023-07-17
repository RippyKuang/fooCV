/*
 * matrix.h
 *
 *  Created on: 2023年7月17日
 *      Author: rippy
 */

#ifndef INC_MATRIX_H_
#define INC_MATRIX_H_

typedef struct _Matrix{
	int row;
	int col;
	float* data;
}Matrix;

typedef struct _Vec{
	int row;
	int col;
	float* data;
}Vec;

void* matMul(void* _mat_a,void* _mat_b);
void printMat(void* _mat);
void* newMat(int row,int col);
void* eye(int row);
Matrix** LUP(Matrix* A);
Vec* LUP_solve(Matrix* A, Vec* b);
void freeMat(void* _m);
#endif /* INC_MATRIX_H_ */

