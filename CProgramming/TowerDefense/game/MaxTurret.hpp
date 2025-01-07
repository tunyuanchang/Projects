#ifndef MAXTURRET_HPP
#define MAXTURRET_HPP
#include "Turret.hpp"

class MaxTurret: public Turret {
public:
	static const int Price;
	int hp;
    MaxTurret(float x, float y);
    void CreateBullet() override;
    void Draw() const override;
    void OnExplode() override;
};
#endif // MAXURRET_HPP

