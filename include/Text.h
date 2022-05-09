#ifndef TEXT_H
#define TEXT_H

#include "Component.h"
#include "Resources.h"
#include <string>
#include <SDL2/SDL.h>

enum class TextStyle {
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
	SharedFont font;
	SDL_Texture * texture;
	void RemakeTexture(void);
public:
	Text (GameObject& associated, const FontStyle & style, const std::string & text);
	~Text (void);

	inline void SetText(const std::string & t)     { text = t       ; RemakeTexture(); }
	inline void SetColor(const SDL_Color & c)      { style.color = c; RemakeTexture(); }
	inline void SetStyle(TextStyle s)              { style.style = s; RemakeTexture(); }
	inline void SetFontFile(const std::string & f) { style.file = f ; RemakeTexture(); }
	inline void SetFontSize(int s)                 { style.size = s ; RemakeTexture(); }

	// inherited from component
	void Update (float dt);
	void Render (void);
	bool Is (const std::string & type) const;
	const std::string GetType(void) const;
};

#endif
