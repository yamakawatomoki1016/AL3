#pragma once
#include "Model.h"
#include "WorldTransform.h"

///<summary>
///���L����
///</summary>
class Player {

	public:
		///<summary>
		///������
		///</summary>
		///<param name="model">���f��</param>
		///<param name="textureHandle">�e�N�X�`���n���h��</param>
	    void Initialize(Model* model, uint32_t textureHandle);

		///<summary>
		///�X�V
		///</summary>
	    void Update();

		///<summary>
		///�`��
		///</summary>
	    void Draw(ViewProjection);

	private:
		//���[���h�ϊ��f�[�^
	    WorldTransform worldTransform_;
		//���f��
	    Model* model_ = nullptr;
		//�e�N�X�`���n���h��
	    uint32_t textureHandle_ = 0u;
};