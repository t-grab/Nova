#ifndef WINDOW_FACTORY_H
#define WINDOW_FACTORY_H

#include "std.hpp"
#include <thread>

namespace Nova {
	class Window;
	
	class Windows {
		public:
			~Windows();
			
			Windows(const Windows&) 		= delete;
			void operator=(const Windows&) 	= delete;
		
			static Windows& get();		
			Window& create(int width, int height);
			void wait();
			
			GLuint create_default_shader();
		private:						
			Windows();
										
			std::vector<Window*> windows;
			
			const char* DEFAULT_VERTEX_SHADER_SRC;
			const char* DEFAULT_FRAGMENT_SHADER_SRC;		
	};
	
	void error(int error, const char* description);
	void key(GLFWwindow* window, int key, int scancode, int action, int mods);
}

#endif