#include <hash.h>

uint64_t hash(uint8_t *str)
{
    uint64_t hash = 5381;
    int32_t c;

    while ((c = *str++))
        hash = ((hash << 5) + hash) + c;

    return hash;
}
