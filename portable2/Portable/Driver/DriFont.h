#ifndef DIRFONT_H
#define DIRFONT_H


//����ASCII��
//ƫ����32 
//ASCII�ַ���: !"#$%&'()*+,-./0123456789:;<=>?@ABCDEFGHIJKLMNOPQRSTUVWXYZ[\]^_`abcdefghijklmnopqrstuvwxyz{|}~
//PC2LCD2002ȡģ��ʽ���ã�����+����ʽ+˳��+C51��ʽ
//�ܹ���2���ַ�����16*16��24*24�����û������������������ֱ��ʵ��ַ�����
//ÿ���ַ���ռ�õ��ֽ���Ϊ:(size/8+((size%8)?1:0))*(size/2),����size:���ֿ�����ʱ�ĵ����С(12/16/24...)

//12*12 ASCII�ַ�������
extern const unsigned char asc2_1206[95][12];

//1608 ASCII�ַ�������
extern const unsigned char asc2_1608[95][16]; 
//2412 ASICII�ַ�������
extern const unsigned char asc2_2412[95][36];
//3216 ASICII�ַ�������
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