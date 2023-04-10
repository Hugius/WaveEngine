#include "gui_manager.hpp"
#include "tools.hpp"
#include "mathematics.hpp"
#include "audio_constants.hpp"

using std::make_shared;
using std::to_string;

void GuiManager::initialize()
{
	_corneredVertexBuffer = make_shared<VertexBuffer>(false, false);
	_centeredVertexBuffer = make_shared<VertexBuffer>(true, true);
	_horizontallyCenteredVertexBuffer = make_shared<VertexBuffer>(false, true);
	_verticallyCenteredVertexBuffer = make_shared<VertexBuffer>(true, false);
	_fontTextureBuffer = make_shared<TextureBuffer>(_imageLoader->getImage(Tools::getRootDirectoryPath() + FONT_PATH));

	const dvec3 black = dvec3(0.0);
	const dvec3 white = dvec3(1.0);
	const dvec3 gray = dvec3(0.25);
	const dvec3 red = dvec3(1.0, 0.0f, 0.0f);
	const double charX = 0.0125;
	const double charY = 0.05;

	_createGuiElement("top", dvec2(-1.0, 0.95), dvec2(2.0, charY), gray, black, "", false, false, false, false, false, true);
	_createGuiElement("new", dvec2(-1.0, 0.95), dvec2(charX * 3.0, charY), gray, white, "New", false, false, true, true, false, true);
	_createGuiElement("load", dvec2(-0.95, 0.95), dvec2(charX * 4.0, charY), gray, white, "Load", false, false, true, true, false, true);
	_createGuiElement("save", dvec2(-0.8875, 0.95), dvec2(charX * 4.0, charY), gray, white, "Save", false, false, true, true, false, true);
	_createGuiElement("waveforms", dvec2(-0.825, 0.95), dvec2(charX * 9.0, charY), gray, white, "Waveforms", false, false, true, true, false, true);
	_createGuiElement("exit", dvec2(-0.7, 0.95), dvec2(charX * 4.0, charY), gray, white, "Exit", false, false, true, true, false, true);

	_createGuiElement("waveforms_menu", dvec2(0.0f), dvec2(1.5), gray, black, "", true, true, false, false, false, false);
	_createGuiElement("waveforms_close", dvec2(0.75 - charX, 0.7), dvec2(charX, charY), gray, red, "X", false, false, true, true, false, false);
	_createGuiElement("waveforms_play", dvec2(-0.75, 0.7), dvec2(charX * 4.0, charY), gray, white, "Play", false, false, true, true, false, false);

	const vector<double> positions = Mathematics::calculateDistributedPositions(-0.75, 1.5, static_cast<int>(AudioConstants::NOTE_NAMES.size()));

	for(int index = 0; index < static_cast<int>(AudioConstants::NOTE_NAMES.size()); index++)
	{
		const string sineDecreaseId = "waveforms_sin_decr" + to_string(index);
		const string sineValueId = "waveforms_sin_val" + to_string(index);
		const string sineIncreaseId = "waveforms_sin_incr" + to_string(index);
		const string sineToggleId = "waveforms_sin_tgl" + to_string(index);
		const string squareDecreaseId = "waveforms_sqr_decr" + to_string(index);
		const string squareValueId = "waveforms_sqr_val" + to_string(index);
		const string squareIncreaseId = "waveforms_sqr_incr" + to_string(index);
		const string squareToggleId = "waveforms_sqr_tgl" + to_string(index);
		const string triangleDecreaseId = "waveforms_tri_decr" + to_string(index);
		const string triangleValueId = "waveforms_tri_val" + to_string(index);
		const string triangleIncreaseId = "waveforms_tri_incr" + to_string(index);
		const string triangleToggleId = "waveforms_tri_tgl" + to_string(index);
		const string sawtoothDecreaseId = "waveforms_saw_decr" + to_string(index);
		const string sawtoothValueId = "waveforms_saw_val" + to_string(index);
		const string sawtoothIncreaseId = "waveforms_saw_incr" + to_string(index);
		const string sawtoothToggleId = "waveforms_saw_tgl" + to_string(index);
		const string noteId = "waveforms_note" + to_string(index);
		const string noteName = AudioConstants::NOTE_NAMES[index];

		_createGuiElement(sineDecreaseId, dvec2(positions[index] - charX, -0.35), dvec2(charX, charY), gray, white, "<", false, true, true, true, false, false);
		_createGuiElement(sineValueId, dvec2(positions[index], -0.35), dvec2(charX, charY), gray, white, "0", false, true, false, false, false, false);
		_createGuiElement(sineIncreaseId, dvec2(positions[index] + charX, -0.35), dvec2(charX, charY), gray, white, ">", false, true, true, true, false, false);
		_createGuiElement(sineToggleId, dvec2(positions[index], -0.4), dvec2(0.0375, charY), gray, white, "SIN", false, true, true, true, true, false);
		_createGuiElement(squareDecreaseId, dvec2(positions[index] - charX, -0.45), dvec2(charX, charY), gray, white, "<", false, true, true, true, false, false);
		_createGuiElement(squareValueId, dvec2(positions[index], -0.45), dvec2(charX, charY), gray, white, "0", false, true, false, false, false, false);
		_createGuiElement(squareIncreaseId, dvec2(positions[index] + charX, -0.45), dvec2(charX, charY), gray, white, ">", false, true, true, true, false, false);
		_createGuiElement(squareToggleId, dvec2(positions[index], -0.5), dvec2(0.0375, charY), gray, white, "SQR", false, true, true, true, true, false);
		_createGuiElement(triangleDecreaseId, dvec2(positions[index] - charX, -0.55), dvec2(charX, charY), gray, white, "<", false, true, true, true, false, false);
		_createGuiElement(triangleValueId, dvec2(positions[index], -0.55), dvec2(charX, charY), gray, white, "0", false, true, false, false, false, false);
		_createGuiElement(triangleIncreaseId, dvec2(positions[index] + charX, -0.55), dvec2(charX, charY), gray, white, ">", false, true, true, true, false, false);
		_createGuiElement(triangleToggleId, dvec2(positions[index], -0.6), dvec2(0.0375, charY), gray, white, "TRI", false, true, true, true, true, false);
		_createGuiElement(sawtoothDecreaseId, dvec2(positions[index] - charX, -0.65), dvec2(charX, charY), gray, white, "<", false, true, true, true, false, false);
		_createGuiElement(sawtoothValueId, dvec2(positions[index], -0.65), dvec2(charX, charY), gray, white, "0", false, true, false, false, false, false);
		_createGuiElement(sawtoothIncreaseId, dvec2(positions[index] + charX, -0.65), dvec2(charX, charY), gray, white, ">", false, true, true, true, false, false);
		_createGuiElement(sawtoothToggleId, dvec2(positions[index], -0.7), dvec2(0.0375, charY), gray, white, "SAW", false, true, true, true, true, false);
		_createGuiElement(noteId, dvec2(positions[index], -0.75), dvec2(charX * static_cast<double>(noteName.size()), charY), gray, white, noteName, false, true, false, false, false, false);
	}
}

void GuiManager::update(const dvec2 & cursorPosition, const bool isLmbPressed)
{
	Tools::setCursorType(CursorType::ARROW);

	for(const auto & [guiElementId, guiElement] : _guiElements)
	{
		guiElement->update(cursorPosition, isLmbPressed);
	}
}

void GuiManager::_createGuiElement(const string & id,
								   const dvec2 & position,
								   const dvec2 & size,
								   const dvec3 & quadColor,
								   const dvec3 & textColor,
								   const string & content,
								   const bool isHorizontallyCentered,
								   const bool isVerticallyCentered,
								   const bool isHoverable,
								   const bool isPressable,
								   const bool isTogglable,
								   const bool isVisible)
{
	if(_isGuiElementExisting(id))
	{
		abort();
	}

	shared_ptr<Quad> quad;
	shared_ptr<Text> text = nullptr;

	if(!isHorizontallyCentered && !isVerticallyCentered)
	{
		quad = make_shared<Quad>(_corneredVertexBuffer, nullptr, _renderDepth++);
	}
	else if(isHorizontallyCentered && isVerticallyCentered)
	{
		quad = make_shared<Quad>(_centeredVertexBuffer, nullptr, _renderDepth++);
	}
	else if(isHorizontallyCentered && !isVerticallyCentered)
	{
		quad = make_shared<Quad>(_horizontallyCenteredVertexBuffer, nullptr, _renderDepth++);
	}
	else if(!isHorizontallyCentered && isVerticallyCentered)
	{
		quad = make_shared<Quad>(_verticallyCenteredVertexBuffer, nullptr, _renderDepth++);
	}

	quad->setPosition(position);
	quad->setSize(size);
	quad->setColor(quadColor);

	_quads.push_back(quad);

	if(!content.empty())
	{
		if(!isHorizontallyCentered && !isVerticallyCentered)
		{
			text = make_shared<Text>(_corneredVertexBuffer, _fontTextureBuffer, _renderDepth++, content);
		}
		else if(isHorizontallyCentered && isVerticallyCentered)
		{
			text = make_shared<Text>(_centeredVertexBuffer, _fontTextureBuffer, _renderDepth++, content);
		}
		else if(isHorizontallyCentered && !isVerticallyCentered)
		{
			text = make_shared<Text>(_horizontallyCenteredVertexBuffer, _fontTextureBuffer, _renderDepth++, content);
		}
		else if(!isHorizontallyCentered && isVerticallyCentered)
		{
			text = make_shared<Text>(_verticallyCenteredVertexBuffer, _fontTextureBuffer, _renderDepth++, content);
		}

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

void GuiManager::inject(const shared_ptr<ImageLoader> & imageLoader)
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