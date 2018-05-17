#include "Model.h" 

Model::Model()
{
	_vboID = 0;
} 

Model::Model(vboInfo3D info)
{
	_vboID = 0;
	init(info);	
}

Model::~Model()
{}

void Model::init(vboInfo3D info)
{
	_info = info;
	if(!_vboID)
	{
		glGenBuffers(1, &_vboID);
	 }


}

void Model::draw()
{}
