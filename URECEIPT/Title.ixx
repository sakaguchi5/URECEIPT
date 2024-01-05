//module; // グローバルモジュールフラグメント
// #includeはグローバルモジュールフラグメント内で行う
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
		//コンストラクタ
		CTitle(s_p<SceneManager> pManager) :CScene(pManager) { Init(); }
		//デストラクタ
		~CTitle() { }

		void Init();//初期化
		void Update();//更新処理
		void Draw();//描画処理

	private:
		// 商品リストを初期化
		std::vector<Receipt> receipts;
		// ターゲット値を設定
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