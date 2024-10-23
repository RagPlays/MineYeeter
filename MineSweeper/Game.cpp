#include "pch.h"
#include "Game.h"

//Basic game functions
#pragma region gameFunctions											
void Start()
{
	for (int idx{}; idx < NrGameModeTypes; ++idx)
	{
		g_BestTimes[idx] = -1;
	}

	InitGameStart();
	InitTextures();
	InitCells();
}

void Draw()
{
	ClearBackground(g_BackGroundC);

	DrawGame();
}

void Update(float elapsedSec, bool& quit)
{
	UpdateGame(elapsedSec, quit);
}

void End()
{
	delete[] g_Cells;
	g_Cells = nullptr;

	utils::DeleteTexture(g_EasyPlayTexture);
	utils::DeleteTexture(g_UIEasyTexture);
	utils::DeleteTexture(g_MediumPlayTexture);
	utils::DeleteTexture(g_UIMediumTexture);
	utils::DeleteTexture(g_HardPlayTexture);
	utils::DeleteTexture(g_UIHardTexture);
	utils::DeleteTexture(g_ExitTexture);
	utils::DeleteTexture(g_ClockTexture);
	utils::DeleteTexture(g_BestTexture);
	utils::DeleteTexture(g_ResetTexture);
	utils::DeleteTexture(g_WinTexture);

	for (int idx{}; idx < g_NrOfTileTextures; ++idx)
	{
		utils::DeleteTexture(g_TileTextures[idx]);
	}

	for (int idx{}; idx < g_NrOfEndTextures; ++idx)
	{
		utils::DeleteTexture(g_BoomTextures[idx]);
	}

	for (int idx{}; idx < g_NrOfNumbers; ++idx)
	{
		utils::DeleteTexture(g_NumberTextures[idx]);
	}
}

#pragma endregion gameFunctions

//Keyboard and mouse input handling
#pragma region inputHandling
void OnKeyDownEvent(SDL_Keycode key)
{
	//switch (key)
	//{
	//case SDLK_LEFT:
	//	//std::cout << "Left arrow key pressed\n";
	//	break;
	//case SDLK_RIGHT:
	//	//std::cout << "Right arrow key pressed\n";
	//	break;
	//case SDLK_UP:
	//	//std::cout << "Right arrow key pressed\n";
	//	break;
	//case SDLK_DOWN:
	//	//std::cout << "Right arrow key pressed\n";
	//	break;
	//}
}

void OnKeyUpEvent(SDL_Keycode key)
{
	switch (key)
	{
	case SDLK_ESCAPE:
		g_Dead = false;
		g_GameState = GameState::startmenu;
		break;
	case SDLK_i:
		OutputInfo();
		break;
	/*case SDLK_r:
		ResetStats();
		break;*/
	default:
		break;
	}
}

void OnMouseMotionEvent(const SDL_MouseMotionEvent& e)
{
	g_MousePos = Point2f{ float( e.x ), float( g_WindowHeight - e.y ) };
}

void OnMouseDownEvent(const SDL_MouseButtonEvent& e)
{

}

void OnMouseUpEvent(const SDL_MouseButtonEvent& e)
{
	switch (e.button)
	{
	case SDL_BUTTON_LEFT:
	{
		UpdateButtonPresses();
		break;
	}
	case SDL_BUTTON_RIGHT:
		UpdateRightButtonPresses();
		break;
	default:
		break;
	}
}

#pragma endregion inputHandling

#pragma region ownDefinitions
//-----------------------------------------------------
//////////  Funtions  /////////////////////////////////
//-----------------------------------------------------
//
//////////////////////  Other  /////////////////////////
void Reset()
{
	if (!g_Dead)
	{
		if (g_GameChoice == GameChoice::easy)
		{
			//std::cout << "GameChoise:: easy\n";
			if (g_BestTimes[0] == -1 || g_GameTime < g_BestTimes[0])
			{
				g_BestTimes[0] = int(std::round(g_GameTime));
			}
		}
		else if (g_GameChoice == GameChoice::medium)
		{
			//std::cout << "GameChoise:: medium\n";
			if (g_BestTimes[1] == -1 || g_GameTime < g_BestTimes[1])
			{
				g_BestTimes[1] = int(std::round(g_GameTime));
			}
		}
		else if (g_GameChoice == GameChoice::hard)
		{
			//std::cout << "GameChoise:: hard\n";
			if (g_BestTimes[2] == -1 || g_GameTime < g_BestTimes[2])
			{
				g_BestTimes[2] = int(std::round(g_GameTime));
			}
		}
		
		SaveToMorrog();
		//std::cout << g_GameTime << "\n";
	}
	g_GameState = GameState::startmenu;
	g_Dead = false;
	g_GameChoice = GameChoice::none;
}

void ResetStats()
{
	// Change ingame
	for (int idx{}; idx < NrGameModeTypes; ++idx)
	{
		g_BestTimes[idx] = -1;
	}

	// Save the changes
	SaveToMorrog();
}

void OutputInfo()
{
	std::cout << "Hello! I am Maurice and also the maker of this game.\n";
	std::cout << "This game is created to learn more about c++.\n\n";

	std::cout << "I have created the game 'MineSweeper', this is a game where you need to break \n";
	std::cout << "all the tiles except where there is a bom. Around the tilemap you find numbers, these numbers indicate\n";
	std::cout << "how many bombs there are around that specific tile. I made 3 differend game difficulties, \n";
	std::cout << "by every difficultie you can vieuw your best time in the startscreen.\n\n";

	std::cout << "Enjoy the game!\n";
	std::cout << "Greetings Maurice / Morrog to my friends\n\n\n\n";
}

void LoadFromMorrog()
{
	std::ifstream in_file;
	in_file.open("Saves/save.morrog");

	if (in_file.is_open())
	{
		//basics
		in_file >> g_BestTimes[0] >> g_BestTimes[1] >> g_BestTimes[2];
	}
	else
	{
		std::cout << "ERROR::GAME_CPP::COULD_NOT_OPEN_TO_LOAD\n";
	}
}

void SaveToMorrog()
{
	std::ofstream out_file;
	out_file.open("Saves/save.morrog");

	if (out_file.is_open())
	{
		//hier wordt alles gesaved..
		out_file
			<< std::round(g_BestTimes[0]) << "\n"
			<< std::round(g_BestTimes[1]) << "\n"
			<< std::round(g_BestTimes[2]) << "\n";
	}
	else
	{
		std::cout << "ERROR::GAME_CPP::COULD_NOT_OPEN_TO_SAVE\n";
	}
}

void PrintAddBombValues(const int idx, const int columnIdx, const int rowIdx)
{
	std::cout << "Value added on index: " << idx << " with columnIdx: " << columnIdx << " and rowIdx: " << rowIdx << "\n";
}

void ShowTiles()
{
	for (int idx{}; idx < g_CellCount; ++idx)
	{
		g_Cells[idx].broken = true;
	}
}

bool CheckWin()
{
	for (int idx{}; idx < g_CellCount; ++idx)
	{
		if (g_Cells[idx].broken == false)
		{
			if (g_Cells[idx].bomb == false)
			{
				return false;
			}
		}
	}
	g_Dead = false;
	return true;
}

void AddBombValues(const int rowIdx, const int columnIdx)
{
	int idx{};
	idx = (columnIdx - 1) + rowIdx * int(sqrt(g_CellCount));
	if (idx >= 0 && idx <= g_CellCount)
	{
		//PrintAddBombValues(idx, columnIdx - 1, rowIdx);
		if (columnIdx != 0)
		{
			++g_Cells[idx].bombValue;
		}
	}
	idx = (columnIdx - 1) + (rowIdx - 1) * int(sqrt(g_CellCount));
	if (idx >= 0 && idx <= g_CellCount)
	{
		//PrintAddBombValues(idx, columnIdx - 1, rowIdx - 1);
		if (columnIdx != 0 && rowIdx != 0)
		{
			++g_Cells[idx].bombValue;
		}
	}
	idx = (columnIdx - 1) + (rowIdx + 1) * int(sqrt(g_CellCount));
	if (idx >= 0 && idx <= g_CellCount)
	{
		//PrintAddBombValues(idx, columnIdx - 1, rowIdx + 1);
		if (columnIdx != 0 && rowIdx != int(sqrt(g_CellCount)) - 1)
		{
			++g_Cells[idx].bombValue;
		}
	}
	idx = (columnIdx) + (rowIdx + 1) * int(sqrt(g_CellCount));
	if (idx >= 0 && idx <= g_CellCount)
	{
		//PrintAddBombValues(idx, columnIdx, rowIdx + 1);
		if (rowIdx != int(sqrt(g_CellCount)) - 1)
		{
			++g_Cells[idx].bombValue;
		}
	}
	idx = (columnIdx) + (rowIdx - 1) * int(sqrt(g_CellCount));
	if (idx >= 0 && idx <= g_CellCount)
	{
		//PrintAddBombValues(idx, columnIdx, rowIdx - 1);
		if (rowIdx != 0)
		{
			++g_Cells[idx].bombValue;
		}
	}
	idx = (columnIdx + 1) + (rowIdx - 1) * int(sqrt(g_CellCount));
	if (idx >= 0 && idx <= g_CellCount)
	{
		//PrintAddBombValues(idx, columnIdx + 1, rowIdx - 1);
		if (columnIdx != int(sqrt(g_CellCount)) - 1 && rowIdx != 0)
		{
			++g_Cells[idx].bombValue;
		}
	}
	idx = (columnIdx + 1) + (rowIdx) * int(sqrt(g_CellCount));
	if (idx >= 0 && idx <= g_CellCount)
	{
		//PrintAddBombValues(idx, columnIdx + 1, rowIdx);
		if (columnIdx != int(sqrt(g_CellCount)) - 1)
		{
			++g_Cells[idx].bombValue;
		}
	}
	idx = (columnIdx + 1) + (rowIdx + 1) * int(sqrt(g_CellCount));
	if (idx >= 0 && idx <= g_CellCount)
	{
		//PrintAddBombValues(idx, columnIdx + 1, rowIdx + 1);
		if (columnIdx != int(sqrt(g_CellCount)) - 1 && rowIdx != int(sqrt(g_CellCount)) - 1)
		{
			++g_Cells[idx].bombValue;
		}
	}
}

void BreakATile(const int idx)
{
	if (g_Cells[idx].flag)
	{
		++g_AvailableFlags;
	}
	g_Cells[idx].broken = true;
}

void BreakTiles(const int rowIdx, const int columnIdx)
{
	int idx{ columnIdx + rowIdx * int(sqrt(g_CellCount)) };

	g_Cells[idx].broken = true;

	if (g_Cells[idx].bombValue == 0)
	{
		BreakSurroundingTiles(rowIdx, columnIdx, 300);
	}
}

void BreakSurroundingTiles(const int rowIdx, const int columnIdx, const int lvl)
{
	int nrOfColums{ int(sqrt(g_CellCount))};
	int idx{ columnIdx + rowIdx * nrOfColums };

	if (columnIdx < 0 || columnIdx > nrOfColums - 1)
	{
		return;
	}
	if (rowIdx < 0 || rowIdx > nrOfColums - 1)
	{
		return;
	}
	if (lvl < 0)
	{
		return;
	}
	if (g_Cells[idx].bombValue != 0 || g_Cells[idx].bomb == true)
	{
		return;
	}
	
	// 1
	idx = (columnIdx - 1) + (rowIdx + 1) * nrOfColums;
	if (idx >= 0 && idx <= g_CellCount && g_Cells[idx].broken == false && g_Cells[idx].bomb == false)
	{
		if (columnIdx != 0 && rowIdx != nrOfColums - 1)
		{
			BreakATile(idx);
			BreakSurroundingTiles(rowIdx + 1, columnIdx - 1, lvl - 1);
		}
	}

	// 2
	idx = columnIdx + (rowIdx + 1) * nrOfColums;
	if (idx >= 0 && idx <= g_CellCount && g_Cells[idx].broken == false && g_Cells[idx].bomb == false)
	{
		if (rowIdx != nrOfColums - 1)
		{
			BreakATile(idx);
			BreakSurroundingTiles(rowIdx + 1, columnIdx, lvl - 1);
		}
	}

	// 3
	idx = (columnIdx + 1) + (rowIdx + 1) * nrOfColums;
	if (idx >= 0 && idx <= g_CellCount && g_Cells[idx].broken == false && g_Cells[idx].bomb == false)
	{
		if (columnIdx != (nrOfColums - 1) && rowIdx != nrOfColums - 1)
		{
			BreakATile(idx);
			BreakSurroundingTiles(rowIdx + 1, columnIdx + 1, lvl - 1);
		}
	}

	// 4
	idx = (columnIdx - 1) + rowIdx * nrOfColums;
	if (idx >= 0 && idx <= g_CellCount && g_Cells[idx].broken == false && g_Cells[idx].bomb == false)
	{
		if (columnIdx != 0)
		{
			BreakATile(idx);
			BreakSurroundingTiles(rowIdx, columnIdx - 1, lvl - 1);
		}
	}

	// 5
	idx = (columnIdx + 1) + rowIdx * nrOfColums;
	if (idx >= 0 && idx <= g_CellCount && g_Cells[idx].broken == false && g_Cells[idx].bomb == false)
	{
		if (columnIdx != nrOfColums - 1)
		{
			BreakATile(idx);
			BreakSurroundingTiles(rowIdx, columnIdx + 1, lvl - 1);
		}
	}

	// 6
	idx = (columnIdx - 1) + (rowIdx - 1) * nrOfColums;
	if (idx >= 0 && idx <= g_CellCount && g_Cells[idx].broken == false && g_Cells[idx].bomb == false)
	{
		if (columnIdx != 0 && rowIdx != 0)
		{
			BreakATile(idx);
			BreakSurroundingTiles(rowIdx - 1, columnIdx - 1, lvl - 1);
		}
	}

	// 7
	idx = columnIdx + (rowIdx - 1) * nrOfColums;
	if (idx >= 0 && idx <= g_CellCount && g_Cells[idx].broken == false && g_Cells[idx].bomb == false)
	{
		if (rowIdx != 0)
		{
			BreakATile(idx);
			BreakSurroundingTiles(rowIdx - 1, columnIdx, lvl - 1);
		}
	}

	// 8
	idx = (columnIdx + 1) + (rowIdx - 1) * nrOfColums;
	if (idx >= 0 && idx <= g_CellCount && g_Cells[idx].broken == false && g_Cells[idx].bomb == false)
	{
		if (columnIdx != (nrOfColums - 1) && rowIdx != 0)
		{
			BreakATile(idx);
			BreakSurroundingTiles(rowIdx - 1, columnIdx + 1, lvl - 1);
		}
	}
}

bool GetClockTime(float& runtime, const float elapsedSec, const float maxTime)
{
	if (runtime >= maxTime)
	{
		runtime = 0.f;
		return true;
	}
	runtime += elapsedSec;
	return false;
}

//////////////////////  Init  /////////////////////////
void InitGameStart()
{
	g_StartRect.height = g_WindowHeight * 0.9f;
	g_StartRect.width = g_StartRect.height;
	
	g_StartRect.left = (g_WindowWidth - g_StartRect.width) / 2.f;
	g_StartRect.bottom = (g_WindowHeight - g_StartRect.height) / 2.f;

	g_TileSize = g_StartRect.height / int(sqrt(g_CellCount));
}

void InitTextures()
{
	// Texts
	int fontSize{ int(g_WindowHeight * 0.1f) };
	const std::string pathName{ "Resources/Fonts/BRITANIC.TTF" };
	// No error messeges because already build in error messege ///////////////////
	utils::TextureFromString("Easy", pathName, fontSize , g_Black , g_EasyPlayTexture);
	utils::TextureFromString("Medium", pathName, fontSize , g_Black , g_MediumPlayTexture);
	utils::TextureFromString("Hard", pathName, fontSize , g_Black , g_HardPlayTexture);
	utils::TextureFromString("Exit", pathName, fontSize - 15, g_Black, g_ExitTexture);

	// Bom and bombNumbers and ui
	fontSize = int(g_WindowHeight * 0.05f);
	utils::TextureFromFile("Resources/Pictures/bomb.png", g_TileTextures[0]);
	utils::TextureFromString("1", pathName, fontSize, g_NumberBlue, g_TileTextures[1]);
	utils::TextureFromString("2", pathName, fontSize, g_NumberGreen, g_TileTextures[2]);
	utils::TextureFromString("3", pathName, fontSize, g_NumberOrange, g_TileTextures[3]);
	utils::TextureFromString("4", pathName, fontSize, g_NumberRed, g_TileTextures[4]);
	utils::TextureFromString("5", pathName, fontSize, g_Margenta, g_TileTextures[5]);
	utils::TextureFromString("6", pathName, fontSize, g_Black, g_TileTextures[6]);
	utils::TextureFromFile("Resources/Pictures/flag.png", g_TileTextures[7]);
	utils::TextureFromString("Reset", pathName, fontSize, g_Black, g_ResetTexture);
	utils::TextureFromFile("Resources/Pictures/clock.png", g_ClockTexture);

	// Boom textures
	utils::TextureFromString("BOOM!", pathName, fontSize * 6, g_Black, g_BoomTextures[0]);
	utils::TextureFromString("BOOM!", pathName, fontSize * 6, g_Red, g_BoomTextures[1]);
	utils::TextureFromString("BOOM!", pathName, fontSize * 6, g_Orange, g_BoomTextures[2]);
	utils::TextureFromString("BOOM!", pathName, fontSize * 6, g_White, g_BoomTextures[3]);
	utils::TextureFromString("Won!", pathName, fontSize * 6, g_Black, g_WinTexture);

	// Numbers
	for (int idx{}; idx < g_NrOfNumbers; ++idx)
	{
		std::string number{ std::to_string(idx) };
		utils::TextureFromString(number, pathName, fontSize + 5, g_White, g_NumberTextures[idx]);
	}

	utils::TextureFromString("Best", pathName, fontSize + 20, g_White, g_BestTexture);
	utils::TextureFromString("Easy", pathName, fontSize + 5, g_White, g_UIEasyTexture);
	utils::TextureFromString("Medium", pathName, fontSize + 5, g_White, g_UIMediumTexture);
	utils::TextureFromString("Hard", pathName, fontSize + 5, g_White, g_UIHardTexture);
}

void InitCells()
{
	// Set Sizes
	Color4f drawColor{};
	Point2f drawPoint{};

	for (int rowidx{}; rowidx < int(sqrt(g_CellCount)); ++rowidx)
	{
		for (int columnidx{}; columnidx < int(sqrt(g_CellCount)); ++columnidx)
		{
			int idx{ columnidx + rowidx * int(sqrt(g_CellCount)) };
			drawPoint = Point2f{ g_StartRect.left + rowidx * g_TileSize, g_StartRect.bottom + columnidx * g_TileSize };
			g_Cells[idx].drawPoint = drawPoint;
			g_Cells[idx].broken = false;
			g_Cells[idx].flag = false;
		}
	}

	// Init boms
	for (int idx{}; idx < g_MaxBoms; ++idx)
	{
		int g_MaxValue{ int(sqrt(g_CellCount)) };
		int rowIdx{ rand() % (g_MaxValue - 1) + 1 };
		int columnIdx{ rand() % g_MaxValue };
		int CellIdx{ columnIdx + rowIdx * int(sqrt(g_CellCount)) };

		while (g_Cells[CellIdx].bomb)
		{
			rowIdx = rand() % g_MaxValue;
			columnIdx = rand() % g_MaxValue;
			CellIdx = columnIdx + rowIdx * int(sqrt(g_CellCount));
		}
		g_Cells[CellIdx].bomb = true;
	}

	// Init Numbers
	for (int rowIdx{}; rowIdx < int(sqrt(g_CellCount)); ++rowIdx)
	{
		for (int columnIdx{}; columnIdx < int(sqrt(g_CellCount)); ++columnIdx)
		{
			int idx{ columnIdx + rowIdx * int(sqrt(g_CellCount)) };
			if (g_Cells[idx].bomb)
			{
				// set ++bombvalue to all surrounding tiles of the bomb
				AddBombValues(rowIdx, columnIdx);
			}
		}
	}
	if (g_CellCount != 0)
	{
		do
		{
			g_HighLightIdx = rand() % g_CellCount;
		} while (g_Cells[g_HighLightIdx].bomb == true || g_Cells[g_HighLightIdx].bombValue != 0);
	}
}

/////////////////////  Update  ////////////////////////
bool UpdateQuit(bool& quit)
{
	if (g_Quit)
	{
		quit = true;
		return true;
	}
	return false;
}

void UpdateButtonPresses()
{
	if (g_GameState == GameState::startmenu)
	{
		g_GameTime = 0.f;
		if (utils::IsPointInRect(g_MousePos, g_EasyPlayButton))
		{
			//easy arr
			g_GameState = GameState::game;
			g_GameChoice = GameChoice::easy;
			g_CellCount = int(pow(7.0, 2.0));
			g_MaxBoms = 5 + (rand() % 7);  // 9 
			g_AvailableFlags = g_MaxBoms;
			delete[] g_Cells;
			g_Cells = nullptr;
			g_Cells = new Cell[g_CellCount]{};
			InitGameStart();
			InitCells();
			
		}
		else if (utils::IsPointInRect(g_MousePos, g_MediumPlayButton))
		{
			//medium arr
			g_GameState = GameState::game;
			g_GameChoice = GameChoice::medium;
			g_CellCount = int(pow(11.0, 2.0));
			g_MaxBoms = 11 + (rand() % 10);  // 17
			g_AvailableFlags = g_MaxBoms;
			delete[] g_Cells;
			g_Cells = nullptr;
			g_Cells = new Cell[g_CellCount]{};
			InitGameStart();
			InitCells();
		}
		else if (utils::IsPointInRect(g_MousePos, g_HardPlayButton))
		{
			//hard arr
			g_GameState = GameState::game;
			g_GameChoice = GameChoice::hard;
			g_CellCount = int(pow(15.0, 2.0));
			g_MaxBoms = 18 + (rand() % 15);  // 26
			g_AvailableFlags = g_MaxBoms;
			delete[] g_Cells;
			g_Cells = nullptr;
			g_Cells = new Cell[g_CellCount]{};
			InitGameStart();
			InitCells();
		}
		else if (utils::IsPointInRect(g_MousePos, g_ExitButton))
		{
			g_Quit = true;
		}
		else if (utils::IsPointInRect(g_MousePos, g_ResetButton))
		{
			ResetStats();
		}
	}
	else if (g_GameState == GameState::game)
	{
		for (int rowIdx{}; rowIdx < int(sqrt(g_CellCount)); ++rowIdx)
		{
			for (int columnIdx{}; columnIdx < int(sqrt(g_CellCount)); ++columnIdx)
			{
				int idx{ columnIdx + rowIdx * int(sqrt(g_CellCount)) };

				if (g_Cells[idx].flag == false)
				{
					if (utils::IsPointInRect(g_MousePos, Rectf(g_Cells[idx].drawPoint, g_TileSize, g_TileSize)) && g_Cells[idx].broken == false)
					{
						BreakTiles(rowIdx, columnIdx);
						if (g_Cells[idx].bomb)
						{
							g_GameState = GameState::end;
							g_Dead = true;
						}
						if (CheckWin())
						{
							g_GameState = GameState::end;
						}
					}
				}
			}
		}
	}
}

void UpdateRightButtonPresses()
{
	if (g_GameState == GameState::game)
	{
		for (int rowIdx{}; rowIdx < int(sqrt(g_CellCount)); ++rowIdx)
		{
			for (int columnIdx{}; columnIdx < int(sqrt(g_CellCount)); ++columnIdx)
			{
				int idx{ columnIdx + rowIdx * int(sqrt(g_CellCount)) };

				if (utils::IsPointInRect(g_MousePos, Rectf(g_Cells[idx].drawPoint, g_TileSize, g_TileSize)))
				{
					if (g_Cells[idx].flag)
					{
						g_Cells[idx].flag = false;
						++g_AvailableFlags;
					}
					else
					{
						//std::cout << g_AvailableFlags << "\n";
						if (g_AvailableFlags)
						{
							--g_AvailableFlags;
							g_Cells[idx].flag = true;
						}
					}
				}
			}
		}
	}
}

void UpdateEndTimings(const float elapsedSec)
{
	if (GetClockTime(g_EndClock, elapsedSec, 0.1f))
	{
		++g_BoomTextureIdx;
		g_BoomTextureIdx %= g_NrOfEndTextures;
	}
}

void UpdateGame(const float elapsedSec, bool& quit)
{
	if (UpdateQuit(quit))
	{
		return;
	}
	else if (g_GameState == GameState::startmenu)
	{
		LoadFromMorrog();
	}
	else if (g_GameState == GameState::game)
	{
		g_GameTime += elapsedSec;
		//std::cout << std::round(g_GameTime) << "\n";
	}
	else if (g_GameState == GameState::end)
	{
		ShowTiles();
		UpdateEndTimings(elapsedSec);

		if (GetClockTime(g_Runtime, elapsedSec, 3))
		{
			Reset();
		}
	}
}

//////////////////////  Draw  /////////////////////////
void DrawButton(const Rectf& drawRect, const Texture& texture, const Color4f& color)
{
	// Rect & circles
	utils::SetColor(color);
	utils::FillRect(drawRect);
	utils::SetColor(g_Black);
	utils::DrawRect(drawRect, 4.f);

	// Texture
	Point2f texturePoint{ drawRect.left + (drawRect.width - texture.width) / 2.f, drawRect.bottom + (drawRect.height - texture.height) / 2.f };
	utils::DrawTexture(texture, texturePoint);

	if (utils::IsPointInRect(g_MousePos, drawRect))
	{
		utils::SetColor(g_HoverButtonC);
		utils::FillRect(drawRect);
		utils::SetColor(g_Black);
		utils::DrawRect(drawRect, 4.f);
	}
}

void DrawStartMenu()
{
	// Play Buttons
	DrawButton(g_EasyPlayButton, g_EasyPlayTexture, g_ButtonC);
	DrawButton(g_MediumPlayButton, g_MediumPlayTexture, g_ButtonC);
	DrawButton(g_HardPlayButton, g_HardPlayTexture, g_ButtonC);

	// Exit
	DrawButton(g_ExitButton, g_ExitTexture, g_ExitButtonC);

	// DrawStats
	DrawStats();
}

void DrawStats()
{
	// Base
	Rectf statsRect{};
	statsRect.height = g_WindowHeight * 0.675f;
	statsRect.bottom = g_HardPlayButton.bottom;

	statsRect.width = g_StartRect.width / 2.f;
	statsRect.left = (g_HardPlayButton.left - statsRect.width) / 2.f;

	utils::SetColor(g_StatsC);
	utils::FillRect(statsRect);
	utils::SetColor(g_Black);
	utils::DrawRect(statsRect, 4.f);

	// Time
	float offsetX{ g_WindowHeight * 0.08f };
	float offsetY{ g_WindowHeight * 0.09f };
	float destWidth{ statsRect.height * 0.22f };
	float destHeight{ destWidth };

	Point2f drawPoint{ statsRect.left + offsetX, statsRect.bottom + statsRect.height - (offsetY / 2.f) - g_BestTexture.height };
	utils::DrawTexture(g_BestTexture, drawPoint);

	drawPoint.x += g_BestTexture.width + offsetX / 2.f;
	drawPoint.y -= destWidth / 3.f;

	Rectf destRect{ drawPoint, destWidth, destHeight };
	utils::DrawTexture(g_ClockTexture, destRect);

	//DrawNumbers
	float numberOffset{ g_NumberTextures[0].width * 1.2f };
	
	DrawTexture(g_UIEasyTexture, Point2f{ statsRect.left + offsetX / 2.f, drawPoint.y - offsetY});
	drawPoint.x = statsRect.left + statsRect.width /2.f + offsetX;
	DrawBestTime(drawPoint, 0);

	DrawTexture(g_UIMediumTexture, Point2f{ statsRect.left + offsetX / 2.f, drawPoint.y - offsetY });
	drawPoint.x = statsRect.left + statsRect.width / 2.f + offsetX;
	DrawBestTime(drawPoint, 1);

	DrawTexture(g_UIHardTexture, Point2f{ statsRect.left + offsetX / 2.f, drawPoint.y - offsetY });
	drawPoint.x = statsRect.left + statsRect.width / 2.f + offsetX;
	DrawBestTime(drawPoint, 2);


	const float resetWidth{g_WindowWidth * 0.18f };
	const float resetHeight{g_WindowHeight *  0.11f };
	const Rectf resetButton{ statsRect.left + (statsRect.width / 2.f) - resetWidth / 2.f, statsRect.bottom + offsetY / 2.f , resetWidth, resetHeight };
	g_ResetButton = resetButton;
	DrawButton(g_ResetButton, g_ResetTexture, g_ButtonC);
}

void DrawTile(const Point2f& drawPoint, const Color4f& color)
{
	utils::SetColor(color);
	utils::FillRect(drawPoint, g_TileSize, g_TileSize);
}

void DrawTiles()
{
	Rectf destRect{0.f, 0.f, g_TileSize, g_TileSize};
	Color4f drawColor{};
	for (int idx{}; idx < g_CellCount; ++idx)
	{
		destRect.left = g_Cells[idx].drawPoint.x;
		destRect.bottom = g_Cells[idx].drawPoint.y;

		if (!g_Cells[idx].broken)
		{
			if (idx == g_HighLightIdx)
			{
				DrawTile(g_Cells[idx].drawPoint, g_HighLightCube);
			}
			else
			{
				(idx % 2) ? drawColor = g_LightGridTileC : drawColor = g_DarkGridTileC;
				DrawTile(g_Cells[idx].drawPoint, drawColor);
			}
			if (utils::IsPointInRect(g_MousePos, Rectf{ g_Cells[idx].drawPoint, g_TileSize, g_TileSize }))
			{
				utils::SetColor(g_HoverTileC);
				utils::FillRect(g_Cells[idx].drawPoint, g_TileSize, g_TileSize);
			}
			if (g_Cells[idx].flag)
			{
				DrawTexture(g_TileTextures[7], destRect);
			}
		}
		else
		{
			// DrawTiles
			(idx % 2) ? drawColor = g_LightBrokenTileC : drawColor = g_DarkBrokenTileC;
			DrawTile(g_Cells[idx].drawPoint, drawColor);
			// draw ON tiles
			// Boms
			if (g_Cells[idx].bomb)
			{
				DrawTexture(g_TileTextures[0], destRect);
			}
			else if (g_Cells[idx].bombValue != 0)
			{
				Point2f drawPoint{	g_Cells[idx].drawPoint.x + ((g_TileSize / 2.f) - (g_TileTextures[g_Cells[idx].bombValue].width / 2.f)),
									g_Cells[idx].drawPoint.y + ((g_TileSize / 2.f) - (g_TileTextures[g_Cells[idx].bombValue].height / 2.f)) };

				DrawTexture(g_TileTextures[g_Cells[idx].bombValue], drawPoint);
			}
		}
	}
	SetColor(g_Black);
	utils::DrawRect(g_StartRect, 4.f);
}

void DrawBestTime(Point2f& drawPoint, int idx)
{
	float offsetY{ g_WindowHeight * 0.1f };
	float numberOffset{ g_NumberTextures[0].width * 1.15f };
	drawPoint.y -= offsetY;
	if (g_BestTimes[idx] != -1)
	{
		for (int idex{}; idex < 3; ++idex)
		{
			int printNumber{};
			if (idex == 0)
			{
				printNumber = g_BestTimes[idx] / 100;
			}
			else if (idex == 1)
			{
				printNumber = g_BestTimes[idx] % 100;
				printNumber /= 10;
			}
			else
			{
				printNumber = g_BestTimes[idx] % 10;
			}
			utils::DrawTexture(g_NumberTextures[printNumber], drawPoint);
			drawPoint.x += numberOffset;
		}
	}
	else
	{
		utils::SetColor(g_White);
		utils::DrawLine(drawPoint, Point2f{ drawPoint.x + 3 * numberOffset, drawPoint.y + g_NumberTextures[0].height }, 4.f);
	}
}

void DrawWinScreen()
{
	Point2f drawPoint{ g_WindowWidth / 2.f - (g_WinTexture.width / 2.f),
						g_WindowHeight / 2.f - (g_WinTexture.height / 2.f) };

	utils::DrawTexture(g_WinTexture, drawPoint);
}

void DrawLoseScreen()
{
	Point2f drawPoint{	g_WindowWidth / 2.f - (g_BoomTextures[0].width / 2.f),
						g_WindowHeight / 2.f - (g_BoomTextures[0].height / 2.f)};

	utils::DrawTexture(g_BoomTextures[g_BoomTextureIdx], drawPoint);
}

void DrawGameUI()
{
	// Base
	float width{ g_StartRect.left - (g_StartRect.bottom * 2.f) };
	float height{ g_StartRect.height / 3.f };

	Rectf uiRect{ g_StartRect.bottom, g_WindowHeight - g_StartRect.bottom - height, width, height };

	utils::SetColor(g_StatsC);
	utils::FillRect(uiRect);
	utils::SetColor(g_Black);
	utils::DrawRect(uiRect, 4.f);

	///////// Time  /////////
	float offset{ g_WindowHeight * 0.02f };
	float desWidth{ uiRect.height * 0.4f };
	float desHeight{ desWidth };
	Rectf destRect{ uiRect.left + offset, uiRect.bottom + uiRect.height - desHeight - offset, desWidth, desHeight };
	utils::DrawTexture(g_ClockTexture, destRect);

	float numberOffset{ g_NumberTextures[0].width * 1.2f };
	destRect.left += numberOffset * 4.f;

	int gameTime = int(std::round(g_GameTime));
	for (int idx{}; idx < 3; ++idx)
	{
		int printNumber{};
		if (idx == 0)
		{
			printNumber = gameTime / 100;
		}
		else if (idx == 1)
		{
			printNumber = gameTime % 100;
			printNumber /= 10;
		}
		else
		{
			printNumber = gameTime % 10;
		}

		Point2f drawPoint{ destRect.left, destRect.bottom + (destRect.height / 2.f) - g_NumberTextures[printNumber].height / 1.9f };
		utils::DrawTexture(g_NumberTextures[printNumber], drawPoint);
		destRect.left += numberOffset;
	}

	////  Flags  ////
	destRect.left = uiRect.left + offset;
	destRect.bottom -= offset * 6.f;
	DrawTexture(g_TileTextures[7], destRect);

	destRect.left += numberOffset * 4.f;

	for (int idx{}; idx < 2; ++idx)
	{
		int printNumber{};
		if (idx == 0)
		{
			printNumber = g_AvailableFlags % 100;
			printNumber /= 10;
		}
		else
		{
			printNumber = g_AvailableFlags % 10;
		}
		Point2f drawPoint{ destRect.left, destRect.bottom + (destRect.height / 2.f) - g_NumberTextures[printNumber].height / 1.9f };
		utils::DrawTexture(g_NumberTextures[printNumber], drawPoint);
		destRect.left += numberOffset;
	}
}

void DrawGame()
{
	if (g_GameState == GameState::startmenu)
	{
		DrawStartMenu();
	}
	else if (g_GameState != GameState::startmenu)
	{
		DrawTiles();
		DrawGameUI();
		if (g_GameState == GameState::end)
		{
			if (g_Dead)
			{
				DrawLoseScreen();
			}
			else
			{
				DrawWinScreen();
			}
		}
	}
}

#pragma endregion ownDefinitions