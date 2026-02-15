# Windows Console Display Class

A lightweight C++ class for drawing graphics directly in the Windows Console using the Windows Console API.

> ⚠️ Designed for the classic Windows Console (pre-Windows 11 console redesign).

This class allows you to easily draw:

* Rectangles
* Lines
* Borders
* Strings
* Custom graphics
* Colored text elements

All using `CHAR_INFO` buffers and the Windows Console API.

---

## Getting Started

Simply include the header file in your project:

```cpp
#include "ConsoleDisplay.h"
```

Create a display instance:

```cpp
ConsoleDisplay display(screenWidth, screenHeight);
```

Then use the provided drawing functions and call:

```cpp
display.drawScreen();
```

---

## Available Commands

### Constructor

```cpp
ConsoleDisplay(screenWidth, screenHeight)
```

Creates a new console display with the specified dimensions.

---

### Drawing Functions

```cpp
addGraphic(graphicX, graphicY, fileName, graphicForegroundColor, graphicBackgroundColor)
```

Draws a graphic from a file at the specified coordinates.

```cpp
addString(stringX, stringY, inputString, stringForegroundColor, stringBackgroundColor)
```

Draws a string at the specified location.

```cpp
addRect(cornerX, cornerY, rectWidth, rectHeight, solid, rectChar, rectForegroundColor, rectBackgroundColor)
```

Draws a rectangle (solid or outline).

```cpp
addLine(x1, y1, x2, y2, lineChar, lineForegroundColor, lineBackgroundColor)
```

Draws a line between two points using an integer line algorithm.

```cpp
addBorder(borderChar, borderForegroundColor, borderBackgroundColor)
```

Draws a border around the screen.

---

### Screen Control

```cpp
drawScreen()
```

Renders the screen buffer to the console.

```cpp
clearScreen()
```

Clears the console screen.

```cpp
clearScreenBuffer()
```

Clears the internal drawing buffer.

```cpp
setConCurPosition(conX, conY, conForegroundColor, conBackgroundColor)
```

Sets the console cursor position and colors.

---

## Color System

The class uses the Windows Console API color enum values:

| Value | Color       |
| ----- | ----------- |
| 0     | Black       |
| 1     | DarkBlue    |
| 2     | DarkGreen   |
| 3     | DarkCyan    |
| 4     | DarkRed     |
| 5     | DarkMagenta |
| 6     | DarkYellow  |
| 7     | Gray        |
| 8     | DarkGray    |
| 9     | Blue        |
| 10    | Green       |
| 11    | Cyan        |
| 12    | Red         |
| 13    | Magenta     |
| 14    | Yellow      |
| 15    | White       |

Foreground and background colors are combined using bitwise operations internally.

---

## Notes

* Uses `CHAR_INFO` buffers for double buffering.
* Optimized integer-based line and circle drawing.
* Designed for classic Windows Console behavior.
* No external dependencies beyond `<windows.h>`.
