#include "tone_template_manager.hpp"

void ToneTemplateManager::addToneTemplate(const shared_ptr<ToneTemplate> & toneTemplate)
{
	if(toneTemplate == nullptr)
	{
		abort();
	}

	if(getToneTemplateCount() == Shared::MAX_TONE_TEMPLATES)
	{
		abort();
	}

	_toneTemplates.push_back(toneTemplate);
}

void ToneTemplateManager::removeToneTemplate()
{
	if(_toneTemplates.empty())
	{
		abort();
	}

	_toneTemplates.erase(_toneTemplates.begin() + _toneTemplateIndex);

	if(_toneTemplateIndex == _toneTemplates.size())
	{
		_toneTemplateIndex--;
	}
}

void ToneTemplateManager::setToneTemplateIndex(const int value)
{
	if(value < 0)
	{
		abort();
	}

	if(value > _toneTemplates.size() - 1)
	{
		abort();
	}

	_toneTemplateIndex = value;
}

const shared_ptr<ToneTemplate> & ToneTemplateManager::getToneTemplate() const
{
	if(_toneTemplates.empty())
	{
		abort();
	}

	return _toneTemplates.at(_toneTemplateIndex);
}

const int ToneTemplateManager::getToneTemplateIndex() const
{
	return _toneTemplateIndex;
}

const int ToneTemplateManager::getToneTemplateCount() const
{
	return static_cast<int>(_toneTemplates.size());
}