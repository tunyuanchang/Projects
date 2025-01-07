#ifndef AUDIOHELPER_HPP
#define AUDIOHELPER_HPP
#include <allegro5/allegro_audio.h>
#include <string>
#include <memory>


class AudioHelper {
private:
	AudioHelper() = default;
public:
	static float BGMVolume;
	static float SFXVolume;
	static ALLEGRO_SAMPLE_ID PlayAudio(const std::string& audio);
	static ALLEGRO_SAMPLE_ID PlayBGM(const std::string& audio);
	static void StopBGM(ALLEGRO_SAMPLE_ID sample);
	static std::shared_ptr<ALLEGRO_SAMPLE_INSTANCE> PlaySample(const std::string& audio, bool loop = false, float volume = 1, float position = 0);
	static void StopSample(std::shared_ptr<ALLEGRO_SAMPLE_INSTANCE> sample_instance);
	static void ChangeSampleVolume(std::shared_ptr<ALLEGRO_SAMPLE_INSTANCE> sample_instance, float volume);
	static void ChangeSamplePosition(std::shared_ptr<ALLEGRO_SAMPLE_INSTANCE> sample_instance, float position);
	static unsigned int GetSampleLength(std::shared_ptr<ALLEGRO_SAMPLE_INSTANCE> sample_instance);
};
#endif // AUDIOHELPER_HPP
