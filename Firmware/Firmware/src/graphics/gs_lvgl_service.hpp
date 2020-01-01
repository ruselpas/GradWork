#pragma once

#include "display/display_idisplay.hpp"

#include "lvgl.h"
#include "lv_conf.h"

#include <array>
#include <memory>

namespace Graphics
{

class LvglGraphicsService
{

public:

    LvglGraphicsService(
            std::unique_ptr<DisplayDriver::IDisplayDriver>&& _displayDriver
        );

    ~LvglGraphicsService();

    void runTest();

    void executeGlTask();

private:

    static constexpr size_t DispHorRes = LV_HOR_RES_MAX*10;

    using TColorBuf = std::array<lv_color_t,DispHorRes>;

    static lv_disp_buf_t displayBuffer;
    static TColorBuf dispFrameBufFirst;
    static TColorBuf dispFrameBufSecond;

private:
    static constexpr std::uint32_t LvglNotificationTime = 15;
    static constexpr std::uint32_t LvgTaskTime = 1000;
private:

    void initLvglLogger();

    void initGfxTimer();

private:

    std::unique_ptr<DisplayDriver::IDisplayDriver> m_hardwareDisplayDriver;

    lv_disp_drv_t m_glDisplayDriver;
    lv_disp_t* m_glDisplay;
};

std::unique_ptr<LvglGraphicsService> createGraphicsService(
        std::unique_ptr<DisplayDriver::IDisplayDriver>&& _displayDriver
    );

};