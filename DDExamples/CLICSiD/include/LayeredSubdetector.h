/*
 * LayeredSubdetector.h
 *
 *  Created on: Mar 27, 2013
 *      Author: Christian Grefe, CERN
 */

#ifndef LAYEREDSUBDETECTOR_H_
#define LAYEREDSUBDETECTOR_H_

#include "DD4hep/Detector.h"
#include "DD4hep/Shapes.h"
#include "Exceptions.h"

#include <map>
#include <sstream>
#include <vector>

namespace DD4hep {
namespace Geometry {

class LayerStack {
public:
	LayerStack(const DetElement& det) : _layerStack(det) {}
	LayerStack(const LayerStack&, const DetElement& det) : _layerStack(det) {}
	~LayerStack() {}

	int getNumberOfLayers() const;
	const DetElement& getLayer(int layerIndex) const;
	double getLayerThickness(int layerIndex) const;
	double getTotalThickness() const;
	double getInteractionLengths(int layerIndex) const;
	double getTotalInteractionLengths() const;
	double getRadiationLengths(int layerIndex) const;
	double getTotalRadiationLengths() const;

protected:
	DetElement _layerStack;

	static double getThickness(const DetElement& det);
	static double getInteractionLengths(const DetElement& det);
	static double getRadiationLengths(const DetElement& det);
};

struct LayeredSubdetector: virtual public DetElement {
	LayeredSubdetector(const DetElement& e) :
			DetElement(e), _layerStack(0) {
		getExtension();
	}
	virtual ~LayeredSubdetector() {
	}

	bool isLayered() const {
		return true;
	}

	int getNumberOfLayers() const {
		return _layerStack->getNumberOfLayers();
	}

	const DetElement& getLayer(int layerIndex) const {
		return _layerStack->getLayer(layerIndex);
	}

	double getLayerThickness(int layerIndex) const {
		return _layerStack->getLayerThickness(layerIndex);
	}

	double getSensorThickness(int layerIndex) const {
		return 0.;
	}

	double getInteractionLengths(int layerIndex) const {
		return _layerStack->getInteractionLengths(layerIndex);
	}

	double getRadiationLengths(int layerIndex) const {
		return _layerStack->getRadiationLengths(layerIndex);
	}

	double getMipEnergyLoss(int layerIndex) const {
		return 0.;
	}

	double getTotalThickness() const {
		return _layerStack->getTotalThickness();
	}

	double getTotalInteractionLengths() const {
		return _layerStack->getTotalInteractionLengths();
	}

	double getTotalRadiationLengths() const {
		return _layerStack->getTotalRadiationLengths();
	}

private:
	LayerStack* _layerStack;
	void getExtension() {
		std::cout << "Getting the extension" << std::endl;

		_layerStack = isValid() ? extension<LayerStack>() : 0;
		if (_layerStack == 0) {
			std::cout << "Failed to get the extension" << std::endl;
		}
	}
};

}
} /* namespace DD4hep */

#endif /* LAYEREDSUBDETECTOR_H_ */
