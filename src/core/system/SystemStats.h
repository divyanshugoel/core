// // Copyright 2022 Divyanshu Goel.
// #pragma once

// #include <string>

// #include "core/core/Core.h"
// #include "core/core/SimpleSingleton.h"

// ////////////////////////////////////////////////////////////////////////////////
// // Convenient function to fetch the system stats.

// struct crCPUInformation
// {
//     crCPUInformation()
//         : numCpus(0), hasMMX(false), hasSSE(false), hasSSE2(false), hasSSE3(false), has3DNow(false), hasSSSE3(false), hasSSE41(false), hasSSE42(false), hasAVX(false), hasAVX2(false)
//     {
//         initialise();
//     }

//     void initialise();

//     int numCpus;
//     bool hasMMX;
//     bool hasSSE;
//     bool hasSSE2;
//     bool hasSSE3;
//     bool has3DNow;
//     bool hasSSSE3;
//     bool hasSSE41;
//     bool hasSSE42;
//     bool hasAVX;
//     bool hasAVX2;
// };

// enum crOperatingSystemType
// {
//     UnknownOS = 0,
//     // To test whether any version of OSX is running, you can use the expression ((getOperatingSystemType() & MacOSX) != 0).
//     MacOSX = 0x0100,
//     // To test whether any version of Windows is running, you can use the expression ((getOperatingSystemType() & Windows) != 0).
//     Windows = 0x0200,
//     Linux = 0x0400,
//     Android = 0x0800,
//     iOS = 0x1000,

//     MacOSX_10_4 = MacOSX | 4,
//     MacOSX_10_5 = MacOSX | 5,
//     MacOSX_10_6 = MacOSX | 6,
//     MacOSX_10_7 = MacOSX | 7,
//     MacOSX_10_8 = MacOSX | 8,
//     MacOSX_10_9 = MacOSX | 9,
//     MacOSX_10_10 = MacOSX | 10,
//     MacOSX_10_11 = MacOSX | 11,
//     MacOSX_10_12 = MacOSX | 12,

//     Win2000 = Windows | 1,
//     WinXP = Windows | 2,
//     WinVista = Windows | 3,
//     Windows7 = Windows | 4,
//     Windows8_0 = Windows | 5,
//     Windows8_1 = Windows | 6,
//     Windows10 = Windows | 7
// };

// ////////////////////////////////////////////////////////////////////////////////

// static const crCPUInformation& getCPUInformation();

// ////////////////////////////////////////////////////////////////////////////////
// // Contains methods for finding out about the current hardware and OS configuration.

// class crSystemStats : crSingleton<crSystemStats>
// {
//     FMS_AUTO_SINGLETON(crSystemStats);

// public:
//     // Returns the type of operating system we're running on.
//     static crOperatingSystemType getOperatingSystemType();
//     // Returns the name of the type of operating system we're running on.
//     static std::string getOperatingSystemName();
//     // Returns true if the OS is 64-bit, or false for a 32-bit OS.
//     static bool isOperatingSystem64Bit();
//     // Returns an environment variable.
//     // If the named value isn't set, this will return the defaultValue std::string instead.
//     static std::string getEnvironmentVariable(const std::string& name, const std::string& defaultValue);
//     // Returns the current user's name, if available.
//     static std::string getLogonName();
//     // Returns the current user's full name, if available.
//     static std::string getFullUserName();
//     // Returns the host-name of the computer.
//     static std::string getComputerName();
//     // Returns the language of the user's locale.
//     // The return value is a 2 or 3 letter language code(ISO 639 - 1 or ISO 639 - 2)
//     static std::string getUserLanguage();
//     // Returns the region of the user's locale.
//     // The return value is a 2 letter country code(ISO 3166 - 1 alpha - 2).
//     static std::string getUserRegion();
//     // Returns the user's display language.
//     // The return value is a 2 or 3 letter language code (ISO 639-1 or ISO 639-2).
//     // Note that depending on the OS and region, this may also be followed by a dash
//     // and a sub-region code, e.g "en-GB"
//     static std::string getDisplayLanguage();
//     // This will attempt to return some kind of std::string describing the device.
//     static std::string getDeviceDescription();

//     ////////////////////////////////////////////////////////////////////////////////
//     // CPU and memory information..

//     // Returns the number of CPU cores.
//     static int getNumCpus() noexcept;
//     // Returns the approximate CPU speed the speed in megahertz, e.g. 1500
//     static int getCpuSpeedInMegaherz();
//     // Returns a std::string to indicate the CPU vendor.
//     static std::string getCpuVendor();
//     // Returns true if Intel MMX instructions are available.
//     static bool hasMMX() noexcept;
//     // Returns true if AMD 3DNOW instructions are available.
//     static bool has3DNow() noexcept;
//     // Returns true if Intel SSE instructions are available.
//     static bool hasSSE() noexcept;
//     // Returns true if Intel SSE2 instructions are available.
//     static bool hasSSE2() noexcept;
//     // Returns true if Intel SSE3 instructions are available.
//     static bool hasSSE3() noexcept;
//     // Returns true if Intel SSSE3 instructions are available.
//     static bool hasSSSE3() noexcept;
//     // Returns true if Intel SSE4.1 instructions are available.
//     static bool hasSSE41() noexcept;
//     // Returns true if Intel SSE4.2 instructions are available.
//     static bool hasSSE42() noexcept;
//     // Returns true if Intel AVX instructions are available.
//     static bool hasAVX() noexcept;
//     // Returns true if Intel AVX2 instructions are available.
//     static bool hasAVX2() noexcept;
//     // Finds out how much RAM is in the machine.
//     static int getMemorySizeInMegabytes();
//     // Returns the system page-size.
//     static int getPageSize();
//     // Returns a backtrace of the current call-stack.
//     // The usefulness of the result will depend on the level of debug symbols
//     // that are available in the executable.
//     static std::string getStackBacktrace();

//     // A void() function type, used by setApplicationCrashHandler().
//     typedef void (*CrashHandlerFunction)();

//     // Sets up a global callback function that will be called if the application
//     // executes some kind of illegal instruction.

//     // You may want to call getStackBacktrace() in your handler function, to find out
//     // where the problem happened and log it, etc.
//     static void setApplicationCrashHandler(CrashHandlerFunction);
// };
