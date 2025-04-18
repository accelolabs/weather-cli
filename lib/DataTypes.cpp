#include "DataTypes.h"


City::City(const std::string &city_name, const std::string &api_key) {
    for (char c : city_name) {
        if (c == ' ') {
            name.append("%20");
        } else {
            name.push_back(c);
        }
    }

    auto response = cpr::Get(
            cpr::Url{"https://api.api-ninjas.com/v1/city?name=" + name},
            cpr::Header{{"X-Api-Key", api_key}}
    );

    auto json = nlohmann::json::parse(response.text);
    latitude = json[0]["latitude"];
    longitude = json[0]["longitude"];
}


void WeatherCode::PrintCell() const {
    switch (code) {
        case 0:
            printw(" Clear sky        ");
            break;
        case 1:
            printw(" Mainly clear     ");
            break;
        case 2:
            printw(" Partly cloudy    ");
            break;
        case 3:
            printw(" Overcast         ");
            break;
        case 45:
        case 48:
            printw(" Fog              ");
            break;
        case 51:
        case 53:
        case 55:
            printw(" Drizzle          ");
            break;
        case 56:
        case 57:
            printw(" Freezing Drizzle ");
            break;
        case 61:
        case 63:
        case 65:
            printw(" Rain             ");
            break;
        case 66:
        case 67:
            printw(" Freezing Rain    ");
            break;
        case 71:
        case 73:
        case 75:
            printw(" Snow fall        ");
            break;
        case 77:
            printw(" Snow grains      ");
            break;
        case 80:
        case 81:
        case 82:
            printw(" Rain showers     ");
            break;
        case 85:
        case 86:
            printw(" Snow showers     ");
            break;
        case 95:
        case 96:
        case 99:
            printw(" Thunderstorm     ");
            break;
        default:
            printw("                  ");
    }
}


void Temperature::PrintCell() const {
    std::string deg = std::to_string(degrees);
    printw(" ");
    printw("%3s", deg.c_str());
    printw(" °C          ");
}

void Humidity::PrintCell() const {
    std::string deg = std::to_string(humidity_per);
    printw(" ");
    printw("%3s", deg.c_str());
    printw("%%             ");
}

void Wind::PrintCell() const {

    printw(" ");
    if (degrees <= 45 or degrees > 315) {
        printw("N");
    } else if (degrees <= 135) {
        printw("E");
    } else if (degrees <= 225) {
        printw("S");
    } else {
        printw("W");
    }

    char buf[20];
    std::sprintf(buf, "%.1f", speed);

    printw(" ");
    printw("%5s", buf);
    printw(" km/h     ");
}

void Day::Print() const {
    printw("| ");
    printw("%s", date.c_str());
    printw(" |===============================================================\n");

    for (int i = 0; i < 4; ++i) {
        printw("|      ");
        printw("%s", parts[i].time.c_str());
        printw("       ");
    }
    printw("|\n");

    for (int i = 0; i < 4; ++i) {
        printw("|");
        parts[i].weather_code.PrintCell();
    }
    printw("|\n");
    for (int i = 0; i < 4; ++i) {
        printw("|");
        parts[i].temperature.PrintCell();
    }
    printw("|\n");
    for (int i = 0; i < 4; ++i) {
        printw("|");
        parts[i].humidity.PrintCell();
    }
    printw("|\n");
    for (int i = 0; i < 4; ++i) {
        printw("|");
        parts[i].wind.PrintCell();
    }
    printw("|\n\n");

    refresh();
}
