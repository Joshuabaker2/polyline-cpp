// Copyright 2016, Josh Baker.
// All rights reserved.
//
// Author: joshuabaker2@gmail.com (Josh Baker)
//
// SimplePolylineTest.cpp for Arduino

#if ARDUINO >= 100
  #include "Arduino.h"
#else
  #include "WProgram.h"
#endif

#include "../../../src/SimplePolyline.h"

int tests_failed = 0;
int tests_succeeded = 0;

void TestSimpleDecode();
void TestSimpleDecodeFromGoogleMapAPI();
void TestSimpleEncodeDecodeLowPrecision();
void TestSimpleDecode();
void TripleSimpleDecode();
void TripSimpleleEncodeDecode();

inline void EXPECT_FLOAT_EQ(float a, float b) {
  if (a != b) {
    Serial.print("Error, "); Serial.print(a); Serial.print(" and "); Serial.print(b); Serial.println(" are not equal");
    tests_failed++;
    return;
  }
  tests_succeeded++;
  return;
}

void setup() {
  TestSimpleDecode();
  TestSimpleDecodeFromGoogleMapAPI();
  TestSimpleEncodeDecodeLowPrecision();
  TestSimpleDecode();
  TripleSimpleDecode();
  TripSimpleleEncodeDecode();

  Serial.print("# of tests failed: "); Serial.println(tests_failed);
  Serial.print("# of tests succeeded: "); Serial.println(tests_succeeded);
}

void loop() {

}

void TestSimpleEncodeDecode() {
  static const int buffer_size = 10;
  static const int num_coords = 1;
  static const int precision = 5;

  char encoded[buffer_size] = {0};

  float coordinates[num_coords][2] = {{41.75368, -87.97330}};

  SimplePolyline polyline(precision);
  polyline.encode(coordinates, num_coords, encoded);

  float decodedCoordinates[num_coords][2];
  polyline.decode(encoded, decodedCoordinates);

  EXPECT_FLOAT_EQ(41.75368, decodedCoordinates[0][0]);
  EXPECT_FLOAT_EQ(-87.97330, decodedCoordinates[0][1]);
}

// Encoded string generated from https://developers.google.com/maps/documentation/utilities/polylineutility
void TestSimpleDecodeFromGoogleMapAPI() {
  static const int num_coords = 1;

  char *encoded = (char*)"zh_pChhmfE";
  float decodedCoordinates[num_coords][2];

  SimplePolyline polyline;

  polyline.decode(encoded, decodedCoordinates);
  EXPECT_FLOAT_EQ(-23.75838, decodedCoordinates[0][0]);
  EXPECT_FLOAT_EQ(-32.67733, decodedCoordinates[0][1]);
}

void TestSimpleEncodeDecodeLowPrecision() {
  static const int buffer_size = 10;
  static const int num_coords = 1;
  static const int precision = 3;

  char encoded[buffer_size] = {0};
  float coordinates[num_coords][2] = {{41.75368, -87.97330}};

  SimplePolyline polyline(precision);

  polyline.encode(coordinates, num_coords, encoded);

  float decodedCoordinates[num_coords][2];
  polyline.decode(encoded, decodedCoordinates);

  EXPECT_FLOAT_EQ(41.753, decodedCoordinates[0][0]);
  EXPECT_FLOAT_EQ(-87.973, decodedCoordinates[0][1]);
}

void TestSimpleDecode() {
  static const int buffer_size = 10;
  static const int num_coords = 1;

  char encoded[buffer_size] = {0};
  float coordinates[num_coords][2] = {{64.12345, -12.91827}};

  SimplePolyline polyline;

  polyline.encode(coordinates, num_coords, encoded);

  float decodedCoordinates[num_coords][2];
  polyline.decode(encoded, decodedCoordinates);

  EXPECT_FLOAT_EQ(64.12345, decodedCoordinates[0][0]);
  EXPECT_FLOAT_EQ(-12.91827, decodedCoordinates[0][1]);
}

// Encoded string generated from https://developers.google.com/maps/documentation/utilities/polylineutility
void TripleSimpleDecode() {
  static const int precision = 5;
  static const int num_coords = 3;

  SimplePolyline polyline(precision);

  float decodedCoordinates[num_coords][2];

  char* encoded = (char*)"_nq~F|}bvOtnGx{DppBq|H";
  polyline.decode(encoded, decodedCoordinates);

  EXPECT_FLOAT_EQ(41.87376, decodedCoordinates[0][0]);
  EXPECT_FLOAT_EQ(-87.67471, decodedCoordinates[0][1]);

  EXPECT_FLOAT_EQ(41.83029, decodedCoordinates[1][0]);
  EXPECT_FLOAT_EQ(-87.70492, decodedCoordinates[1][1]);

  EXPECT_FLOAT_EQ(41.81212, decodedCoordinates[2][0]);
  EXPECT_FLOAT_EQ(-87.65411, decodedCoordinates[2][1]);
}

void TripSimpleleEncodeDecode() {
  static const int buffer_size = 32;
  static const int num_coords = 3;
  char encoded[buffer_size] = {0};

  SimplePolyline polyline;

  float coordinates[num_coords][2] = {{41.87376, -87.67471}, {41.83029, -87.70492}, {41.81212, -87.65411}};
  polyline.encode(coordinates, num_coords, encoded);

  float decodedCoordinates[num_coords][2];
  polyline.decode(encoded, decodedCoordinates);

  EXPECT_FLOAT_EQ(41.87376, decodedCoordinates[0][0]);
  EXPECT_FLOAT_EQ(-87.67471, decodedCoordinates[0][1]);

  EXPECT_FLOAT_EQ(41.83029, decodedCoordinates[1][0]);
  EXPECT_FLOAT_EQ(-87.70492, decodedCoordinates[1][1]);

  EXPECT_FLOAT_EQ(41.81212, decodedCoordinates[2][0]);
  EXPECT_FLOAT_EQ(-87.65411, decodedCoordinates[2][1]);
}
