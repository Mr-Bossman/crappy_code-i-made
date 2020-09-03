#include <iostream>
#include <map>
#include <cmath>
class reststor { 
    public:
    struct doub{
        double r1;
        double r2;
        double out;
    };
    //returns nth value in the series
    double Eseries(int series, int n){
        return std::round(10*std::pow(10,(double)n/(double)series))/10;
    }
    //retuns the standard tolerance 
    double Etolernace(int &series){
        switch (series){
            case 3:
            return 40;
            case 6:
            return 20;
            case 12:
            return 10;
            case 24:
            return 5;
            case 48:
            return 2;
            case 96:
            return 1;
            case 192:
            return 0.5;
        } 
    }
    std::map<double,doub> find(int &series,double &value,double &tolerance,double (*operation)(double,double)){
        std::map<double,doub> array;
        for(int r1 = 0; r1 < series;r1++){
            for(int r2 = 0; r2 < series;r2++){
                double r1val = Eseries(series,r1);
                double r2val = Eseries(series,r2);
                double out = operation(r1val,r2val);
                double tol = out/value;
                if(tol < 1+tolerance && tol > 1-tolerance) array[tol] = {r1val,r2val,out};
            } 
        }
        return array;
    }
}reststor;