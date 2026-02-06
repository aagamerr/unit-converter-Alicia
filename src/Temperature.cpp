#include "Temperature.h"
#include <iostream>

Temperature::Temperature() {
    // base = Celcius
    multipliers["Farenheit"] = 1.8;
    multipliers["Reamur"] = 0.8;
    multipliers["Kelvin"] = 1;
}

double Temperature::toBase(double value, std::string unit){
    if (multipliers.count(unit)) {
        if(unit == "Farenheit"){
            value -= 32;
        }else if(unit == "Kelvin"){
            value -= 273;
        }
        return value * multipliers[unit];
    }
    std::cerr << "Error: Unit not found\n";
    return 0.0; 
}

double Temperature::fromBase(double baseValue, std::string targetUnit) {
    double ans = 0;
    if (multipliers.count(targetUnit)) {
        ans = baseValue / multipliers[targetUnit];
    }
    if (targetUnit == "Farenheit"){
        ans += 32;
    } else if (targetUnit == "Kelvin"){
        ans += 273;
    }
    return ans;
    std::cerr << "Error: Unit not found\n";
    return 0.0; 
}