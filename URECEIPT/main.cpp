//#include<memory>
//#include <iostream>
#include <Windows.h>
import std;
import Mod_MyCommon;
import Mod_SceneManager;

import Mod_Title;
//import Mod_Mouse;


int main()
{

	//シーン管理クラス
	auto smanager = std::make_shared<SceneManager>();
	//初回シーン
	smanager->SetScene<CTitle>(smanager);


	//ループ
	while (true)
	{
		//ClearDrawScreen();	//画面クリア


		//シーンの更新と描画処理
		smanager->Update();
		smanager->Draw();


		
		//ScreenFlip();	//画面を更新

		//escキーでプログラム終了
		//if (CheckHitKey(KEY_INPUT_ESCAPE) || (ProcessMessage() == -1)) break;
		if (GetAsyncKeyState(VK_ESCAPE))	break;
	}

	std::cout << "hello";
	int a;
	std::cin >> a;
	return 0;
}