#pragma once
class Marble
{
public:
    Marble();
    ~Marble();

    Marble * _prev;
    Marble * _next;
    long long _value;
};

