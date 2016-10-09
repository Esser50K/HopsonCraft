#ifndef CHUNK_H
#define CHUNK_H

#include <unordered_map>
#include <memory>
#include <vector>

#include <SFML/Graphics.hpp>

#include "OpenGL/Glm/glm_transformations.h"
#include "Vector.h"
#include "Model.h"
#include "Entity.h"

#include "Blocks.h"



namespace Block
{
    class Block_Base;
}

class Texture_Atlas;

class Chunk;
typedef std::unique_ptr<Chunk> Chunk_Ptr;

class Chunk : public Entity
{
    public:
        Chunk( std::unordered_map<Vector2i, Chunk_Ptr>* chunkMap,
               const Vector2i& location,
               const Texture_Atlas& atlas  );

        void generateMesh ();

        const Block::Block_Base& getBlock ( int x, int y, int z ) const;

        const Model& getModel       () const;

        bool hasVertexData          () const;

        const Vector2i& getLocation () const;

    private:
        void makeBlock ( GLfloat x, GLfloat y, GLfloat z, const Block::Block_Base& block );

        void makeBack   (   GLfloat x, GLfloat y, GLfloat z, const Block::Block_Base& block );
        void makeTop    (   GLfloat x, GLfloat y, GLfloat z, const Block::Block_Base& block );
        void makeLeft   (   GLfloat x, GLfloat y, GLfloat z, const Block::Block_Base& block );
        void makeRight  (   GLfloat x, GLfloat y, GLfloat z, const Block::Block_Base& block );
        void makeFront  (   GLfloat x, GLfloat y, GLfloat z, const Block::Block_Base& block );
        void makeBottom (   GLfloat x, GLfloat y, GLfloat z, const Block::Block_Base& block );

        void makeTree   (   GLuint x, GLuint y, GLuint z );

        void setBlock   (   GLuint x, GLuint y, GLuint z, std::unique_ptr<Block::Block_Base> block );

    private:
        std::unordered_map<Vector2i, Chunk_Ptr>* m_p_chunkMap;
        std::vector<std::unique_ptr<Block::Block_Base>> m_blocks;

        Model    m_model;

        Vector2i m_location;

        const Texture_Atlas* m_p_atlas;

        bool m_hasBlockData     = false;
        bool m_hasVertexData    = false;

        std::vector<GLfloat> m_vertexCoords;
        std::vector<GLfloat> m_textureCoords;

        std::unique_ptr<Block::Dirt> m_dirtBlock;
        std::unique_ptr<Block::Block_Base> m_airBlock;

    public:
        static constexpr int WIDTH  = 16,
                             HEIGHT = 128,
                             WATER_LEVEL = 70,
                             BEACH_LEVEL = WATER_LEVEL + 2;

        static int maxHeight;
        static int minHeight;
};


#endif // CHUNK_H