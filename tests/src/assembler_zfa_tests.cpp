#include <catch/catch.hpp>

#include <array>
#include <cstring>

#include <biscuit/assembler.hpp>

using namespace biscuit;

static constexpr std::array fli_constants{
    0xBFF0000000000000ULL,  // -1.0
    0x0010000000000000ULL,  // Minimum positive normal
    0x3EF0000000000000ULL,  // 1.0 * 2^-16
    0x3F00000000000000ULL,  // 1.0 * 2^-15
    0x3F70000000000000ULL,  // 1.0 * 2^-8
    0x3F80000000000000ULL,  // 1.0 * 2^-7
    0x3FB0000000000000ULL,  // 1.0 * 2^-4
    0x3FC0000000000000ULL,  // 1.0 * 2^-3
    0x3FD0000000000000ULL,  // 0.25
    0x3FD4000000000000ULL,  // 0.3125
    0x3FD8000000000000ULL,  // 0.375
    0x3FDC000000000000ULL,  // 0.4375
    0x3FE0000000000000ULL,  // 0.5
    0x3FE4000000000000ULL,  // 0.625
    0x3FE8000000000000ULL,  // 0.75
    0x3FEC000000000000ULL,  // 0.875
    0x3FF0000000000000ULL,  // 1.0
    0x3FF4000000000000ULL,  // 1.25
    0x3FF8000000000000ULL,  // 1.5
    0x3FFC000000000000ULL,  // 1.75
    0x4000000000000000ULL,  // 2.0
    0x4004000000000000ULL,  // 2.5
    0x4008000000000000ULL,  // 3
    0x4010000000000000ULL,  // 4
    0x4020000000000000ULL,  // 8
    0x4030000000000000ULL,  // 16
    0x4060000000000000ULL,  // 2^7
    0x4070000000000000ULL,  // 2^8
    0x40E0000000000000ULL,  // 2^15
    0x40F0000000000000ULL,  // 2^16
    0x7FF0000000000000ULL,  // +inf
    0x7FF8000000000000ULL,  // Canonical NaN
};

TEST_CASE("FLI.D", "[Zfa]") {
    uint32_t value = 0;
    Assembler as(reinterpret_cast<uint8_t*>(&value), sizeof(value));

    for (size_t i = 0; i < fli_constants.size(); i++) {
        const auto constant = fli_constants[i];
        double fconstant{};
        std::memcpy(&fconstant, &constant, sizeof(fconstant));

        as.FLI_D(f10, fconstant);

        const auto op_base = 0xF2100553;
        const auto verify = op_base | (i << 15);
        REQUIRE(value == verify);

        as.RewindBuffer();
    }
}

TEST_CASE("FLI.H", "[Zfa]") {
    uint32_t value = 0;
    Assembler as(reinterpret_cast<uint8_t*>(&value), sizeof(value));

    for (size_t i = 0; i < fli_constants.size(); i++) {
        const auto constant = fli_constants[i];
        double fconstant{};
        std::memcpy(&fconstant, &constant, sizeof(fconstant));

        as.FLI_H(f10, fconstant);

        const auto op_base = 0xF4100553;
        const auto verify = op_base | (i << 15);
        REQUIRE(value == verify);

        as.RewindBuffer();
    }
}

TEST_CASE("FLI.S", "[Zfa]") {
    uint32_t value = 0;
    Assembler as(reinterpret_cast<uint8_t*>(&value), sizeof(value));

    for (size_t i = 0; i < fli_constants.size(); i++) {
        const auto constant = fli_constants[i];
        double fconstant{};
        std::memcpy(&fconstant, &constant, sizeof(fconstant));

        as.FLI_S(f10, fconstant);

        const auto op_base = 0xF0100553;
        const auto verify = op_base | (i << 15);
        REQUIRE(value == verify);

        as.RewindBuffer();
    }
}
