// Generated C++ file by Il2CppInspector - http://www.djkaty.com - https://github.com/djkaty
// Helper functions

#pragma once

#include <string>
#include <sstream>
#include <iomanip>

#include "il2cpp-metadata-version.h"

// Helper function to get the module base address
uintptr_t il2cppi_get_base_address();

#if _MSC_VER >= 1920
// Helper function to convert Il2CppString to std::string
std::string il2cppi_to_string(Il2CppString* str);

// Helper function to convert System.String to std::string
std::string il2cppi_to_string(app::String* str);
#endif

// Helper function to check if a metadata usage pointer is initialized
template<typename T> bool il2cppi_is_initialized(T* metadataItem) {
#if __IL2CPP_METADATA_VERISON < 270
    return *metadataItem != 0;
#else
    // Metadata >=27 (Unity 2020.2)
    return !((uintptr_t)*metadataItem & 1);
#endif
}
