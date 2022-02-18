# SVG_Parser
This project implements a basic SVG parser useing libxml2 library.SVG files are parsed and converted into well-formatted humanly readable strings.




This program uses a LinkedListAPI to store various vector image components.

Functionality:
- Get the shapes element, title, description, namespace and their attributes out of an SVG file.
  - The following SVG elements that are supported right now: svg, rects, circles, g (group), paths.
- Search through the image (SVG File) to find if the image contains specific elements.


How to compile?
 $ make SVGParser
 
How to run?
 $ ./SVGParser
 
Things to keep in mind before compiling and running:
- the libxml2 library must be installed
  - $ sudo apt-get install libxml2.
- the svg file must exist in the bin directory or else it will give a parsing error
  - I have added a test.svg file already there.

Example

![gitSVG](https://user-images.githubusercontent.com/95400232/154628565-f24dc59f-42e4-480b-a4e8-345d77287340.png)
