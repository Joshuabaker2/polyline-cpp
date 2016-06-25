/*
 * Created by joshuabaker2 on 26/03/16.
*/

#include "SimplePolyline.h"

SimplePolyline::SimplePolyline(int precision) {
  _precision = precision;
  _factor = power(10, _precision);
}

SimplePolyline::SimplePolyline() { }

/**
 * Encodes the given latitude, longitude coordinates.
 *
 * @param {float[2]} coordinates
 *  coordinates[0] = latitude
 *  coordinates[1] = longitude
 * @returns char*
 */
void SimplePolyline::encode(float coordinates[][2], int num_coords, char *output) {
  _encodeSingleCoord(coordinates[0][0], output);
  _encodeSingleCoord(coordinates[0][1], output);

  for (int i = 1; i < num_coords; i++) {
    _encodeSingleCoord(coordinates[i][0] - coordinates[i - 1][0], output);
    _encodeSingleCoord(coordinates[i][1] - coordinates[i - 1][1], output);
  }
}


/** TODO documentation
 * Decodes to a [latitude, longitude] coordinates array.
 *
 * This is adapted from the implementation in Project-OSRM.
 *
 * @param {String} str
 * @param {[float]} decodedCoords - return coordinates through here (passed by reference)
 * @returns void
 *
 * @see https://github.com/Project-OSRM/osrm-frontend/blob/master/WebContent/routing/OSRM.RoutingGeometry.js
 */
void SimplePolyline::decode(char *str, float output[][2]) {
  int32_t index = 0, shift = 0, result = 0;
  float latlng[2] = {0, 0};
  char byte = '\0';

  for (int i = 0; index < strlen(str); i++) {
    for (int j = 0; j < 2; j++) {
      shift = result = 0;
      byte = '\0';
      do {
        byte = str[index++] - 63;
        result |= (int32_t)(byte & 0x1f) << (int32_t) shift;
        shift += 5;
      } while (byte >= 0x20); // 0x20 is blank, numbers below are garbage
      latlng[j] += (((result & 1) != 0 ? ~(result >> 1) : (result >> 1)));
      output[i][j] = latlng[j] / _factor;
    }
  }
}

/**
 * Based off https://developers.google.com/maps/documentation/utilities/polylinealgorithm
 */
void SimplePolyline::_encodeSingleCoord(float coordinate, char *output) {
  int32_t intCoord = (int32_t)(coordinate * _factor);
  intCoord <<= (int32_t) 1;

  if (intCoord < 0) {
    intCoord = ~intCoord;
  }

  int index;
  for (index = 0; output[index]; index++);

  for (index; intCoord >= 0x20; index++) {
    output[index] = (char) (0x20 | (int32_t)(intCoord & 0x1f)) + 63;
    intCoord >>= (int32_t) 5;
  }
  output[index] = (char) (intCoord + 63);
}




