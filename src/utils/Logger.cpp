#include "utils/Logger.hpp"

#include <iostream>

namespace Log {

std::vector<std::shared_ptr<Logger>> Logger::gLoggers;

void Logger::registerLogger(const std::shared_ptr<Logger>& toAdd)
{
    gLoggers.push_back(toAdd);
}

void Logger::unregisterLogger(const std::shared_ptr<Logger>& toRm)
{
    gLoggers.erase(std::remove(gLoggers.begin(), gLoggers.end(), toRm),
                   gLoggers.end());
}

void Logger::printAll(const std::string& message, eLogType type)
{
    for (auto& logger : Logger::gLoggers)
        if (logger != nullptr)
            logger->print(message, type);
}

////////////////////////////////////////////////
// Simple loggers
////////////////////////////////////////////////

void LoggerConsole::print(const std::string& message, eLogType type)
{
    std::cout << '[';
    switch (type) {
    case eLogType::DEBUG:
        std::cout << "Debug";
        break;
    case eLogType::LOG:
        std::cout << "Log";
        break;
    case eLogType::INFORMATION:
        std::cout << "Info";
        break;
    case eLogType::ERROR:
        std::cout << "ERROR";
        break;
    default:
        std::cout << "Unknown type";
    }
    std::cout << "] \t" << message << std::endl;
}

LoggerFile::LoggerFile(const std::string& filePath)
{
    // TODO
    // use a ofstream class member ?
}

void LoggerFile::print(const std::string& message, eLogType type)
{
    // TODO print in file
}

////////////////////////////////////////////////
// fast access QString
////////////////////////////////////////////////

void print(const QString& message, eLogType type)
{
    Logger::printAll(message.toStdString(), type);
}
void debug(const QString& message)
{
#ifdef QT_DEBUG
    Logger::printAll(message.toStdString(), eLogType::DEBUG);
#endif // QT_DEBUT
}
void log(const QString& message)
{
    Logger::printAll(message.toStdString(), eLogType::LOG);
}
void info(const QString& message)
{
    Logger::printAll(message.toStdString(), eLogType::INFORMATION);
}
void error(const QString& message)
{
    Logger::printAll(message.toStdString(), eLogType::ERROR);
}

////////////////////////////////////////////////
// fast access Std::String
////////////////////////////////////////////////

void print(const std::string& message, eLogType type)
{
    Logger::printAll(message, type);
}
void debug(const std::string& message)
{
#ifdef QT_DEBUG
    Logger::printAll(message, eLogType::DEBUG);
#endif // QT_DEBUT
}
void log(const std::string& message)
{
    Logger::printAll(message, eLogType::LOG);
}
void info(const std::string& message)
{
    Logger::printAll(message, eLogType::INFORMATION);
}
void error(const std::string& message)
{
    Logger::printAll(message, eLogType::ERROR);
}

} // namespace Log
