#pragma once
#include "..\..\stdafx.h"
#include "..\..\app\app.h"

#include "..\..\math\Vector2.h"
#include "..\Color.h"
#include <unordered_map>

#include "..\GameSettings.h"

class TerrainManager
{
public:
	// Singlton pattern
	////////
	static TerrainManager& getInstance()
	{
		static TerrainManager instance;
		return instance;
	}
	////////

    int height;
    int width;
	
    void Update(float dt);
	void Draw();
	void Destroy();

    void Generate();

    float GetFloor(float x);
    void Explode(Vector2 position, float radius);

	void Reset();
    
private:
	// Singlton pattern
	////////
	TerrainManager();
	TerrainManager(TerrainManager const&);
    void operator=(TerrainManager const&);
	////////

	void Settle();
	void CreateTree(Vector2 pos, int type);
	void DestroyTree(Vector2 pos);

    float tileSize = 5.0f;
	float surface = TERRAIN_SURFACE;
    float amplitude = TERRAIN_AMPLITUDE;
    float period = TERRAIN_PERIOD;

    std::unordered_map<Vector2, Color, Vector2::HashFunction> tiles;
	std::unordered_map<Vector2, CSimpleSprite*, Vector2::HashFunction> trees;
};

