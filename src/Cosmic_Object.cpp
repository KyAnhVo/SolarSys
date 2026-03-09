#include "Cosmic_Object.h"
#include <glm/fwd.hpp>
#include <glm/geometric.hpp>

Cosmic_Object::Cosmic_Object(glm::float32_t mass, glm::float32_t radius, glm::vec4 initial_p, glm::vec4 initial_v) {
    assert(initial_p[3] == 1);
    assert(initial_v[3] == 0);

    this->m = mass;
    this->r = radius;
    this->p = initial_p;
    this->v = initial_v;
    this->a = glm::vec4(0.0f);

}

glm::float32_t Cosmic_Object::dist2(const Cosmic_Object& other) const {
    glm::vec4 to_other = other.p - this->p;
    return glm::dot(to_other, to_other);
}

glm::vec4 Cosmic_Object::normal_to(const Cosmic_Object& other) const {
    return glm::normalize(other.p - this->p);
}
