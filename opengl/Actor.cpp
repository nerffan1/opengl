#include "Actor.h"
#include <iostream>


Actor::Actor()
{
}

void Actor::draw() const
{
    glBindVertexArray(vao);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glDrawArrays(GL_TRIANGLES, 0, vertCount);
}
