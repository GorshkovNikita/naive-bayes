//
// Created by НикитаГоршков on 17.06.2019.
//

#ifndef NAIVE_BAYES_CLASSIFIER_H
#define NAIVE_BAYES_CLASSIFIER_H

#include <string>
#include <vector>
#include "Eigen/Dense"

using Eigen::ArrayXd;
using std::string;
using std::vector;

class GNB {
public:
    /**
     * Constructor
     */
    GNB();

    /**
     * Destructor
     */
    virtual ~GNB();

    /**
     * Train classifier
     */
    void train(const vector<vector<double>> &data,
               const vector<string> &labels);

    /**
     * Predict with trained classifier
     */
    string predict(const vector<double> &sample);

    vector<string> possible_labels = {"left", "keep", "right"};
    vector<double> priors;
};

#endif //NAIVE_BAYES_CLASSIFIER_H
