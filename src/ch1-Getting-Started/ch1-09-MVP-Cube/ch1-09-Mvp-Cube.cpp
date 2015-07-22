/*
 *                      Model Matrix              View Matrix
 * Local(Object) Space ------------->World Space------------>
 *                       Proj Matrix                 
 * Camera(View)  Space ------------->Clip  Space(change data to (-1.0, 1.0) 
 * which is NDC, frustum clip , then take the  perspective division 
 * Viewport
 * ----------> Screen Space( Map to Window Screen Width and Height)
 */
#include "RenderSystem.h"
#include <memory>

int main(int argc, const char **argv)
{
	auto app = std::make_shared<byhj::RenderSystem>();

	app->Run(app);

	return 0;
}