#pragma once
#include "stdafx.h"
#include "Neuron.h"

class Layer
{
public:
    Layer(const std::vector<Neuron*> & neurons);
    ~Layer();
    void AddNeuron(Neuron * neuron);
    void SetInputSignals(const std::vector<double> & signals);
    void ChangeWeights();
    void Calculate();
    const std::vector<double> & GetOutputSignals() const { return m_OutputSignals; }
private:
    std::vector<Neuron*> m_Neurons;
    std::vector<double> m_OutputSignals;
};

