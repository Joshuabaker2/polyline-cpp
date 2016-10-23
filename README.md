# polyline-cpp
A polyline encoder/decoder for GPS coordinates. No dynamic memory allocation, so it's safe for embedded programming!

To see how polyline encoding/decoding works, check out Google's [Interactive Polyline Encoder Utility](https://developers.google.com/maps/documentation/utilities/polylineutility).
## How To Build
This project uses CMake to build. For a quick start, simply run `./setup.sh` in the root directory.

## How To Use
There are two different classes made available - Polyline and SimplePolyline. Polyline uses a GPSCoordinate class
(included in src/datatypes) whereas SimplePolyline just uses arrays of floats.

### Polyline Class
To use the Polyline class to encode an array of GPSCoordinates into a char array:

```
  int buffer_size = 10;
  float latitude = 41.75368;
  float longitude = -87.97330;
  char encoded[buffer_size] = {0};
  GPSCoordinate gps_coordinates[num_coords];
  gps_coordinates[0].set_coordinates(latitude, longitude);

  Polyline polyline();  // we have a default floating point precision of 5 decimal places
  polyline.encode(gps_coordinates, num_coords, encoded);
```

And your polyline will be in the `encoded` char buffer array.

And to decode a char array into an array of GPSCoordinates:

```
  GPSCoordinate decoded_coordinates[buffer_size];
  polyline.decode(encoded, decoded_coordinates);
```

And to access the first GPSCoordinate's latitude/longitude:

```
  float latitude = gps_coordinates[0].latitude();
  float longitude = gps_coordinates[0].longitude();
```

We can also set the precision if we want higher/lower decimal precision when we initialize the class by:

```
  int precision = 3;    // default precision is 5
  Polyline polyline(precision);
```

### SimplePolyline Class
To use the SimplePolyline class to encode an array of arrays of floats into a char array:

```
  static const int buffer_size = 32;
  static const int num_coords = 3;
  char encoded[buffer_size] = {0};
  float coordinates[num_coords][2] = {
    {41.87376, -87.67471},
    {41.83029, -87.70492},
    {41.81212, -87.65411}
  };
  SimplePolyline polyline();
  polyline.encode(coordinates, num_coords, encoded);
```

And your polyline will be in the `encoded` char buffer array.

And to decode a char array into an array of GPSCoordinates:

```
  float decoded_coordinates[num_coords][2];
  int num_decoded_coords = polyline.decode(encoded, decoded_coordinates);
```

And to access the first gps coordinates's latitude/longitude:

```
  float latitude = gps_coordinates[0][0];
  float longitude = gps_coordinates[0][1];
```

We can also set the precision if we want higher/lower decimal precision when we initialize the class by:

```
  int precision = 3;    // default precision is 5
  Polyline polyline(precision);
```


## Compatible Platforms
Tested on a 64bit Linux machine, 64bit OS X.

There has been preliminary testing on an Arduino Mega, but the test cases aren't quite complete and more rigorous testing needs to occur.


## How To Test
After running `./setup.sh`, (which also runs the tests) go to the `build` directory and run `./polyline_test`.