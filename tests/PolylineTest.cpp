// Copyright 2016, Josh Baker.
// All rights reserved.
//
// Author: joshuabaker2@gmail.com (Josh Baker)
//
// The Polyline Class Tests using gtest

#include "PolylineTest.h"

TEST_F(PolylineTest, TestEncodeDecode) {
  static const int buffer_size = 10;
  static const int num_coords = 1;
  static const int precision = 5;

  char encoded[buffer_size] = {0};
  GPSCoordinate gps_coordinates[num_coords];
  gps_coordinates[0].set_coordinates(41.75368, -87.97330);

  Polyline polyline(precision);
  polyline.encode(gps_coordinates, num_coords, encoded);

  GPSCoordinate decoded_coordinates[10];
  polyline.decode(encoded, decoded_coordinates);

  EXPECT_FLOAT_EQ(gps_coordinates[0].latitude(), decoded_coordinates[0].latitude());
  EXPECT_FLOAT_EQ(gps_coordinates[0].longitude(), decoded_coordinates[0].longitude());
}

// Encoded string generated from https://developers.google.com/maps/documentation/utilities/polylineutility
TEST_F(PolylineTest, TestDecodeFromGoogleMapAPI) {
  char *encoded = (char*)"zh_pChhmfE";
  GPSCoordinate decoded_coordinates[5];

  Polyline polyline;

  polyline.decode(encoded, decoded_coordinates);
  EXPECT_FLOAT_EQ(-23.75838, decoded_coordinates[0].latitude());
  EXPECT_FLOAT_EQ(-32.67733, decoded_coordinates[0].longitude());
}

TEST_F(PolylineTest, TestEncodeDecodeLowPrecision) {
  static const int buffer_size = 10;
  static const int num_coords = 1;
  static const int precision = 3;

  char encoded[buffer_size] = {0};
  GPSCoordinate gps_coordinates[num_coords];
  gps_coordinates[0].set_coordinates(41.75368, -87.97330);

  Polyline polyline(precision);

  polyline.encode(gps_coordinates, num_coords, encoded);

  GPSCoordinate decoded_coordinates[5];
  polyline.decode(encoded, decoded_coordinates);

  EXPECT_FLOAT_EQ(41.753, decoded_coordinates[0].latitude());
  EXPECT_FLOAT_EQ(-87.973, decoded_coordinates[0].longitude());
}

TEST_F(PolylineTest, TestDecode) {
  static const int buffer_size = 10;
  static const int num_coords = 1;
  char encoded[buffer_size] = {0};
  GPSCoordinate gps_coordinates[num_coords];
  gps_coordinates[0].set_coordinates(64.12345, -12.91827);

  Polyline polyline;

  polyline.encode(gps_coordinates, num_coords, encoded);

  GPSCoordinate decoded_coordinates[5];
  polyline.decode(encoded, decoded_coordinates);

  EXPECT_FLOAT_EQ(64.12345, decoded_coordinates[0].latitude());
  EXPECT_FLOAT_EQ(-12.91827, decoded_coordinates[0].longitude());
}

// Encoded string generated from https://developers.google.com/maps/documentation/utilities/polylineutility
TEST_F(PolylineTest, TripleDecode) {
  static const int precision = 5;
  Polyline polyline(precision);
  int buffer_size = 5;
  GPSCoordinate decoded_coordinates[buffer_size];

  static char* encoded = (char*)"_nq~F|}bvOtnGx{DppBq|H";
  int num_decoded_coords = polyline.decode(encoded, decoded_coordinates);

  EXPECT_TRUE(num_decoded_coords <= buffer_size);

  EXPECT_FLOAT_EQ(41.87376, decoded_coordinates[0].latitude());
  EXPECT_FLOAT_EQ(-87.67471, decoded_coordinates[0].longitude());

  EXPECT_FLOAT_EQ(41.83029, decoded_coordinates[1].latitude());
  EXPECT_FLOAT_EQ(-87.70492, decoded_coordinates[1].longitude());

  EXPECT_FLOAT_EQ(41.81212, decoded_coordinates[2].latitude());
  EXPECT_FLOAT_EQ(-87.65411, decoded_coordinates[2].longitude());
}

TEST_F(PolylineTest, TripleEncodeDecode) {
  static const int buffer_size = 32;
  static const int num_coords = 3;
  char encoded[buffer_size] = {0};


  Polyline polyline;

  GPSCoordinate gps_coordinates[num_coords];
  gps_coordinates[0].set_coordinates(41.87376, -87.67471);
  gps_coordinates[1].set_coordinates(41.83029, -87.70492);
  gps_coordinates[2].set_coordinates(41.81212, -87.65411);

  polyline.encode(gps_coordinates, num_coords, encoded);

  GPSCoordinate decoded_coordinates[3];
  polyline.decode(encoded, decoded_coordinates);

  EXPECT_FLOAT_EQ(41.87376, decoded_coordinates[0].latitude());
  EXPECT_FLOAT_EQ(-87.67471, decoded_coordinates[0].longitude());

  EXPECT_FLOAT_EQ(41.83029, decoded_coordinates[1].latitude());
  EXPECT_FLOAT_EQ(-87.70492, decoded_coordinates[1].longitude());

  EXPECT_FLOAT_EQ(41.81212, decoded_coordinates[2].latitude());
  EXPECT_FLOAT_EQ(-87.65411, decoded_coordinates[2].longitude());
}