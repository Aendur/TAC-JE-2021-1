#ifndef TEXT_H
#define TEXT_H

#include "Component.h"
#include <string>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

enum TextStyle {
	SOLID,
	SHADED,
	BLENDED
};

class FontStyle {
public:
	std::string file;
	int size;
	TextStyle style;
	SDL_Color color;
};

class Text : public Component {
private:
	FontStyle style;
	std::string text;
	TTF_Font * font;
	SDL_Texture * texture;
	void RemakeTexture(void);
public:
	Text (GameObject& associated, const FontStyle & style, const std::string & text);
	~Text (void);

	inline void SetText(const std::string & t) { text = t; }
	inline void SetColor(const SDL_Color & c) { style.color = c; }
	inline void SetStyle(TextStyle s) { style.style = s; }
	inline void SetFontFile(const std::string & f) { style.file = f; }
	inline void SetFontSize(int s) { style.size = s; }


	// inherited from component
	void Update (float dt);
	void Render (void);
	bool Is (const std::string & type) const;
	const std::string GetType(void) const;
};

#endif
