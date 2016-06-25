/*
 * Created by joshuabaker2 on 26/03/16.
*/

#ifndef MCU_POLYLINE_H
#define MCU_POLYLINE_H

#include <stdint.h>

class SimplePolyline {
 public:
  SimplePolyline();
  SimplePolyline(int precision);
  void encode(float coordinates[][2], int num_coords, char *output);
  void decode(char *str, float output[][2]);

 private:
  int _precision = 5;
  float _factor = power(10, _precision);

  void _encodeSingleCoord(float coordinate, char *output);

  /*
  * @param: base and exponent
  * returns: the power of the base to the exponent, as a float
  */
  inline float power(float base, int exponent) {
    float r = 1.0;
    if (exponent < 0) {
      base = 1.0 / base;
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
  inline int strlen(char *str) {
    int len;
    for (len = 0; str[len]; len++);
    return len;
  }

};


#endif //MCU_POLYLINE_H
