#pragma once
#include "IRule.h"

class RuleConway : public IRule {
public:
    [[nodiscard]] int apply(int currentState, int nbNeighbours) const override {
        if (currentState == 1)
            return (nbNeighbours == 2 || nbNeighbours == 3) ? 1 : 0;
        else
            return (nbNeighbours == 3) ? 1 : 0;
    }
};
