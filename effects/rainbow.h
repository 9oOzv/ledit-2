#include "effect.h"
#include "../common.h"
#include "../info.h"

namespace effect {

class Rainbow : public Effect {
public:
    Rainbow(uint16_t speed = 20) : speed(speed) {}
    void set_parameter(uint8_t i, uint16_t val) {
        if(i > 1)
            return;
        speed = val;
    }
protected:
    void apply(uint32_t *a, uint16_t n, uint32_t *out) {
        const unsigned long t = millis();
        const uint16_t step = 360 * 100 / n;
        const uint8_t sat = 255;
        const uint8_t val = 255;
        for(uint16_t i = 0; i < n; i++) {
            const uint16_t hue = (
                (i * step) / 100
                + (t * speed / 1000)
            ) % 360;
            out[i] = hsv_to_rgb(hue, sat, val);
        }
    }
private:
    uint16_t speed;
};

} // namespace effect
