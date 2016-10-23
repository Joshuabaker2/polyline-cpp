// Copyright 2016, Josh Baker.
// All rights reserved.
//
// Author: joshuabaker2@gmail.com (Josh Baker)
//
// The Polyline Class

#include "Polyline.h"

/**
 * Precision is the floating point precision.
 */
Polyline::Polyline(int precision) {
  _precision = precision;
  _factor = power(10, _precision);
}

Polyline::Polyline() { }

/**
 * Encodes the given latitude, longitude coordinates.
 *
 * @param {float[2]} coordinates
 *  coordinates[0] = latitude
 *  coordinates[1] = longitude
 * @param {char*} output_str - The output c-string that is passed back by reference.
 */
void Polyline::encode(GPSCoordinate gpsCoordinates[], int num_coords, char *output_str) {
  encodeSingleCoord(gpsCoordinates[0].latitude(), output_str);
  encodeSingleCoord(gpsCoordinates[0].longitude(), output_str);

  for (int i = 1; i < num_coords && !gpsCoordinates[i].is_empty(); i++) {
    encodeSingleCoord(gpsCoordinates[i].latitude() - gpsCoordinates[i - 1].latitude(), output_str);
    encodeSingleCoord(gpsCoordinates[i].longitude() - gpsCoordinates[i - 1].longitude(), output_str);
  }
}


/**
 * Decodes to a [latitude, longitude] coordinates array from a given polyline string.
 *
 * This is adapted from the implementation in Project-OSRM.
 *
 * @param {String} str
 * @param {[GPSCoordinate]} decoded_coords - return coordinates through here (passed by reference)
 * @returns {int} - The number of coordinates that were decoded.
 *
 * @see https://github.com/Project-OSRM/osrm-frontend/blob/master/WebContent/routing/OSRM.RoutingGeometry.js
 */
int Polyline::decode(char *str, GPSCoordinate decoded_coords[]) {
  int32_t index = 0, shift = 0, result = 0;
  float latlng[2] = {0, 0};
  char byte;

  int i;
  for (i = 0; index + 1 < strlen(str); i++) {
    for (int j = 0; j < 2; j++) {
      shift = result = 0;
      do {
        byte = static_cast<char> (str[index++] - 63);
        result |= (int32_t) (byte & 0x1f) << (int32_t) shift;
        shift += 5;
      } while (byte >= 0x20);  // 0x20 is blank, numbers below are garbage
      latlng[j] += (((result & 1) != 0 ? ~(result >> 1) : (result >> 1))) / _factor;
    }
    decoded_coords[i].set_coordinates(latlng[0], latlng[1]);
  }

  return i;
}

/**
 * Based off https://developers.google.com/maps/documentation/utilities/polylinealgorithm
 */
void Polyline::encodeSingleCoord(float coordinate, char *output_str) {
  int32_t int_coord = (int32_t) (coordinate * _factor);
  int_coord <<= (int32_t) 1;

  if (int_coord < 0) {
    int_coord = ~int_coord;
  }

  int index;
  for (index = 0; output_str[index]; index++) {}

  for (index; int_coord >= 0x20; index++) {
    output_str[index] = static_cast<char> (static_cast<char> (0x20 | (int32_t) (int_coord & 0x1f)) + 63);
    int_coord >>= (int32_t) 5;
  }
  output_str[index] = static_cast<char> (int_coord + 63);
}




