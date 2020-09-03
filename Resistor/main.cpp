#include <iostream>
#include <map>
#include <cmath>
#include "resistor.cpp"
double oPlus(double a, double b){
        return 1/((1/a)+(1/b));
    }
    double Plus(double a, double b){
        return a+b;
    }
int main(int argc, char** argv) {


    int series = 24;
    double value = 15.6;
    double tolerance = .02;
    auto yeet = reststor.find(series,value,tolerance,Plus);
    for (auto const& val: yeet) {
        std::cout << val.second.r1 << " oPlused with " << val.second.r2 << " is " << val.second.out << " and is " << val.first << " away from " << value << std::endl; 
    }
    return 0;
}