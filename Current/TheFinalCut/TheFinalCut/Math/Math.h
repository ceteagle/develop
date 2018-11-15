#ifndef __MATH__H__
#define __MATH__H__

#include <math.h>

#include "Vector3.h"

namespace TFC
{
    namespace Math
    {
#define PI 3.14159

        double ConvertToRadians(double degrees)
        {
            return (degrees * PI) / 180.0;
        }

        double ConvertToDegrees(double radians)
        {
            return (radians * 180) / PI;
        }

        TFC::Math::Vector3<float> RotatePoint(TFC::Math::Vector3<float> point, TFC::Math::Vector3<float> pivot, float rot)
        {
            double radRot = ConvertToRadians(rot);
            double s = sin(radRot);
            double c = cos(radRot);
            point = point - pivot;

            float newX = (float)(point.x * c - point.y * s);
            float newY = (float)(point.x * s + point.y * c);

            point.x = newX + pivot.x;
            point.y = newY + pivot.y;
            
            return point;
        }

        float Min(std::vector<float> vec)
        {
            float min = vec[0];
            for (size_t i = 1; i < vec.size(); i++)
            {
                if (vec[i] < min)
                    min = vec[i];
            }
            return min;
        }

        float Max(std::vector<float> vec)
        {
            float max = vec[0];
            for (size_t i = 1; i < vec.size(); i++)
            {
                if (vec[i] > max)
                    max = vec[i];
            }
            return max;
        }
    }
}
#endif  // __MATH__H__
