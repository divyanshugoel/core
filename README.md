Fleet Server
==============

Components
============
1. Server.
2. Visualization of the current Fleet.
3. NodeGraph.
4. Simulation.

Dependencies
============

The following dependencies are required by the system:
1. CMake >= 3.7.2
2. Git
3. Docker-compose [Optional]
4. Qt [Optional]
5. System Dependencies [DESKTOP ONLY]

INSTALLATION
============

Use the following command to install the above dependencies:

``` {.sourceCode .bash}
sudo chmod +x INSTALL_DEP
./INSTALL_DEP
```

SYSTEM DEPENDENCIES
============

``` {.sourceCode .bash}
sudo snap install cmake
sudo apt get install -y build-essential git
# DESKTOP ONLY
sudo apt get install -y libxinerama-dev libxcursor-dev libglu1-mesa-dev xorg-dev
```

BUILD
============
The current codebase doesn't build in this form. This is only for viewing purposes. It is non-critical  part of a bigger codebase.