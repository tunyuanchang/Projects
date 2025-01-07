#ifndef BOMBTURRET_HPP
#define BOMBTURRET_HPP
#include "Turret.hpp"

class BombTurret: public Turret {
public:
	static const int Price;
    BombTurret(float x, float y);
    void CreateBullet() override;
};
#endif // POTATOURRET_HPP
