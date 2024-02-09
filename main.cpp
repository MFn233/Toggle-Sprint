#include <Windows.h>
#include <iostream>
#include <stdio.h>
#include "VK_Controls.h"
#define _ GetAsyncKeyState

bool doSprinting = false;
bool lastValue = true;

using namespace std;

struct profile {
	string text_enable = "[Sprinting(Toggled)]";
	string text_disable = "[Not Sprinting]";
	int hotKey = VK_I;
};profile pro;

void loadProfile(void) {
	freopen("./toggle_sprint.config","r",stdin);
	getline(cin,pro.text_enable);//read the first line
	getline(cin,pro.text_disable);//read the second line
	cin>>hex>>pro.hotKey;//read the third line
	fclose(stdin);
	cout<<"loading profile...";
}

void render(void) {
	if(lastValue != doSprinting) {
		system("cls");
		char hotKey_ascii = pro.hotKey;
		cout<<"Hotkey: "<<hotKey_ascii<<"\n\n";
		if(doSprinting) {
			cout<<pro.text_enable<<'\n';
		} else {
			cout<<pro.text_disable<<'\n';
		}
		lastValue = doSprinting;
	}
}
void behavior(void) {
	if (_(pro.hotKey) < 0) {//Press hot key = switch mode
		if (!doSprinting) {
			doSprinting = true;
			//cout<<doSprinting<<endl;
		} else {
			doSprinting = false;
			VK_Up(VK_CTRL);
			//cout<<doSprinting<<endl;
		}
		Sleep(100);
	}
	
	if(doSprinting) {
		if(_(VK_W) < 0) {
			VK_Down(VK_CTRL);
		} else {
			VK_Up(VK_CTRL);
		}
	}
}

void mainLoop(void) {
	behavior();
	render();
	Sleep(1);
}

int main() {
	cin.tie(0),cout.tie(0);
	loadProfile();
	Sleep(1000);
	while(true) {
		mainLoop();
		if(_(VK_ESC) < 0 && _(VK_SHIFT) < 0) {
			break;
		}
	}
	exit(0);
}

//[Sprinting(Key Held)]
//[Sprinting(Toggled)]