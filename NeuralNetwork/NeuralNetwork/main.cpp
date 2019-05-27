// NeuralNetwork.cpp : Defines the entry point for the console application.

#include "stdafx.h"

// defines
const size_t EPOCH_MAX = 100;
const double WEIGHT_STEP = 0.1;
const double ERROR_LIMIT = 0.2;

double GetRandom()
{
    return double(rand()) / RAND_MAX;
}

const std::vector<double> signals1 = { 0.0, 0.0, 1.0, 0.0, 1.0, 1.0, 0.0, 0.0, 1.0, 0.0, 0.0, 1.0, 0.0, 0.0, 1.0 }; //1
const std::vector<double> signals2 = { 1.0, 1.0, 1.0, 1.0, 0.0, 1.0, 0.0, 1.0, 0.0, 1.0, 0.0, 0.0, 1.0, 1.0, 1.0 }; //2
const std::vector<double> signals3 = { 1.0, 1.0, 1.0, 0.0, 0.0, 1.0, 1.0, 1.0, 1.0, 0.0, 0.0, 1.0, 1.0, 1.0, 1.0 }; //3
const std::vector<double> signals4 = { 1.0, 0.0, 1.0, 1.0, 0.0, 1.0, 1.0, 1.0, 1.0, 0.0, 0.0, 1.0, 0.0, 0.0, 1.0 }; //4
const std::vector<double> signals5 = { 1.0, 1.0, 1.0, 1.0, 0.0, 0.0, 1.0, 1.0, 1.0, 0.0, 0.0, 1.0, 1.0, 1.0, 1.0 }; //5

const std::vector<double> weights1 = { GetRandom(), GetRandom(), GetRandom(), GetRandom(), GetRandom(), GetRandom(), GetRandom(), GetRandom(), GetRandom(), GetRandom(), GetRandom(), GetRandom(), GetRandom(), GetRandom(), GetRandom() };
const std::vector<double> weights2 = { GetRandom(), GetRandom(), GetRandom(), GetRandom(), GetRandom(), GetRandom(), GetRandom(), GetRandom(), GetRandom(), GetRandom(), GetRandom(), GetRandom(), GetRandom(), GetRandom(), GetRandom() };
const std::vector<double> weights3 = { GetRandom(), GetRandom(), GetRandom(), GetRandom(), GetRandom(), GetRandom(), GetRandom(), GetRandom(), GetRandom(), GetRandom(), GetRandom(), GetRandom(), GetRandom(), GetRandom(), GetRandom() };
const std::vector<double> weights4 = { GetRandom(), GetRandom(), GetRandom(), GetRandom(), GetRandom(), GetRandom(), GetRandom(), GetRandom(), GetRandom(), GetRandom(), GetRandom(), GetRandom(), GetRandom(), GetRandom(), GetRandom() };
const std::vector<double> weights5 = { GetRandom(), GetRandom(), GetRandom(), GetRandom(), GetRandom(), GetRandom(), GetRandom(), GetRandom(), GetRandom(), GetRandom(), GetRandom(), GetRandom(), GetRandom(), GetRandom(), GetRandom() };

void Sigmoid(double & x) 
{
    x = std::round(1 / (1 + std::pow(M_E, -x)) * 100) / 100;
}

void Tangens(double & x)
{
    double tx = 2 * x;
    double epow = (int)std::round(std::pow(M_E, tx) * 100) / 100;
    x = std::round((epow - 1) / (epow + 1) * 100) / 100;
}

double ErrorLight(double rightAnswer, double output)
{
    return std::round((rightAnswer - output) * 100) / 100;
}

struct Neuron
{
    Neuron() : output(0) {}
    std::vector<double> inputs{0.0};
    std::vector<double> weights{0.0};
    double              output;
    double              weightStep;
    void Normalize(void(*func)(double & x))
    {
        if (output > 0)
        {
            func(output);
        }
    }
    void Summarize()
    {
        output = 0.0;
        for (size_t i = 0; i < inputs.size(); i++)
        {
            output += inputs[i] * weights[i];
        }
    }
    void Lern()
    {
        for (size_t i = 0; i < weights.size(); i++)
        {
            if (inputs[i] > 0)
            {
                weights[i] += weightStep;
            }
        }
    }
    double GetError(double(*func)(double rightAnswer, double outputSignal), double rightAnswer)
    {
        return func(rightAnswer, output);
    }
};

void Study(std::vector<Neuron> & layer, const size_t epoch)
{
    std::cout << "START STUDYING" << std::endl;
    for (size_t i = 0; i < epoch; i++)
    {
        std::cout << "EPOCH = " << i << std::endl;
        for (size_t j = 0; j < layer.size(); j++)
        {
            layer[j].Summarize();
            layer[j].Normalize(Tangens);
            layer[j].Lern();
            std::cout << "Neuron #" << j
                << std::fixed << std::setprecision(2)
                << " Output = " << layer[j].output
                << " Error = " << layer[j].GetError(ErrorLight, 1) << std::endl;
        }
        std::cout << std::endl;
    }
}

void Recognize(std::vector<std::vector<Neuron>> & net, const std::vector<double> & signal)
{
    if (net.size() < 2)
    {
        return;
    }

    auto & hiddenLayer = net[0];
    // calculate output signal 
    for (size_t i = 0; i < hiddenLayer.size(); i++)
    {
        hiddenLayer[i].inputs = { signal[i] };
        hiddenLayer[i].Summarize();
        hiddenLayer[i].Normalize(Tangens);
    }

    std::vector<double> outputSignals;
    for (size_t i = 0; i < hiddenLayer.size(); i++)
    {
        outputSignals.push_back(hiddenLayer[i].output);
    }

    auto & outputLayer = net[1];
    double error = 0;
    double output = 0;
    for (size_t i = 0; i < outputLayer.size(); i++)
    {
        outputLayer[i].inputs = outputSignals;
        outputLayer[i].Summarize();
        outputLayer[i].Normalize(Tangens);
        output += outputLayer[i].output;
        error += outputLayer[i].GetError(ErrorLight, 1);
    }

    output /= outputLayer.size();
    error /= outputLayer.size();

    if (!error)
    {
        std::cout << "Recognized number" << std::endl;
        return;
    }
    std::cout << "No recognized any number" << std::endl;
}

int main()
{
    std::srand(unsigned(std::time(0)));

    const std::vector<std::vector<double>> TestSignals = {
        { 1.0, 0.0, 0.0, 1.0, 0.0, 0.0, 1.0, 0.0, 0.0, 1.0, 0.0, 0.0, 1.0, 0.0, 0.0 }, //1
        { 1.0, 1.0, 1.0, 1.0, 0.0, 1.0, 0.0, 1.0, 0.0, 1.0, 0.0, 0.0, 1.0, 1.0, 1.0 }, //2
        { 1.0, 1.0, 1.0, 0.0, 0.0, 1.0, 1.0, 1.0, 1.0, 0.0, 0.0, 1.0, 1.0, 1.0, 1.0 }, //3
        { 1.0, 0.0, 1.0, 1.0, 0.0, 1.0, 1.0, 1.0, 1.0, 0.0, 0.0, 1.0, 0.0, 0.0, 1.0 }, //4
        { 1.0, 1.0, 1.0, 1.0, 0.0, 0.0, 1.0, 1.0, 1.0, 0.0, 0.0, 1.0, 1.0, 1.0, 1.0 }, //5
    };

    // init hidden layer
    std::vector<Neuron> hiddenLayer;
    for (size_t i = 0; i < 15; i++)
    {
        hiddenLayer.push_back(Neuron());
    }
       
    for (size_t i = 0; i < hiddenLayer.size(); i++)
    {
        hiddenLayer[i].inputs = { signals1[i] };
        hiddenLayer[i].weights = { weights1[i] };
        hiddenLayer[i].weightStep = WEIGHT_STEP;
    }

    // learning
    Study(hiddenLayer, EPOCH_MAX);

    //init output layer
    std::vector<Neuron> outputLayer;
    outputLayer.push_back(Neuron());

    std::vector<double> outputSignals;
    for (size_t i = 0; i < hiddenLayer.size(); i++)
    {
        outputSignals.push_back(hiddenLayer[i].output);
    }

    for (size_t i = 0; i < outputLayer.size(); i++)
    {
        outputLayer[i].inputs = outputSignals;
        outputLayer[i].weights = weights2;
        outputLayer[i].weightStep = WEIGHT_STEP;
    }

    Study(outputLayer, EPOCH_MAX);

    std::vector<std::vector<Neuron>> net;
    net.push_back(hiddenLayer);
    net.push_back(outputLayer);

    // trying to find out
    Recognize(net, signals1);
    Recognize(net, signals2);
    Recognize(net, signals3);
    Recognize(net, signals4);
    Recognize(net, signals5);
    
    std::cin.get();
    return 0;
}

