/*
 * CartesianXYSegmentation.cpp
 *
 *  Created on: Jun 28, 2013
 *      Author: Christian Grefe, CERN
 */

#include "CartesianXYSegmentation.h"

namespace DD4hep {
namespace Segmentation {

using std::string;

CartesianXYSegmentation::CartesianXYSegmentation(const string& cellEncoding, double cellSizeX, double cellSizeY,
		double offsetX, double offsetY) :
		CartesianSegmentation(cellEncoding), _cellSizeX(cellSizeX), _cellSizeY(cellSizeY), _offsetX(offsetX), _offsetY(
				offsetY) {

}

CartesianXYSegmentation::CartesianXYSegmentation(BitField64& decoder, double cellSizeX, double cellSizeY,
		double offsetX, double offsetY) :
		CartesianSegmentation(decoder), _cellSizeX(cellSizeX), _cellSizeY(cellSizeY), _offsetX(offsetX), _offsetY(
				offsetY) {

}

CartesianXYSegmentation::~CartesianXYSegmentation() {

}

double* CartesianXYSegmentation::getLocalPosition(const long64& cellID) const {
	_decoder.setValue(cellID);
	double x = binToPosition(_decoder["x"].value(), _cellSizeX, _offsetX);
	double y = binToPosition(_decoder["y"].value(), _cellSizeY, _offsetY);
	return {x, y, 0.0};
}

long64 CartesianXYSegmentation::getCellID(double x, double y, double z) const {
	_decoder.reset();
	_decoder["x"] = positionToBin(x, _cellSizeX, _offsetX);
	_decoder["y"] = positionToBin(y, _cellSizeY, _offsetY);
	return _decoder.getValue();
}

} /* namespace Segmentation */
} /* namespace DD4hep */
