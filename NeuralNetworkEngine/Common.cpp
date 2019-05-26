#include "Common.h"

void LinearFunction(double & x)
{
    x = x; 
}

void Sigmoid(double & x)
{
    x = 1 / 1 + std::pow(std::exp(x), -x);
}

void HyperbolicTangent(double & x)
{
    double top = std::pow(std::exp(x), -1);
    double bottom = std::pow(std::exp(x), 1);
    x = top / bottom;
}

double MSE(double x, const std::vector<double>& signals)
{
    double result = 0.0;
    for (auto signal : signals)
    {
        result += std::pow(x - signal, 2);
    }
    result /= signals.size();

    return result;
}

double RootMSE(double x, const std::vector<double>& signals)
{
    double result = 0.0;
    for (auto signal : signals)
    {
        result += std::pow(x - signal, 2);
    }
    result /= signals.size();
    result = std::sqrt(result);

    return result;
}

double Arctan(double x, const std::vector<double>& signals)
{
    double result = 0.0;
    for (auto signal : signals)
    {
        result += std::pow(std::atan(x - signal), 2);
    }
    result /= signals.size();

    return result;
}
