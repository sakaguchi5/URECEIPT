//module; // �O���[�o�����W���[���t���O�����g
// #include�̓O���[�o�����W���[���t���O�����g���ōs��
export module Mod_Title;
import std;
import Mod_MyCommon;
import Mod_SceneManager;
import Mod_FileProcessor;
import Mod_OperationHandler;

export
{

	class CTitle :public CScene
	{
	public:
		//�R���X�g���N�^
		CTitle(s_p<SceneManager> pManager) :CScene(pManager) { Init(); }
		//�f�X�g���N�^
		~CTitle() { }

		void Init();//������
		void Update();//�X�V����
		void Draw();//�`�揈��

	private:
		// ���i���X�g��������
		std::vector<Receipt> receipts;
		// �^�[�Q�b�g�l��ݒ�
		Config config;
		//void printClass() { std::cout << typeid(this).name() << std::endl; };
		void printClass();
		FileSelector fileSelector;
		
		FileProcessor fileprocessor;
		OperationHandler<std::string> oHandler;

		/*
		void displayResults(std::vector<Receipt>& ans)
		{
			std::map<int, std::vector<int>> result;

			for (const auto& receipt : ans) {
				result[receipt.date].push_back(receipt.price);
			}

			for (const auto& entry : result) {
				std::cout << "Key: " << entry.first << ", Values: ";
				for (int value : entry.second) {
					std::cout << value << " ";
				}
				std::cout << std::endl;
			}
			std::cout << std::endl;
			result.clear();

		}*/
	};


}