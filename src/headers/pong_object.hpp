#pragma once
#include <string>
#include "color.hpp"    // TextColor, setTextColor(), resetTextColor()
#include "ultils.hpp"   // move_cursor(), random_range()

struct XYPosition {
    float x;
    float y;
};

class PongObject {
public:
    // length = height in rows, thickness = width in columns
    // symbol is a UTF-8 string (e.g. "█" or "●")
    PongObject(int windowX, int windowY, int length, int thickness, const std::string& symbol = "█");

    virtual ~PongObject() {}

    // --- geometry/state ---
    XYPosition getPosition() const;
    void setPosition(float x, float y);
    void setWindowLimits(int maxX, int maxY);

    int getLength()     const;
    int getThickness()  const;
    std::string getSymbol() const;
    void setSymbol(const std::string& s);

    // --- visuals ---
    void setColor(TextColor c);
    TextColor getColor() const;
    void switchColor();               // pick a random ANSI color

    // --- rendering ---
    virtual void draw()  const;       // prints the object
    virtual void clear() const;       // erases the object

    // --- helpers ---
    void clampToBounds();             // keeps within 1..(limit-2) box

    // optional per-frame physics (no-op by default)
    virtual void update(float /*deltaTime*/) {}

protected:
    int _windowLimitX, _windowLimitY; // terminal bounds in cols/rows
    XYPosition _position;             // top-left anchor (column=x, row=y)
    int _length;                      // rows (height)
    int _thickness;                   // cols (width)
    std::string _symbol;              // printed glyph
    TextColor _color = WHITE;
};
