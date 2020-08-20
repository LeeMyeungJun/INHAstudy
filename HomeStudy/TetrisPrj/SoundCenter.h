#pragma once

using namespace std;
class SoundCenter
{

private:
	GameCenter* m_gameCenter;

	/*System * fmodSystem;

	Channel* bgmChannel;
	Channel* sfxChannel;

	Sound* bgm;
	map<string, Sound*> soundHash;
*/
public:
	SoundCenter(GameCenter* wrapped);
	~SoundCenter();


	void AddSFX(string path, string musicName);
	void AddBGM(string path);

	void PlaySFX(string soundName);
	void PlayBGM();

	void Stop();

	void Destroy();


	
};

