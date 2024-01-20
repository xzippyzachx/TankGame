#pragma once
#include "..\..\stdafx.h"
#include "..\..\app\app.h"

#include "..\..\math\Vector2.h"
#include "..\Color.h"
#include <unordered_map>

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
    void Explode(Vector2 position);

    void Settle();
    
private:
	// Singlton pattern
	////////
	TerrainManager();
	TerrainManager(TerrainManager const&);
    void operator=(TerrainManager const&);
	////////

    float tileSize = 5.0f;
    float amplitude = 20.0f;
    float period = 100.0f;
    float surface = 100.0f;

    std::unordered_map<Vector2, Color, Vector2::HashFunction> tiles;
};

