//
// Created by daniel on 08/06/23.
//

#ifndef CANVAS_CLION_UTILS_H
#define CANVAS_CLION_UTILS_H


#include "vectors/Vector2D.h"

class Utils {
    public:
        static fvec2 bspline(const fvec2* points, float t, int baseIndex, int arraySize) {
            fvec2 p{0, 0};

            for (int i = 0; i < 4; i++) {
                int accessIndex = baseIndex + i;
                // If we are on the last points we then avoid to access unexisting points and calculate with the last point repeatedly
                if (accessIndex >= arraySize) {
                    accessIndex = arraySize - 1;
                }
                p.x += bsplineFragment(points[accessIndex].x, t, i);
                p.y += bsplineFragment(points[accessIndex].y, t, i);
            }

            return p;
        }

        static float bsplineFragment(float p, float t, int index) {
            switch (index) {
                case 0:
                    return p * ((1-t)*(1-t)*(1-t))/6;
                case 1:
                    return p * (3*t*t*t - 6*t*t + 4)/6;
                case 2:
                    return p * (-3*t*t*t + 3*t*t + 3*t + 1)/6;
                case 3:
                    return p * (t*t*t)/6;
                default:
                    throw std::runtime_error("Invalid index provided to bsplineFn");
            }
        }

        static float modularReduction(float number, float modulus) {
            // Calculate the integer quotient
            float quotient = std::floor(number / modulus);

            // Calculate the remainder
            float remainder = number - (quotient * modulus);

            // Ensure the remainder is within the range of [0, modulus)
            if (remainder < 0) {
                remainder += modulus;
            }

            return remainder;
        }
};


#endif //CANVAS_CLION_UTILS_H
