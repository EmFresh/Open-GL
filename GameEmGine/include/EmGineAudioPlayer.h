#pragma once
#include <FMOD/fmod.hpp>
#include <cstdio>
#include <vector>

typedef  FMOD::System AudioSystem;
typedef FMOD::Sound Audio;

class EmGineAudioPlayer
{
public:
	EmGineAudioPlayer(int channels = 36);
	~EmGineAudioPlayer();

	static void init(int channels = 36);


	void createSound(const char* file);

	void createStream(const char* file);

	void play( bool loop = false, bool newInstance = false, unsigned int index = (m_channels->size() - 1));

	void pause(unsigned int index = (m_channels->size() - 1));

	void pauseAll();

	void stop(unsigned int index = (m_channels->size() - 1));

	void stopAll();

	void mute(unsigned int index = (m_channels->size() - 1));

	void muteAll();

	bool isStoped(unsigned int index = (m_channels->size() - 1));

	bool isPaused(unsigned int index = (m_channels->size() - 1));

	unsigned int size();
	/*
	**normal volume levels from 0 -> 1.
	**below 0 will invert sound.
	**increasing level above the normal level may resault in distortion.
	*/
	void setVolume(float vol, unsigned int index = (m_channels->size() - 1));

	void setMasterVolume(float vol);

	//not needed but recomended in certin platforms within their update loop
	static void update();

private:
	static AudioSystem* m_system;
	static FMOD::ChannelGroup* m_mainChannelGroup;
	//static std::vector<const char*>* m_files;
	static std::vector<FMOD::Channel*>* m_channels;
	static std::vector<Audio*>* m_sounds;
};

