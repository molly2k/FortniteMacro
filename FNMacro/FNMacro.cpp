#include <iostream>
#include <cstdlib>
#include <Windows.h>
#include <ostream>

using namespace std;



class MENU
{
public:

	int response = 0;
	string index = "OFF";

	//menu
	void MenuPrint()
	{
		cout << endl;
		cout << "MENU";
		cout << endl;
		cout << "LSHIFT: MACRO " << " [" << index << "]" << "         TOGGLE F8 TO TURN ON/OFF" << endl;
		cout << "END: EXIT" << endl;
	}

	//macro
	void MacroHook()
	{
		SHORT key;
		UINT mappedkey;
		INPUT input = { 0 };
		key = VkKeyScan('e');
		mappedkey = MapVirtualKey(LOBYTE(key), 0);
		input.type = INPUT_KEYBOARD;
		input.ki.dwFlags = KEYEVENTF_SCANCODE;
		input.ki.wScan = mappedkey;
		SendInput(1, &input, sizeof(input));
		Sleep(1);
		input.ki.dwFlags = KEYEVENTF_SCANCODE | KEYEVENTF_KEYUP;
		SendInput(1, &input, sizeof(input));
	}
};

int main()
{

	MENU menu;
	menu.MenuPrint();
	while (true)
	{
	check:
		if (GetAsyncKeyState(VK_END))
		{
			system("cls");
			cout << "Exiting...";
			Sleep(3000);
			return 0;
		}
		if (GetAsyncKeyState(VK_F8))
		{
			if (menu.response == 0)
			{
				system("cls");
				menu.index = "ON";
				menu.response = 1;
				menu.MenuPrint();
				Sleep(200);
			}
			else
			{
				system("cls");
				menu.index = "OFF";
				menu.response = 0;
				menu.MenuPrint();
				Sleep(200);
			}
		}
		while (menu.response == 1)
		{
			if (GetAsyncKeyState(VK_LSHIFT))
				menu.MacroHook();
			goto check;
		}
	} 
}
