﻿#include "WorldTransform.h"
#include "MathFunction.h"

void  WorldTransform::UpdateMatrix() {
	matWorld_ = MakeAffineMatrix(scale_, rotation_, translation_);
	TransferMatrix();
}