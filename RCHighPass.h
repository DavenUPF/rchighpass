#pragma once

#include <cmath>

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

class RCHighPass
{
public:
    RCHighPass(float sampleRate, float cutoffFrequency, float r_source = 75.0f,
        float r_series = 1000.0f, float r_load = 10000.0f);

    void setCutoff(float cutoffFrequency);
    void prepare(float sampleRate);
    float processSample(float inputSample);

private:
    float sampleRate;
    float cutoff;
    float r_source;
    float r_series;
    float r_load;

    float C;  // Capacitance value computed from cutoff
    float alpha;  // Filter coefficient for processing

    float prevInput = 0.0f;
    float prevOutput = 0.0f;

    void updateCoefficients();
};


