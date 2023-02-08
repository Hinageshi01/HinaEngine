#pragma once

#include "Texture.h"
#include <memory>

namespace Hina
{

class Texture2D : public Texture
{
public:
	static std::shared_ptr<Texture2D> Create(const uint32_t width, const uint32_t height);
	static std::shared_ptr<Texture2D> Create(const std::string &path);
};

} // namespace Hina
