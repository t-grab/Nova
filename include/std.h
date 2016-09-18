#ifndef NOVA_STD_H
#define NOVA_STD_H

#include <vector>
#include <string>
#include <stdexcept>
#include <iostream>
#include <fstream>
#include <sstream>
#include <memory>
#include <functional>
#include <algorithm>

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

typedef unsigned int uint;

struct Error {
    std::stringstream m_stream;

public:
    enum Action { Throw };

    Error();

    void operator<<(Action action);
    template<typename T> Error& operator<<(const T& val);
};

extern Error error;

class Log {
    std::string m_file_name;
    std::stringstream m_stream;

public:
    enum Action { Commit, RollBack };

    Log(const std::string& file_name);
    
    void operator<<(Action action);
    template<typename T> Log& operator<<(const T& val);
};

extern Log glLog;

////////////////////////////////////////////////////////////////////////////////
////////// LOG IMPLEMENTATION //////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

template<typename T>
Log& Log::operator<<(const T& val) {
    m_stream << val;
    return *this;
}

////////////////////////////////////////////////////////////////////////////////
////////// ERRORTHROWER IMPLEMENTATION /////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

template<typename T>
Error& Error::operator<<(const T& val) {
    m_stream << val;
    return *this;
}

#endif