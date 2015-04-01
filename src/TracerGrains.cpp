/*
 * TracerGrains.cpp
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

#include "TracerGrains.h"
#include "CombinerVariables.h"

namespace SedFlow {

TracerGrains::TracerGrains()
{
	this->typeOfGrains = CombinerVariables::TracerGrains;
	this->typeSpecificGetterAvailable = false;
}

TracerGrains::TracerGrains(const std::vector<double> &fractionalAbundance):
	GrainType(fractionalAbundance)
{
	this->typeOfGrains = CombinerVariables::TracerGrains;
	this->typeSpecificGetterAvailable = false;
}

TracerGrains::TracerGrains(const GrainType* toCopy):
	GrainType(toCopy->getFractions())
{
	if( (*toCopy).getTypeOfGrains() != CombinerVariables::TracerGrains)
	{
		const char *const errorMessage = "Action on not matching types of grains";
		throw(errorMessage);
	} else {
		this->typeOfGrains = CombinerVariables::TracerGrains;
		this->typeSpecificGetterAvailable = false;
	}
}

TracerGrains::TracerGrains(const std::vector<double>& fractionalAbundance, const std::vector<double>& additionalParameters):
	GrainType(fractionalAbundance)
{
	this->typeOfGrains = CombinerVariables::TracerGrains;
	this->typeSpecificGetterAvailable = false;
}

TracerGrains::~TracerGrains() {}

GrainType* TracerGrains::createGrainTypePointerCopy() const
{
	GrainType* result = new TracerGrains(static_cast<const GrainType*>(this));
	return result;
}

ConstructionVariables TracerGrains::createConstructionVariables()const
{
	ConstructionVariables result = ConstructionVariables();
	result.interfaceOrCombinerType = CombinerVariables::GrainType;
	result.realisationType = CombinerVariables::typeOfGrainsToString(CombinerVariables::TracerGrains);
	std::vector<double> doubleVector;
	doubleVector.reserve( fractionalAbundance.size() );
	for(std::vector<double>::const_iterator iterator = fractionalAbundance.begin(); iterator < fractionalAbundance.end(); ++iterator)
			{ doubleVector.push_back(*iterator); }
	result.labelledDoubles["fractionalAbundance"] = doubleVector;
	return result;
}

}
