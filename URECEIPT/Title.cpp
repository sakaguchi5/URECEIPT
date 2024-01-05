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
	//std::cout << "CTitle " << std::endl; 
	//std::string str = "fileData";
	printClass();
	oHandler.addFunction([]() { return std::string("data3.txt"); });
	oHandler.addFunction([this]() {return fileSelector.GetSelectedFileName() ;});

	std::string filepath;
	bool loopf;
	do
	{
		// ��̕����񂪕Ԃ������胋�[�v
		while ((filepath = oHandler.selectOperation("1�Ńf�t�H���g�A2�Ńt�@�C���I��: ")).empty())
		{
			//std::cout << "Invalid result. Retrying..." << std::endl;
		}
		loopf=fileprocessor.addfileReaderUmap("fileData", filepath, std::string(TARGETDATASTRING));
	} while (!loopf);

	//�����S�폜
	oHandler.removeAllFunctions();

	oHandler.addFunction([]() { return std::string("config2.txt"); });
	oHandler.addFunction([this]() {return fileSelector.GetSelectedFileName(); });

	do
	{
		// ��̕����񂪕Ԃ������胋�[�v
		while ((filepath = oHandler.selectOperation("1�Ńf�t�H���g�A2�Ńt�@�C���I��: ")).empty())		
		{	
			;//�������Ȃ�
		}
		loopf = fileprocessor.addfileReaderUmap("fileConfig", filepath, std::string(TARGETCONFIGSTRING));
	} while (!loopf);


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
		{"MAX_COUNT_THRESHOLD", &config.maxCountThreshold},
		{"MAX_SIZE_THRESHOLD", &config.maxSizeThreshold},
		{"MIN_COUNT", &config.minCount},
		{"MAX_COUNT", &config.maxCount},
		{"MAX", &config.MAX},
		{"TARGET", &config.target}
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

	fileprocessor.processFile("fileData",tes3, receipts);
	fileprocessor.processFile("fileConfig", tes4, config, configMap);



}

//�X�V����
void CTitle::Update()
{


	/*
	std::function<std::string()>f = []() { return std::string("hello"); };

	oHandler.addFunction(f);
	oHandler.addFunction([]() { return std::string("world"); });
	oHandler.addFunction([]() { return std::string("end"); });
	std::cout << oHandler.selectOperation() << std:: endl;*/

	//displayResults(receipts);

	//auto str = oHandler.selectOperation();
	//std::cout << str << std::endl;
	//std::cout << "" << std::endl;

	auto x = Input<char>::read("y�ŃV�[���ڍs");
	if (x=='y')
	{
		smanager->SetScene<CGame>(smanager,config,receipts);
	}

	






}

//�`�揈��
void CTitle::Draw()
{
	
	

}
/**/
void CTitle::printClass() 
{
	//std::cout << "CTitle " << std::endl;
	//std::cout << typeid(this).name() << std::endl;
	std::println("CTitle Start");
}
