#ifndef COSMIC_CONTROLLER
#define COSMIC_CONTROLLER

#include "Cosmic_Object.h"

#include <shared_mutex>
#include "glm/fwd.hpp"

#define PI  3.1415926535f
#define G   4.0f * PI * PI

class Cosmic_Controller {
    /** UNITS
     *
     * Distance: AU
     * Time: Earth year
     * Mass: Solar mass
     *
     * All other units follow
     */
public:

    // mutex for accessing without race conditioning
    std::shared_mutex mtx;

    // list of cosmic objects
    std::vector<Cosmic_Object *> cosmic_objects;

    /** Construct a Cosmic_Controller object
     */
    Cosmic_Controller();

    /** Destructor for Cosmic_Controller object
     */
    ~Cosmic_Controller();
    
    void add_cosmic_object(glm::float32_t, glm::float32_t, glm::vec4, glm::vec4);

    void update_objects_physics(glm::float32_t);

private:

    /** Calculate new acceleration for each object based on other objects
     */
    void calculate_objects_accelerations();

    /** Calculate the new position and velocity for each object
     *  based on its current acceleration
     */
    void calculate_objects_new_kinematics(glm::float32_t);
};

#endif
