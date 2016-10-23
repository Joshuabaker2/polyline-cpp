// Copyright 2016, Josh Baker.
// All rights reserved.
//
// Author: joshuabaker2@gmail.com (Josh Baker)
//
// The GPSCoordinate Class for Polyline

#ifndef DATATYPES_GPSCOORDINATE_H_
#define DATATYPES_GPSCOORDINATE_H_

class GPSCoordinate {
 public:
  GPSCoordinate() {
    is_empty_ = true;
  }

  GPSCoordinate(float latitude, float longitude) : latitude_(latitude), longitude_(longitude) {
    is_empty_ = false;
  }

  void set_coordinates(float latitude, float longitude) {
    latitude_ = latitude;
    longitude_ = longitude;
    is_empty_ = false;
  }

  bool is_empty() { return is_empty_; }
  float latitude() { return latitude_; }
  float longitude() { return longitude_; }

 private:
  float latitude_, longitude_;
  bool is_empty_ = true;
};

#endif  // DATATYPES_GPSCOORDINATE_H_
