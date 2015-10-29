/**
 *  The class for the Visualisation Manager
 *  (Shamelessly copied from a G4 example)
 *
 * @author    Nikolaos Karastathis < nkarast .at. cern .dot. ch >
 * @version   v2.0
 */

#ifndef UMVisManager_h
   #define UMVisManager_h 1

   #ifdef G4VIS_USE

      #include "G4VisManager.hh"

      class UMVisManager: public G4VisManager {
         public:
            UMVisManager ();

         private:
            void RegisterGraphicsSystems ();
      };

   #endif
#endif
