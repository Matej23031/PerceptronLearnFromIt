#ifndef PERCEPTRON_H
#define PERCEPTRON_H

#include <vector>
#include <random>
#include <string>
#include <iostream>

constexpr double BIAS_INPUT = 1.0;
constexpr int MAX_EPOCHS = 100;

// Function prototypes
double computeIntegration(const std::vector<double>& input, const std::vector<double>& weights);
int computeActivation(const double input);
void randomizeWeights(std::vector<double>& weights, std::default_random_engine& generator);
void trainPerceptron(std::vector<std::vector<double>>& data, std::vector<double>& weights);

extern std::vector<double> weights;  // External linkage for weights

template<typename T>
T promptInput(const std::string& prompt) {
    std::cout << prompt;
    std::string line;
    std::getline(std::cin, line);
    try {
        return std::stod(line);
    }
    catch (const std::invalid_argument& ia) {
        std::cerr << "Invalid input, please enter a valid number.\n";
        return promptInput<T>(prompt);
    }
}

int classify(const std::vector<double>& input, const std::vector<double>& weights);

#endif // PERCEPTRON_H
