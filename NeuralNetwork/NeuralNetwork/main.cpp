// NeuralNetwork.cpp : Defines the entry point for the console application.

#include "stdafx.h"
#include "Common.h"
#include "NeuralNetwork.h"


int main()
{
    const std::vector<std::string> inputData = {
        "001011001001001", //1
        "111101010100111", //2
        "111001011001111", //3
        "101101111001001", //4
        "111100111001111", //5
        "111100111101111", //6
        "111001001001001", //7
        "111101111101111", //8
        "111101111001111", //9
        "111101101101111", //0
    };

    const std::vector<std::vector<double>> signals = {
        { 0.0, 0.0, 1.0, 0.0, 1.0, 1.0, 0.0, 0.0, 1.0, 0.0, 0.0, 1.0, 0.0, 0.0, 1.0 }, //1
        { 1.0, 1.0, 1.0, 1.0, 0.0, 1.0, 0.0, 1.0, 0.0, 1.0, 0.0, 0.0, 1.0, 1.0, 1.0 }, //2
        { 1.0, 1.0, 1.0, 0.0, 0.0, 1.0, 0.0, 1.0, 1.0, 0.0, 0.0, 1.0, 1.0, 1.0, 1.0 }, //3
    };
    const std::vector<std::vector<double>> weights = {
        { 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 },
        { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
        { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
    };

    std::vector<Neuron*> first;
    std::vector<Neuron*> second;
    std::vector<Neuron*> thirt;
    std::vector<double> tmpSignals;
    std::vector<double> tmpWeights;
    for (size_t i = 0; i < signals[0].size(); i++)
    {
        tmpSignals.push_back(signals[0][i]);
        tmpWeights.push_back(weights[0][i]);
        first.push_back(new Neuron(tmpSignals, tmpWeights, 0.23, LinearFunction));
        second.push_back(new Neuron(std::vector<double>(), weights[0], 0.23, Sigmoid));
        thirt.push_back(new Neuron(std::vector<double>(), weights[0], 0.23, Sigmoid));
        tmpSignals.clear();
        tmpWeights.clear();
    }

    std::vector<Layer*> tmpLayers;
    tmpLayers.push_back(new Layer(first));
    tmpLayers.push_back(new Layer(second));
    tmpLayers.push_back(new Layer(thirt));

    double rightAnswer = 1;
    NeuralNetwork network(tmpLayers, rightAnswer, MSE);

    try
    {
        for (size_t i = 0; i < 100; i++)
        {
            network.Calculate();
            const auto error = network.GetError();
            const auto & answer = network.GetOutputSignals();
            network.ChangeWeights();
        }
    }
    catch (const std::logic_error & e)
    {
        std::cout << e.what() << std::endl;
    }

    return 0;
}

