#include "stdafx.h"
#include "TerrainManager.h"

#include "..\GameSettings.h"

TerrainManager::TerrainManager()
{
}

void TerrainManager::operator=(TerrainManager const &)
{
}

void TerrainManager::Update(float dt)
{
}

void TerrainManager::Draw()
{
    for (auto& tree : trees)
	{
        tree.second->Draw();
    }

    for (auto& tile : tiles)
	{
        float x = tile.first.x;
        float y = tile.first.y;

        #if APP_USE_VIRTUAL_RES
            APP_VIRTUAL_TO_NATIVE_COORDS(x, y);
        #endif

        Color color = tile.second;
        glColor3f(color.r, color.g, color.b);
        
        int triangleAmount = 20;
        
        GLfloat radius = 0.002f * tileSize;
        GLfloat twicePi = 2.0f * PI;
        
        glBegin(GL_TRIANGLE_FAN);
            glVertex2f(x, y);
            for(float j = 0; j <= triangleAmount; j++)
            {
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
    tiles.clear();
    trees.clear();
}

void TerrainManager::Reset()
{
    tiles.clear();
    trees.clear();
}

void TerrainManager::Generate()
{
    height = (int)(surface / tileSize);
    width = APP_VIRTUAL_WIDTH / (int)tileSize;

    amplitude = FRAND_RANGE(TERRAIN_AMPLITUDE - 5.0f, TERRAIN_AMPLITUDE + 5.0f);
    period = FRAND_RANGE(TERRAIN_PERIOD - 20.0f, TERRAIN_PERIOD + 20.0f);

    for (int c = 0; c <= width; c++)
    {
        float x = (float)c * tileSize;
        for (int r = (int)(-amplitude / tileSize); r < height; r++)
        {
            float y = (float)r * tileSize;

            float newY = (amplitude * sin(x / period) + y);
            newY = (float)((int)newY - ((int)newY % (int)tileSize));

            if (newY < 0.0f)
            {
                continue;
            }

            Color color = Color(0.502f, 0.333f, 0.196f);
            if (r == height - 1)
            {
                color = Color(0.137f, 0.749f, 0.463f);

                int r = (int)FRAND_RANGE(0, 20);
                if (r <= 1)
                {
                    CreateTree(Vector2(x, newY), r);
                }
            }

            tiles.insert({ Vector2(x, newY),  color});
        }
    }
}

float TerrainManager::GetFloor(float x)
{
    int tileX = (int)x - ((int)x % (int)tileSize);

    float floor = -25.0f;
    for (auto& tilePos : tiles)
	{
        if (tilePos.first.x == tileX && tilePos.first.y > floor)
        {
            floor = tilePos.first.y;
        }
    }

    return floor;
}

void TerrainManager::Explode(Vector2 position, float radius)
{
    std::unordered_map<Vector2, Color, Vector2::HashFunction> newTiles;

    for (auto& tile : tiles)
	{
        if (!(position.Distance(tile.first) <= radius))
        {
            newTiles.insert({ tile.first, tile.second });
        }
        else
        {
            DestroyTree(tile.first);
        }
    }
    
    tiles.swap(newTiles);

    Settle();
}

void TerrainManager::Settle()
{
    std::unordered_map<Vector2, Color, Vector2::HashFunction> newTiles;

    for (int c = 0; c <= width; c++)
	{
        float x = (float)c * tileSize;
        bool fall = false;
        float fallAmount = 0;
        for (int r = 0; r < height + amplitude / tileSize; r++)
        {
            float y = (float)r * tileSize;

            //std::cout << x << "," << y << "\n";
            Vector2 pos = Vector2(x, y);
            if (tiles.find(pos) == tiles.end())
            {
                fall = true;
                fallAmount += tileSize;
            }
            else if (!fall)
            {
                newTiles.insert({ pos, tiles[pos] });
            }
            else
            {
                DestroyTree(pos);

                Color color = tiles[pos];
                pos.y -= fallAmount;
                newTiles.insert({ pos, color});
            }
        }
    }

    tiles.swap(newTiles);
}

void TerrainManager::CreateTree(Vector2 pos, int type)
{
    char* treeFilename;
	switch (type)
	{
		case 0:
			treeFilename = ".\\Resources\\Sprites\\treePine.png";
			break;
		case 1:
			treeFilename =  ".\\Resources\\Sprites\\treeLong.png";
			break;
        default:
			treeFilename = ".\\Resources\\Sprites\\treePine.png";
			break;
	}

    CSimpleSprite* newTree = App::CreateSprite(treeFilename, 1, 1);
	newTree->SetScale(0.1f);

    Vector2 treePos = pos + Vector2(0.0f, 27.0f);
    newTree->SetPosition(treePos.x, treePos.y);
	trees.insert({ pos, newTree });
}

void TerrainManager::DestroyTree(Vector2 pos)
{
    if (trees.find(pos) != trees.end())
    {
        trees.erase(pos);
    }
}
