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
	_horizontallyCenteredVertexBuffer = make_shared<VertexBuffer>(true, false);
	_verticallyCenteredVertexBuffer = make_shared<VertexBuffer>(false, true);
	_fontTextureBuffer = make_shared<TextureBuffer>(_imageLoader->getImage(Tools::getRootDirectoryPath() + FONT_PATH));

	const dvec3 white = dvec3(1.0);
	const dvec3 black = dvec3(0.0);
	const dvec3 gray = dvec3(0.25);
	const dvec3 darkGray = dvec3(0.15);
	const dvec3 red = dvec3(1.0, 0.0, 0.0);
	const dvec3 blue = dvec3(0.25, 0.25, 0.5);
	const double charX = 0.0125;
	const double charY = 0.05;

	_addGuiRectangle("background", dvec2(0.0), dvec2(2.0), blue, true, true, true);
	_addGuiRectangle("top", dvec2(-1.0, 0.95), dvec2(2.0, charY), gray, false, false, true);
	_addGuiButton("new", dvec2(-1.0, 0.95), dvec2(charX * 3.0, charY), gray, white, "New", false, false, true, true, false, true);
	_addGuiButton("load", dvec2(-0.95, 0.95), dvec2(charX * 4.0, charY), gray, white, "Load", false, false, true, true, false, true);
	_addGuiButton("save", dvec2(-0.8875, 0.95), dvec2(charX * 4.0, charY), gray, white, "Save", false, false, true, true, false, true);
	_addGuiButton("waveforms", dvec2(-0.825, 0.95), dvec2(charX * 9.0, charY), gray, white, "Waveforms", false, false, true, true, false, true);
	_addGuiButton("exit", dvec2(-0.7, 0.95), dvec2(charX * 4.0, charY), gray, white, "Exit", false, false, true, true, false, true);
	_addGuiRectangle("waveforms_menu", dvec2(0.0), dvec2(1.5), gray, true, true, false);
	_addGuiButton("waveforms_close", dvec2(0.75 - charX, 0.7), dvec2(charX, charY), gray, red, "X", false, false, true, true, false, false);
	_addGuiWaveform("waveforms_visualization", dvec2(0.0f, 0.5 - charY), dvec2(1.475f, 0.5f - charY / 2.0), white, true, true, false);
	_addGuiButton("waveforms_play", dvec2(0.0, 0.0f), dvec2(charX * 4.0, charY), darkGray, white, "Play", true, true, true, true, false, false);
	_addGuiButton("waveforms_oct_decr", dvec2(0.0 - charX, -0.25 + charY), dvec2(charX, charY), gray, white, "<", true, true, true, true, false, false);
	_addGuiLabel("waveforms_oct_val", dvec2(0.0, -0.25 + charY), dvec2(charX, charY), white, "0", true, true, false);
	_addGuiButton("waveforms_oct_incr", dvec2(0.0 + charX, -0.25 + charY), dvec2(charX, charY), gray, white, ">", true, true, true, true, false, false);
	_addGuiLabel("waveforms_oct_name", dvec2(0.0, -0.25), dvec2(charX * 6.0, charY), white, "Octave", true, true, false);

	const vector<double> positions = Mathematics::calculateDistributedPositions(-0.75, 1.5, static_cast<int>(AudioConstants::NOTE_NAMES.size()));

	for(int index = 0; index < static_cast<int>(AudioConstants::NOTE_NAMES.size()); index++)
	{
		const string sineDecreaseId = "waveforms_sin_decr" + to_string(index);
		const string sineValueId = "waveforms_sin_val" + to_string(index);
		const string sineIncreaseId = "waveforms_sin_incr" + to_string(index);
		const string sineToggleId = "waveforms_sin_txt" + to_string(index);
		const string squareDecreaseId = "waveforms_sqr_decr" + to_string(index);
		const string squareValueId = "waveforms_sqr_val" + to_string(index);
		const string squareIncreaseId = "waveforms_sqr_incr" + to_string(index);
		const string squareToggleId = "waveforms_sqr_txt" + to_string(index);
		const string triangleDecreaseId = "waveforms_tri_decr" + to_string(index);
		const string triangleValueId = "waveforms_tri_val" + to_string(index);
		const string triangleIncreaseId = "waveforms_tri_incr" + to_string(index);
		const string triangleToggleId = "waveforms_tri_txt" + to_string(index);
		const string sawtoothDecreaseId = "waveforms_saw_decr" + to_string(index);
		const string sawtoothValueId = "waveforms_saw_val" + to_string(index);
		const string sawtoothIncreaseId = "waveforms_saw_incr" + to_string(index);
		const string sawtoothToggleId = "waveforms_saw_txt" + to_string(index);
		const string noteId = "waveforms_note" + to_string(index);
		const string noteName = AudioConstants::NOTE_NAMES[index];

		_addGuiButton(sineDecreaseId, dvec2(positions[index] - charX, -0.35), dvec2(charX, charY), gray, white, "<", true, false, false, false, false, false);
		_addGuiLabel(sineValueId, dvec2(positions[index], -0.35), dvec2(charX, charY), white, "0", true, false, false);
		_addGuiButton(sineIncreaseId, dvec2(positions[index] + charX, -0.35), dvec2(charX, charY), gray, white, ">", true, false, true, true, false, false);
		_addGuiButton(sineToggleId, dvec2(positions[index], -0.4), dvec2(charX * 3.0, charY), gray, white, "SIN", true, false, true, true, true, false);
		_addGuiButton(squareDecreaseId, dvec2(positions[index] - charX, -0.45), dvec2(charX, charY), gray, white, "<", true, false, false, false, false, false);
		_addGuiLabel(squareValueId, dvec2(positions[index], -0.45), dvec2(charX, charY), white, "0", true, false, false);
		_addGuiButton(squareIncreaseId, dvec2(positions[index] + charX, -0.45), dvec2(charX, charY), gray, white, ">", true, false, true, true, false, false);
		_addGuiButton(squareToggleId, dvec2(positions[index], -0.5), dvec2(charX * 3.0, charY), gray, white, "SQR", true, false, true, true, true, false);
		_addGuiButton(triangleDecreaseId, dvec2(positions[index] - charX, -0.55), dvec2(charX, charY), gray, white, "<", true, false, false, false, false, false);
		_addGuiLabel(triangleValueId, dvec2(positions[index], -0.55), dvec2(charX, charY), white, "0", true, false, false);
		_addGuiButton(triangleIncreaseId, dvec2(positions[index] + charX, -0.55), dvec2(charX, charY), gray, white, ">", true, false, true, true, false, false);
		_addGuiButton(triangleToggleId, dvec2(positions[index], -0.6), dvec2(charX * 3.0, charY), gray, white, "TRI", true, false, true, true, true, false);
		_addGuiButton(sawtoothDecreaseId, dvec2(positions[index] - charX, -0.65), dvec2(charX, charY), gray, white, "<", true, false, false, false, false, false);
		_addGuiLabel(sawtoothValueId, dvec2(positions[index], -0.65), dvec2(charX, charY), white, "0", true, false, false);
		_addGuiButton(sawtoothIncreaseId, dvec2(positions[index] + charX, -0.65), dvec2(charX, charY), gray, white, ">", true, false, true, true, false, false);
		_addGuiButton(sawtoothToggleId, dvec2(positions[index], -0.7), dvec2(charX * 3.0, charY), gray, white, "SAW", true, false, true, true, true, false);
		_addGuiLabel(noteId, dvec2(positions[index], -0.75), dvec2(charX * static_cast<double>(noteName.size()), charY), black, noteName, true, false, false);
	}
}

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

void GuiManager::_addGuiButton(const string & id, const dvec2 & position, const dvec2 & size, const dvec3 & quadColor, const dvec3 & textColor, const string & content, const bool isHorizontallyCentered, const bool isVerticallyCentered, const bool isHoverable, const bool isPressable, const bool isTogglable, const bool isVisible)
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
	guiButton->setTogglable(isTogglable);

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
	const shared_ptr<Quad> quad = make_shared<Quad>();

	if(!isHorizontallyCentered && !isVerticallyCentered)
	{
		quad->setVertexBuffer(_corneredVertexBuffer);
	}
	else if(isHorizontallyCentered && isVerticallyCentered)
	{
		quad->setVertexBuffer(_centeredVertexBuffer);
	}
	else if(isHorizontallyCentered && !isVerticallyCentered)
	{
		quad->setVertexBuffer(_horizontallyCenteredVertexBuffer);
	}
	else if(!isHorizontallyCentered && isVerticallyCentered)
	{
		quad->setVertexBuffer(_verticallyCenteredVertexBuffer);
	}

	quad->setPosition(position);
	quad->setSize(size);
	quad->setColor(color);

	return quad;
}

const shared_ptr<Text> GuiManager::_createText(const dvec2 & position, const dvec2 & size, const dvec3 & color, const string & content, const bool isHorizontallyCentered, const bool isVerticallyCentered) const
{
	const shared_ptr<Text> text = make_shared<Text>();

	if(!isHorizontallyCentered && !isVerticallyCentered)
	{
		text->setVertexBuffer(_corneredVertexBuffer);
	}
	else if(isHorizontallyCentered && isVerticallyCentered)
	{
		text->setVertexBuffer(_centeredVertexBuffer);
	}
	else if(isHorizontallyCentered && !isVerticallyCentered)
	{
		text->setVertexBuffer(_horizontallyCenteredVertexBuffer);
	}
	else if(!isHorizontallyCentered && isVerticallyCentered)
	{
		text->setVertexBuffer(_verticallyCenteredVertexBuffer);
	}

	text->setTextureBuffer(_fontTextureBuffer);
	text->setContent(content);
	text->setPosition(position);
	text->setSize(size);
	text->setColor(color);

	return text;
}

const shared_ptr<Line> GuiManager::_createLine(const dvec2 & position, const dvec2 & size, const dvec3 & color, const bool isHorizontallyCentered, const bool isVerticallyCentered) const
{
	const shared_ptr<Line> line = make_shared<Line>();
	const vector<dvec2> vertices = {dvec2(-1.0f, 0.0), dvec2(1.0f, 0.0)};
	const shared_ptr<VertexBuffer> vertexBuffer = make_shared<VertexBuffer>(vertices, isHorizontallyCentered, isVerticallyCentered);

	line->setVertexBuffer(vertexBuffer);
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