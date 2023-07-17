/*
 * matrix.c
 *
 *  Created on: 2023年7月17日
 *      Author: rippy
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>
#include "matrix.h"
void* matMul(void* _mat_a,void* _mat_b){
	Matrix* mata=(Matrix*)_mat_a;
	Matrix* matb=(Matrix*)_mat_b;
	Matrix* res=(Matrix*)malloc(sizeof(Matrix));
	if(mata->col!=matb->row){
		printf("矩阵尺寸不匹配");
		return NULL;
	}
	res->data=(float*)malloc(sizeof(float)*(mata->row)*(matb->col));
	memset(res->data,0,sizeof(float)*(mata->row)*(matb->col));
	res->col=matb->col;
	res->row=mata->row;
	for(int x=0;x<res->col;x++)
		for(int y=0;y<res->row;y++)
			for(int i=0;i<mata->col;i++)
				res->data[y*res->col+x]+= mata->data[y*mata->col+i]*matb->data[x+i*matb->col];

	return res;
}
void printMat(void* _mat){
	Matrix* mat=(Matrix*)_mat;
	for(int y=0;y<mat->row;y++){
		for(int x=0;x<mat->col;x++)
			printf("%f ",mat->data[y*mat->col+x]);
		printf("\n");
	}
}
void* newMat(int row,int col){
	Matrix* A=(Matrix*)malloc(sizeof(Matrix));
	A->row=row;
	A->col=col;

	return A;
}
void* eye(int row){
	Matrix* A=(Matrix*)malloc(sizeof(Matrix));
	A->row=row;
	A->col=row;
	A->data=(float*)malloc(sizeof(float)*(A->row)*(A->row));
	memset(A->data,0,sizeof(float)*(A->row)*(A->row));
	for(int x=0;x<A->row;x++)
		A->data[x*A->col+x]=1;
	return A;
}
void freeMat(void* _m){
	Matrix* m=(Matrix*)(_m);
	free(m->data);
	free(m);
}
Matrix** LUP(Matrix* A){
	Matrix** lu=(Matrix**)malloc(sizeof(Matrix*)*3);
	Matrix* l=eye(A->row);
	Matrix* u=newMat(A->row,A->col);
	Matrix* p=eye(A->row);
	u->data=(float*)malloc(sizeof(float)*(u->row)*(u->row));
	memset(u->data,0,sizeof(float)*(u->row)*(u->row));

	lu[0]=l;
	lu[1]=u;
	lu[2]=p;
	for(int k=0;k<A->row;k++){
		float z=0;
		int k_dot=0;
		for(int i=k;i<A->row;i++){
			if(fabs(A->data[i*A->row+k])>z){
				z=fabs(A->data[i*A->row+k]);
				k_dot=i;
			}
		}
		for(int i=0;i<A->row;i++){
			float temp=p->data[k*A->row+i];
		p->data[k*A->row+i]=p->data[k_dot*A->row+i];
		p->data[k_dot*A->row+i]=temp;
		}

		for(int i=k;i<A->row;i++){
				float temp=A->data[k*A->row+i];
			    A->data[k*A->row+i]=A->data[k_dot*A->row+i];
			   A->data[k_dot*A->row+i]=temp;
		}

		for(int i=0;i<k;i++){
				float temp=l->data[k*A->row+i];
			    l->data[k*A->row+i]=l->data[k_dot*A->row+i];
			    l->data[k_dot*A->row+i]=temp;
		}

		u->data[k*u->row+k]=A->data[k*u->row+k];
		for(int i=k+1;i<A->row;i++){
			l->data[i*A->row+k]=A->data[i*A->row+k]/u->data[k*u->row+k];
			u->data[k*u->row+i]=A->data[k*u->row+i];
		}
		for(int i=k+1;i<A->row;i++)
			for(int j=k+1;j<A->row;j++)
				A->data[i*A->row+j]=A->data[i*A->row+j]-l->data[i*A->row+k]*u->data[k*u->row+j];
	}
	return lu;
}
Vec* LUP_solve(Matrix* A, Vec* b){
	Matrix** lu=LUP(A);
    Matrix* L=lu[0];
    Matrix* U=lu[1];
    Matrix* P=lu[2];
    int n=L->col;
    Vec* x= newMat(n, 1);
    Vec* y= newMat(n, 1);
    x->data=(float*)malloc(sizeof(float)*n);
    y->data=(float*)malloc(sizeof(float)*n);
    Matrix* b_dot=matMul(P, b);

    for(int i=0;i<n;i++){
    	float q=0;
    	for(int j=0;j<=i-1;j++)
    		q+=L->data[i*n+j]*y->data[j];

    	y->data[i]=b_dot->data[i]-q;
    }

    for(int i=n-1;i>=0;i--){
    	float q=0;
    	for(int j=n-1;j>i;j--)
    	    q+=U->data[i*n+j]*x->data[j];
    	x->data[i]=(y->data[i]-q)/U->data[i*n+i];
    }
    return x;
}
