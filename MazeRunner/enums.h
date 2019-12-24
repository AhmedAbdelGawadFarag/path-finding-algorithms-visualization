#pragma once
enum class MainMenuElementName
{
	Generate, Solve, Files, Save, Options, Exit
};
enum class OptionsMenuElementName
{
	Back, ScreenMode, ScreenRes, RowCount, ColumnCount, Animation
};
enum class SolveMenuElementName
{
	Back, DFS, BFS, BestFirst, Dijkstra
};
enum class MenuElement
{
	MainMenu, OptionsMenu, SolveMenu
};
enum class ScreenMode
{
	Default , FullScreen 
};
enum class Animation
{
	ON, OFF
};