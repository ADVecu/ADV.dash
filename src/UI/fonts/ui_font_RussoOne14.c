/*******************************************************************************
 * Size: 14 px
 * Bpp: 1
 * Opts: --bpp 1 --size 14 --font C:\Users\danie\Documents\GNVPerformance\ADVdash\SquerLine Project\assets\RussoOne-Regular.ttf -o C:\Users\danie\Documents\GNVPerformance\ADVdash\SquerLine Project\assets\ui_font_RussoOne14.c --format lvgl -r 0x20-0x7f --no-compress --no-prefilter
 ******************************************************************************/

#include "../ui.h"

#ifndef UI_FONT_RUSSOONE14
#define UI_FONT_RUSSOONE14 1
#endif

#if UI_FONT_RUSSOONE14

/*-----------------
 *    BITMAPS
 *----------------*/

/*Store the image of the glyphs*/
static LV_ATTRIBUTE_LARGE_CONST const uint8_t glyph_bitmap[] = {
    /* U+0020 " " */
    0x0,

    /* U+0021 "!" */
    0xff, 0xfc, 0x3c,

    /* U+0022 "\"" */
    0xde, 0xf7, 0xb0,

    /* U+0023 "#" */
    0x19, 0x86, 0xe1, 0xb1, 0xff, 0x7f, 0xcc, 0xc3,
    0x33, 0xfe, 0xff, 0x8d, 0x86, 0x60,

    /* U+0024 "$" */
    0x18, 0x7e, 0xfe, 0xc0, 0xc0, 0xc0, 0xfe, 0x7f,
    0x3, 0x3, 0xff, 0xfe, 0x18, 0x18,

    /* U+0025 "%" */
    0x70, 0xcd, 0x98, 0xd9, 0x8d, 0xb0, 0xff, 0x7,
    0x7e, 0xd, 0xf0, 0xdb, 0x19, 0xb1, 0x9b, 0x31,
    0xe0,

    /* U+0026 "&" */
    0x3e, 0x1f, 0x86, 0x1, 0x8c, 0x63, 0x1f, 0xff,
    0xff, 0xc, 0xc3, 0x3f, 0xc7, 0xf0,

    /* U+0027 "'" */
    0xff,

    /* U+0028 "(" */
    0x36, 0x66, 0xcc, 0xcc, 0xcc, 0xc6, 0x66, 0x30,

    /* U+0029 ")" */
    0xc6, 0x66, 0x33, 0x33, 0x33, 0x36, 0x66, 0xc0,

    /* U+002A "*" */
    0x32, 0xdf, 0xde, 0xfe, 0xd3, 0x0,

    /* U+002B "+" */
    0x30, 0x63, 0xff, 0xf3, 0x6, 0xc, 0x0,

    /* U+002C "," */
    0xf6,

    /* U+002D "-" */
    0xff, 0xf0,

    /* U+002E "." */
    0xf0,

    /* U+002F "/" */
    0xc, 0x18, 0x70, 0xc3, 0x87, 0xc, 0x38, 0x60,
    0xc3, 0x80,

    /* U+0030 "0" */
    0x7e, 0xff, 0xc3, 0xc3, 0xc3, 0xc3, 0xc3, 0xc3,
    0xc3, 0xff, 0x7e,

    /* U+0031 "1" */
    0x7f, 0xf3, 0x33, 0x33, 0x33, 0x30,

    /* U+0032 "2" */
    0xfd, 0xfc, 0x18, 0x30, 0xe3, 0x8f, 0x38, 0xe1,
    0xff, 0xf8,

    /* U+0033 "3" */
    0xfc, 0xfe, 0x6, 0x6, 0x6, 0x3e, 0x3e, 0x3,
    0x3, 0xff, 0xfe,

    /* U+0034 "4" */
    0x1c, 0xc, 0xe, 0x6, 0x7, 0x3, 0x33, 0x99,
    0xff, 0xff, 0x83, 0x1, 0x80,

    /* U+0035 "5" */
    0x7e, 0x7e, 0x60, 0x60, 0x7e, 0x7f, 0x3, 0x3,
    0x3, 0xff, 0xfe,

    /* U+0036 "6" */
    0x7e, 0xfe, 0xc0, 0xc0, 0xfe, 0xff, 0xc3, 0xc3,
    0xc3, 0xff, 0x7e,

    /* U+0037 "7" */
    0xff, 0xff, 0x7, 0x6, 0xe, 0xe, 0x1c, 0x1c,
    0x1c, 0x38, 0x38,

    /* U+0038 "8" */
    0x3e, 0x7f, 0x63, 0x63, 0x63, 0x7e, 0xff, 0xc3,
    0xc3, 0xff, 0x7e,

    /* U+0039 "9" */
    0x7e, 0xff, 0xc3, 0xc3, 0xc3, 0xff, 0x7f, 0x3,
    0x3, 0x7f, 0x7e,

    /* U+003A ":" */
    0xf0, 0xf,

    /* U+003B ";" */
    0xf0, 0xf, 0x60,

    /* U+003C "<" */
    0x6, 0x3d, 0xf7, 0x8f, 0xf, 0x87, 0x83,

    /* U+003D "=" */
    0xff, 0xf0, 0x3f, 0xfc,

    /* U+003E ">" */
    0x81, 0xc3, 0xe0, 0xf1, 0xef, 0x38, 0x40,

    /* U+003F "?" */
    0xfe, 0xff, 0x3, 0x3, 0x7, 0x3f, 0x3c, 0x30,
    0x0, 0x30, 0x30,

    /* U+0040 "@" */
    0x7f, 0xbf, 0xfc, 0x1f, 0x3f, 0xdf, 0xf6, 0x3d,
    0xff, 0x3b, 0xc0, 0x3f, 0xe7, 0xf8,

    /* U+0041 "A" */
    0x1e, 0x7, 0x81, 0xe0, 0xfc, 0x3f, 0xc, 0xc7,
    0x39, 0xfe, 0x7f, 0xb8, 0x7e, 0x1c,

    /* U+0042 "B" */
    0xfe, 0xff, 0xc3, 0xc3, 0xc3, 0xfe, 0xff, 0xc3,
    0xc3, 0xff, 0xfe,

    /* U+0043 "C" */
    0x7f, 0xff, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0,
    0xc0, 0xff, 0x7f,

    /* U+0044 "D" */
    0xfe, 0xff, 0xc3, 0xc3, 0xc3, 0xc3, 0xc3, 0xc3,
    0xc3, 0xff, 0xfe,

    /* U+0045 "E" */
    0xff, 0xff, 0xc0, 0xc0, 0xc0, 0xfe, 0xfe, 0xc0,
    0xc0, 0xff, 0xff,

    /* U+0046 "F" */
    0xff, 0xff, 0xc0, 0xc0, 0xc0, 0xfe, 0xfe, 0xc0,
    0xc0, 0xc0, 0xc0,

    /* U+0047 "G" */
    0x7e, 0xfe, 0xc0, 0xc0, 0xc0, 0xcf, 0xcf, 0xc3,
    0xc3, 0xff, 0x7f,

    /* U+0048 "H" */
    0xc3, 0xc3, 0xc3, 0xc3, 0xc3, 0xff, 0xff, 0xc3,
    0xc3, 0xc3, 0xc3,

    /* U+0049 "I" */
    0xff, 0xcc, 0x63, 0x18, 0xc6, 0x37, 0xfe,

    /* U+004A "J" */
    0x7b, 0xc6, 0x31, 0x8c, 0x63, 0x1f, 0xfc,

    /* U+004B "K" */
    0xc7, 0xc6, 0xce, 0xce, 0xdc, 0xfc, 0xfc, 0xcc,
    0xce, 0xc6, 0xc7,

    /* U+004C "L" */
    0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0,
    0xc0, 0xff, 0xff,

    /* U+004D "M" */
    0xc0, 0x7c, 0x1f, 0xc7, 0xf8, 0xff, 0xbf, 0xf7,
    0xf7, 0xde, 0x73, 0xce, 0x78, 0xf, 0x1, 0x80,

    /* U+004E "N" */
    0xc3, 0xe3, 0xf3, 0xf3, 0xfb, 0xdb, 0xdf, 0xcf,
    0xcf, 0xc7, 0xc3,

    /* U+004F "O" */
    0x7f, 0x7f, 0xf0, 0x78, 0x3c, 0x1e, 0xf, 0x7,
    0x83, 0xc1, 0xff, 0xdf, 0xc0,

    /* U+0050 "P" */
    0xfe, 0xff, 0xc3, 0xc3, 0xc3, 0xc3, 0xff, 0xfe,
    0xc0, 0xc0, 0xc0,

    /* U+0051 "Q" */
    0x7f, 0x7f, 0xf0, 0x78, 0x3c, 0x1e, 0xf, 0x7,
    0x83, 0xc1, 0xff, 0xdf, 0xc3, 0x81, 0xe0, 0x70,

    /* U+0052 "R" */
    0xfe, 0xff, 0xc3, 0xc3, 0xc3, 0xc3, 0xff, 0xfe,
    0xce, 0xc6, 0xc3,

    /* U+0053 "S" */
    0x7e, 0xfe, 0xc0, 0xc0, 0xc0, 0xfe, 0x7f, 0x3,
    0x3, 0xff, 0xfe,

    /* U+0054 "T" */
    0xff, 0xff, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18,
    0x18, 0x18, 0x18,

    /* U+0055 "U" */
    0xc1, 0xe0, 0xf0, 0x78, 0x3c, 0x1e, 0xf, 0x7,
    0x83, 0xc1, 0xff, 0xdf, 0xc0,

    /* U+0056 "V" */
    0xe1, 0xf8, 0x76, 0x19, 0xce, 0x73, 0x8c, 0xc3,
    0xf0, 0xfc, 0x1e, 0x7, 0x81, 0xe0,

    /* U+0057 "W" */
    0xe3, 0x1f, 0x9c, 0x7e, 0x79, 0x99, 0xee, 0x77,
    0xb9, 0xfe, 0xe7, 0xdf, 0xf, 0x3c, 0x3c, 0xf0,
    0xf3, 0xc3, 0x8e, 0x0,

    /* U+0058 "X" */
    0xe3, 0xb9, 0x9d, 0xc7, 0xc1, 0xe0, 0xe0, 0xf8,
    0x7c, 0x77, 0x39, 0xf8, 0xe0,

    /* U+0059 "Y" */
    0x61, 0x9c, 0xe7, 0x38, 0xcc, 0x3f, 0x7, 0x81,
    0xe0, 0x30, 0xc, 0x3, 0x0, 0xc0,

    /* U+005A "Z" */
    0xff, 0xff, 0x7, 0xe, 0x1c, 0x3c, 0x38, 0x70,
    0xe0, 0xff, 0xff,

    /* U+005B "[" */
    0xff, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcf, 0xf0,

    /* U+005C "\\" */
    0xe0, 0xc1, 0x83, 0x83, 0x6, 0xe, 0xc, 0x1c,
    0x18, 0x30,

    /* U+005D "]" */
    0xff, 0x33, 0x33, 0x33, 0x33, 0x33, 0x3f, 0xf0,

    /* U+005E "^" */
    0x18, 0x71, 0xb3, 0x6c, 0x60,

    /* U+005F "_" */
    0xff, 0xf0,

    /* U+0060 "`" */
    0xec,

    /* U+0061 "a" */
    0x7c, 0xfc, 0x1b, 0xff, 0xf8, 0xff, 0xbf,

    /* U+0062 "b" */
    0xc1, 0x83, 0x7, 0xef, 0xf8, 0xf1, 0xe3, 0xc7,
    0xff, 0xf0,

    /* U+0063 "c" */
    0x7f, 0xff, 0x6, 0xc, 0x18, 0x3f, 0xbf,

    /* U+0064 "d" */
    0x6, 0xc, 0x1b, 0xff, 0xf8, 0xf1, 0xe3, 0xc7,
    0xfd, 0xf8,

    /* U+0065 "e" */
    0x7d, 0xff, 0x1f, 0xff, 0xf8, 0x3f, 0xbf,

    /* U+0066 "f" */
    0x3e, 0xfd, 0x83, 0xf, 0xdf, 0x98, 0x30, 0x60,
    0xc1, 0x80,

    /* U+0067 "g" */
    0x7f, 0xff, 0x1e, 0x3c, 0x78, 0xff, 0xbf, 0x7,
    0xff, 0xf0,

    /* U+0068 "h" */
    0xc1, 0x83, 0x7, 0xef, 0xf8, 0xf1, 0xe3, 0xc7,
    0x8f, 0x18,

    /* U+0069 "i" */
    0x6c, 0x7e, 0xdb, 0x6d, 0x80,

    /* U+006A "j" */
    0x18, 0xc0, 0x31, 0x8c, 0x63, 0x18, 0xc6, 0x3f,
    0xf8,

    /* U+006B "k" */
    0xc1, 0x83, 0x6, 0x7c, 0xdb, 0xbe, 0x7c, 0xdd,
    0x9b, 0x38,

    /* U+006C "l" */
    0xcc, 0xcc, 0xcc, 0xcc, 0xcf, 0x70,

    /* U+006D "m" */
    0xdd, 0xef, 0xff, 0xc6, 0x3c, 0x63, 0xc6, 0x3c,
    0x63, 0xc6, 0x3c, 0x63,

    /* U+006E "n" */
    0xfd, 0xff, 0x1e, 0x3c, 0x78, 0xf1, 0xe3,

    /* U+006F "o" */
    0x7d, 0xff, 0x1e, 0x3c, 0x78, 0xff, 0xbe,

    /* U+0070 "p" */
    0xfd, 0xff, 0x1e, 0x3c, 0x78, 0xff, 0xfe, 0xc1,
    0x83, 0x0,

    /* U+0071 "q" */
    0x7f, 0xff, 0x1e, 0x3c, 0x78, 0xff, 0xbf, 0x6,
    0xc, 0x18,

    /* U+0072 "r" */
    0xdf, 0xfc, 0x30, 0xc3, 0xc, 0x30,

    /* U+0073 "s" */
    0x7e, 0xfe, 0xe0, 0xfe, 0x7e, 0x7, 0xfe, 0xfe,

    /* U+0074 "t" */
    0x61, 0x8f, 0xbe, 0x61, 0x86, 0x18, 0x7c, 0xf0,

    /* U+0075 "u" */
    0xc7, 0x8f, 0x1e, 0x3c, 0x78, 0xff, 0xbf,

    /* U+0076 "v" */
    0xe3, 0xe7, 0x66, 0x66, 0x7e, 0x3c, 0x3c, 0x3c,

    /* U+0077 "w" */
    0xe6, 0x3e, 0x77, 0x6f, 0x76, 0xf6, 0x7d, 0x67,
    0xde, 0x39, 0xe3, 0x9c,

    /* U+0078 "x" */
    0xe6, 0x6e, 0x7c, 0x3c, 0x3c, 0x7c, 0x6e, 0xe7,

    /* U+0079 "y" */
    0xe3, 0x67, 0x67, 0x76, 0x36, 0x3e, 0x3c, 0x1c,
    0x1c, 0x78, 0x70,

    /* U+007A "z" */
    0xff, 0xfc, 0x79, 0xe7, 0x9e, 0x3f, 0xff,

    /* U+007B "{" */
    0x3b, 0xd8, 0xc6, 0x33, 0x98, 0x63, 0x18, 0xc6,
    0x3c, 0xe0,

    /* U+007C "|" */
    0xff, 0xff, 0xff, 0xf0,

    /* U+007D "}" */
    0xe7, 0x8c, 0x63, 0x18, 0xe3, 0x31, 0x8c, 0x63,
    0x7b, 0x80,

    /* U+007E "~" */
    0x75, 0xfd, 0x70
};


/*---------------------
 *  GLYPH DESCRIPTION
 *--------------------*/

static const lv_font_fmt_txt_glyph_dsc_t glyph_dsc[] = {
    {.bitmap_index = 0, .adv_w = 0, .box_w = 0, .box_h = 0, .ofs_x = 0, .ofs_y = 0} /* id = 0 reserved */,
    {.bitmap_index = 0, .adv_w = 67, .box_w = 1, .box_h = 1, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 1, .adv_w = 63, .box_w = 2, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 4, .adv_w = 90, .box_w = 5, .box_h = 4, .ofs_x = 1, .ofs_y = 7},
    {.bitmap_index = 7, .adv_w = 164, .box_w = 10, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 21, .adv_w = 141, .box_w = 8, .box_h = 14, .ofs_x = 1, .ofs_y = -2},
    {.bitmap_index = 35, .adv_w = 193, .box_w = 12, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 52, .adv_w = 161, .box_w = 10, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 66, .adv_w = 47, .box_w = 2, .box_h = 4, .ofs_x = 1, .ofs_y = 7},
    {.bitmap_index = 67, .adv_w = 73, .box_w = 4, .box_h = 15, .ofs_x = 1, .ofs_y = -3},
    {.bitmap_index = 75, .adv_w = 73, .box_w = 4, .box_h = 15, .ofs_x = 0, .ofs_y = -3},
    {.bitmap_index = 83, .adv_w = 111, .box_w = 6, .box_h = 7, .ofs_x = 1, .ofs_y = 4},
    {.bitmap_index = 89, .adv_w = 121, .box_w = 7, .box_h = 7, .ofs_x = 1, .ofs_y = 2},
    {.bitmap_index = 96, .adv_w = 54, .box_w = 2, .box_h = 4, .ofs_x = 1, .ofs_y = -2},
    {.bitmap_index = 97, .adv_w = 105, .box_w = 6, .box_h = 2, .ofs_x = 1, .ofs_y = 4},
    {.bitmap_index = 99, .adv_w = 54, .box_w = 2, .box_h = 2, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 100, .adv_w = 105, .box_w = 7, .box_h = 11, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 110, .adv_w = 150, .box_w = 8, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 121, .adv_w = 91, .box_w = 4, .box_h = 11, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 127, .adv_w = 132, .box_w = 7, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 137, .adv_w = 137, .box_w = 8, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 148, .adv_w = 146, .box_w = 9, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 161, .adv_w = 134, .box_w = 8, .box_h = 11, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 172, .adv_w = 141, .box_w = 8, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 183, .adv_w = 125, .box_w = 8, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 194, .adv_w = 150, .box_w = 8, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 205, .adv_w = 141, .box_w = 8, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 216, .adv_w = 54, .box_w = 2, .box_h = 8, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 218, .adv_w = 54, .box_w = 2, .box_h = 10, .ofs_x = 1, .ofs_y = -2},
    {.bitmap_index = 221, .adv_w = 114, .box_w = 7, .box_h = 8, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 228, .adv_w = 110, .box_w = 6, .box_h = 5, .ofs_x = 1, .ofs_y = 3},
    {.bitmap_index = 232, .adv_w = 114, .box_w = 7, .box_h = 8, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 239, .adv_w = 130, .box_w = 8, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 250, .adv_w = 172, .box_w = 10, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 264, .adv_w = 159, .box_w = 10, .box_h = 11, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 278, .adv_w = 159, .box_w = 8, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 289, .adv_w = 139, .box_w = 8, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 300, .adv_w = 161, .box_w = 8, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 311, .adv_w = 142, .box_w = 8, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 322, .adv_w = 140, .box_w = 8, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 333, .adv_w = 157, .box_w = 8, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 344, .adv_w = 164, .box_w = 8, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 355, .adv_w = 94, .box_w = 5, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 362, .adv_w = 103, .box_w = 5, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 369, .adv_w = 151, .box_w = 8, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 380, .adv_w = 138, .box_w = 8, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 391, .adv_w = 202, .box_w = 11, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 407, .adv_w = 164, .box_w = 8, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 418, .adv_w = 164, .box_w = 9, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 431, .adv_w = 159, .box_w = 8, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 442, .adv_w = 164, .box_w = 9, .box_h = 14, .ofs_x = 1, .ofs_y = -3},
    {.bitmap_index = 458, .adv_w = 161, .box_w = 8, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 469, .adv_w = 150, .box_w = 8, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 480, .adv_w = 139, .box_w = 8, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 491, .adv_w = 168, .box_w = 9, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 504, .adv_w = 159, .box_w = 10, .box_h = 11, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 518, .adv_w = 220, .box_w = 14, .box_h = 11, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 538, .adv_w = 148, .box_w = 9, .box_h = 11, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 551, .adv_w = 150, .box_w = 10, .box_h = 11, .ofs_x = -1, .ofs_y = 0},
    {.bitmap_index = 565, .adv_w = 137, .box_w = 8, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 576, .adv_w = 81, .box_w = 4, .box_h = 15, .ofs_x = 1, .ofs_y = -3},
    {.bitmap_index = 584, .adv_w = 105, .box_w = 7, .box_h = 11, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 594, .adv_w = 81, .box_w = 4, .box_h = 15, .ofs_x = 0, .ofs_y = -3},
    {.bitmap_index = 602, .adv_w = 114, .box_w = 7, .box_h = 5, .ofs_x = 0, .ofs_y = 6},
    {.bitmap_index = 607, .adv_w = 105, .box_w = 6, .box_h = 2, .ofs_x = 1, .ofs_y = -3},
    {.bitmap_index = 609, .adv_w = 56, .box_w = 3, .box_h = 2, .ofs_x = 0, .ofs_y = 8},
    {.bitmap_index = 610, .adv_w = 133, .box_w = 7, .box_h = 8, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 617, .adv_w = 139, .box_w = 7, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 627, .adv_w = 123, .box_w = 7, .box_h = 8, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 634, .adv_w = 141, .box_w = 7, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 644, .adv_w = 134, .box_w = 7, .box_h = 8, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 651, .adv_w = 101, .box_w = 7, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 661, .adv_w = 139, .box_w = 7, .box_h = 11, .ofs_x = 1, .ofs_y = -3},
    {.bitmap_index = 671, .adv_w = 141, .box_w = 7, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 681, .adv_w = 72, .box_w = 3, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 686, .adv_w = 67, .box_w = 5, .box_h = 14, .ofs_x = -2, .ofs_y = -3},
    {.bitmap_index = 695, .adv_w = 134, .box_w = 7, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 705, .adv_w = 76, .box_w = 4, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 711, .adv_w = 207, .box_w = 12, .box_h = 8, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 723, .adv_w = 141, .box_w = 7, .box_h = 8, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 730, .adv_w = 141, .box_w = 7, .box_h = 8, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 737, .adv_w = 141, .box_w = 7, .box_h = 11, .ofs_x = 1, .ofs_y = -3},
    {.bitmap_index = 747, .adv_w = 139, .box_w = 7, .box_h = 11, .ofs_x = 1, .ofs_y = -3},
    {.bitmap_index = 757, .adv_w = 103, .box_w = 6, .box_h = 8, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 763, .adv_w = 130, .box_w = 8, .box_h = 8, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 771, .adv_w = 99, .box_w = 6, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 779, .adv_w = 143, .box_w = 7, .box_h = 8, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 786, .adv_w = 130, .box_w = 8, .box_h = 8, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 794, .adv_w = 197, .box_w = 12, .box_h = 8, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 806, .adv_w = 123, .box_w = 8, .box_h = 8, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 814, .adv_w = 128, .box_w = 8, .box_h = 11, .ofs_x = 0, .ofs_y = -3},
    {.bitmap_index = 825, .adv_w = 120, .box_w = 7, .box_h = 8, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 832, .adv_w = 83, .box_w = 5, .box_h = 15, .ofs_x = 1, .ofs_y = -3},
    {.bitmap_index = 842, .adv_w = 67, .box_w = 2, .box_h = 14, .ofs_x = 1, .ofs_y = -3},
    {.bitmap_index = 846, .adv_w = 83, .box_w = 5, .box_h = 15, .ofs_x = 0, .ofs_y = -3},
    {.bitmap_index = 856, .adv_w = 112, .box_w = 7, .box_h = 3, .ofs_x = 0, .ofs_y = 4}
};

/*---------------------
 *  CHARACTER MAPPING
 *--------------------*/



/*Collect the unicode lists and glyph_id offsets*/
static const lv_font_fmt_txt_cmap_t cmaps[] =
{
    {
        .range_start = 32, .range_length = 95, .glyph_id_start = 1,
        .unicode_list = NULL, .glyph_id_ofs_list = NULL, .list_length = 0, .type = LV_FONT_FMT_TXT_CMAP_FORMAT0_TINY
    }
};

/*-----------------
 *    KERNING
 *----------------*/


/*Pair left and right glyphs for kerning*/
static const uint8_t kern_pair_glyph_ids[] =
{
    3, 21,
    3, 34,
    8, 21,
    8, 34,
    11, 21,
    11, 34,
    14, 18,
    14, 19,
    14, 20,
    14, 24,
    14, 34,
    14, 43,
    14, 53,
    14, 55,
    14, 56,
    14, 58,
    14, 59,
    17, 24,
    19, 21,
    20, 20,
    20, 24,
    21, 3,
    21, 8,
    21, 11,
    21, 18,
    21, 19,
    21, 24,
    21, 63,
    21, 65,
    22, 18,
    22, 24,
    23, 18,
    23, 24,
    24, 13,
    24, 15,
    24, 21,
    25, 24,
    26, 24,
    34, 3,
    34, 8,
    34, 11,
    34, 14,
    34, 36,
    34, 40,
    34, 48,
    34, 50,
    34, 53,
    34, 54,
    34, 55,
    34, 56,
    34, 58,
    34, 63,
    34, 65,
    34, 87,
    34, 88,
    34, 90,
    35, 53,
    35, 55,
    35, 56,
    35, 57,
    35, 58,
    35, 59,
    36, 14,
    36, 87,
    36, 88,
    36, 90,
    37, 34,
    37, 53,
    37, 55,
    37, 57,
    37, 58,
    37, 59,
    39, 13,
    39, 14,
    39, 15,
    39, 34,
    39, 43,
    39, 66,
    39, 68,
    39, 69,
    39, 70,
    39, 71,
    39, 72,
    39, 78,
    39, 79,
    39, 80,
    39, 81,
    39, 82,
    39, 83,
    39, 84,
    39, 85,
    39, 86,
    39, 87,
    39, 88,
    39, 89,
    39, 90,
    39, 91,
    40, 53,
    40, 55,
    40, 56,
    40, 58,
    43, 34,
    44, 14,
    44, 36,
    44, 40,
    44, 48,
    44, 50,
    45, 3,
    45, 8,
    45, 11,
    45, 14,
    45, 53,
    45, 55,
    45, 56,
    45, 58,
    45, 63,
    45, 65,
    45, 87,
    45, 88,
    45, 90,
    48, 34,
    48, 55,
    48, 56,
    48, 57,
    48, 58,
    49, 13,
    49, 15,
    49, 34,
    49, 55,
    49, 57,
    49, 58,
    50, 34,
    50, 55,
    50, 57,
    50, 58,
    52, 34,
    52, 53,
    52, 55,
    52, 56,
    52, 57,
    52, 58,
    53, 13,
    53, 14,
    53, 15,
    53, 34,
    53, 43,
    53, 66,
    53, 68,
    53, 69,
    53, 70,
    53, 71,
    53, 72,
    53, 78,
    53, 79,
    53, 80,
    53, 81,
    53, 82,
    53, 83,
    53, 84,
    53, 86,
    53, 87,
    53, 88,
    53, 89,
    53, 90,
    53, 91,
    54, 34,
    55, 13,
    55, 14,
    55, 15,
    55, 34,
    55, 36,
    55, 40,
    55, 43,
    55, 48,
    55, 50,
    55, 52,
    55, 66,
    55, 68,
    55, 69,
    55, 70,
    55, 72,
    55, 78,
    55, 79,
    55, 80,
    55, 81,
    55, 82,
    55, 83,
    55, 84,
    55, 86,
    55, 91,
    56, 13,
    56, 14,
    56, 15,
    56, 34,
    56, 36,
    56, 40,
    56, 43,
    57, 36,
    57, 40,
    57, 48,
    57, 50,
    58, 13,
    58, 14,
    58, 15,
    58, 34,
    58, 36,
    58, 40,
    58, 43,
    58, 48,
    58, 50,
    58, 52,
    58, 66,
    58, 68,
    58, 69,
    58, 70,
    58, 72,
    58, 78,
    58, 79,
    58, 80,
    58, 81,
    58, 82,
    58, 83,
    58, 84,
    58, 86,
    58, 87,
    58, 88,
    58, 89,
    58, 90,
    58, 91,
    59, 14,
    63, 21,
    63, 34,
    65, 21,
    65, 34,
    66, 87,
    66, 88,
    66, 90,
    67, 87,
    67, 88,
    67, 89,
    67, 90,
    70, 87,
    70, 88,
    70, 89,
    70, 90,
    71, 13,
    71, 15,
    71, 66,
    71, 77,
    75, 75,
    76, 68,
    76, 69,
    76, 70,
    76, 72,
    76, 80,
    76, 82,
    77, 71,
    77, 72,
    77, 85,
    77, 87,
    77, 88,
    77, 90,
    80, 87,
    80, 88,
    80, 89,
    80, 90,
    81, 87,
    81, 88,
    81, 89,
    81, 90,
    83, 13,
    83, 15,
    83, 66,
    83, 68,
    83, 69,
    83, 70,
    83, 72,
    83, 75,
    83, 80,
    83, 82,
    84, 74,
    84, 87,
    84, 88,
    84, 90,
    85, 14,
    85, 66,
    85, 68,
    85, 69,
    85, 70,
    85, 72,
    85, 74,
    85, 77,
    85, 80,
    85, 82,
    85, 85,
    85, 87,
    85, 88,
    85, 90,
    87, 13,
    87, 15,
    87, 66,
    87, 68,
    87, 69,
    87, 70,
    87, 72,
    87, 80,
    87, 82,
    88, 13,
    88, 15,
    88, 66,
    88, 68,
    88, 69,
    88, 70,
    88, 72,
    88, 80,
    88, 82,
    89, 68,
    89, 69,
    89, 70,
    89, 72,
    89, 80,
    89, 82,
    90, 13,
    90, 15,
    90, 66,
    90, 68,
    90, 69,
    90, 70,
    90, 72,
    90, 80,
    90, 82
};

/* Kerning between the respective left and right glyphs
 * 4.4 format which needs to scaled with `kern_scale`*/
static const int8_t kern_pair_values[] =
{
    -9, -13, -9, -13, -9, -13, -9, -7,
    -7, -11, -7, -7, -13, -7, -4, -11,
    -9, -4, -9, -4, -4, -9, -9, -9,
    -11, 4, -13, -9, -9, -7, -4, -7,
    -4, -11, -11, -9, -4, -4, -13, -13,
    -13, -7, -4, -4, -4, -4, -16, -4,
    -16, -11, -18, -13, -13, -7, -4, -7,
    -4, -4, -4, -4, -4, -2, -7, -9,
    -9, -9, -7, -4, -4, -4, -4, -2,
    -18, -7, -18, -13, -11, -9, -9, -9,
    -9, -4, -9, -4, -4, -9, -4, -9,
    -9, -4, -4, -4, -9, -9, -9, -9,
    -9, -11, -9, -7, -9, -7, -7, -4,
    -4, -4, -4, -11, -11, -11, -9, -27,
    -22, -18, -27, -11, -11, -9, -9, -9,
    -4, -4, 0, -4, -4, -18, -18, -13,
    0, -4, -4, -4, -4, -4, -4, -4,
    -11, -7, -7, -4, -7, -18, -13, -18,
    -16, -11, -11, -11, -11, -11, -7, -11,
    -11, -11, -11, -11, -11, -11, -11, -11,
    -11, -11, -11, -11, -11, -4, -18, -7,
    -18, -16, -4, -4, -11, -4, -4, 0,
    -9, -7, -7, -7, -7, -7, -7, -7,
    -7, -7, -7, -7, -7, -4, -11, -4,
    -11, -11, -4, -4, -9, -4, -4, -4,
    -4, -18, -11, -18, -18, -4, -4, -11,
    -4, -4, 0, -11, -11, -11, -11, -11,
    -7, -7, -11, -7, -11, -7, -11, -7,
    -7, -7, -7, -7, -7, -9, -9, -13,
    -9, -13, -2, -2, -2, -2, -2, -2,
    -2, -2, -2, -2, -2, -11, -11, -7,
    4, 9, -2, -2, -2, -2, -2, -2,
    -9, -4, -4, -9, -9, -9, -2, -2,
    -2, -2, -2, -2, -2, -2, -11, -11,
    -9, -4, -4, -4, -4, -4, -4, -4,
    -2, -4, -4, -4, -4, -4, -2, -2,
    -2, -4, -4, -4, -4, -4, -4, -4,
    -4, -4, -9, -9, -4, -2, -2, -2,
    -2, -2, -2, -7, -7, -4, -2, -2,
    -2, -2, -2, -2, -2, -2, -2, -2,
    -2, -2, -7, -7, -4, -2, -2, -2,
    -2, -2, -2
};

/*Collect the kern pair's data in one place*/
static const lv_font_fmt_txt_kern_pair_t kern_pairs =
{
    .glyph_ids = kern_pair_glyph_ids,
    .values = kern_pair_values,
    .pair_cnt = 331,
    .glyph_ids_size = 0
};

/*--------------------
 *  ALL CUSTOM DATA
 *--------------------*/

#if LV_VERSION_CHECK(8, 0, 0)
/*Store all the custom data of the font*/
static  lv_font_fmt_txt_glyph_cache_t cache;
static const lv_font_fmt_txt_dsc_t font_dsc = {
#else
static lv_font_fmt_txt_dsc_t font_dsc = {
#endif
    .glyph_bitmap = glyph_bitmap,
    .glyph_dsc = glyph_dsc,
    .cmaps = cmaps,
    .kern_dsc = &kern_pairs,
    .kern_scale = 16,
    .cmap_num = 1,
    .bpp = 1,
    .kern_classes = 0,
    .bitmap_format = 0,
#if LV_VERSION_CHECK(8, 0, 0)
    .cache = &cache
#endif
};


/*-----------------
 *  PUBLIC FONT
 *----------------*/

/*Initialize a public general font descriptor*/
#if LV_VERSION_CHECK(8, 0, 0)
const lv_font_t ui_font_RussoOne14 = {
#else
lv_font_t ui_font_RussoOne14 = {
#endif
    .get_glyph_dsc = lv_font_get_glyph_dsc_fmt_txt,    /*Function pointer to get glyph's data*/
    .get_glyph_bitmap = lv_font_get_bitmap_fmt_txt,    /*Function pointer to get glyph's bitmap*/
    .line_height = 15,          /*The maximum line height required by the font*/
    .base_line = 3,             /*Baseline measured from the bottom of the line*/
#if !(LVGL_VERSION_MAJOR == 6 && LVGL_VERSION_MINOR == 0)
    .subpx = LV_FONT_SUBPX_NONE,
#endif
#if LV_VERSION_CHECK(7, 4, 0) || LVGL_VERSION_MAJOR >= 8
    .underline_position = -1,
    .underline_thickness = 1,
#endif
    .dsc = &font_dsc           /*The custom font data. Will be accessed by `get_glyph_bitmap/dsc` */
};



#endif /*#if UI_FONT_RUSSOONE14*/

