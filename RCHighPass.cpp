#include "RCHighPass.h"

RCHighPass::RCHighPass(float sampleRate, float cutoffFrequency,
    float r_source, float r_series, float r_load)
    : sampleRate(sampleRate),
    cutoff(cutoffFrequency),
    r_source(r_source),
    r_series(r_series),
    r_load(r_load),
    prevInput(0.0f),
    prevOutput(0.0f)
{
    setCutoff(cutoffFrequency);
}

void RCHighPass::setCutoff(float cutoffFrequency)
{
    if (cutoffFrequency <= 0.0f)
        cutoffFrequency = 1.0f;  // Avoid invalid cutoff

    cutoff = cutoffFrequency;

    // Calculate capacitance C = 1 / (2 * pi * R_load * cutoff)
    C = 1.0f / (2.0f * float(M_PI) * r_load * cutoff);

    updateCoefficients();
}

void RCHighPass::prepare(float newSampleRate)
{
    sampleRate = newSampleRate;
    updateCoefficients();
}

void RCHighPass::updateCoefficients()
{
    // RC constant
    float RC = 1.0f / (2.0f * float(M_PI) * cutoff);

    // Calculate alpha for simple one-pole high-pass filter
    float dt = 1.0f / sampleRate;
    alpha = RC / (RC + dt);
}

float RCHighPass::processSample(float inputSample)
{
    // Simple one-pole high-pass filter formula:
    float output = alpha * (prevOutput + inputSample - prevInput);
    prevInput = inputSample;
    prevOutput = output;
    return output;
}
