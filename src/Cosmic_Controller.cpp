#include "Cosmic_Controller.h"
#include "Cosmic_Object.h"
#include <glm/exponential.hpp>
#include <glm/fwd.hpp>

#include <mutex>

Cosmic_Controller::Cosmic_Controller() {}
Cosmic_Controller::~Cosmic_Controller() {
    for (size_t i = 0; i < this->cosmic_objects.size(); i++) {
        delete this->cosmic_objects[i];
    }
}

void Cosmic_Controller::add_cosmic_object(glm::float32_t mass, glm::float32_t radius, glm::vec4 initial_p, glm::vec4 initial_v) {
    this->cosmic_objects.push_back(new Cosmic_Object(mass, radius, initial_p, initial_v));
}

void Cosmic_Controller::update_objects_physics(glm::float32_t dt) {
    std::unique_lock<std::shared_mutex> lock(this->mtx);
    this->calculate_objects_accelerations();
    this->calculate_objects_new_kinematics(dt);
}

void Cosmic_Controller::calculate_objects_accelerations() {
    for (size_t i = 0; i < this->cosmic_objects.size(); i++) {
        Cosmic_Object * current = this->cosmic_objects[i];
        glm::vec4 total_acc = glm::vec4(0.0f);
        
        // if sun, we skip
        if (current->is_sun) {
            current->a = total_acc;
            continue;
        }

        // else, we calculate G * sum_other(other.m * r / |r|^3)
        for (size_t j = 0; j < this->cosmic_objects.size(); j++) {
            if (i == j) 
                continue;
            Cosmic_Object * other = this->cosmic_objects[j];
            total_acc += current->normal_to(*other) * (other->m / current->dist2(*other));
        }

        // multiply everything by G
        current->a = total_acc * G;
    }
}

void Cosmic_Controller::calculate_objects_new_kinematics(glm::float32_t dt) {
    for (size_t i = 0; i < this->cosmic_objects.size(); i++) {
        Cosmic_Object * current = this->cosmic_objects[i];
        if (current->is_sun) continue;
        current->v = current->v + current->a * dt;
        current->p = current->p + current->v * dt;
    }
}
