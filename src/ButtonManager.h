#ifndef BUTTONMANAGER_H
#define BUTTONMANAGER_H

#include <OneButton.h>
#include "Config.h"


class ButtonManager_
{
public:
    static ButtonManager_ &getInstance();
    bool inMenu;

    void setup();
    void tick();

private:
    ButtonManager_() = default;
};

extern ButtonManager_ &ButtonManager;

#endif // BUTTONMANAGER_H