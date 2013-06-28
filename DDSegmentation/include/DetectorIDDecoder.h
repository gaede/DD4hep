/*
 * DetectorIDDecoder.h
 *
 *  Created on: Jun 27, 2013
 *      Author: Christian Grefe, CERN
 */

#ifndef DETECTORIDDECODER_H_
#define DETECTORIDDECODER_H_

#include "IDDecoder.h"

namespace DD4hep {
namespace Segmentation {

class DetectorIDDecoder: public IDDecoder {
public:
	DetectorIDDecoder(std::string decoderString) : IDDecoder(decoderString) {}
	virtual ~DetectorIDDecoder();

	long64 getDetectorID(const long64& cellID) const;
};

} /* namespace Segmentation */
} /* namespace DD4hep */
#endif /* DETECTORIDDECODER_H_ */
