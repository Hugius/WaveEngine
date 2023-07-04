#include "gui_manager.hpp"
#include "tools.hpp"
#include "mathematics.hpp"
#include "shared.hpp"

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
	const double width = 2.0;
	const double y = 0.95;

	addGuiRectangle("top_menu_background", dvec2(-1.0, y), dvec2(width, CHAR_Y), DARK_GRAY, false, false, true);

	double x = -1.0;

	addGuiButton("top_menu_new", dvec2(x, y), dvec2(WIDTH("New"), CHAR_Y), DARK_GRAY, Shared::WHITE, "New", false, false, true, true, true);

	x += WIDTH("New");
	x += CHAR_X;

	addGuiButton("top_menu_load", dvec2(x, y), dvec2(WIDTH("Load"), CHAR_Y), DARK_GRAY, Shared::WHITE, "Load", false, false, true, true, true);

	x += WIDTH("Load");
	x += CHAR_X;

	addGuiButton("top_menu_save", dvec2(x, y), dvec2(WIDTH("Save"), CHAR_Y), DARK_GRAY, Shared::WHITE, "Save", false, false, true, true, true);

	x += WIDTH("Save");
	x += CHAR_X;

	addGuiButton("top_menu_tone_editor", dvec2(x, y), dvec2(WIDTH("ToneEditor"), CHAR_Y), DARK_GRAY, Shared::WHITE, "ToneEditor", false, false, true, true, true);

	x += WIDTH("ToneEditor");
	x += CHAR_X;

	addGuiButton("top_menu_export", dvec2(x, y), dvec2(WIDTH("Export"), CHAR_Y), DARK_GRAY, Shared::WHITE, "Export", false, false, true, true, true);

	x += WIDTH("Export");
	x += CHAR_X;

	addGuiButton("top_menu_exit", dvec2(x, y), dvec2(WIDTH("Exit"), CHAR_Y), DARK_GRAY, Shared::WHITE, "Exit", false, false, true, true, true);
}

void GuiManager::_initializeTimeline()
{
	const double x = -1.0;
	const double y = -0.75;
	const double width = 2.0;
	const double height = 2.0 - 0.25 - CHAR_Y;
	const double separatorOffset = CHAR_X * 6.0;

	addGuiRectangle("timeline_background", dvec2(x, y), dvec2(width, height), GRAY, false, false, true);
	addGuiRectangle("timeline_separator", dvec2(x + separatorOffset, y), dvec2(CHAR_X * 0.75, height), DARK_GRAY, false, false, true);

	const int noteCount = Shared::NOTE_COUNT;
	const vector<double> notePositions = Mathematics::calculateDistributedPositions(y, height, noteCount, true);

	for(int index = 0; index < noteCount; index++)
	{
		const string noteId = "timeline_note" + to_string(index);
		const string separatorId = "timeline_separator" + to_string(index);
		const string noteName = NOTE_NAMES.at(index);
		const dvec2 buttonPosition = dvec2(x + separatorOffset / 2.0, notePositions.at(index) + separatorOffset / 2.0);
		const dvec2 buttonSize = dvec2(WIDTH(noteName), CHAR_Y) * 2.0;
		const dvec2 rectanglePosition = dvec2(x + separatorOffset, notePositions.at(index));
		const dvec2 rectangleSize = dvec2(width, CHAR_Y * 0.35);

		addGuiButton(noteId, buttonPosition, buttonSize, GRAY, Shared::WHITE, noteName, true, false, true, true, true);

		if(index > 0)
		{
			addGuiRectangle(separatorId, rectanglePosition, rectangleSize, DARK_GRAY, false, false, true);
		}
	}
}

void GuiManager::_initializeBottomMenu()
{
	const double x = -1.0;
	const double y = -1.0;
	const double width = 2.0;
	const double height = 0.25;
	const double defaultOffset = 0.05;
	const double waveformOffset = 0.025;
	const vector<double> yPositions = Mathematics::calculateDistributedPositions(-1.0 + height, -height, 3, false);

	addGuiRectangle("bottom_menu_background", dvec2(x, y), dvec2(width, height), DARK_GRAY, false, false, true);
	addGuiButton("bottom_menu_create", dvec2(x + defaultOffset, yPositions.at(0)), dvec2(WIDTH("Create"), CHAR_Y), GRAY, Shared::WHITE, "Create", true, true, true, true, true);
	addGuiButton("bottom_menu_previous", dvec2(x + defaultOffset - WIDTH("00"), yPositions.at(1)), dvec2(WIDTH("<"), CHAR_Y), GRAY, Shared::WHITE, "<", true, true, true, true, true);
	addGuiLabel("bottom_menu_number", dvec2(x + defaultOffset, yPositions.at(1)), dvec2(WIDTH("00"), CHAR_Y), Shared::WHITE, "00", true, true, true);
	addGuiButton("bottom_menu_next", dvec2(x + defaultOffset + WIDTH("00"), yPositions.at(1)), dvec2(WIDTH(">"), CHAR_Y), GRAY, Shared::WHITE, ">", true, true, true, true, true);
	addGuiButton("bottom_menu_delete", dvec2(x + defaultOffset, yPositions.at(2)), dvec2(WIDTH("Delete"), CHAR_Y), GRAY, Shared::WHITE, "Delete", true, true, true, true, true);
	addGuiWaveform("bottom_menu_waveform", dvec2(x + defaultOffset + WIDTH("Create") / 2.0 + waveformOffset, yPositions.at(1)), dvec2(width - defaultOffset - WIDTH("Create") / 2.0 - waveformOffset * 2.0, height - waveformOffset), Shared::WHITE, false, true, false);
}

void GuiManager::_initializeToneEditor()
{
	const double x = 0.0f;
	const double y = 0.125;
	const double width = 1.5;
	const double height = 1.5;
	const double waveformOffset = 0.025;
	const double notesOffset = 0.2;
	const double attackOffset = 0.15;
	const double releaseOffset = 0.15;
	const int noteCount = Shared::NOTE_COUNT;
	const int octaveCount = Shared::OCTAVE_COUNT;
	const vector<double> notePositions = Mathematics::calculateDistributedPositions(-width / 2.0, width, noteCount, false);
	const vector<double> octavePositionsX = Mathematics::calculateDistributedPositions(-width / 2.0, width, octaveCount, false);
	const vector<double> octavePositionsY = Mathematics::calculateDistributedPositions(y, -0.75, 10, false);

	addGuiRectangle("tone_editor_background", dvec2(x, y), dvec2(width, height), LIGHT_GRAY, true, true, false);
	addGuiButton("tone_editor_close", dvec2(x + width / 2.0 - WIDTH("X"), y + height / 2.0 - CHAR_Y), dvec2(WIDTH("X"), CHAR_Y), LIGHT_GRAY, RED, "X", false, false, true, true, false);
	addGuiWaveform("tone_editor_waveform", dvec2(x, y + height / 3.0), dvec2(width - waveformOffset, height / 4.0 - waveformOffset), Shared::WHITE, true, true, false);

	for(int index = 0; index < noteCount; index++)
	{
		const string noteId = "tone_editor_note" + to_string(index);
		const string noteName = NOTE_NAMES.at(index);

		addGuiButton(noteId, dvec2(x + notePositions.at(index), y + notesOffset), dvec2(WIDTH(noteName), CHAR_Y) * 3.0, LIGHT_GRAY, Shared::WHITE, noteName, true, true, true, true, false);
	}

	addGuiButton("tone_editor_attack_decrease", dvec2(x - WIDTH("00") - attackOffset, y + CHAR_Y), dvec2(WIDTH("<"), CHAR_Y), LIGHT_GRAY, Shared::WHITE, "<", true, true, true, true, false);
	addGuiLabel("tone_editor_attack_value", dvec2(x - attackOffset, y + CHAR_Y), dvec2(WIDTH("000"), CHAR_Y), Shared::WHITE, "000", true, true, false);
	addGuiButton("tone_editor_attack_increase", dvec2(x + WIDTH("00") - attackOffset, y + CHAR_Y), dvec2(WIDTH(">"), CHAR_Y), LIGHT_GRAY, Shared::WHITE, ">", true, true, true, true, false);
	addGuiLabel("tone_editor_attack_text", dvec2(x - attackOffset, y), dvec2(WIDTH("ATT"), CHAR_Y), Shared::WHITE, "ATT", true, true, false);

	addGuiButton("tone_editor_duration_decrease", dvec2(x - WIDTH("00"), y + CHAR_Y), dvec2(WIDTH("<"), CHAR_Y), LIGHT_GRAY, Shared::WHITE, "<", true, true, true, true, false);
	addGuiLabel("tone_editor_duration_value", dvec2(x, y + CHAR_Y), dvec2(WIDTH("000"), CHAR_Y), Shared::WHITE, "000", true, true, false);
	addGuiButton("tone_editor_duration_increase", dvec2(x + WIDTH("00"), y + CHAR_Y), dvec2(WIDTH(">"), CHAR_Y), LIGHT_GRAY, Shared::WHITE, ">", true, true, true, true, false);
	addGuiLabel("tone_editor_duration_text", dvec2(x, y), dvec2(WIDTH("DUR"), CHAR_Y), Shared::WHITE, "DUR", true, true, false);

	addGuiButton("tone_editor_release_decrease", dvec2(x - WIDTH("00") + releaseOffset, y + CHAR_Y), dvec2(WIDTH("<"), CHAR_Y), LIGHT_GRAY, Shared::WHITE, "<", true, true, true, true, false);
	addGuiLabel("tone_editor_release_value", dvec2(x + releaseOffset, y + CHAR_Y), dvec2(WIDTH("000"), CHAR_Y), Shared::WHITE, "000", true, true, false);
	addGuiButton("tone_editor_release_increase", dvec2(x + WIDTH("00") + releaseOffset, y + CHAR_Y), dvec2(WIDTH(">"), CHAR_Y), LIGHT_GRAY, Shared::WHITE, ">", true, true, true, true, false);
	addGuiLabel("tone_editor_release_text", dvec2(x + releaseOffset, y), dvec2(WIDTH("REL"), CHAR_Y), Shared::WHITE, "REL", true, true, false);

	for(int index = 0; index < octaveCount; index++)
	{
		const string sineDecreaseId = "tone_editor_sine_decrease" + to_string(index);
		const string sineValueId = "tone_editor_sine_value" + to_string(index);
		const string sineIncreaseId = "tone_editor_sine_increase" + to_string(index);
		const string sineToggleId = "tone_editor_sine_text" + to_string(index);
		const string squareDecreaseId = "tone_editor_square_decrease" + to_string(index);
		const string squareValueId = "tone_editor_square_value" + to_string(index);
		const string squareIncreaseId = "tone_editor_square_increase" + to_string(index);
		const string squareToggleId = "tone_editor_square_text" + to_string(index);
		const string triangleDecreaseId = "tone_editor_triangle_decrease" + to_string(index);
		const string triangleValueId = "tone_editor_triangle_value" + to_string(index);
		const string triangleIncreaseId = "tone_editor_triangle_increase" + to_string(index);
		const string triangleToggleId = "tone_editor_triangle_text" + to_string(index);
		const string sawtoothDecreaseId = "tone_editor_sawtooth_decrease" + to_string(index);
		const string sawtoothValueId = "tone_editor_sawtooth_value" + to_string(index);
		const string sawtoothIncreaseId = "tone_editor_sawtooth_increase" + to_string(index);
		const string sawtoothToggleId = "tone_editor_sawtooth_text" + to_string(index);
		const string octaveId = "tone_editor_octave" + to_string(index);
		const string octaveName = "OCT " + to_string(index);

		addGuiButton(sineDecreaseId, dvec2(x + octavePositionsX.at(index) - WIDTH("0"), octavePositionsY.at(1)), dvec2(WIDTH("<"), CHAR_Y), LIGHT_GRAY, Shared::WHITE, "<", true, false, true, true, false);
		addGuiLabel(sineValueId, dvec2(x + octavePositionsX.at(index), octavePositionsY.at(1)), dvec2(WIDTH("0"), CHAR_Y), Shared::WHITE, "0", true, false, false);
		addGuiButton(sineIncreaseId, dvec2(x + octavePositionsX.at(index) + WIDTH("0"), octavePositionsY.at(1)), dvec2(WIDTH(">"), CHAR_Y), LIGHT_GRAY, Shared::WHITE, ">", true, false, true, true, false);
		addGuiButton(sineToggleId, dvec2(x + octavePositionsX.at(index), octavePositionsY.at(2)), dvec2(WIDTH("SIN"), CHAR_Y), LIGHT_GRAY, Shared::WHITE, "SIN", true, false, true, true, false);
		addGuiButton(squareDecreaseId, dvec2(x + octavePositionsX.at(index) - WIDTH("0"), octavePositionsY.at(3)), dvec2(WIDTH("<"), CHAR_Y), LIGHT_GRAY, Shared::WHITE, "<", true, false, true, true, false);
		addGuiLabel(squareValueId, dvec2(x + octavePositionsX.at(index), octavePositionsY.at(3)), dvec2(WIDTH("0"), CHAR_Y), Shared::WHITE, "0", true, false, false);
		addGuiButton(squareIncreaseId, dvec2(x + octavePositionsX.at(index) + WIDTH("0"), octavePositionsY.at(3)), dvec2(WIDTH(">"), CHAR_Y), LIGHT_GRAY, Shared::WHITE, ">", true, false, true, true, false);
		addGuiButton(squareToggleId, dvec2(x + octavePositionsX.at(index), octavePositionsY.at(4)), dvec2(WIDTH("SQR"), CHAR_Y), LIGHT_GRAY, Shared::WHITE, "SQR", true, false, true, true, false);
		addGuiButton(triangleDecreaseId, dvec2(x + octavePositionsX.at(index) - WIDTH("0"), octavePositionsY.at(5)), dvec2(WIDTH("<"), CHAR_Y), LIGHT_GRAY, Shared::WHITE, "<", true, false, true, true, false);
		addGuiLabel(triangleValueId, dvec2(x + octavePositionsX.at(index), octavePositionsY.at(5)), dvec2(WIDTH("0"), CHAR_Y), Shared::WHITE, "0", true, false, false);
		addGuiButton(triangleIncreaseId, dvec2(x + octavePositionsX.at(index) + WIDTH("0"), octavePositionsY.at(5)), dvec2(WIDTH(">"), CHAR_Y), LIGHT_GRAY, Shared::WHITE, ">", true, false, true, true, false);
		addGuiButton(triangleToggleId, dvec2(x + octavePositionsX.at(index), octavePositionsY.at(6)), dvec2(WIDTH("TRI"), CHAR_Y), LIGHT_GRAY, Shared::WHITE, "TRI", true, false, true, true, false);
		addGuiButton(sawtoothDecreaseId, dvec2(x + octavePositionsX.at(index) - WIDTH("0"), octavePositionsY.at(7)), dvec2(WIDTH("<"), CHAR_Y), LIGHT_GRAY, Shared::WHITE, "<", true, false, true, true, false);
		addGuiLabel(sawtoothValueId, dvec2(x + octavePositionsX.at(index), octavePositionsY.at(7)), dvec2(WIDTH("0"), CHAR_Y), Shared::WHITE, "0", true, false, false);
		addGuiButton(sawtoothIncreaseId, dvec2(x + octavePositionsX.at(index) + WIDTH("0"), octavePositionsY.at(7)), dvec2(WIDTH(">"), CHAR_Y), LIGHT_GRAY, Shared::WHITE, ">", true, false, true, true, false);
		addGuiButton(sawtoothToggleId, dvec2(x + octavePositionsX.at(index), octavePositionsY.at(8)), dvec2(WIDTH("SAW"), CHAR_Y), LIGHT_GRAY, Shared::WHITE, "SAW", true, false, true, true, false);
		addGuiLabel(octaveId, dvec2(x + octavePositionsX.at(index), octavePositionsY.at(9)), dvec2(WIDTH(octaveName), CHAR_Y), Shared::BLACK, octaveName, true, false, false);
	}
}