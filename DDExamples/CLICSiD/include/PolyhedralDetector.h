/*
 * PolyhedralDetector.h
 *
 *  Created on: Apr 3, 2013
 *      Author: Christian Grefe, CERN
 */

#ifndef POLYHEDRALDETECTOR_H_
#define POLYHEDRALDETECTOR_H_

#include "DD4hep/Detector.h"

namespace DD4hep {
namespace Geometry {
struct PolyhedralDetector : virtual public DetElement {
	PolyhedralDetector(const DetElement& e) : DetElement(e) {}
	virtual ~PolyhedralDetector() {}

	int getNSides() const {
		return getPolyhedra()->GetNedges();
	}
protected:
	PolyhedraRegular getPolyhedra() const {
		PolyhedraRegular polyhedra(volume().solid());
		return polyhedra;
	}
};
} /* namespace Geometry */
} /* namespace DD4hep */
#endif /* POLYHEDRALDETECTOR_H_ */
