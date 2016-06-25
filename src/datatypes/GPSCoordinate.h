//
// Created by joshuabaker2 on 24/06/16.
//

#ifndef PROJECT_GPSCOORDINATE_H
#define PROJECT_GPSCOORDINATE_H


class GPSCoordinate {
 public:
  GPSCoordinate() {
    is_empty_ = true;
  };

  GPSCoordinate(float latitude, float longitude) : latitude_(latitude), longitude_(longitude) {
    is_empty_ = false;
  };

  void SetCoordinates(float latitude, float longitude) {
    latitude_ = latitude;
    longitude_ = longitude;
    is_empty_ = false;
  };

  bool isEmpty() {}
  float latitude() { return latitude_; };
  float longitude() { return longitude_; };

 private:
  float latitude_, longitude_;
  bool is_empty_ = true;
};


#endif //PROJECT_GPSCOORDINATE_H
