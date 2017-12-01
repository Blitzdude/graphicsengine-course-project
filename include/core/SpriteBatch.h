#ifndef _SPRITE_BATCH_H_
#define _SPRITE_BATCH_H_

#include "core/Object.h"
#include <GLES2/gl2.h>
#include <glm/common.hpp>
#include "graphics/Vertex.h"
#include <vector>

namespace engine {

	// Determines how we should sort the glyphs
	enum class GlyphSortType {
		NONE,
		FRONT_TO_BACK,
		BACK_TO_FRONT,
		TEXTURE
	};

	class Glyph {
	public:
		Glyph() {};
		Glyph(const glm::vec4& destRect, const glm::vec4& uvRect, GLuint Texture, float Depth, const ColorRGBA8& color);
		Glyph(const glm::vec4& destRect, const glm::vec4& uvRect, GLuint Texture, float Depth, const ColorRGBA8& color, float angle);

		GLuint texture;
		float depth;

		Vertex	topLeft;
		Vertex	bottomLeft;
		Vertex	topRight;
		Vertex	bottomRight;
	private:
		// Rotates a point about (0,0) by angle
		glm::vec2 rotatePoint(const glm::vec2& pos, float angle);
	};

	// Each render batch is used for a single draw call
	class RenderBatch {
	public:
		RenderBatch(GLuint Offset,
					GLuint NumVertices,
					GLuint Texture) : offset(Offset), numVertices(NumVertices), texture(Texture) {
		}

		GLuint offset;
		GLuint numVertices;
		GLuint texture;
	};

	class SpriteBatch : public Object {
	public:
		SpriteBatch();
		~SpriteBatch();

		// Initializes the spritebatch
		void init();
		void dispose();

		// begins the spritebatch
		void begin(GlyphSortType sortType = GlyphSortType::TEXTURE);

		// ends the spritebatch
		void end();

		// Adds a glyph to the spritebatch
		void draw(const glm::vec4& destRect, const glm::vec4& uvRect, GLuint texture, float depth, const ColorRGBA8& color);
		// Adds a glyph to the spritebatch with rotation
		void draw(const glm::vec4& destRect, const glm::vec4& uvRect, GLuint texture, float depth, const ColorRGBA8& color, float angle);
		// Adds a glyph to the spritebatch with rotation
		void draw(const glm::vec4& destRect, const glm::vec4& uvRect, GLuint texture, float depth, const ColorRGBA8& color, const glm::vec2& dir);

		// renders entire batch to screen
		void renderBatch();
		
	private: // methods
		// Creates all the needed RenderBatches
		void createRenderBatches();

		// Generates our VAO and VBO
		void createVertexArray();

		// Sorts glyphs according to _sortType
		void sortGlyphs();

		// Comparators used by sortGlyphs()
		static bool compareFrontToBack(Glyph* a, Glyph* b);
		static bool compareBackToFront(Glyph* a, Glyph* b);
		static bool compareTexture(Glyph* a, Glyph* b);

	private: // attributes
		GLuint m_vbo;
		GLuint m_vao;

		GlyphSortType m_sortType;

		std::vector<Glyph*> m_glyphPointers; ///< This is for sorting
		std::vector<Glyph> m_glyphs; ///< These are the actual glyphs
		std::vector<RenderBatch> m_renderBatches;
	};
}
#endif // !_SPRITE_BATCH_H_