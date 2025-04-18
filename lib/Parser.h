#ifndef MAIN10_PARSER_H
#define MAIN10_PARSER_H

#include "DataTypes.h"
#include "../ext/json.hpp"

class Parser {
public:
    static std::vector<Day> Parse (const City& city, const int& n_days);
};


#endif //MAIN10_PARSER_H
