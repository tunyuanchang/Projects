#include <allegro5/base.h>
#include <cmath>
#include <string>

#include "AudioHelper.hpp"
#include "PockyBullet.hpp"
#include "Group.hpp"
#include "PlateletTurret.hpp"
#include "PlayScene.hpp"
#include "Point.hpp"
#include "Enemy.hpp"
#include "ShootEffect.hpp"

const int PlateletTurret::Price = 35;
PlateletTurret::PlateletTurret(float x, float y) :
	Turret("play/turret-2.png", x, y, Price, 0.5, 50) {
	// Move center downward, since we the turret head is slightly biased upward.
	Anchor.y += 8.0f / GetBitmapHeight();
}
void PlateletTurret::CreateBullet() {
	Engine::Point diff = Engine::Point(cos(Rotation - ALLEGRO_PI / 2), sin(Rotation - ALLEGRO_PI / 2));
	float rotation = atan2(diff.y, diff.x);
	Engine::Point normalized = diff.Normalize();
	Engine::Point normal = Engine::Point(-normalized.y, normalized.x);
	// Change bullet position to the front of the gun barrel.
	// TODO 3 (1/2): Add a Shoot Effect here.
	getPlayScene()->EffectGroup->AddNewObject(new ShootEffect(Position.x + normalized.x * 36 - normal.x * 4 , Position.y + normalized.y * 36 + normal.y * 4));
	getPlayScene()->BulletGroup->AddNewObject(new PockyBullet(Position + normalized * 36 - normal * 6, diff, rotation, this));
	getPlayScene()->BulletGroup->AddNewObject(new PockyBullet(Position + normalized * 36 + normal * 6, diff, rotation, this));
	AudioHelper::PlayAudio("laser.wav");
}
void PlateletTurret::Update(float deltaTime){
	Sprite::Update(deltaTime);
	PlayScene* scene = getPlayScene();
	if (!Enabled)
		return;
	if (Target) {
		if (Target->Position.x < Position.x) {
			Target->lockedTurrets.erase(lockedTurretIterator);
			Target = nullptr;
			lockedTurretIterator = std::list<Turret*>::iterator();
		}
	}
	if (!Target) {
		// Lock first seen target.
		// Can be improved by Spatial Hash, Quad Tree, ...
		// However simply loop through all enemies is enough for this program.
		int ty = static_cast<int>(floor(Position.y / PlayScene::BlockSize));
		int ey;
		for (auto& it : scene->EnemyGroup->GetObjects()) {
            ey = static_cast<int>(floor(it->Position.y / PlayScene::BlockSize));
			if (it->Position.x > Position.x && ey >= ty-1 && ey <= ty +1) {
				Target = dynamic_cast<Enemy*>(it);
				Target->lockedTurrets.push_back(this);
				lockedTurretIterator = std::prev(Target->lockedTurrets.end());
				break;
			}
		}
	}
	if (Target) {
		Engine::Point originRotation = Engine::Point(cos(Rotation - ALLEGRO_PI / 2), sin(Rotation - ALLEGRO_PI / 2));
		Engine::Point targetRotation = (Target->Position - Position).Normalize();
		float maxRotateRadian = rotateRadian * deltaTime;
		float cosTheta = originRotation.Dot(targetRotation);
		// Might have floating-point precision error.
		if (cosTheta > 1) cosTheta = 1;
		else if (cosTheta < -1) cosTheta = -1;
		float radian = acos(cosTheta);
		Engine::Point rotation;
		if (abs(radian) <= maxRotateRadian)
			rotation = targetRotation;
		else
			rotation = ((abs(radian) - maxRotateRadian) * originRotation + maxRotateRadian * targetRotation) / radian;
		// Add 90 degrees (PI/2 radian), since we assume the image is oriented upward.
		Rotation = atan2(rotation.y, rotation.x) + ALLEGRO_PI / 2;
		// Shoot reload.
		reload -= deltaTime;
		if (reload <= 0) {
			// shoot.
			reload = coolDown;
			CreateBullet();
		}
	}
}
