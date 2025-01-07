#include <allegro5/color.h>
#include <allegro5/allegro_primitives.h>
#include <cmath>
#include <random>
#include <utility>

#include "AudioHelper.hpp"
#include "ExplosionEffect.hpp"
#include "Enemy.hpp"
#include "GameEngine.hpp"
#include "Group.hpp"
#include "IObject.hpp"
#include "IScene.hpp"
#include "PlayScene.hpp"
#include "Point.hpp"
#include "Turret.hpp"
#include "PlayScene.hpp"

PlayScene* Turret::getPlayScene() {
	return dynamic_cast<PlayScene*>(Engine::GameEngine::GetInstance().GetActiveScene());
}
Turret::Turret(std::string imgTurret, float x, float y, /*float radius,*/ int price, float coolDown, int hp) :
	Sprite(imgTurret, x, y), price(price), coolDown(coolDown), hp(hp) {
	//CollisionRadius = radius;
}
void Turret::Update(float deltaTime) {
	Sprite::Update(deltaTime);
	PlayScene* scene = getPlayScene();
	if (!Enabled)
		return;
	if (Target) {
		if (Target->Position.x < Position.x&& Target->Position.y >= Position.y  && Target->Position.y < Position.y+scene->BlockSize) {
			Target->lockedTurrets.erase(lockedTurretIterator);
			Target = nullptr;
			lockedTurretIterator = std::list<Turret*>::iterator();
		}
		// Shoot reload.
		reload -= deltaTime;
		if (reload <= 0) {
			// shoot.
			reload = coolDown;
			CreateBullet();
		}
	}
	if (!Target) {
		// Lock first seen target.
		// Can be improved by Spatial Hash, Quad Tree, ...
		// However simply loop through all enemies is enough for this program.
		for (auto& it : scene->EnemyGroup->GetObjects()) {
            if (it->Position.x > Position.x && it->Position.y >= Position.y  && it->Position.y < Position.y+scene->BlockSize) {
				Target = dynamic_cast<Enemy*>(it);
				Target->lockedTurrets.push_back(this);
				lockedTurretIterator = std::prev(Target->lockedTurrets.end());
				break;
			}
		}
	}

}
void Turret::OnExplode(){
    getPlayScene()->EffectGroup->AddNewObject(new ExplosionEffect(Position.x, Position.y));
    getPlayScene()->ModifyReadMapTiles(Position.x, Position.y);
	std::random_device dev;
	std::mt19937 rng(dev());
	std::uniform_int_distribution<std::mt19937::result_type> distId(1, 3);
	std::uniform_int_distribution<std::mt19937::result_type> dist(1, 20);
	/*for (int i = 0; i < 10; i++) {
		// Random add 10 dirty effects.
		getPlayScene()->GroundEffectGroup->AddNewObject(new DirtyEffect("play/dirty-" + std::to_string(distId(rng)) + ".png", dist(rng), Position.x, Position.y));
	}*/
}
void Turret::Hit(int h){
    hp -= h;
    if(hp <= 0){
        OnExplode();
        getPlayScene()->TowerGroup->RemoveObject(objectIterator);
        AudioHelper::PlayAudio("explosion.wav");
    }
}
void Turret::Draw() const {
	/*if (Preview) {
		al_draw_filled_circle(Position.x, Position.y, CollisionRadius, al_map_rgba(0, 255, 0, 50));
	}*/
	Sprite::Draw();
	if (PlayScene::DebugMode) {
		// Draw target radius.
		al_draw_circle(Position.x, Position.y, 16, al_map_rgb(0, 0, 255), 2);
	}
}
int Turret::GetPrice() const {
	return price;
}
