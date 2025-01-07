// [main.cpp]
// this template is provided for the 2D tower defense game.
// Program entry point.
// Returns program exit code.
#include "GameEngine.hpp"
#include "LOG.hpp"
#include "LoseScene.hpp"
#include "PlayScene.hpp"
#include "StageSelectScene.hpp"
#include "SettingScene.hpp"
#include "WinScene.hpp"
#include "Start_Scene.hpp"

int main(int argc, char **argv) {
	Engine::LOG::SetConfig(true);
	Engine::GameEngine& game = Engine::GameEngine::GetInstance();
    // TODO 1 (1/3): Add a New Scene here
	game.AddNewScene("stage-select", new StageSelectScene());
	game.AddNewScene("setting", new SettingScene());
	game.AddNewScene("play", new PlayScene());
	game.AddNewScene("lose", new LoseScene());
	game.AddNewScene("win", new WinScene());
	game.AddNewScene("start_scene", new StartScene());

	game.Start("start_scene", 60, 1536, 896);
	return 0;
}
