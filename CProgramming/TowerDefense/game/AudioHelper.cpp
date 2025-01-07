#include <allegro5/allegro_audio.h>

#include "Allegro5Exception.hpp"
#include "AudioHelper.hpp"
#include "LOG.hpp"
#include "Resources.hpp"

float AudioHelper::BGMVolume = 1.0;
float AudioHelper::SFXVolume = 1.0;
ALLEGRO_SAMPLE_ID AudioHelper::PlayAudio(const std::string& audio) {
	ALLEGRO_SAMPLE* sample = Engine::Resources::GetInstance().GetSample(audio).get();
	ALLEGRO_SAMPLE_ID id;
	if (!al_play_sample(sample, SFXVolume, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, &id))
		Engine::LOG(Engine::INFO) << "failed to play audio (once)";
	else
		Engine::LOG(Engine::VERBOSE) << "played audio (once)";
	return id;
}
ALLEGRO_SAMPLE_ID AudioHelper::PlayBGM(const std::string& audio) {
	ALLEGRO_SAMPLE* sample = Engine::Resources::GetInstance().GetSample(audio).get();
	ALLEGRO_SAMPLE_ID id;
	if (!al_play_sample(sample, BGMVolume, 0.0, 1.0, ALLEGRO_PLAYMODE_LOOP, &id))
		Engine::LOG(Engine::INFO) << "failed to play audio (bgm)";
	else
		Engine::LOG(Engine::VERBOSE) << "played audio (bgm)";
	return id;
}
void AudioHelper::StopBGM(ALLEGRO_SAMPLE_ID sample) {
	// No need to stop BGM by ourselves since the audio stops when the sample is destroyed.
	al_stop_sample(&sample);
	Engine::LOG(Engine::INFO) << "stopped audio (bgm)";
}
std::shared_ptr<ALLEGRO_SAMPLE_INSTANCE> AudioHelper::PlaySample(const std::string& audio, bool loop, float volume, float position) {
	// Not safe if release resource while playing, however we only free while change scene, so it's fine.
	std::shared_ptr<ALLEGRO_SAMPLE_INSTANCE> smart_ptr = Engine::Resources::GetInstance().GetSampleInstance(audio);
	ALLEGRO_SAMPLE_INSTANCE* sample_instance = smart_ptr.get();
	if (!al_set_sample_instance_playmode(sample_instance, loop ? ALLEGRO_PLAYMODE_LOOP : ALLEGRO_PLAYMODE_ONCE))
		throw Engine::Allegro5Exception("failed to set audio play mode (sample)");
    if (!al_attach_sample_instance_to_mixer(sample_instance, al_get_default_mixer()))
		throw Engine::Allegro5Exception("failed to attach mixer to audio (sample)");
	if (volume != 1)
		ChangeSampleVolume(smart_ptr, volume);
	if (position != 0)
		ChangeSamplePosition(smart_ptr, position);
    if (!al_play_sample_instance(sample_instance))
		Engine::LOG(Engine::INFO) << "failed to play audio (sample)";
	else
		Engine::LOG(Engine::VERBOSE) << "played audio (sample)";
	return smart_ptr;
}
void AudioHelper::ChangeSampleVolume(std::shared_ptr<ALLEGRO_SAMPLE_INSTANCE> sample_instance, float volume) {
	if (!al_set_sample_instance_gain(sample_instance.get(), volume))
		throw Engine::Allegro5Exception(("failed to change sample volume to " + std::to_string(volume)).c_str());
}
void AudioHelper::ChangeSamplePosition(std::shared_ptr<ALLEGRO_SAMPLE_INSTANCE> sample_instance, float position) {
	// Get sample frequency (samples per second)
	unsigned int sample_index = al_get_sample_instance_frequency(sample_instance.get()) * position;
	if (!al_set_sample_instance_position(sample_instance.get(), sample_index))
		throw Engine::Allegro5Exception(("failed to change sample position to " + std::to_string(position) + " s").c_str());
}
unsigned int AudioHelper::GetSampleLength(std::shared_ptr<ALLEGRO_SAMPLE_INSTANCE> sample_instance) {
	// Get sample frequency (samples per second)
	return al_get_sample_instance_length(sample_instance.get()) / al_get_sample_instance_frequency(sample_instance.get());
}
void AudioHelper::StopSample(std::shared_ptr<ALLEGRO_SAMPLE_INSTANCE> sample_instance) {
	if (!al_get_sample_instance_playing(sample_instance.get()))
		return;
	// No need to stop BGM by ourselves since the audio stops when the sample is destroyed.
	if (!al_stop_sample_instance(sample_instance.get()))
		Engine::LOG(Engine::INFO) << "failed to stop audio (sample)";
	else
		Engine::LOG(Engine::INFO) << "stopped audio (sample)";
}
