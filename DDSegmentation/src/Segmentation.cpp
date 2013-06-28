/*
 * Segmentation.cpp
 *
 *  Created on: Jun 27, 2013
 *      Author: Christian Grefe, CERN
 */

#include "Segmentation.h"

#include <algorithm>

namespace DD4hep {
namespace Segmentation {

using std::copy;
using std::string;
using std::vector;

Segmentation::Segmentation(const string& cellEncoding) : _decoder(cellEncoding) {
}

Segmentation::Segmentation(const BitField64& decoder) : _decoder(decoder.fieldDescription()) {

}

Segmentation::~Segmentation() {

}

long64 Segmentation::getCellID(const vector<double>& localPosition) const {
	return getCellID(localPosition[0], localPosition[1], localPosition[2]);
}

long64 Segmentation::getCellID(double* localPosition) const {
	return getCellID(localPosition[0], localPosition[1], localPosition[2]);
}

} /* namespace Segmentation */
} /* namespace DD4hep */
