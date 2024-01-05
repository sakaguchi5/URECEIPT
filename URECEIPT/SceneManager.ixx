module; // グローバルモジュールフラグメント

// #includeはグローバルモジュールフラグメント内で行う
//シーン管理用ヘッダ

//#include "main.h"
//#include<memory>
//#include<vector>

export module Mod_SceneManager;// mulibモジュールのインターフェース単位の宣言
import std; 
import Mod_MyCommon;


class SceneManager;//シーン管理クラス
// 無名空間ごとエクスポート！
export
{
	//シーンの基底クラス
	class CScene
	{
	public:
		CScene(s_p<SceneManager> pManager) : smanager(pManager) {}
		//デストラクタ
		virtual ~CScene() {}
		//更新処理
		virtual void Update() { }
		//描画処理
		virtual void Draw() {}
	protected:
		s_p<SceneManager> smanager;
	private:
	protected:
		MyData mydata;
		virtual void printClass() = 0;
	private:
	};

	//シーン管理クラス
	class SceneManager
	{
	public:
		SceneManager() {}
		~SceneManager() {}

		void Update() { scene->Update(); }
		void Draw() { scene->Draw(); }

		//シーンの作成
		template <typename T, class... Args>
		void SetScene(s_p<SceneManager> pManager, Args... args)
		{
			scene = std::make_unique<T>(pManager, args...);
		}
	private:
		//シーンポインタ	
		u_p<CScene>scene;
	};


}
