#ifndef NOVA_SHADER_H
#define NOVA_SHADER_H

#include "std.h"
#include <type_traits>

namespace Nova {
    /*
    class Shader {
        GLuint handle;
        GLint matrix;

        GLuint compile_shader(const std::string& src, GLuint type);

    public:
        static const char* stdVertex;
        static const char* stdFragment;

        Shader(const std::string& vertexSrc, const std::string& fragmentSrc);    
        void activate() const;
        void set_transform(const glm::mat4& mat);

        friend class ShaderProgram;
    };
    */

    class ShaderProgram;

    class Shader {
    protected:
        uint_t m_shader;
        uint64_t m_id;

        Shader(uint_t shader, uint64_t id);

        template<typename T>
        static std::shared_ptr<T> compile(const std::string& src, uint_t type,
                                          std::vector<std::shared_ptr<T>>& shaders) {
            static_assert(std::is_base_of<Shader, T>::value,
                          "Shader::compile(): T does not implement Shader");
            auto cstr = src.c_str();

            uint_t shader = glCreateShader(type);
            glShaderSource(shader, 1, &cstr, nullptr);
            glCompileShader(shader);
            
            int params = -1;
            glGetShaderiv(shader, GL_COMPILE_STATUS, &params);
            if (params != GL_TRUE) {
                const int max_length = 2048;
                int actual_length = 0;
                char log[max_length];

                glGetShaderInfoLog(shader, max_length, &actual_length, log);
                error << "Error: Shader " << shader << " did not compile!\n"
                    << "Compiler Output: \n"
                    << log << "\n"
                    << Error::Throw;
            }

            uint64_t size{shaders.size()};
            std::shared_ptr<T> shader_ptr{new T(shader, size)};
            shaders.push_back(shader_ptr);

            return shader_ptr;
        }      

        friend class ShaderProgram;
    public:
        virtual ~Shader();
        
        int_t get_uniform(const std::string& name) const;
    };

    class VertexShader : public Shader {        
        VertexShader(uint_t shader, uint64_t id);

        static std::mutex static_mutex;
        static std::vector<std::shared_ptr<VertexShader>> shaders;
    public:
        ~VertexShader();
        static std::string standard;
        static std::shared_ptr<VertexShader> compile(const std::string& src);
        
        friend class Shader;
    };

    class FragmentShader : public Shader {
        FragmentShader(uint_t shader, uint64_t id);

        static std::mutex static_mutex;
        static std::vector<std::shared_ptr<FragmentShader>> shaders;
    public: 
        ~FragmentShader();
        static std::string standard;
        static std::shared_ptr<FragmentShader> compile(const std::string& src);

        friend class Shader;
    }; 

    class ShaderProgram {
        uint_t m_program;
        uint64_t m_id;
        
        ShaderProgram(uint_t program, uint64_t id);

        static std::mutex static_mutex;
        static std::vector<std::shared_ptr<ShaderProgram>> shaders;
    public:
        ~ShaderProgram();
        static std::shared_ptr<ShaderProgram> link(std::shared_ptr<VertexShader> vertex,
                                                   std::shared_ptr<FragmentShader> fragment);
    };
}

#endif