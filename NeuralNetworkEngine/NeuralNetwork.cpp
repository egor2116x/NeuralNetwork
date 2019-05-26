#include "NeuralNetwork.h"
#include "Common.h"

NeuralNetwork::NeuralNetwork(const std::vector<Layer*> & layers, double rightAnswer, ErrorFunc errorFunc)
{
    m_Layers.assign(layers.begin(), layers.end());
    m_RightAnswer = rightAnswer;
    m_ErrorFunc = errorFunc;
}

NeuralNetwork::~NeuralNetwork()
{
    for (auto & layer : m_Layers)
    {
        delete layer;
    }
}

void NeuralNetwork::AddLayer(Layer * layer)
{
    if (layer == nullptr)
    {
        throw std::logic_error("Layer is null");
    }
    m_Layers.push_back(layer);
}

void NeuralNetwork::Calculate()
{
    if (m_Layers.size() != MAX_LAYERS)
    {
        throw std::logic_error("Incorrect input params");
    }

    for (size_t i = 0; i < m_Layers.size(); i++)
    {
        m_Layers[i]->Calculate();
        auto & outputSignal = m_Layers[0]->GetOutputSignals();
        if (i != MAX_LAYERS - 1)
        {
            m_Layers[i + 1]->SetInputSignals(outputSignal);
        }
    }

    auto & outputSignals = m_Layers[MAX_LAYERS - 1]->GetOutputSignals();
    m_OutputSignals.assign(outputSignals.begin(), outputSignals.end());
}

void NeuralNetwork::ChangeWeights()
{
    for (auto & layer : m_Layers)
    {
        layer->ChangeWeights();
    }
}

double NeuralNetwork::GetError()
{
    if (m_ErrorFunc == nullptr)
    {
        throw std::logic_error("Error function is empty");
    }

    return m_ErrorFunc(m_RightAnswer, m_OutputSignals);
}
