#include "app_configuration.h"

const Configuration AppConfiguration::getConfig() { return conf_; }

void AppConfiguration::loadConfiguration(std::string config_file) {
    spdlog::info("Load configurations");
    try {
        boost::property_tree::ptree json;
        boost::property_tree::read_json(config_file, json);

        resolveWindowConfig(json);
        resolveName(json);

    } catch (const std::exception& exception) {
        spdlog::error("Failed loading configurations: " + std::string(exception.what()));
        std::rethrow_exception(std::current_exception());
    }
}

void AppConfiguration::resolveWindowConfig(boost::property_tree::ptree json) {
    boost::optional<uint> width = json.get_optional<uint>("window.width");
    boost::optional<uint> height = json.get_optional<uint>("window.height");

    if (!width.has_value() || !height.has_value()) {
        spdlog::critical("No configuration for window.height or window.width!");
    } else {
        spdlog::info("Width: " + std::to_string(width.value()));
        spdlog::info("Height: " + std::to_string(height.value()));
        conf_.width = width.value();
        conf_.height = height.value();
    }
}

void AppConfiguration::resolveName(boost::property_tree::ptree json) {
    boost::optional<std::string> name = json.get_optional<std::string>("name");
    if (name.has_value()) {
        conf_.name = name.value();
    }
}
