#include "EmGineAudioPlayer.h"

using namespace std;
using namespace FMOD;

#pragma region Static Variables
AudioSystem *EmGineAudioPlayer::m_system;
ChannelGroup* EmGineAudioPlayer::m_mainChannelGroup;
//vector<const char*>*  EmGineAudioPlayer::m_files;
vector<Channel*>* EmGineAudioPlayer::m_channels;
vector<Audio*>* EmGineAudioPlayer::m_sounds;
#pragma endregion

EmGineAudioPlayer::EmGineAudioPlayer(int channels)
{
	init(channels);
}


EmGineAudioPlayer::~EmGineAudioPlayer()
{
	m_system->release();
	m_sounds->clear();
	m_channels->clear();
}

void EmGineAudioPlayer::init(int channels)
{
	if(m_system)
		return;

	m_channels = new vector<Channel*>;
	m_sounds = new vector<Audio*>;

	if(FMOD::System_Create(&m_system))
		return;
	int driverCount;
	if(m_system->getNumDrivers(&driverCount))
		return;

	m_system->init(channels, FMOD_INIT_NORMAL, nullptr);
}

void EmGineAudioPlayer::createSound(const char * file)
{
	Audio* newSound;

	if(m_system->createSound(file, FMOD_DEFAULT | FMOD_ACCURATETIME, nullptr, &newSound))
		printf("failed to create sound");

	m_sounds->push_back(newSound);
	m_channels->push_back(nullptr);
}

void EmGineAudioPlayer::createStream(const char * file)
{
	Audio* newSound;
	if(m_system->createStream(file, FMOD_DEFAULT | FMOD_ACCURATETIME, nullptr, &newSound))
		printf("failed to create sound");

	m_sounds->push_back(newSound);
	m_channels->push_back(nullptr);
}

void EmGineAudioPlayer::play(bool loop, bool newInst, unsigned int index)
{

	//if(m_channels[0][index])
	//	if(isStoped(index))
	//		m_channels[0][index]->setPosition(0, FMOD_TIMEUNIT_MS);
	if(newInst && m_channels[0][index])
		m_sounds->push_back(m_sounds[0][index]),
		m_channels->push_back(nullptr),
		index = m_channels->size() - 1;


	if(!m_channels[0][index] || (m_channels[0][index] ? isStoped(index) : false))
		m_system->playSound(m_sounds[0][index], nullptr, true, &m_channels[0][index]);

	if(loop)
		m_channels[0][index]->setMode(FMOD_LOOP_NORMAL),
		m_channels[0][index]->setLoopCount(-1);
	else
		m_channels[0][index]->setMode(FMOD_LOOP_OFF);

	m_channels[0][index]->setPaused(false);
}

void EmGineAudioPlayer::pause(unsigned int index)
{
	m_channels[0][index]->setPaused(true);
}

void EmGineAudioPlayer::pauseAll()
{
	ChannelGroup* cg;
	m_system->getMasterChannelGroup(&cg);
	cg->setPaused(true);
}

void EmGineAudioPlayer::stop(unsigned int index)
{
	unsigned int length;

	Audio* cs;
	m_channels[0][index]->getCurrentSound(&cs);
	cs->getLength(&length, FMOD_TIMEUNIT_MS);
	printf("song length: %d\n", length);

	m_channels[0][index]->stop();
}

void EmGineAudioPlayer::stopAll()
{
	ChannelGroup* cg;
	m_system->getMasterChannelGroup(&cg);
	cg->stop();
}

bool EmGineAudioPlayer::isStoped(unsigned int index)
{
	bool play;
	m_channels[0][index]->isPlaying(&play);
	return !play;
}

bool EmGineAudioPlayer::isPaused(unsigned int index)
{
	bool pause;
	m_channels[0][index]->getPaused(&pause);
	return pause;
}

unsigned int EmGineAudioPlayer::size()
{
	return m_channels->size();
}

void EmGineAudioPlayer::setVolume(float vol, unsigned int index)
{
	m_channels[0][index]->setVolume(vol);
}

void EmGineAudioPlayer::setMasterVolume(float vol)
{
	ChannelGroup* cg;
	m_system->getMasterChannelGroup(&cg);
	cg->setVolume(vol);
}

void EmGineAudioPlayer::mute(unsigned int index)
{
	bool mute;
	m_channels[0][index]->getMute(&mute);
	m_channels[0][index]->setMute(!mute);
}

void EmGineAudioPlayer::muteAll()
{
	ChannelGroup* cg;
	m_system->getMasterChannelGroup(&cg);
	bool mute;
	cg->getMute(&mute);
	cg->setMute(!mute);
}

void EmGineAudioPlayer::update()
{
	m_system->update();
}







// for later reference
FMOD_RESULT mycallback(FMOD_CHANNELCONTROL *chanCtrl, FMOD_CHANNELCONTROL_TYPE ctrlType, FMOD_CHANNELCONTROL_CALLBACK_TYPE callbackType, void *commandData1, void *commandData2)
{
	if(ctrlType == FMOD_CHANNELCONTROL_CHANNEL)
	{
		Channel *channel = (Channel *) chanCtrl;
		// Channel specific functions here...
	} else
	{
		//	ChannelGroup *group = (ChannelGroup *) chanCtrl;
			// ChannelGroup specific functions here...
	}

	// ChannelControl generic functions here...
	return FMOD_OK;
}
