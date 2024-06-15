cdef from extern "_bilateral_3d.h":
    void _apply_bilateral_filter(double*** original_image,
                                 double*** filtered_image,
                                 int x,
                                 int y,
                                 int z,
                                 int diameter,
                                 double sigma_i,
                                 double sigma_s,
                                 int dim_x,
                                 int dim_y,
                                 int dim_z)

import numpy as np
cimport numpy as np


def apply_bilateral_filter(np.ndarray[np.float64_t, ndim=3] original_image,
                           np.ndarray[np.float64_t, ndim=3] filtered_image,
                           int x, int y, int z,
                           int diameter,
                           double sigma_i,
                           double sigma_s):
    cdef int dim_x = original_image.shape[0]
    cdef int dim_y = original_image.shape[1]
    cdef int dim_z = original_image.shape[2]

    cdef double*** original_image_ptr = <double***> np.PyArray_DATA(original_image)
    cdef double*** filtered_image_ptr = <double***> np.PyArray_DATA(filtered_image)

    _apply_bilateral_filter(original_image_ptr,
                            filtered_image_ptr,
                            x, y, z,
                            diameter,
                            sigma_i,
                            sigma_s,
                            dim_x,
                            dim_y,
                            dim_z)

def bilateral_filter(np.ndarray[np.float64_t, ndim=3] source,
                         int filter_diameter,
                         double sigma_i,
                         double sigma_s):
    cdef int i, j, k
    cdef int dim_x = source.shape[0]
    cdef int dim_y = source.shape[1]
    cdef int dim_z = source.shape[2]

    filtered_image = np.zeros_like(source)

    for i in range(dim_x):
        for j in range(dim_y):
            for k in range(dim_z):
                apply_bilateral_filter(source, filtered_image, i, j, k, filter_diameter, sigma_i, sigma_s)

    return filtered_image
