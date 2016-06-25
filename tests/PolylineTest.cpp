//
// Created by joshuabaker2 on 12/04/16.
//

#include "PolylineTest.h"

TEST_F(PolylineTest, TestEncodeDecode) {
  static const int buffer_size = 10;
  static const int num_coords = 1;
  static const int precision = 5;

  char encoded[buffer_size] = {0};
  GPSCoordinate gpsCoordinates[num_coords];
  gpsCoordinates[0].SetCoordinates(41.75368, -87.97330);

  Polyline polyline(precision);
  polyline.encode(gpsCoordinates, num_coords, encoded);

  GPSCoordinate decodedCoordinates[10];
  polyline.decode(encoded, decodedCoordinates);

  EXPECT_FLOAT_EQ(gpsCoordinates[0].latitude(), decodedCoordinates[0].latitude());
  EXPECT_FLOAT_EQ(gpsCoordinates[0].longitude(), decodedCoordinates[0].longitude());
}

// Encoded string generated from https://developers.google.com/maps/documentation/utilities/polylineutility
TEST_F(PolylineTest, TestDecodeFromGoogleMapAPI) {
  char *encoded = (char*)"zh_pChhmfE";
  GPSCoordinate decodedCoordinates[5];

  Polyline polyline;

  polyline.decode(encoded, decodedCoordinates);
  EXPECT_FLOAT_EQ(-23.75838, decodedCoordinates[0].latitude());
  EXPECT_FLOAT_EQ(-32.67733, decodedCoordinates[0].longitude());
}

TEST_F(PolylineTest, TestEncodeDecodeLowPrecision) {
  static const int buffer_size = 10;
  static const int num_coords = 1;
  static const int precision = 3;

  char encoded[buffer_size] = {0};
  GPSCoordinate gpsCoordinates[num_coords];
  gpsCoordinates[0].SetCoordinates(41.75368, -87.97330);

  Polyline polyline(precision);

  polyline.encode(gpsCoordinates, num_coords, encoded);

  GPSCoordinate decodedCoordinates[5];
  polyline.decode(encoded, decodedCoordinates);

  EXPECT_FLOAT_EQ(41.753, decodedCoordinates[0].latitude());
  EXPECT_FLOAT_EQ(-87.973, decodedCoordinates[0].longitude());
}

TEST_F(PolylineTest, TestDecode) {
  static const int buffer_size = 10;
  static const int num_coords = 1;
  char encoded[buffer_size] = {0};
  GPSCoordinate gpsCoordinates[num_coords];
  gpsCoordinates[0].SetCoordinates(64.12345, -12.91827);

  Polyline polyline;

  polyline.encode(gpsCoordinates, num_coords, encoded);

  GPSCoordinate decodedCoordinates[5];
  polyline.decode(encoded, decodedCoordinates);

  EXPECT_FLOAT_EQ(64.12345, decodedCoordinates[0].latitude());
  EXPECT_FLOAT_EQ(-12.91827, decodedCoordinates[0].longitude());
}

// Encoded string generated from https://developers.google.com/maps/documentation/utilities/polylineutility
TEST_F(PolylineTest, TripleDecode) {
  static const int precision = 5;
  Polyline polyline(precision);
  GPSCoordinate decodedCoordinates[5];

  static char* encoded = (char*)"_nq~F|}bvOtnGx{DppBq|H";
  polyline.decode(encoded, decodedCoordinates);

  EXPECT_FLOAT_EQ(41.87376, decodedCoordinates[0].latitude());
  EXPECT_FLOAT_EQ(-87.67471, decodedCoordinates[0].longitude());

  EXPECT_FLOAT_EQ(41.83029, decodedCoordinates[1].latitude());
  EXPECT_FLOAT_EQ(-87.70492, decodedCoordinates[1].longitude());

  EXPECT_FLOAT_EQ(41.81212, decodedCoordinates[2].latitude());
  EXPECT_FLOAT_EQ(-87.65411, decodedCoordinates[2].longitude());
}

TEST_F(PolylineTest, TripleEncodeDecode) {
  static const int buffer_size = 32;
  static const int num_coords = 3;
  char encoded[buffer_size] = {0};


  Polyline polyline;

  GPSCoordinate gpsCoordinates[num_coords];
  gpsCoordinates[0].SetCoordinates(41.87376, -87.67471);
  gpsCoordinates[1].SetCoordinates(41.83029, -87.70492);
  gpsCoordinates[2].SetCoordinates(41.81212, -87.65411);

  polyline.encode(gpsCoordinates, num_coords, encoded);

  GPSCoordinate decodedCoordinates[3];
  polyline.decode(encoded, decodedCoordinates);

  EXPECT_FLOAT_EQ(41.87376, decodedCoordinates[0].latitude());
  EXPECT_FLOAT_EQ(-87.67471, decodedCoordinates[0].longitude());

  EXPECT_FLOAT_EQ(41.83029, decodedCoordinates[1].latitude());
  EXPECT_FLOAT_EQ(-87.70492, decodedCoordinates[1].longitude());

  EXPECT_FLOAT_EQ(41.81212, decodedCoordinates[2].latitude());
  EXPECT_FLOAT_EQ(-87.65411, decodedCoordinates[2].longitude());
}