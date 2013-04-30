/*
 * Layer.cpp
 *
 *  Created on: Apr 18, 2013
 *      Author: Christian Grefe, CERN
 */

#include "LayerStack.h"
#include "Exceptions.h"
#include "DD4hep/Detector.h"
#include "DD4hep/Shapes.h"

#include <sstream>

namespace DD4hep {
namespace Geometry {

using std::stringstream;

LayerStack::LayerStack(const DetElement& det) : det(det) {

}

LayerStack::LayerStack(const LayerStack& layerStack, const DetElement& det) : det(det) {

}

LayerStack::~LayerStack() {

}

double LayerStack::getThickness(int layerIndex, int moduleIndex) const {
	double thickness = 0.;
	for (int sliceIndex = 0; sliceIndex < getNumberOfSlices(layerIndex, moduleIndex); sliceIndex++) {
		thickness += Box(getSlice(layerIndex, moduleIndex, sliceIndex).volume().solid())->GetDZ();
	}
	return thickness;
}

double LayerStack::getRadiationLengths(int layerIndex, int moduleIndex) const {
	double radiationLengths = 0.;
	for (int sliceIndex = 0; sliceIndex < getNumberOfSlices(layerIndex, moduleIndex); sliceIndex++) {
		radiationLengths += Box(getSlice(layerIndex, moduleIndex, sliceIndex).volume().solid())->GetDZ() / getSlice(layerIndex, moduleIndex).volume().material().radLength();
	}
	return radiationLengths;
}

double LayerStack::getInteractionLengths(int layerIndex, int moduleIndex) const {
	double interactionLengths = 0.;
	for (int sliceIndex = 0; sliceIndex < getNumberOfSlices(layerIndex, moduleIndex); sliceIndex++) {
		interactionLengths += Box(getSlice(layerIndex, moduleIndex, sliceIndex).volume().solid())->GetDZ() / getSlice(layerIndex, moduleIndex).volume().material().intLength();
	}
	return interactionLengths;
}

double LayerStack::getTotalThickness(int moduleIndex) const {
	double thickness = 0.;
	for (int layerIndex = 0; layerIndex < getNumberOfLayers(); layerIndex++) {
		thickness += getThickness(layerIndex, moduleIndex);
	}
	return thickness;
}

double LayerStack::getTotalInteractionLengths(int moduleIndex) const {
	double interactionLengths = 0.;
	for (int layerIndex = 0; layerIndex < getNumberOfLayers(); layerIndex++) {
		interactionLengths += getInteractionLengths(layerIndex, moduleIndex);
	}
	return interactionLengths;
}

double LayerStack::getTotalRadiationLengths(int moduleIndex) const {
	double radiationLengths = 0.;
	for (int layerIndex = 0; layerIndex < getNumberOfLayers(); layerIndex++) {
		radiationLengths += getRadiationLengths(layerIndex, moduleIndex);
	}
	return radiationLengths;
}

PolyhedralCalorimeterLayerStack::PolyhedralCalorimeterLayerStack(const DetElement& det) : LayerStack(det) {

}

PolyhedralCalorimeterLayerStack::PolyhedralCalorimeterLayerStack(const PolyhedralCalorimeterLayerStack& layerStack, const DetElement& det) : LayerStack(layerStack, det) {

}

PolyhedralCalorimeterLayerStack::~PolyhedralCalorimeterLayerStack() {

}

int PolyhedralCalorimeterLayerStack::getNumberOfLayers() const {
	stringstream moduleName;
	moduleName << "stave0";
	return det.child(moduleName.str()).children().size();
}

int PolyhedralCalorimeterLayerStack::getNumberOfModules(int layerIndex) const {
	return det.children().size();
}

DetElement PolyhedralCalorimeterLayerStack::getModule(int layerIndex, int moduleIndex) const {
	stringstream moduleName;
	moduleName << "stave" << moduleIndex;
	stringstream layerName;
	layerName << "layer" << layerIndex;
	return det.child(moduleName.str()).child(layerName.str());
}

int PolyhedralCalorimeterLayerStack::getNumberOfSlices(int layerIndex, int moduleIndex) const {
	return getModule(layerIndex, moduleIndex).children().size();
}

DetElement PolyhedralCalorimeterLayerStack::getSlice(int layerIndex, int moduleIndex, int sliceIndex) const {
	stringstream sliceName;
	sliceName << "slice" << sliceIndex;
	return getModule(layerIndex, moduleIndex).child(sliceName.str());
}

int PolyhedralCalorimeterLayerStack::getNumberOfSensors(int layerIndex, int moduleIndex) const {
	int nSensors = 0;
	for (int sliceIndex = 0; sliceIndex < getNumberOfSlices(layerIndex, moduleIndex); sliceIndex++) {
		if (getSlice(layerIndex, moduleIndex, sliceIndex).volume().isSensitive()) {
			nSensors++;
		}
	}
	return nSensors;
}

DetElement PolyhedralCalorimeterLayerStack::getSensor(int layerIndex, int moduleIndex, int sensorIndex) const {
	int nSensors = 0;
	for (int sliceIndex = 0; sliceIndex < getNumberOfSlices(layerIndex, moduleIndex); sliceIndex++) {
		const DetElement& slice = getSlice(layerIndex, moduleIndex, sliceIndex);
		if (slice.volume().isSensitive()) {
			nSensors++;
		}
		if (nSensors == sensorIndex) {
			return slice;
		}
	}
	throw OutsideGeometryException("No sensor with index " + sensorIndex);
}

} /* namespace Geometry */
} /* namespace DD4hep */
