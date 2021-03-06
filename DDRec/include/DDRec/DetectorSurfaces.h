#ifndef rec_DetectorSurfaces_H_
#define rec_DetectorSurfaces_H_

#include "DDRec/Surface.h"

namespace dd4hep {
  namespace rec {

    /** View on DetElements for accessing the surfaces assigned to this DetElement
     *  in detector construction.
     *
     * @author F.Gaede, DESY
     * @date Apr, 10 2014
     * @version $Id$
     */
    class DetectorSurfaces: virtual public DetElement {

    public:
      typedef DetElement DetElement;

      DetectorSurfaces(const DetElement& e);

      virtual ~DetectorSurfaces();

      /// get the list of surfaces added to this DetElement
      const SurfaceList& surfaceList() { return *_sL ; }

    protected :
      SurfaceList* _sL ;

      /// initializes surfaces from VolSurfaces assigned to this DetElement in detector construction
      void initialize() ;

    };

  } /* namespace rec */
} /* namespace dd4hep */



#endif // rec_DetectorSurfaces_H_
