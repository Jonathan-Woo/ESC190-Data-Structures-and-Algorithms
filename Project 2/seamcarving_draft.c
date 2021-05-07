#include "seamcarving.h"
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

void calc_energy(struct rgb_img *im, struct rgb_img **grad) {
    /*
     * Calculates the dual gradient energy at every position
     */
    //Initialize the dual gradient energy array
    *grad = (struct rgb_img *) malloc(sizeof(struct rgb_img));
    (*grad)->height = im->height;
    (*grad)->width = im->width;
    (*grad)->raster = (u_int8_t *) malloc((*grad)->height * (*grad)->width * 3);

    //go through each column and each row and calculate dual gradient energy
    int x, y;
    int x_next, x_pre, y_next, y_pre;
    int col;
    double sum = 0;

    for(y = 0; y < (*grad)->height; y++){
        for(x = 0; x < (*grad)->width; x++){
            x_next = x + 1;
            x_pre = x - 1;
            y_next = y + 1;
            y_pre = y - 1;

            //modify x, y if at edges
            if(x_next > (int)(*grad)->width - 1){
                x_next = 0;
            }
            if(x_pre < 0){
                x_pre = (int)(*grad)->width - 1;
            }
            if(y_next > (int)(*grad)->height - 1){
                y_next = 0;
            }
            if(y_pre < 0){
                y_pre = (int)(*grad)->height - 1;
            }

            //loop through each colour (RGB) for each position
            //For (y + 1, x) - (y - 1, x)
            for(col = 0; col < 3; col++){
                sum += pow(get_pixel(im, y_next, x, col) - get_pixel(im, y_pre, x, col), 2);
            }
            //For (y, x + 1) - (y, x - 1)
            for(col = 0; col < 3; col++){
                sum += pow(get_pixel(im, y, x_next, col) - get_pixel(im, y, x_pre, col), 2);
            }
            sum = sqrt(sum);

            //write to the new raster and setting RGB values to the same 
            set_pixel(*grad, y, x, (uint8_t)(sum/10), (uint8_t)(sum/10), (uint8_t)(sum/10));
            sum = 0;
        }
    }
}

void dynamic_seam(struct rgb_img *grad, double **best_arr){
    /*
     * Calculates the minimum energy cost at each position
     */
    int x, y;
    double cur_min = 10000;
    double cost = 0;
    int opt;

    //initialize best_arr
    *best_arr = (double *)malloc(sizeof(double) * grad->width * grad->height);

    //set the first row of best_arr to the first row of grad
    for(x = 0; x < grad->width; x++){
        (*best_arr)[x] = get_pixel(grad, 0, x, 0);
    }

    //loop through each row and column of grad and calculate minimum cost
    for(y = 1; y < grad->height; y++){
        for(x = 0; x < grad->width; x++){
            for(opt = -1; opt < 2; opt++){
                //check each option (either left, middle, or right)
                //skip the option if it's out of bounds.
                if(x + opt < 0 || x + opt > grad->width - 1){
                    continue;
                }
                //update the current minimum if the option being checked is minimal
                cost = (*best_arr)[grad->width * (y - 1) + x + opt] + get_pixel(grad, y, x, 0);
                if(cost < cur_min){
                    cur_min = cost;
                }
            }
            //Set the solution of the position to the minimum
            (*best_arr)[grad->width * y + x] = cur_min;
            cur_min = 10000;
        }
    }
}

void recover_path(double *best, int height, int width, int **path){
    /*
     * Recovers the best path (minimum energy) from a double array of
     * energy costs
     */
    *path = (int *)malloc(sizeof(int) * height);

    int row, col, cur_pos, cur_min_pos;
    int cur_min = 10000;
    //find the initial position
    for(col = 0; col < width; col++){
        if(best[col] < cur_min){
            cur_min = (int)best[col];
            cur_min_pos = col;
        }
    }
    cur_pos = cur_min_pos;
    (*path)[0] = cur_pos;
    cur_min = 10000;

    int opt;
    //now that we have the initial position
    //loop through the height of the array from top to bottom
    //check adjacent positions and choose the minimum
    for(row = 1; row < height; row++){
        for(opt = -1; opt < 2; opt++){
            if(cur_pos + opt < 0 || cur_pos + opt > width - 1){
                continue;
            }
            //update the current minimum if the option is minimal
            if(best[width * row + cur_pos + opt] < cur_min){
                cur_min = (int)best[width * row + cur_pos + opt];
                cur_min_pos = cur_pos + opt;
            }
        }
        //set the solution at the position as the minimal option
        cur_pos = cur_min_pos;
        (*path)[row] = cur_min_pos;
        cur_min = 10000;
    }
}

void remove_seam(struct rgb_img *src, struct rgb_img **dest, int *path){
    /*
     * Removes a seam from images src and writes it to dest given path
     */
    //initialize new image
    *dest = (struct rgb_img *)malloc(sizeof(struct rgb_img));
    (*dest)->width = src->width - 1;
    (*dest)->height = src->height;
    (*dest)->raster = (uint8_t *)malloc(3 * (*dest)->height * (*dest)->width);

    //build the raster by copying all items from previous raster except
    //the column of the path
    int row, col, iter = 0;
    for(row = 0; row < src->height; row++){
        for(col = 0; col < src->width; col++){
            if(col == path[row]){
                continue;
            }
            set_pixel(*dest, row, iter, get_pixel(src, row, col, 0), get_pixel(src, row, col, 1), get_pixel(src, row, col, 2));
            iter += 1;
        }
        iter = 0;
    }
}

void print_d_arr(double *arr, int width, int height){
    /*
     * Prints a double array
     */
    int row, col, item = 0;

    for(col = 0; col < height; col++){
        for(row = 0; row < width - 1; row++){
            printf("%f ", arr[item]);
            item += 1;
        }
        printf("%f\n", arr[item]);
        item += 1;
    }
}

void print_iarr(int *arr, int width, int height){
    /*
     * Prints an integer array
     */
    int row, col, item = 0;

    for(col = 0; col < height; col++){
        for(row = 0; row < width - 1; row++){
            printf("%d ", arr[item]);
            item += 1;
        }
        printf("%d\n", arr[item]);
        item += 1;
    }
}

int main(void){
    //read in the 6x5.bin image
    struct rgb_img *img;
    char name[] = "HJoceanSmall.bin";
    read_in_img(&img, name);

    //Part 1: Dual-Gradient Energy Function
    struct rgb_img *grad;
    calc_energy(img,  &grad);
//    print_grad(grad);

    //Part 2: Cost Array
    double *best_arr;
    dynamic_seam(grad, &best_arr);
//    print_d_arr(best_arr, grad->width, grad->height);

    //Part 3: Recover the seam
    int *best_path;
    recover_path(best_arr, grad->height, grad->width, &best_path);
    print_iarr(best_path, grad->height, 1);

    //Part 4: Write a function that removes the seam
    struct rgb_img *dest;
    remove_seam(img, &dest, best_path);

    return 0;
}
