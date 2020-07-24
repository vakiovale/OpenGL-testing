#include "object_storage.h"

ObjectStorage::ObjectStorage(std::vector<ObjectResource>&& resources): resources_(resources) {
    
}

ObjectStorage::~ObjectStorage() {
    
}

std::vector<ObjectResource>& ObjectStorage::getAll() {
    return resources_;
}

void ObjectStorage::translateAll(glm::vec3 translate) {
    for (auto& resource : resources_) {
        resource.position = resource.position + translate;
    }
}
