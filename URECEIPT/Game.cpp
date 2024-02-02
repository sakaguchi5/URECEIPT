import std;
import Mod_MyCommon;
import Mod_SceneManager;
import Mod_Game;
import Mod_InputKey;
import Mod_FileProcessor;
import Mod_OperationHandler;

void CGame::Init()
{
	printClass();
	config.PrintConfig();
}

void CGame::Update()
{
	if (isTargetChar<'y'>(Input<char>::getInputWithRetry("yで組み合わせ探索を実行")))
	{
		// 組み合わせ探索を実行
		dpp.initializeDP(config,receipts);
		dpp.calculateDP(config, receipts);

		cs.searchCombination(config, receipts,dpp.dp, (int)receipts.size(), config.target);
		// 結果を表示
		auto ans = cs.GetAnswer();
		ResultDisplay::displayResults(ans);
		//rd.displayResults(ans);
		if (isTargetChar<'n'>(Input<char>::getInputWithRetry("nでシーン移行")))
		{
			
			std::cout << "ok";
			int casenum;
			
			std::string str2 = ("1から" + std::to_string(config.maxSizeThreshold) + "の中から選んでください");
			casenum = Input<int>::getInputWithRetry_ex(
				[=](int x) {return(0 < x && x < config.maxSizeThreshold + 1); } ,
				"caseを指定してください\n" + str2);
			std::string outputpath;
			//出力用のOPENFILENAME 構造体を用意する必要があるため、一旦出力先は固定
			/*
			OperationHandler<std::string> oHandler;
			
			oHandler.addFunction([]() { return std::string("output.txt"); });
			oHandler.addFunction([]() 
				{
					FileSelector fileSelector;
					return fileSelector.GetSelectedFileName();
				});

			// 空の文字列が返される限りループ
			do
			{
				outputpath = oHandler.selectOperation("1でデフォルト、2でファイル選択: ");
				if (outputpath.empty())
				{
					std::cout << "もう一度選択し直してください" << std::endl;
				}

			} while (outputpath.empty());*/

			outputpath = ("output.txt");

		
			FileProcessor::writeAnswer(ans[casenum - 1], outputpath);


		}

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
