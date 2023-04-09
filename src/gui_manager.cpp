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

	_createGuiElement("top", dvec2(-1.0, 0.95), dvec2(2.0, 0.05), dvec3(0.25), dvec3(0.0), "", false, false, false, true);
	_createGuiElement("new", dvec2(-1.0, 0.95), dvec2(0.0375, 0.05), dvec3(0.25), dvec3(1.0), "New", true, true, false, true);
	_createGuiElement("load", dvec2(-0.95, 0.95), dvec2(0.05, 0.05), dvec3(0.25), dvec3(1.0), "Load", true, true, false, true);
	_createGuiElement("save", dvec2(-0.8875, 0.95), dvec2(0.05, 0.05), dvec3(0.25), dvec3(1.0), "Save", true, true, false, true);
	_createGuiElement("waveforms", dvec2(-0.825, 0.95), dvec2(0.1125, 0.05), dvec3(0.25), dvec3(1.0), "Waveforms", true, true, false, true);
	_createGuiElement("exit", dvec2(-0.7, 0.95), dvec2(0.05, 0.05), dvec3(0.25), dvec3(1.0), "Exit", true, true, false, true);

	_createGuiElement("waveforms_menu", dvec2(-0.75), dvec2(1.5), dvec3(0.25), dvec3(0.0), "", false, false, false, false);
	_createGuiElement("waveforms_close", dvec2(0.725, 0.675), dvec2(0.025, 0.075), dvec3(0.25), dvec3(1.0, 0.0, 0.0), "X", true, true, false, false);
	_createGuiElement("waveforms_play", dvec2(-0.75, 0.675), dvec2(0.05, 0.075), dvec3(0.25), dvec3(1.0), "Play", true, true, false, false);

	const string sinePhaseId = "waveforms_sin_phs";
	const string sineAmplitudeId = "waveforms_sin_amp";
	const string sineTypeId = "waveforms_sin_typ";
	const string squarePhaseId = "waveforms_sqr_phs";
	const string squareAmplitudeId = "waveforms_sqr_amp";
	const string squareTypeId = "waveforms_sqr_typ";
	const string trianglePhaseId = "waveforms_tri_phs";
	const string triangleAmplitudeId = "waveforms_tri_amp";
	const string triangleTypeId = "waveforms_tri_typ";
	const string sawtoothPhaseId = "waveforms_saw_phs";
	const string sawtoothAmplitudeId = "waveforms_saw_amp";
	const string sawtoothTypeId = "waveforms_saw_typ";

	_createGuiElement(sinePhaseId, dvec2(-0.75f, -0.15), dvec2(0.0375, 0.05), dvec3(0.25), dvec3(1.0), "PHS", false, false, false, false);
	_createGuiElement(sineAmplitudeId, dvec2(-0.75f, -0.2), dvec2(0.0375, 0.05), dvec3(0.25), dvec3(1.0), "AMP", false, false, false, false);
	_createGuiElement(sineTypeId, dvec2(-0.75f, -0.25), dvec2(0.0375, 0.05), dvec3(0.25), dvec3(1.0), "TYP", false, false, false, false);
	_createGuiElement(squarePhaseId, dvec2(-0.75f, -0.3), dvec2(0.0375, 0.05), dvec3(0.25), dvec3(1.0), "PHS", false, false, false, false);
	_createGuiElement(squareAmplitudeId, dvec2(-0.75f, -0.35), dvec2(0.0375, 0.05), dvec3(0.25), dvec3(1.0), "AMP", false, false, false, false);
	_createGuiElement(squareTypeId, dvec2(-0.75f, -0.4), dvec2(0.0375, 0.05), dvec3(0.25), dvec3(1.0), "TYP", false, false, false, false);
	_createGuiElement(trianglePhaseId, dvec2(-0.75f, -0.45), dvec2(0.0375, 0.05), dvec3(0.25), dvec3(1.0), "PHS", false, false, false, false);
	_createGuiElement(triangleAmplitudeId, dvec2(-0.75f, -0.5), dvec2(0.0375, 0.05), dvec3(0.25), dvec3(1.0), "AMP", false, false, false, false);
	_createGuiElement(triangleTypeId, dvec2(-0.75f, -0.55), dvec2(0.0375, 0.05), dvec3(0.25), dvec3(1.0), "TYP", false, false, false, false);
	_createGuiElement(sawtoothPhaseId, dvec2(-0.75f, -0.6), dvec2(0.0375, 0.05), dvec3(0.25), dvec3(1.0), "PHS", false, false, false, false);
	_createGuiElement(sawtoothAmplitudeId, dvec2(-0.75f, -0.65), dvec2(0.0375, 0.05), dvec3(0.25), dvec3(1.0), "AMP", false, false, false, false);
	_createGuiElement(sawtoothTypeId, dvec2(-0.75f, -0.7), dvec2(0.0375, 0.05), dvec3(0.25), dvec3(1.0), "TYP", false, false, false, false);

	const vector<double> positions = Mathematics::calculateDistributedPositions(-0.75, 1.5, static_cast<int>(AudioConstants::NOTE_NAMES.size()));

	for(int index = 0; index < static_cast<int>(AudioConstants::NOTE_NAMES.size()); index++)
	{
		const string sinePhaseId = "waveforms_sin_phs" + to_string(index);
		const string sineAmplitudeId = "waveforms_sin_amp" + to_string(index);
		const string sineToggleId = "waveforms_sin_tgl" + to_string(index);
		const string squarePhaseId = "waveforms_sqr_phs" + to_string(index);
		const string squareAmplitudeId = "waveforms_sqr_amp" + to_string(index);
		const string squareToggleId = "waveforms_sqr_tgl" + to_string(index);
		const string trianglePhaseId = "waveforms_tri_phs" + to_string(index);
		const string triangleAmplitudeId = "waveforms_tri_amp" + to_string(index);
		const string triangleToggleId = "waveforms_tri_tgl" + to_string(index);
		const string sawtoothPhaseId = "waveforms_saw_phs" + to_string(index);
		const string sawtoothAmplitudeId = "waveforms_saw_amp" + to_string(index);
		const string sawtoothToggleId = "waveforms_saw_tgl" + to_string(index);
		const string noteId = "waveforms_note" + to_string(index);
		const string noteName = AudioConstants::NOTE_NAMES[index];

		_createGuiElement(sinePhaseId, dvec2(positions[index], -0.15), dvec2(0.0375, 0.05), dvec3(0.25), dvec3(1.0), "0", false, false, false, false);
		_createGuiElement(sineAmplitudeId, dvec2(positions[index], -0.2), dvec2(0.0375, 0.05), dvec3(0.25), dvec3(1.0), "0", false, false, false, false);
		_createGuiElement(sineToggleId, dvec2(positions[index], -0.25), dvec2(0.0375, 0.05), dvec3(0.25), dvec3(1.0), "SIN", true, true, true, false);
		_createGuiElement(squarePhaseId, dvec2(positions[index], -0.3), dvec2(0.0375, 0.05), dvec3(0.25), dvec3(1.0), "0", false, false, false, false);
		_createGuiElement(squareAmplitudeId, dvec2(positions[index], -0.35), dvec2(0.0375, 0.05), dvec3(0.25), dvec3(1.0), "0", false, false, false, false);
		_createGuiElement(squareToggleId, dvec2(positions[index], -0.4), dvec2(0.0375, 0.05), dvec3(0.25), dvec3(1.0), "SQR", true, true, true, false);
		_createGuiElement(trianglePhaseId, dvec2(positions[index], -0.45), dvec2(0.0375, 0.05), dvec3(0.25), dvec3(1.0), "0", false, false, false, false);
		_createGuiElement(triangleAmplitudeId, dvec2(positions[index], -0.5), dvec2(0.0375, 0.05), dvec3(0.25), dvec3(1.0), "0", false, false, false, false);
		_createGuiElement(triangleToggleId, dvec2(positions[index], -0.55), dvec2(0.0375, 0.05), dvec3(0.25), dvec3(1.0), "TRI", true, true, true, false);
		_createGuiElement(sawtoothPhaseId, dvec2(positions[index], -0.6), dvec2(0.0375, 0.05), dvec3(0.25), dvec3(1.0), "0", false, false, false, false);
		_createGuiElement(sawtoothAmplitudeId, dvec2(positions[index], -0.65), dvec2(0.0375, 0.05), dvec3(0.25), dvec3(1.0), "0", false, false, false, false);
		_createGuiElement(sawtoothToggleId, dvec2(positions[index], -0.7), dvec2(0.0375, 0.05), dvec3(0.25), dvec3(1.0), "SAW", true, true, true, false);
		_createGuiElement(noteId, dvec2(positions[index], -0.75), dvec2(0.0125 * static_cast<double>(noteName.size()), 0.05), dvec3(0.25), dvec3(1.0), noteName, false, false, false, false);
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