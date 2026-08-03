#include "opengl_texture2d.h"

namespace PotatoEngine::Core::Rendering {

GLuint WrapToGl(const TextureWrap wrap) {
    return wrap == TextureWrap::REPEAT ? GL_REPEAT
         : wrap == TextureWrap::MIRRORED_REPEAT ? GL_MIRRORED_REPEAT
         : wrap == TextureWrap::CLAMP_TO_EDGE   ? GL_CLAMP_TO_EDGE
         : wrap == TextureWrap::CLAMP_TO_BORDER ? GL_CLAMP_TO_BORDER
         : GL_REPEAT;
}

GLuint FilterToGl(const TextureFilter filter) {
    return filter == TextureFilter::POINT ? GL_NEAREST
         : filter == TextureFilter::BILINEAR ? GL_LINEAR 
         : GL_LINEAR;
}

OpenGL_Texture2D::OpenGL_Texture2D(const std::string& filepath, const Texture2D_Settings& settings) {
    glGenTextures(1, &m_id);
    glBindTexture(GL_TEXTURE_2D, m_id);

    GLuint textureWrapS = WrapToGl(settings.WrapS);
    GLuint textureWrapT = WrapToGl(settings.WrapT);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, textureWrapS);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, textureWrapT);
    
    GLuint filter = FilterToGl(settings.Filter);
    
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, filter);

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