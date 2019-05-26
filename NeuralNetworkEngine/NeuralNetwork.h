#pragma once
#include "stdafx.h"
#include "Layer.h"

class NeuralNetwork
{
public:
    using ErrorFunc = double(*)(double, const std::vector<double> &);
    NeuralNetwork(const std::vector<Layer*> & layers, double rightAnswer, ErrorFunc errorFunc);
    ~NeuralNetwork();
    void AddLayer(Layer * layers);
    void Calculate();
    void ChangeWeights();
    const std::vector<double> & GetOutputSignals() const { return m_OutputSignals; }
    double GetError();

private:
    std::vector<Layer*> m_Layers;
    std::vector<double> m_OutputSignals;
    ErrorFunc m_ErrorFunc;
    double m_RightAnswer;
};

