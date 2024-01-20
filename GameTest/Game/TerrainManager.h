#pragma once
#include "..\stdafx.h"
#include "..\app\app.h"

#include <vector>
#include "..\math\Vector2.h"

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

    std::vector<Vector2> tilePositions;
};

