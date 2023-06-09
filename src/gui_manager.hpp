#pragma once

#include "image_loader.hpp"
#include "gui_button.hpp"
#include "gui_rectangle.hpp"
#include "gui_label.hpp"
#include "line.hpp"
#include "gui_waveform.hpp"
#include "shared.hpp"

#include <array>

using std::array;

class GuiManager final
{
public:
	void inject(const shared_ptr<ImageLoader> & imageLoader);
	void initialize();
	void update(const dvec2 & cursorPosition, const bool isLmbPressed);
	void addGuiRectangle(const string & id, const dvec2 & position, const dvec2 & size, const dvec3 & color, const bool isHorizontallyCentered, const bool isVerticallyCentered, const bool isVisible);
	void addGuiLabel(const string & id, const dvec2 & position, const dvec2 & size, const dvec3 & color, const string & content, const bool isHorizontallyCentered, const bool isVerticallyCentered, const bool isVisible);
	void addGuiButton(const string & id, const dvec2 & position, const dvec2 & size, const dvec3 & defaultQuadColor, const dvec3 & hoveredQuadColor, const bool isHorizontallyCentered, const bool isVerticallyCentered, const bool isHoverable, const bool isPressable, const bool isVisible);
	void addGuiButton(const string & id, const dvec2 & position, const dvec2 & size, const dvec3 & defaultQuadColor, const dvec3 & defaultTextColor, const dvec3 & hoveredQuadColor, const dvec3 & hoveredTextColor, const string & content, const bool isHorizontallyCentered, const bool isVerticallyCentered, const bool isHoverable, const bool isPressable, const bool isVisible);
	void addGuiWaveform(const string & id, const dvec2 & position, const dvec2 & size, const dvec3 & color, const bool isHorizontallyCentered, const bool isVerticallyCentered, const bool isVisible);

	const vector<shared_ptr<Quad>> & getQuads() const;
	const vector<shared_ptr<Text>> & getTexts() const;
	const vector<shared_ptr<Line>> & getLines() const;

	const shared_ptr<GuiRectangle> & getGuiRectangle(const string & id) const;
	const shared_ptr<GuiLabel> & getGuiLabel(const string & id) const;
	const shared_ptr<GuiButton> & getGuiButton(const string & id) const;
	const shared_ptr<GuiWaveform> & getGuiWaveform(const string & id) const;

private:
	void _initializeTopMenu();
	void _initializeBottomMenu();
	void _initializeTimeline();
	void _initializeToneEditor();

	const shared_ptr<Quad> _createQuad(const dvec2 & position, const dvec2 & size, const dvec3 & color, const bool isHorizontallyCentered, const bool isVerticallyCentered) const;
	const shared_ptr<Text> _createText(const dvec2 & position, const dvec2 & size, const dvec3 & color, const string & content, const bool isHorizontallyCentered, const bool isVerticallyCentered) const;
	const shared_ptr<Line> _createLine(const dvec2 & position, const dvec2 & size, const dvec3 & color, const bool isHorizontallyCentered, const bool isVerticallyCentered) const;

	const bool _isGuiRectangleExisting(const string & id) const;
	const bool _isGuiLabelExisting(const string & id) const;
	const bool _isGuiButtonExisting(const string & id) const;
	const bool _isGuiWaveformExisting(const string & id) const;

	static inline const array<string, Shared::NOTE_COUNT> NOTE_NAMES = {"C", "C#", "D", "D#", "E", "F", "F#", "G", "G#", "A", "A#", "B"};

	static inline const string FONT_PATH = "images\\font.tga";

	static inline const double CHAR_X = 0.0125;
	static inline const double CHAR_Y = 0.05;

	unordered_map<string, shared_ptr<GuiRectangle>> _guiRectangles = {};
	unordered_map<string, shared_ptr<GuiLabel>> _guiLabels = {};
	unordered_map<string, shared_ptr<GuiButton>> _guiButtons = {};
	unordered_map<string, shared_ptr<GuiWaveform>> _guiWaveforms = {};
	vector<shared_ptr<Quad>> _quads = {};
	vector<shared_ptr<Text>> _texts = {};
	vector<shared_ptr<Line>> _lines = {};

	shared_ptr<ImageLoader> _imageLoader = nullptr;
	shared_ptr<VertexBuffer> _corneredVertexBuffer = nullptr;
	shared_ptr<VertexBuffer> _centeredVertexBuffer = nullptr;
	shared_ptr<VertexBuffer> _horizontallyCenteredVertexBuffer = nullptr;
	shared_ptr<VertexBuffer> _verticallyCenteredVertexBuffer = nullptr;
	shared_ptr<TextureBuffer> _fontTextureBuffer = nullptr;
};