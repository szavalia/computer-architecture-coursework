// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
#include "video_driver.h"
#include "keyboard.h"



extern int side, context;

struct vbe_mode_info_structure {
	uint16_t attributes;		// deprecated, only bit 7 should be of interest to you, and it indicates the mode supports a linear frame buffer.
	uint8_t window_a;			// deprecated
	uint8_t window_b;			// deprecated
	uint16_t granularity;		// deprecated; used while calculating bank numbers
	uint16_t window_size;
	uint16_t segment_a;
	uint16_t segment_b;
	uint32_t win_func_ptr;		// deprecated; used to switch banks from protected mode without returning to real mode
	uint16_t pitch;			// number of bytes per horizontal line
	uint16_t width;			// width in pixels
	uint16_t height;			// height in pixels
	uint8_t w_char;			// unused...
	uint8_t y_char;			// ...
	uint8_t planes;
	uint8_t bpp;			// bits per pixel in this mode
	uint8_t banks;			// deprecated; total number of banks in this mode
	uint8_t memory_model;
	uint8_t bank_size;		// deprecated; size of a bank, almost always 64 KB but may be 16 KB...
	uint8_t image_pages;
	uint8_t reserved0;

	uint8_t red_mask;
	uint8_t red_position;
	uint8_t green_mask;
	uint8_t green_position;
	uint8_t blue_mask;
	uint8_t blue_position;
	uint8_t reserved_mask;
	uint8_t reserved_position;
	uint8_t direct_color_attributes;

	uint32_t framebuffer;		// physical address of the linear frame buffer; write here to draw to the screen
	uint32_t off_screen_mem_off;
	uint16_t off_screen_mem_size;	// size of memory in the framebuffer but not being displayed on the screen
	uint8_t reserved1[206];
} __attribute__ ((packed));

char font8x8_basic[128][8] = {
    { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00},   // U+0000 (nul)
    { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00},   // U+0001
    { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00},   // U+0002
    { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00},   // U+0003
    { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00},   // U+0004
    { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00},   // U+0005
    { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00},   // U+0006
    { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00},   // U+0007
    { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00},   // U+0008
    { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00},   // U+0009
    { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00},   // U+000A
    { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00},   // U+000B
    { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00},   // U+000C
    { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00},   // U+000D
    { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00},   // U+000E
    { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00},   // U+000F
    { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00},   // U+0010
    { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00},   // U+0011
    { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00},   // U+0012
    { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00},   // U+0013
    { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00},   // U+0014
    { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00},   // U+0015
    { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00},   // U+0016
    { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00},   // U+0017
    { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00},   // U+0018
    { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00},   // U+0019
    { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00},   // U+001A
    { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00},   // U+001B
    { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00},   // U+001C
    { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00},   // U+001D
    { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00},   // U+001E
    { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00},   // U+001F
    { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00},   // U+0020 (space)
    { 0x18, 0x3C, 0x3C, 0x18, 0x18, 0x00, 0x18, 0x00},   // U+0021 (!)
    { 0x36, 0x36, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00},   // U+0022 (")
    { 0x36, 0x36, 0x7F, 0x36, 0x7F, 0x36, 0x36, 0x00},   // U+0023 (#)
    { 0x0C, 0x3E, 0x03, 0x1E, 0x30, 0x1F, 0x0C, 0x00},   // U+0024 ($)
    { 0x00, 0x63, 0x33, 0x18, 0x0C, 0x66, 0x63, 0x00},   // U+0025 (%)
    { 0x1C, 0x36, 0x1C, 0x6E, 0x3B, 0x33, 0x6E, 0x00},   // U+0026 (&)
    { 0x06, 0x06, 0x03, 0x00, 0x00, 0x00, 0x00, 0x00},   // U+0027 (')
    { 0x18, 0x0C, 0x06, 0x06, 0x06, 0x0C, 0x18, 0x00},   // U+0028 (()
    { 0x06, 0x0C, 0x18, 0x18, 0x18, 0x0C, 0x06, 0x00},   // U+0029 ())
    { 0x00, 0x66, 0x3C, 0xFF, 0x3C, 0x66, 0x00, 0x00},   // U+002A (*)
    { 0x00, 0x0C, 0x0C, 0x3F, 0x0C, 0x0C, 0x00, 0x00},   // U+002B (+)
    { 0x00, 0x00, 0x00, 0x00, 0x00, 0x0C, 0x0C, 0x06},   // U+002C (,)
    { 0x00, 0x00, 0x00, 0x3F, 0x00, 0x00, 0x00, 0x00},   // U+002D (-)
    { 0x00, 0x00, 0x00, 0x00, 0x00, 0x0C, 0x0C, 0x00},   // U+002E (.)
    { 0x60, 0x30, 0x18, 0x0C, 0x06, 0x03, 0x01, 0x00},   // U+002F (/)
    { 0x3E, 0x63, 0x73, 0x7B, 0x6F, 0x67, 0x3E, 0x00},   // U+0030 (0)
    { 0x0C, 0x0E, 0x0C, 0x0C, 0x0C, 0x0C, 0x3F, 0x00},   // U+0031 (1)
    { 0x1E, 0x33, 0x30, 0x1C, 0x06, 0x33, 0x3F, 0x00},   // U+0032 (2)
    { 0x1E, 0x33, 0x30, 0x1C, 0x30, 0x33, 0x1E, 0x00},   // U+0033 (3)
    { 0x38, 0x3C, 0x36, 0x33, 0x7F, 0x30, 0x78, 0x00},   // U+0034 (4)
    { 0x3F, 0x03, 0x1F, 0x30, 0x30, 0x33, 0x1E, 0x00},   // U+0035 (5)
    { 0x1C, 0x06, 0x03, 0x1F, 0x33, 0x33, 0x1E, 0x00},   // U+0036 (6)
    { 0x3F, 0x33, 0x30, 0x18, 0x0C, 0x0C, 0x0C, 0x00},   // U+0037 (7)
    { 0x1E, 0x33, 0x33, 0x1E, 0x33, 0x33, 0x1E, 0x00},   // U+0038 (8)
    { 0x1E, 0x33, 0x33, 0x3E, 0x30, 0x18, 0x0E, 0x00},   // U+0039 (9)
    { 0x00, 0x0C, 0x0C, 0x00, 0x00, 0x0C, 0x0C, 0x00},   // U+003A (:)
    { 0x00, 0x0C, 0x0C, 0x00, 0x00, 0x0C, 0x0C, 0x06},   // U+003B (;)
    { 0x18, 0x0C, 0x06, 0x03, 0x06, 0x0C, 0x18, 0x00},   // U+003C (<)
    { 0x00, 0x00, 0x3F, 0x00, 0x00, 0x3F, 0x00, 0x00},   // U+003D (=)
    { 0x06, 0x0C, 0x18, 0x30, 0x18, 0x0C, 0x06, 0x00},   // U+003E (>)
    { 0x1E, 0x33, 0x30, 0x18, 0x0C, 0x00, 0x0C, 0x00},   // U+003F (?)
    { 0x3E, 0x63, 0x7B, 0x7B, 0x7B, 0x03, 0x1E, 0x00},   // U+0040 (@)
    { 0x0C, 0x1E, 0x33, 0x33, 0x3F, 0x33, 0x33, 0x00},   // U+0041 (A)
    { 0x3F, 0x66, 0x66, 0x3E, 0x66, 0x66, 0x3F, 0x00},   // U+0042 (B)
    { 0x3C, 0x66, 0x03, 0x03, 0x03, 0x66, 0x3C, 0x00},   // U+0043 (C)
    { 0x1F, 0x36, 0x66, 0x66, 0x66, 0x36, 0x1F, 0x00},   // U+0044 (D)
    { 0x7F, 0x46, 0x16, 0x1E, 0x16, 0x46, 0x7F, 0x00},   // U+0045 (E)
    { 0x7F, 0x46, 0x16, 0x1E, 0x16, 0x06, 0x0F, 0x00},   // U+0046 (F)
    { 0x3C, 0x66, 0x03, 0x03, 0x73, 0x66, 0x7C, 0x00},   // U+0047 (G)
    { 0x33, 0x33, 0x33, 0x3F, 0x33, 0x33, 0x33, 0x00},   // U+0048 (H)
    { 0x1E, 0x0C, 0x0C, 0x0C, 0x0C, 0x0C, 0x1E, 0x00},   // U+0049 (I)
    { 0x78, 0x30, 0x30, 0x30, 0x33, 0x33, 0x1E, 0x00},   // U+004A (J)
    { 0x67, 0x66, 0x36, 0x1E, 0x36, 0x66, 0x67, 0x00},   // U+004B (K)
    { 0x0F, 0x06, 0x06, 0x06, 0x46, 0x66, 0x7F, 0x00},   // U+004C (L)
    { 0x63, 0x77, 0x7F, 0x7F, 0x6B, 0x63, 0x63, 0x00},   // U+004D (M)
    { 0x63, 0x67, 0x6F, 0x7B, 0x73, 0x63, 0x63, 0x00},   // U+004E (N)
    { 0x1C, 0x36, 0x63, 0x63, 0x63, 0x36, 0x1C, 0x00},   // U+004F (O)
    { 0x3F, 0x66, 0x66, 0x3E, 0x06, 0x06, 0x0F, 0x00},   // U+0050 (P)
    { 0x1E, 0x33, 0x33, 0x33, 0x3B, 0x1E, 0x38, 0x00},   // U+0051 (Q)
    { 0x3F, 0x66, 0x66, 0x3E, 0x36, 0x66, 0x67, 0x00},   // U+0052 (R)
    { 0x1E, 0x33, 0x07, 0x0E, 0x38, 0x33, 0x1E, 0x00},   // U+0053 (S)
    { 0x3F, 0x2D, 0x0C, 0x0C, 0x0C, 0x0C, 0x1E, 0x00},   // U+0054 (T)
    { 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x3F, 0x00},   // U+0055 (U)
    { 0x33, 0x33, 0x33, 0x33, 0x33, 0x1E, 0x0C, 0x00},   // U+0056 (V)
    { 0x63, 0x63, 0x63, 0x6B, 0x7F, 0x77, 0x63, 0x00},   // U+0057 (W)
    { 0x63, 0x63, 0x36, 0x1C, 0x1C, 0x36, 0x63, 0x00},   // U+0058 (X)
    { 0x33, 0x33, 0x33, 0x1E, 0x0C, 0x0C, 0x1E, 0x00},   // U+0059 (Y)
    { 0x7F, 0x63, 0x31, 0x18, 0x4C, 0x66, 0x7F, 0x00},   // U+005A (Z)
    { 0x1E, 0x06, 0x06, 0x06, 0x06, 0x06, 0x1E, 0x00},   // U+005B ([)
    { 0x03, 0x06, 0x0C, 0x18, 0x30, 0x60, 0x40, 0x00},   // U+005C (\)
    { 0x1E, 0x18, 0x18, 0x18, 0x18, 0x18, 0x1E, 0x00},   // U+005D (])
    { 0x08, 0x1C, 0x36, 0x63, 0x00, 0x00, 0x00, 0x00},   // U+005E (^)
    { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xFF},   // U+005F (_)
    { 0x0C, 0x0C, 0x18, 0x00, 0x00, 0x00, 0x00, 0x00},   // U+0060 (`)
    { 0x00, 0x00, 0x1E, 0x30, 0x3E, 0x33, 0x6E, 0x00},   // U+0061 (a)
    { 0x07, 0x06, 0x06, 0x3E, 0x66, 0x66, 0x3B, 0x00},   // U+0062 (b)
    { 0x00, 0x00, 0x1E, 0x33, 0x03, 0x33, 0x1E, 0x00},   // U+0063 (c)
    { 0x38, 0x30, 0x30, 0x3e, 0x33, 0x33, 0x6E, 0x00},   // U+0064 (d)
    { 0x00, 0x00, 0x1E, 0x33, 0x3f, 0x03, 0x1E, 0x00},   // U+0065 (e)
    { 0x1C, 0x36, 0x06, 0x0f, 0x06, 0x06, 0x0F, 0x00},   // U+0066 (f)
    { 0x00, 0x00, 0x6E, 0x33, 0x33, 0x3E, 0x30, 0x1F},   // U+0067 (g)
    { 0x07, 0x06, 0x36, 0x6E, 0x66, 0x66, 0x67, 0x00},   // U+0068 (h)
    { 0x0C, 0x00, 0x0E, 0x0C, 0x0C, 0x0C, 0x1E, 0x00},   // U+0069 (i)
    { 0x30, 0x00, 0x30, 0x30, 0x30, 0x33, 0x33, 0x1E},   // U+006A (j)
    { 0x07, 0x06, 0x66, 0x36, 0x1E, 0x36, 0x67, 0x00},   // U+006B (k)
    { 0x0E, 0x0C, 0x0C, 0x0C, 0x0C, 0x0C, 0x1E, 0x00},   // U+006C (l)
    { 0x00, 0x00, 0x33, 0x7F, 0x7F, 0x6B, 0x63, 0x00},   // U+006D (m)
    { 0x00, 0x00, 0x1F, 0x33, 0x33, 0x33, 0x33, 0x00},   // U+006E (n)
    { 0x00, 0x00, 0x1E, 0x33, 0x33, 0x33, 0x1E, 0x00},   // U+006F (o)
    { 0x00, 0x00, 0x3B, 0x66, 0x66, 0x3E, 0x06, 0x0F},   // U+0070 (p)
    { 0x00, 0x00, 0x6E, 0x33, 0x33, 0x3E, 0x30, 0x78},   // U+0071 (q)
    { 0x00, 0x00, 0x3B, 0x6E, 0x66, 0x06, 0x0F, 0x00},   // U+0072 (r)
    { 0x00, 0x00, 0x3E, 0x03, 0x1E, 0x30, 0x1F, 0x00},   // U+0073 (s)
    { 0x08, 0x0C, 0x3E, 0x0C, 0x0C, 0x2C, 0x18, 0x00},   // U+0074 (t)
    { 0x00, 0x00, 0x33, 0x33, 0x33, 0x33, 0x6E, 0x00},   // U+0075 (u)
    { 0x00, 0x00, 0x33, 0x33, 0x33, 0x1E, 0x0C, 0x00},   // U+0076 (v)
    { 0x00, 0x00, 0x63, 0x6B, 0x7F, 0x7F, 0x36, 0x00},   // U+0077 (w)
    { 0x00, 0x00, 0x63, 0x36, 0x1C, 0x36, 0x63, 0x00},   // U+0078 (x)
    { 0x00, 0x00, 0x33, 0x33, 0x33, 0x3E, 0x30, 0x1F},   // U+0079 (y)
    { 0x00, 0x00, 0x3F, 0x19, 0x0C, 0x26, 0x3F, 0x00},   // U+007A (z)
    { 0x38, 0x0C, 0x0C, 0x07, 0x0C, 0x0C, 0x38, 0x00},   // U+007B ({)
    { 0x18, 0x18, 0x18, 0x00, 0x18, 0x18, 0x18, 0x00},   // U+007C (|)
    { 0x07, 0x0C, 0x0C, 0x38, 0x0C, 0x0C, 0x07, 0x00},   // U+007D (})
    { 0x6E, 0x3B, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00},   // U+007E (~)
    { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}    // U+007F
};

#define WHITE {255,255,255}
#define RED {0,0,255}
#define BLUE {255,0,0}
#define GREEN {0,255,0}
#define BLACK {0,0,0} 
#define CHAR_SIZE 8
#define SCREEN_START 0xFD000000
#define SCREEN_POSITION (screen_info->framebuffer - SCREEN_START)
#define LINE_SPACING (2 * CHAR_SIZE)

static int black[]=BLACK, blue[]=BLUE, white[] = WHITE;

int WIDTH = 1024;
int HALF = 504;
int HEIGHT = 768;
int left_line = 512 -3;
int right_line =  512 +3;
struct vbe_mode_info_structure * screen_info = 0x5C00;
static char buffer[65];
static char cero[8];

extern int side;

uint32_t fb1 = 0xFD000000;
uint32_t fb2 = 0xFD000203;


void change_screen_buffer(int mySide){
    if(mySide == 0){ // voy a guardar mi current en fb1 y pongo mi current como la de fb2
        fb1 = screen_info->framebuffer;
        screen_info->framebuffer = fb2;
    }
    else if(mySide == 1){
        fb2 = screen_info->framebuffer;
        screen_info->framebuffer = fb1;
    }
}

long getFrameBuffer(){
    return screen_info -> framebuffer;
}

int getContext(){
	return side;
}

char * getPixelDataByPosition(int x, int y){
    return (char *) screen_info->framebuffer + (x+y*WIDTH) * 3;
}
void writePixel(int y, int x, int colour[]){ //colour[3] = B - G - R
    char * pos = getPixelDataByPosition(y,x); //TODO: invertí el nombre de las variables, chequear que se vaya el warning
    //char * pos = screen_info -> framebuffer + (5*3);
    for(int i=0; i<3;i++){
        pos[i] = colour[i];
    }   
}

void copyPixelBelow(){
    for ( int i = 0 ; i < 3 ; i++){
        ((char *) screen_info->framebuffer)[i] = ((char *) screen_info->framebuffer + WIDTH*3*(LINE_SPACING))[i];
    }
}

void writePixelWhite(int x, int y){ //colour[3] = B - G - R
    char * pos = getPixelDataByPosition(x,y);
    //char * pos = screen_info -> framebuffer + (5*3); 
    for(int i=0; i<3;i++){
        pos[i] = white[i];
    }   
}

void writePixelBlack(int x, int y){ //colour[3] = B - G - R
    char * pos = getPixelDataByPosition(x,y);
    //char * pos = screen_info -> framebuffer + (5*3); 
    for(int i=0; i<3;i++){
        pos[i] = black[i];
    }   
}

void writePixelBlue(int x, int y){ //colour[3] = B - G - R
    char * pos = getPixelDataByPosition(x,y);
    //char * pos = screen_info -> framebuffer + (5*3); 
    for(int i=0; i<3;i++){
        pos[i] = blue[i];
    }   
}

void render(char *bitmap) { 
    int x,y;
    int set;
    int white[] = WHITE;
    for (x=0; x < CHAR_SIZE; x++) {
        for (y=0; y < CHAR_SIZE; y++) {
            set = bitmap[x] & 1 << y; //set = 1 si tengo que poner un pixel
			if(set){
				writePixel(y,x,white); //si es x, y se imprime acostada (?)
			}
        }
    }
}



void printChar(char c){
    if( side == 1 && ((SCREEN_POSITION %(WIDTH*3) < right_line*3) || SCREEN_POSITION%(WIDTH*3) >= (WIDTH-CHAR_SIZE)*3) && c != '\n' && c != '\b')
    {
        newlineR();
    }  
    if(SCREEN_POSITION == 0 && side ==1){
        screen_info->framebuffer += right_line *3;
    }
    if(c=='\n'){ //llegué al final de la linea
        if(side == 0)
            newline();
        else{
            newlineR();
        }
    }
    else if(c == '\b'){
        backspace();
    }
    else if(c=='\t'){
        for(int i=0; i<5;i++){
            printChar(' ');
        }
    }
    else {
        render((char *) font8x8_basic[c]);
        screen_info->framebuffer += CHAR_SIZE * 3;
    } 
    if( side == 0 && (SCREEN_POSITION %(WIDTH*3) >= HALF*3) && c != '\n' && c != '\b')
    {
        newline();
    }


}
 

    
void scroll(){
    screen_info -> framebuffer = SCREEN_START;
    while(SCREEN_POSITION < (WIDTH*(HEIGHT-LINE_SPACING)*3)){ //recorro hasta la anteúltima línea
        copyPixelBelow();
        screen_info->framebuffer += 3;
        if((SCREEN_POSITION%(WIDTH*3) >= left_line*3) && (side == 0)){
            toStartOfLine();
            screen_info->framebuffer+=WIDTH*3;
        }
        if((SCREEN_POSITION%(WIDTH*3) < right_line*3) && side == 1){
            toStartOfLine();
            screen_info->framebuffer += right_line * 3;
            //screen_info->framebuffer+=WIDTH*3;
        }

    } 
    if(side == 0){ 
        do{
            blackRender(); //paint it black
            screen_info -> framebuffer += CHAR_SIZE*3;
        }
        while(SCREEN_POSITION %(WIDTH*3) < HALF*3 ); //mientras no llegues al final de la (última) línea
        toStartOfLine();
    }
    else if( side == 1){
        do{
            blackRender();
            screen_info->framebuffer += CHAR_SIZE*3;
        }
        while(SCREEN_POSITION%(WIDTH*3)>=right_line*3);
        toStartOfLine();
        screen_info->framebuffer += right_line*3;
    }
        
 }


void printS(const char * string){
    int i;
    for(i = 0; string[i]!= 0; i++){
        printChar(string[i]);
    }
}

void print(const char * string, int size){
    int i;
    
    for(i = 0; i < size && string[i] != 0; i++){
        printChar(string[i]);
    }
}

void backspace(){ 
    if(SCREEN_POSITION >= (CHAR_SIZE*3)){ //hay algo en pantalla
        if ( SCREEN_POSITION %  (WIDTH * 3 ) == 0 ){ //si estoy al principio de una linea //NO va con * char_size por que ahi solo estaris buscando las lineas multiplos de 8!
            screen_info->framebuffer -= ( WIDTH*LINE_SPACING*3); //borro un newline 
        }
        screen_info->framebuffer -= CHAR_SIZE * 3;
        blackRender();
    } 
}

void splitScreen(){ //va bien hasta que haces scroll
    for(int x = 0; x < WIDTH*3; x++){
        for(int y = 0; y < HEIGHT; y++){
            if( y > left_line && y < right_line){
                writePixelBlue(y,x);
            }
        }
    }
}

void blackRender(){
    for (int x=0; x < CHAR_SIZE + LINE_SPACING; x++) { //si imprimo un espacio no setea en negro lo que habia abajo, lo "pisa"
        for (int y=0; y < CHAR_SIZE; y++) {
			writePixelBlack(y,x); 
		}
    }
}

void whiteRender(){
    for (int x=0; x < CHAR_SIZE + LINE_SPACING; x++) { //si imprimo un espacio no setea en negro lo que habia abajo, lo "pisa"
        for (int y=0; y < CHAR_SIZE; y++) {
            writePixelWhite(y,x);
		}
    }
}

void blueRender(){
        for (int x=0; x < CHAR_SIZE + LINE_SPACING; x++) { //si imprimo un espacio no setea en negro lo que habia abajo, lo "pisa"
        for (int y=0; y < CHAR_SIZE; y++) {
			writePixelBlue(y,x); 
		}
    }
}

void blueScreen(){
    for(int x = 0; x < WIDTH/3-42; x++){
        for(int y = 0; y < HEIGHT*3; y++){ 
            writePixelBlue(y,x);
        }
    }
}



void clear(){
    screen_info -> framebuffer = SCREEN_START;
    while(SCREEN_POSITION < HEIGHT * WIDTH * 3){
        if(side == 0 && SCREEN_POSITION%(WIDTH*3) >= (left_line*3 - 3*CHAR_SIZE)){
            toStartOfLine();
            screen_info->framebuffer+=WIDTH*3;
        }
        else if((SCREEN_POSITION%(WIDTH*3) < right_line*3 || SCREEN_POSITION%(WIDTH*3)>= (WIDTH-CHAR_SIZE)*3) && side == 1){
            toStartOfLine();
            screen_info->framebuffer += right_line * 3;
            screen_info->framebuffer+=WIDTH*3;
        }
        for (int x=0; x < CHAR_SIZE; x++) { //si imprimo un espacio no setea en negro lo que habia abajo, lo "pisa"
            for (int y=0; y < CHAR_SIZE; y++) {
				writePixelBlack(y,x); 
			}
        }
        screen_info->framebuffer += CHAR_SIZE*3;

    }
    screen_info -> framebuffer = SCREEN_START;
}

void newline(){
    toStartOfLine();
    screen_info->framebuffer += WIDTH * LINE_SPACING * 3;
    if(SCREEN_POSITION >= (WIDTH*3)*HEIGHT){ //llegué al final de la pantalla
        scroll();    
    }
}

void newlineR(){
    toStartOfLine();
    screen_info->framebuffer += WIDTH * LINE_SPACING * 3;
    screen_info-> framebuffer += right_line * 3;
    if(SCREEN_POSITION >= (WIDTH*3)*HEIGHT){ //llegué al final de la pantalla
        scroll();    
    }
}

void toStartOfLine(){
	screen_info -> framebuffer -= SCREEN_POSITION % (WIDTH*3);
}




void printBase(uint64_t value, uint32_t base)
{
    uintToBase(value, buffer, base);
    printS(buffer);
}

void printDec(uint64_t value){
    printBase(value, 10);
}

void printHex(uint64_t value){
    printBase(value, 16);
}

void printBin(uint64_t value){
    printBase(value, 2);
}
//print adaptado para imprimir registros y siempre mostrar 8 digitos HEXA
void printReg(uint64_t value){
    int digits;
    digits = uintToBase(value,buffer,16);
    print(cero,8-digits);
    printS(buffer);
}

uint32_t uintToBase(uint64_t value, char * buffer, uint32_t base)
{
	char *p = buffer;
	char *p1, *p2;
	uint32_t digits = 0;

	//Calculate characters for each digit
	do
	{
		uint32_t remainder = value % base;
		*p++ = (remainder < 10) ? remainder + '0' : remainder + 'A' - 10;
		digits++;
	}
	while (value /= base);

	// Terminate string in buffer.
	*p = 0;

	//Reverse string in buffer.
	p1 = buffer;
	p2 = p - 1;
	while (p1 < p2)
	{
		char tmp = *p1;
		*p1 = *p2;
		*p2 = tmp;
		p1++;
		p2--;
	}

	return digits;
}


void printRegs(){ 
	uint64_t * regs = getRegs();
    char * regNames[] = {"RAX","RBX","RCX","RDX","RSI","RDI","RBP","RSP","R8","R9","R10","R11","R12","R13","R14","R15"};
	for(int i=0; i<16;i++){
        printS(regNames[i]);
		printChar(':');
		printReg(regs[i]);	
		printChar('\n');
	}
}

void changeContext(){
    if(side != context){
    side = !side;
    change_screen_buffer(side);
    }
}