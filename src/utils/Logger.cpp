#include "utils/Logger.hpp"

#include <QDateTime>
#include <QDir>
#include <iostream>

namespace Log {

std::vector<std::shared_ptr<Logger>> Logger::gLoggers;

void Logger::registerLogger(const std::shared_ptr<Logger>& toAdd)
{
    gLoggers.push_back(toAdd);
}

void Logger::unregisterLogger(const std::shared_ptr<Logger>& toRm)
{
    gLoggers.erase(std::remove(gLoggers.begin(), gLoggers.end(), toRm), gLoggers.end());
}

void Logger::printAll(const std::string& message, eLogType type)
{
    for (const auto& logger : Logger::gLoggers)
        if (logger != nullptr)
            logger->print(message, type);
}

QString Logger::getTypeString(eLogType type)
{
    switch (type) {
    case eLogType::DEBUG:
        return "Debug";
    case eLogType::LOG:
        return "Log";
    case eLogType::INFORMATION:
        return "Info";
    case eLogType::ERROR:
        return "ERROR";
    default:
        return "Unknown type";
    }
}

////////////////////////////////////////////////
// Simple loggers
////////////////////////////////////////////////

void LoggerConsole::print(const std::string& message, eLogType type)
{
    std::cout << '[' << getTypeString(type).toStdString() << "] \t" << message << std::endl;
}

LoggerFile::LoggerFile()
{
    QDir logpath("./log/");
    if (! logpath.exists()) {
        QDir().mkdir("./log/");
    }
    m_logFile.setFileName("./log/" + QDate::currentDate().toString("yyyy-MM-dd") + "_logfile.txt");

    if (m_logFile.open(QFile::ReadWrite | QFile::Text | QFile::Append)) {
        m_stream.setDevice(&m_logFile);
    }
}

void LoggerFile::print(const std::string& message, eLogType type)
{
    m_stream << QTime::currentTime().toString();
    m_stream << " [" << getTypeString(type) << "] ";
    m_stream << QString::fromStdString(message) << endl;
}

////////////////////////////////////////////////
// fast access QString
////////////////////////////////////////////////

void print(const std::string& message, eLogType type)
{
    Logger::printAll(message, type);
}
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

} // namespace Log
