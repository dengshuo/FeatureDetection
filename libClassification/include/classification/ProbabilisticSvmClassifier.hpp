/*
 * ProbabilisticSvmClassifier.hpp
 *
 *  Created on: 25.02.2013
 *      Author: Patrik Huber
 */
#pragma once

#ifndef PROBABILISTICSVMCLASSIFIER_HPP_
#define PROBABILISTICSVMCLASSIFIER_HPP_

#include "classification/ProbabilisticClassifier.hpp"
#include <memory>

using std::shared_ptr;
using std::string;

namespace classification {

class SvmClassifier;

/**
 * SVM classifier that produces pseudo-probabilistic output. The hyperplane distance of a feature vector will be transformed
 * into a probability using a logistic function p(x) = 1 / (1 + exp(a + b * x)) with x being the hyperplane distance and a and
 * b being parameters.
 */
class ProbabilisticSvmClassifier : public ProbabilisticClassifier {
public:

	/**
	 * Constructs a new empty probabilistic SVM classifier.
	 */
	ProbabilisticSvmClassifier();

	/**
	 * Constructs a new probabilistic SVM classifier.
	 *
	 * @param[in] svm The actual SVM.
	 * @param[in] logisticA Parameter a of the logistic function for pseudo-probabilistic output p(x) = 1 / (1 + exp(a + b * x)).
	 * @param[in] logisticB Parameter b of the logistic function for pseudo-probabilistic output p(x) = 1 / (1 + exp(a + b * x)).
	 */
	explicit ProbabilisticSvmClassifier(shared_ptr<SvmClassifier> svm, double logisticA = 0.00556, double logisticB = -2.95);

	~ProbabilisticSvmClassifier();

	/**
	 * @return The actual SVM.
	 */
	shared_ptr<SvmClassifier> getSvm() {
		return svm;
	}

	/**
	 * @return The actual SVM.
	 */
	const shared_ptr<SvmClassifier> getSvm() const {
		return svm;
	}

	pair<bool, double> classify(const Mat& featureVector) const;

	/**
	 * Changes the logistic parameters of this probabilistic SVM.
	 *
	 * @param[in] logisticA Parameter a of the logistic function for pseudo-probabilistic output p(x) = 1 / (1 + exp(a + b * x)).
	 * @param[in] logisticB Parameter b of the logistic function for pseudo-probabilistic output p(x) = 1 / (1 + exp(a + b * x)).
	 */
	void setLogisticParameters(double logisticA, double logisticB);

	/**
	 * Creates a new probabilistic SVM classifier from the parameters given in some Matlab file. Loads the logistic function's
	 * parameters from the matlab file, then passes the loading to the underlying SVM which loads the vectors and thresholds
	 * from the matlab file.
	 *
	 * @param[in] classifierFilename TODO
	 * @param[in] thresholdsFilename TODO
	 */
	static shared_ptr<ProbabilisticSvmClassifier> loadMatlab(const string& classifierFilename, const string& thresholdsFilename); // TODO: Re-work this.

private:

	shared_ptr<SvmClassifier> svm; ///< The actual SVM.
	double logisticA; ///< Parameter a of the logistic function for pseudo-probabilistic output p(x) = 1 / (1 + exp(a + b * x)).
	double logisticB; ///< Parameter b of the logistic function for pseudo-probabilistic output p(x) = 1 / (1 + exp(a + b * x)).
};

} /* namespace classification */
#endif /* PROBABILISTICSVMCLASSIFIER_HPP_ */
