/*
 * Segmentation.h
 *
 *  Created on: Jun 27, 2013
 *      Author: Christian Grefe, CERN
 */

#ifndef SEGMENTATION_H_
#define SEGMENTATION_H_

#include "BitField64.h"

#include <string>

namespace DD4hep {
namespace Segmentation {

class Segmentation {
public:
	Segmentation(const std::string& cellEncoding);
	Segmentation(BitField64& decoder);
	virtual ~Segmentation();

	double* getLocalPosition(const long64& cellID) const = 0;
	long64 getCellID(double x, double y, double z) const = 0;
	long64 getCellID(double* localPosition) const;
protected:
	mutable BitField64 _decoder;
};

} /* namespace Segmentation */
} /* namespace DD4hep */
#endif /* SEGMENTATION_H_ */
