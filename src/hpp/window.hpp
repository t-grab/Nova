#ifndef WINDOW_HPP
#define WINDOW_HPP

#include "windows.hpp"
#include <thread>
#include <mutex>
#include <condition_variable>

namespace Nova {
	typedef std::lock_guard<std::mutex> lock_guard;
	
	class Window {
		friend class Windows;
		
		public:
			Window(int w, int h);
			~Window();
			
			void open();
			void close();
			void wait();
		private:
			GLFWwindow* handle;
			GLuint shader;
			
			std::thread thread;
			std::mutex initializing;
			std::mutex running;
			
			int width;
			int height;
			
			void init();
			void main();
	};
}

#endif