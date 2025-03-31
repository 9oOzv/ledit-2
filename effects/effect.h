#pragma once

namespace effect {

class Effect {
public:
    template<uint16_t T>
    inline void apply(
        uint32_t (&color)[T],
        uint32_t (&out)[T]
    ) {
        apply(color, T, out);
    }
    virtual void set_parameter(uint8_t i, uint16_t val) = 0;
    virtual void set_parameters(uint16_t *values) {
        for(uint8_t i = 0; i < 10; i++) {
            set_parameter(i, values[i]);
        }
    }
protected:
    virtual void apply(uint32_t *color, uint16_t n, uint32_t *out) = 0;
};

} // namespace effect
