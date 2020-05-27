#include"video_driver.h"
#include"naiveConsole.h"
#include<stdint.h>

#define WHITE {255,255,255}
#define RED {0,0,255}
#define BLUE {255,0,0}
#define GREEN {0,255,0}

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

int WIDTH = 1024;
int HEIGHT = 768;
struct vbe_mode_info_structure * screen_info = 0x5C00;

char * getPixelDataByPosition(int x, int y){
    return screen_info->framebuffer + (x+y*WIDTH) * 3;
}
void writePixel(int x, int y, int colour[]){ //colour[3] = B - G - R
    char * pos = getPixelDataByPosition(x,y);
    //char * pos = screen_info -> framebuffer + (5*3); 
    for(int i=0; i<3;i++){
        pos[i] = colour[i];
    }   
}
void render(char *bitmap) { //tengo que hacer andar esto!
    int x,y;
    int set;
	int colour[] = WHITE;
    for (x=0; x < 8; x++) {
        for (y=0; y < 8; y++) {
            set = bitmap[x] & 1 << y; //set = 1 si tengo que poner un pixel
            //printf("%c", set ? 'X' : ' ');
			if(set){
				writePixel(x,y,colour);
			}
        }
        ncNewline();
    }
}


