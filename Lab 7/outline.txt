Lab 7
=====

1. In thie question, you will familiarize yourself with working with images using c_img.c and png2bin.py,
   files that were given to you as part of Project 2.

   You can make an image brighter by multiplying all the pixel values by a constant
   larger than 1; and you can make an image darker by multiplying all the pixel values
   by a constant smaller than one.

   c_img.c/c_img.h store reg/green/blue pixel values as uint8_t's -- values between 0
   and 255. If you are trying to make an image brighter, you may need to round the products
   you obtain by multiplying by a larger constant down to 255.

   Download the image

   https://www.president.utoronto.ca/secure-content/uploads/2017/09/UofTPresidentMericGertler-smaller.jpg

   Convert the image to a bin file using png2bin.py

   Write C code to create five different versions of the image at different levels of brightness.

2. Write Python code to find the cost of the minimum-energy seam in a list of lists.

energies = [[24,      22,      30,      15,      18,      19],
            [12,      23,      15,      23,      10,     15],
            [11,      13,      22,      13,      21,      14],
            [13,      15,      17,      28,      19,      21],
            [17,      17,      7,       27,      20,      19]]
     
    The correct output for the given energies data is 15+10+13+17+7 = 62.
