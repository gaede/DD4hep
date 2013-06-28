/*
 * Segmentation.cpp
 *
 *  Created on: Jun 27, 2013
 *      Author: Christian Grefe, CERN
 */

#include "Segmentation.h"

namespace DD4hep {
namespace Segmentation {

using std::string;

Segmentation::Segmentation(string cellEncoding) : _decoder(cellEncoding) {
}

Segmentation::Segmentation(BitField64& decoder) {
	_decoder = decoder;
}

Segmentation::~Segmentation() {

}

long64 Segmentation::getCellID(double* localPosition) const {
	return getCellID(localPosition[0], localPosition[1], localPosition[2]);
}

} /* namespace Segmentation */
} /* namespace DD4hep */
