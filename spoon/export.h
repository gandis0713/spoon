#pragma once

// clang-format off
#if defined(SPOON_SHARED_LIBRARY)
    #if defined(_WIN32)
        #if defined(SPOON_IMPLEMENTATION)
            #define SPOON_EXPORT __declspec(dllexport)
        #else
            #define SPOON_EXPORT __declspec(dllimport)
        #endif
    #else // defined(_WIN32)
        #if defined(SPOON_IMPLEMENTATION)
            #define SPOON_EXPORT __attribute__((visibility("default")))
        #else
            #define SPOON_EXPORT
        #endif
    #endif // defined(_WIN32)
#else      // defined(SPOON_SHARED_LIBRARY)
    #define SPOON_EXPORT
#endif // defined(SPOON_SHARED_LIBRARY)
// clang-format on