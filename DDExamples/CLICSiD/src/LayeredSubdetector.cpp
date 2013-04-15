/*
 * LayeredSubdetector.cpp
 *
 *  Created on: Apr 9, 2013
 *      Author: Christian Grefe, CERN
 */

#include "LayeredSubdetector.h"
#include "DD4hep/LCDD.h"

namespace DD4hep {
namespace Geometry {

int LayerStack::getNumberOfLayers() const {
	return _layerStack.children().size();
}

const DetElement& LayerStack::getLayer(int layerIndex) const  {
	DetElement::Children::const_iterator it;
	for (it = _layerStack.children().begin(); it != _layerStack.children().end(); ++it) {
		if (it->second._data().id == layerIndex) {
			return it->second;
		}
	}
	std::stringstream err;
	err << "Layer index not found: " << layerIndex;
	throw OutsideGeometryException(err.str());
}

double LayerStack::getLayerThickness(int layerIndex) const {
	return getThickness(getLayer(layerIndex));
}

double LayerStack::getTotalThickness() const {
	return getThickness(_layerStack);
}

double LayerStack::getInteractionLengths(int layerIndex) const {
	return getInteractionLengths(getLayer(layerIndex));
}

double LayerStack::getTotalInteractionLengths() const {
	return getInteractionLengths(_layerStack);
}

double LayerStack::getRadiationLengths(int layerIndex) const {
	return getRadiationLengths(getLayer(layerIndex));
}

double LayerStack::getTotalRadiationLengths() const {
	return getRadiationLengths(_layerStack);
}

double LayerStack::getThickness(const DetElement& det) {
	return Box(det.volume().solid())->GetDZ();
}

double LayerStack::getInteractionLengths(const DetElement& det) {
	double interactionLengths = 0.;
	if (!det.volume().material()) {
		DetElement::Children::const_iterator it;
		for (it = det.children().begin(); it != det.children().end(); ++it) {
			DetElement child = it->second;
			interactionLengths += getInteractionLengths(child);
		}
	} else {
		//interactionLengths += det.volume().material().intLength() / Box(det.volume().solid())->GetDZ();
		interactionLengths += 0.;
	}
	return interactionLengths;
}

double LayerStack::getRadiationLengths(const DetElement& det) {
	double radiationLengths = 0.;
	std::cout << det.name() << std::endl;
	DetElement::Children children = det.children();
	if (!children.empty()) {
		DetElement::Children::const_iterator it;
		for (it = det.children().begin(); it != det.children().end(); ++it) {
			DetElement child = it->second;
			radiationLengths += getRadiationLengths(child);
			std::cout << radiationLengths << std::endl;
		}
	} else {
		Material material = det.volume().material();
		Box box = det.volume().solid();
		std::cout << "Material: " << material.toString() << std::endl;
		std::cout << "Radiation length: " << material.radLength() << std::endl;
		std::cout << "Thickness: " << box->GetDZ() << std::endl;
		std::cout << "Material: " << material.toString() << std::endl;
		std::cout << "Pointer: " << material.ptr() << std::endl;
		std::cout << "Radiation length: " << material.radLength() << std::endl;
		std::cout << "Thickness: " << box->GetDZ() << std::endl;
		radiationLengths += material.radLength() / box->GetDZ();
	}
	std::cout << "Returning " << radiationLengths << std::endl;
	return radiationLengths;
}

}
}

