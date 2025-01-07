#include <allegro5/base.h>
#include <cmath>
#include <string>

#include "AudioHelper.hpp"
#include "IceCreamBullet.hpp"
#include "Group.hpp"
#include "WBCellTurret.hpp"
#include "PlayScene.hpp"
#include "Point.hpp"
#include "Enemy.hpp"

const int WBCellTurret::Price = 20;
WBCellTurret::WBCellTurret(float x, float y) :
    // TODO 2 (2/8): You can imitate the 2 files: 'FreezeTurret.hpp', 'FreezeTurret.cpp' to create a new turret.
	Turret("play/turret-1.png", x, y, Price, 0.5, 30) {
	// Move center downward, since we the turret head is slightly biased upward.
	Anchor.y += 8.0f / GetBitmapHeight();
}
void WBCellTurret::CreateBullet() {
	Engine::Point diff = Engine::Point(1,0);
	float rotation = ALLEGRO_PI / 2;
	getPlayScene()->BulletGroup->AddNewObject(new IceCreamBullet(Position , diff, rotation, this));
	AudioHelper::PlayAudio("gun.wav");
}
