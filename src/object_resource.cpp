#include "object_resource.h"

object_resource loadResource(
    std::pair<std::basic_string<char>, boost::property_tree::ptree> object) {
    object_resource result;
    std::string file = object.second.get<std::string>("file");
    result.file = file;
    result.object = loadObject(file);
    auto translate = object.second.get_child("translate");
    result.translate =
        glm::vec3(translate.get<float>("x"), translate.get<float>("y"), translate.get<float>("z"));
    return result;
}

std::vector<object_resource> initializeResourceObjects() {
    spdlog::info("Loading resources from objects.json");
    std::vector<object_resource> resources;
    try {
        boost::property_tree::ptree json;
        boost::property_tree::read_json("resources/objects.json", json);
        auto objects = json.get_child("objects");

        std::vector<std::future<object_resource>> futures;
        for (auto& obj : objects) {
            futures.push_back(std::async(&loadResource, obj));
        }
        for (auto& future : futures) {
            future.wait();
            resources.push_back(future.get());
        }
    } catch (const std::exception& exception) {
        spdlog::error("Failed parsing json: " + std::string(exception.what()));
        throw exception;
    }
    spdlog::info("Finished loading resources");
    return resources;
}

