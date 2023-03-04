#ifndef __FONT_H__
#define __FONT_H__	 

//常用ASCII表
//偏移量32 
//ASCII字符集: !"#$%&'()*+,-./0123456789:;<=>?@ABCDEFGHIJKLMNOPQRSTUVWXYZ[\]^_`abcdefghijklmnopqrstuvwxyz{|}~
//PC2LCD2002取模方式设置：阴码+逐列式+顺向+C51格式
//总共：2个字符集（16*16和24*24），用户可以自行新增其他分辨率的字符集。
//每个字符所占用的字节数为:(size/8+((size%8)?1:0))*(size/2),其中size:是字库生成时的点阵大小(12/16/24...)

//12*12 ASCII字符集点阵
extern const unsigned char asc2_1206[95][12];

//1608 ASCII字符集点阵
extern const unsigned char asc2_1608[95][16]; 
//2412 ASICII字符集点阵
extern const unsigned char asc2_2412[95][36];
//3216 ASICII字符集点阵
extern const unsigned char asc2_3216[95][64];


extern const unsigned char tfont24[];
extern const unsigned char tfont32[];
extern const unsigned char ASCII64[];


extern const unsigned char gImage_pic[4800];

extern const unsigned char gImage_AA[528];
extern const unsigned char gImage_A_RED[528];
extern const unsigned char gImage_A_GREEN[528];
extern const unsigned char gImage_A_yellow[528];

extern const unsigned char gImage_0[6700];
extern const unsigned char gImage_1[6700];
extern const unsigned char gImage_2[6700];
extern const unsigned char gImage_3[6700];
extern const unsigned char gImage_4[6700];
extern const unsigned char gImage_5[6700];

extern const unsigned char gImage_LED_NO[1152];
extern const unsigned char gImage_LED_RED[1152];
extern const unsigned char gImage_LED_GREEN[1152];
extern const unsigned char gImage_LED_YELLOW[1152];

#endif

