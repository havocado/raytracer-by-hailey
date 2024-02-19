#include "scene.h"

CollisionData Scene::findClosestCollision(const Ray &r) const {
    CollisionData closestCollision(false);
    for (auto hittable: this->objectList) {
        CollisionData coll = hittable->rayCollisionPoint(r);
        if (!coll.collided) {
            continue;
        }
        if (!closestCollision.collided || coll.t < closestCollision.t) {
            closestCollision = coll;
        }
    }
    return closestCollision;
}

std::vector<Ray> Scene::getBouncedRays(const CollisionData &closestCollision,
                                const int &NUM_BOUNCE, const int &NUM_BOUNCED_RAYS,
                                const int &STOP_DIVIDING_AFTER_K_BOUNCES) const {
    std::vector<Ray> bouncedRays;
    int kthBounce = closestCollision.r.kthBounce+1;
    if (kthBounce > NUM_BOUNCE) {
        // do nothing
    }
    else if (kthBounce > STOP_DIVIDING_AFTER_K_BOUNCES) {
        bouncedRays.push_back(closestCollision.getNextRay());
    }
    else {
        for (int i = 0; i < NUM_BOUNCED_RAYS; i++) {
            bouncedRays.push_back(closestCollision.getNextRay());
        }
    }
    return bouncedRays;
}