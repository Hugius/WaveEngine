#pragma once

#include "audio.hpp"

#include <memory>
#include <string>
#include <unordered_map>

using std::shared_ptr;
using std::string;
using std::unordered_map;

class AudioManager final
{
public:
	void createAudio(const string & id, shared_ptr<Audio> audio);

	const shared_ptr<Audio> & getAudio(const string & id) const;

private:
	const bool _isAudioExisting(const string & id) const;

	unordered_map<string, shared_ptr<Audio>> _audios = {};
}