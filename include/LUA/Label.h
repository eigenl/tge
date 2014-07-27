#ifndef LUA_LABEL_OBJECT
#define LUA_LABEL_OBJECT

#include <Label.h>

#include "lunar.h"
#include "strutil/strutil.h"

#define OBJ_CLASS Label
#define LUA_OBJ_CLASS LuaLabel

namespace tge
{
  class LUA_OBJ_CLASS
  {
  public:

    LUNA_CLASS_HEADER_INSTANCE

  };
}

#undef OBJ_CLASS
#undef LUA_OBJ_CLASS

#endif
