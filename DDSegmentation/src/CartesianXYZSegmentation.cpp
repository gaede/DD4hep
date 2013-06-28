/*
 * CartesianXYZSegmentation.cpp
 *
 *  Created on: Jun 28, 2013
 *      Author: Christian Grefe, CERN
 */

#include "CartesianXYZSegmentation.h"

namespace DD4hep {
namespace Segmentation {

using std::string;

CartesianXYZSegmentation::CartesianXYZSegmentation(const string& cellEncoding, double cellSizeX, double cellSizeY, double cellSizeZ,
		double offsetX, double offsetY, double offsetZ) :
		CartesianXYSegmentation(cellEncoding, cellSizeX, cellSizeY, offsetX, offsetY), _cellSizeZ(cellSizeZ), _offsetZ(offsetZ) {

}

CartesianXYZSegmentation::CartesianXYZSegmentation(BitField64& decoder, double cellSizeX, double cellSizeY, double cellSizeZ,
		double offsetX, double offsetY, double offsetZ) :
		CartesianXYSegmentation(decoder, cellSizeX, cellSizeY, offsetX, offsetY), _cellSizeZ(cellSizeZ), _offsetZ(offsetZ) {

}

CartesianXYZSegmentation::~CartesianXYZSegmentation() {

}

double* CartesianXYZSegmentation::getLocalPosition(const long64& cellID) const {
	_decoder.setValue(cellID);
	double x = binToPosition(_decoder["x"].value(), _cellSizeX, _offsetX);
	double y = binToPosition(_decoder["y"].value(), _cellSizeY, _offsetY);
	double z = binToPosition(_decoder["z"].value(), _cellSizeZ, _offsetZ);
	return {x, y, 0.0};
}

long64 CartesianXYZSegmentation::getCellID(double x, double y, double z) const {
	_decoder.reset();
	_decoder["x"] = positionToBin(x, _cellSizeX, _offsetX);
	_decoder["y"] = positionToBin(y, _cellSizeY, _offsetY);
	_decoder["z"] = positionToBin(z, _cellSizeZ, _offsetZ);
	return _decoder.getValue();
}

} /* namespace Segmentation */
} /* namespace DD4hep */
