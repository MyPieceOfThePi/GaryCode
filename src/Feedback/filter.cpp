#include "main.h"

//Definition of the constructor for all filters. Overload constructors are possible
Filter::Filter(double _weight){
    weight=_weight;
}
//Destructor
Filter::~Filter(){}

//Definition of the virtual member compute in the derived class EMA, which filters the input value
//as defined by the EMA algoritm
double EMA::compute(double sensorVal){
    sensor=sensorVal;
    oldValue=(weight*sensor)+((1-weight)*oldValue);
    return oldValue;
}
double SMA::compute(double sensorVal){
    int length = sizeof(values) / sizeof(double);
    double sum = 0;
    for(double i:values){
        sum+=i;
    }
    for(int i = 1; i < length; i++){
        values[i-1]=values[i];
    }
    values[length]=sensorVal;
    return sum/length;
}