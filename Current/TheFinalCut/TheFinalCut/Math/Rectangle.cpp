#include "Rectangle.h"
#include "../Graphics/Engine.h"
#include "Math.h"

#include <iostream>
#include <vector>

using namespace TFC::Math;
using namespace std;

Rectangle::Rectangle()
{
    _size = Vector3<float>(0.0);
    _position = Vector3<float>(0.0);
    _scale = Vector3<float>(1.0);

    _upperLeftVertex = Vector3<float>(0.0);
    _upperRightVertex = Vector3<float>(0.0);
    _lowerLeftVertex = Vector3<float>(0.0);
    _lowerRightVertex = Vector3<float>(0.0);
    
}

Rectangle::Rectangle(Vector3<float> size) : Rectangle()
{
    _size = size;
}

Rectangle::Rectangle(Vector3<float> size, Vector3<float> position) : Rectangle()
{
    _size = size;
    _position = position;
}

void Rectangle::MoveBy(Vector3<float> by)
{
    _position += by;
}

void Rectangle::MoveTo(Vector3<float> to)
{
    _position = to;
}

void Rectangle::SetSize(Vector3<float> size)
{
    _size = size;
}

void Rectangle::SetScale(float x)
{
    _scale = Vector3<float>(x, x, 0.0);
}

void Rectangle::SetScale(Vector3<float>& v)
{
    _scale = v;
}

void Rectangle::Render(Vector3<float> color)
{
    glLoadIdentity();
    glTranslatef(_position.x, _position.y, _position.z);
    //glRotatef(_rotation, 0, 0, 1);
    glScalef(_scale.x, _scale.y, _scale.z);

    glColor4f(color.x, color.y, color.z, 1);

    glBegin(GL_LINE_LOOP);
    {
        glVertex2f(_lowerLeftVertex.x, _lowerLeftVertex.y);
        glVertex2f(_lowerRightVertex.x, _lowerRightVertex.y);
        glVertex2f(_upperRightVertex.x, _upperRightVertex.y);
        glVertex2f(_upperLeftVertex.x, _upperLeftVertex.y);
    }
    glEnd();
}

void Rectangle::UpdateVertices()
{
    _lowerLeftVertex = Vector3<float>( - (_size.x * .5),  - (_size.y * .5), 0.);
    _lowerRightVertex = Vector3<float>( + (_size.x * .5),  - (_size.y * .5), 0.);
    _upperLeftVertex = Vector3<float>( - (_size.x * .5),  + (_size.y * .5), 0.);
    _upperRightVertex = Vector3<float>( + (_size.x * .5),  + (_size.y * .5), 0.);
}

void Rectangle::Rotate(float rotation)
{
    _lowerLeftVertex = Math::RotatePoint(_lowerLeftVertex, Math::Vector3<float>(0.0), rotation);
    _lowerRightVertex = Math::RotatePoint(_lowerRightVertex, Math::Vector3<float>(0.0), rotation);
    _upperLeftVertex = Math::RotatePoint(_upperLeftVertex, Math::Vector3<float>(0.0), rotation);
    _upperRightVertex = Math::RotatePoint(_upperRightVertex, Math::Vector3<float>(0.0), rotation);
}

bool Rectangle::CollidesWith(Rectangle& rectangle)
{
    Vector3<float> aUR = (_upperRightVertex * _scale) + _position;
    Vector3<float> aUL = (_upperLeftVertex* _scale + _position) ;
    Vector3<float> aLR = (_lowerRightVertex* _scale + _position) ;
    Vector3<float> aLL = (_lowerLeftVertex* _scale + _position) ;

    Vector3<float> bUR = (rectangle._upperRightVertex * rectangle._scale + rectangle._position);
    Vector3<float> bUL = (rectangle._upperLeftVertex * rectangle._scale + rectangle._position);
    Vector3<float> bLR = (rectangle._lowerRightVertex * rectangle._scale + rectangle._position);
    Vector3<float> bLL = (rectangle._lowerLeftVertex * rectangle._scale + rectangle._position);

    //cout << "aURV " << _upperRightVertex.ToString() << endl;
    //cout << "aULV " << _upperLeftVertex.ToString() << endl;
    //cout << "aLRV " << _lowerRightVertex.ToString() << endl;
    //cout << "aLLV " << _lowerLeftVertex.ToString() << endl;

    //cout << "a POS " << _position.ToString() << endl;
    //cout << "a SCALE " << _scale.ToString() << endl;
    //cout << "aUR " << aUR.ToString() << endl;
    //cout << "aUL " << aUL.ToString() << endl;
    //cout << "aLR " << aLR.ToString() << endl;
    //cout << "aLL " << aLL.ToString() << endl << endl;

    //cout << "bURV " << rectangle._upperRightVertex.ToString() << endl;
    //cout << "bULV " << rectangle._upperLeftVertex.ToString() << endl;
    //cout << "bLRV " << rectangle._lowerRightVertex.ToString() << endl;
    //cout << "bLLV " << rectangle._lowerLeftVertex.ToString() << endl;

    //cout << "b POS " << rectangle._position.ToString() << endl;
    //cout << "b SCALE " << rectangle._scale.ToString() << endl;

    //cout << "bUR " << bUR.ToString() << endl;
    //cout << "bUL " << bUL.ToString() << endl;
    //cout << "bLR " << bLR.ToString() << endl;
    //cout << "bLL " << bLL.ToString() << endl << endl;

    //cout << "aUR SCALED " << (aUR * _scale).ToString() << endl;
    //cout << "aUL SCALED " << (aUL * _scale).ToString() << endl;
    //cout << "aLR SCALED " << (aLR * _scale).ToString() << endl;
    //cout << "aLL SCALED " << (aLL * _scale).ToString() << endl << endl;

    //cout << "bUR SCALED " << (bUR * rectangle._scale).ToString() << endl;
    //cout << "bUL SCALED " << (bUL * rectangle._scale).ToString() << endl;
    //cout << "bLR SCALED " << (bLR * rectangle._scale).ToString() << endl;
    //cout << "bLL SCALED " << (bLL * rectangle._scale).ToString() << endl << endl;

    float aMax = 0.;
    float aMin = 0.;
    float bMax = 0.;
    float bMin = 0.;

    Vector3<float> axis1 = aUR - aUL;
    Vector3<float> axis2 = aUR - aLR;
    Vector3<float> axis3 = bLR - bUR;
    Vector3<float> axis4 = bUL - bUR;

    //cout << "axis1 " << axis1.ToString() << endl;
    //cout << "axis2 " << axis2.ToString() << endl;
    //cout << "axis3 " << axis3.ToString() << endl;
    //cout << "axis4 " << axis4.ToString() << endl << endl;

    std::vector<Vector3<float>> axes;
    axes.push_back(axis1);
    axes.push_back(axis2);
    axes.push_back(axis3);
    axes.push_back(axis4);

    for (int i = 0; i < axes.size(); i++)
    {
        Vector3<float> aURProj = aUR.Project(axes[i]);
        Vector3<float> aULProj = aUL.Project(axes[i]);
        Vector3<float> aLRProj = aLR.Project(axes[i]);
        Vector3<float> aLLProj = aLL.Project(axes[i]);

        Vector3<float> bURProj = bUR.Project(axes[i]);
        Vector3<float> bULProj = bUL.Project(axes[i]);
        Vector3<float> bLRProj = bLR.Project(axes[i]);
        Vector3<float> bLLProj = bLL.Project(axes[i]);

        float aURScalar = aURProj.Dot(axes[i]);
        float aULScalar = aULProj.Dot(axes[i]);
        float aLRScalar = aLRProj.Dot(axes[i]);
        float aLLScalar = aLLProj.Dot(axes[i]);

        float bURScalar = bURProj.Dot(axes[i]);
        float bULScalar = bULProj.Dot(axes[i]);
        float bLRScalar = bLRProj.Dot(axes[i]);
        float bLLScalar = bLLProj.Dot(axes[i]);

        std::vector<float> aScalars;
        aScalars.push_back(aURScalar);
        aScalars.push_back(aULScalar);
        aScalars.push_back(aLRScalar);
        aScalars.push_back(aLLScalar);

        std::vector<float> bScalars;
        bScalars.push_back(bURScalar);
        bScalars.push_back(bULScalar);
        bScalars.push_back(bLRScalar);
        bScalars.push_back(bLLScalar);

        aMin = Math::Min(aScalars);
        aMax = Math::Max(aScalars);

        bMin = Math::Min(bScalars);
        bMax = Math::Max(bScalars);

        if ((bMin <= aMax && bMax >= aMin))
        {

        }
        else
        {
            return false;
        }
    }

    return true;
}