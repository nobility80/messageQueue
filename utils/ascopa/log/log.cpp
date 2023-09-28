//
// Copyright 2022, Mercedes-Benz AG
// Mercedes-Benz Korea R&D joerg.c.wolf@mercedes-benz.com
//
#include <Log/log.h>

#include <iostream>
#include <chrono>
#include <cstring>
#include <iomanip>
#include <sstream>
#include <fstream>
#include <algorithm>


#define BUFFERSIZE  (unsigned int)10000

#if defined(LOG_WITH_DLT)
  #include <dlt.h>
  #include <dlt_user_macros.h>
  DLT_DECLARE_CONTEXT(con_mbos_log1);
#endif

namespace mbos {

bool log::LogToFile = true;
bool log::LogToTerminal = true;
bool log::firstLogOfProcess = true;
char* log::filename = nullptr;
std::string log::applicationName4Letter = std::string("NVMV");
std::string log::applicationLongName = std::string("Reference Navigation");
std::string log::folder = std::string("");

char const* DEBUGSTR = "DEBUG";
char const* INFOSTR  = "INFO";
char const* WARNSTR = "WARN";
char const* ERRORSTR = "ERROR";

void log::SetLogOutput(const bool ToFile, const bool ToTerminal)
{
    log::LogToFile = ToFile;
    log::LogToTerminal = ToTerminal;
}

void log::SetOutputFolder(const char* const folder)
{
    log::folder = std::string(folder);
}

void log::SetApplicationName(const char* const capplicationName4Letter, const char* const capplicationLongName)
{
    log::applicationName4Letter = std::string(capplicationName4Letter);
    log::applicationName4Letter = applicationName4Letter.substr((unsigned int)0, (unsigned int)4);
    std::transform(applicationName4Letter.begin(), applicationName4Letter.end(), applicationName4Letter.begin(),
                       [](const unsigned char c){ return toupper(c); });
    log::applicationLongName = std::string(capplicationLongName);
}

void log::I(const char* const channelName, const char* const format, ...) {
    va_list args;
    char    buffer[BUFFERSIZE];
    va_start( args, format );
    vsnprintf(&buffer[0], BUFFERSIZE, format, args); // C4996
    doLog(DL_INFO,channelName, &buffer[0]);
    va_end(args);
}

void log::D(const char* const channelName, const char* const format, ...) {
    va_list args;
    char    buffer[BUFFERSIZE];
    va_start( args, format );
    vsnprintf(&buffer[0], BUFFERSIZE, format, args); // C4996
    doLog(DL_DEBUG,channelName, &buffer[0]);
    va_end(args);
}

void log::W(const char* const channelName, const char* const format, ...) {
    va_list args;
    char    buffer[BUFFERSIZE];
    va_start( args, format );
    vsnprintf(&buffer[0], BUFFERSIZE, format, args); // C4996
    doLog(DL_WARN,channelName, &buffer[0]);
    va_end(args);
}

void log::E(const char* const channelName, const char* const format, ...) {
    va_list args;
    char    buffer[BUFFERSIZE];

    va_start( args, format );
    vsnprintf(&buffer[0], BUFFERSIZE, format, args); // C4996
    doLog(DL_ERROR,channelName, &buffer[0]);
    va_end(args);
}

void log::doLog(DebugLevel const IDorELevel, const char* const channelName, const char* const buffer)
{
    char const* IDorE;
    switch(IDorELevel){
        case DL_DEBUG: IDorE = DEBUGSTR; break;
        case DL_ERROR: IDorE = ERRORSTR; break;
        case DL_WARN: IDorE = WARNSTR; break;
        case DL_INFO: IDorE = INFOSTR; break;
        default:   IDorE = INFOSTR; break;
    }

    if(log::LogToTerminal)
    {
        if(IDorELevel == DL_ERROR){
            std::cerr << buffer << std::endl;
        }else{
            std::cout << buffer << std::endl;
        }
    }
    if(log::LogToFile)
    {
        if(log::filename == nullptr)
        {
            // create file
            const std::time_t now_c = std::chrono::system_clock::to_time_t( std::chrono::system_clock::now() );
            std::stringstream names; names << "Trace_" << log::applicationName4Letter << "_" << std::put_time(std::localtime(&now_c), "%F_%H-%M-%S") << ".log";
            std::string namestr = names.str();
            std::string slash = "";
            if(folder.length() > (unsigned int)0){
#if defined(WIN32) || defined(WIN64) || defined(_WIN32) || defined(_WIN64)
                if( folder.back() != '\\'){ slash = std::string("\\"); }
#else
                if( folder.back() != '/'){ slash = std::string("/"); }
#endif
            }
            namestr = folder + slash + namestr;
            char *filenameBuffer = new char[namestr.length()+(unsigned int)1];
            std::memcpy(filenameBuffer,namestr.c_str(), namestr.length());
            filenameBuffer[namestr.length()] = '\0';
            log::filename = filenameBuffer;
            std::ofstream loginitialfile;
            loginitialfile.open (log::filename,std::ios::out);
            loginitialfile << "MBOS Tracelog\n";
            loginitialfile.close();
        }
        std::ofstream logstream;
        logstream.open (log::filename,std::ios::app | std::ios::ate);
        const std::chrono::system_clock::time_point t = std::chrono::system_clock::now();
        std::time_t now_c = std::chrono::system_clock::to_time_t( t  );
        const std::chrono::duration<double> tse = t.time_since_epoch();
        const std::chrono::seconds::rep milliseconds = std::chrono::duration_cast<std::chrono::milliseconds>(tse).count() % 1000;
        logstream << std::put_time(std::localtime(&now_c), "%F_%H-%M-%S.") << std::setfill('0') << std::setw(3) << milliseconds << "," << IDorE << "," << channelName << "," << buffer << "\n";
        logstream.close();
    }

#if defined(LOG_WITH_DLT)
    if(log::firstLogOfProcess == true){
        DLT_REGISTER_APP(log::applicationName4Letter.c_str(), log::applicationLongName.c_str());

        std::string channelAsContext(channelName);
        channelAsContext = channelAsContext.substr((unsigned int)0, (unsigned int)4);
        std::transform(channelAsContext.begin(), channelAsContext.end(), channelAsContext.begin(),
                           [](const unsigned char c){ return toupper(c); });

        DLT_REGISTER_CONTEXT(con_mbos_log1, channelAsContext.c_str(), channelName);

    }
    switch(IDorELevel){
        case DL_DEBUG:
            DLT_LOG(con_mbos_log1, DLT_LOG_DEBUG, DLT_STRING(buffer));  break;
        case DL_ERROR:
            DLT_LOG(con_mbos_log1, DLT_LOG_ERROR, DLT_STRING(buffer));  break;
        case DL_WARN:
            DLT_LOG(con_mbos_log1, DLT_LOG_WARN, DLT_STRING(buffer));   break;
        case DL_INFO:
            DLT_LOG(con_mbos_log1, DLT_LOG_INFO, DLT_STRING(buffer));   break;
        default:
            DLT_LOG(con_mbos_log1, DLT_LOG_INFO, DLT_STRING(buffer));   break;
    }
#endif
    log::firstLogOfProcess = false;

}

void log::Shutdown(){
#if defined(LOG_WITH_DLT)
    if(log::firstLogOfProcess == false){
        DLT_UNREGISTER_CONTEXT(con_mbos_log1);
        DLT_UNREGISTER_APP();
    }
#endif
}

} // namespace mbos
