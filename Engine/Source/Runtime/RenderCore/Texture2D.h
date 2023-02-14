#pragma once

#include "Texture.h"

namespace Hina
{

class Texture2D : public Texture
{
public:
	static std::shared_ptr<Texture2D> Create(const std::string &path);
};

} // namespace Hina
