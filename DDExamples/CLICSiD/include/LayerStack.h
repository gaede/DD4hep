/*
 * LayerStack.h
 *
 *  Created on: Apr 18, 2013
 *      Author: Christian Grefe, CERN
 */

#ifndef LAYERSTACK_H_
#define LAYERSTACK_H_

#include "DD4hep/Detector.h"

#include <vector>

namespace DD4hep {
namespace Geometry {

class LayerStack {
public:
	LayerStack(const DetElement& det);
	LayerStack(const LayerStack& layerStack, const DetElement& det);
	virtual ~LayerStack();
	virtual int getNumberOfLayers() const = 0;
	virtual int getNumberOfModules(int layerIndex = 0) const = 0;
	virtual DetElement getModule(int layerIndex = 0, int moduleIndex = 0) const = 0;
	double getThickness(int layerIndex = 0, int moduleIndex = 0) const;
	double getRadiationLengths(int layerIndex = 0, int moduleIndex = 0) const;
	double getInteractionLengths(int layerIndex = 0, int moduleIndex = 0) const;
	double getTotalThickness(int moduleIndex = 0) const;
	double getTotalInteractionLengths(int moduleIndex = 0) const;
	double getTotalRadiationLengths(int moduleIndex = 0) const;
	virtual int getNumberOfSlices(int layerIndex = 0, int moduleIndex = 0) const = 0;
	virtual DetElement getSlice(int layerIndex = 0, int moduleIndex = 0, int sliceIndex = 0) const = 0;
	virtual int getNumberOfSensors(int layerIndex = 0, int moduleIndex = 0) const = 0;
	virtual DetElement getSensor(int layerIndex = 0, int moduleIndex = 0, int sensorIndex = 0) const = 0;

protected:
	DetElement det;
};

class PolyhedralCalorimeterLayerStack: public LayerStack {
public:
	PolyhedralCalorimeterLayerStack(const DetElement& det);
	PolyhedralCalorimeterLayerStack(const PolyhedralCalorimeterLayerStack& layerStack, const DetElement& det);
	virtual ~PolyhedralCalorimeterLayerStack();
	int getNumberOfLayers() const;
	int getNumberOfModules(int layerIndex = 0) const;
	DetElement getModule(int layerIndex = 0, int moduleIndex = 0) const;
	int getNumberOfSlices(int layerIndex = 0, int moduleIndex = 0) const;
	DetElement getSlice(int layerIndex = 0, int moduleIndex = 0, int sliceIndex = 0) const;
	int getNumberOfSensors(int layerIndex = 0, int moduleIndex = 0) const;
	DetElement getSensor(int layerIndex = 0, int moduleIndex = 0, int sensorIndex = 0) const;
};

} /* namespace Geometry */
} /* namespace DD4hep */
#endif /* LAYERSTACK_H_ */
