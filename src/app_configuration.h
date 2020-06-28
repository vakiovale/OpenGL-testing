#ifndef APP_CONFIGURATION_H_
#define APP_CONFIGURATION_H_

#include <spdlog/spdlog.h>

#include <boost/property_tree/json_parser.hpp>
#include <exception>
#include <string>

typedef struct {
    std::string name;
    uint width = 800;
    uint height = 600;
} Configuration;

class AppConfiguration {
   private:
    Configuration conf_;
    void resolveWindowConfig(boost::property_tree::ptree json);
    void resolveName(boost::property_tree::ptree json);

   public:
    void loadConfiguration(std::string config_file);
    const Configuration getConfig();
};

#endif
