module; // グローバルモジュールフラグメント
// #includeはグローバルモジュールフラグメント内で行う
export module Mod_Game;
import std;
import Mod_MyCommon;
import Mod_SceneManager;
import Mod_FileProcessor;
import Mod_OperationHandler;
import Mod_DPProcessor;

export
{
	class CGame :public CScene
	{
	public:
		//コンストラクタ
		CGame(s_p<SceneManager> pManager, const Config &config, const std::vector<Receipt> &receipts) :CScene(pManager), config(config), receipts(receipts)
		{
			
			Init(); 
		
		}
		//デストラクタ
		~CGame() { }

		void Init();//初期化
		void Update();//更新処理
		void Draw();//描画処理

	private:
		// 商品リストを初期化
		std::vector<Receipt> receipts;
		// ターゲット値を設定
		Config config;
		DynamicProgrammingProcessor dpp;
		CombinationSearch cs;
		void printClass();
		
	};

}