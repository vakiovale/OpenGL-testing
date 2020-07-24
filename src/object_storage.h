#ifndef OBJECT_STORAGE_H_
#define OBJECT_STORAGE_H_

#include <glm/glm.hpp>
#include <vector>

#include "object_resource.h"

class ObjectStorage {
   private:
    std::vector<ObjectResource> resources_;

   public:
    ObjectStorage(std::vector<ObjectResource>&& resources);
    ~ObjectStorage();
    std::vector<ObjectResource>& getAll();
    void translateAll(glm::vec3 translate);
};

#endif
