class CfgPatches
{
    class JM_CF_GUI
    {
        units[]={};
        weapons[]={};
        requiredVersion=0.1;
        requiredAddons[]=
        {
			"DZ_Data"
        };
    };
};
class CfgWrapperUI
{
	class Colors
	{
		color1[] = {0.0,0.0,0.0,1.0};
		color2[] = {0.2,0.2,0.2,1.0};
		color3[] = {0.5,0.5,0.5,1.0};
		color4[] = {0.6,0.6,0.6,1.0};
		color5[] = {0.8,0.8,0.8,1.0};
	};
	class Background
	{
		alpha = 0.75;
		texture = "#(argb,8,8,3)color(1,1,1,1)";
	};
	class TitleBar
	{
		alpha = 0.3;
		texture = "#(argb,8,8,3)color(1,1,1,1)";
	};
	class GroupBox
	{
		alpha = 0.2;
	};
	class GroupBox2
	{
		alpha = 0.5;
		texture = "#(argb,8,8,3)color(1,1,1,1)";
	};
	class Button
	{
		color1[] = {0.0,0.0,0.0,0.3};
		color2[] = {0.2,0.2,0.2,0.3};
		color3[] = {0.5,0.5,0.5,0.3};
		color4[] = {0.6,0.6,0.6,0.3};
		color5[] = {0.8,0.8,0.8,0.3};
	};
	class ListBox
	{
		line = "#(argb,8,8,3)color(1,1,1,1)";
		thumb = "#(argb,8,8,3)color(1,1,1,1)";
		arrowEmpty = "#(argb,8,8,3)color(1,1,1,1)";
		arrowFull = "#(argb,8,8,3)color(1,1,1,1)";
		border = "#(argb,8,8,3)color(1,1,1,1)";
		boxLeft = "#(argb,8,8,3)color(1,1,1,1)";
		boxRight = "#(argb,8,8,3)color(1,1,1,1)";
		boxHorz = "#(argb,8,8,3)color(1,1,1,1)";
	};
	class Slider
	{
		arrowEmpty = "#(argb,8,8,3)color(1,1,1,1)";
		arrowFull = "#(argb,8,8,3)color(1,1,1,1)";
		border = "#(argb,8,8,3)color(1,1,1,1)";
		thumb = "#(argb,8,8,3)color(1,1,1,1)";
	};
	class Cursors
	{
		class Arrow
		{
			texture = "JM\CF\GUI\textures\arrow_raw.paa";
			width = 16;
			height = 16;
			hotspotX = 0;
			hotspotY = 0;
			color[] = {0.8,0.8,0.8,1};
			shadow = 0;
		};
		class Debug: Arrow
		{
			color[] = {1.0,1.0,0.7,1};
			shadow = 0;
		};
		class Track
		{
			texture = "#(argb,32,32,1)color(1,1,1,1)";
			width = 24;
			height = 24;
			hotspotX = 0.5;
			hotspotY = 0.5;
			color[] = {0.7,0.1,0.0,1};
			shadow = 0;
		};
		class Move
		{
			texture = "#(argb,32,32,1)color(1,1,1,1)";
			width = 24;
			height = 24;
			hotspotX = 0.5;
			hotspotY = 0.5;
			color[] = {0.0,0.6,0.0,1};
			shadow = 0;
		};
		class Scroll
		{
			texture = "#(argb,32,32,1)color(1,1,1,1)";
			width = 24;
			height = 24;
			hotspotX = 0.5;
			hotspotY = 0.5;
			color[] = {0.8,0.6,0.0,1};
			shadow = 0;
		};
		class Rotate
		{
			texture = "#(argb,32,32,1)color(1,1,1,1)";
			width = 24;
			height = 24;
			hotspotX = 0.5;
			hotspotY = 0.5;
			color[] = {0.1,0.1,0.9,1};
			shadow = 0;
		};
		class Track3D
		{
			texture = "#(argb,32,32,1)color(1,1,1,1)";
			width = 24;
			height = 24;
			hotspotX = 0.5;
			hotspotY = 0.5;
			color[] = {0.7,0.1,0.0,1};
			shadow = 0;
		};
		class Move3D
		{
			texture = "#(argb,32,32,1)color(1,1,1,1)";
			width = 24;
			height = 24;
			hotspotX = 0.5;
			hotspotY = 0.5;
			color[] = {0.0,0.6,0.0,1};
			shadow = 0;
		};
		class Rotate3D
		{
			texture = "#(argb,32,32,1)color(1,1,1,1)";
			width = 24;
			height = 24;
			hotspotX = 0.5;
			hotspotY = 0.5;
			color[] = {0.1,0.1,0.9,1};
			shadow = 0;
		};
		class Raise3D
		{
			texture = "#(argb,32,32,1)color(1,1,1,1)";
			width = 24;
			height = 24;
			hotspotX = 0.5;
			hotspotY = 0.5;
			color[] = {0,0.8,1,1};
			shadow = 0;
		};
		class Wait
		{
			texture = "#(argb,32,32,1)color(1,1,1,1)";
			width = 24;
			height = 24;
			hotspotX = 0.5;
			hotspotY = 0.5;
			color[] = {0.1,0.1,0.9,1};
			shadow = 0;
		};
	};
};