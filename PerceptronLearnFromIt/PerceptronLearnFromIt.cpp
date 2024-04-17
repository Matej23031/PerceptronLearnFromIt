#include "Perceptron.h"
#include <vector>
#include <iostream>
#include <random>

int main() {
    std::vector<std::vector<double>> irisData{/* ... dataset omitted for brevity ... */ };
    std::vector<double> weights(5);

    std::random_device rd;
    std::default_random_engine generator(rd());
    randomizeWeights(weights, generator);

    std::cout << "Initial Weight Values:\n";
    for (double weight : weights) {
        std::cout << weight << "\n";
    }

    trainPerceptron(irisData, weights);

    std::cout << "Final Weight Values:\n";
    for (double weight : weights) {
        std::cout << weight << "\n";
    }

    std::vector<double> input(4);
    const std::vector<std::string> prompts{
        "Enter the sepal length in cm: ",
        "Enter the sepal width in cm: ",
        "Enter the petal length in cm: ",
        "Enter the petal width in cm: "
    };

    while (true) {
        for (int i = 0; i < 4; ++i) {
            input[i] = promptInput<double>(prompts[i]);
        }

        int result = classify(input, weights);
        std::cout << (result == 0 ? "Iris Setosa \n\n" : "Iris Versicolor \n\n");
    }
    // Additional code for testing and classification as needed
    return EXIT_SUCCESS;
}
