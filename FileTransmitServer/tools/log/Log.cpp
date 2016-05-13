//
// Created by ivan on 20.03.16.
//

#include "Log.h"

unsigned short Log::level = 0;

void Log::_debug(std::string module, std::string message) {
    if(Log::level & LEVEL_DEBUG)
        _print(module, message, "DEBUG");
}

void Log::_info(std::string module, std::string message) {
    if(Log::level & LEVEL_INFO)
        _print(module, message, "INFO");
}

void Log::_error(std::string module, std::string message) {
    if(Log::level & LEVEL_ERROR)
        _print(module, message, "ERROR");
}

Log::Log(std::string module) {
    this->module = module;
    internal("loaded");
}

void Log::info(std::string message) {
    _info(module, message);
}

void Log::debug(std::string message) {
    _debug(module, message);
}

void Log::error(std::string message) {
    _error(module, message);
}

void Log::_print(std::string module, std::string message, std::string level) {
    printf("[%s] %s: %s \n", level.c_str(), module.c_str(), message.c_str());
}

Log::~Log() {
    internal("unloaded");
}

void Log::_internal(std::string module, std::string message) {
    if(Log::level & LEVEL_INTERNAL)
        _print(module, message, "INTERNAL");
}

void Log::internal(std::string message) {
    _internal(module, message);
}

void Log::setLevel(unsigned short _level) {
    level = _level;
}













