#ifndef DEFINES_H
#define DEFINES_H

enum QFigureType: quint8
{
    Rect = 0,
    Ellipse,
    Triangle,
    Line
};

enum Columns {
    Id,
    Type,
    Position,
    Region,
    Visible,
    Delete
};

#endif // DEFINES_H
