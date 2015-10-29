import os
import sys

init_name = "uMSim_45degBeam_fixedDistance_QGSP_BERT_10M_5dot1MeV_"
#init_name = "atest_"
end_name  = ".root"

namelst = ["000", "001", "002", "003", "004", "005", "006", "007", "008","009","010", "011","012","013","014","015","016","017", "018","019","020"]#,"021","022","023","024","025","026","027", "028","029","030","031","032","033","034","035","036","037", "038","039","040","041","042","043","044","045","046","047", "048","049","050" ]

#namelst = ["100", "101", "102", "103", "104", "105", "106", "107", "108","109","110", "111","112","113","114","115","116","117", "118","119","120","121","122","123","124","125","126","127", "128","129","130","131","132","133","134","135","136","137", "138","139","140","141","142","143","144","145","146","147", "148","149","150" ]

for add_name in namelst:
    filename = init_name+add_name+end_name
    submitname = "submit"+add_name+".sh"
    outfile = open(submitname, 'write')

    outfile.write("echo '######################################'\n")
    outfile.write("echo '#    Setting up the environment      #'\n")
    outfile.write("echo '######################################'\n")
    
    outfile.write("echo 'source gcc 4.9.0'\n")
    outfile.write("source /afs/cern.ch/sw/lcg/external/gcc/4.9/x86_64-slc6-gcc49-opt/setup.sh\n")
    
    outfile.write("echo 'source root 5.34.25 gcc 4.9'\n")
    outfile.write("source /afs/cern.ch/sw/lcg/app/releases/ROOT/5.34.25/x86_64-slc6-gcc49-opt/root/bin/thisroot.sh\n")
    
    outfile.write("export CXX=`which g++`; export CC=`which gcc`\n")
    outfile.write("echo $CXX $CC\n")
    outfile.write("echo 'sourcing geant4'\n")
    outfile.write("GEANT4_DIR=/afs/cern.ch/sw/lcg/external/geant4/10.1/x86_64-slc6-gcc49-opt\n")
    outfile.write("echo 'sourcing CMake-setup.sh'\n")
    outfile.write("source ${GEANT4_DIR}/CMake-setup.sh\n")
    
    
    outfile.write("echo '######################################'\n")
    outfile.write("echo '#         Copying the project        #'\n")
    outfile.write("echo '######################################'\n")
    
    outfile.write("echo 'cp build dir'\n")
    outfile.write("cp -R /afs/cern.ch/work/n/nkarast/uMSim-build .\n")
 
    outfile.write("cd uMSim-build/\n")
    outfile.write("chmod +x mylar\n")
    
    outfile.write("echo 'executing the mylar'\n")
    outfile.write("./mylar | tee out.log\n")
    
    last_line = "xrdcp output.root root://eosatlas//eos/atlas/user/n/nkarast/GeantOutputs/uMSim/Energy5dot1MeV/"+filename+"\n"
#    outfile.write("xrdcp output.root root://eosatlas//eos/atlas/user/n/nkarast/GeantOutputs/mylar2D/${name}\n")
    outfile.write(last_line)
#    logfilename = filename+"\b\b\b\b"+"log"
#    last_line2 = "xrdcp out.log root://eosatlas//eos/atlas/user/n/nkarast/GeantOutputs/mylar2D_angularBeam/"+logfilename+"\n"
#    outfile.write("xrdcp output.root root://eosatlas//eos/atlas/user/n/nkarast/GeantOutputs/mylar2D/${name}\n")
#    outfile.write(last_line2)

 
    outfile.close()
    cmd1 = "chmod +x "+submitname
    os.system(cmd1)
    cmd2 = "bsub -q 2nd "+submitname
    os.system(cmd2)
    os.system("sleep 1")

    print "File ", submitname, " closed."
