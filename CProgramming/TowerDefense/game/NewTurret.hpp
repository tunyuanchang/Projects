#ifndef NewTURRET_HPP
#define NewTURRET_HPP
#include "Turret.hpp"

class NewTurret: public Turret {
public:
	static const int Price;
	int hp;
    NewTurret(float x, float y);
	void CreateBullet() override;
};
#endif // NewTURRET_HPP
