#include "effect.h"
#include "../common.h"
#include "../info.h"

namespace effect {

class Static : public Effect {
public:
    Static(uint32_t color = 0xFFFFFF) : color(color) {}
    void set_parameter(uint8_t i, uint16_t val) {
        if(i > 2)
            return;
        color =
            (color & ~(0xFF0000 >> (i * 8)))
            | (val >> 8 << 16 >> (i * 8));

    }
protected:
    void apply(uint32_t *a, uint16_t n, uint32_t *out) { fill(out, color, n); }
private:
    uint32_t color;
};

} // namespace effect
