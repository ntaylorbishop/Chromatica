#pragma once

#include <string>
#include <map>
#include <vector>

#include "Engine/General/Core/Memory/UntrackedAllocator.hpp"
#include "Engine/General/Utils/ErrorWarningAssert.hpp"
#include "Engine/Math/Vector2.hpp"

typedef unsigned char BYTE;
typedef Vector2 TexCoords;
typedef unsigned int uint;
typedef std::string String;
typedef unsigned long ulong;
typedef unsigned char uchar;

#define STATIC
#define VIRTUAL
#define INLINE
#define COMPARE(a, b) (((a) > (b)) - ((a) < (b)))