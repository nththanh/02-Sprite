/* =============================================================
	INTRODUCTION TO GAME PROGRAMMING SE102
	
	SAMPLE 02 - SPRITE AND ANIMATION

	This sample illustrates how to:

		1/ Render a sprite (within a sprite sheet)
		2/ How to manage sprites/animations in a game
		3/ Enhance CGameObject with sprite animation
================================================================ */

#include <windows.h>
#include <d3d9.h>
#include <d3dx9.h>



#include "debug.h"
#include "Game.h"
#include "GameObject.h"
#include "Textures.h"

#include "Mario.h"
#include "Misc.h"
#include "Enemy.h"

#include <iostream>
#include <fstream>

#include <vector>

using namespace std;

#define WINDOW_CLASS_NAME L"SampleWindow"
#define MAIN_WINDOW_TITLE L"02 - Sprite animation - 16521125"

#define BACKGROUND_COLOR D3DCOLOR_XRGB(200, 200, 255)
#define SCREEN_WIDTH 320
#define SCREEN_HEIGHT 240

#define MAX_FRAME_RATE 60

#define ID_TEX_MARIO 0
#define ID_TEX_ENEMY 10
#define ID_TEX_MISC 20


CGame *game;
CMario *mario;
CMisc *misc;
CEnemy *enemy;
vector<CGameObject*> objects;


LRESULT CALLBACK WinProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message) {
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}

	return 0;
}

/*
	Load all game resources 
	In this example: load textures, sprites, animations and mario object
*/
void LoadResources()
{
	CTextures * textures = CTextures::GetInstance();

	textures->Add(ID_TEX_MARIO, L"textures\\mario.png",D3DCOLOR_XRGB(176, 224, 248));
	textures->Add(ID_TEX_ENEMY, L"textures\\enemies.png", D3DCOLOR_XRGB(156, 219, 239));
	textures->Add(ID_TEX_MISC, L"textures\\misc.png", D3DCOLOR_XRGB(156, 219, 239));


	CSprites * sprites = CSprites::GetInstance();
	CAnimations * animations = CAnimations::GetInstance();
	
	LPDIRECT3DTEXTURE9 texMario = textures->Get(ID_TEX_MARIO);
	LPDIRECT3DTEXTURE9 texMisc = textures->Get(ID_TEX_MISC);
	LPDIRECT3DTEXTURE9 texEnemy = textures->Get(ID_TEX_ENEMY);
	// readline => id, left, top, right 
	int ID[255];
	int i = 0;
	ifstream fileInput(L"textures\\file.txt");
	while (!fileInput.eof())
	{
		int left;
		int top;
		int right;
		int bottom;
		int tex;
		fileInput >> ID[i] >> left >> top >> right >> bottom >> tex;	
		switch (tex)
		{
			case 1:
			{
				sprites->Add(ID[i], left, top, right, bottom, texMario);
				break;
			}
			case 2:
			{
				sprites->Add(ID[i], left, top, right, bottom, texMisc);
				break;
			}
			case 3:
				sprites->Add(ID[i], left, top, right, bottom, texEnemy);
				break;
		}
		i += 1;
	}

	fileInput.close();	


	LPANIMATION ani;

	ani = new CAnimation(100);
	ani->Add(ID[0]);
	ani->Add(ID[1]);
	ani->Add(ID[2]);
	animations->Add(500, ani);

	ani = new CAnimation(100);
	ani->Add(ID[3]);
	ani->Add(ID[4]);
	ani->Add(ID[5]);
	animations->Add(501, ani);

	
	ani = new CAnimation(50);
	ani->Add(ID[6]);
	ani->Add(ID[7]);
	ani->Add(ID[8]);
	ani->Add(ID[9]);
	animations->Add(510, ani);
	
	ani = new CAnimation(50);
	ani->Add(ID[10]);
	ani->Add(ID[11]);
	ani->Add(ID[12]);
	ani->Add(ID[13]);
	animations->Add(511, ani);

	ani = new CAnimation(100);
	ani->Add(ID[14]);
	ani->Add(ID[15]);
	animations->Add(520, ani);

	ani = new CAnimation(100);
	ani->Add(ID[14]);
	ani->Add(ID[15]);
	animations->Add(521, ani);

	
	mario = new CMario();
	mario->AddAnimation(500);
	mario->AddAnimation(501);
	//mario->AddAnimation(510);

	misc = new CMisc();
	misc->AddAnimation(510);
	misc->AddAnimation(511);

	enemy = new CEnemy();
	enemy->AddAnimation(520);
	enemy->AddAnimation(521);

	mario->SetPosition(10.0f, 100.0f);
	objects.push_back(mario);

	misc->SetPosition(0, 0);
	objects.push_back(misc);

	enemy->SetPosition(5.0f, 50.0f);
	objects.push_back(enemy);

}

/*
	Update world status for this frame
	dt: time period between beginning of last frame and beginning of this frame
*/
void Update(DWORD dt)
{
	for (int i = 0; i < objects.size(); i++)
		objects[i]->Update(dt);
	
}

/*
	Render a frame 
*/
void Render()
{
	LPDIRECT3DDEVICE9 d3ddv = game->GetDirect3DDevice();
	LPDIRECT3DSURFACE9 bb = game->GetBackBuffer();
	LPD3DXSPRITE spriteHandler = game->GetSpriteHandler();

	if (d3ddv->BeginScene())
	{
		// Clear back buffer with a color
		d3ddv->ColorFill(bb, NULL, BACKGROUND_COLOR);

		spriteHandler->Begin(D3DXSPRITE_ALPHABLEND);

		for (int i = 0; i < objects.size(); i++)
			objects[i]->Render();
		//
		// TEST SPRITE DRAW
		//

		/*
		CTextures *textures = CTextures::GetInstance();

		D3DXVECTOR3 p(20, 20, 0);
		RECT r;
		r.left = 274;
		r.top = 234;
		r.right = 292;
		r.bottom = 264;
		spriteHandler->Draw(textures->Get(ID_TEX_MARIO), &r, NULL, &p, D3DCOLOR_XRGB(255, 255, 255));
		*/

		spriteHandler->End();
		d3ddv->EndScene();
	}

	// Display back buffer content to the screen
	d3ddv->Present(NULL, NULL, NULL, NULL);
}

HWND CreateGameWindow(HINSTANCE hInstance, int nCmdShow, int ScreenWidth, int ScreenHeight)
{
	WNDCLASSEX wc;
	wc.cbSize = sizeof(WNDCLASSEX);

	wc.style = CS_HREDRAW | CS_VREDRAW;
	wc.hInstance = hInstance;

	wc.lpfnWndProc = (WNDPROC)WinProc;
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.hIcon = NULL;
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	wc.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
	wc.lpszMenuName = NULL;
	wc.lpszClassName = WINDOW_CLASS_NAME;
	wc.hIconSm = NULL;

	RegisterClassEx(&wc);

	HWND hWnd =
		CreateWindow(
			WINDOW_CLASS_NAME,
			MAIN_WINDOW_TITLE,
			WS_OVERLAPPEDWINDOW, // WS_EX_TOPMOST | WS_VISIBLE | WS_POPUP,
			CW_USEDEFAULT,
			CW_USEDEFAULT,
			ScreenWidth,
			ScreenHeight,
			NULL,
			NULL,
			hInstance,
			NULL);

	if (!hWnd) 
	{
		OutputDebugString(L"[ERROR] CreateWindow failed");
		DWORD ErrCode = GetLastError();
		return FALSE;
	}

	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);

	return hWnd;
}

int Run()
{
	MSG msg;
	int done = 0;
	DWORD frameStart = GetTickCount();
	DWORD tickPerFrame = 1000 / MAX_FRAME_RATE;

	while (!done)
	{
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			if (msg.message == WM_QUIT) done = 1;

			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}

		DWORD now = GetTickCount();

		// dt: the time between (beginning of last frame) and now
		// this frame: the frame we are about to render
		DWORD dt = now - frameStart;

		if (dt >= tickPerFrame)
		{
			frameStart = now;
			Update(dt);
			Render();
		}
		else
			Sleep(tickPerFrame - dt);	
	}

	return 1;
}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	HWND hWnd = CreateGameWindow(hInstance, nCmdShow, SCREEN_WIDTH, SCREEN_HEIGHT);

	game = CGame::GetInstance();
	game->Init(hWnd);

	LoadResources();
	Run();

	return 0;
}