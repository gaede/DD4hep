/*
 * Layering.h
 *
 *  Created on: Apr 6, 2013
 *      Author: Christian Grefe, CERN
 */

#ifndef BARRELDETECTORDATA_H_
#define BARRELDETECTORDATA_H_

#include "DD4hep/Detector.h"

#include <vector>

namespace DD4hep {
namespace Geometry {

struct BarrelDetectorData: public DetElement::Object {
	double rMin;
	double rMax;
	double zMin;
	double zMax;
};

}
}

#endif /* BARRELDETECTORDATA_H_ */
