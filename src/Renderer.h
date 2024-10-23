#ifndef RENDERER_H
#define RENDERER_H
#include <vector>
#include <external/glad.h>

class Renderer {
    Element* element;

    void draw() {
        element->draw();
    }
};
//
// SVG: 12 elemetns -> 12 renderer ddee
//
// Renderer rend;
//
// vector <Element *> elements;
//
// Renderer r;
// r.draw() -> for (element: )

#endif //RENDERER_H
