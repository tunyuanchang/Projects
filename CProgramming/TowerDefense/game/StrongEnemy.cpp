#include <string>
#include <cmath>

#include "StrongEnemy.hpp"

StrongEnemy::StrongEnemy(int x, int y) : Enemy("play/enemy-5.png", x, y, 12, 45, 50, 50, 0.25, 10) {
	// Use bounding circle to detect collision is for simplicity, pixel-perfect collision can be implemented quite easily,
	// and efficiently if we use AABB collision detection first, and then pixel-perfect collision.
    center_y = y;
}
void StrongEnemy::Update(float deltaTime){
    if(!flag) Position.y = center_y  + 30 * sin(Position.x / 10);
    Enemy::Update(deltaTime);
}
