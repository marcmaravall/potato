#include "opengl_texture2d.h"

namespace PotatoEngine::Core::Rendering {

OpenGL_Texture2D::OpenGL_Texture2D(const std::string& filepath) {
    glGenTextures(1, &m_id);
    glBindTexture(GL_TEXTURE_2D, m_id);

    // This should be set according to the texture's actual properties,
    // for now we can just set it to some default values
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER,
                    GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

    unsigned char* data =
        stbi_load(filepath.c_str(), &m_width, &m_height, &m_channels, 4);
    if (data) {
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, m_width, m_height, 0, GL_RGBA,
                     GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);
    } else {
        MEB_LOG_ERRORF("Cannot load texture from file: %s", filepath.c_str());
        MEB_ASSERT(0 && "Failed to load texture!");
    }
    stbi_image_free(data);
}

}  // namespace PotatoEngine::Core::Rendering