#ifndef SETTINGSCENE_HPP
#define SETTINGCENE_HPP
#include <allegro5/allegro_audio.h>
#include <memory>
#include "IScene.hpp"

class SettingScene final : public Engine::IScene {
private:
	std::shared_ptr<ALLEGRO_SAMPLE_INSTANCE> bgmInstance;
public:
	explicit SettingScene() = default;
	void Initialize() override;
	void Terminate() override;
	void BackOnClick(int setting);
	void BGMSlideOnValueChanged(float value);
	void SFXSlideOnValueChanged(float value);
};

#endif // SETTINGSCENE_HPP
