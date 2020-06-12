#define TINYOBJLOADER_IMPLEMENTATION
#include "object_loader.h"

object loadObject(std::string file) {
    object result;

    tinyobj::attrib_t attrib;
    std::vector<tinyobj::shape_t> shapes;
    std::vector<tinyobj::material_t> materials;

    std::string warn;
    std::string err;

    tinyobj::LoadObj(&attrib, &shapes, &materials, &err, file.c_str());
    std::vector<GLfloat> vertices;
    std::vector<GLfloat> colors;

    for (size_t s = 0; s < shapes.size(); s++) {
        size_t index_offset = 0;
        for (size_t f = 0; f < shapes[s].mesh.num_face_vertices.size(); f++) {
            int fv = shapes[s].mesh.num_face_vertices[f];
            for (size_t v = 0; v < fv; v++) {
                tinyobj::index_t idx = shapes[s].mesh.indices[index_offset + v];
                tinyobj::real_t vx = attrib.vertices[3 * idx.vertex_index + 0];
                tinyobj::real_t vy = attrib.vertices[3 * idx.vertex_index + 1];
                tinyobj::real_t vz = attrib.vertices[3 * idx.vertex_index + 2];

                result.vertices.push_back(vx);
                result.vertices.push_back(vy);
                result.vertices.push_back(vz);
                result.colors.push_back(0.3f + vx);
                result.colors.push_back(0.3f + vy);
                result.colors.push_back(0.3f + vz);
            }
            index_offset += fv;
        }
    }

    return result;
}
