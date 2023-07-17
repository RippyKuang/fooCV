#include "imgproc.h"
#include "imgconf.h"
#include "matrix.h"
#include <math.h>
int main(){
	Matrix* A=newMat(3,3);

	float dta[]={1,5,4,
				2,0,3,
				5,8,2};
	A->data=dta;
	Vec* B=newMat(3,1);
	float dtb[]={12,9,5};
	B->data=dtb;
	Vec* lu=LUP_solve(A,B);
	 printMat(lu);

	return 0;
}
