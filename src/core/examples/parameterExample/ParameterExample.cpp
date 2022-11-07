// // Copyright 2022 Divyanshu Goel.
#include <core/core/Core.h>

// This is an example code to demonstrate how to use parameter server.
int main(int argc, const char** argv)
{
    crParameterD adfa("TReri", 123, 123, "");

    param::crParameterSet paramServer;
    paramServer.add(adfa);
    paramServer.print();

    // Check Update
    paramServer.update("TReri", 67.0);
    paramServer.print();
    {
        double value3;
        bool found = paramServer.find(value3, "TReri");
        printf("Update %f\n", value3);
    }


    // Link only works for variable.
    double value = 9;
    double value3 = 78.0;
    bool found = paramServer.find(value, "TReri");
    paramServer.link("TReri", value3);

    paramServer.print();

    double value13 = 9;
    found = paramServer.find(value13, "TReri");
    auto etrValue = adfa.value();

    printf("Value %d\n", found);
    printf("Value %f\n", value);
    printf("NEW %f\n", etrValue);
    printf("NEW %f\n", value13);
    paramServer.print();

    // Reset
    paramServer.reset();
    paramServer.print();
    
    // Clear
    paramServer.clear();
    paramServer.print();

    return 0;
}
