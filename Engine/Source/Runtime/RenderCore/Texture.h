#pragma once

namespace Hina
{

class Texture
{
public:
	virtual ~Texture() = default;

	virtual const uint32_t GetWidth() const = 0;
	virtual const uint32_t GetHeight() const = 0;
	virtual const uint32_t GetRenderID() const = 0;
	virtual const std::string &GetPath() const = 0;

	virtual void Bind(const uint32_t slot) const = 0;

	virtual inline bool operator==(const Texture &other) const = 0;
};

} // namespace Hina
