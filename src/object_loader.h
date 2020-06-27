#ifndef OBJECT_LOADER_H_
#define OBJECT_LOADER_H_

#include <glad/glad.h>
#include <tiny_obj_loader.h>

#include <string>

#include "raw_data_object.h"

RawDataObject loadObject(std::string file);

#endif
