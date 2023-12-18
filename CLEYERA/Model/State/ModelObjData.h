#pragma once
#include"Model.h"

class ModelObjData
{
public:
	
	ModelObjData(SModelData modelData, uint32_t index, Model* model) {
		modelData_ = modelData,
			index_ = index;
		model_ = move(model);
	}

	~ModelObjData() { delete model_; }

	SModelData GetData() { return modelData_; }
    Model* GetModel() { return model_;}

	uint32_t GetIndex() { return index_; }


private:

	Model * model_;
	SModelData modelData_;
	uint32_t index_;
};