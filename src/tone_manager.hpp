#pragma once

#include "tone.hpp"

#include <memory>
#include <string>
#include <unordered_map>

using std::shared_ptr;
using std::string;
using std::unordered_map;

class ToneManager final
{
public:
	void addTone(const string & id, const shared_ptr<Tone> & tone);

	const shared_ptr<Tone> & getTone(const string & id) const;
	const unordered_map<string, shared_ptr<Tone>> & getTones() const;

private:
	const bool _isToneExisting(const string & id) const;

	unordered_map<string, shared_ptr<Tone>> _tones = {};
};