//
// Created by ivan on 20.03.16.
//

#ifndef FILETRANSMITSERVER_LOG_H
#define FILETRANSMITSERVER_LOG_H


#include <string>
/*
 * Класс-помошник для организации логирования
 */
class Log {
private:
    static void _print(std::string module, std::string message, std::string level);
    static void _info(std::string module, std::string message);
    static void _debug(std::string module, std::string message);
    static void _error(std::string module, std::string message);
    static void _internal(std::string module, std::string message);
    void internal(std::string message);
    std::string module;
public:
    static unsigned short level;
    static const unsigned short LEVEL_INFO = 0x1;
    static const unsigned short LEVEL_DEBUG = 0x2;
    static const unsigned short LEVEL_ERROR = 0x4;
    static const unsigned short LEVEL_INTERNAL = 0x8;
    static const unsigned short LEVEL_ALL = LEVEL_INFO | LEVEL_DEBUG | LEVEL_ERROR | LEVEL_INTERNAL;
    Log(std::string module);
    ~Log();
    void info(std::string message);
    void debug(std::string message);
    void error(std::string message);
    /*
     * Устанавливает уровень выводимых сообщений
     */
    static void setLevel(unsigned short level);
};

#endif //FILETRANSMITSERVER_LOG_H
