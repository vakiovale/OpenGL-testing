#ifndef OBJECT_RESOURCE_H_
#define OBJECT_RESOURCE_H_

#include <spdlog/spdlog.h>

#include <boost/property_tree/json_parser.hpp>
#include <boost/property_tree/ptree.hpp>
#include <future>
#include <glm/glm.hpp>
#include <string>
#include <thread>
#include <vector>

#include "object_loader.h"
#include "raw_data_object.h"

typedef struct {
    std::string file;
    RawDataObject object;
    glm::vec3 translate;
    glm::vec3 scale;
} ObjectResource;

ObjectResource loadResource(
    std::pair<std::basic_string<char>, boost::property_tree::ptree> object);

std::vector<ObjectResource> initializeResourceObjects();

#endif
