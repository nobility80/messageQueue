//
// Copyright 2022, Mercedes-Benz AG
// Mercedes-Benz Korea R&D joerg.c.wolf@mercedes-benz.com
//
#ifndef LOG_H
#define LOG_H
#include <string>

namespace mbos {
class log
{

public:

    static void I(const char* const channelName, const char* const format, ...);
    static void D(const char* const channelName, const char* const format, ...);
    static void W(const char* const channelName, const char* const format, ...);
    static void E(const char* const channelName, const char* const format, ...);
    static void SetLogOutput(bool const ToFile, bool const ToTerminal);
    static void SetOutputFolder(const char* const folder);
    static void SetApplicationName(const char* const capplicationName4Letter, const char* const capplicationLongName);
    static void Shutdown();

private:
    enum DebugLevel {
        DL_DEBUG,
        DL_INFO,
        DL_WARN,
        DL_ERROR
    };

    static void doLog(DebugLevel const IDorELevel, const char* const channelName, const char* const buffer);

    static bool LogToFile;
    static bool LogToTerminal;
    static char *filename;
    static std::string applicationName4Letter;
    static std::string applicationLongName;
    static std::string folder;
    static bool firstLogOfProcess;
};

}
#endif // LOG_H
