#ifndef COSMIC_OBJECT_H
#define COSMIC_OBJECT_H

#include <glm/fwd.hpp>
#include <glm/glm.hpp>

class Cosmic_Object {
    /** UNITS
     *
     * Distance: AU
     * Time: Earth year
     * Mass: Solar mass
     *
     * All other units follow
     */
public:
    // mass
    glm::float32_t m;

    // radius of the object, calculate from its core
    glm::float32_t r;

    // position
    glm::vec4 p;

    // velocity
    glm::vec4 v;

    // acceleration
    glm::vec4 a;

    // is the sun in the solar system
    bool is_sun;

public:

    /** Create a Cosmic_Object object, representing possibly the sun, a planet, or
     *  a planet's moon (no moon for the meantime).
     */
    Cosmic_Object(glm::float32_t, glm::float32_t, glm::vec4, glm::vec4);
    
    /** Calculate distance between this and other cosmic object
     */
    glm::float32_t dist2(const Cosmic_Object&) const;

    /** Calculate the normal vector to the other cosmic object
     */
    glm::vec4 normal_to(const Cosmic_Object&) const;
};

#endif
