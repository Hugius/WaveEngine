#include "gui_manager.hpp"
#include "tools.hpp"
#include "mathematics.hpp"
#include "tone_constants.hpp"

#define WIDTH(content) (CHAR_X * static_cast<double>(string(content).size()))

using std::make_shared;
using std::to_string;

void GuiManager::initialize()
{
	_corneredVertexBuffer = make_shared<VertexBuffer>(false, false);
	_centeredVertexBuffer = make_shared<VertexBuffer>(true, true);
	_horizontallyCenteredVertexBuffer = make_shared<VertexBuffer>(true, false);
	_verticallyCenteredVertexBuffer = make_shared<VertexBuffer>(false, true);
	_fontTextureBuffer = make_shared<TextureBuffer>(_imageLoader->getImage(Tools::getRootDirectoryPath() + FONT_PATH));

	_initializeTopMenu();
	_initializeTimeline();
	_initializeBottomMenu();
	_initializeToneEditor();
}

void GuiManager::_initializeTopMenu()
{
	const double y = 0.95;

	_addGuiRectangle("top_menu_background", dvec2(-1.0, y), dvec2(2.0, CHAR_Y), GRAY, false, false, true);

	double x = -1.0;

	_addGuiButton("top_menu_new", dvec2(x, y), dvec2(WIDTH("New"), CHAR_Y), GRAY, WHITE, "New", false, false, true, true, false, true);

	x += WIDTH("New");
	x += CHAR_X;

	_addGuiButton("top_menu_load", dvec2(x, y), dvec2(WIDTH("Load"), CHAR_Y), GRAY, WHITE, "Load", false, false, true, true, false, true);

	x += WIDTH("Load");
	x += CHAR_X;

	_addGuiButton("top_menu_save", dvec2(x, y), dvec2(WIDTH("Save"), CHAR_Y), GRAY, WHITE, "Save", false, false, true, true, false, true);

	x += WIDTH("Save");
	x += CHAR_X;

	_addGuiButton("top_menu_tone", dvec2(x, y), dvec2(WIDTH("ToneEditor"), CHAR_Y), GRAY, WHITE, "ToneEditor", false, false, true, true, false, true);

	x += WIDTH("ToneEditor");
	x += CHAR_X;

	_addGuiButton("top_menu_export", dvec2(x, y), dvec2(WIDTH("Export"), CHAR_Y), GRAY, WHITE, "Export", false, false, true, true, false, true);

	x += WIDTH("Export");
	x += CHAR_X;

	_addGuiButton("top_menu_exit", dvec2(x, y), dvec2(WIDTH("Exit"), CHAR_Y), GRAY, WHITE, "Exit", false, false, true, true, false, true);
}

void GuiManager::_initializeBottomMenu()
{
	const vector<double> positions = Mathematics::calculateDistributedPositions(-1.0, 0.25, 3);

	_addGuiRectangle("bottom_menu_background", dvec2(-1.0, -1.0), dvec2(2.0, 0.25), DARK_GRAY, false, false, true);
	_addGuiButton("bottom_menu_create", dvec2(-0.95, positions[0]), dvec2(WIDTH("Create"), CHAR_Y), GRAY, WHITE, "Create", false, true, true, true, false, true);
	_addGuiButton("bottom_menu_delete", dvec2(-0.95, positions[1]), dvec2(WIDTH("Delete"), CHAR_Y), GRAY, WHITE, "Delete", false, true, true, true, false, true);
}

void GuiManager::_initializeTimeline()
{
	_addGuiRectangle("timeline_background", dvec2(-0.8, -1.0), dvec2(1.8, 2.0 - CHAR_Y), BLUE, false, false, true);
}

void GuiManager::_initializeToneEditor()
{
	_addGuiRectangle("tone_editor_background", dvec2(0.0), dvec2(1.5), GRAY, true, true, false);
	_addGuiButton("tone_editor_close", dvec2(0.75 - CHAR_X, 0.7), dvec2(CHAR_X, CHAR_Y), GRAY, RED, "X", false, false, true, true, false, false);
	_addGuiWaveform("tone_editor_visualization", dvec2(0.0f, 0.5 - CHAR_Y), dvec2(1.475f, 0.5f - CHAR_Y / 2.0), WHITE, true, true, false);
	_addGuiButton("tone_editor_play", dvec2(0.0, 0.0f), dvec2(WIDTH("Play"), CHAR_Y), DARK_GRAY, WHITE, "Play", true, true, true, true, false, false);
	_addGuiButton("tone_editor_save", dvec2(0.0, -0.1f), dvec2(WIDTH("Save"), CHAR_Y), DARK_GRAY, WHITE, "Save", true, true, true, true, false, false);
	_addGuiButton("tone_editor_oct_decr", dvec2(0.0 - CHAR_X, -0.25 + CHAR_Y), dvec2(CHAR_X, CHAR_Y), GRAY, WHITE, "<", true, true, true, true, false, false);
	_addGuiLabel("tone_editor_oct_val", dvec2(0.0, -0.25 + CHAR_Y), dvec2(CHAR_X, CHAR_Y), WHITE, "0", true, true, false);
	_addGuiButton("tone_editor_oct_incr", dvec2(0.0 + CHAR_X, -0.25 + CHAR_Y), dvec2(CHAR_X, CHAR_Y), GRAY, WHITE, ">", true, true, true, true, false, false);
	_addGuiLabel("tone_editor_oct_name", dvec2(0.0, -0.25), dvec2(WIDTH("Octave"), CHAR_Y), WHITE, "Octave", true, true, false);

	const vector<double> positions = Mathematics::calculateDistributedPositions(-0.75, 1.5, static_cast<int>(ToneConstants::NOTE_NAMES.size()));

	for(int index = 0; index < static_cast<int>(ToneConstants::NOTE_NAMES.size()); index++)
	{
		const string sineDecreaseId = "tone_editor_sin_decr" + to_string(index);
		const string sineValueId = "tone_editor_sin_val" + to_string(index);
		const string sineIncreaseId = "tone_editor_sin_incr" + to_string(index);
		const string sineToggleId = "tone_editor_sin_txt" + to_string(index);
		const string squareDecreaseId = "tone_editor_sqr_decr" + to_string(index);
		const string squareValueId = "tone_editor_sqr_val" + to_string(index);
		const string squareIncreaseId = "tone_editor_sqr_incr" + to_string(index);
		const string squareToggleId = "tone_editor_sqr_txt" + to_string(index);
		const string triangleDecreaseId = "tone_editor_tri_decr" + to_string(index);
		const string triangleValueId = "tone_editor_tri_val" + to_string(index);
		const string triangleIncreaseId = "tone_editor_tri_incr" + to_string(index);
		const string triangleToggleId = "tone_editor_tri_txt" + to_string(index);
		const string sawtoothDecreaseId = "tone_editor_saw_decr" + to_string(index);
		const string sawtoothValueId = "tone_editor_saw_val" + to_string(index);
		const string sawtoothIncreaseId = "tone_editor_saw_incr" + to_string(index);
		const string sawtoothToggleId = "tone_editor_saw_txt" + to_string(index);
		const string noteId = "tone_editor_note" + to_string(index);
		const string noteName = ToneConstants::NOTE_NAMES[index];

		_addGuiButton(sineDecreaseId, dvec2(positions[index] - CHAR_X, -0.35), dvec2(CHAR_X, CHAR_Y), GRAY, WHITE, "<", true, false, false, false, false, false);
		_addGuiLabel(sineValueId, dvec2(positions[index], -0.35), dvec2(CHAR_X, CHAR_Y), WHITE, "0", true, false, false);
		_addGuiButton(sineIncreaseId, dvec2(positions[index] + CHAR_X, -0.35), dvec2(CHAR_X, CHAR_Y), GRAY, WHITE, ">", true, false, true, true, false, false);
		_addGuiButton(sineToggleId, dvec2(positions[index], -0.4), dvec2(WIDTH("SIN"), CHAR_Y), GRAY, WHITE, "SIN", true, false, true, true, true, false);
		_addGuiButton(squareDecreaseId, dvec2(positions[index] - CHAR_X, -0.45), dvec2(CHAR_X, CHAR_Y), GRAY, WHITE, "<", true, false, false, false, false, false);
		_addGuiLabel(squareValueId, dvec2(positions[index], -0.45), dvec2(CHAR_X, CHAR_Y), WHITE, "0", true, false, false);
		_addGuiButton(squareIncreaseId, dvec2(positions[index] + CHAR_X, -0.45), dvec2(CHAR_X, CHAR_Y), GRAY, WHITE, ">", true, false, true, true, false, false);
		_addGuiButton(squareToggleId, dvec2(positions[index], -0.5), dvec2(WIDTH("SQR"), CHAR_Y), GRAY, WHITE, "SQR", true, false, true, true, true, false);
		_addGuiButton(triangleDecreaseId, dvec2(positions[index] - CHAR_X, -0.55), dvec2(CHAR_X, CHAR_Y), GRAY, WHITE, "<", true, false, false, false, false, false);
		_addGuiLabel(triangleValueId, dvec2(positions[index], -0.55), dvec2(CHAR_X, CHAR_Y), WHITE, "0", true, false, false);
		_addGuiButton(triangleIncreaseId, dvec2(positions[index] + CHAR_X, -0.55), dvec2(CHAR_X, CHAR_Y), GRAY, WHITE, ">", true, false, true, true, false, false);
		_addGuiButton(triangleToggleId, dvec2(positions[index], -0.6), dvec2(WIDTH("TRI"), CHAR_Y), GRAY, WHITE, "TRI", true, false, true, true, true, false);
		_addGuiButton(sawtoothDecreaseId, dvec2(positions[index] - CHAR_X, -0.65), dvec2(CHAR_X, CHAR_Y), GRAY, WHITE, "<", true, false, false, false, false, false);
		_addGuiLabel(sawtoothValueId, dvec2(positions[index], -0.65), dvec2(CHAR_X, CHAR_Y), WHITE, "0", true, false, false);
		_addGuiButton(sawtoothIncreaseId, dvec2(positions[index] + CHAR_X, -0.65), dvec2(CHAR_X, CHAR_Y), GRAY, WHITE, ">", true, false, true, true, false, false);
		_addGuiButton(sawtoothToggleId, dvec2(positions[index], -0.7), dvec2(WIDTH("SAW"), CHAR_Y), GRAY, WHITE, "SAW", true, false, true, true, true, false);
		_addGuiLabel(noteId, dvec2(positions[index], -0.75), dvec2(WIDTH(noteName), CHAR_Y), BLACK, noteName, true, false, false);
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