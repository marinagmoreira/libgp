//
// libgp - Gaussian Process library for Machine Learning
// Copyright (C) 2010 Universität Freiburg
//
// This program is free software; you can redistribute it and/or
// modify it under the terms of the GNU General Public License
// as published by the Free Software Foundation; either version 2
// of the License, or (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.

#ifndef COV_H_YTE8CCNB
#define COV_H_YTE8CCNB

#include <iostream>
#include <vector>

#include <Eigen/Dense>

namespace libgp
{

/** Covariance function base class.
 *  @author Manuel Blum
 *  @ingroup cov_group 
 *  @todo implement more covariance functions
 */
class CovarianceFunction
{
public:
	/** Constructor. */
	CovarianceFunction() {};

	/** Destructor. */
	virtual ~CovarianceFunction() {};

  /** Initialization method for atomic covariance functions. 
   *  @param input_dim dimensionality of the input vectors */
	virtual void init(int input_dim) {};

  /** Initialization method for compound covariance functions. 
   *  @param input_dim dimensionality of the input vectors 
   *  @param first first covariance function of compound
   *  @param second second covariance function of compound
   */
	virtual void init(int input_dim, CovarianceFunction * first, CovarianceFunction * second) {};

	/** Computes the covariance of two input vectors.
	 *  @param x1 first input vector
	 *  @param x2 second input vector
   *  @return covariance of x1 and x2
	 */
	virtual double get(Eigen::VectorXd &x1, Eigen::VectorXd &x2) = 0;

	/** Covariance gradient of two input vectors with respect to the hyperparameters.
	 *  @param x1 first input vector
	 *  @param x2 second input vector
	 *  @param grad covariance gradient 
	 */
	virtual void grad(Eigen::VectorXd &x1, Eigen::VectorXd &x2, Eigen::VectorXd &grad) = 0;

	/** Update parameter vector.
	 *  @param p new parameter vector
	 *  @return true for success
	 */
	virtual bool set_loghyper(Eigen::VectorXd &p);

	/** Get number of parameters for this covariance function.
	 *  @return parameter vector dimensionality
	 */
	size_t get_param_dim();

	/** Get input dimensionality.
	 *  @return input dimensionality
	 */
	size_t get_input_dim();

	/** Get log-hyperparameter of covariance function.
	 *  @return log-hyperparameter
	 */
	Eigen::VectorXd get_loghyper();

  /** Returns a string representation of this covariance function.
   *  @return string containing the name of this covariance function 
   */
	virtual std::string to_string() = 0;
	
protected:
	/** Input dimensionality. */
	size_t input_dim;

	/** Size of parameter vector. */
	size_t param_dim;

	/** Parameter vector containing the log hyper-parameters of the Gaussian process.
	 *  The number of necessary parameters depends on the kernel function and is
	 *  given in param_dim.
	 */
	Eigen::VectorXd loghyper;
};

}

#endif /* end of include guard: COV_H_YTE8CCNB */


/** Currently the following covariance functions are implemented in libgp.
 *  @defgroup cov_group Covariance Functions */