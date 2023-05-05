#include "gui_manager.hpp"
#include "tools.hpp"
#include "mathematics.hpp"

using std::make_shared;

void GuiManager::update(const dvec2 & cursorPosition, const bool isLmbPressed)
{
	Tools::setCursorType(CursorType::ARROW);

	for(const auto & [guiRectangleId, guiRectangle] : _guiRectangles)
	{
		guiRectangle->update();
	}

	for(const auto & [guiLabelId, guiLabel] : _guiLabels)
	{
		guiLabel->update();
	}

	for(const auto & [guiButtonId, guiButton] : _guiButtons)
	{
		guiButton->update(cursorPosition, isLmbPressed);
	}

	for(const auto & [guiWaveformId, guiWaveform] : _guiWaveforms)
	{
		guiWaveform->update();
	}
}

void GuiManager::_addGuiRectangle(const string & id, const dvec2 & position, const dvec2 & size, const dvec3 & color, const bool isHorizontallyCentered, const bool isVerticallyCentered, const bool isVisible)
{
	if(_isGuiRectangleExisting(id))
	{
		abort();
	}

	shared_ptr<Quad> quad = _createQuad(position, size, color, isHorizontallyCentered, isVerticallyCentered);

	_quads.push_back(quad);

	shared_ptr<GuiRectangle> guiRectangle = make_shared<GuiRectangle>(quad);

	guiRectangle->setVisible(isVisible);

	_guiRectangles.insert({id, guiRectangle});
}

void GuiManager::_addGuiLabel(const string & id, const dvec2 & position, const dvec2 & size, const dvec3 & color, const string & content, const bool isHorizontallyCentered, const bool isVerticallyCentered, const bool isVisible)
{
	if(_isGuiLabelExisting(id))
	{
		abort();
	}

	shared_ptr<Text> text = _createText(position, size, color, content, isHorizontallyCentered, isVerticallyCentered);

	_texts.push_back(text);

	shared_ptr<GuiLabel> guiLabel = make_shared<GuiLabel>(text);

	guiLabel->setVisible(isVisible);

	_guiLabels.insert({id, guiLabel});
}

void GuiManager::_addGuiButton(const string & id, const dvec2 & position, const dvec2 & size, const dvec3 & quadColor, const dvec3 & textColor, const string & content, const bool isHorizontallyCentered, const bool isVerticallyCentered, const bool isHoverable, const bool isPressable, const bool isVisible)
{
	if(_isGuiButtonExisting(id))
	{
		abort();
	}

	shared_ptr<Quad> quad = _createQuad(position, size, quadColor, isHorizontallyCentered, isVerticallyCentered);

	_quads.push_back(quad);

	shared_ptr<Text> text = nullptr;

	if(!content.empty())
	{
		text = _createText(position, size, textColor, content, isHorizontallyCentered, isVerticallyCentered);

		_texts.push_back(text);
	}

	shared_ptr<GuiButton> guiButton = make_shared<GuiButton>(quad, text);

	guiButton->setVisible(isVisible);
	guiButton->setHoverable(isHoverable);
	guiButton->setPressable(isPressable);

	_guiButtons.insert({id, guiButton});
}

void GuiManager::_addGuiWaveform(const string & id, const dvec2 & position, const dvec2 & size, const dvec3 & color, const bool isHorizontallyCentered, const bool isVerticallyCentered, const bool isVisible)
{
	if(_isGuiWaveformExisting(id))
	{
		abort();
	}

	shared_ptr<Line> line = _createLine(position, size, color, isHorizontallyCentered, isVerticallyCentered);

	_lines.push_back(line);

	shared_ptr<GuiWaveform> guiWaveform = make_shared<GuiWaveform>(line);

	guiWaveform->setVisible(isVisible);

	_guiWaveforms.insert({id, guiWaveform});
}

const shared_ptr<Quad> GuiManager::_createQuad(const dvec2 & position, const dvec2 & size, const dvec3 & color, const bool isHorizontallyCentered, const bool isVerticallyCentered) const
{
	shared_ptr<Quad> quad;

	if(!isHorizontallyCentered && !isVerticallyCentered)
	{
		quad = make_shared<Quad>(_corneredVertexBuffer);
	}
	else if(isHorizontallyCentered && isVerticallyCentered)
	{
		quad = make_shared<Quad>(_centeredVertexBuffer);
	}
	else if(isHorizontallyCentered && !isVerticallyCentered)
	{
		quad = make_shared<Quad>(_horizontallyCenteredVertexBuffer);
	}
	else if(!isHorizontallyCentered && isVerticallyCentered)
	{
		quad = make_shared<Quad>(_verticallyCenteredVertexBuffer);
	}
	else
	{
		abort();
	}

	quad->setPosition(position);
	quad->setSize(size);
	quad->setColor(color);

	return quad;
}

const shared_ptr<Text> GuiManager::_createText(const dvec2 & position, const dvec2 & size, const dvec3 & color, const string & content, const bool isHorizontallyCentered, const bool isVerticallyCentered) const
{
	shared_ptr<Text> text;

	if(!isHorizontallyCentered && !isVerticallyCentered)
	{
		text = make_shared<Text>(_corneredVertexBuffer, _fontTextureBuffer, content);
	}
	else if(isHorizontallyCentered && isVerticallyCentered)
	{
		text = make_shared<Text>(_centeredVertexBuffer, _fontTextureBuffer, content);
	}
	else if(isHorizontallyCentered && !isVerticallyCentered)
	{
		text = make_shared<Text>(_horizontallyCenteredVertexBuffer, _fontTextureBuffer, content);
	}
	else if(!isHorizontallyCentered && isVerticallyCentered)
	{
		text = make_shared<Text>(_verticallyCenteredVertexBuffer, _fontTextureBuffer, content);
	}
	else
	{
		abort();
	}

	text->setPosition(position);
	text->setSize(size);
	text->setColor(color);

	return text;
}

const shared_ptr<Line> GuiManager::_createLine(const dvec2 & position, const dvec2 & size, const dvec3 & color, const bool isHorizontallyCentered, const bool isVerticallyCentered) const
{
	const vector<dvec2> vertices = {dvec2(-1.0f, 0.0), dvec2(1.0f, 0.0)};
	const shared_ptr<VertexBuffer> vertexBuffer = make_shared<VertexBuffer>(vertices, isHorizontallyCentered, isVerticallyCentered);
	const shared_ptr<Line> line = make_shared<Line>(vertexBuffer);

	line->setPosition(position);
	line->setSize(size);
	line->setColor(color);

	return line;
}

const bool GuiManager::_isGuiRectangleExisting(const string & id) const
{
	return _guiRectangles.find(id) != _guiRectangles.end();
}

const bool GuiManager::_isGuiLabelExisting(const string & id) const
{
	return _guiLabels.find(id) != _guiLabels.end();
}

const bool GuiManager::_isGuiButtonExisting(const string & id) const
{
	return _guiButtons.find(id) != _guiButtons.end();
}

const bool GuiManager::_isGuiWaveformExisting(const string & id) const
{
	return _guiWaveforms.find(id) != _guiWaveforms.end();
}

void GuiManager::inject(const shared_ptr<ImageLoader> & imageLoader)
{
	if(imageLoader == nullptr)
	{
		abort();
	}

	_imageLoader = imageLoader;
}

const vector<shared_ptr<Quad>> & GuiManager::getQuads() const
{
	return _quads;
}

const vector<shared_ptr<Text>> & GuiManager::getTexts() const
{
	return _texts;
}

const vector<shared_ptr<Line>> & GuiManager::getLines() const
{
	return _lines;
}

const shared_ptr<GuiRectangle> & GuiManager::getGuiRectangle(const string & id) const
{
	if(!_isGuiRectangleExisting(id))
	{
		abort();
	}

	return _guiRectangles.at(id);
}

const shared_ptr<GuiLabel> & GuiManager::getGuiLabel(const string & id) const
{
	if(!_isGuiLabelExisting(id))
	{
		abort();
	}

	return _guiLabels.at(id);
}

const shared_ptr<GuiButton> & GuiManager::getGuiButton(const string & id) const
{
	if(!_isGuiButtonExisting(id))
	{
		abort();
	}

	return _guiButtons.at(id);
}

const shared_ptr<GuiWaveform> & GuiManager::getGuiWaveform(const string & id) const
{
	if(!_isGuiWaveformExisting(id))
	{
		abort();
	}

	return _guiWaveforms.at(id);
}