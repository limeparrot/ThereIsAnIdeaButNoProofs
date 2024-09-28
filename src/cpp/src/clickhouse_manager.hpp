#pragma once

#include "config.hpp"

class ClickhouseManager{
  public:
    ClickhouseManager(const Config& config);
    void run();
};
