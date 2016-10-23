// Copyright 2016, Josh Baker.
// All rights reserved.
//
// Author: joshuabaker2@gmail.com (Josh Baker)
//
// The SimplePolyline Class Tests using gtest

#include "SimplePolylineTest.h"

TEST_F(SimplePolylineTest, TestSimpleEncodeDecode) {
  static const int buffer_size = 10;
  static const int num_coords = 1;
  static const int precision = 5;

  char encoded[buffer_size] = {0};

  float coordinates[num_coords][2] = {{41.75368, -87.97330}};

  SimplePolyline polyline(precision);
  polyline.encode(coordinates, num_coords, encoded);

  float decoded_coordinates[num_coords][2];
  int num_decoded_coords = polyline.decode(encoded, decoded_coordinates);

  EXPECT_EQ(num_coords, num_decoded_coords);
  EXPECT_FLOAT_EQ(41.75368, decoded_coordinates[0][0]);
  EXPECT_FLOAT_EQ(-87.97330, decoded_coordinates[0][1]);
}

// Encoded string generated from https://developers.google.com/maps/documentation/utilities/polylineutility
TEST_F(SimplePolylineTest, TestSimpleDecodeFromGoogleMapAPI) {
  static const int num_coords = 1;

  char *encoded = (char*)"zh_pChhmfE";
  float decoded_coordinates[num_coords][2];

  SimplePolyline polyline;

  int num_decoded_coords = polyline.decode(encoded, decoded_coordinates);

  EXPECT_EQ(num_coords, num_decoded_coords);
  EXPECT_FLOAT_EQ(-23.75838, decoded_coordinates[0][0]);
  EXPECT_FLOAT_EQ(-32.67733, decoded_coordinates[0][1]);
}

TEST_F(SimplePolylineTest, TestSimpleEncodeDecodeLowPrecision) {
  static const int buffer_size = 10;
  static const int num_coords = 1;
  static const int precision = 3;

  char encoded[buffer_size] = {0};
  float coordinates[num_coords][2] = {{41.75368, -87.97330}};

  SimplePolyline polyline(precision);

  polyline.encode(coordinates, num_coords, encoded);

  float decoded_coordinates[num_coords][2];
  int num_decoded_coords = polyline.decode(encoded, decoded_coordinates);

  EXPECT_EQ(num_coords, num_decoded_coords);
  EXPECT_FLOAT_EQ(41.753, decoded_coordinates[0][0]);
  EXPECT_FLOAT_EQ(-87.973, decoded_coordinates[0][1]);
}

TEST_F(SimplePolylineTest, TestSimpleDecode) {
  static const int buffer_size = 10;
  static const int num_coords = 1;

  char encoded[buffer_size] = {0};
  float coordinates[num_coords][2] = {{64.12345, -12.91827}};

  SimplePolyline polyline;

  polyline.encode(coordinates, num_coords, encoded);

  float decoded_coordinates[num_coords][2];
  int num_decoded_coords = polyline.decode(encoded, decoded_coordinates);

  EXPECT_EQ(num_coords, num_decoded_coords);
  EXPECT_FLOAT_EQ(64.12345, decoded_coordinates[0][0]);
  EXPECT_FLOAT_EQ(-12.91827, decoded_coordinates[0][1]);
}

// Encoded string generated from https://developers.google.com/maps/documentation/utilities/polylineutility
TEST_F(SimplePolylineTest, TripleSimpleDecode) {
  static const int precision = 5;
  static const int num_coords = 3;

  SimplePolyline polyline(precision);

  float decoded_coordinates[num_coords][2];

  char* encoded = (char*)"_nq~F|}bvOtnGx{DppBq|H";
  int num_decoded_coords = polyline.decode(encoded, decoded_coordinates);

  EXPECT_EQ(num_coords, num_decoded_coords);

  EXPECT_FLOAT_EQ(41.87376, decoded_coordinates[0][0]);
  EXPECT_FLOAT_EQ(-87.67471, decoded_coordinates[0][1]);

  EXPECT_FLOAT_EQ(41.83029, decoded_coordinates[1][0]);
  EXPECT_FLOAT_EQ(-87.70492, decoded_coordinates[1][1]);

  EXPECT_FLOAT_EQ(41.81212, decoded_coordinates[2][0]);
  EXPECT_FLOAT_EQ(-87.65411, decoded_coordinates[2][1]);
}

TEST_F(SimplePolylineTest, TripSimpleEncodeDecode) {
  static const int buffer_size = 32;
  static const int num_coords = 3;
  char encoded[buffer_size] = {0};

  SimplePolyline polyline;

  float coordinates[num_coords][2] = {{41.87376, -87.67471}, {41.83029, -87.70492}, {41.81212, -87.65411}};
  polyline.encode(coordinates, num_coords, encoded);

  float decoded_coordinates[num_coords][2];
  int num_decoded_coords = polyline.decode(encoded, decoded_coordinates);

  EXPECT_EQ(num_coords, num_decoded_coords);

  EXPECT_FLOAT_EQ(41.87376, decoded_coordinates[0][0]);
  EXPECT_FLOAT_EQ(-87.67471, decoded_coordinates[0][1]);

  EXPECT_FLOAT_EQ(41.83029, decoded_coordinates[1][0]);
  EXPECT_FLOAT_EQ(-87.70492, decoded_coordinates[1][1]);

  EXPECT_FLOAT_EQ(41.81212, decoded_coordinates[2][0]);
  EXPECT_FLOAT_EQ(-87.65411, decoded_coordinates[2][1]);
}
