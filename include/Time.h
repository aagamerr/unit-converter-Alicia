#ifndef TIME_H
#define TIME_H

#include "Converter.h"

#include <iostream>
#include <string>
#include <map>

class Time : public Converter {
private:
    std::map<std::string, double> multipliers;

public:
    Time();

    double toBase(double value, std::string unit) override;

    double fromBase(double baseValue, std::string targetUnit) override;
};

#endif