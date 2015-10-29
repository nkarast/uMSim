echo 'making clean'
make clean

echo 'sourcing gcc 4.9.0'
#source /afs/cern.ch/sw/lcg/contrib/gcc/4.9.1/x86_64-slc6/setup.sh
source /afs/cern.ch/sw/lcg/external/gcc/4.9/x86_64-slc6-gcc49-opt/setup.sh
echo 'sourcing root 5.34.25 gcc49'
source /afs/cern.ch/sw/lcg/app/releases/ROOT/5.34.25/x86_64-slc6-gcc49-opt/root/bin/thisroot.sh


export CXX=`which g++`; export CC=`which gcc`
echo $CXX $CC
echo 'sourcing geant4'
GEANT4_DIR=/afs/cern.ch/sw/lcg/external/geant4/10.1/x86_64-slc6-gcc49-opt
echo 'sourcing CMake-setup.sh'
source ${GEANT4_DIR}/CMake-setup.sh
#echo 'sourcing geant4make'
#source ${GEANT4_DIR}/share/Geant4-10.1.0/geant4make/geant4make.sh
#echo 'sourcing datasets'
#source ${GEANT4_DIR}/../setup_g4datasets.sh

echo 'cmaking mylar'
cmake -DGEANT4_DIR=${GEANT4_DIR}/lib64/Geant4-10.1.0/ ../uMSim

echo 'making...'
make

# /afs/cern.ch/sw/lcg/external/geant4/10.1/x86_64-slc6-gcc49-dbg-MT
