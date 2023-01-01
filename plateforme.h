#ifndef PLATEFORME_H_INCLUDED
#define PLATEFORME_H_INCLUDED

#include <iostream>
#include <algorithm>
#include <cstdlib>


enum Tetrominos
{
    NoShape, ZShape, SShape, LineShape, TShape, SquareShape, LShape, MirroredLShape

};

class Shape
{
public:
    Shape(){SetShape(NoShape);}
    void SetShape(Tetrominos shape);
    void SetRandomShape();

    Tetrominos GetShape()const {return pieceShape;}
    int x(int index)const {return coords[index][0];}
    int y(int index)const {return coords[index][1];}

    int MinX()const;
    int MaxX()const;
    int MinY()const;
    int MaxY()const;

    Shape RotateLeft()const;
    Shape RotateRight()const;

private:
    void SetX(int index, int x){coords[index][0] = x;}
    void SetY(int index, int y){coords[index][1] = y;}
    Tetrominos pieceShape;
    int coords[4][2];

};

#endif // PLATEFORME_H_INCLUDED
