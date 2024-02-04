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
		CGame(s_p<SceneManager> pManager, const MyData& myData) :CScene(pManager), myData(myData)
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
		//std::vector<Receipt> receipts;
		// ターゲット値を設定
		//Config config;

		MyData myData;
		DynamicProgrammingProcessor dpp;
		CombinationSearch cs;
		
	};

}