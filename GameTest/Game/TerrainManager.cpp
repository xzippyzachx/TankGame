#include "stdafx.h"
#include "TerrainManager.h"

TerrainManager::TerrainManager()
{
    float surface = 80.0f;
	for (float y = surface; y > -20.0f; y -= 5.0f)
	{
		for (float x = 0; x < APP_VIRTUAL_WIDTH; x += 5.0f)
		{
            float newY = 15.0f * sin(x / 100.0f) + y;
            if (newY < -2.0f)
            {
                continue;
            }

            Color color = Color(0.502f, 0.333f, 0.196f);
            if (y == surface)
            {
                color = Color(0.49f, 0.749f, 0.059f);
            }

            tiles.insert({ Vector2(x, newY),  color});
        }
    }
}

void TerrainManager::operator=(TerrainManager const &)
{
}

void TerrainManager::Update(float dt)
{
}

void TerrainManager::Draw()
{
    for (auto& tile : tiles)
	{
        float x = tile.first.x;
        float y = tile.first.y;

        #if APP_USE_VIRTUAL_RES
            APP_VIRTUAL_TO_NATIVE_COORDS(x, y);
        #endif

        Color color = tile.second;
        glColor3f(color.r, color.g, color.b);
        
        int triangleAmount = 20; // # of triangles used to draw circle
        
        GLfloat radius = 0.01f; // radius
        GLfloat twicePi = 2.0f * PI;
        
        glBegin(GL_TRIANGLE_FAN);
            glVertex2f(x, y); // center of circle
            for(float j = 0; j <= triangleAmount; j++) { 
                glVertex2f(
                    x + (radius * cos(j *  twicePi / triangleAmount)), 
                    y + (radius * sin(j * twicePi / triangleAmount))
                );
            }
        glEnd();
    }
}

void TerrainManager::Destroy()
{
    //tiles.clear();
}

float TerrainManager::GetFloor(float x)
{
    int tileX = (int)x - ((int)x % 5);

    float floor = 0.0f;
    for (auto& tilePos : tiles)
	{
        if (tilePos.first.x == tileX && tilePos.first.y > floor)
        {
            floor = tilePos.first.y;
        }
    }

    return floor;
}

void TerrainManager::Explode(Vector2 position)
{
    std::unordered_map<Vector2, Color, Vector2::HashFunction> newTiles;

    for (auto& tile : tiles)
	{
        if (!(position.Distance(tile.first) < 20.0f))
        {
            newTiles.insert({ tile.first, tile.second });
        }
    }
    
    tiles.swap(newTiles);
}
