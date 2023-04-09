#pragma once

#include "image_loader.hpp"
#include "gui_element.hpp"

class GuiManager final
{
public:
	void inject(const shared_ptr<ImageLoader> & imageLoader);
	void initialize();
	void update(const dvec2 & cursorPosition, const bool isLmbPressed);

	const vector<shared_ptr<Quad>> & getQuads() const;
	const vector<shared_ptr<Text>> & getTexts() const;

	const shared_ptr<GuiElement> getGuiElement(const string & id) const;

private:
	void _createGuiElement(const string & id,
						   const dvec2 & position,
						   const dvec2 & size,
						   const dvec3 & quadColor,
						   const dvec3 & textColor,
						   const string & content,
						   const bool isCentered,
						   const bool isHoverable,
						   const bool isPressable,
						   const bool isTogglable,
						   const bool isVisible);

	const bool _isGuiElementExisting(const string & id) const;

	static inline const string FONT_PATH = "images\\font.tga";

	unordered_map<string, shared_ptr<GuiElement>> _guiElements = {};
	vector<shared_ptr<Quad>> _quads = {};
	vector<shared_ptr<Text>> _texts = {};

	shared_ptr<ImageLoader> _imageLoader = nullptr;
	shared_ptr<VertexBuffer> _corneredVertexBuffer = nullptr;
	shared_ptr<VertexBuffer> _centeredVertexBuffer = nullptr;
	shared_ptr<TextureBuffer> _fontTextureBuffer = nullptr;

	int _renderDepth = 1;
};