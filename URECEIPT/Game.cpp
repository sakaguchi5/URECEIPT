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
	auto x = Input<char>::read("yでシーン移行");
	if (x == 'y')
	{
		// 組み合わせ探索を実行
		dpp.initializeDP(config,receipts);
		dpp.calculateDP(config, receipts);

		cs.searchCombination(config, receipts,dpp.dp, receipts.size(), config.target);
		// 結果を表示
		auto ans = cs.GetAnswer();
		ResultDisplay::displayResults(ans);
		//rd.displayResults(ans);
	}
	x = Input<char>::read("eでシーン移行");
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
