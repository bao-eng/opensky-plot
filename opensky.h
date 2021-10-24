#pragma once
#include <vector>
#include <string>

// https://openskynetwork.github.io/opensky-api/rest.html
struct state {
  std::string icao24;    // 0 Unique ICAO 24-bit address of the transponder in hex
                    // string representation.
  std::string callsign;  // 1 Callsign of the vehicle (8 chars). Can be null if no
                    // callsign has been received.
  std::string
      origin_country;  // 2 Country name inferred from the ICAO 24-bit address.
  int time_position;   // 3 Unix timestamp (seconds) for the last position
                       // update. Can be null if no position report was received
                       // by OpenSky within the past 15s.
  int last_contact;    // 4 Unix timestamp (seconds) for the last update in
                       // general. This field is updated for any new, valid
                       // message received from the transponder.
  float longitude;     // 5 WGS-84 longitude in decimal degrees. Can be null.
  float latitude;      // 6 WGS-84 latitude in decimal degrees. Can be null.
  float baro_altitude;  // 7 Barometric altitude in meters. Can be null.
  bool on_ground;       // 8 Boolean value which indicates if the position was
                        // retrieved from a surface position report.
  float velocity;       // 9 Velocity over ground in m/s. Can be null.
  float true_track;     // 10 True track in decimal degrees clockwise from north
                        // (north=0°). Can be null.
  float vertical_rate;  // 11 Vertical rate in m/s. A positive value indicates
                        // that the airplane is climbing, a negative value
                        // indicates that it descends. Can be null.
  std::vector<int> sensors;  // 12 IDs of the receivers which contributed to this
                        // state vector. Is null if no filtering for sensor was
                        // used in the request.
  float geo_altitude;   // 13 Geometric altitude in meters. Can be null.
  std::string squawk;        // 14 The transponder code aka Squawk. Can be null.
  bool spi;  // 15 Whether flight status indicates special purpose indicator.
  int position_source;  // 16 Origin of this state’s position: 0 = ADS-B, 1 =
                        // ASTERIX, 2 = MLAT
};