#include "utils/Logger.hpp"

#include <iostream>
#include <QDateTime>
#include <QDebug>
#include <QDir>
#include <QFileDialog>
#include <QTextStream>
#include <QTime>

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
    for (const auto& logger : Logger::gLoggers)
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

LoggerFile::LoggerFile()
{

    QDir logpath("./log/");
    if (!logpath.exists()){
        QDir().mkdir("./log/");
    }
    m_logFile.setFileName("./log/"
                          + QDate::currentDate().toString("yyyyMMdd") + "_"
                          + QTime::currentTime().toString("hh-mm-ss")
                          + "_logfile.txt");

    if ( m_logFile.open(QFile::ReadWrite | QFile::Text) )
    {
        m_stream.setDevice( &m_logFile );
    }

}

void LoggerFile::print(const std::string& message, eLogType type)
{
    m_line = QTime::currentTime().toString() + ' [';
    switch (type) {
    case eLogType::DEBUG:
        m_line += "Debug";
        break;
    case eLogType::LOG:
        m_line += "Log";
        break;
    case eLogType::INFORMATION:
        m_line += "Info";
        break;
    case eLogType::ERROR:
        m_line += "ERROR";
        break;
    default:
        m_line += "Unknown type";
    }
    m_line += "] " + QString::fromStdString(message);
    m_stream << m_line << endl;
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
