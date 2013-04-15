/*
 * Layering.h
 *
 *  Created on: Apr 6, 2013
 *      Author: Christian Grefe, CERN
 */

#ifndef LAYERING_H_
#define LAYERING_H_

#include "DD4hep/Detector.h"

#include "Exceptions.h"

#include <vector>

namespace DD4hep {
namespace Geometry {

struct LayerData: public DetElement::Object {

	double getThickness() {
		return _thickness;
	}

	double getInteractionLengths() {
		return _interactionLengths;
	}

	double getRadiationLengths() {
		return _radiationLengths;
	}

	void calculate() {
		if (children.size() == 0) {
			Box box = volume.solid();
			_thickness = box->GetDZ();
			_interactionLengths = volume.material().intLength() / _thickness;
			_radiationLengths = volume.material().radLength() / _thickness;
		} else {
			_thickness = 0.;
			_radiationLengths = 0.;
			_interactionLengths = 0.;
			std::map<std::string, DetElement>::iterator it;
			for (it = children.begin(); it != children.end(); ++it) {
				LayerData* layerData = it->second.data<LayerData>();
				layerData->calculate();
				_thickness += layerData->getThickness();
				_interactionLengths += layerData->getInteractionLengths();
				_radiationLengths += layerData->getRadiationLengths();
			}
		}
	}

protected:
	double _thickness;
	double _radiationLengths;
	double _interactionLengths;
};

}
}

#endif /* LAYERING_H_ */
