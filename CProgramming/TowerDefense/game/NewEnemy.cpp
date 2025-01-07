#include <string>
#include <cmath>

#include "NewEnemy.hpp"

NewEnemy::NewEnemy(int x, int y) : Enemy("play/enemy-3.png", x, y, 16, 20, 50, 50, 0.5, 15) {
}
void NewEnemy::Update(float deltaTime){
    this->Velocity.x = (this->Velocity.x >= 120) ? 120 : this->Velocity.x + 1 * (50 - hp);
    Enemy::Update(deltaTime);
}
