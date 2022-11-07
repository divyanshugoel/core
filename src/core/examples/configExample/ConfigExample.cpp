// Copyright 2022 Divyanshu Goel.
#include <core/core/Core.h>

// This is an example code to demonstrate how to use parameter server.
int main(int argc, const char** argv)
{
    // Eventually, move this to use the files from test assets.

    // Despite the number of elements created.
    // There is only once instance created.
    // It can be considered static for most purposes.
    crConfigManager cfgManager;
    crConfigManager cfgManager2;
    // Only the first read works.
    cfgManager.readFromFile("RobotInfo2.xml");
    // This read will be ignored.
    cfgManager2.readFromFile("Config.xml");
    // Prints the first config value contents.
    fmsPrintRepeated("_", 30);
    cfgManager.print();
    fmsPrintRepeated("_", 30);
    // Prints the first config value contents.
    cfgManager2.print();
    fmsPrintRepeated("_", 30);

    // You can only get one value at a time
    // Or you can get the entire subConfig.
    std::string searchFor = "MoveParam/maxToleranceAtGoalOrientation";
    std::string data;

    bool found = cfgManager.get(data, searchFor);
    fmsPrint("%s %s %d", searchFor.c_str(), data.c_str(), found);

    searchFor = "RobotsConfigPath";
    found = cfgManager.get(data, searchFor);
    fmsPrint("%s %s %d", searchFor.c_str(), data.c_str(), found);

    // If you need to reset the cfg manager.
    cfgManager2.reset("Config.xml");

    searchFor = "uiparameters/interface";
    found = cfgManager.get(data, searchFor);
    fmsPrint("%s %s %d", searchFor.c_str(), data.c_str(), found);
    // Search is case insensitive
    searchFor = "UIParameters/interface";
    found = cfgManager.get(data, searchFor);
    fmsPrint("%s %s %d", searchFor.c_str(), data.c_str(), found);

    return 0;
}
