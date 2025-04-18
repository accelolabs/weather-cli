#ifndef MAIN10_DATATYPES_H
#define MAIN10_DATATYPES_H

#include <cpr/cpr.h>
#include <ncurses.h>
#include "../ext/json.hpp"


class City {
private:
    std::string name;
    double latitude = 0.0;
    double longitude = 0.0;
public:
    explicit City(const std::string& city_name, const std::string& api_key);

    double GetLatitude() const {return latitude;}
    double GetLongitude() const {return longitude;}
};


class WeatherCode {
private:
    int code = 0;
public:
    explicit WeatherCode(const int& c) : code(c) {};

    void PrintCell() const;
};


class Temperature {
private:
    int degrees = 0;
public:
    explicit Temperature(const int& deg) : degrees(deg) {};

    void PrintCell() const;
};


class Humidity {
private:
    int humidity_per = 0;
public:
    explicit Humidity(const int& hum) : humidity_per(hum) {};

    void PrintCell() const;
};


class Wind {
private:
    int degrees = 0;
    double speed = 0;
public:
    explicit Wind(const int& deg, const double& spe) : degrees(deg), speed(spe) {};

    void PrintCell() const;
};


class DayPart {
public:
    std::string time;
    WeatherCode weather_code;
    Temperature temperature;
    Humidity humidity;
    Wind wind;

    explicit DayPart(
            std::string time,
            const int& code,
            const int& temperature,
            const int& humidity,
            const int& degrees,
            const double& speed) :
            time(std::move(time)),
            weather_code(code),
            temperature(temperature),
            humidity(humidity),
            wind(degrees, speed)
    {};
};


class Day {
public:
    std::string date;
    std::vector<DayPart> parts;

    void Print() const;
};


#endif //MAIN10_DATATYPES_H