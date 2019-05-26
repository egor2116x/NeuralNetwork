#include "Layer.h"

Layer::Layer(const std::vector<Neuron*> & neurons)
{
    for (const auto & neuron : neurons)
    {
        m_Neurons.push_back(neuron);
    }
}

Layer::~Layer()
{
    for (auto & neuron : m_Neurons)
    {
        delete neuron;
    }
}

void Layer::AddNeuron(Neuron * neuron)
{
    if (neuron == nullptr)
    {
        throw std::logic_error("Neuron is null");
    }

    m_Neurons.push_back(neuron);
}

void Layer::SetInputSignals(const std::vector<double> & signals)
{
    if (m_Neurons.size() != signals.size())
    {
        throw std::logic_error("Incorrect input params");
    }

    for (size_t i = 0; i < m_Neurons.size(); i++)
    {
        m_Neurons[i]->SetInputSignals(signals);
    }
}

void Layer::ChangeWeights()
{
    for (auto & neuron : m_Neurons)
    {
        neuron->ChangeWeights();
    }
}

void Layer::Calculate()
{
    for (auto & neuron : m_Neurons)
    {
        neuron->Calculate();
        m_OutputSignals.push_back(neuron->GetOutputSignal());
    }
}
