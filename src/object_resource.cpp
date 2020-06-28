#include "object_resource.h"

ObjectResource loadResource(
    std::pair<std::basic_string<char>, boost::property_tree::ptree> object) {
    ObjectResource result;
    std::string file = object.second.get<std::string>("file");
    result.file = file;
    result.object = loadObject(file);
    auto translate = object.second.get_child("translate");
    result.translate =
        glm::vec3(translate.get<float>("x"), translate.get<float>("y"), translate.get<float>("z"));
    auto scale = object.second.get_optional<float>("scale");
    if (scale.has_value()) {
        result.scale = glm::vec3(scale.get(), scale.get(), scale.get());
    } else {
        result.scale = glm::vec3(10.0f);
    }
    return result;
}

std::vector<ObjectResource> loadResources(
    std::vector<std::pair<std::basic_string<char>, boost::property_tree::ptree>> objects) {
    std::vector<ObjectResource> resources;
    for (auto& object : objects) {
        resources.push_back(loadResource(object));
    }
    spdlog::info("Loaded " + std::to_string(resources.size()) + " resource(s)");
    return resources;
}

unsigned int numberOfThreadsToUse() {
    return std::thread::hardware_concurrency() > 0 ? std::thread::hardware_concurrency() : 2;
}

std::vector<ObjectResource> initializeResourceObjects() {
    spdlog::info("Loading resources from objects.json");
    std::vector<ObjectResource> resources;
    try {
        boost::property_tree::ptree json;
        boost::property_tree::read_json("resources/objects.json", json);
        auto objects = json.get_child("objects");
        spdlog::info(std::to_string(objects.size()) + " number of objects to load");

        std::vector<std::future<std::vector<ObjectResource>>> futures;
        unsigned int num_of_cpu_threads = numberOfThreadsToUse();
        unsigned int batch_size = std::floor((float)objects.size() / num_of_cpu_threads);

        spdlog::info("Hardware concurrency: " +
                     std::to_string(std::thread::hardware_concurrency()));
        spdlog::info("Batch size: " + std::to_string(batch_size));
        spdlog::info("Loading starts...");

        std::vector<std::pair<std::basic_string<char>, boost::property_tree::ptree>> batch;
        for (auto& obj : objects) {
            if (batch.size() == batch_size) {
                spdlog::info("Loading full batch");
                futures.push_back(std::async(&loadResources, std::move(batch)));
                batch = {};
            }
            batch.push_back(obj);
        }
        spdlog::info("Loading last batch (size: " + std::to_string(batch.size()) + ")");
        futures.push_back(std::async(&loadResources, batch));

        for (auto& future : futures) {
            future.wait();
            for (auto& resource : future.get()) {
                resources.push_back(resource);
            }
        }
    } catch (const std::exception& exception) {
        spdlog::error("Failed parsing json: " + std::string(exception.what()));
        std::rethrow_exception(std::current_exception());
    }
    spdlog::info("Finished loading resources");
    return resources;
}
