#include "ModelBatch.h" 

ModelBatch::ModelBatch()
{
	//_vboID = 0;
} 

ModelBatch::ModelBatch(vboInfo3D info)
{
//	_vboID = 0;
	init(info);	
}

ModelBatch::~ModelBatch()
{}

void ModelBatch::init(vboInfo3D info)
{
	//_info = info;
	//if(!_vboID)
	//{
	//	glGenBuffers(1, &_vboID);
	// }


}

//void ModelBatch::draw()
//{}
