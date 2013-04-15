/*
 * CLICSiDCalorimeterReco.cpp
 *
 *  Created on: Apr 5, 2013
 *      Author: Christian Grefe, CERN
 */

#include "DD4hep/LCDD.h"
#include "BarrelDetector.h"
#include "PolyhedralBarrelCalorimeter.h"
#include "Calorimeter.h"

using namespace std;
using namespace DD4hep;
using namespace Geometry;

int main(int argc,char** argv)  {

	LCDD& lcdd = LCDD::getInstance();
	lcdd.fromCompact(argv[1]);

	PolyhedralBarrelCalorimeter calorimeter = lcdd.detector("EcalBarrel");
	std::string delimiter = "-------------------------------------\n";

	cout << delimiter << "Calorimeter interface:" << endl;
	cout << "\tNumber of layers: " << calorimeter.getNumberOfLayers() << endl;
	cout << "\tTotal thickness: " << calorimeter.getTotalThickness() << endl;
	cout << "\tTotal radiation lengths: " << calorimeter.getTotalRadiationLengths() << endl;
	cout << "\tTotal interaction lengths: " << calorimeter.getTotalInteractionLengths() << endl;

	cout << delimiter << "Barrel interface:" << endl;
	cout << "\tInner radius: " << calorimeter.getRMin() << " mm" << endl;
	cout << "\tOuter radius: " << calorimeter.getRMax() << " mm" << endl;
	cout << "\tMinimum z: " << calorimeter.getZMin() << " mm" << endl;
	cout << "\tMaximum z: " << calorimeter.getZMax() << " mm" << endl;

	cout << delimiter << "Polyhedra interface:" << endl;
	cout << "\tNumber of sides: " << calorimeter.getNSides() << endl;
	return 0;
}
