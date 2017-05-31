//==========================================================================
//  AIDA Detector description implementation for LCD
//--------------------------------------------------------------------------
// Copyright (C) Organisation europeenne pour la Recherche nucleaire (CERN)
// All rights reserved.
//
// For the licensing terms see $DD4hepINSTALL/LICENSE.
// For the list of contributors see $DD4hepINSTALL/doc/CREDITS.
//
// @author F.Gaede, DESY
// @date May, 2017
//==========================================================================

// Framework include files
#include "DD4hep/LCDD.h"
#include "DD4hep/DDTest.h"

#include "DD4hep/DD4hepUnits.h"
#include "DD4hep/BitField64.h"
#include "DDRec/CellIDPositionConverter.h"

#include "lcio.h"
#include "IO/LCReader.h"
#include "EVENT/LCEvent.h"
#include "EVENT/LCCollection.h"
#include "EVENT/SimCalorimeterHit.h"

#include <sstream>

using namespace std ;
using namespace DD4hep ;
using namespace DD4hep::Geometry;
using namespace DD4hep::DDRec ;

using namespace lcio;


static DDTest test( "cellid_position_converter" ) ; 

//=============================================================================

const double epsilon = dd4hep::micrometer ;

double dist( const Position& p0, const Position& p1 ){
  Position p2 = p1 - p0 ;
  return p2.r() ;
} 


int main_wrapper(int argc, char** argv ){

  if( argc < 3 ) {
    std::cout << " usage: test_cellid_position_converter compact.xml lcio_file.slcio" << std::endl ;
    exit(1) ;
  }
  
  std::string inFile =  argv[1] ;

  LCDD& lcdd = LCDD::getInstance();

  lcdd.fromCompact( inFile );

  CellIDPositionConverter idposConv( lcdd )  ;

  
  //---------------------------------------------------------------------
  //    open lcio file with SimCalorimeterHits
  //---------------------------------------------------------------------

  std::string lcioFileName = argv[2] ;

  LCReader* rdr = LCFactory::getInstance()->createLCReader() ;
  rdr->open( lcioFileName ) ;

  LCEvent* evt = 0 ;


  // use only hits from these collections
  std::set< std::string > subset = {} ;
  //{"BeamCalCollection" } ; //EcalBarrelCollection" } ; //"HcalBarrelRegCollection"} ; 


  // ignore all hits from these collections
  std::set< std::string > subsetIgnore = {} ;
  //{"HCalBarrelRPCHits","HCalECRingRPCHits","HCalEndcapRPCHits" } ;
  
  while( ( evt = rdr->readNextEvent() ) != 0 ){

    const std::vector< std::string >& colNames = *evt->getCollectionNames() ;

    for(unsigned icol=0, ncol = colNames.size() ; icol < ncol ; ++icol ){

      LCCollection* col =  evt->getCollection( colNames[ icol ] ) ;

      std::string typeName = col->getTypeName() ;

      if( typeName != lcio::LCIO::SIMCALORIMETERHIT )
        continue ;

      if( !subset.empty() && subset.find( colNames[icol] ) ==  subset.end()  ) 
	continue ;

      if( !subsetIgnore.empty() && subsetIgnore.find( colNames[icol] ) !=  subsetIgnore.end()  ) 
       	continue ;

      std::cout << "  -- testing collection : " <<  colNames[ icol ] << std::endl ;

      std::string cellIDEcoding = col->getParameters().getStringVal("CellIDEncoding") ;
      
      DD4hep::BitField64 idDecoder( cellIDEcoding ) ;

      int nHit = col->getNumberOfElements() ;
      
      for(int i=0 ; i< nHit ; ++i){
	
        SimCalorimeterHit* sHit = (SimCalorimeterHit*) col->getElementAt(i) ;
	
        DD4hep::long64 id0 = sHit->getCellID0() ;
        DD4hep::long64 id1 = sHit->getCellID1() ;
	DD4hep::long64 id = ( id1 << 32 | id0 ) ;
	
        idDecoder.setValue( id ) ;
	

	Position point( sHit->getPosition()[0]* dd4hep::mm , sHit->getPosition()[1]* dd4hep::mm ,  sHit->getPosition()[2]* dd4hep::mm ) ;
	

	// ====== test cellID to position and positio to cellID conversion  ================================
	
	//	CellID idFromDecoder = idposConv.cellID( point ) ;

	Position pointFromDecoder = idposConv.position( id ) ;

	//	test( idFromDecoder , id  , " compare ids:  " ) ;

	double d = dist(pointFromDecoder, point)  ;
	std::stringstream sst ;
	sst << " dist " << d << " ( " <<  pointFromDecoder << " ) - ( " << point << " )" ;

	test( d < epsilon , true  , sst.str()  ) ;
	
      }
    }
    
  }
  return 0;
}

//=============================================================================
#include "main.h"
