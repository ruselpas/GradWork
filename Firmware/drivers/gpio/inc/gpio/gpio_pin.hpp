#pragma once

#include <memory>

namespace Gpio::Pins
{
    extern const std::uint8_t Display_DataCommand;
    extern const std::uint8_t Display_Reset;
}//namespace Gpio::Pins

namespace Gpio
{


enum class Direction
{
        Input
    ,   Output
};

class GpioPin
{

public:

    GpioPin(
            std::uint8_t _pinNumber
        ,   Gpio::Direction _gpioDirection
    );

    ~GpioPin();

public:

    void set();

    void reset();

private:

    class GpioBackendImpl;
    std::unique_ptr<GpioBackendImpl> m_pGpioBackendImpl;
};

GpioPin getGpioPin ( std::uint8_t _pinNumber, Direction _pinDirection );

} // namespace Gpio
