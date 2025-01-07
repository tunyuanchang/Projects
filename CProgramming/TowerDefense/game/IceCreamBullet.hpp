#ifndef ICECREAMBULLET_HPP
#define ICECREAMBULLET_HPP
#include "Bullet.hpp"

class Enemy;
class Turret;
namespace Engine {
struct Point;
}  // namespace Engine

class IceCreamBullet : public Bullet {
public:
	explicit IceCreamBullet(Engine::Point position, Engine::Point forwardDirection, float rotation, Turret* parent);
	void OnExplode(Enemy* enemy) override;
};
#endif // ICECREAMBULLET_HPP
