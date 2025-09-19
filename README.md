Welcome to the Windows Console Display Class! (Which works on the Windows console pre-Windows 11, since that's when they decided to change everything)

This class gives you the ability to, with relative ease, draw rectangles, lines, borders, of any character and color in the Windows console!
Simply add the header file to your program and you can use these easy commands!


There are currently 10 custom commands:

ConsoleDisplay(new Screen Width, new Screen Height)

addGraphic(graphicX, graphicY, fileName, graphicForegroundColor, graphicBackgroundColor)

addString(stringX, stringY, inputString, stringForegroundColor, stringBackgroundColor)

drawScreen()

addBorder(borderChar, borderForegroundColor, borderBackgroundColor)

clearScreen()

clearScreenBuffer()

setConCurPosition(conX, conY, conForegroundColor, conBackgroundColor)

addRect(cornerX, cornerY, rectWidth, rectHeight, solid, rectChar, rectForegroundColor, rectBackgroundColor)

addLine(x1, y1, x2, y2, lineChar, lineForegroundColor, lineBackgroundColor)


The Console Display Class uses the Windows Console API enum system for colors, where each color is represented by an integer:
0  Black
1  DarkBlue
2  DarkGreen
3  DarkCyan
4  DarkRed
5  DarkMagenta
6  DarkYellow
7  Gray
8  DarkGray
9  Blue
10 Green
11 Cyan
12 Red
13 Magenta
14 Yellow
15 White
