#include "Actor.h"


Actor::Actor()
{
}

void Actor::draw()
{
    glBindVertexArray(vao);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glDrawArrays(GL_POINTS, 0, vertCount);
}
