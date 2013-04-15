/*
 * PolyhedralBarrelCalorimeter.h
 *
 *  Created on: Apr 3, 2013
 *      Author: Christian Grefe, CERN
 */

#ifndef POLYHEDRALBARRELCALORIMETER_H_
#define POLYHEDRALBARRELCALORIMETER_H_

#include "Calorimeter.h"
#include "BarrelDetector.h"
#include "PolyhedralDetector.h"

namespace DD4hep {
namespace Geometry {

struct PolyhedralBarrelCalorimeter: public Calorimeter, public BarrelDetector, public PolyhedralDetector {
	PolyhedralBarrelCalorimeter(const DetElement& e) : DetElement(e), Calorimeter(e), BarrelDetector(e), PolyhedralDetector(e) {}
	~PolyhedralBarrelCalorimeter() {}

	double getRMin() const {
		return getPolyhedra()->GetRmin(0);
	}
	double getRMax() const {
		return getPolyhedra()->GetRmax(0);
	}
	double getZMin() const {
		return getPolyhedra()->GetZ(0);
	}
	double getZMax() const {
		return getPolyhedra()->GetZ(1);
	}
};
} /* namespace Geometry */
} /* namespace DD4hep */
#endif /* POLYHEDRALBARRELCALORIMETER_H_ */
