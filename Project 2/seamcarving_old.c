#include "seamcarving.h"
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
//#include "c_img.c"

void calc_energy(struct rgb_img *im, struct rgb_img **grad) {
    //Initialize the dual gradient energy array
    *grad = (struct rgb_img *) malloc(sizeof(struct rgb_img));
    (*grad)->height = im->height / 3;
    (*grad)->width = im->width / 3;
    (*grad)->raster = (u_int8_t *) malloc((*grad)->height * (*grad)->width);

    //Loop through each row and then column to calculate
    //dual gradient energy
    int x, y;
    int dr, dg, db;
    double sum = 0;

    //Works on all pixels except edge pixels
    for (y = 1; y < (*grad)->height - 1; y++) {
        for (x = 1; x < (*grad)->width - 1; x++) {
            //find delta-r, delta-g, delta-b between (y + 1, x) and (y - 1, x)
            dr = im->raster[im->width * (y + 1) + (x * 3)] - im->raster[im->width * (y - 1) + (x * 3)];
            dg = im->raster[im->width * (y + 1) + (x * 3) + 1] - im->raster[im->width * (y - 1) + (x * 3) + 1];
            db = im->raster[im->width * (y + 1) + (x * 3) + 2] - im->raster[im->width * (y - 1) + (x * 3) + 2];

            sum += pow(dr, 2) + pow(dg, 2) + pow(db, 2);

            //find delta-r, delta-g, delta-b between (y, x + 1) and (y - 1, x - 1)
            dr = im->raster[im->width * y + (x * 3) + 3] - im->raster[im->width * (y - 1) + (x * 3) - 3];
            dg = im->raster[im->width * y + (x * 3) + 4] - im->raster[im->width * (y - 1) + (x * 3) - 2];
            db = im->raster[im->width * y + (x * 3) + 5] - im->raster[im->width * (y - 1) + (x * 3) - 1];

            sum += sqrt(pow(dr, 2) + pow(dg, 2) + pow(db, 2)) / 10;
            (*grad)->raster[(*grad)->width * y + x] = (uint8_t) sum;
            sum = 0;
        }
    }

    //Now consider edge pixels
    //Top edge (y = 0, x iterates) excluding corners
    for (x = 1; x < (*grad)->width - 1; x++) {
        //find delta-r, delta-g, delta-b between (y + 1, x) and (y - 1, x)
        dr = im->raster[im->width + (x * 3)] - im->raster[im->width * (im->height - 1) + (x * 3)];
        dg = im->raster[im->width + (x * 3) + 1] - im->raster[im->width * (im->height - 1) + (x * 3) + 1];
        db = im->raster[im->width + (x * 3) + 2] - im->raster[im->width * (im->height - 1) + (x * 3) + 2];

        sum += pow(dr, 2) + pow(dg, 2) + pow(db, 2);

        //find delta-r, delta-g, delta-b between (y, x + 1) and (y, x + 1)
        dr = im->raster[(x * 3) + 3] - im->raster[(x * 3) - 3];
        dg = im->raster[(x * 3) + 4] - im->raster[(x * 3) - 2];
        db = im->raster[(x * 3) + 5] - im->raster[(x * 3) - 1];

        sum += sqrt(pow(dr, 2) + pow(dg, 2) + pow(db, 2)) / 10;
        (*grad)->raster[x] = (uint8_t) sum;
        sum = 0;
    }

    //Bottom edge (y = (*grad)->height - 1, x iterates) excluding corners
    for (x = 1; x < (*grad)->width - 1; x++) {
        //find delta-r, delta-g, delta-b between (y + 1, x) and (y - 1, x)
        dr = im->raster[x * 3] - im->raster[im->width * (im->height - 2) + (x * 3)];
        dg = im->raster[(x * 3) + 1] - im->raster[im->width * (im->height - 2) + (x * 3) + 1];
        db = im->raster[(x * 3) + 2] - im->raster[im->width * (im->height - 2) + (x * 3) + 2];

        sum += pow(dr, 2) + pow(dg, 2) + pow(db, 2);

        //find delta-r, delta-g, delta-b between (y, x + 1) and (y, x + 1)
        dr = im->raster[im->width * (im->height - 1) + (x * 3) + 3] -
             im->raster[im->width * (im->height - 1) + (x * 3) - 3];
        dg = im->raster[im->width * (im->height - 1) + (x * 3) + 4] -
             im->raster[im->width * (im->height - 1) + (x * 3) - 2];
        db = im->raster[im->width * (im->height - 1) + (x * 3) + 5] -
             im->raster[im->width * (im->height - 1) + (x * 3) - 1];

        sum += sqrt(pow(dr, 2) + pow(dg, 2) + pow(db, 2)) / 10;
        (*grad)->raster[((*grad)->height - 1) * (*grad)->width + x] = (uint8_t) sum;
        sum = 0;
    }

    //Left edge (y iterates, x = 0) excluding corners
    for (y = 1; y < (*grad)->height - 1; y++) {
        //find delta-r, delta-g, delta-b between (y + 1, x) and (y - 1, x)
        dr = im->raster[(im->width) * (y + 1)] - im->raster[(im->width) * (y - 1)];
        dg = im->raster[(im->width) * (y + 1) + 1] - im->raster[(im->width) * (y - 1) + 1];
        db = im->raster[(im->width) * (y + 1) + 2] - im->raster[(im->width) * (y - 1) + 2];

        sum += pow(dr, 2) + pow(dg, 2) + pow(db, 2);

        //find delta-r, delta-g, delta-b between (y, x + 1) and (y, x + 1)
        dr = im->raster[im->width * y + 3] - im->raster[im->width * (y + 1) - 3];
        dg = im->raster[im->width * y + 4] - im->raster[im->width * (y + 1) - 2];
        db = im->raster[im->width * y + 5] = im->raster[im->width * (y + 1) - 1];

        sum += sqrt(pow(dr, 2) + pow(dg, 2) + pow(db, 2)) / 10;
        (*grad)->raster[(*grad)->width * y] = (uint8_t) sum;
        sum = 0;
    }

    //Right edge (y iterates, x = (*grad)->width - 1) excluding corners
    for (y = 1; y < (*grad)->height - 1; y++) {
        //find delta-r, delta-g, delta-b between (y + 1, x) and (y - 1, x)
        dr = im->raster[im->width * (y + 2) - 3] - im->raster[im->width * y - 3];
        dg = im->raster[im->width * (y + 2) - 2] - im->raster[im->width * y - 2];
        db = im->raster[im->width * (y + 2) - 1] - im->raster[im->width * y - 1];

        sum += pow(dr, 2) + pow(dg, 2) + pow(db, 2);

        //find delta-r, delta-g, delta-b between (y, x + 1) and (y, x + 1)
        dr = im->raster[im->width * y] - im->raster[im->width * (y + 1) - 6];
        dg = im->raster[im->width * y + 1] - im->raster[im->width * (y + 1) - 5];
        db = im->raster[im->width * y + 2] - im->raster[im->width * (y + 1) - 4];

        sum += sqrt(pow(dr, 2) + pow(dg, 2) + pow(db, 2)) / 10;
        (*grad)->raster[(*grad)->width * (y + 1) - 1] = (uint8_t) sum;
        sum = 0;
    }

    //Consider 4 corners
    //top left
    //find delta-r, delta-g, delta-b between (y + 1, x) and (y - 1, x)
    dr = im->raster[im->width] - im->raster[im->width * (im->height - 1)];
    dg = im->raster[im->width + 1] - im->raster[im->width * (im->height - 1) + 1];
    db = im->raster[im->width + 2] - im->raster[im->width * (im->height - 1) + 2];

    sum += pow(dr, 2) + pow(dg, 2) + pow(db, 2);

    //find delta-r, delta-g, delta-b between (y, x + 1) and (y, x + 1)
    dr = im->raster[4] - im->raster[im->width - 3];
    dg = im->raster[5] - im->raster[im->width - 2];
    db = im->raster[6] - im->raster[im->width - 1];

    sum += sqrt(pow(dr, 2) + pow(dg, 2) + pow(db, 2)) / 10;
    (*grad)->raster[0] = (uint8_t) sum;
    sum = 0;

    //top right
    //find delta-r, delta-g, delta-b between (y + 1, x) and (y - 1, x)
    dr = im->raster[im->width * 2 - 3] - im->raster[im->width * im->height - 3];
    dg = im->raster[im->width * 2 - 2] - im->raster[im->width * im->height - 2];
    db = im->raster[im->width * 2 - 1] - im->raster[im->width * im->height - 1];

    sum += pow(dr, 2) + pow(dg, 2) + pow(db, 2);

    //find delta-r, delta-g, delta-b between (y, x + 1) and (y, x + 1)
    dr = im->raster[0] - im->raster[im->width - 6];
    dg = im->raster[1] - im->raster[im->width - 5];
    db = im->raster[2] - im->raster[im->width - 4];

    sum += sqrt(pow(dr, 2) + pow(dg, 2) + pow(db, 2)) / 10;
    (*grad)->raster[(*grad)->width - 1] = (uint8_t) sum;
    sum = 0;

    //bottom left
    //find delta-r, delta-g, delta-b between (y + 1, x) and (y - 1, x)
    dr = im->raster[0] - im->raster[im->width * (im->height - 2)];
    dg = im->raster[1] - im->raster[im->width * (im->height - 2) + 1];
    db = im->raster[2] - im->raster[im->width * (im->height - 2) + 2];

    sum += pow(dr, 2) + pow(dg, 2) + pow(db, 2);

    //find delta-r, delta-g, delta-b between (y, x + 1) and (y, x + 1)
    dr = im->raster[im->width * (im->height - 1) + 3] - im->raster[im->width * im->height - 3];
    dg = im->raster[im->width * (im->height - 1) + 4] - im->raster[im->width * im->height - 2];
    db = im->raster[im->width * (im->height - 1) + 5] - im->raster[im->width * im->height - 1];

    sum += sqrt(pow(dr, 2) + pow(dg, 2) + pow(db, 2)) / 10;
    (*grad)->raster[(*grad)->width * ((*grad)->height - 1)] = (uint8_t) sum;
    sum = 0;

    //bottom right
    //find delta-r, delta-g, delta-b between (y + 1, x) and (y - 1, x)
    dr = im->raster[im->width - 3] - im->raster[im->width * (im->height - 1) - 3];
    dg = im->raster[im->width - 2] - im->raster[im->width * (im->height - 1) - 2];
    db = im->raster[im->width - 1] - im->raster[im->width * (im->height - 1) - 1];

    sum += pow(dr, 2) + pow(dg, 2) + pow(db, 2);

    //find delta-r, delta-g, delta-b between (y, x + 1) and (y, x + 1)
    dr = im->raster[im->width * (im->height - 1)] - im->raster[im->width * (im->height) - 6];
    dg = im->raster[im->width * (im->height - 1) + 1] - im->raster[im->width * (im->height) - 5];
    db = im->raster[im->width * (im->height - 1) + 2] - im->raster[im->width * (im->height) - 4];

    sum += sqrt(pow(dr, 2) + pow(dg, 2) + pow(db, 2)) / 10;
    (*grad)->raster[(*grad)->width * (*grad)->height - 1] = (uint8_t) sum;
    sum = 0;
}

int main(void){
    struct rgb_img *img;
    char name[] = "3x4.bin";
    read_in_img(&img, name);
    
   struct rgb_img *grad;
   calc_energy(img,  &grad);
   print_grad(grad);

    return 0;
}
