#include "SpriteBatch.h"

SpriteBatch::SpriteBatch() :_vboID(0), _vaoID(0)
{}


SpriteBatch::~SpriteBatch()
{}

void SpriteBatch::init()
{
	createVertArrayObject();
}

void SpriteBatch::begin(GlyphSort type)
{
	_sortType = type;
	_numGlyphs = 0;
	_numRenderBatches = 0;
}

void SpriteBatch::end()
{
	sortGlyphs();
	createRenderBatches();
}

void SpriteBatch::draw(VboInfo2D * info, float depth, GLuint texture, const Colour * colour)
{
	Glyph* newGlyph = new Glyph;
	newGlyph->texture = texture;
	newGlyph->depth = depth;

	int w, h;
	glfwGetFramebufferSize(glfwGetCurrentContext(), &w, &h);
	info->size.width /= w;
	info->size.height /= h;
	info->position.x /= w;
	info->position.y /= h;

	newGlyph->bottomLeft.colour = *colour;
	newGlyph->bottomLeft.coord = info->position;
	newGlyph->bottomLeft.setUV(0, 0);

	newGlyph->topLeft.colour = *colour;
	newGlyph->topLeft.coord = Coord2D {0.f,info->size.height} +info->position;
	newGlyph->topLeft.setUV(0, 1);

	newGlyph->topRight.colour = *colour;
	newGlyph->topRight.coord = Coord2D {info->size.width,info->size.height}+info->position;
	newGlyph->topRight.setUV(1, 1);

	newGlyph->bottomRight.colour = *colour;
	newGlyph->bottomRight.coord = Coord2D {info->size.width,0.f}+info->position;
	newGlyph->bottomRight.setUV(1, 0);

	addGlyph(newGlyph);
}

void SpriteBatch::render()
{
	glActiveTexture(GL_TEXTURE0);
	glBindVertexArray(_vaoID);
	for(int a = 0; a < _numRenderBatches; a++)
	{
		glBindTexture(GL_TEXTURE_2D, _renderBatches[a].texture);
		glDrawArrays(GL_TRIANGLES, _renderBatches[a].offset, _renderBatches[a].numVerts);
	}
	glBindVertexArray(0);
	glBindTexture(GL_TEXTURE_2D, 0);
}

void SpriteBatch::createRenderBatches()
{
	static Vertex2D* verts;
	delete[] verts;
	verts = new Vertex2D[_numGlyphs * 6];
	if(!_numGlyphs)
		return;

	int
		offset = 0,
		cv = 0;

	addRenderBatch({(GLuint)offset,(GLuint)6,_glyphs[0]->texture});
	verts[cv++] = _glyphs[0]->bottomLeft;
	verts[cv++] = _glyphs[0]->topLeft;
	verts[cv++] = _glyphs[0]->topRight;
	verts[cv++] = _glyphs[0]->topRight;
	verts[cv++] = _glyphs[0]->bottomRight;
	verts[cv++] = _glyphs[0]->bottomLeft;
	offset += 6;
	for(int cg = 1; cg < _numGlyphs; cg++)
	{
		if(_glyphs[cg]->texture != _glyphs[cg - 1]->texture)
			addRenderBatch({(GLuint)offset,(GLuint)6,_glyphs[cg]->texture});
		else
			_renderBatches[_numRenderBatches - 1].numVerts += 6;
		verts[cv++] = _glyphs[cg]->bottomLeft;
		verts[cv++] = _glyphs[cg]->topLeft;
		verts[cv++] = _glyphs[cg]->topRight;
		verts[cv++] = _glyphs[cg]->topRight;
		verts[cv++] = _glyphs[cg]->bottomRight;
		verts[cv++] = _glyphs[cg]->bottomLeft;
		offset += 6;
	}
	glBindBuffer(GL_ARRAY_BUFFER, _vboID);
	//orphan data
	glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex2D)*(_numGlyphs * 6), nullptr, GL_DYNAMIC_DRAW);
	//upload data
	glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(Vertex2D)*(_numGlyphs * 6), verts);

	glBindBuffer(GL_ARRAY_BUFFER, 0);


}

void SpriteBatch::createVertArrayObject()
{
	if(!_vaoID)
		glGenVertexArrays(1, &_vaoID);

	glBindVertexArray(_vaoID);
	if(!_vboID)
		glGenBuffers(1, &_vboID);

	glBindBuffer(GL_ARRAY_BUFFER, _vboID);

	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
	glEnableVertexAttribArray(2);

	//vertex atributes
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex2D), (void*)offsetof(Vertex2D, coord));
	//Colour atributes
	glVertexAttribPointer(1, 4, GL_UNSIGNED_BYTE, GL_TRUE, sizeof(Vertex2D), (void*)offsetof(Vertex2D, colour));
	//UV     atributes
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex2D), (void*)offsetof(Vertex2D, uv));

	glBindVertexArray(0);
}

void SpriteBatch::addGlyph(Glyph *add)
{
	//Glyph** newer = new Glyph*[++_numGlyphs];
	//memcpy(newer, _glyphs, sizeof(Glyph*)*(_numGlyphs - 1));
	_glyphs = (Glyph**)realloc(_glyphs, sizeof(Glyph*)*(++_numGlyphs));
	_glyphs[_numGlyphs - 1] = add;
}

void SpriteBatch::addRenderBatch(RenderBatch add)
{
	//RenderBatch* newer = new RenderBatch[++_numRenderBatches];
	//memcpy(newer, _renderBatches, sizeof(RenderBatch)*(_numRenderBatches - 1));
	_renderBatches = (RenderBatch*)realloc(_renderBatches, sizeof(RenderBatch)*(++_numRenderBatches));
	_renderBatches[_numRenderBatches - 1] = add;
	//_renderBatches = newer;
}

void SpriteBatch::sortGlyphs()
{

	switch(_sortType)
	{
	case NONE:
		break;
	case BACK_TO_FRONT:
		std::qsort(_glyphs, _numGlyphs, sizeof(Glyph**), backToFrontSort);
		break;
	case FRONT_TO_BACK:
		std::qsort(_glyphs, _numGlyphs, sizeof(Glyph**), frontToBackSort);
		break;
	case BY_TEXTURE:
		std::qsort(_glyphs, _numGlyphs, sizeof(Glyph**), byTextureSort);
	}
}

int SpriteBatch::frontToBackSort(const void * a, const void * b)
{
	return ((Glyph**)a)[0]->depth - ((Glyph**)b)[0]->depth;
}

int SpriteBatch::backToFrontSort(const void * a, const void * b)
{
	return -((Glyph**)a)[0]->depth - ((Glyph**)b)[0]->depth;
}

int SpriteBatch::byTextureSort(const void * a, const void * b)
{
	return ((Glyph**)a)[0]->texture < ((Glyph**)b)[0]->texture;
}


