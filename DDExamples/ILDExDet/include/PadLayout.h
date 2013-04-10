// $Id$
//====================================================================
//  AIDA Detector description implementation for LCD
//--------------------------------------------------------------------
//
//  Author     : A.Muennich
//
//====================================================================
#ifndef PadLayout_H
#define PadLayout_H

#include <string>
#include <vector> 
#include <sstream>
#include <DD4hepExceptions.h> 

#include "gear/PadRowLayout2D.h"

namespace DD4hep {
  
  //  typedef gear::PadRowLayout2D  PadLayout ;
 
  struct PadLayout : public gear::PadRowLayout2D {

    /// Default destructor
    virtual ~PadLayout() {}
    

    // FIXME: empty default implementations for unimplemented functions :
    virtual bool isInsidePad(double c0, double c1) const { throwNIE() ; };
    virtual int getCoordinateType() const { throwNIE() ; };
    virtual int getPadLayoutImplType() const { throwNIE() ; };
    virtual int getPadLayoutType() const { throwNIE() ; };
    virtual const std::vector<double>  & getPlaneExtent() const { throwNIE() ; };
    virtual double getPadHeight(int padIndex) const { throwNIE() ; };
    virtual bool isInsidePad(double c0, double c1, int padIndex) const { throwNIE() ; };
    virtual const std::vector<int>  & getPadsInRow(int rowNumber) const { throwNIE() ; };
    virtual double getPadWidth(int padIndex) const { throwNIE() ; };
    virtual PadRowLayout2D * clone() const { throwNIE() ; };
    virtual int getPadShape() const { throwNIE() ; };
    virtual double getDistanceToPad(double c0, double c1, int padIndex) const { throwNIE() ; };
    

  //   /** The type of pad layout (segmentation) on this module.
  //    */
    virtual std::string getPadType() const{
      std::stringstream s ; s << getPadType() ;
      return s.str() ;
    }

  //   /** The total number of pads on this module.
  //    */
  //   virtual int getNPads() const=0;
  //   /** The total number of rows on this module.
  //    */
  //   virtual int getNRows() const=0;
  //   /** The number of pads in a given row on this module.
  //    */
    virtual int  getNPadsInRow(int row)const{
      return getPadsInRow( row ).size() ;
    }

  //    /** The height of a given row on this module.
  //    */
  //   virtual double getRowHeight (int row) const=0;
  //   /** The pad pitch (sensitive plus surroundings = effective size) of a given pad on this module.
  //    */
  //   virtual double getPadPitch (int padIndex) const=0;
  //   /** The row which contains the given pad on this module.
  //    */
  //   virtual int getRowNumber (int padIndex) const=0;
  //   /** The position of a pad within the row on this module.
  //    */
  //   virtual int	getPadNumber (int padIndex) const=0;
  //   /** The pad id for a pad with padNum in row with rowNum on this module.
  //    */
  //   virtual int getPadIndex (int rowNum, int padNum)const=0;
  //   /** The right neighbour of a pad with the given index on this module.
  //    */
  //   virtual int	getRightNeighbour (int padIndex) const=0;
  //   /** The left neighbour of a pad with the given index on this module.
  //    */
  //   virtual int	getLeftNeighbour (int padIndex) const=0;
  //   /** The center of a pad on this module in global coordinates.
  //    */
  //    virtual std::vector<double>	getPadCenter (int padIndex) const=0;
  //
  //   /** Closest pad to a given location.
  //    */
  //   virtual int getNearestPad (double c0, double c1) const=0;

  };


}
#endif

