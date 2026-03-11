#pragma once
#include "TurnInput.h"

class IHandChooser {
public:
    virtual ~IHandChooser() = default;
    virtual void chooseHand(TurnInput& input) = 0;
};
