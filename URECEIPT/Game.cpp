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
	if (isTargetChar<'y'>(Input<char>::getInputWithRetry("y�őg�ݍ��킹�T�������s")))
	{
		// �g�ݍ��킹�T�������s
		dpp.initializeDP(config,receipts);
		dpp.calculateDP(config, receipts);

		cs.searchCombination(config, receipts,dpp.dp, (int)receipts.size(), config.target);
		// ���ʂ�\��
		auto ans = cs.GetAnswer();
		ResultDisplay::displayResults(ans);
		//rd.displayResults(ans);
		if (isTargetChar<'n'>(Input<char>::getInputWithRetry("n�ŃV�[���ڍs")))
		{
			
			std::cout << "ok";
			int casenum;
			
			std::string str2 = ("1����" + std::to_string(config.maxSizeThreshold) + "�̒�����I��ł�������");
			casenum = Input<int>::getInputWithRetry_ex(
				[=](int x) {return(0 < x && x < config.maxSizeThreshold + 1); } ,
				"case���w�肵�Ă�������\n" + str2);
			std::string outputpath;
			//�o�͗p��OPENFILENAME �\���̂�p�ӂ���K�v�����邽�߁A��U�o�͐�͌Œ�
			/*
			OperationHandler<std::string> oHandler;
			
			oHandler.addFunction([]() { return std::string("output.txt"); });
			oHandler.addFunction([]() 
				{
					FileSelector fileSelector;
					return fileSelector.GetSelectedFileName();
				});

			// ��̕����񂪕Ԃ������胋�[�v
			do
			{
				outputpath = oHandler.selectOperation("1�Ńf�t�H���g�A2�Ńt�@�C���I��: ");
				if (outputpath.empty())
				{
					std::cout << "������x�I���������Ă�������" << std::endl;
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
