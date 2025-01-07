#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/color.h>
#include <allegro5/base.h>
#include <cmath>
#include <string>

#include "AudioHelper.hpp"
#include "Group.hpp"
#include "MaxTurret.hpp"
#include "PlayScene.hpp"
#include "Point.hpp"
#include "Enemy.hpp"
#include "Sprite.hpp"
#include "GameEngine.hpp"
#include "Collider.hpp"
#include "ExplosionEffect.hpp"

const int MaxTurret::Price = 80;
MaxTurret::MaxTurret(float x, float y) :
    // TODO 2 (2/8): You can imitate the 2 files: 'FreezeTurret.hpp', 'FreezeTurret.cpp' to create a new turret.
	Turret("play/turret-4.png", x, y, Price, 0.5, 1) {
	// Move center downward, since we the turret head is slightly biased upward.
	Anchor.y += 8.0f / GetBitmapHeight();
}
void MaxTurret::CreateBullet(){ }
void MaxTurret::OnExplode(){
    for (auto& it: getPlayScene()->EnemyGroup->GetObjects()){
        Enemy* enemy = dynamic_cast<Enemy*>(it);
		if (pow((Position.x - enemy->Position.x), 2) + pow((Position.y - enemy->Position.y), 2)  <= pow(250,2) + enemy->CollisionRadius) {
			enemy->Hit(1000);
		}
    }
    getPlayScene()->EffectGroup->AddNewObject(new ExplosionEffect(Position.x, Position.y));
    getPlayScene()->ModifyReadMapTiles(Position.x, Position.y);
}
void MaxTurret::Draw() const{
    Sprite::Draw();
    al_draw_circle(Position.x,Position.y,250,al_map_rgb(255,0,0),2);
}
