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
            tilePositions.push_back(Vector2(x, newY));
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
    for (const auto& tilePos : tilePositions)
	{
        float x = tilePos.x;
        float y = tilePos.y;

        #if APP_USE_VIRTUAL_RES
            APP_VIRTUAL_TO_NATIVE_COORDS(x, y);
        #endif

        glColor3f(0.502f, 0.333f, 0.196f);
        
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
}

float TerrainManager::GetFloor(float x)
{
    int tileX = (int)x - ((int)x % 5);

    float floor = 0.0f;
    for (const auto& tilePos : tilePositions)
	{
        if (tilePos.x == tileX && tilePos.y > floor)
        {
            floor = tilePos.y;
        }
    }

    return floor;
}

void TerrainManager::Explode(Vector2 position)
{
    std::vector<Vector2> newTiles;

    for (int i = 0; i < tilePositions.size(); i++)
	{
        if (!(position.Distance(tilePositions[i]) < 20.0f))
        {
            newTiles.push_back(tilePositions[i]);
        }
    }

    tilePositions.swap(newTiles);
}
