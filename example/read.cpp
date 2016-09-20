#include "main.h"

std::vector<glm::vec3> read(const std::string& file_name) {
    std::ifstream file(file_name);
    if (!file) {
        error << "read(): Could not open file '" << file_name << "'" << Error::Throw;
    }

    std::vector<glm::vec3> result;
    std::vector<double> values;
    double current;
    std::string dummy;

    while (file >> current) {
        values.push_back(current);
        std::getline(file, dummy, ',');

        if (values.size() == 3U) {
            result.push_back(glm::vec3(values[0], values[1], values[2]));
            values.clear();
        }
    }    

    return result;
}