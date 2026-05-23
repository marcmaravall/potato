#include "editor/editor.h"

using namespace PotatoEngine::Core;

int main(int argc, char** argv) {
	Application* application = new PotatoEngine::Editor::EditorApplication();
	application->Run();

	return 0;
}