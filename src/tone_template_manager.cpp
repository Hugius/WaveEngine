#include "tone_template_manager.hpp"

void ToneTemplateManager::addToneTemplate(const shared_ptr<ToneTemplate> & tone)
{
	_tones.push_back(tone);
}

void ToneTemplateManager::removeToneTemplate()
{
	if(_tones.empty())
	{
		abort();
	}

	_tones.erase(_tones.begin() + _toneIndex);

	if(_toneIndex == _tones.size())
	{
		_toneIndex--;
	}
}

void ToneTemplateManager::setToneTemplateIndex(const int value)
{
	if(value < 0)
	{
		abort();
	}

	if(value > _tones.size() - 1)
	{
		abort();
	}

	_toneIndex = value;
}

const shared_ptr<ToneTemplate> & ToneTemplateManager::getToneTemplate() const
{
	if(_tones.empty())
	{
		abort();
	}

	return _tones.at(_toneIndex);
}

const int ToneTemplateManager::getToneTemplateIndex() const
{
	return _toneIndex;
}

const int ToneTemplateManager::getToneTemplateCount() const
{
	return static_cast<int>(_tones.size());
}