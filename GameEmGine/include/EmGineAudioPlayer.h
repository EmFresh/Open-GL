#pragma once
#include <FMOD/fmod.hpp>
#include <cstdio>

typedef  FMOD::System AudioSystem;
typedef  FMOD::Sound Sound;
class EmGineAudioPlayer
{
public:
	EmGineAudioPlayer(int channels=36);
	~EmGineAudioPlayer();

	void init(int channels = 36);
	void createSound(Sound** sound, const char* file);
	void play(Sound* sound, bool loop=false);
	void pause();
	void stop();
	void setVolume(int vol);

	void releaseSound(Sound* sound);

	//not needed but recomended in certin platforms for each frame
	void update();
private:
	AudioSystem * m_system;
	Sound* m_sound;
};

