//----------------------------------------------------
// Copyright (c) 2014, SHENZHEN PENGRUI SOFT CO LTD. All rights reserved.

// Redistribution and use in source and binary forms, with or without
// modification, are permitted provided that the following conditions are met:

// 1. Redistributions of source code must retain the above copyright notice,
//    this list of conditions and the following disclaimer.
// 2. Redistributions in binary form must reproduce the above copyright notice,
//    this list of conditions and the following disclaimer in the documentation
//    and/or other materials provided with the distribution.

// THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
// AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
// IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
// ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE
// LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
// CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
// SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
// INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
// CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
// ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
// POSSIBILITY OF SUCH DAMAGE.
//-----------------------------------------------------------------------------
// Copyright (c) 2014 ����Ȩ�����������������޹�˾���С�����Ȩ�˱���һ��Ȩ����
//
// �����Ȩ�����ʹ���߷������������������£�����ʹ����ʹ�ü���ɢ����
// ������װԭʼ�뼰����λ��ִ����ʽ��Ȩ�������۴˰�װ�Ƿ񾭸�����Ȼ��
//
// 1. ���ڱ�����Դ�������ɢ�������뱣�������İ�Ȩ���桢�������б�����
//    ������������������
// 2. ���ڱ��׼�����λ��ִ����ʽ����ɢ���������������ļ��Լ�������������
//    ��ɢ����װ�е�ý�鷽ʽ����������֮��Ȩ���桢�������б����Լ�����
//    ������������

// �����������������Ǳ�������Ȩ�������Լ�����������״��"as is"���ṩ��
// ��������װ�����κ���ʾ��Ĭʾ֮�������Σ������������ھ��������Լ��ض�Ŀ
// �ĵ�������ΪĬʾ�Ե�������Ȩ�����˼�������֮�����ߣ������κ�������
// ���۳�����κ��������塢���۴�����Ϊ���Լ��ϵ���޹�ʧ������������Υ
// Լ֮��Ȩ��������ʧ������ԭ��ȣ����𣬶����κ���ʹ�ñ�������װ��������
// �κ�ֱ���ԡ�����ԡ�ż���ԡ������ԡ��ͷ��Ի��κν�����𺦣�����������
// �������Ʒ������֮���á�ʹ����ʧ��������ʧ��������ʧ��ҵ���жϵȵȣ���
// �����κ����Σ����ڸ���ʹ���ѻ���ǰ��֪���ܻ���ɴ����𺦵���������Ȼ��
//-----------------------------------------------------------------------------


#include "stdint.h"
#include "stdlib.h"
#include "stddef.h"
#include "string.h"

#include "board-config.h"
#include "gkernel.h"
#include <gui/gkernel/gk_display.h>
#include "cpu_peri.h"

#if 1

#if CN_LCD_PIXEL_FORMAT ==CN_SYS_PF_RGB565
#define LCD_BPP     16
#elif   CN_LCD_PIXEL_FORMAT ==CN_SYS_PF_ERGB8888
#define LCD_BPP     24
#else
#error LCD_PIXEL_FORMAT����֧��!
#endif


#define LCD_FRAME_RATE  50

#define VS_INV      1
#define HS_INV      1
#define VCLK_INV    1
#define VDEN_INV    1

#define VFPD    2
#define VBPD    2
#define VSPW    10

#define HFPD    2
#define HBPD    2
#define HSPW    41


//* VIDCON0

#define VIDOUT      (0)
#define L1_DATA16   (4)
#define L0_DATA16   (4)
#define PNRMODE     (0)
#define CLKVALUP    (1)
#define CLKVAL_F    (6)
#define CLKDIR      (1)
#define CLKSEL_F    (0)



//* WINCON1to4
#if(LCD_BPP==16)
#define BITSWP      (0) //shift on basis of half-word swap
#define BYTSWP      (0) //shift on basis of half-word swap
#define HAWSWP      (1) //shift on basis of half-word swap
#endif

#if(LCD_BPP==24)
#define BITSWP      (0) //shift on basis of half-word swap
#define BYTSWP      (0) //shift on basis of half-word swap
#define HAWSWP      (0) //shift on basis of half-word swap
#endif

#define WINCONx_4WORD_BURST     (2)
#define WINCONx_8WORD_BURST     (1)
#define WINCONx_16WORD_BURST        (0)
#define WINCONx_PLANE_BLENDING      (0)
#define WINCONx_PIXEL_BLENDING      (1)
#define WINCONx_1BPP_PALLET     (0)
#define WINCONx_2BPP_PALLET     (1)
#define WINCONx_4BPP_PALLET     (2)
#define WINCONx_8BPP_PALLET     (3)
#define WINCONx_8BPP_NO_PALLET      (4)
#define WINCONx_16BPP_565       (5)
#define WINCONx_16BPP_A555      (6)
#define WINCONx_16BPP_1555      (7)
#define WINCONx_18BPP_666       (8)
#define WINCONx_18BPP_A665      (9)
#define WINCONx_19BPP_A666      (10)
#define WINCONx_24BPP_888       (11)
#define WINCONx_24BPP_A887      (12)
#define WINCONx_25BPP_A888      (13)
#define WINCONx_ALPHA_MODE_0        (0)
#define WINCONx_ALPHA_MODE_1        (1)


static  u16 *pFrameBufferFG;    //ǰ̨��ʾ������.

u32 GK_GetPixelBm(struct RectBitmap *bitmap, s32 x,s32 y);

//----��ʼ��lcdӲ��------------------------------------------------------------
//����: ��ʼ��lcdӲ����
//����: ��
//����: ��
//��ע: ����������ֲ�ؼ�����
//----------------------------------------------------------------------------
static void __lcd_hard_init(u32 lcd_buffer_addr)
{
    u8 clk_div=0;
    u16 hsync_cnt,vclk_cnt;
    u32 clk_mhz,clk_lcd_src;

    struct GPIO_REG *gpio =GPIO_REG_BASE;
    struct LCD_REG *lcd =LCD_REG_BASE;

    gpio->MISCCR |= (1<<28);

    gpio->GPCCON = 0xAAAAAAAA;
    gpio->GPCUDP = 0xAAAAAAAA;

    gpio->GPDCON = 0xAAAAAAAA;
    gpio->GPDUDP = 0xAAAAAAAA;

    hsync_cnt = (HFPD+HBPD+HSPW+CN_LCD_XSIZE);
    vclk_cnt  = (VFPD+VBPD+VSPW+CN_LCD_YSIZE);

    lcd->WINCON0 &= ~0x01;
    lcd->WINCON1 &= ~0x01;
    lcd->VIDCON0 &= (~3); // ENVID Off
    //LCD_CLK =HCLK
    clk_lcd_src = (133*1000000);
   // clk_div = (u8)(clk_lcd_src/(hsync_cnt*vclk_cnt*LCD_FRAME_RATE))-1;
    clk_div = 7;

    lcd->VIDCON0 = (VIDOUT<<22)|(L1_DATA16<<19)|(L0_DATA16<<16)|(PNRMODE<<13)|(CLKVALUP<<12)|(clk_div<<6)|(0<<5)|(CLKDIR<<4)|(0<<2)|(0<<0);
    lcd->VIDCON1 = (VCLK_INV<<7)|(HS_INV<<6)|(VS_INV<<5)|(VDEN_INV<<4);
    lcd->VIDTCON0 = ((VBPD-1)<<16)|((VFPD-1)<<8)|(VSPW-1);
    lcd->VIDTCON1 = ((HBPD-1)<<16)|((HFPD-1)<<8)|(HSPW-1);
    lcd->VIDTCON2 = ((CN_LCD_YSIZE-1)<<11)|(CN_LCD_XSIZE-1);

    lcd->VIDOSD0A = (0<<11)|(0);
    lcd->VIDOSD0B = (CN_LCD_XSIZE-1)<<11|(CN_LCD_YSIZE-1);

    #if(LCD_BPP==16)
    lcd->WINCON0 = (BITSWP<<18)|(BYTSWP<<17)|(HAWSWP<<16)|(WINCONx_16WORD_BURST<<9)|(WINCONx_16BPP_565<<2); // 16word burst, 16bpp,

    lcd->VIDW00ADD0B0 = (u32)lcd_buffer_addr;
    lcd->VIDW00ADD1B0 = (u32)lcd_buffer_addr + CN_LCD_XSIZE*CN_LCD_YSIZE*2;
    lcd->VIDW00ADD2B0 = (0<<13)|(CN_LCD_XSIZE*2);
    #endif

    #if(LCD_BPP==24)
    lcd->rWINCON0 = (BITSWP<<18)|(BYTSWP<<17)|(HAWSWP<<16)|(WINCONx_16WORD_BURST<<9)|(WINCONx_24BPP_888<<2); // 16word burst, 24bpp,

    lcd->VIDW00ADD0B0 = (u32)lcd_buffer_addr;
    lcd->VIDW00ADD1B0 = (u32)lcd_buffer_addr + CN_LCD_XSIZE*CN_LCD_YSIZE*4;
    lcd->VIDW00ADD2B0 = (0<<13)|(CN_LCD_XSIZE*4);
    #endif


    lcd->DITHMODE = (1<<5)|(1<<3)|(1<<1)|(1<<0);

    lcd->WINCON0 |= 0x1;
    lcd->VIDCON0 |= (1<<5)|0x3;

}

static  void __lcd_backlight_onoff(bool_t onoff)
{
  // BKLIGHT: GPC0(tq2416)
  struct GPIO_REG *gpio =GPIO_REG_BASE;

  gpio->GPCCON &= ~(0x3<<0);
  gpio->GPCCON |=  (0x1<<0);

  if(onoff!=false)
  { //ON
      gpio->GPCDAT |=  (1<<0);

  }
  else
  { //OFF
      gpio->GPCDAT &= ~(1<<0);
  }

}

//----������ʾ��---------------------------------------------------------------
//����: ������driver�ṩ�̱�д�ģ�����������ʾ�����ֲ����ĺ���������Ӧ�ó����
//      ���룬�������豸���̶��塣
//����: disp����ʾ��ָ��
//����: true=�ɹ���false=ʧ��
//-----------------------------------------------------------------------------
bool_t __lcd_disp_ctrl(struct DisplayRsc *disp)
{
    return true;
}
//----��ʽ��pattern------------------------------------------------------------
//����: ���û��ύ����Ϊpattern��bitmap��ʽ����driver��ʶ��ĸ�ʽ��
//����: pattern����������ָ��
//      bitmap���û��ṩ��λͼ
//����: true=�ɹ���false=ʧ��
//-----------------------------------------------------------------------------
bool_t __lcd_format_pattern(u8 *pattern,struct RectBitmap *bitmap)
{
    s32 x,y;
    u32 color,bytes;

    if(bitmap->PixelFormat == CN_LCD_PIXEL_FORMAT)
        return true;
    bytes = 0;
    for(y = 0;y < bitmap->height;y++)
    {
        for(x = 0;x < bitmap->width;x++)
        {
            color = GK_GetPixelBm(bitmap,x,y);
            color = GK_ConvertPF2PF(CN_LCD_PIXEL_FORMAT,bitmap->PixelFormat,color,NULL);
            pattern[bytes] = (u8)color;
            pattern[bytes+1] = (u8)(color>>8);
            bytes += 2;
        }
    }
    return true;
}
//----λͼ�л�����-------------------------------------------------------------
//����: ��λͼ�л�һ�����أ�ֻ����bitmap�����ظ�ʽΪcn_custom_pfʱ������Ҫ���ơ�
//      ����Կ�������֧���Զ����ʽ��������ֱ�ӷ��ء�
//����: bitmap��Ŀ��λͼ
//      limit�����ƾ��Σ�ֻ�����ڸþ����ڲ��Ĳ���
//      x��y������
//      color����ͼ�õ���ɫ��cn_sys_pf_e8r8g8b8��ʽ
//      r2_code����Ԫ��դ������
//����: ��
//-----------------------------------------------------------------------------
bool_t __lcd_set_pixel_bm(struct RectBitmap *bitmap,
                     s32 x,s32 y,u32 color,u32 r2_code)
{
    return false;
}
//----λͼ�л���---------------------------------------------------------------
//����: ��λͼ�л�һ��ֱ�ߣ�������(x2,y2)�㣬ֻ������limit�޶��������ڵĲ��֡�
//����: bitmap��Ŀ��λͼ
//      limit�����ƾ��Σ�ֻ�����ڸþ����ڲ��Ĳ���
//      x1��y1��x2��y2������յ�����
//      color����ͼ�õ���ɫ��cn_sys_pf_e8r8g8b8��ʽ
//      r2_code����Ԫ��դ������
//����: true=�ɹ����ƣ�false=ʧ�ܣ���Ӳ�����ٻ�֧�ְ�r2_code����
//-----------------------------------------------------------------------------
bool_t __lcd_line_bm(struct RectBitmap *bitmap,struct Rectangle *limit,
                        s32 x1,s32 y1,s32 x2,s32 y2,u32 color,u32 r2_code)
{
    return false;
}
//----λͼ�л���(���˵�)-------------------------------------------------------
//����: ��λͼ�л�һ��ֱ�ߣ�ֻ������limit�޶��������ڵĲ��֡�
//����: bitmap��Ŀ��λͼ
//      limit�����ƾ��Σ�ֻ�����ڸþ����ڲ��Ĳ���
//      x1��y1��x2��y2������յ�����
//      color����ͼ�õ���ɫ��cn_sys_pf_e8r8g8b8��ʽ
//      r2_code����Ԫ��դ������
//����: true=�ɹ����ƣ�false=ʧ�ܣ���Ӳ�����ٻ�֧�ְ�r2_code����
//-----------------------------------------------------------------------------
bool_t __lcd_line_bm_ie(struct RectBitmap *bitmap,struct Rectangle *limit,
                        s32 x1,s32 y1,s32 x2,s32 y2,u32 color,u32 r2_code)
{
    return false;
}
//----λͼ��������-----------------------------------------------------------
//����: ��λͼ�еľ�����color��ɫ��䡣
//����: bitmap��Ŀ��λͼ
//      dst_rect�������ľ���
//      color�������ɫ��cn_sys_pf_e8r8g8b8��ʽ
//����: true=�ɹ����ƣ�false=ʧ��
//-----------------------------------------------------------------------------
bool_t __lcd_fill_rect_bm(struct RectBitmap *dst_bitmap,
                          struct Rectangle *Target,
                          struct Rectangle *Focus,
                          u32 Color0,u32 Color1,u32 Mode)
{
    s32 x, y;
    u16 pixel;
    u16 *dst,*p;

    if(Mode != CN_FILLRECT_MODE_N)
        return false;

    if(dst_bitmap->PixelFormat != CN_SYS_PF_RGB565)
        return false;

    pixel = GK_ConvertRGB24ToPF(CN_SYS_PF_RGB565,Color0);

    dst = (u16*)((u32)dst_bitmap->bm_bits
                      + Focus->top * dst_bitmap->linebytes);
    dst += Focus->left;

    for(y = Focus->top; y < Focus->bottom; y++)
    {
        p =dst;
        for(x=Focus->left; x<Focus->right;x++)
        {
            *p++ =pixel;
        }
        dst += dst_bitmap->linebytes >> 1;
    }
    return true;
}
//----bitmap��λ�鴫��---------------------------------------------------------
//����: ��һ��λͼ�е�һ�����������͵���һ����������λͼ�����ظ�ʽ������ͬ��
//      Դ��Ŀ��λͼ������ͬ��
//����: dst_bitmap��Ŀ��λͼ
//      dst_rect��Ŀ�����
//      src_bitmap��Դλͼ
//      xsrc��ysrc��Դλͼ�б����͵��������Ͻ�����
//      pat��patternָ��
//      bitmsk��rop4������Ҫ������
//      rop_code����Ԫ��դ������
//      transparentcolor��͸��ɫ
//����: true=�ɹ�,false=ʧ��
//-----------------------------------------------------------------------------
bool_t __lcd_blt_bm_to_bm(struct RectBitmap *dst_bitmap,
                        struct Rectangle *DstRect,
                        struct RectBitmap *src_bitmap,
                        struct Rectangle *SrcRect,
                        struct RopGroup RopCode,u32 HyalineColor)
{
    struct RopGroup Rop = { 0, 0, 0, CN_R2_COPYPEN, 0, 0, 0  };
    u16 *src_offset,*dst_offset;    //Դλͼ���󻺳������ܲ�����!!!
    u32 y;
    if((dst_bitmap->PixelFormat != CN_SYS_PF_RGB565)
      ||(src_bitmap->PixelFormat != CN_SYS_PF_RGB565)
      ||(memcmp(&RopCode, &Rop ,sizeof(struct RopGroup))!=0))
    {
        return false;
    }
    else
    {
        if((ptu32_t)src_bitmap->bm_bits & 1)    //Դλͼ�������Ƕ���ģ��
        {
        }else
        {
            dst_offset = (u16*)((ptu32_t)dst_bitmap->bm_bits
                                      + DstRect->top * dst_bitmap->linebytes);
            dst_offset += DstRect->left;

            src_offset = (u16*)((ptu32_t)src_bitmap->bm_bits
                                      + SrcRect->top * src_bitmap->linebytes);
            src_offset += SrcRect->left;

            for(y = DstRect->top; y < DstRect->bottom; y++)
            {
                memcpy(dst_offset,src_offset,(DstRect->right-DstRect->left)<<1);
                dst_offset += dst_bitmap->linebytes >> 1;
                src_offset += src_bitmap->linebytes >> 1;
            }
        }
    }
    return true;
}
//----��ȡλͼ�е�����---------------------------------------------------------
//����: ȡλͼ�е�һ�����أ�ֻ����bitmap�����ظ�ʽΪcn_custom_pfʱ������Ҫ��ȡ��
//      ����Կ�������֧���Զ����ʽ��������ֱ�ӷ���false��
//����: bitmap��Ŀ��λͼ
//      x��y������
//����: ��ȡ������ֵ��cn_sys_pf_e8r8g8b8��ʽ
//-----------------------------------------------------------------------------
u32 __lcd_get_pixel_bm(struct RectBitmap *bitmap,s32 x,s32 y)
{
    return 0;
}
//----��ȡbitmap�о��ο�-------------------------------------------------------
//����: ��һ��λͼ�еľ��ζ�ȡ����һ��λͼ�С�
//����: src��Դλͼ
//      rect������ȡ�ľ���
//      dest��������ε�λͼ���䳤��������rect��ͬ
//����: true=�ɹ���ȡ��false=ʧ�ܣ�ԭ��������ṩ�˲�֧�ֵ����ظ�ʽ
//-----------------------------------------------------------------------------
bool_t __lcd_get_rect_bm(struct RectBitmap *src,struct Rectangle *rect,
                     struct RectBitmap *dest)
{
    return false;
}
//----screen�л�����-----------------------------------------------------------
//����: ��screen�л�һ������.
//����: x��y����������
//      color����ɫ
//      r2_code����Ԫ��դ������
//����: true=�ɹ����ƣ�false=û�л��ƣ����������
//-----------------------------------------------------------------------------
bool_t __lcd_set_pixel_screen(s32 x,s32 y,u32 color,u32 rop2_code)
{
    u32 dest;
    u32 byteoffset;
    byteoffset = y*CN_LCD_XSIZE + x;

    color = GK_ConvertRGB24ToPF(CN_SYS_PF_RGB565,color);

    dest = (u32)pFrameBufferFG[byteoffset];
    dest = GK_BlendRop2(dest,color,rop2_code);
    pFrameBufferFG[byteoffset] = (u16)dest;
    return true;
}
//----screen�л���---------------------------------------------------------------
//����: ��screen�л�һ������ֱ�ߣ������˵㣬ֻ������limit�޶��������ڵĲ��֡���
//      ��֧�ֻ��ߵ�Ӳ�����٣�ֱ�ӷ���false��
//����: limit�����ƾ��Σ�ֻ�����ڸþ����ڲ��Ĳ���
//      x1��y1��x2��y2������յ�����
//      color����ͼ�õ���ɫ
//      r2_code����Ԫ��դ������
//����: true=�ɹ����ƣ�false=ʧ�ܣ���Ӳ�����ٻ�֧�ְ�r2_code����
//-----------------------------------------------------------------------------
bool_t __lcd_line_screen(struct Rectangle *limit,
                    s32 x1,s32 y1,s32 x2,s32 y2,u32 color,u32 r2_code)
{
    return false;
}
//----screen�л���(���˵�)------------------------------------------------------
//����: ��screen�л�һ��ֱ�ߣ�ֻ������limit�޶��������ڵĲ��֡�
//����: limit�����ƾ��Σ�ֻ�����ڸþ����ڲ��Ĳ���
//      x1��y1��x2��y2������յ�����
//      color����ͼ�õ���ɫ��cn_sys_pf_e8r8g8b8��ʽ
//      r2_code����Ԫ��դ������
//����: true=�ɹ����ƣ�false=ʧ�ܣ���Ӳ�����ٻ�֧�ְ�r2_code����
//-----------------------------------------------------------------------------
bool_t __lcd_line_screen_ie(struct Rectangle *limit,
                        s32 x1,s32 y1,s32 x2,s32 y2,u32 color,u32 r2_code)
{
    return false;
}
//----screen��������-----------------------------------------------------------
//����: ��screen�еľ�����color��ɫ��䣬color�ĸ�ʽ��cn_sys_pf_e8r8g8b8��
//����: dst_rect�������ľ���
//      color�������ɫ
//����: true=�ɹ����ƣ�false=ʧ��
//-----------------------------------------------------------------------------
bool_t __lcd_fill_rect_screen(struct Rectangle *Target,
                              struct Rectangle *Focus,
                              u32 Color0,u32 Color1,u32 Mode)
{
    int x,y;
    u32 pen;
    u16 *p;
    return false;

    if(Mode != CN_FILLRECT_MODE_N)
        return false;
    pen = __GK_ConvertColorToPF(CN_SYS_PF_RGB565,Color0);

    for(y=Focus->top;y<Focus->bottom;y++)
    {
        p =&pFrameBufferFG[y*CN_LCD_XSIZE];

        for(x=Focus->left;x<Focus->right;x++)
        {
            *p++ =pen;
        }
    }
    return true;
}

//----bitmap��screenλ�鴫��---------------------------------------------------
//����: ��һ��λͼ�е�һ�����������͵���һ����������λͼ�����ظ�ʽ������ͬ��
//      Դ��Ŀ��λͼ������ͬ��
//����: dst_rect��Ŀ�����
//      src_bitmap��Դλͼ
//      xsrc��ysrc��Դλͼ�б����͵��������Ͻ�����(��Դλͼ���Ͻ�����Ϊԭ��)
//����: true=�ɹ���false=ʧ��
//-----------------------------------------------------------------------------
bool_t __lcd_bm_to_screen(struct Rectangle *dst_rect,
                struct RectBitmap *src_bitmap,s32 xsrc,s32 ysrc)
{
    u32 size,double_width_src;
    u32 byteoffset_rect,byteoffset_bitmap;
    s32 y;

    if(src_bitmap->PixelFormat!=CN_LCD_PIXEL_FORMAT)
    {   //���Դλͼ��LCD��ʽ����ͬ
        return false;
    }

    double_width_src = src_bitmap->width*2;     //Դλͼһ����ռ���ֽ���
    //ÿһ��Ҫ�����͵��ֽ���
    size = (dst_rect->right-dst_rect->left)*(CN_LCD_PIXEL_FORMAT>>8)/8;
    //Դλͼ���Ͻ�������ֽ�ƫ����
    byteoffset_bitmap = ysrc*double_width_src + xsrc*2;
    //Ŀ��������Ͻ������˫�ֽ�ƫ��������Ϊpg_video_bufΪu16��ָ��
    //��Ϊ�Ǵ��͵�screen�ϣ�����ÿ��˫�ֽ���ȡcn_lcd_xsize
    byteoffset_rect = dst_rect->top*CN_LCD_XSIZE + dst_rect->left;

    //bitmap��screenλ�鴫��
    for(y = dst_rect->top;y < dst_rect->bottom;y++)
    {
        memcpy(&(pFrameBufferFG[byteoffset_rect]),
                    &src_bitmap->bm_bits[byteoffset_bitmap],size);
        byteoffset_bitmap += double_width_src;
        byteoffset_rect += CN_LCD_XSIZE;
    }
    return true;
}
//----��screen��ȡ����---------------------------------------------------------
//����: ��screen��ȡһ���أ���ת����cn_sys_pf_e8r8g8b8��cn_sys_pf_a8r8g8b8��ʽ��
//����: x��y������
//����: ������ɫֵ
//-----------------------------------------------------------------------------
u32 __lcd_get_pixel_screen(s32 x,s32 y)
{
    u32 r,g,b,color,offset;

    offset = (u32)pFrameBufferFG;
    offset += y*CN_LCD_XSIZE*2;
    offset += x*2;
    color = (u32)(*(u16*)offset);
    r = (color>>11) &0x1f;
    g = (color>>5) & 0x3f;
    b = color & 0x1f;
    return (r<<19) | (g<<10) | (b<<3);
}

//----��ȡbitmap�о��ο�-------------------------------------------------------
//����: ��һ��λͼ�еľ��ζ�ȡ����һ��λͼ�С�
//����: rect������ȡ�ľ���
//      dest��������ε�λͼ���䳤��������rect��ͬ
//����: true=�ɹ���ȡ��false=ʧ�ܣ�ԭ��������ṩ�˲�֧�ֵ����ظ�ʽ
//-----------------------------------------------------------------------------
bool_t __lcd_get_rect_screen(struct Rectangle *rect,struct RectBitmap *dest)
{
    return false;
}

////////////////////////////////////////////////////////

static struct DisplayRsc lcd_display;
static struct GkWinRsc   frame_win;

static  u16 lcd_buffer_fg[CN_LCD_XSIZE*CN_LCD_YSIZE];


#ifdef  CN_LCD_DRV_FRAME_BUFFER_EN

static struct RectBitmap frame_bm;


static  u16 lcd_buffer_bk[CN_LCD_XSIZE*CN_LCD_YSIZE];
static  u16 *pFrameBufferBK;    //��̨��ʾ������.
#endif

//----��ʼ��lcd�豸------------------------------------------------------------
//����: ��ʼ��lcd�豸��
//����: ��
//����: ��ʾ����Դָ��
//-----------------------------------------------------------------------------

struct DisplayRsc* ModuleInstall_LCD(const char *DisplayName,const char* HeapName)
{
    struct HeapCB *heap;

    __lcd_backlight_onoff(false);

    heap =M_FindHeap(HeapName);
    if(heap==NULL)
    {
        return NULL;
    }

   // pFrameBufferFG =lcd_buffer_fg;
    pFrameBufferFG =M_MallocHeap(CN_LCD_XSIZE*CN_LCD_YSIZE*2,heap,0);

    __lcd_hard_init(pFrameBufferFG);

    //�����ʼ��frame_buffer��desktop��z_topmost������Ա
#ifdef  CN_LCD_DRV_FRAME_BUFFER_EN

    pFrameBufferBK =lcd_buffer_bk;
    frame_bm.PixelFormat = CN_LCD_PIXEL_FORMAT;
    frame_bm.width = CN_LCD_XSIZE;
    frame_bm.height = CN_LCD_YSIZE;
    frame_bm.linebytes = CN_LCD_XSIZE*2;
    frame_bm.bm_bits = (u8*)pFrameBufferBK;
    frame_win.wm_bitmap =&frame_bm;

    lcd_display.frame_buffer = &frame_win;
    lcd_display.framebuf_direct = false;
    //lcd_display.reset_clip = false;
#else

    lcd_display.frame_buffer =NULL;
    lcd_display.framebuf_direct = true;
    //lcd_display.reset_clip = true;

#endif

    lcd_display.xmm = 0;
    lcd_display.ymm = 0;
    lcd_display.width = CN_LCD_XSIZE;
    lcd_display.height = CN_LCD_YSIZE;
    lcd_display.pixel_format = CN_LCD_PIXEL_FORMAT;


    lcd_display.draw.set_pixel_bm = __lcd_set_pixel_bm;
    lcd_display.draw.fill_rect_bm = __lcd_fill_rect_bm;
    lcd_display.draw.get_pixel_bm = __lcd_get_pixel_bm;
    lcd_display.draw.line_bm = __lcd_line_bm;
    lcd_display.draw.line_bm_ie = __lcd_line_bm_ie;
    lcd_display.draw.blt_bm_to_bm = __lcd_blt_bm_to_bm;
    lcd_display.draw.get_rect_bm = __lcd_get_rect_bm;
//    lcd_display.draw.check_raster = __lcd_check_raster;
    lcd_display.draw.set_pixel_screen = __lcd_set_pixel_screen;
    lcd_display.draw.line_screen = __lcd_line_screen;
    lcd_display.draw.line_screen_ie = __lcd_line_screen_ie;
    lcd_display.draw.fill_rect_screen = __lcd_fill_rect_screen;
    lcd_display.draw.bm_to_screen = __lcd_bm_to_screen;
    lcd_display.draw.get_pixel_screen = __lcd_get_pixel_screen;
    lcd_display.draw.get_rect_screen = __lcd_get_rect_screen;


    lcd_display.DisplayHeap =  heap;
    lcd_display.disp_ctrl = __lcd_disp_ctrl;

    if(GK_InstallDisplay(&lcd_display,DisplayName))
    {
        __lcd_backlight_onoff(true);
        return &lcd_display;
    }
    else
    {

        return NULL;
    }
}

#endif



