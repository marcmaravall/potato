#include "editor/editor_application.h"

using namespace PotatoEngine::Core;

int main(int argc, char** argv) {
	Application* application = new PotatoEngine::Editor::EditorApplication();
	application->Run();

	return 0;
}

#define MEB_IMPLEMENTATION
#define MEB_LOG_TO_FILE
#include <meb.h>