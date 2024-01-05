//タイトル画面
//#include<string>
#include <Windows.h>
import std;
import Mod_MyCommon;
import Mod_SceneManager;
import Mod_Title;
import Mod_Game;
import Mod_InputKey;

//初期化
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
		// 空の文字列が返される限りループ
		while ((filepath = oHandler.selectOperation("1でデフォルト、2でファイル選択: ")).empty())
		{
			//std::cout << "Invalid result. Retrying..." << std::endl;
		}
		loopf=fileprocessor.addfileReaderUmap("fileData", filepath, std::string(TARGETDATASTRING));
	} while (!loopf);

	//操作を全削除
	oHandler.removeAllFunctions();

	oHandler.addFunction([]() { return std::string("config2.txt"); });
	oHandler.addFunction([this]() {return fileSelector.GetSelectedFileName(); });

	do
	{
		// 空の文字列が返される限りループ
		while ((filepath = oHandler.selectOperation("1でデフォルト、2でファイル選択: ")).empty())		
		{	
			;//何もしない
		}
		loopf = fileprocessor.addfileReaderUmap("fileConfig", filepath, std::string(TARGETCONFIGSTRING));
	} while (!loopf);


	LineParser<std::vector<Receipt>> tes3
		= [](const std::string& line, std::vector<Receipt>& receipts)
		{
			// 1行ごとにパース
			int year, month, day;
			char slash;
			std::istringstream lineStream(line);
			lineStream >> year >> slash >> month >> slash >> day;

			// 年月日を8桁の整数に変換
			int date = year * 10000 + month * 100 + day;

			// 数値を読み取り、receiptsに追加
			int value;
			while (lineStream >> value) {
				receipts.push_back(Receipt(date, value));
			}
		};

	// 設定情報とメンバ変数の対応を保持するマップ
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
			// 行をキーと値に分割
			std::istringstream iss(line);
			std::string key, value;
			if (std::getline(iss, key, '=') && std::getline(iss, value))
			{
				// キーを使って対応するメンバ変数を探し、値を設定
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

//更新処理
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

	auto x = Input<char>::read("yでシーン移行");
	if (x=='y')
	{
		smanager->SetScene<CGame>(smanager,config,receipts);
	}

	






}

//描画処理
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
