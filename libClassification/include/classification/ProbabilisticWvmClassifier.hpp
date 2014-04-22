/*
 * ProbabilisticWvmClassifier.hpp
 *
 *  Created on: 25.02.2013
 *      Author: Patrik Huber
 */
#pragma once

#ifndef PROBABILISTICWVMCLASSIFIER_HPP_
#define PROBABILISTICWVMCLASSIFIER_HPP_

#include "classification/ProbabilisticClassifier.hpp"
#include "boost/property_tree/ptree.hpp"
#include <memory>

using boost::property_tree::ptree;
using std::shared_ptr;
using std::string;

namespace classification {

class WvmClassifier;

/**
 * WVM classifier that produces pseudo-probabilistic output. The hyperplane distance of a feature vector will be transformed
 * into a probability using a logistic function p(x) = 1 / (1 + exp(a + b * x)) with x being the hyperplane distance and a and
 * b being parameters.
 * TODO: different computation when feature vector did not reach the final stage -> mention it in this documentation (and change computation)
 */
class ProbabilisticWvmClassifier : public ProbabilisticClassifier {
public:

	/**
	 * Constructs a new probabilistic WVM classifier.
	 *
	 * @param[in] wvm The actual WVM.
	 * @param[in] logisticA Parameter a of the logistic function for pseudo-probabilistic output p(x) = 1 / (1 + exp(a + b * x)).
	 * @param[in] logisticB Parameter b of the logistic function for pseudo-probabilistic output p(x) = 1 / (1 + exp(a + b * x)).
	 */
	explicit ProbabilisticWvmClassifier(shared_ptr<WvmClassifier> wvm, double logisticA = 0.00556, double logisticB = -2.95);

	~ProbabilisticWvmClassifier();

	bool classify(const Mat& featureVector) const;

	pair<bool, double> getConfidence(const Mat& featureVector) const;

	pair<bool, double> getProbability(const Mat& featureVector) const;

	/**
	 * Computes the probability for being positive given the distance of a feature vector to the decision hyperplane.
	 *
	 * @param[in] levelAndDistance The index of the last used filter and distance of that filter level.
	 * @return A pair containing the binary classification result and a probability between zero and one for being positive.
	 */
	pair<bool, double> getProbability(pair<int, double> levelAndDistance) const;

	/**
	 * Creates a new probabilistic WVM classifier from the parameters given in some Matlab file. Loads the logistic function's
	 * parameters from the matlab file, then passes the loading to the underlying WVM which loads the vectors and thresholds
	 * from the matlab file. TODO update doc
	 *
	 * @param[in] classifierFilename The name of the file containing the WVM parameters.
	 * @param[in] thresholdsFilename The name of the file containing the thresholds of the filter levels and the logistic function's parameters.
	 * @return The newly created probabilistic WVM classifier.
	 */
	static std::pair<double, double> loadSigmoidParamsFromMatlab(const string& thresholdsFilename);

	/**
	 * Creates a new probabilistic WVM classifier from the parameters given in some Matlab file. Loads the logistic function's
	 * parameters from the matlab file, then passes the loading to the underlying WVM which loads the vectors and thresholds
	 * from the matlab file. TODO: This could be renamed just to "load(...)". But NOTE: The classifier will then be loaded with
	 * default settings, and any deviation from that (e.g. adjusting the thresholds) must be done manually.
	 *
	 * @param[in] classifierFilename The name of the file containing the WVM parameters.
	 * @param[in] thresholdsFilename The name of the file containing the thresholds of the filter levels and the logistic function's parameters.
	 * @return The newly created probabilistic WVM classifier.
	 */
	static shared_ptr<ProbabilisticWvmClassifier> loadFromMatlab(const string& classifierFilename, const string& thresholdsFilename);

	/**
	 * Creates a new probabilistic WVM classifier from the parameters given in the ptree sub-tree. Loads the logistic function's
	 * parameters, then passes the loading to the underlying WVM which loads the vectors and thresholds
	 * from the matlab file. Supports the following settings in the ptree: ....TODO
	 *
	 * @param[in] subtree The subtree containing the config information for this classifier.
	 * @return The newly created probabilistic WVM classifier.
	 */
	static shared_ptr<ProbabilisticWvmClassifier> load(const ptree& subtree);

	/**
	 * @return The actual WVM.
	 */
	shared_ptr<WvmClassifier> getWvm() {
		return wvm;
	}

	/**
	 * @return The actual WVM.
	 */
	const shared_ptr<WvmClassifier> getWvm() const {
		return wvm;
	}

private:

	shared_ptr<WvmClassifier> wvm; ///< The actual WVM.
	double logisticA; ///< Parameter a of the logistic function for pseudo-probabilistic output p(x) = 1 / (1 + exp(a + b * x)).
	double logisticB; ///< Parameter b of the logistic function for pseudo-probabilistic output p(x) = 1 / (1 + exp(a + b * x)).
};

} /* namespace classification */
#endif /* PROBABILISTICWVMCLASSIFIER_HPP_ */

