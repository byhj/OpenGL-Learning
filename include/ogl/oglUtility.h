#ifndef OGLUTILITY_H
#define OGLUTILITY_H

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

namespace byhj
{
	struct MvpMatrix
	{
	   glm::mat4 model;
	   glm::mat4 view;
	   glm::mat4 proj;
	};
}
#endif
