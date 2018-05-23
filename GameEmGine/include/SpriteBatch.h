#pragma once
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "StructInfo.h"

struct Glyph
{
	Vertex2D
		bottomLeft,
		topLeft,
		topRight,
		bottomRight;

	GLuint texture;

	float depth=0;

	
};

enum GlyphSort
{
	NONE,
	FRONT_TO_BACK,
	BACK_TO_FRONT,
	BY_TEXTURE
};

struct RenderBatch
{
	GLuint
		offset,
		numVerts,
		texture;
};

class SpriteBatch
{
public:
	SpriteBatch();
	~SpriteBatch();

	void init();

	void begin(GlyphSort type = BY_TEXTURE);
	void end();

	void draw(VboInfo2D* info, float depth, GLuint texture, const Colour* colour);
	void render();
private:
	void createRenderBatches();
	void createVertArrayObject();
	void addGlyph(Glyph);
	void addRenderBatch(RenderBatch);
	void sortGlyphs();

	//sorting functions
	static int frontToBackSort(const void* a, const void *b);
	static int backToFrontSort(const void* a, const void *b);
	static int byTextureSort(const void* a, const void *b);

	GLuint _vboID, _vaoID;
	Glyph* _glyphs;
	RenderBatch* _renderBatches;
	GlyphSort _sortType;
	short _numGlyphs,_numRenderBatches;
};

