#include "./_bilateral_3d.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define PI 3.14159265

double __distance(double x, double y, double z, double i, double j, double k) {
    return sqrt(pow((x - i), 2) + pow((y - j), 2) + pow((z - k), 2));
}

double __gaussian(double x, double sigma) {
    double __sig_square = pow(sigma, 2);
    return (1.0 / (2 * PI * __sig_square)) * exp(-1 * (pow(x, 2) / (2 * __sig_square)));
}

void _apply_bilateral_filter(
    double*** original_image,
    double*** filtered_image,
    int x,
    int y,
    int z,
    int diameter,
    double sigma_i,
    double sigma_s,
    int dim_x,
    int dim_y,
    int dim_z
) {
    int hl = floor(diameter / 2);
    double i_filtered = 0.0;
    double Wp = 0.0;

    for (int i = 0; i < diameter; i++) {
        for (int j = 0; j < diameter; j++) {
            for (int k = 0; k < diameter; k++) {
                int neighbour_x = x - hl + i;
                int neighbour_y = y - hl + j;
                int neighbour_z = z - hl + k;

                // Handling out-of-bounds by wrapping around
                if (neighbour_x < 0) neighbour_x += dim_x;
                if (neighbour_x >= dim_x) neighbour_x -= dim_x;

                if (neighbour_y < 0) neighbour_y += dim_y;
                if (neighbour_y >= dim_y) neighbour_y -= dim_y;

                if (neighbour_z < 0) neighbour_z += dim_z;
                if (neighbour_z >= dim_z) neighbour_z -= dim_z;

                double intensity_diff = original_image[neighbour_x][neighbour_y][neighbour_z] - original_image[x][y][z];
                double gi = __gaussian(intensity_diff, sigma_i);
                double gs = __gaussian(__distance(neighbour_x, neighbour_y, neighbour_z, x, y, z), sigma_s);
                double w = gi * gs;
                i_filtered += original_image[neighbour_x][neighbour_y][neighbour_z] * w;
                Wp += w;
            }
        }
    }

    if (Wp != 0) {
        i_filtered = i_filtered / Wp;
    } else {
        i_filtered = original_image[x][y][z];
    }
    filtered_image[x][y][z] = round(i_filtered);

}