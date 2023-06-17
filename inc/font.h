#ifndef __FONT_H__
#define __FONT_H__

typedef enum
{
	PTT_FONT_TYPE_12,
	PTT_FONT_TYPE_16
} enFontType;

void font_pkg_init(void);
int font_get_16_bmp(unsigned short usUnicode, unsigned char *pBuf);
int font_display_test(unsigned short usUnicode);

int font_get_data(unsigned short usUnicode, enFontType iFont, unsigned char *pData);
int font_get_data_ex(unsigned short usUnicode, enFontType iFont, unsigned char *pData);

#endif
