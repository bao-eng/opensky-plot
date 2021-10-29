#include <matplot/matplot.h>

#include <cmath>
#include <ctime>
#include <fstream>
#include <iostream>

#include "json.hpp"

using json = nlohmann::json;
using namespace matplot;

int main() {
  std::ifstream i("../opensky.json");
  json j;
  i >> j;

  auto time = j["time"].get<std::time_t>();
  std::ostringstream oss;
  oss << std::put_time(std::gmtime(&time), "%c %Z");
  auto time_str = oss.str();

  std::unordered_map<std::string,
                     std::pair<std::vector<double>, std::vector<double>>>
      fleets;
  std::unordered_map<std::string, size_t> countries;

  for (json &c : j["states"]) {
    if (!c[5].is_null() && !c[6].is_null()) {
      auto origin_country = c[2].get<std::string>();
      fleets[origin_country].second.push_back(c[5].get<double>());
      fleets[origin_country].first.push_back(c[6].get<double>());
      countries[origin_country]++;
    }
  }

  std::vector<std::pair<size_t, std::string>> fleet_chart;
  std::for_each(countries.begin(), countries.end(),
                [&](const std::pair<std::string, size_t> &i) {
                  fleet_chart.push_back({i.second, i.first});
                });
  std::sort(fleet_chart.rbegin(), fleet_chart.rend());

  auto f = figure(true);
  figure(f);

  // std::vector<matplot::line_handle> scatters;
  for (auto i = fleet_chart.begin(); i < fleet_chart.begin() + 5; i++) {
    auto p =
        geoscatter(fleets.at(i->second).first, fleets.at(i->second).second);
    p->marker_style(line_spec::marker_style::point);
    p->marker_size(5);
    p->display_name(i->second + "(" + std::to_string(i->first) + ")");
    // scatters.push_back(p);
  }

  color_array terrain = {0.f, 0.71f, 0.65f, 0.59f};
  geoplot()->color(terrain).display_name("terrain");

  color_array blue_water = {0.f, 0.4f, 0.61f, 0.76f};
  gca()->color(blue_water);
  gca()->title(time_str);

  legend();

  f->show();
  return 0;
}