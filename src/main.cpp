#include "Converter.h"
#include "Length.h"
#include "Time.h"
#include "Temperature.h"

#include <iostream>
#include <string>

int main(){
    std::string input;
    std::cout << "Enter value in km: ";
    
    std::cin >> input;
    double val = std::stod(input);

    Length myconverter;
    double baseVal = myconverter.toBase(val, "km");
    double result = myconverter.fromBase(baseVal, "ft");

    std::cout << "Value in ft : " << result << std::endl;

    std::string input;
    std::cout << "Enter value in hour: ";
    
    std::cin >> input;
    double val = std::stod(input);

    Time time_converter;
    double baseVal = time_converter.toBase(val, "hour");
    double result =time_converter.fromBase(baseVal, "sec");

    std::cout << "Value in sec : " << result << std::endl;

    std::string input;
    std::cout << "Enter value in Celcius: ";
    
    std::cin >> input;
    double val = std::stod(input);

    Temperature temp_converter;
    double baseVal = temp_converter.toBase(val, "Celcius");
    double result = temp_converter.fromBase(baseVal, "Farenheit");

    std::cout << "Value in Farenheit : " << result << std::endl;


    return 0;
}