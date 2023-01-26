#include "Application.h"
#include "Event/ApplicationEvent.h"
#include "Log/Log.h"

namespace Hina
{

Application::Application() {

}

Application::~Application() {

}

void Application::Run() {
	WindowResizeEvent wre{ 123, 456 };
	std::cout << wre << std::endl;

	while(true) {
		
	}
}

}
