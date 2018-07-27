#include "EmGineAudioPlayer.h"

EmGineAudioPlayer::EmGineAudioPlayer(int channels)
{
	if(FMOD::System_Create(&m_system))
		return;
	int driverCount;
	if(m_system->getNumDrivers(&driverCount))
		return;

	m_system->init(channels, FMOD_INIT_NORMAL, nullptr);
}


EmGineAudioPlayer::~EmGineAudioPlayer()
{
	m_system->release();
}

void EmGineAudioPlayer::createSound(Sound** sound, const char * file)
{
	if(m_system->createSound(file, FMOD_DEFAULT, nullptr, &m_sound))
		printf("failed to create sound");
}

void EmGineAudioPlayer::play(Sound* sound, bool loop)
{
	if(loop)
		m_sound->setMode(FMOD_LOOP_NORMAL),
		m_sound->setLoopCount(-1);
	else
		m_sound->setMode(FMOD_LOOP_OFF);

	m_system->playSound(m_sound, nullptr, false, nullptr);
	//m_system.pau
}

void EmGineAudioPlayer::releaseSound(Sound* sound)
{
	sound->release();
}

void EmGineAudioPlayer::update()
{
	m_system->update();
}
