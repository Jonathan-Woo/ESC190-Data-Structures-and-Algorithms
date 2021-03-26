# Lab 7
# =====
#
# 1. In thie question, you will familiarize yourself with working with images using c_img.c and png2bin.py,
#    files that were given to you as part of Project 2.
#
#    You can make an image brighter by multiplying all the pixel values by a constant
#    larger than 1; and you can make an image darker by multiplying all the pixel values
#    by a constant smaller than one.
#
#    c_img.c/c_img.h store reg/green/blue pixel values as uint8_t's -- values between 0
#    and 255. If you are trying to make an image brighter, you may need to round the products
#    you obtain by multiplying by a larger constant down to 255.
#
#    Download the image
#
#    https://www.president.utoronto.ca/secure-content/uploads/2017/09/UofTPresidentMericGertler-smaller.jpg
#
#    Convert the image to a bin file using png2bin.py


#image = Image.open("meric.jpg")
#write_image(image, "meric.bin")


#    Write C code to create five different versions of the image at different levels of brightness.

#    Use set_pixel to change the values of RGB


# 2. Write Python code to find the cost of the minimum-energy seam in a list of lists.

energies = [[24,      22,      30,      15,      18,      19],
            [12,      23,      15,      23,      10,      15],
            [11,      13,      22,      13,      21,      14],
            [13,      15,      17,      28,      19,      21],
            [17,      17,      7,       27,      20,      19]]

#     The correct output for the given energies data is 15+10+13+17+7 = 62.

def min_energy (energies):
    previous_seam_energies_row = list(energies[0])

    # Skip the first row in the following loop.
    for y in range(1, len(energies)):
        pixel_energies_row = energies[y]
        seam_energies_row = []
        for x, pixel_energy in enumerate(pixel_energies_row):
            # Determine the range of x values to iterate over in the
            # previous row. The range depends on if the current pixel
            # is in the middle of the image, or on one of the edges.
            x_left = max(x - 1, 0)
            x_right = min(x + 1, len(pixel_energies_row) - 1)
            x_range = range(x_left, x_right + 1)
            min_seam_energy = pixel_energy + min(previous_seam_energies_row[x_i] for x_i in x_range)
            seam_energies_row.append(min_seam_energy)
        previous_seam_energies_row = seam_energies_row

    print (min(seam_energy for seam_energy in previous_seam_energies_row))