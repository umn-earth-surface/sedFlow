/*
 * ReducedWaterEnergyslopeNotUsingWaterEnergyslopeVariable.h
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

#ifndef REDUCEDWATERENERGYSLOPENOTUSINGWATERENERGYSLOPEVARIABLE_H_
#define REDUCEDWATERENERGYSLOPENOTUSINGWATERENERGYSLOPEVARIABLE_H_

#include "CalcGradient.h"
#include "ReducedWaterEnergyslope.h"
#include "RegularRiverReachProperties.h"
#include "RegularRiverSystemProperties.h"

#include <vector>

namespace SedFlow {

class ReducedWaterEnergyslopeNotUsingWaterEnergyslopeVariable: public ReducedWaterEnergyslope {
private:
	CalcGradient* simpleWaterEnergyslopeCalculationMethod;

public:
	ReducedWaterEnergyslopeNotUsingWaterEnergyslopeVariable(CalcGradient* simpleWaterEnergyslopeCalculationMethod, double stressPartitioningExponent, bool calculationBasedOnqInsteadOfh, double maximumFroudeNumber, bool ensureMinimumInputSlope, double minimumInputSlope);
	virtual ~ReducedWaterEnergyslopeNotUsingWaterEnergyslopeVariable();

	CalcGradient* createCalcGradientMethodPointerCopy() const;

	ConstructionVariables createConstructionVariables()const;

	double calculate (const RiverReachProperties& riverReachProperties) const;
	double calculate (const RiverSystemProperties& river, int cellID) const;
	std::vector<double> calculate (const RiverSystemProperties& river) const;

	std::pair<double,double> calculateReducedAndUnreducedSedimentEnergyslope (const RiverReachProperties& riverReachProperties) const;
	std::pair<double,double> calculateReducedAndUnreducedSedimentEnergyslope (const RiverSystemProperties& river, int cellID) const;
	std::pair< std::vector<double>, std::vector<double> > calculateReducedAndUnreducedSedimentEnergyslope (const RiverSystemProperties& river) const;
};

}

#endif /* REDUCEDWATERENERGYSLOPENOTUSINGWATERENERGYSLOPEVARIABLE_H_ */
