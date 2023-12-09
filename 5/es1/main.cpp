#include <algorithm>
#include <boost/algorithm/string/trim.hpp>
#include <fstream>
#include <iostream>
#include <mutex>
#include <regex>
#include <string>
#include <unordered_map>
#include <vector>
using namespace std;
vector<string> splitStringBy(string s, string c) {
  regex rgx(c);
  sregex_token_iterator iter(s.begin(), s.end(), rgx, -1);
  sregex_token_iterator end;
  vector<string> fields(iter, end);
  return fields;
}
struct map_value {
  long long source;
  long long destination;
  long long length;
  map_value(long long s, long long d, long long l) {
    source = s;
    destination = d;
    length = l;
  }
};
vector<long long> getIntsFromStrings(vector<string> strings) {
  vector<long long> ints;
  for (long long i = 0LL; i < strings.size(); i++) {
    if (strings[i] != "") {
      ints.push_back(stoll(strings[i]));
    }
  }
  return ints;
}
std::unordered_map<long long, long long>
mapValues(const std::vector<long long> &seeds,
               const std::vector<map_value> &values) {
  std::unordered_map<long long, long long> mappedValues;

  for (long long seed : seeds) {
    bool found = false;
    for (const auto &mapping : values) {
      long long sourceStart = mapping.source;
      long long destStart = mapping.destination;
      long long length = mapping.length;

      if (sourceStart <= seed && seed < sourceStart + length) {
        long long destSoil = destStart + (seed - sourceStart);
        mappedValues[seed] = destSoil;
        found = true;
        break;
      }
    }
    if (!found) {
      // Seeds without a mapping remain unchanged
      mappedValues[seed] = seed;
    }
  }

  return mappedValues;
}
vector<long long> getValuesFromMap(unordered_map<long long, long long> map) {
  vector<long long> values;
  for (const auto &entry : map) {
    values.push_back(entry.second);
  }
  return values;
}
int main(int argc, char *argv[]) {
  string line;
  ifstream file("input.txt");
  int sum = 0;
  vector<string> lines;
  if (file.is_open()) {
    while (getline(file, line)) {
      lines.push_back(line);
    }
  }
  file.close();
  vector<long long> seeds;
  vector<string> tmp;
  vector<map_value> soil_map;
  vector<map_value> fertilizer_map;
  vector<map_value> water_map;
  vector<map_value> light_map;
  vector<map_value> temperature_map;
  vector<map_value> humidity_map;
  vector<map_value> location_map;
  // Get the seeds
  tmp = splitStringBy(lines[0], ":");
  boost::algorithm::trim(tmp[1]);
  seeds = getIntsFromStrings(splitStringBy(tmp[1], " "));
  // Get the soil values
  string temp_string = "";
  bool locked = false;
  for (int i = 0; i < lines.size(); i++) {
    if (lines[i] == "") {
      locked = false;
      temp_string = "";
    }
    // Get the soil map
    if (lines[i] == "seed-to-soil map:") {
      if (!locked) {
        locked = true;
        temp_string = lines[i];
      }
    } else if (locked == true && temp_string == "seed-to-soil map:") {
      vector<long long> values =
          getIntsFromStrings(splitStringBy(lines[i], " "));
      map_value soil_value = map_value(values[1], values[0], values[2]);
      soil_map.push_back(soil_value);
    }
    // Get the fertilizer map
    if (lines[i] == "soil-to-fertilizer map:") {
      if (!locked) {
        locked = true;
        temp_string = lines[i];
      }
    } else if (locked == true && temp_string == "soil-to-fertilizer map:") {
      vector<long long> values =
          getIntsFromStrings(splitStringBy(lines[i], " "));
      map_value soil_value = map_value(values[1], values[0], values[2]);
      fertilizer_map.push_back(soil_value);
    }
    // Get the water map
    if (lines[i] == "fertilizer-to-water map:") {
      if (!locked) {
        locked = true;
        temp_string = lines[i];
      }
    } else if (locked == true && temp_string == "fertilizer-to-water map:") {
      vector<long long> values =
          getIntsFromStrings(splitStringBy(lines[i], " "));
      map_value soil_value = map_value(values[1], values[0], values[2]);
      water_map.push_back(soil_value);
    }
    // Get the light map
    if (lines[i] == "water-to-light map:") {
      if (!locked) {
        locked = true;
        temp_string = lines[i];
      }
    } else if (locked == true && temp_string == "water-to-light map:") {
      vector<long long> values =
          getIntsFromStrings(splitStringBy(lines[i], " "));
      map_value soil_value = map_value(values[1], values[0], values[2]);
      light_map.push_back(soil_value);
    }
    // Get the temperature map
    if (lines[i] == "light-to-temperature map:") {
      if (!locked) {
        locked = true;
        temp_string = lines[i];
      }
    } else if (locked == true && temp_string == "light-to-temperature map:") {
      vector<long long> values =
          getIntsFromStrings(splitStringBy(lines[i], " "));
      map_value soil_value = map_value(values[1], values[0], values[2]);
      temperature_map.push_back(soil_value);
    }
    // Get the humidity map
    if (lines[i] == "temperature-to-humidity map:") {
      if (!locked) {
        locked = true;
        temp_string = lines[i];
      }
    } else if (locked == true &&
               temp_string == "temperature-to-humidity map:") {
      vector<long long> values =
          getIntsFromStrings(splitStringBy(lines[i], " "));
      map_value soil_value = map_value(values[1], values[0], values[2]);
      humidity_map.push_back(soil_value);
    }
    // Get the location map
    if (lines[i] == "humidity-to-location map:") {
      if (!locked) {
        locked = true;
        temp_string = lines[i];
      }
    } else if (locked == true && temp_string == "humidity-to-location map:") {
      vector<long long> values =
          getIntsFromStrings(splitStringBy(lines[i], " "));
      map_value soil_value = map_value(values[1], values[0], values[2]);
      location_map.push_back(soil_value);
    }
  }
  std::unordered_map<long long, long long> seedToSoil =
      mapValues(seeds, soil_map);
  vector<long long> soil = getValuesFromMap(seedToSoil);
  unordered_map<long long, long long> soilToFertilizer =
      mapValues(soil, fertilizer_map);
  vector<long long> fertilizer = getValuesFromMap(soilToFertilizer);
  unordered_map<long long, long long> fertilizerToWater =
      mapValues(fertilizer, water_map);
  vector<long long> water = getValuesFromMap(fertilizerToWater);
  unordered_map<long long, long long> waterToLight =
      mapValues(water, light_map);
  vector<long long> light = getValuesFromMap(waterToLight);
  unordered_map<long long, long long> lightToTemperature =
      mapValues(light, temperature_map);
  vector<long long> temperature = getValuesFromMap(lightToTemperature);
  unordered_map<long long, long long> temperatureToHumidity =
      mapValues(temperature, humidity_map);
  vector<long long> humidity = getValuesFromMap(temperatureToHumidity);
  unordered_map<long long, long long> humidityToLocation =
      mapValues(humidity, location_map);
  vector<long long> location = getValuesFromMap(humidityToLocation);
  for (const auto &entry : humidityToLocation) {
    std::cout << "humidity " << entry.first << " corresponds to location "
              << entry.second << std::endl;
  }
  // auto minElement = std::min_element(myVector.begin(), myVector.end());
  auto min = std::min_element(location.begin(), location.end());
  cout << "The minimum location is " << *min << endl;
}
