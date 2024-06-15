from ._bilateral_3d import apply_bilateral_filter

import numpy as np


def bilateral_filter_3d(image, filter_diameter, sigma_i, sigma_s):
    if len(image.shape) != 4:
        raise ValueError(
            f"The image should have 4 dimensions, found {len(image.shape)}."
        )

    filtered_images = np.zeros_like(image)

    for idx in range(image.shape[0]):
        filtered_images[idx] = apply_bilateral_filter(
            image[idx], filter_diameter, sigma_i, sigma_s
        )

    return filtered_images
