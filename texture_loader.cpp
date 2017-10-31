#include "texture_loader.h"

GLuint load_texture(char const* filename)
{
    if(!filename) {
        std::cerr << "Cannot find " << filename << std::endl;
    }
    GLuint texture = SOIL_load_OGL_texture
	(
		filename,
		SOIL_LOAD_AUTO,
		SOIL_CREATE_NEW_ID,
		SOIL_FLAG_MIPMAPS | SOIL_FLAG_INVERT_Y | SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_COMPRESS_TO_DXT
    );
    if(!texture) {
        std::cerr << "Failed to load " << filename << std::endl;
    }
    return texture;
}