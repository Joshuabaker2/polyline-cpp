// Copyright 2016, Josh Baker.
// All rights reserved.
//
// Author: joshuabaker2@gmail.com (Josh Baker)
//
// The SimplePolyline Class


#ifndef SIMPLEPOLYLINE_H_
#define SIMPLEPOLYLINE_H_

#include <stdint.h>

class SimplePolyline {
 public:
  SimplePolyline();
  explicit SimplePolyline(int precision);
  void encode(float coordinates[][2], int num_coords, char *output_str);
  int decode(char *str, float output[][2]);

 private:
  int _precision = 5;
  float _factor = power(10, _precision);

  void encodeSingleCoord(float coordinate, char *output_str);

  /*
  * @param: base and exponent
  * returns: the power of the base to the exponent, as a float
  */
  inline float power(float base, int exponent) {
    float r = 1.0;
    if (exponent < 0) {
      base = r / base;
      exponent = -exponent;
    }
    while (exponent) {
      if (exponent & 1)
        r *= base;
      base *= base;
      exponent >>= 1;
    }
    return r;
  }

/**
 * Reimplementing a basic strlen because we don't want to include string.h in an embedded system.
 */
  inline int32_t strlen(char *str) {
    int32_t len = 0;
    while (str[++len]) {}
    return len;
  }
};

#endif  // SIMPLEPOLYLINE_H_
