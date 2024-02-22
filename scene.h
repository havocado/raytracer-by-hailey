#ifndef SCENE_H
#define SCENE_H

#include <vector>
#include "hittableObject.h"

class Scene {
public:
    std::vector<HittableObject *> objectList;

    CollisionData findClosestCollision(const Ray &r) const;

    std::vector<Ray> getBouncedRays(const CollisionData &closestCollision,
                                    const int &NUM_BOUNCE, const int &NUM_BOUNCED_RAYS,
                                    const int &STOP_DIVIDING_AFTER_K_BOUNCES) const;
};


#endif //SCENE_H
