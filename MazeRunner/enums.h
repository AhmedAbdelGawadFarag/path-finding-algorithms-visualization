#pragma once
enum class MainMenuElementName
{
	Generate, Files, Save, Options, Exit
};
enum class OptionsMenuElementName
{
	Back, ScreenMode, ScreenRes, RowCount, ColumnCount, Animation
};
enum class MenuElement
{
	MainMenu, OptionsMenu, FilesMenu
};
enum class ScreenMode
{
	Default , FullScreen 
};
enum class Animation
{
	ON, OFF
};