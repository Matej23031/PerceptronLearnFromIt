#include "Perceptron.h"
#include <numeric>
#include <algorithm>
#include <random>
#include <iostream>

double computeIntegration(const std::vector<double>& input, const std::vector<double>& weights) {
    return std::inner_product(input.begin(), input.end() - 1, weights.begin(), 0.0);
}

int computeActivation(const double input) {
    return input >= 0 ? 1 : 0;
}

void randomizeWeights(std::vector<double>& weights, std::default_random_engine& generator) {
    std::uniform_real_distribution<double> distribution(-0.5, 0.5);
    std::generate(weights.begin(), weights.end(), [&]() { return distribution(generator); });
}

void trainPerceptron(std::vector<std::vector<double>>& data, std::vector<double>& weights) {
    std::random_device rd;
    std::default_random_engine generator(rd());
    int epoch = 0, incorrect;

    do {
        incorrect = 0;
        std::shuffle(data.begin(), data.end(), generator);

        for (auto& sample : data) {
            double dotProduct = computeIntegration(sample, weights) + BIAS_INPUT * weights.back();
            int prediction = computeActivation(dotProduct);
            double error = sample.back() - prediction;

            if (error != 0) {
                std::transform(sample.begin(), sample.end() - 1, weights.begin(), weights.begin(),
                    [error](double input, double weight) { return weight + input * error; });
                weights.back() += BIAS_INPUT * error;
                incorrect++;
            }
        }

        std::cout << "Epoch " << ++epoch << ": Incorrect classifications = " << incorrect << std::endl;
    } while (incorrect > 0 && epoch < MAX_EPOCHS);
}

std::vector<double> weights{ -1.3119, -5.89517, 9.44548, 3.78922, -1.22725 };  // Initialize weights

int classify(const std::vector<double>& input, const std::vector<double>& weights) {
    auto integration_function = [](const auto& in, const auto& wt) {
        return std::inner_product(in.begin(), in.end(), wt.begin(), 0.0, std::plus<>(),
            [](double a, double b) { return a * b + a * 0.1 - b * 0.05; });
    };

    double result = integration_function(input, weights) + BIAS_INPUT * weights.back();
    return result >= 0 ? 1 : 0;
}
