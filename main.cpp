#include <cpr/cpr.h>
#include "ext/json.hpp"

#include "lib/DataTypes.h"
#include <vector>
#include <ncurses.h>
#include "lib/Parser.h"
#include <thread>
#include <chrono>


void Refresh(const std::vector<Day>& data, const std::string& city_name) {
    clear();
    printw("%s", city_name.c_str());
    printw("\n");
    for (const auto& day : data) day.Print();
}


void ChangeDays(int& days, const int& amount) {
    if (days + amount < 1 or days + amount > 6) return;
    days += amount;
}


void ChangeCity(int& city, const int& n_cities, const int& amount) {
    if (city + amount < 0 or city + amount > n_cities - 1) return;
    city += amount;
}


int main(int argc, char** argv) {
    initscr();
    cbreak();
    noecho();

    std::ifstream ifs("config.json");
    auto config = nlohmann::json::parse(ifs);

    std::string ninjas_api_key = std::string(config["ninjas_api_key"]);
    int refresh_interval = config["refresh_interval"];
    int init_days = config["init_days"];
    int city = 0;
    int n_cities = config["cities"].size();

    std::vector<City> cities;
    for (int i = 0; i < config["cities"].size(); ++i) cities.emplace_back(std::string(config["cities"][i]), ninjas_api_key);

    std::vector<Day> data;

    std::thread updateThread([&](){
        while (true) {
            std::vector<Day> data = Parser::Parse(cities[0], init_days);
            Refresh(data, config["cities"][city]);
            std::this_thread::sleep_for(std::chrono::seconds(refresh_interval));
        }
    });

    int symbol;
    while ((symbol = getch()) != 27) {
        switch (symbol) {
            case 'N':
            case 'n':
                ChangeCity(city, n_cities, -1);
                data = Parser::Parse(cities[city], init_days);
                Refresh(data, config["cities"][city]);
                break;
            case 'P':
            case 'p':
                ChangeCity(city, n_cities, 1);
                data = Parser::Parse(cities[city], init_days);
                Refresh(data, config["cities"][city]);
                break;
            case '=':
            case '+':
                ChangeDays(init_days, 1);
                data = Parser::Parse(cities[city], init_days);
                Refresh(data, config["cities"][city]);
                break;
            case '-':
            case '_':
                ChangeDays(init_days, -1);
                data = Parser::Parse(cities[city], init_days);
                Refresh(data, config["cities"][city]);
                break;
            default:
                break;
        }
    }

    endwin();
    return 0;
}
