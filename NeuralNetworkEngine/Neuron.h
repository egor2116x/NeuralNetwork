#pragma once
#include "stdafx.h"

class Neuron
{
public:
    using Activation = void(*)(double & outputSignal);
    Neuron(const std::vector<double> & inputSignals, const std::vector<double> & weights, double weightStep, Activation activation);

    void SetInputSignals(const std::vector<double> & inputSignals);
    const std::vector<double> & GetInputSignals() const { return m_InputSignals; }

    void SetWeights(const std::vector<double> & weights);
    const std::vector<double> & GetWeights() const { return m_Weights; }

    void ChangeWeights();
    void Calculate();
    double GetOutputSignal() const { return m_OutputSignal; }
private:
    void Summarize();
    void Normalize();
private:
    std::vector<double> m_InputSignals;
    std::vector<double> m_Weights;
    double m_WeightStep;
    double m_OutputSignal;
    Activation m_Activation;
};

