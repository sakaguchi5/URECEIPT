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

	//�V�[���Ǘ��N���X
	auto smanager = std::make_shared<SceneManager>();
	//����V�[��
	smanager->SetScene<CTitle>(smanager);


	//���[�v
	while (true)
	{
		//ClearDrawScreen();	//��ʃN���A


		//�V�[���̍X�V�ƕ`�揈��
		smanager->Update();
		smanager->Draw();


		
		//ScreenFlip();	//��ʂ��X�V

		//esc�L�[�Ńv���O�����I��
		//if (CheckHitKey(KEY_INPUT_ESCAPE) || (ProcessMessage() == -1)) break;
		if (GetAsyncKeyState(VK_ESCAPE))	break;
	}

	std::cout << "hello";
	int a;
	std::cin >> a;
	return 0;
}