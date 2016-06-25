/*
 * Created by joshuabaker2 on 26/03/16.
*/

#include "Polyline.h"

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
 * @returns char*
 */
void Polyline::encode(GPSCoordinate *gpsCoordinates, char *output) {
  _encodeSingleCoord(gpsCoordinates[0].latitude(), output);
  _encodeSingleCoord(gpsCoordinates[0].longitude(), output);

  for (int i = 1; !gpsCoordinates[i].isEmpty(); i++) {
    _encodeSingleCoord(gpsCoordinates[i].latitude() - gpsCoordinates[i - 1].latitude(), output);
    _encodeSingleCoord(gpsCoordinates[i].longitude() - gpsCoordinates[i - 1].latitude(), output);
  }

}


/** TODO documentation
 * Decodes to a [latitude, longitude] coordinates array.
 *
 * This is adapted from the implementation in Project-OSRM.
 *
 * @param {String} str
 * @param {[GPSCoordinate]} decodedCoords - return coordinates through here (passed by reference)
 * @returns void
 *
 * @see https://github.com/Project-OSRM/osrm-frontend/blob/master/WebContent/routing/OSRM.RoutingGeometry.js
 */
void Polyline::decode(char *str, GPSCoordinate *output) {
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
    }
    output[i].SetCoordinates(latlng[0] / _factor, latlng[1] / _factor);
  }
}

/**
 * Based off https://developers.google.com/maps/documentation/utilities/polylinealgorithm
 */
void Polyline::_encodeSingleCoord(float coordinate, char *output) {
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




