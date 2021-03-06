#ifndef LOGGER_HPP
#define LOGGER_HPP

#include <QFile>
#include <QString>
#include <QTextStream>
#include <memory>
#include <vector>

/*
 * This class provide global loggers for this application.
 *
 * To use it, just call Log::log("My message")
 *
 *
 */

namespace Log {
enum class eLogType
{
    DEBUG,       // to help developpers only
    LOG,         // write in log file but not to final user
    INFORMATION, // info printable to user
    ERROR,       // error
};

class Logger
{
public:
    virtual ~Logger() {}
    virtual void print(const std::string& message, eLogType type) = 0;

    static void registerLogger(const std::shared_ptr<Logger>& toAdd);
    static void unregisterLogger(const std::shared_ptr<Logger>& toRm);
    static void printAll(const std::string& message, eLogType type);

protected:
    static QString getTypeString(eLogType type);

private:
    static std::vector<std::shared_ptr<Logger>> gLoggers;
};

//////////////////////////
// Some default loggers
class LoggerConsole : public Logger
{
public:
    void print(const std::string& message, eLogType type) override;
};

class LoggerFile : public Logger
{
public:
    explicit LoggerFile();
    void print(const std::string& message, eLogType type) override;

private:
    QFile m_logFile;
    QTextStream m_stream;
};

//////////////////////////
// Fast access methods

void print(const std::string& message, eLogType type);
void print(const QString& message, eLogType type);

void debug(const QString& message);
void log(const QString& message);
void info(const QString& message);
void error(const QString& message);


} // namespace Log

#endif // LOGGER_HPP
