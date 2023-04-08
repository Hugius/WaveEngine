#include "gui_manager.hpp"
#include "tools.hpp"
#include "mathematics.hpp"
#include "audio_constants.hpp"

using std::make_shared;
using std::to_string;

void GuiManager::initialize()
{
	_vertexBuffer = make_shared<VertexBuffer>();
	_fontTextureBuffer = make_shared<TextureBuffer>(_imageLoader->getImage(Tools::getRootDirectoryPath() + FONT_PATH));

	_createGuiElement("top", fvec2(-1.0f, 0.95f), fvec2(2.0f, 0.05f), fvec3(0.25f), fvec3(0.0f), "", false, false, false, true);
	_createGuiElement("new", fvec2(-1.0f, 0.95f), fvec2(0.0375f, 0.05f), fvec3(0.25f), fvec3(1.0f), "New", true, true, false, true);
	_createGuiElement("load", fvec2(-0.95f, 0.95f), fvec2(0.05f, 0.05f), fvec3(0.25f), fvec3(1.0f), "Load", true, true, false, true);
	_createGuiElement("save", fvec2(-0.8875f, 0.95f), fvec2(0.05f, 0.05f), fvec3(0.25f), fvec3(1.0f), "Save", true, true, false, true);
	_createGuiElement("waveforms", fvec2(-0.825f, 0.95f), fvec2(0.1125f, 0.05f), fvec3(0.25f), fvec3(1.0f), "Waveforms", true, true, false, true);
	_createGuiElement("exit", fvec2(-0.7f, 0.95f), fvec2(0.05f, 0.05f), fvec3(0.25f), fvec3(1.0f), "Exit", true, true, false, true);

	_createGuiElement("waveforms_menu", fvec2(-0.75f), fvec2(1.5f), fvec3(0.25f), fvec3(0.0f), "", false, false, false, false);
	_createGuiElement("waveforms_close", fvec2(0.725f, 0.675f), fvec2(0.025f, 0.075f), fvec3(0.25f), fvec3(1.0f, 0.0f, 0.0f), "X", true, true, false, false);
	_createGuiElement("waveforms_play", fvec2(-0.75f, 0.675f), fvec2(0.05f, 0.075f), fvec3(0.25f), fvec3(1.0f), "Play", true, true, false, false);

	const vector<float> positions = Mathematics::calculateDistributedPositions(-0.75f, 1.5f, static_cast<int>(AudioConstants::NOTE_NAMES.size()));

	for(int index = 0; index < static_cast<int>(AudioConstants::NOTE_NAMES.size()); index++)
	{
		const string sineId = "waveforms_sin" + to_string(index);
		const string squareId = "waveforms_sqr" + to_string(index);
		const string triangleId = "waveforms_tri" + to_string(index);
		const string sawtoothId = "waveforms_saw" + to_string(index);
		const string noteId = "waveforms_note" + to_string(index);
		const string noteName = AudioConstants::NOTE_NAMES[index];

		_createGuiElement(sineId, fvec2(positions[index], -0.55f), fvec2(0.0375f, 0.05f), fvec3(0.25f), fvec3(1.0f), "SIN", true, true, true, false);
		_createGuiElement(squareId, fvec2(positions[index], -0.6f), fvec2(0.0375f, 0.05f), fvec3(0.25f), fvec3(1.0f), "SQR", true, true, true, false);
		_createGuiElement(triangleId, fvec2(positions[index], -0.65f), fvec2(0.0375f, 0.05f), fvec3(0.25f), fvec3(1.0f), "TRI", true, true, true, false);
		_createGuiElement(sawtoothId, fvec2(positions[index], -0.7f), fvec2(0.0375f, 0.05f), fvec3(0.25f), fvec3(1.0f), "SAW", true, true, true, false);
		_createGuiElement(noteId, fvec2(positions[index], -0.75f), fvec2(0.0125f * static_cast<float>(noteName.size()), 0.05f), fvec3(0.25f), fvec3(1.0f), noteName, false, false, false, false);
	}

	//_createGuiElement("waveforms_sin", fvec2(-0.75f, -0.75f), fvec2(0.0375f, 0.05f), fvec3(0.25f), fvec3(1.0f), "SIN", false, false, false, false);
	//_createGuiElement("waveforms_sin_decr", fvec2(-0.75f, -0.7f), fvec2(0.0125f, 0.05f), fvec3(0.25f), fvec3(1.0f), "<", true, true, false, false);
	//_createGuiElement("waveforms_sin_incr", fvec2(-0.725f, -0.7f), fvec2(0.0125f, 0.05f), fvec3(0.25f), fvec3(1.0f), ">", true, true, false, false);
	//_createGuiElement("waveforms_sqr", fvec2(-0.7f, -0.75f), fvec2(0.0375f, 0.05f), fvec3(0.25f), fvec3(1.0f), "SQR", false, false, false, false);
	//_createGuiElement("waveforms_sqr_decr", fvec2(-0.7f, -0.7f), fvec2(0.0125f, 0.05f), fvec3(0.25f), fvec3(1.0f), "<", true, true, false, false);
	//_createGuiElement("waveforms_sqr_incr", fvec2(-0.675f, -0.7f), fvec2(0.0125f, 0.05f), fvec3(0.25f), fvec3(1.0f), ">", true, true, false, false);
	//_createGuiElement("waveforms_tri", fvec2(-0.65f, -0.75f), fvec2(0.0375f, 0.05f), fvec3(0.25f), fvec3(1.0f), "TRI", false, false, false, false);
	//_createGuiElement("waveforms_tri_decr", fvec2(-0.65f, -0.7f), fvec2(0.0125f, 0.05f), fvec3(0.25f), fvec3(1.0f), "<", true, true, false, false);
	//_createGuiElement("waveforms_tri_incr", fvec2(-0.625f, -0.7f), fvec2(0.0125f, 0.05f), fvec3(0.25f), fvec3(1.0f), ">", true, true, false, false);
	//_createGuiElement("waveforms_saw", fvec2(-0.6f, -0.75f), fvec2(0.0375f, 0.05f), fvec3(0.25f), fvec3(1.0f), "SAW", false, false, false, false);
	//_createGuiElement("waveforms_saw_decr", fvec2(-0.6f, -0.7f), fvec2(0.0125f, 0.05f), fvec3(0.25f), fvec3(1.0f), "<", true, true, false, false);
	//_createGuiElement("waveforms_saw_incr", fvec2(-0.575f, -0.7f), fvec2(0.0125f, 0.05f), fvec3(0.25f), fvec3(1.0f), ">", true, true, false, false);
}

void GuiManager::update(const fvec2 & cursorPosition, const bool isLmbPressed)
{
	Tools::setCursorType(CursorType::ARROW);

	for(const auto & [guiElementId, guiElement] : _guiElements)
	{
		guiElement->update(cursorPosition, isLmbPressed);
	}
}

void GuiManager::_createGuiElement(const string & id,
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
	if(_isGuiElementExisting(id))
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

	shared_ptr<GuiElement> guiElement = make_shared<GuiElement>(id, quad, text, isHoverable, isPressable, isTogglable);

	guiElement->setVisible(isVisible);

	_guiElements.insert({id, guiElement});
}

const bool GuiManager::_isGuiElementExisting(const string & id) const
{
	return _guiElements.find(id) != _guiElements.end();
}

void GuiManager::inject(const shared_ptr<ImageLoader> imageLoader)
{
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

const shared_ptr<GuiElement> GuiManager::getGuiElement(const string & id) const
{
	if(!_isGuiElementExisting(id))
	{
		abort();
	}

	return _guiElements.at(id);
}