#include "basic.h"
#include "object.h"

// NOLINTNEXTLINE
class object *gRoot = new object((class object *)-1);
// NOLINTNEXTLINE
class object *gAxis = new object(gRoot, point(160, 120, -200));
