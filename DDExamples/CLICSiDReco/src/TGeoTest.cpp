/*
 * CLICSiDCalorimeterReco.cpp
 *
 *  Created on: Apr 5, 2013
 *      Author: Christian Grefe, CERN
 */

#include "TGeoManager.h"

#include "DD4hep/LCDD.h"
#include "DD4hep/Detector.h"

using namespace std;
using namespace DD4hep;
using namespace Geometry;

int main(int argc,char** argv)  {
	LCDD& lcdd = LCDD::getInstance();
	lcdd.fromCompact(argv[1]);

	DetElement calorimeter = lcdd.detector("EcalBarrel");
	TGeoManager* manager = calorimeter.volume()->GetGeoManager();
	TGeoMedium* medium = manager->GetMedium("Silicon");
	TGeoMaterial* material = medium->GetMaterial();
	cout << "Test stand-alone TGeoManager" << endl;
	cout << medium->GetName() << endl;
	cout << material->GetRadLen() << endl;
	cout << material->GetRadLen() << endl;


	DetElement stave = calorimeter.child("stave0");
	DetElement layer = stave.child("layer0");
	DetElement slice = layer.child("slice0");

	Material materialHandle = slice.volume().material();
	cout << materialHandle.radLength() << endl;
	TGeoMaterial* sliceMaterial = materialHandle->GetMaterial();
	cout << sliceMaterial << endl;
	cout << sliceMaterial->GetName() << endl;
	cout << sliceMaterial->GetRadLen() << endl;
	cout << sliceMaterial->GetRadLen() << endl;
	return 0;
}
