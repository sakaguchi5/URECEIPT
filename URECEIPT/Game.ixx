module; // �O���[�o�����W���[���t���O�����g
// #include�̓O���[�o�����W���[���t���O�����g���ōs��
export module Mod_Game;
import std;
import Mod_MyCommon;
import Mod_SceneManager;
import Mod_FileProcessor;
import Mod_OperationHandler;
import Mod_DPProcessor;

export
{
	class CGame :public CScene
	{
	public:
		//�R���X�g���N�^
		CGame(s_p<SceneManager> pManager, const Config &config, const std::vector<Receipt> &receipts) :CScene(pManager), config(config), receipts(receipts)
		{
			
			Init(); 
		
		}
		//�f�X�g���N�^
		~CGame() { }

		void Init();//������
		void Update();//�X�V����
		void Draw();//�`�揈��

	private:
		// ���i���X�g��������
		std::vector<Receipt> receipts;
		// �^�[�Q�b�g�l��ݒ�
		Config config;
		DynamicProgrammingProcessor dpp;
		CombinationSearch cs;
		void printClass();
		
	};

}