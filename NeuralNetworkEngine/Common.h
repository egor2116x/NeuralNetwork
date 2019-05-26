#pragma once
#include "stdafx.h"

const unsigned MAX_LAYERS = 3;

// Activation function
void LinearFunction(double & x);
void Sigmoid(double & x);
void HyperbolicTangent(double & x);

// Error function
double MSE(double x, const std::vector<double> & signals);
double RootMSE(double x, const std::vector<double> & signals);
double Arctan(double x, const std::vector<double> & signals);