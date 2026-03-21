#pragma once

class IRule {
public:
    virtual ~IRule() = default;
    // Retourne le nouvel état (0 ou 1) selon l'état actuel et le nombre de voisins vivants
    [[nodiscard]] virtual int apply(int currentState, int nbNeighbours) const = 0;
};
