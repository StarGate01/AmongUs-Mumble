#include <string>
#include <cstdio>
#include <codecvt>
#include <algorithm>
#include <sstream>
#include <iostream>
#include <fstream>
#include <limits>
#include "il2cpp-appdata.h"
#include "Map.h"


using namespace app;


// Converts a map point to a string representation
std::string MapPoint::ToString()
{
    std::stringstream s;
    s << "(" << x << ", " << y << ")";
    return s.str();
}

// Converts a map point to a svg string representation
std::string MapPoint::ToSVGString()
{
    std::stringstream s;
    s << (x * 100.0f) << "," << (y * -100.0f);
    return s.str();
}

// Converts a map object to a string representation
std::string MapObject::ToString()
{
    std::stringstream s;
    s << "  " << name << " (Type ";
    s << (int)type << "):" << std::endl;
    s << "    Position: " << position.ToString() << ", Center: " << center.ToString() << 
        ", Extents: " << extents.ToString() << std::endl;
    s << "    Vertices: ";
    for (auto& vertex : vertices) s << vertex.ToString() << ", ";
    s << std::endl;
    return s.str();
}

// Converts a map object to a svg string representation
std::string MapObject::ToSVGString()
{
    std::stringstream s;
    s << "<polyline name=\"" << name << "\" points=\"";
    for (auto& vertex : vertices) s << vertex.ToSVGString() << " ";
    s << "\" />" << std::endl;
    return s.str();
}

Map map;

Map::Map():
    nameBlacklist({
        "Button"
    })
{}

// Gets vertices of box collider
void Map::GetColliderVertices(BoxCollider2D* collider, std::vector<MapPoint>& vertices, MAP_OBJECT_TYPE& type)
{
    Vector2 size = BoxCollider2D_get_size(collider, NULL);
    vertices = { { 0.0f, 0.0f }, { size.x, 0.0f }, { size.x, size.y }, { 0.0f, size.y }, { 0.0f, 0.0f } };
    type = MAP_OBJECT_TYPE::BOX;
}

// Gets vertices of polygon collider
void Map::GetColliderVertices(PolygonCollider2D* collider, std::vector<MapPoint>& vertices, MAP_OBJECT_TYPE& type)
{
    ArrayToVector(PolygonCollider2D_get_points(collider, NULL), vertices);
    type = MAP_OBJECT_TYPE::POLYGON;
}

// Gets vertices of edge (line) collider
void Map::GetColliderVertices(EdgeCollider2D* collider, std::vector<MapPoint>& vertices, MAP_OBJECT_TYPE& type)
{
    ArrayToVector(EdgeCollider2D_get_points(collider, NULL), vertices);
    type = MAP_OBJECT_TYPE::EDGE;
}

// Adds points in array to vector
void Map::ArrayToVector(Vector2__Array* source, std::vector<MapPoint>& vertices)
{
    int32_t len = Array_get_Length((Array*)source, NULL);
    for (int i = 0; i < len; i++)
    {
        // Use pointer access because array stores values
        Vector2* p = source->vector + (i * sizeof(Vector2));
        vertices.push_back({ p->x, p->y });
    }
}

float magnitude(float m1, float m2, float m3, float m4)
{
    return sqrt(m1 * m1 + m2 * m2 + m3 * m3 + m4 * m4);
}

// Finds all colliders and converts them
template<typename T> void Map::AddAddColliders(std::string netname)
{
    // Find all Unity objects matching type
    std::string tname = "UnityEngine." + netname + 
        ", UnityEngine.Physics2DModule, Version=0.0.0.0, Culture=neutral, PublicKeyToken=null";
    Object_1__Array* colliders = Object_1_FindObjectsOfType(
        Type_GetType_2((String*)il2cpp_string_new(tname.c_str()), NULL), NULL);

    // Iterate colliders
    int32_t len = Array_get_Length((Array*)colliders, NULL);
    for (int i = 0; i < len; i++)
    {
        // Use GetValue because array stores refs
        Collider2D* collider = (Collider2D*)Array_GetValue_5((Array*)colliders, i, NULL);

        // Get collider name
        String* nameRaw = Object_1_get_name((Object_1*)collider, NULL);
        std::string name = wideToNarrow.to_bytes(std::wstring((const wchar_t*)
            (&((Il2CppString*)nameRaw)->chars), ((Il2CppString*)nameRaw)->length));

        // Exclude blacklisted names (buttons etc.)
        if (std::find(nameBlacklist.begin(), nameBlacklist.end(), name) == nameBlacklist.end())
        {
            // Get collider vertices and type
            std::vector<MapPoint> vertices;
            MAP_OBJECT_TYPE type = MAP_OBJECT_TYPE::INVALID;
            GetColliderVertices((T*)collider, vertices, type);

            // Transform vertices according to translation
            Vector2 offset = Collider2D_get_offset(collider, NULL);
            Transform* trans = Component_get_transform((Component*)collider, NULL);
            Matrix4x4 localToWorld = Transform_get_localToWorldMatrix(trans, NULL);
            for (auto& vertex : vertices)
            {
                vertex.x += offset.x;
                vertex.y += offset.y;

                vertex.x *= magnitude(localToWorld.m00, localToWorld.m10, localToWorld.m20, localToWorld.m30);
                vertex.y *= magnitude(localToWorld.m01, localToWorld.m11, localToWorld.m21, localToWorld.m31);

                vertex.x += localToWorld.m03;
                vertex.y += localToWorld.m13;

                /*vertex.x += localToWorld.m03;
                vertex.y += localToWorld.m13;*/

               /* vertex.x = vertex.x * localToWorld.m00 + vertex.y * localToWorld.m01 + localToWorld.m03;
                vertex.y = vertex.x * localToWorld.m10 + vertex.y * localToWorld.m11 + localToWorld.m13;*/
            }

            // Add to map objects, include bounds (already in world space)
            Bounds bounds = Collider2D_get_bounds(collider, NULL);
            content.push_back({
                name,
                { offset.x + localToWorld.m03, offset.y + localToWorld.m13 },
                { bounds.m_Center.x, bounds.m_Center.y },
                { bounds.m_Extents.x, bounds.m_Extents.y },
                vertices, type
            });
        }
    }
}



// Rebuilds the cached state from the game state
void Map::Rebuild()
{
    content.clear();

    // These colliders are the ones known to be used
    AddAddColliders<BoxCollider2D>("BoxCollider2D");
    AddAddColliders<PolygonCollider2D>("PolygonCollider2D");
    AddAddColliders<EdgeCollider2D>("EdgeCollider2D");
}

// Prints the cached state
void Map::Print()
{
    std::cout << "Map contains " << content.size() << " colliders: " << std::endl;
    for (auto & obj : content) std::cout << obj.ToString();
}

// Saves the cache as svg file
void Map::SaveSVG(const std::string& fileName)
{
    // Assemble content string
    float xmin = std::numeric_limits<float>::infinity();
    float ymin = std::numeric_limits<float>::infinity();
    float xmax = -std::numeric_limits<float>::infinity();
    float ymax = -std::numeric_limits<float>::infinity();
    std::stringstream s;
    for (auto& obj : content)
    {
        for (auto& vertex : obj.vertices)
        {
            xmin = std::min(xmin, vertex.x * 100.f);
            ymin = std::min(ymin, vertex.y * -100.f);
            xmax = std::max(xmax, vertex.x * 100.f);
            ymax = std::max(ymax, vertex.y * -100.f);
        }
        s << obj.ToSVGString();
    }

    // Write file
    std::ofstream file;
    file.open(fileName, std::ios::out | std::ios::trunc);
    file << "<svg xmlns=\"http://www.w3.org/2000/svg\" xmlns:xlink=\"http://www.w3.org/1999/xlink\" ";
    file << "viewBox=\"" << (int)xmin << " " << (int)ymin << " " << (int)(xmax - xmin) << " " << (int)(ymax - ymin) << "\" ";
    file << "width=\"100%\" height=\"auto\" style=\"fill:none;stroke:black;stroke-width:3\">" << std::endl;
    file << s.str() << "</svg>" << std::endl;
    file.close();
}