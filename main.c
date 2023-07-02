#include "imgproc.h"
#include "imgconf.h"
#include <math.h>
int main() {
	BMPIMG* bmp_img=getBMPIMG("/home/rippy/workspace/fooCV/res/lenna.bmp", 0);
	IMG* img_0=getIMG(bmp_img);
	F32_IMG* img_1=U8toF32(img_0);
	F32_IMG** dog=DoG(&img_1,1.6,5);
	 	saveBMPIMG("/home/rippy/workspace/fooCV/res/Lenna_DoG_1.bmp",F32toU8(dog[0]), 0);
		saveBMPIMG("/home/rippy/workspace/fooCV/res/Lenna_DoG_2.bmp",F32toU8(dog[1]), 0);
		saveBMPIMG("/home/rippy/workspace/fooCV/res/Lenna_DoG_3.bmp",F32toU8(dog[2]), 0);
		saveBMPIMG("/home/rippy/workspace/fooCV/res/Lenna_DoG_4.bmp",F32toU8(dog[3]), 0);
		saveBMPIMG("/home/rippy/workspace/fooCV/res/Lenna_DoG_5.bmp",F32toU8(dog[4]), 0);
	dog=DoG(&img_1,1.6*pow(2,1/3),5);
		saveBMPIMG("/home/rippy/workspace/fooCV/res/Lenna_DoG_o2_1.bmp",F32toU8(dog[0]), 0);
		saveBMPIMG("/home/rippy/workspace/fooCV/res/Lenna_DoG_o2_2.bmp",F32toU8(dog[1]), 0);
		saveBMPIMG("/home/rippy/workspace/fooCV/res/Lenna_DoG_o2_3.bmp",F32toU8(dog[2]), 0);
		saveBMPIMG("/home/rippy/workspace/fooCV/res/Lenna_DoG_o2_4.bmp",F32toU8(dog[3]), 0);
		saveBMPIMG("/home/rippy/workspace/fooCV/res/Lenna_DoG_o2_5.bmp",F32toU8(dog[4]), 0);
			
	return 0;
}
