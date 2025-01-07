#include <allegro5/allegro_primitives.h>
#include <allegro5/color.h>
#include <cmath>
#include <random>
#include <string>
#include <vector>

#include "AudioHelper.hpp"
#include "Bullet.hpp"
#include "DirtyEffect.hpp"
#include "Enemy.hpp"
#include "ExplosionEffect.hpp"
#include "GameEngine.hpp"
#include "Group.hpp"
#include "IScene.hpp"
#include "IObject.hpp"
#include "LOG.hpp"
#include "PlayScene.hpp"
#include "Turret.hpp"

PlayScene* Enemy::getPlayScene() {
	return dynamic_cast<PlayScene*>(Engine::GameEngine::GetInstance().GetActiveScene());
}
void Enemy::OnExplode() {
	getPlayScene()->EffectGroup->AddNewObject(new ExplosionEffect(Position.x, Position.y));
	std::random_device dev;
	std::mt19937 rng(dev());
	std::uniform_int_distribution<std::mt19937::result_type> distId(1, 3);
	std::uniform_int_distribution<std::mt19937::result_type> dist(1, 20);
	for (int i = 0; i < 10; i++) {
		// Random add 10 dirty effects.
		getPlayScene()->GroundEffectGroup->AddNewObject(new DirtyEffect("play/dirty-" + std::to_string(distId(rng)) + ".png", dist(rng), Position.x, Position.y));
	}
}
Enemy::Enemy(std::string img, float x, float y, float radius, float speed, float hp, int money, float coolDown, float hit) :
	Engine::Sprite(img, x, y), speed(speed), hp(hp), money(money),coolDown(coolDown),hit(hit) {
	CollisionRadius = radius;
	reachEndTime = 0;
	flag = false;
	Velocity = Engine::Point(speed , 0);
	target = Engine::Point(PlayScene::EndGridPointx , static_cast<int>(floor(Position.y / PlayScene::BlockSize))) * PlayScene::BlockSize + Engine::Point(PlayScene::BlockSize / 2, PlayScene::BlockSize / 2);
}
void Enemy::Hit(float damage) {
	hp -= damage;
	if (hp <= 0) {
		OnExplode();
		// Remove all turret's reference to target.
		for (auto& it: lockedTurrets)
			it->Target = nullptr;
		for (auto& it: lockedBullets)
			it->Target = nullptr;
		getPlayScene()->EarnMoney(money);
		getPlayScene()->EnemyGroup->RemoveObject(objectIterator);
		AudioHelper::PlayAudio("explosion.wav");
	}
}
void Enemy::Update(float deltaTime) {
    float remainSpeed = speed * deltaTime;
    if(!flag){
        Position.x -= Velocity.x * deltaTime;
        Position.y += Velocity.y * deltaTime;
    }
    reload -= deltaTime;
    //turret
    for (auto& it: getPlayScene()->TowerGroup->GetObjects()){
        Turret* tower = dynamic_cast<Turret*>(it);
        if(Position.x  - tower->Position.x >= 0 && Position.x  - tower->Position.x <= PlayScene::BlockSize - 50 && abs(Position.y  - tower->Position.y) <= 5){
            if(reload <= 0){
                reload = coolDown;
                if(tower->hp <= hit){
                    tower->Hit(hit);
                    flag = false;
                    break;
                }
                else{
                    tower->Hit(hit);
                }
            }
            flag = true;
            break;
        }
        flag = false;
    }
    //end
	if(Position.x <= PlayScene::EndGridPointx * PlayScene::BlockSize + PlayScene::BlockSize / 2){
		//Hit(hp);
		OnExplode();
		// Remove all turret's reference to target.
		for (auto& it: lockedTurrets)
			it->Target = nullptr;
		for (auto& it: lockedBullets)
			it->Target = nullptr;
        getPlayScene()->EnemyGroup->RemoveObject(objectIterator);
		getPlayScene()->Hit();
		reachEndTime = 0;
		return;
	}
	Engine::Point vec = target - Position;
	if(!flag) reachEndTime = (vec.Magnitude() - remainSpeed) / speed;
}
void Enemy::Draw() const {
	Sprite::Draw();
	if (PlayScene::DebugMode) {
		// Draw collision radius.
		al_draw_circle(Position.x, Position.y, CollisionRadius, al_map_rgb(255, 0, 0), 2);
	}
}
