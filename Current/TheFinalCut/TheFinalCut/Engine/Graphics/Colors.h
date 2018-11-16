#ifndef __COLORS__H__
#define __COLORS__H__

#include "../../Math/Vector3.h"

namespace TFC
{
    namespace Engine
    {
        namespace Graphics
        {
            static TFC::Math::Vector3<float> COLOR_WHITE = TFC::Math::Vector3<float>(1.0, 1.0, 1.0);
            static TFC::Math::Vector3<float> COLOR_RED = TFC::Math::Vector3<float>(1.0, 0.0, 0.0);
            static TFC::Math::Vector3<float> COLOR_GREEN = TFC::Math::Vector3<float>(0.0, 1.0, 0.0);
            static TFC::Math::Vector3<float> COLOR_BLUE = TFC::Math::Vector3<float>(0.0, 0.0, 1.0);
        }
    }
}
#endif  // __COLORS__H__
