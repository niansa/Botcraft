#include <vector>
#include <algorithm>

#include "botcraft/Game/World/Biome.hpp"

namespace Botcraft
{
    // The corners of the triangle defining grass and leaves colors in the following order:
    // upper left, lower left, lower right
    const std::vector<std::vector<unsigned int> > grass_color_triangle{ { 71, 205, 51 }, { 191, 183, 85 }, { 128, 180, 151 } };
    const std::vector<std::vector<unsigned int> > leaves_color_triangle{ { 26, 191, 0 }, { 174, 164, 42 }, { 96, 161, 123 } };

    const int sea_level = 62;

    Biome::Biome(const std::string& name_, const float temperature_,
                 const float rainfall_, const BiomeType biome_type_)
    {
        name = name_;
        temperature = temperature_;
        rainfall = rainfall_;
        biome_type = biome_type_;

        default_grass = ComputeColorTriangle(0, true);
        default_leaves = ComputeColorTriangle(0, false);
    }

    Biome::~Biome()
    {
    }

    const std::string& Biome::GetName() const
    {
        return name;
    }

    const unsigned int Biome::GetColorMultiplier(const int height, const bool is_grass) const
    {
        if (height <= sea_level)
        {
            if (is_grass)
            {
                return default_grass;
            }
            else
            {
                return default_leaves;
            }
        }


        switch (biome_type)
        {
        case BiomeType::Classic:
        {
            const int relativ_height = std::max(0, height - sea_level);
            return ComputeColorTriangle(relativ_height, is_grass);
        }
        case BiomeType::Swamp:
        {
            // We do not use the Perlin Noise as specified in the wiki, but rather
            // we choose to select the color of temperature > -0.1
            // Maybe one day I'll take the time to implement a Perlin Noise function
            // somewhere
            return 0xFF6A7039;
        }
        case BiomeType::DarkForest:
        {
            const int relativ_height = std::max(0, height - sea_level);
            const unsigned int base_color = ComputeColorTriangle(relativ_height, is_grass);
            // Average the base color with the hardcoded value
            // Average formula from https://www.compuphase.com/graphic/scale3.htm
            return ((((base_color ^ 0xFF28340A) & 0xFFFEFEFE) >> 1) + (base_color & 0xFF28340A));

        }
        case BiomeType::Badlands:
        {
            const unsigned int base_color = is_grass ? 0xFF90814D : 0xFF9E814D;
            return base_color;
        }
        default:
            return 0xFFFFFFFF;
        }
        return 0xFFFFFFFF;
    }

    const unsigned int Biome::GetWaterColorMultiplier() const
    {
#if PROTOCOL_VERSION < 393 /* < 1.13 */
        switch (biome_type)
        {
        case BiomeType::Swamp:
            // The hardcoded value for the water in swamps
            return 0xFFE0FFAE;
        default:
            return 0xFFFFFFFF;
        }
#else
        switch (biome_type)
        {
            // I couldn't find these values anywhere so
            // I tried to find something which works
        case BiomeType::Swamp:
            return 0xFF4F4F2F; // dark green grayish
        case BiomeType::WarmOcean:
            return 0xFFD0E040; // turquoise
        case BiomeType::LukewarmOcean: // light tealish
            return 0xFFb2b964;
        case BiomeType::ColdOcean:
            return 0xFF7B3C24; // dark indigoish
        case BiomeType::FrozenOcean:
            return 0xFF341930;  // dark purple
        default:
            return 0xFFD48717; // blue
        }
#endif
    }

    const unsigned int Biome::ComputeColorTriangle(const int height, const bool is_grass) const
    {
        const float local_temperature = std::max(0.0f, std::min(1.0f, temperature - height * 0.0016667f));
        const float local_rainfall = std::max(0.0f, std::min(1.0f, rainfall)) * local_temperature;

        std::vector<float> triangle_coordinates(3);
        triangle_coordinates[0] = local_rainfall;
        triangle_coordinates[1] = local_temperature - local_rainfall;
        triangle_coordinates[2] = 1.0f - local_temperature;

        std::vector<float> color(3);
        for (int i = 0; i < 3; ++i)
        {
            for (int j = 0; j < 3; ++j)
            {
                if (is_grass)
                {
                    color[j] += triangle_coordinates[i] * grass_color_triangle[i][j];
                }
                else
                {
                    color[j] += triangle_coordinates[i] * leaves_color_triangle[i][j];
                }
            }
        }

        const unsigned char r = static_cast<unsigned char>(std::max(0.0f, std::min(255.0f, color[0])));
        const unsigned char g = static_cast<unsigned char>(std::max(0.0f, std::min(255.0f, color[1])));
        const unsigned char b = static_cast<unsigned char>(std::max(0.0f, std::min(255.0f, color[2])));
        const unsigned char a = 255;

        return ((a << 24) | (b << 16) | (g << 8) | r);
    }
} //Botcraft
