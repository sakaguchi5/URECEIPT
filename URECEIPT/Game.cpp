import std;
import Mod_MyCommon;
import Mod_SceneManager;
import Mod_Game;
import Mod_InputKey;


void CGame::Init()
{
	printClass();
	config.PrintConfig();
}

void CGame::Update()
{
	auto x = Input<char>::read("y�ŃV�[���ڍs");
	if (x == 'y')
	{
		// �g�ݍ��킹�T�������s
		dpp.initializeDP(config,receipts);
		dpp.calculateDP(config, receipts);

		cs.searchCombination(config, receipts,dpp.dp, receipts.size(), config.target);
		// ���ʂ�\��
		auto ans = cs.GetAnswer();
		ResultDisplay::displayResults(ans);
		//rd.displayResults(ans);
	}
	x = Input<char>::read("e�ŃV�[���ڍs");
	if (x == 'e')
	{
		std::cout << "ok";
	}
	
}

void CGame::Draw()
{
}

void CGame::printClass()
{
	//std::cout << "CTitle " << std::endl;
	//std::cout << typeid(this).name() << std::endl;
	std::println("CGame Start");
}
