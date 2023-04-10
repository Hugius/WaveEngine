#pragma once

#include "image_loader.hpp"
#include "gui_button.hpp"
#include "gui_rectangle.hpp"

class GuiManager final
{
public:
	void inject(const shared_ptr<ImageLoader> & imageLoader);
	void initialize();
	void update(const dvec2 & cursorPosition, const bool isLmbPressed);

	const vector<shared_ptr<Quad>> & getQuads() const;
	const vector<shared_ptr<Text>> & getTexts() const;

	const shared_ptr<GuiRectangle> & getGuiRectangle(const string & id) const;
	const shared_ptr<GuiButton> & getGuiButton(const string & id) const;

private:
	void _createGuiRectangle(const string & id, const dvec2 & position, const dvec2 & size, const dvec3 & color, const bool isHorizontallyCentered, const bool isVerticallyCentered, const bool isVisible);
	void _createGuiButton(const string & id, const dvec2 & position, const dvec2 & size, const dvec3 & quadColor, const dvec3 & textColor, const string & content, const bool isHorizontallyCentered, const bool isVerticallyCentered, const bool isHoverable, const bool isPressable, const bool isTogglable, const bool isVisible);

	const bool _isGuiRectangleExisting(const string & id) const;
	const bool _isGuiButtonExisting(const string & id) const;

	static inline const string FONT_PATH = "images\\font.tga";

	unordered_map<string, shared_ptr<GuiButton>> _guiButtons = {};
	unordered_map<string, shared_ptr<GuiRectangle>> _guiRectangles = {};
	vector<shared_ptr<Quad>> _quads = {};
	vector<shared_ptr<Text>> _texts = {};

	shared_ptr<ImageLoader> _imageLoader = nullptr;
	shared_ptr<VertexBuffer> _corneredVertexBuffer = nullptr;
	shared_ptr<VertexBuffer> _centeredVertexBuffer = nullptr;
	shared_ptr<VertexBuffer> _horizontallyCenteredVertexBuffer = nullptr;
	shared_ptr<VertexBuffer> _verticallyCenteredVertexBuffer = nullptr;
	shared_ptr<TextureBuffer> _fontTextureBuffer = nullptr;

	int _renderDepth = 1;
};