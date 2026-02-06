#include "Length.h"
#include <iostream>

Length::Length() {
    // base = meter
    multipliers["m"] = 1.0;
    multipliers["km"] = 1000.0;
    multipliers["cm"] = 0.01;
    multipliers["mm"] = 0.001;
    multipliers["mi"] = 1609.34;
    multipliers["ft"] = 0.3048;
    multipliers["in"] = 0.0254;
}

double Length::toBase(double value, std::string unit){
    if (multipliers.count(unit)) {
        return value * multipliers[unit];
    }
    std::cerr << "Error: Unit not found\n";
    return 0.0; 
}

double Length::fromBase(double baseValue, std::string targetUnit) {
    if (multipliers.count(targetUnit)) {
        return baseValue / multipliers[targetUnit];
    }
    std::cerr << "Error: Unit not found\n";
    return 0.0; // Error
}