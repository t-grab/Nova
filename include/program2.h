#ifndef NOVA_PROGRAM2_H
#define NOVA_PROGRAM2_H

#include "std.h"
#include "window.h"
#include "context.h"
#include <type_traits>
#include <thread>

namespace Nova {
    class Program2 {
        Window2& m_window;
        OpenGLContext m_context;
        std::string m_title;
        std::thread m_thread;
        
        static void start_thread(std::shared_ptr<Program2> program);
    public:
        Program2(const std::string& title, int width = 640, int height = 480);
        virtual ~Program2();

        Window2& window();
        OpenGLContext& context();

        virtual const std::string& get_title() const;
        virtual void set_title(const std::string& title);

        virtual void init();
        virtual void main();
        virtual void finish();

        template<typename T, typename... Args> static std::shared_ptr<T> run(Args... args);
    };
    
////////////////////////////////////////////////////////////////////////////////
////////// PROGRAM 2 TEMPLATE IMPLEMENTATION ///////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

    template<typename T, typename... Args> std::shared_ptr<T> Program2::run(Args... args) {
        static_assert(std::is_base_of<Program2, T>::value,
                      "Program2::run(): T does not implement Program2");
        std::shared_ptr<T> program{std::make_shared<T>(args...)};
        program->m_thread = std::thread(Program2::start_thread, program);
        return program;
    }
}

#endif