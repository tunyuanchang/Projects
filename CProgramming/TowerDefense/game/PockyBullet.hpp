#ifndef POCKYBULLET_HPP
#define POCKYBULLET_HPP
#include "Bullet.hpp"

class Enemy;
class Turret;
namespace Engine {
struct Point;
}  // namespace Engine

class PockyBullet : public Bullet {
public:
	explicit PockyBullet(Engine::Point position, Engine::Point forwardDirection, float rotation, Turret* parent);
	void OnExplode(Enemy* enemy) override;
};
#endif // POCKYBULLET_HPP
