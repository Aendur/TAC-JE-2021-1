#ifndef TEXT_H
#define TEXT_H

#include "Component.h"
#include "Resources.h"
#include <string>
#include <SDL2/SDL.h>

enum class TextStyle {
	SOLID,
	SHADED,
	BLENDED,
	BLINKING,
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
	std::u8string text;
	SharedFont font;
	SDL_Texture * texture;
	void RemakeTexture(void);
public:
	Text (GameObject& associated, const FontStyle & style, const std::u8string & text);
	~Text (void);

	inline void SetText(const std::u8string & value)   { text = value       ; RemakeTexture(); }
	inline void SetColor(const SDL_Color & value)      { style.color = value; RemakeTexture(); }
	inline void SetStyle(TextStyle value)              { style.style = value; RemakeTexture(); }
	inline void SetFontFile(const std::string & value) { style.file = value ; RemakeTexture(); }
	inline void SetFontSize(int value)                 { style.size = value ; RemakeTexture(); }

	// inherited from component
	void Update (float dt);
	void Render (void);
	bool Is (const std::string & type) const;
	const std::string GetType(void) const;
};

#endif
