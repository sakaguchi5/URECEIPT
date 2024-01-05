module; // �O���[�o�����W���[���t���O�����g

// #include�̓O���[�o�����W���[���t���O�����g���ōs��
//�V�[���Ǘ��p�w�b�_

//#include "main.h"
//#include<memory>
//#include<vector>

export module Mod_SceneManager;// mulib���W���[���̃C���^�[�t�F�[�X�P�ʂ̐錾
import std; 
import Mod_MyCommon;


class SceneManager;//�V�[���Ǘ��N���X
// ������Ԃ��ƃG�N�X�|�[�g�I
export
{
	//�V�[���̊��N���X
	class CScene
	{
	public:
		CScene(s_p<SceneManager> pManager) : smanager(pManager) {}
		//�f�X�g���N�^
		virtual ~CScene() {}
		//�X�V����
		virtual void Update() { }
		//�`�揈��
		virtual void Draw() {}
	protected:
		s_p<SceneManager> smanager;
	private:
	protected:
		MyData mydata;
		virtual void printClass() = 0;
	private:
	};

	//�V�[���Ǘ��N���X
	class SceneManager
	{
	public:
		SceneManager() {}
		~SceneManager() {}

		void Update() { scene->Update(); }
		void Draw() { scene->Draw(); }

		//�V�[���̍쐬
		template <typename T, class... Args>
		void SetScene(s_p<SceneManager> pManager, Args... args)
		{
			scene = std::make_unique<T>(pManager, args...);
		}
	private:
		//�V�[���|�C���^	
		u_p<CScene>scene;
	};


}
