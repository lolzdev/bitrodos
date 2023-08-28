#include <rendering/text.h>

static FT_Library ft;

void load_ft()
{
    if (FT_Init_FreeType(&ft))
        fatal("Failed to load the freetype library!");
}

FT_Face create_font_face(char *name)
{
    FT_Face face;
    if (FT_New_Face(ft, name, 0, &face)){
        error("Couldn't load font %s", name);
    }

    return face;
}
