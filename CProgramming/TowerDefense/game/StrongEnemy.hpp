#ifndef STRONGENEMY_HPP
#define STRONGENEMY_HPP
#include "Enemy.hpp"

class StrongEnemy : public Enemy {
private:
    float center_y;
public:
	StrongEnemy(int x, int y);
	void Update(float deltaTime)override;
};
#endif // STRONGENEMY_HPP
