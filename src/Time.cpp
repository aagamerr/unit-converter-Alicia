#include "Time.h"
#include <iostream>

Time::Time() {
    // base = second
    multipliers["hour"] = 1/3600;
    multipliers["min"] = 1/60;
    multipliers["ms"] = 1000;
}

double Time::toBase(double value, std::string unit){
    if (multipliers.count(unit)) {
        return value * multipliers[unit];
    }
    std::cerr << "Error: Unit not found\n";
    return 0.0; 
}

double Time::fromBase(double baseValue, std::string targetUnit) {
    if (multipliers.count(targetUnit)) {
        return baseValue / multipliers[targetUnit];
    }
    std::cerr << "Error: Unit not found\n";
    return 0.0; // Error
}