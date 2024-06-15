#pragma once

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
);