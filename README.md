
# uMSim = A Geant4 Simulation of the MicroMeGaS detector under various beams
by Nikos Karastathis

The basic software simulates the micromegas (Tmm prototype) detector under neutron beam in 45deg angle. Other configurations are possible and the most common ones are under the respective directory.

* doc/  -> Documentation in HTML and Latex including UML
* include/ -> header files
* macros/ -> some macros to process the ROOT files generated
* otherConfigurations -> the files that are necessary for configurations other than neutrons
* src/ -> the C++ files
* uMSim.cc -> the main function + visualisation proc
* CMakeLists.txt -> the lists for CMake-ing the project
* doxygen_config.conf -> the Doxygen configuration file for customizing the docs
