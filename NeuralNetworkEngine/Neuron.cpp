#include "Neuron.h"

Neuron::Neuron(const std::vector<double>& inputSignals, const std::vector<double>& weights, double weightStep, Activation activation)
{
    m_InputSignals.assign(inputSignals.begin(), inputSignals.end());
    m_Weights.assign(weights.begin(), weights.end());
    m_WeightStep = weightStep;
    m_Activation = activation;
    m_OutputSignal = 0.0;
}

void Neuron::SetInputSignals(const std::vector<double>& inputSignals)
{
    if (inputSignals.size() != m_Weights.size())
    {
        throw std::logic_error("Incorrect input params");
    }

    m_InputSignals.assign(inputSignals.begin(), inputSignals.end());
}

void Neuron::SetWeights(const std::vector<double>& weights)
{
    if (m_InputSignals.size() != m_Weights.size())
    {
        throw std::logic_error("Incorrect input params");
    }

    m_Weights.assign(weights.begin(), weights.end());
}

void Neuron::ChangeWeights()
{
    for (auto & weight : m_Weights)
    {
        weight += m_WeightStep;
    }
}

void Neuron::Calculate()
{
    Summarize();
    Normalize();
}

void Neuron::Summarize()
{
    if (m_InputSignals.empty() || m_Weights.empty() || m_InputSignals.size() != m_Weights.size())
    {
        throw std::logic_error("Icorrect input params");
    }

    for (size_t i = 0; i < m_InputSignals.size(); i++)
    {
        m_OutputSignal += (m_InputSignals[i] * m_Weights[i]);
    }
}

void Neuron::Normalize()
{
    if (m_Activation == nullptr)
    {
        throw std::logic_error("Activation functionis is null");
    }

    m_Activation(m_OutputSignal);
}
