#pragma once

//Abstract base class Filter with virtual member compute
class Filter{
    public:
    Filter(double weight_);
    ~Filter();
    virtual double compute(double sensorValue) = 0;
    protected:
    double oldValue;
    double sensor;
    double weight;
};

//Derived class EMA defines compute as according to the EMA alogorithm
class EMA: public Filter{
    public:
    using Filter::Filter;
    double compute(double sensorValue);
};

class SMA: public Filter{
    public:
    using Filter::Filter;
    double values[10];
    double compute(double sensorValue);
};