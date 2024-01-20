#pragma once
#include "..\stdafx.h"
#include "..\app\app.h"

#include "..\math\Vector2.h"
#include "Color.h"
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
	
    void Update(float dt);
	void Draw();
	void Destroy();

    float GetFloor(float x);
    void Explode(Vector2 position);
    
private:
	// Singlton pattern
	////////
	TerrainManager();
	TerrainManager(TerrainManager const&);
    void operator=(TerrainManager const&);
	////////

    std::unordered_map<Vector2, Color, Vector2::HashFunction> tiles;
};

