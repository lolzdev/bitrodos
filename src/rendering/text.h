#ifndef RENDERING_TEXT_H
#define RENDERING_TEXT_H

#include <log.h>
#include <ft2build.h>
#include FT_FREETYPE_H

void load_ft();
FT_Face create_font_face(char *name);

#endif
