//
// Created by НикитаГоршков on 17.06.2019.
//

#include "classifier.h"
#include <math.h>
#include <string>
#include <vector>
#include <iostream>
#include <random>
#include "helpers.h"

using std::string;
using std::vector;

// Initializes GNB
GNB::GNB() {
    /**
     * TODO: Initialize GNB, if necessary. May depend on your implementation.
     */
}

GNB::~GNB() {}

void GNB::train(const vector<vector<double>> &data,
                const vector<string> &labels) {
    /**
     * Trains the classifier with N data points and labels.
     * @param data - array of N observations
     *   - Each observation is a tuple with 4 values: s, d, s_dot and d_dot.
     *   - Example : [[3.5, 0.1, 5.9, -0.02],
     *                [8.0, -0.3, 3.0, 2.2],
     *                 ...
     *                ]
     * @param labels - array of N labels
     *   - Each label is one of "left", "keep", or "right".
     *
     * TODO: Implement the training function for your classifier.
     */
    vector<int> number_of_class_samples(possible_labels.size(), 0);
    means = vector<vector<double>>(possible_labels.size(), {0,0,0,0});
    stds = vector<vector<double>>(possible_labels.size(), {0,0,0,0});
    for (int i = 0; i < labels.size(); i++) {
        int label_idx;
        if (labels[i] == "left") {
            label_idx = 0;
        } else if (labels[i] == "keep") {
            label_idx = 1;
        } else {
            label_idx = 2;
        }
        number_of_class_samples[label_idx]++;
        for (int j = 0; j < data[i].size(); j++) {
            means[label_idx][j] += data[i][j];
        }
    }
    for (int i = 0; i < number_of_class_samples.size(); i++) {
        priors.push_back((double)number_of_class_samples[i] / labels.size());
        for (int j = 0; j < means[i].size(); j++) {
            means[i][j] /= number_of_class_samples[i];
        }
    }
    for (int i = 0; i < labels.size(); i++) {
        int label_idx;
        if (labels[i] == "left") {
            label_idx = 0;
        } else if (labels[i] == "keep") {
            label_idx = 1;
        } else {
            label_idx = 2;
        }
        for (int j = 0; j < data[i].size(); j++) {
            stds[label_idx][j] += (data[i][j] - means[label_idx][j]) * (data[i][j] - means[label_idx][j]);
        }
    }
    for (int i = 0; i < stds.size(); i++) {
        for (int j = 0; j < stds[i].size(); j++) {
            stds[i][j] /= number_of_class_samples[i];
            stds[i][j] = sqrt(stds[i][j]);
        }
    }
}

string GNB::predict(const vector<double> &sample) {
    /**
     * Once trained, this method is called and expected to return
     *   a predicted behavior for the given observation.
     * @param observation - a 4 tuple with s, d, s_dot, d_dot.
     *   - Example: [3.5, 0.1, 8.5, -0.2]
     * @output A label representing the best guess of the classifier. Can
     *   be one of "left", "keep" or "right".
     *
     * TODO: Complete this function to return your classifier's prediction
     */

    vector<double> class_probabilities{0.0, 0.0, 0.0, 0.0};
    double pb_of_data = 0.0;
    for (int i = 0; i < possible_labels.size(); i++) {
        float pb_of_x_given_class = 1.0;
        for (int j = 0; j < sample.size(); j++) {
            pb_of_x_given_class *= Helpers::normpdf(sample[j], means[i][j], stds[i][j]);
        }
        pb_of_data += pb_of_x_given_class * priors[i];
        class_probabilities[i] = pb_of_x_given_class * priors[i];
    }

    for (int i = 0; i < possible_labels.size(); i++) {
        class_probabilities[i] /= pb_of_data;
    }

    double best_fit = class_probabilities[0];
    int label_idx = 0;
    for (int i = 1; i < class_probabilities.size(); i++) {
        if (class_probabilities[i] > best_fit) {
            best_fit = class_probabilities[i];
            label_idx = i;
        }
    }
    return this -> possible_labels[label_idx];
}