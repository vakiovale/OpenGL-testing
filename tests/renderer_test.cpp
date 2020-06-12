#include "renderer.h"

#include <glm/ext.hpp>
#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>
#include <iostream>

#include "catch.hpp"

const glm::vec<4, bool> GLM_TRUE(true, true, true, true);

void print(const glm::mat4 matrix) {
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            std::cout << matrix[j][i] << "\t";
        }
        std::cout << std::endl;
    }
}

std::array<float, 16> to_flat_array(const glm::mat4& matrix) {
    std::array<float, 16> result;
    const float* values = glm::value_ptr(matrix);
    for (int i = 0; i < 16; i++) {
        result[i] = values[i];
    }
    return result;
}

SCENARIO("Matrix transformations", "[matrix]") {
    GIVEN("an identity matrix") {
        glm::mat4 matrix(1.0);
        WHEN("multiplying with identity matrix") {
            THEN("returns same matrix") {
                glm::mat4 expectedMatrix = matrix * glm::mat4(1.0);
                REQUIRE(glm::equal(matrix, expectedMatrix) == GLM_TRUE);
                REQUIRE(to_flat_array(matrix) == to_flat_array(expectedMatrix));
            }
        }
    }

    GIVEN("a vector") {
        glm::vec4 vector(1.0, 2.0, 3.0, 1.0);
        WHEN("multiplying with identity matrix") {
            THEN("returns same vector") {
                glm::mat4 identity(1.0);
                glm::vec4 result = identity * vector;
                REQUIRE(glm::equal(vector, result) == GLM_TRUE);
            }
        }

        WHEN("multiplying with translate x matrix") {
            THEN("returns vector with x translation") {
                glm::mat4 translateXmatrix(1.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0, 0.0, 0.0, 0.0, 1.0,
                                           0.0, 3.0, 0.0, 0.0, 1.0);
                glm::vec4 result = translateXmatrix * vector;
                REQUIRE(glm::equal(glm::vec4(4.0, 2.0, 3.0, 1.0), result) == GLM_TRUE);
            }
        }

        WHEN("multiplying with glm translate") {
            THEN("returns vector with translation") {
                glm::mat4 translateMatrix = glm::translate(glm::vec3(-5.0, 0.0, 0.0));
                glm::vec4 result = translateMatrix * vector;
                REQUIRE(glm::equal(glm::vec4(-4.0, 2.0, 3.0, 1.0), result) == GLM_TRUE);
            }
        }
    }
}
