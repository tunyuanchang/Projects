#ifndef NEWENEMY_HPP
#define NEWENEMY_HPP
#include "Enemy.hpp"

class NewEnemy : public Enemy {
public:
	NewEnemy(int x, int y);
	void Update(float deltaTime)override;
};
#endif // NORMALENEMY_HPP
