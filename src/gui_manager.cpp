#include "gui_manager.hpp"
#include "tools.hpp"

using std::make_shared;

void GuiManager::initialize()
{
	_vertexBuffer = make_shared<VertexBuffer>();
	_fontTextureBuffer = make_shared<TextureBuffer>(_imageLoader->getImage(Tools::getRootDirectoryPath() + FONT_PATH));

	_createElement("top", fvec2(-1.0f, 0.95f), fvec2(2.0f, 0.05f), fvec3(0.25f), fvec3(0.0f), "", false, false, false, true);
	_createElement("new", fvec2(-1.0f, 0.95f), fvec2(0.0375f, 0.05f), fvec3(0.25f), fvec3(1.0f), "New", true, true, false, true);
	_createElement("load", fvec2(-0.95f, 0.95f), fvec2(0.05f, 0.05f), fvec3(0.25f), fvec3(1.0f), "Load", true, true, false, true);
	_createElement("save", fvec2(-0.8875f, 0.95f), fvec2(0.05f, 0.05f), fvec3(0.25f), fvec3(1.0f), "Save", true, true, false, true);
	_createElement("waveforms", fvec2(-0.825f, 0.95f), fvec2(0.1125f, 0.05f), fvec3(0.25f), fvec3(1.0f), "Waveforms", true, true, false, true);
	_createElement("exit", fvec2(-0.7f, 0.95f), fvec2(0.05f, 0.05f), fvec3(0.25f), fvec3(1.0f), "Exit", true, true, false, true);

	_createElement("waveforms_menu", fvec2(-0.75f), fvec2(1.5f), fvec3(0.25f), fvec3(0.0f), "", false, false, false, false);
	_createElement("waveforms_close", fvec2(0.725f, 0.675f), fvec2(0.025f, 0.075f), fvec3(0.25f), fvec3(1.0f, 0.0f, 0.0f), "X", true, true, false, false);
	_createElement("waveforms_100", fvec2(-0.75f, -0.75f), fvec2(0.0375f, 0.05f), fvec3(0.25f), fvec3(1.0f), "100", true, true, true, false);
	_createElement("waveforms_200", fvec2(-0.71f, -0.75f), fvec2(0.0375f, 0.05f), fvec3(0.25f), fvec3(1.0f), "200", true, true, true, false);
	_createElement("waveforms_300", fvec2(-0.67f, -0.75f), fvec2(0.0375f, 0.05f), fvec3(0.25f), fvec3(1.0f), "300", true, true, true, false);
	_createElement("waveforms_400", fvec2(-0.63f, -0.75f), fvec2(0.0375f, 0.05f), fvec3(0.25f), fvec3(1.0f), "400", true, true, true, false);
	_createElement("waveforms_500", fvec2(-0.59f, -0.75f), fvec2(0.0375f, 0.05f), fvec3(0.25f), fvec3(1.0f), "500", true, true, true, false);
	_createElement("waveforms_600", fvec2(-0.55f, -0.75f), fvec2(0.0375f, 0.05f), fvec3(0.25f), fvec3(1.0f), "600", true, true, true, false);
	_createElement("waveforms_700", fvec2(-0.51f, -0.75f), fvec2(0.0375f, 0.05f), fvec3(0.25f), fvec3(1.0f), "700", true, true, true, false);
	_createElement("waveforms_800", fvec2(-0.47f, -0.75f), fvec2(0.0375f, 0.05f), fvec3(0.25f), fvec3(1.0f), "800", true, true, true, false);
	_createElement("waveforms_900", fvec2(-0.43f, -0.75f), fvec2(0.0375f, 0.05f), fvec3(0.25f), fvec3(1.0f), "900", true, true, true, false);
}

void GuiManager::update(const fvec2 & cursorPosition, const bool isLmbPressed)
{
	Tools::setCursorType(CursorType::ARROW);

	for(const auto & [elementId, element] : _elements)
	{
		element->update(cursorPosition, isLmbPressed);
	}
}

void GuiManager::_createElement(const string & id,
								const fvec2 & position,
								const fvec2 & size,
								const fvec3 & quadColor,
								const fvec3 & textColor,
								const string & content,
								const bool isHoverable,
								const bool isPressable,
								const bool isTogglable,
								const bool isVisible)
{
	if(_isElementExisting(id))
	{
		abort();
	}

	shared_ptr<Quad> quad = make_shared<Quad>(_vertexBuffer, nullptr, _renderDepth++);
	shared_ptr<Text> text = nullptr;

	quad->setPosition(position);
	quad->setSize(size);
	quad->setColor(quadColor);

	_quads.push_back(quad);

	if(!content.empty())
	{
		text = make_shared<Text>(_vertexBuffer, _fontTextureBuffer, _renderDepth++, content);

		text->setPosition(position);
		text->setSize(size);
		text->setColor(textColor);

		_texts.push_back(text);
	}

	shared_ptr<GuiElement> element = make_shared<GuiElement>(id, quad, text, isHoverable, isPressable, isTogglable);

	element->setVisible(isVisible);

	_elements.insert({id, element});
}

const bool GuiManager::_isElementExisting(const string & id) const
{
	return _elements.find(id) != _elements.end();
}

void GuiManager::inject(const shared_ptr<ImageLoader> imageLoader)
{
	_imageLoader = imageLoader;
}

const vector<shared_ptr<Quad>> GuiManager::getQuads() const
{
	return _quads;
}

const vector<shared_ptr<Text>> GuiManager::getTexts() const
{
	return _texts;
}

const shared_ptr<GuiElement> GuiManager::getElement(const string & id) const
{
	if(!_isElementExisting(id))
	{
		abort();
	}

	return _elements.at(id);
}