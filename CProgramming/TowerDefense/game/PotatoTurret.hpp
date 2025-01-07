#ifndef POTATOTURRET_HPP
#define POTATOTURRET_HPP
#include "Turret.hpp"

class PotatoTurret: public Turret {
public:
	static const int Price;
	int hp;
    PotatoTurret(float x, float y);
    void CreateBullet() override;
};
#endif // POTATOTURRET_HPP
