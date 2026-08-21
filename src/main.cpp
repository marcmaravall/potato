#include <string>
#include <vector>

#include "core/executable.h"
#include "core/game.hpp"
#include "editor/editor_application.h"

using namespace PotatoEngine::Core;

int main(int argc, char** argv) {
    MEB_INIT(nullptr);

    bool runEditor = true;

    for (int i = 0; i < argc; i++) {
        if (strcmp(argv[i], "--build") == 0) runEditor = false;
    }

    if (runEditor) {
        // run editor
        Application* editor = new PotatoEngine::Editor::EditorApplication();
        editor->Run();
    } else {
        // run game
        Application* game = new Game();
        game->Run();
    }
    return 0;
}

#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>

#define MEB_IMPLEMENTATION
#define MEB_LOG_TO_STDOUT
#include <meb.h>
