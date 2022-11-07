#!/bin/bash

############################################################
# Help                                                     #
############################################################

Help()
{
   # Display Help
   echo "This function is to build the fleet system and create a symlink for it in the same folder."
   echo "By default runs the cmake and build." 
   echo
   echo "Syntax: build [-I|c|b|f|s|h|V]"
   echo "options:"
   echo "I     Install Dependencies "
   echo "c     Only run Setup "
   echo "b     Setup and Build Only"
   echo "f     force a clean build."
   echo "s     Setup, build and create the symlink [Default]"
   echo "h     Print this Help."
   echo "V     Print software version and exit."
   echo
}

############################################################
# Create Folder and run CMakeLists.txt                     #
############################################################

Setup()
{
  # Create the build folder if it does not exists already.   
  if [ ! "$EUID" -ne 0 ]; then
    echo "Please run as normal user, not as root."
    exit
  fi
  buildDir="$DIR/build"
  if [ ! -d "$buildDir" ]; then
    mkdir -p "$buildDir"
  fi
  # Check if it is server or desktop then pass the option. 
  CheckIfDesktop
  # If you need Qt you can provide the same by -DCMAKE_PREFIX_PATH="External/Qt/glnxa64/5.11.0/gcc_64" 
  # Optional: set the build type to release -DCMAKE_BUILD_TYPE=Release
  if [ "$IsDesktop" -eq 1 ]; then  
    cmake -S $DIR -B "$buildDir"
  else
    cmake -S $DIR -B "$buildDir" -DBUILD_SERVER=ON
  fi
}

############################################################
# Run the make command                                     #
############################################################

MakeFunction()
{
  if [ ! "$EUID" -ne 0 ]; then
    echo "Please run as normal user, not as root."
    exit
  fi
  buildDir="$DIR/build"
  makeFile="$DIR/build/Makefile"
  # Check if the build foler exists.
  if [ ! -d "$buildDir" ]; then
    Setup
  fi
  # Check if the Makefile exists or not
  if [ ! -d "$makeFile" ]; then
    Setup
  fi
  # Number of threads need to be optional. 
  make --directory="$buildDir" -j$(nproc) --no-print-directory
}

############################################################
# Run the make install command                             #
############################################################

MakeInstall()
{
  buildDir="$DIR/build"
  fleetServer="$DIR/build/src/fleetServer"
  # Check if the code is built or not. 
  # Check if the build folder exists.
  if [ ! -d "$buildDir" ]; then
    MakeFunction
  fi
  # Check if executable exists. 
  if [ ! -d "$fleetServer" ]; then
    MakeFunction
  fi
  # Set the cmake install prefix here as an argument if it exists. 
  make --directory="$buildDir" -j$(nproc) --no-print-directory install
}

############################################################
# Create the shortcut for the project                      #
############################################################

MakeSymlink()
{
  fleetServer="$DIR/build/src/fleetServer"
  # Check if executable exists if not then build the code
  if [ ! -d "$fleetServer" ]; then
    MakeFunction
  fi
  ln -s "$fleetServer" "$DIR/fleetServer"
}

############################################################
# print the version of the software                        #
############################################################

PrintVersion()
{
  fleetServer="$DIR/build/src/fleetServer"
  # Check if executable exists if not then build the code
  if [ ! -d "$fleetServer" ]; then
    make --directory="$buildDir" -j$(nproc) --no-print-directory
  fi
  "./$fleetServer" --version
}

############################################################
# CleanBuild                                               #
############################################################

CleanBuild()
{
  rm -rf build
}

############################################################
# CleanBuild                                               #
############################################################


CheckIfDesktop()
{
    IsDesktop=1

    displayManager=(
      'xserver-common' # X Window System (X.Org) infrastructure
      'xwayland' # Xwayland X server
    )
    for i in "${displayManager[@]}"; do
      dpkg-query --show --showformat='${Status}\n' $i 2> /dev/null | grep "install ok installed" &> /dev/null
      if [[ $? -eq 0 ]]; then
        IsDesktop=1
      fi
    done
}

############################################################
# Install Dependencies                                     #
############################################################
# TODO: replace ./ with pwd relative to the linuxBuild.sh
InstallDep()
{
  CheckIfDesktop
  if [ "$EUID" -ne 0 ]; then
    echo "Please run as root."
    exit
  fi
  if [ "$IsDesktop" -eq 0 ]; then  
    chmod a+x scripts/installLocal.sh
    ./scripts/installLocal.sh
  else
    chmod a+x scripts/installServer.sh
    ./scripts/installServer.sh
  fi
  chmod a+x scripts/getDocker.sh
  ./scripts/getDocker.sh
  
}

############################################################
# Main program                                             #
############################################################

############################################################
# Process the input options. Add options as needed.        #
############################################################


DIR="$(dirname "${BASH_SOURCE[0]}")"
DIR="$(realpath "${DIR}")"

# Get the options
while getopts ":IcbfshV:" option; do
   case $option in 
      h) # display Help"
        Help
        exit;;

      I) #install dependencies
        InstallDep
        exit;;

      c) # create the build folder and run cmake.
        Setup
        exit;;

      b) # build the code. 
        MakeFunction
        exit;;

      s) # make the symlink
        MakeSymlink
        exit;;

      V) # print the vertsion.      
        PrintVersion
        exit;;

      f) # do a clean build
        CleanBuild
        MakeFunction
        exit;;

      \?) # Invalid option
        Help
        echo "Error: Invalid option"
        exit;;

      *) #default
        MakeFunction
        exit;;
      
   esac
   exit;
done

# Default mode of operation. If no argument is provided. 
if (( $OPTIND == 1 )); then
  MakeFunction
fi