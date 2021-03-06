/*
 * FalsePositionMethod.h
 *
 *   Copyright (C) 2014 Swiss Federal Research Institute WSL (http://www.wsl.ch)
 *   Developed by F.U.M. Heimann
 *   Published by the Swiss Federal Research Institute WSL
 *   
 *   This program is free software: you can redistribute it and/or modify it
 *   under the terms of the GNU General Public License version 3
 *   as published by the Free Software Foundation.
 *   
 *   This program is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY;
 *   without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. 
 *   See the GNU General Public License for more details.
 *   
 *   You should have received a copy of the GNU General Public License
 *   along with this program.  If not, see http://www.gnu.org/licenses
 *   
 *   This software is part of the model sedFlow,
 *   which is intended for the simulation of bedload dynamics in mountain streams.
 *   
 *   For details on sedFlow see http://www.wsl.ch/sedFlow
 */

#ifndef FALSEPOSITIONMETHOD_H_
#define FALSEPOSITIONMETHOD_H_

#include "NumericRootFinder.h"

#include <iostream>
#include <math.h>
#include <limits>

namespace SedFlow {

template <typename UnaryFunction> class FalsePositionMethod: public NumericRootFinder<UnaryFunction> {
public:
	FalsePositionMethod(){}
	virtual ~FalsePositionMethod(){}

	NumericRootFinder<UnaryFunction>* createNumericRootFinderPointerCopy() const //This method HAS TO BE implemented.
	{
		NumericRootFinder<UnaryFunction>* result = new FalsePositionMethod<UnaryFunction>();
		return result;
	}

	ConstructionVariables createConstructionVariables()const
	{
		ConstructionVariables result = ConstructionVariables();
		result.interfaceOrCombinerType = CombinerVariables::NumericRootFinder;
		result.realisationType = CombinerVariables::typeOfNumericRootFinderToString(CombinerVariables::FalsePositionMethod);
		return result;
	}

	double findRoot (const UnaryFunction& function, double firstBracket, double secondBracket, double errorTolerance, int maximumNumberOfIterations) const
	{
		double fFirst = function(firstBracket);
		double fSecond = function(secondBracket);

		if( (fFirst * fSecond) > 0.0 )
		{
			const char *const bracketingErrorMessage = "FalsePositionMethod: Root must be bracketed by the input brackets.";
			throw(bracketingErrorMessage);
		}

		if( fFirst > 0.0 ) //firstBracket should have the negative function value
		{
			double tmp = firstBracket;
			firstBracket = secondBracket;
			secondBracket = tmp;

			tmp = fFirst;
			fFirst = fSecond;
			fSecond = tmp;
		}

		double currentGuess, fCurrentGuess, delta;

		for(int i = 1; i <= maximumNumberOfIterations; ++i)
		{
			currentGuess = firstBracket + ((secondBracket - firstBracket) * ( fFirst / (fFirst - fSecond) ));
			fCurrentGuess = function(currentGuess);

			if( fCurrentGuess < 0.0 )
			{
				delta = firstBracket - currentGuess;
				firstBracket = currentGuess;
				fFirst = fCurrentGuess;
			}
			else
			{
				delta = secondBracket - currentGuess;
				secondBracket = currentGuess;
				fSecond = fCurrentGuess;
			}

			if( fCurrentGuess == 0.0 || fabs(delta) <= errorTolerance ){return currentGuess;}
		}

		const char *const maxIterationErrorMessage = "FalsePositionMethod: Maximum number of iterations exceeded.";
		throw(maxIterationErrorMessage);
		return std::numeric_limits<double>::signaling_NaN();
	}

};

}

#endif /* FALSEPOSITIONMETHOD_H_ */
