#pragma once
using namespace utils;
#pragma region gameInformation
// Set your name and group in the title here
std::string g_WindowTitle{ "MineYeeter Feat. Morrog" };

// Change the window dimensions here
float g_WindowWidth{ 1280 };
float g_WindowHeight{ 720 };
#pragma endregion gameInformation

#pragma region gameFunctions											
void Start();
void Draw();
void Update(float elapsedSec, bool& quit);
void End();
#pragma endregion gameFunctions


#pragma region inputHandling											
void OnKeyDownEvent(SDL_Keycode key);
void OnKeyUpEvent(SDL_Keycode key);
void OnMouseMotionEvent(const SDL_MouseMotionEvent& e);
void OnMouseDownEvent(const SDL_MouseButtonEvent& e);
void OnMouseUpEvent(const SDL_MouseButtonEvent& e);
#pragma endregion inputHandling


#pragma region ownDeclarations
//-----------------------------------------------------
//////////  Variables  ////////////////////////////////
//-----------------------------------------------------
//
/////////////////////  Colors  ////////////////////////
const Color4f g_White			{ 1.f, 1.f, 1.f, 1.f };
const Color4f g_Black			{ 0.f, 0.f, 0.f, 1.f };

const Color4f g_Red				{ 1.f, 0.f, 0.f, 1.f };
const Color4f g_Green			{ 0.f, 1.f, 0.f, 1.f };
const Color4f g_Blue			{ 0.f, 0.f, 1.f, 1.f };

const Color4f g_Yellow			{ 1.f, 1.f, 0.f, 1.f };
const Color4f g_Margenta		{ 1.f, 0.f, 1.f, 1.f };
const Color4f g_Cyan			{ 0.f, 1.f, 1.f, 1.f };

const Color4f g_Orange			{ 1.f, 0.5f, 0.f, 1.f };
const Color4f g_ChartreuseGreen	{ 0.5f, 1.f, 0.f, 1.f };
const Color4f g_SpringGreen		{ 0.f, 1.f, 0.5f, 1.f };
const Color4f g_Azure			{ 0.f, 0.5f, 1.f, 1.f };
const Color4f g_Violet			{ 0.5f, 0.f, 1.f, 1.f };
const Color4f g_Rose			{ 1.f, 0.f, 0.5f, 1.f };

const Color4f g_BackGroundC		{ 70.f / 255.f, 190.f / 255.f, 250.f / 255.f , 1.f};
const Color4f g_DarkGridTileC	{ 162.f / 255.f, 208.f / 255.f, 73.f / 255.f, 1.f };
const Color4f g_LightGridTileC	{ 170.f / 255.f, 220.f / 255.f, 85.f / 255.f, 1.f };
const Color4f g_DarkBrokenTileC	{ 210.f / 255.f, 180.f / 255.f, 150.f / 255.f, 1.f };
const Color4f g_LightBrokenTileC{ 228.f / 255.f, 194.f / 255.f, 159.f / 255.f, 1.f };
const Color4f g_HoverTileC		{ 185.f / 255.f, 222.f / 255.f , 119.f / 255.f , 1.f };
const Color4f g_ButtonC			{ 0.6f, 0.8f, 0.4f, 1.f };
const Color4f g_HoverButtonC	{ 1.f, 1.f, 1.f, 0.3f };
const Color4f g_ExitButtonC		{ 0.7f, 0.1f, 0.26f, 1.f };
const Color4f g_StatsC			{ 74.f / 255.f, 117.f / 255.f, 45.f / 255.f, 1.f };

const Color4f g_NumberBlue{ 25.f / 255.f, 120.f /255.f, 212.f / 255.f, 1.f };
const Color4f g_NumberGreen{ 49.f / 255.f, 147.f / 255.f, 62.f / 255.f, 1.f };
const Color4f g_NumberOrange{ 246.f / 255.f, 131.f / 255.f, 12.f / 255.f, 1.f };
const Color4f g_NumberRed{ 226.f / 255.f,  39.f / 255.f, 46.f / 255.f, 1.f };

const Color4f g_HighLightCube{ 0.8f, 1.f, 0.8f, 1.f };
 
//////////////////////  Other  ////////////////////////

//
bool g_Dead{ false };
// Mouse Pos
Point2f g_MousePos{};

// cells and startrect
Rectf g_StartRect{};
struct Cell
{
	Point2f drawPoint;
	Texture texture;
	bool bomb;
	int bombValue;
	bool broken;
	bool flag;
};
int g_HighLightIdx{};

int g_MaxBoms{};
float g_TileSize{}; // width and height
int g_CellCount{};
Cell* g_Cells{};  // Dynamic arr for controlling everything in grid
const int g_MaxBomCounts{ 21 };
int bomIdx[g_MaxBomCounts]{};

enum class GameState
{
	startmenu,
	game,
	end
};
GameState g_GameState{ GameState::startmenu };

enum class GameChoice
{
	none,
	easy,
	medium,
	hard
};
GameChoice g_GameChoice{ GameChoice::none };

// StartMenu Buttons
const float g_ButtonWidth{ g_WindowWidth * 0.25f };
const float g_ButtonHeight{ g_WindowHeight * 0.17f };
const Rectf g_EasyPlayButton{ g_WindowWidth * 0.5f - (g_ButtonWidth / 2.f), g_WindowHeight * 0.75f - (g_ButtonHeight / 2.f), g_ButtonWidth, g_ButtonHeight };
const Rectf g_MediumPlayButton{ g_WindowWidth * 0.5f - (g_ButtonWidth / 2.f), g_WindowHeight * 0.5f - (g_ButtonHeight / 2.f), g_ButtonWidth, g_ButtonHeight };
const Rectf g_HardPlayButton{ g_WindowWidth * 0.5f - (g_ButtonWidth / 2.f), g_WindowHeight * 0.25f - (g_ButtonHeight / 2.f), g_ButtonWidth, g_ButtonHeight };
const Rectf g_ExitButton{g_WindowWidth * 0.875f, g_WindowHeight * 0.86f, g_WindowWidth * 0.1f, g_WindowHeight * 0.1f };
Rectf g_ResetButton{};

Texture g_EasyPlayTexture{};
Texture g_UIEasyTexture{};
Texture g_MediumPlayTexture{};
Texture g_UIMediumTexture{};
Texture g_HardPlayTexture{};
Texture g_UIHardTexture{};
Texture g_ExitTexture{};
Texture g_ResetTexture{};

const int g_NrOfTileTextures{ 8 };
Texture	g_TileTextures[ g_NrOfTileTextures ] {};
const int g_NrOfEndTextures{ 4 };
int g_BoomTextureIdx{ 0 };
Texture g_BoomTextures[ g_NrOfEndTextures ]{};
Texture g_WinTexture{};
const int g_NrOfNumbers{ 10 };
Texture g_NumberTextures[ g_NrOfNumbers ]{};

// UI-Textures
Texture g_BestTexture{};
Texture g_ClockTexture{};

// Time
float g_Runtime{};
float g_EndClock{};
float g_ShowWorldClock{};
float g_GameTime{};

const int NrGameModeTypes{ 3 };
int g_BestTimes[ NrGameModeTypes ]{};

int g_AvailableFlags{};

// Quit
bool g_Quit{ false };
//-----------------------------------------------------
//////////  Functions  /////////////////////////////////
//-----------------------------------------------------
//
//////////////////////  Other  ////////////////////////
void Reset();
void ResetStats();
void OutputInfo();
void LoadFromMorrog();
void SaveToMorrog();
void PrintAddBombValues(const int idx, const int columnIdx, const int rowIdx);
void ShowTiles();
bool CheckWin();
void AddBombValues(const int rowIdx, const int columnIdx);
void BreakATile(const int idx);
void BreakTiles(const int rowIdx, const int columnIdx);
void BreakSurroundingTiles(const int rowIdx, const int columnIdx, const int lvl);
bool GetClockTime(float& runtime, const float elapsedSec, const float maxTime);

//////////////////////  Init  /////////////////////////
void InitGameStart();
void InitTextures();
void InitCells();

/////////////////////  Update  ////////////////////////
bool UpdateQuit(bool& quit);
void UpdateButtonPresses();
void UpdateRightButtonPresses();
void UpdateEndTimings(const float elapsedSec);
void UpdateGame(const float elapsedSec, bool& quit);

//////////////////////  Draw  /////////////////////////
void DrawButton(const Rectf& drawRect, const Texture& texture, const Color4f& color);
void DrawStartMenu();
void DrawStats();
void DrawTile(const Point2f& drawPoint, const Color4f& color);
void DrawTiles();
void DrawBestTime(Point2f& drawPoint, int idx);
void DrawWinScreen();
void DrawLoseScreen();
void DrawGameUI();
void DrawGame();
#pragma endregion ownDeclarations