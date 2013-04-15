/*
 * BarrelDetector.h
 *
 *  Created on: Apr 3, 2013
 *      Author: Christian Grefe, CERN
 */

#ifndef BARRELDETECTOR_H_
#define BARRELDETECTOR_H_

#include "DD4hep/Detector.h"

namespace DD4hep {

namespace Geometry {
struct BarrelDetector: virtual public DetElement {

	BarrelDetector() {};
	BarrelDetector(const DetElement& e) : DetElement(e) {};
	virtual ~BarrelDetector() {}

	virtual bool isBarrel() const {
		return true;
	}

	virtual double getRMin() const = 0;
	virtual double getRMax() const = 0;
	virtual double getZMin() const = 0;
	virtual double getZMax() const = 0;
};

} /* namespace Geometry */
} /* namespace DD4hep */
#endif /* BARRELDETECTOR_H_ */
