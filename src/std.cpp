#include "../include/std.h"

////////////////////////////////////////////////////////////////////////////////
////////// LOG IMPLEMENTATION //////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

Log::Log(const std::string& file_name)
        : m_file_name(file_name), m_stream() {
}

void Log::operator<<(Log::Action action) {
    switch (action) {        
        case Log::Commit: {
            std::ofstream out(m_file_name, std::ofstream::app);
            if (!out) {
                error << "Log::operator<<(): Could not open log file" << Error::Throw;
            }
            out << m_stream.str();
            out.close();
        }
        case Log::RollBack: {
            m_stream.clear();
            break;
        }
        default: {
            error << "Log::operator(): Unknown Action" << Error::Throw;
        }
    }
}

////////////////////////////////////////////////////////////////////////////////
////////// ERROR IMPLEMENTATION ////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

Error error;

Error::Error()
        : m_stream() {
}

void Error::operator<<(Error::Action action) {
    switch (action) {
        case Error::Throw: {
            std::string error(m_stream.str());
            m_stream.clear();
            throw std::runtime_error(error);
        }
        default: {
            throw std::runtime_error("Error::operator<<(): Unknown Action");
        }
    }
}