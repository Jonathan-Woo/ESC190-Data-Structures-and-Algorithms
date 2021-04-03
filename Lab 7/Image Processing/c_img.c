#include "c_img.h"
#include <stdio.h>
#include <math.h>
#include <string.h>
#include <stdlib.h>

#define min(X,Y) ((X) < (Y) ? (X) : (Y))
#define max(X,Y) ((X) > (Y) ? (X) : (Y))

void create_img(struct rgb_img **im, size_t height, size_t width){
    *im = (struct rgb_img *)malloc(sizeof(struct rgb_img));
    (*im)->height = height;
    (*im)->width = width;
    (*im)->raster = (uint8_t *)malloc(3 * height * width);
}

int read_2bytes(FILE *fp){
    uint8_t bytes[2];
    fread(bytes, sizeof(uint8_t), 1, fp);
    fread(bytes+1, sizeof(uint8_t), 1, fp);
    return (  ((int)bytes[0]) << 8)  + (int)bytes[1];
}

void write_2bytes(FILE *fp, int num){
    uint8_t bytes[2];
    bytes[0] = (uint8_t)((num & 0XFFFF) >> 8);
    bytes[1] = (uint8_t)(num & 0XFF);
    fwrite(bytes, 1, 1, fp);
    fwrite(bytes+1, 1, 1, fp);
}

void read_in_img(struct rgb_img **im, char *filename){
    FILE *fp = fopen(filename, "rb");
    size_t height = read_2bytes(fp);
    size_t width = read_2bytes(fp);
    create_img(im, height, width);
    fread((*im)->raster, 1, 3*width*height, fp);
    fclose(fp);
}

void write_img(struct rgb_img *im, char *filename){
    FILE *fp = fopen(filename, "wb");
    write_2bytes(fp, im->height);
    write_2bytes(fp, im->width);
    fwrite(im->raster, 1, im->height * im->width * 3, fp);
    fclose(fp);
}

uint8_t get_pixel(struct rgb_img *im, int y, int x, int col){
    return im->raster[3 * (y*(im->width) + x) + col];
}

void set_pixel(struct rgb_img *im, int y, int x, int r, int g, int b){
    im->raster[3 * (y*(im->width) + x) + 0] = r;
    im->raster[3 * (y*(im->width) + x) + 1] = g;
    im->raster[3 * (y*(im->width) + x) + 2] = b;
}

void destroy_image(struct rgb_img *im)
{
    free(im->raster);
    free(im);
}


void print_grad(struct rgb_img *grad){
    int height = grad->height;
    int width = grad->width;
    for(int i = 0; i < height; i++){
        for(int j = 0; j < width; j++){
            printf("%d\t", get_pixel(grad, i, j, 0));
        }
    printf("\n");    
    }
}

int main(void){
    struct rgb_img *president;
    struct rgb_img *president_temp;

    char name[] = "president.bin";
    read_in_img(&president, name);
    read_in_img(&president_temp, name);
    int i;
    int e;
    int j;

    uint8_t r;
    uint8_t g;
    uint8_t b;

    char new_name [100];

    //loop 5 times for 5 photos
    for(j = 1; j < 2; j++){
        //Loop through height and width to modify values
        for(i = 0; i < president->height; i++){
            for(e = 0; e < president->width; e++){
                //assuming int col refers to 0 = r 1 = g 2 = b
                r = get_pixel(president, i, e, 0);
                g = get_pixel(president, i, e, 1);
                b = get_pixel(president, i, e, 2);
                set_pixel(president_temp, i, e, (uint8_t)min((1 + 0.2 * j) * r, 255), (uint8_t)min((1 + 0.2 * j) * g, 255), (uint8_t)min((1 + 0.2 * j) * b, 255));
            }
        }
        // strcat(new_name, itoa(j));
        // strcat(new_name, ".bin");
        write_img(president_temp, "sol.bin");
    }
    
    return 0;
}
