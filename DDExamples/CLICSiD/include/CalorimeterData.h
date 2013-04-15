/*
 * CalorimeterData.h
 *
 *  Created on: Apr 6, 2013
 *      Author: Christian Grefe, CERN
 */

#ifndef CALORIMETERDATA_H_
#define CALORIMETERDATA_H_

#include "DD4hep/Detector.h"

#include <vector>

namespace DD4hep {
namespace Geometry {

struct CalorimeterData: public DetElement::Object {
	DetElement layerStack;
};

}
}

#endif /* CALORIMETERDATA_H_ */
