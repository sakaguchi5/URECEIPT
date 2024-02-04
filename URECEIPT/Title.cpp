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
	oHandler.addFunction([]() { return std::string("data3.txt"); });
	oHandler.addFunction([this]() {return fileSelector.GetSelectedFileName() ;});

	fileprocessor.processFilePath(oHandler, "fileData", std::string(TARGETDATASTRING));

	//操作を全削除
	oHandler.removeAllFunctions();

	oHandler.addFunction([]() { return std::string("config2.txt"); });
	oHandler.addFunction([this]() {return fileSelector.GetSelectedFileName(); });

	fileprocessor.processFilePath(oHandler, "fileConfig", std::string(TARGETCONFIGSTRING));


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

	fileprocessor.processFile("fileData",tes3, myData.receipts);
	fileprocessor.processFile("fileConfig", tes4, myData.config, configMap);



}

//更新処理
void CTitle::Update()
{
	
	if (isTargetChar<'y'>(Input<char>::getInputWithRetry("yでシーン移行")))
	{
		smanager->SetScene<CGame>(smanager, myData);
	}

}

//描画処理
void CTitle::Draw()
{
	
	

}
