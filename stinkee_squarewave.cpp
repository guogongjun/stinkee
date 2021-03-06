#include <stinkee_squarewave.h>

#include <cassert>

namespace stinkee {

void encodeByte(const unsigned char  byte,
                const int            samplingRate,
                const int            bit0Frequency,
                const int            bit1Frequency,
                std::vector<float>  *frames)
{
    assert(samplingRate > 0);
    assert(bit0Frequency > 0);
    assert(bit1Frequency > 0);
    assert(frames);

    std::vector<bool> bits;

    for (std::size_t i = 0; i < 8; ++i) {
        bits.push_back(byte & (128 >> i));
    }

    encodeBits(bits, samplingRate, bit0Frequency, bit1Frequency, frames);
}

void encodeBits(const std::vector<bool>&  bits,
                const int                 samplingRate,
                const int                 bit0Frequency,
                const int                 bit1Frequency,
                std::vector<float>       *frames)
{
    assert(samplingRate > 0);
    assert(bit0Frequency > 0);
    assert(bit1Frequency > 0);
    assert(frames);

    const int numFramesPerBit0 = samplingRate / bit0Frequency;
    const int numFramesPerBit1 = samplingRate / bit1Frequency;

    for (const bool& bit : bits) {
        const int numFramesPerLevel = bit
                                    ? numFramesPerBit1 / 2
                                    : numFramesPerBit0 / 2;

        frames->insert(frames->end(), numFramesPerLevel, LOW_LEVEL_AMPLITUDE);
        frames->insert(frames->end(), numFramesPerLevel, HIGH_LEVEL_AMPLITUDE);
    }
}

}  // library namespace
