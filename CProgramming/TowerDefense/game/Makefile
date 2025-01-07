# Makefile for Windows
CXX = g++
CXXFLAGS = -std=c++11 -IC:\allegro-x86_64-w64-mingw32-gcc-9.2.0-posix-seh-static-5.2.6.0\allegro\include -O2
LDFLAGS = -lm -Wall -Wextra
LDLIBS = -LC:\allegro-x86_64-w64-mingw32-gcc-9.2.0-posix-seh-static-5.2.6.0\allegro\lib -lallegro_monolith.dll
exe = TowerDefense.exe
obj = Allegro5Exception.o AudioHelper.o Bullet.o Collider.o DirtyEffect.o Enemy.o ExplosionEffect.o FireBullet.o GameEngine.o Group.o IControl.o Image.o ImageButton.o IObject.o IScene.o Label.o LaserBullet.o LaserTurret.o LOG.o LoseScene.o MachineGunTurret.o MissileBullet.o MissileTurret.o Plane.o PlaneEnemy.o PlayScene.o Point.o Resources.o Slider.o SoldierEnemy.o Sprite.o StageSelectScene.o TankEnemy.o Turret.o TurretButton.o WinScene.o main.o

.PHONY: all clean

all: $(obj)
	$(CXX) -o $(exe) $(obj) $(LDFLAGS) $(LDLIBS)

%.o: %.cpp
	$(CXX) -c $< -o $@ $(CXXFLAGS)

clean:
	del $(exe) $(obj)
