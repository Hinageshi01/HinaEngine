#pragma once

#include "Camera/Camera.h"

namespace Hina
{

class CameraController
{
public:
	virtual void SetCamera(const std::shared_ptr<Camera> &pCamera) = 0;
};

} //namespace Hina
