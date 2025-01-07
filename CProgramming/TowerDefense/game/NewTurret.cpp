#include <allegro5/base.h>
#include <cmath>
#include <string>

#include "AudioHelper.hpp"
#include "NewBullet.hpp"
#include "Group.hpp"
#include "NewTurret.hpp"
#include "PlayScene.hpp"
#include "Point.hpp"
#include "Enemy.hpp"

const int NewTurret::Price = 50;

NewTurret::NewTurret(float x, float y) :
	Turret("play/turret-3.png", x, y, Price, 0.5, 30) {
	Anchor.y += 8.0f / GetBitmapHeight();
}
void NewTurret::CreateBullet() {
	Engine::Point diff = Engine::Point(1,0);
	float rotation = ALLEGRO_PI / 2;
	getPlayScene()->BulletGroup->AddNewObject(new NewBullet(Position , diff, rotation, this));
	AudioHelper::PlayAudio("gun.wav");
}
