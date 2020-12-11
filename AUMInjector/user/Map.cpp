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

#pragma pack(push, 1)
struct BmpHeader {
    char bitmapSignatureBytes[2] = { 'B', 'M' };
    uint32_t sizeOfBitmapFile = 54 + (1024 * 1024 * 3);
    uint32_t reservedBytes = 0;
    uint32_t pixelDataOffset = 54;
} bmpHeader;

struct BmpInfoHeader {
    uint32_t sizeOfThisHeader = 40;
    int32_t width = 1024; // in pixels
    int32_t height = 1024; // in pixels
    uint16_t numberOfColorPlanes = 1; // must be 1
    uint16_t colorDepth = 24;
    uint32_t compressionMethod = 0;
    uint32_t rawBitmapDataSize = 0; // generally ignored
    int32_t horizontalResolution = 3780; // in pixel per meter
    int32_t verticalResolution = 3780; // in pixel per meter
    uint32_t colorTableEntries = 0;
    uint32_t importantColors = 0;
} bmpInfoHeader;

struct Pixel {
    uint8_t blue = 0;
    uint8_t green = 0;
    uint8_t red = 0;
};
#pragma pack(pop)

Map map;

Map::Map():
    nameBlacklist({
        "Button"
    })
{}

// Finds all colliders and converts them
template<typename T> void Map::AddAddColliders(std::string netname)
{
    // Find all Unity objects matching type
    std::string tname = "UnityEngine." + netname + 
        ", UnityEngine.Physics2DModule, Version=0.0.0.0, Culture=neutral, PublicKeyToken=null";
    Object_1__Array* colliders = Object_1_FindObjectsOfType(
        Type_GetType_4((String*)il2cpp_string_new(tname.c_str()), NULL), NULL);

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
            // BMP
            std::stringstream ofname;
            ofname << "maps\\" << name << "_" << i << ".bmp";
            std::ofstream fout(ofname.str(), std::ios::binary | std::ios::trunc);
            fout.write((char*)&bmpHeader, 14);
            fout.write((char*)&bmpInfoHeader, 40);

            Vector2__Boxed* v = (Vector2__Boxed*)il2cpp_object_new((Il2CppClass*)Vector2__TypeInfo);
            Vector2__ctor(v, 0.0f, 0.0f, NULL);
            Vector2 ve = *(Vector2*)v;
            for (int x = 0; x < 1024; x++)
            {
                for (int y = 0; y < 1024; y++)
                {
                    ve.x = (((float)x / 1024.0f) - 0.5f) * 80.0f;
                    ve.y = (((float)y / 1024.0f) - 0.5f) * 80.0f;

                    Pixel pixel;
                    if (Collider2D_OverlapPoint(collider, ve, NULL))
                    {
                        pixel.red = 255;
                        pixel.green = 0;
                        pixel.blue = 0;
                    }
                    else
                    {
                        pixel.red = 0;
                        pixel.green = 255;
                        pixel.blue = 0;
                    }
                    fout.write((char*)&pixel, 3);
                }
            }

            fout.close();
        }
    }
}



// Rebuilds the cached state from the game state
void Map::Rebuild()
{
    // These colliders are the ones known to be used
    AddAddColliders<BoxCollider2D>("BoxCollider2D");
    AddAddColliders<PolygonCollider2D>("PolygonCollider2D");
    AddAddColliders<EdgeCollider2D>("EdgeCollider2D");
}
