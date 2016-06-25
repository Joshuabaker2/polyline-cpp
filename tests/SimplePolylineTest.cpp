//
// Created by joshuabaker2 on 12/04/16.
//

#include "SimplePolylineTest.h"

TEST_F(PolylineTest, TestEncodeDecode) {
  static const int bufferSize = 10;
  static const int precision = 5;

  char encoded[bufferSize] = {0};
  float coordinates[2] = {41.75368, -87.97330};

  Polyline polyline(precision);
  polyline.encode(coordinates, encoded);

  float decodedCoordinates[10];
  polyline.decode(encoded, decodedCoordinates);

  EXPECT_FLOAT_EQ(41.75368, decodedCoordinates[0]);
  EXPECT_FLOAT_EQ(-87.97330, decodedCoordinates[1]);
}

// Encoded string generated from https://developers.google.com/maps/documentation/utilities/polylineutility
TEST_F(PolylineTest, TestDecodeFromGoogleMapAPI) {
  char *encoded = (char*)"zh_pChhmfE";
  float decodedCoordinates[10];

  Polyline polyline;

  polyline.decode(encoded, decodedCoordinates);
  EXPECT_FLOAT_EQ(-23.75838, decodedCoordinates[0]);
  EXPECT_FLOAT_EQ(-32.67733, decodedCoordinates[1]);
}

TEST_F(PolylineTest, TestEncodeDecodeLowPrecision) {
  static const int bufferSize = 10;
  static const int precision = 3;

  char encoded[bufferSize] = {0};
  float coordinates[2] = {41.75368, -87.97330};

  Polyline polyline(precision);

  polyline.encode(coordinates, encoded);

  float decodedCoordinates[10];
  polyline.decode(encoded, decodedCoordinates);

  EXPECT_FLOAT_EQ(41.753, decodedCoordinates[0]);
  EXPECT_FLOAT_EQ(-87.973, decodedCoordinates[1]);
}

TEST_F(PolylineTest, TestDecode) {
  static const int bufferSize = 10;
  char encoded[bufferSize] = {0};
  float coordinates[2] = {64.12345, -12.91827};

  Polyline polyline;

  polyline.encode(coordinates, encoded);

  float decodedCoordinates[10];
  polyline.decode(encoded, decodedCoordinates);

  EXPECT_FLOAT_EQ(64.12345, decodedCoordinates[0]);
  EXPECT_FLOAT_EQ(-12.91827, decodedCoordinates[1]);
}

// Encoded string generated from https://developers.google.com/maps/documentation/utilities/polylineutility
TEST_F(PolylineTest, TripleDecode) {
  static const int precision = 5;
  Polyline polyline(precision);
  float decodedCoordinates[10];
  char* encoded = (char*)"_nq~F|}bvOtnGx{DppBq|H";
  polyline.decode(encoded, decodedCoordinates);

  EXPECT_FLOAT_EQ(41.87376, decodedCoordinates[0]);
  EXPECT_FLOAT_EQ(-87.67471, decodedCoordinates[1]);

  EXPECT_FLOAT_EQ(41.83029, decodedCoordinates[2]);
  EXPECT_FLOAT_EQ(-87.70492, decodedCoordinates[3]);

  EXPECT_FLOAT_EQ(41.81212, decodedCoordinates[4]);
  EXPECT_FLOAT_EQ(-87.65411, decodedCoordinates[5]);
}

TEST_F(PolylineTest, TripleEncodeDecode) {
  static const int bufferSize = 32;
  char encoded[bufferSize] = {0};

  Polyline polyline;

  float coordinates[6] = {41.87376, -87.67471, 41.83029, -87.70492, 41.81212, -87.65411};
  polyline.encode(coordinates, encoded);

  float decodedCoordinates[10];
  polyline.decode(encoded, decodedCoordinates);

  EXPECT_NEAR(41.87376, decodedCoordinates[0], 0.000015);
  EXPECT_NEAR(-87.67471, decodedCoordinates[1], 0.000015);

  EXPECT_NEAR(41.83029, decodedCoordinates[2], 0.000015);
  EXPECT_NEAR(-87.70492, decodedCoordinates[3], 0.000015);

  EXPECT_NEAR(41.81212, decodedCoordinates[4], 0.000015);
  EXPECT_NEAR(-87.65411, decodedCoordinates[5], 0.000015);
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}