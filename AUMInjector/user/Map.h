#pragma once

#include <string>
#include <vector>
#include "il2cpp-appdata.h"


using namespace app;


// Describes what the original type of a collider was
enum class MAP_OBJECT_TYPE : int
{
	INVALID = 0,
	BOX = 1,
	POLYGON = 2,
	EDGE = 3
};

// Descripes a point on the map
struct MapPoint
{
	float x, y;

	// Converts a map point to a string representation
	std::string ToString();

	// Converts a map point to a svg string representation
	std::string ToSVGString();
};

// Describes a collider on the map
struct MapObject
{
	std::string name;
	MapPoint position, center, extents;
	std::vector<MapPoint> vertices;
	MAP_OBJECT_TYPE type;

	// Converts a map object to a string representation
	std::string ToString();

	// Converts a map object to a svg string representation
	std::string ToSVGString();
};

// Provides access to the collision map
class Map
{

	public:
		Map();

		// Rebuilds the cached state from the game state
		void Rebuild();

		// Prints the cached state
		void Print();

		// Saves the cache as svg file
		void SaveSVG(const std::string& fileName);

	private:
		// Gets vertices of box collider
		void GetColliderVertices(BoxCollider2D* collider, std::vector<MapPoint>& vertices, MAP_OBJECT_TYPE& type);

		// Gets vertices of polygon collider
		void GetColliderVertices(PolygonCollider2D* collider, std::vector<MapPoint>& vertices, MAP_OBJECT_TYPE& type);

		// Gets vertices of edge (line) collider
        void GetColliderVertices(EdgeCollider2D* collider, std::vector<MapPoint>& vertices, MAP_OBJECT_TYPE& type);

		// Adds points in array to vector
		void ArrayToVector(Vector2__Array* source, std::vector<MapPoint>& vertices);

		// Finds all colliders and converts them
        template<typename T> void AddAddColliders(std::string netname);

		// What collider names shall not be included
		std::vector<std::string> nameBlacklist;

		// Chached map objects
		std::vector<MapObject> content;

		// String conversion helper
		std::wstring_convert<std::codecvt_utf8<wchar_t>> wideToNarrow;

};

extern Map map;