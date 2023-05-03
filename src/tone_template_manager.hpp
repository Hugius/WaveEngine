#pragma once

#include "tone_template.hpp"

#include <memory>
#include <vector>

using std::shared_ptr;
using std::vector;

class ToneTemplateManager final
{
public:
	void addToneTemplate(const shared_ptr<ToneTemplate> & tone);
	void removeToneTemplate();
	void setToneTemplateIndex(const int value);

	const shared_ptr<ToneTemplate> & getToneTemplate() const;

	const int getToneTemplateIndex() const;
	const int getToneTemplateCount() const;

private:
	vector<shared_ptr<ToneTemplate>> _tones = {};

	int _toneIndex = 0;
};