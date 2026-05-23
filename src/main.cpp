#include "editor/editor.h"

int main(int argc, char** argv) {
	PotatoEngine::Editor editor;
	editor.Init();

	while (!editor.ShouldClose()) {
		editor.Update();
	}

	editor.End();

	return 0;
}