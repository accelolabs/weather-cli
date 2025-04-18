#include "Parser.h"

std::vector<Day> Parser::Parse(const City &city, const int &n_days) {
    auto response = cpr::Get(
            cpr::Url{"https://api.open-meteo.com/v1/forecast?"
                     "latitude=" + std::to_string(city.GetLatitude()) + "&"
                     "longitude=" + std::to_string(city.GetLongitude()) + "&"
                     "forecast_days=" + std::to_string(n_days + 1) + "&"
                     "hourly="
                     "weathercode,"
                     "temperature_2m,"
                     "relativehumidity_2m,"
                     "windspeed_10m,"
                     "winddirection_10m&"
                     "timezone=auto"
            });

    auto json = nlohmann::json::parse(response.text);

    std::vector<Day> result;

    int count = 6;
    for (int i = 0; i < n_days; ++i) {
        result.emplace_back();

        for (int j = 0; j < 4; j++) {
            if (j == 0) result[i].date = std::string(json["hourly"]["time"][count]).substr(0, 10);
            result[i].parts.emplace_back(
                    std::string(json["hourly"]["time"][count + j * 6]).substr(11, 5),
                    int(json["hourly"]["weathercode"][count + j * 6]),
                    int(json["hourly"]["temperature_2m"][count + j * 6]),
                    int(json["hourly"]["relativehumidity_2m"][count + j * 6]),
                    int(json["hourly"]["winddirection_10m"][count + j * 6]),
                    double(json["hourly"]["windspeed_10m"][count + j * 6])
            );
        }
        count += 24;
    }

    return result;
}
