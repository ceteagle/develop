#ifndef __RECTANGLE__H__
#define __RECTANGLE__H__

#include "Vector3.h"

namespace TFC
{
    namespace Math
    {
        class Rectangle
        {
        public:
            Rectangle();
            Rectangle(Vector3<float> size);
            Rectangle(Vector3<float> size, Vector3<float> position);

            void MoveBy(Vector3<float> by);
            void MoveTo(Vector3<float> to);
            void SetSize(Vector3<float> size);
            void SetScale(float s);
            void SetScale(TFC::Math::Vector3<float>& v);

            void UpdateVertices();
            void Render(Vector3<float> color);
            void Rotate(float rotation);

            bool CollidesWith(Rectangle& rectangle);

        private:
            Vector3<float> _size;
            TFC::Math::Vector3<float> _scale;

        protected:
            Vector3<float> _position;
            Vector3<float> _upperLeftVertex;
            Vector3<float> _upperRightVertex;
            Vector3<float> _lowerLeftVertex;
            Vector3<float> _lowerRightVertex;
        };
    }
}
#endif  // __RECTANGLE__H__
