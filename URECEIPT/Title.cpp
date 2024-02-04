//�^�C�g�����
//#include<string>
#include <Windows.h>
import std;
import Mod_MyCommon;
import Mod_SceneManager;
import Mod_Title;
import Mod_Game;
import Mod_InputKey;

//������
void CTitle::Init()
{
	oHandler.addFunction([]() { return std::string("data3.txt"); });
	oHandler.addFunction([this]() {return fileSelector.GetSelectedFileName() ;});

	fileprocessor.processFilePath(oHandler, "fileData", std::string(TARGETDATASTRING));

	//�����S�폜
	oHandler.removeAllFunctions();

	oHandler.addFunction([]() { return std::string("config2.txt"); });
	oHandler.addFunction([this]() {return fileSelector.GetSelectedFileName(); });

	fileprocessor.processFilePath(oHandler, "fileConfig", std::string(TARGETCONFIGSTRING));


	LineParser<std::vector<Receipt>> tes3
		= [](const std::string& line, std::vector<Receipt>& receipts)
		{
			// 1�s���ƂɃp�[�X
			int year, month, day;
			char slash;
			std::istringstream lineStream(line);
			lineStream >> year >> slash >> month >> slash >> day;

			// �N������8���̐����ɕϊ�
			int date = year * 10000 + month * 100 + day;

			// ���l��ǂݎ��Areceipts�ɒǉ�
			int value;
			while (lineStream >> value) {
				receipts.push_back(Receipt(date, value));
			}
		};

	// �ݒ���ƃ����o�ϐ��̑Ή���ێ�����}�b�v
	std::map<std::string, int*> configMap = {
		{"MAX_COUNT_THRESHOLD", &myData.config.maxCountThreshold},
		{"MAX_SIZE_THRESHOLD", &myData.config.maxSizeThreshold},
		{"MIN_COUNT", &myData.config.minCount},
		{"MAX_COUNT", &myData.config.maxCount},
		{"MAX", &myData.config.MAX},
		{"TARGET", &myData.config.target}
	};

	
	LineParser< Config, std::map<std::string, int*> > tes4
		= [](const std::string& line, Config& config, std::map<std::string, int*> configMap)
		{
			// �s���L�[�ƒl�ɕ���
			std::istringstream iss(line);
			std::string key, value;
			if (std::getline(iss, key, '=') && std::getline(iss, value))
			{
				// �L�[���g���đΉ����郁���o�ϐ���T���A�l��ݒ�
				auto it = configMap.find(key);
				if (it != configMap.end())
				{
					*(it->second) = std::stoi(value);
				}
			}

		};

	fileprocessor.processFile("fileData",tes3, myData.receipts);
	fileprocessor.processFile("fileConfig", tes4, myData.config, configMap);



}

//�X�V����
void CTitle::Update()
{
	
	if (isTargetChar<'y'>(Input<char>::getInputWithRetry("y�ŃV�[���ڍs")))
	{
		smanager->SetScene<CGame>(smanager, myData);
	}

}

//�`�揈��
void CTitle::Draw()
{
	
	

}
