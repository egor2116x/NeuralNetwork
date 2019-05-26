// NeuralNetwork.cpp : Defines the entry point for the console application.

#include "stdafx.h"
#include "Common.h"

struct Neuron
{
    Neuron() : output(0) {}
    std::vector<double> inputs;
    std::vector<double> weights;
    double              output;
    double              weightStep;
    void Normalize(void(*func)(double & x))
    {
        func(output);
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

void Study(std::vector<Neuron> & net, const size_t epoch)
{
    for (size_t i = 0; i < epoch; i++)
    {
        std::cout << "EPOCH = " << i << std::endl;
        for (size_t j = 0; j < net.size(); j++)
        {
            net[j].Summarize();
            net[j].Normalize(Sigmoid);
            net[j].Lern();
            std::cout << "Neuron #" << j
                << std::fixed << std::setprecision(2)
                << " Output = " << net[j].output
                << " Error = " << net[j].GetError(MSE, 1) << std::endl;
        }
        std::cout << std::endl;
    }
}

void Recognize(std::vector<Neuron> & net, const std::vector<double> & signal)
{
    for (size_t i = 0; i < net.size(); i++)
    {
        net[i].inputs = signal;
        net[i].Summarize();
        net[i].Normalize(Sigmoid);
        const double error = net[i].GetError(MSE, 1);
        if (!error && (1 - net[i].output < 0.1))
        {
            std::cout << "Recognized number is " << i + 1 << std::endl;
            return;
        }
    }
    std::cout << "No recognized any number" << std::endl;
}

int main()
{
    const std::vector<std::vector<double>> signals = {
        { 0.0, 0.0, 1.0, 0.0, 1.0, 1.0, 0.0, 0.0, 1.0, 0.0, 0.0, 1.0, 0.0, 0.0, 1.0 }, //1
        { 1.0, 1.0, 1.0, 1.0, 0.0, 1.0, 0.0, 1.0, 0.0, 1.0, 0.0, 0.0, 1.0, 1.0, 1.0 }, //2
        { 1.0, 1.0, 1.0, 0.0, 0.0, 1.0, 1.0, 1.0, 1.0, 0.0, 0.0, 1.0, 1.0, 1.0, 1.0 }, //3
        { 1.0, 0.0, 1.0, 1.0, 0.0, 1.0, 1.0, 1.0, 1.0, 0.0, 0.0, 1.0, 0.0, 0.0, 1.0 }, //4
        { 1.0, 1.0, 1.0, 1.0, 0.0, 0.0, 1.0, 1.0, 1.0, 0.0, 0.0, 1.0, 1.0, 1.0, 1.0 }, //5
    };
    const std::vector<std::vector<double>> weights = {
        { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
        { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
        { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
        { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
        { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
    };

    const std::vector<std::vector<double>> TestSignals = {
        { 1.0, 0.0, 0.0, 1.0, 0.0, 0.0, 1.0, 0.0, 0.0, 1.0, 0.0, 0.0, 1.0, 0.0, 0.0 }, //1
        { 1.0, 1.0, 1.0, 1.0, 0.0, 1.0, 0.0, 1.0, 0.0, 1.0, 0.0, 0.0, 1.0, 1.0, 1.0 }, //2
        { 1.0, 1.0, 1.0, 0.0, 0.0, 1.0, 1.0, 1.0, 1.0, 0.0, 0.0, 1.0, 1.0, 1.0, 1.0 }, //3
        { 1.0, 0.0, 1.0, 1.0, 0.0, 1.0, 1.0, 1.0, 1.0, 0.0, 0.0, 1.0, 0.0, 0.0, 1.0 }, //4
        { 1.0, 1.0, 1.0, 1.0, 0.0, 0.0, 1.0, 1.0, 1.0, 0.0, 0.0, 1.0, 1.0, 1.0, 1.0 }, //5
    };

    // defines
    const size_t EPOCH_MAX = 4;
    const double WEIGHT_STEP = 0.1;
    const double ERROR_LIMIT = 0.2;

    std::vector<Neuron> net;
    net.push_back(Neuron());
    net.push_back(Neuron());
    net.push_back(Neuron());
    net.push_back(Neuron());
    net.push_back(Neuron());

    // init
    for (size_t i = 0; i < net.size(); i++)
    {
        net[i].inputs = signals[i];
        net[i].weights = weights[i];
        net[i].weightStep = WEIGHT_STEP;
    }

    // learning
    Study(net, EPOCH_MAX);

    // trying to find out
    for (size_t i = 0; i < net.size(); i++)
    {
        Recognize(net, TestSignals[i]);
    }
    
    std::cin.get();
    return 0;
}

