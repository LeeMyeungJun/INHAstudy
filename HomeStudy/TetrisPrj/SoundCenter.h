#pragma once

using namespace std;
class SoundCenter
{
	/*System * fmodSystem;

	Channel* bgmChannel;
	Channel* sfxChannel;

	Sound* bgm;
	map<string, Sound*> soundHash;
*/
public:
	SoundCenter();
	~SoundCenter();


	void AddSFX(string path, string musicName);
	void AddBGM(string path);

	void PlaySFX(string soundName);
	void PlayBGM();

	void Stop();

	void Destroy();


	
};

