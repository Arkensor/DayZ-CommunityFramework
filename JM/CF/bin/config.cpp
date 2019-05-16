////////////////////////////////////////////////////////////////////
//DeRap: bin\config.bin
//Produced from mikero's Dos Tools Dll version 7.16
//https://armaservices.maverick-applications.com/Products/MikerosDosTools/default
//'now' is Wed May 15 14:49:29 2019 : 'file' last modified on Tue May 14 20:18:35 2019
////////////////////////////////////////////////////////////////////

#define _ARMA_

//(18 Enums)
enum {
	destructengine = 2,
	destructdefault = 6,
	destructwreck = 7,
	destructtree = 3,
	destructtent = 4,
	drive_fwd = 0,
	drive_awd = 2,
	destructno = 0,
	drive_rwd = 1,
	htnone = 0,
	htmoveright = 3,
	sptpercents = 1,
	drive_642 = 3,
	htfade = 1,
	htmoveleft = 2,
	destructman = 5,
	sptplain = 0,
	destructbuilding = 1
};

battleyeLicenceUrl = "BattlEye\EULA.txt";
class CfgMods
{
	defaultAction = "http://www.arma2.com/mods";
};
class CfgTextureToMaterial
{
	class CarGlass
	{
		textures[] = {};
		material = "#SpecularGlass";
	};
	class AirborneGlass
	{
		textures[] = {};
		material = "#SpecularGlass";
	};
	class Metal
	{
		textures[] = {};
		material = "#Metal";
	};
	class AirBorneMetal
	{
		textures[] = {};
		material = "#Metal";
	};
	class RifleMetal
	{
		textures[] = {};
		material = "#RifleMetal";
	};
};
class CfgMaterials
{
	class Water
	{
		PixelShaderID = "Water";
		VertexShaderID = "Water";
		ambient[] = {0.016,0.0264,0.04,0.4};
		diffuse[] = {0.032,0.128,0.128,1.0};
		forcedDiffuse[] = {0,0,0,0};
		specular[] = {1,1,1,0};
		specularPower = 4;
		emmisive[] = {0,0,0,0};
		class Stage1
		{
			texture = "#(rgb,8,8,3)color(0.5,0.5,1.0,1)";
			uvSource = "texWaterAnim";
			class uvTransform
			{
				aside[] = {0,4,0};
				up[] = {4,0,0};
				dir[] = {0,0,4};
				pos[] = {0.2,0.5,0};
			};
		};
		class Stage3
		{
			texture = "#(ai,16,64,1)waterirradiance(16)";
			uvSource = "none";
		};
		class Stage4
		{
			texture = "#(argb,8,8,3)color(0.5,0.5,0.5,1)";
			uvSource = "none";
		};
		class Stage5
		{
			texture = "#(argb,8,8,3)color(0.5,0.5,0.5,1)";
			uvSource = "none";
		};
	};
	class Shore
	{
		PixelShaderID = "Shore";
		VertexShaderID = "Shore";
		ambient[] = {0.016,0.0264,0.04,0.4};
		diffuse[] = {0.032,0.128,0.128,1.0};
		forcedDiffuse[] = {0,0,0,0};
		specular[] = {1,1,1,0};
		specularPower = 4;
		emmisive[] = {0,0,0,0};
		class Stage1
		{
			texture = "#(rgb,8,8,3)color(0.5,0.5,1.0,1)";
			uvSource = "texWaterAnim";
			class uvTransform
			{
				aside[] = {0,4,0};
				up[] = {4,0,0};
				dir[] = {0,0,4};
				pos[] = {0.2,0.5,0};
			};
		};
		class Stage3
		{
			texture = "#(ai,16,64,1)waterirradiance(16)";
			uvSource = "none";
		};
		class Stage4
		{
			texture = "#(argb,8,8,3)color(0.5,0.5,0.5,1)";
			uvSource = "none";
		};
		class Stage5
		{
			texture = "#(argb,8,8,3)color(0.5,0.5,0.5,1)";
			uvSource = "none";
		};
	};
	class ShoreFoam
	{
		PixelShaderID = "ShoreFoam";
		VertexShaderID = "Shore";
		ambient[] = {0.016,0.0264,0.04,0.4};
		diffuse[] = {0.032,0.128,0.128,1.0};
		forcedDiffuse[] = {0,0,0,0};
		specular[] = {1,1,1,0};
		specularPower = 4;
		emmisive[] = {0,0,0,0};
		class Stage1
		{
			texture = "#(rgb,8,8,3)color(0.5,0.5,1.0,1)";
			uvSource = "texWaterAnim";
			class uvTransform
			{
				aside[] = {0,4,0};
				up[] = {4,0,0};
				dir[] = {0,0,4};
				pos[] = {0.2,0.5,0};
			};
		};
		class Stage3
		{
			texture = "#(ai,16,64,1)waterirradiance(16)";
			uvSource = "none";
		};
		class Stage4
		{
			texture = "#(argb,8,8,3)color(0.5,0.5,0.5,1)";
			uvSource = "none";
		};
		class Stage5
		{
			texture = "#(argb,8,8,3)color(0.5,0.5,0.5,1)";
			uvSource = "none";
		};
	};
	class ShoreWet
	{
		PixelShaderID = "ShoreWet";
		VertexShaderID = "Shore";
	};
	class Terrain
	{
		ambient[] = {1,1,1,1};
		diffuse[] = {0.6,0.6,0.6,1};
		forcedDiffuse[] = {0.05,0.05,0.05,1};
		specular[] = {0.0,0.0,0.0,0};
		specularPower = 1;
		emmisive[] = {0,0,0,0};
		PixelShaderID = "NormalMapDiffuse";
		VertexShaderID = "NormalMapDiffuseAlpha";
		class Stage1
		{
			texture = "#(argb,8,8,3)color(0,0,1,1)";
			uvSource = "tex";
			class uvTransform
			{
				aside[] = {1,0,0};
				up[] = {0,1,0};
				dir[] = {0,0,1};
				pos[] = {0,0,0};
			};
		};
		class Stage2
		{
			texture = "#(argb,8,8,3)color(0.5,0.5,0.5,1)";
			uvSource = "tex";
			class uvTransform
			{
				aside[] = {1,0,0};
				up[] = {0,1,0};
				dir[] = {0,0,1};
				pos[] = {0,0,0};
			};
		};
	};
	class SpecularGlass
	{
		ambient[] = {1,1,1,1};
		diffuse[] = {1,1,1,1};
		forcedDiffuse[] = {0,0,0,0};
		specular[] = {0.5,0.5,0.8,0};
		specularPower = 5;
		emmisive[] = {0,0,0,0};
	};
	class Metal
	{
		ambient[] = {1,1,1,1};
		diffuse[] = {1,1,1,1};
		forcedDiffuse[] = {0,0,0,0};
		specular[] = {0.2,0.2,0.2,0};
		specularPower = 5;
		emmisive[] = {0,0,0,0};
	};
	class RifleMetal
	{
		ambient[] = {1,1,1,1};
		diffuse[] = {1,1,1,1};
		forcedDiffuse[] = {0,0,0,0};
		specular[] = {0.2,0.2,0.2,0};
		specularPower = 5;
		emmisive[] = {0,0,0,0};
	};
};
class CfgRecoils
{
	access = 1;
	empty[] = {};
	impulse[] = {0.03,0.02,0.2,0.08,0.08,0.8,0.1,0.03,-0.1,0.3,0,0};
};
class WeaponMode_Base
{
	autoFire = 0;
	soundContinuous = 0;
	burst = 1;
	dispersion = 0.0;
	reloadTime = 0.0;
	sound[] = {};
	soundBegin[] = {};
	soundEnd[] = {};
	soundLoop[] = {};
};
class Mode_SemiAuto: WeaponMode_Base
{
	dispersion = 0.0002;
	reloadTime = 0.1;
	sound[] = {"",10.0,1};
	soundBegin[] = {"sound",1};
};
class Mode_Burst: Mode_SemiAuto
{
	burst = 3;
	dispersion = 0.0005;
	sound[] = {"",10.0,1};
	soundLoop[] = {"sound",1};
	soundEnd[] = {"sound",1};
};
class Mode_FullAuto: Mode_SemiAuto
{
	autoFire = 1;
	soundContinuous = 1;
	dispersion = 0.0005;
	reloadTime = 0.08;
	sound[] = {"",10.0,1};
	soundEnd[] = {"sound",1};
};
class OpticsInfoDefault
{
	memoryPointCamera = "eye";
	opticsZoomMin = 0.35;
	opticsZoomMax = 0.35;
	opticsZoomInit = 0.35;
	distanceZoomMin = 400;
	distanceZoomMax = 400;
	discreteDistance[] = {100};
	discreteDistanceInitIndex = 0;
};
class Muzzle_Base
{
	chamberSize = 0;
	muzzlePos = "usti hlavne";
	muzzleEnd = "konec hlavne";
	cartridgePos = "nabojnicestart";
	cartridgeVel = "nabojniceend";
	modes[] = {};
	magazines[] = {};
	chamberableFrom[] = {};
	barrelArmor = 1000.0;
	initSpeedMultiplier = 1.0;
	aiDispersionCoefX = 1.0;
	aiDispersionCoefY = 1.0;
	irDistance = 0.0;
	irLaserPos = "laser pos";
	irLaserEnd = "laser dir";
	drySound[] = {"",1,1};
	soundBullet[] = {"emptySound",1};
	useModelOptics = 1;
	modelOptics = "";
	class OpticsInfo: OpticsInfoDefault{};
};
class CfgWeapons
{
	access = 1;
	class Weapon_Base
	{
		access = 3;
		scope = 0;
		physLayer = "item_small";
		simulation = "Weapon";
		model = "";
		reversed = 0;
		inventorySlot = "";
		attachments[] = {};
		displayName = "";
		cargoClass = "";
		itemSize[] = {1,1};
		clothingType = "";
		destrType = "DestructDefault";
		maxSpeed = 80;
		itemsCargoSize[] = {0,0};
		class Reflectors{};
		aggregateReflectors[] = {};
		hiddenSelections[] = {};
		hiddenSelectionsTextures[] = {};
		hiddenSelectionsMaterials[] = {};
		selectionDamage = "zbytek";
		autoFire = 0;
		soundContinuous = 0;
		sound[] = {"",1,1};
		soundBegin[] = {"sound",1};
		dispersion = 0.002;
		chamberSize = 0;
		drySound[] = {"",1,1};
		soundBullet[] = {"emptySound",1};
		aiDispersionCoefX = 1.0;
		aiDispersionCoefY = 1.0;
		irDistance = 0;
		magazines[] = {};
		chamberableFrom[] = {};
		modes[] = {"this"};
		barrelArmor = 1000.0;
		initSpeedMultiplier = 1.0;
		useModelOptics = 1;
		modelOptics = "";
		muzzlePos = "usti hlavne";
		muzzleEnd = "konec hlavne";
		irLaserPos = "laser pos";
		irLaserEnd = "laser dir";
		cartridgePos = "nabojnicestart";
		cartridgeVel = "nabojniceend";
		class OpticsInfo: OpticsInfoDefault{};
		selectionFireAnim = "";
		muzzles[] = {"this"};
		reloadSound[] = {"",1,1};
		reloadMagazineSound[] = {"",1,1};
		prepSoundDry[] = {"sound",1};
		prepSoundLoaded[] = {"sound",1};
		emptySound[] = {"",1,1};
		soundEngine[] = {"",1,1};
		soundCrash[] = {"",1.0,1};
		soundLandCrash[] = {"",1.0,1};
		soundWaterCrash[] = {"",1.0,1};
	};
	class DefaultWeapon: Weapon_Base{};
	class PistolCore: DefaultWeapon{};
	class RifleCore: DefaultWeapon
	{
		aiRateOfFire = 0.5;
		aiRateOfFireDistance = 500;
		inventorySlot = "Shoulder";
		itemSize[] = {2,1};
	};
	class LauncherCore: DefaultWeapon
	{
		inventorySlot = "Shoulder";
		itemSize[] = {2,1};
	};
};
class CfgAmmo
{
	access = 1;
	class DefaultAmmo
	{
		access = 3;
		simulation = "";
		model = "";
		animated = 0;
		shadow = 0;
		reverses = 1;
		class DamageSystem
		{
			class GlobalHealth
			{
				class Health
				{
					hitpoints = 100;
					healthLevels[] = {{"PRISTINE_VALUE",{}},{"WORN_VALUE",{}},{"DAMAGED_VALUE",{}},{"BADLY_DAMAGED_VALUE",{}},{"RUINED_VALUE",{}}};
				};
			};
		};
		hit = 0.0;
		indirectHit = 0.0;
		indirectHitRange = 1.0;
		initSpeed = 100.0;
		maxLeadSpeed = 50.0;
		typicalSpeed = 900.0;
		initTime = 0.0;
		explosionTime = 0.0;
		fuseDistance = 0.0;
		maxSpeed = 0.0;
		simulationStep = 0.05;
		explosive = 1.0;
		caliber = 1.0;
		deflecting = 0.0;
		dispersion = 0.0;
		projectilesCount = 0;
		deflectionSlowDown = 0.8;
		timeToLive = 10.0;
		airFriction = -0.0005;
		coefGravity = 1.0;
		defaultMagazine = "";
		tracerScale = 0.0;
		traceStartTime = 0.0;
		traceEndTime = 0.0;
		nvgOnly = 0;
		soundHit[] = {"",1,1};
		hitGroundSoft[] = {"soundHit",1};
		hitGroundHard[] = {"soundHit",1};
		hitMan[] = {"soundHit",1};
		hitArmor[] = {"soundHit",1};
		hitIron[] = {"soundHit",1};
		hitBuilding[] = {"soundHit",1};
		hitFoliage[] = {"soundHit",1};
		hitWood[] = {"soundHit",1};
		hitGlass[] = {"soundHit",1};
		hitGlassArmored[] = {"soundHit",1};
		hitPlastic[] = {"soundHit",1};
		hitConcrete[] = {"soundHit",1};
		hitRubber[] = {"soundHit",1};
		hitMetalplate[] = {"soundHit",1};
		hitMetal[] = {"soundHit",1};
		hitDefault[] = {"soundHit",1};
		bulletFly[] = {};
		soundFly[] = {"",1,1};
		soundEngine[] = {"",1,1};
		supersonicCrackNear[] = {"",1,1};
		supersonicCrackFar[] = {"",1,1};
		soundSetExplosion[] = {};
		soundSetBulletFly[] = {};
		soundSetSuperSonic[] = {};
		SoundSetsGroundHits[] = {};
		damageBarrel = 1.0;
		damageBarrelDestroyed = 5.0;
		jamChance = 0.0;
		jamChanceDestroyed = 0.0;
		cartridge = "";
		proxyShape = "";
	};
	class BulletCore: DefaultAmmo
	{
		simulation = "shotBullet";
		simulationStep = 0.05;
		timeToLive = 3.0;
		explosive = 0.0;
		soundHit1[] = {"",0.031622775,1};
		soundHit2[] = {"",0.031622775,1};
		soundHit3[] = {"",0.031622775,1};
		soundHitMan1[] = {"",0.012589254,1};
		soundHitMan2[] = {"",0.012589254,1};
		soundHitArmor1[] = {"",0.031622775,1};
		soundHitArmor2[] = {"",0.031622775,1};
		soundHitBuilding1[] = {"",0.031622775,1};
		soundHitBuilding2[] = {"",0.031622775,1};
		hitGround[] = {"soundHit1",0.33,"soundHit2",0.33,"soundHit3",0.33};
		hitMan[] = {"soundHitMan1",0.5,"soundHitMan2",0.5};
		hitArmor[] = {"soundHitArmor1",0.7,"soundHitArmor2",0.3};
		hitBuilding[] = {"soundHitBuilding1",0.5,"soundHitBuilding2",0.5};
		soundFly[] = {"",0.25118864,0.7};
	};
	class ShotgunCore: DefaultAmmo
	{
		simulation = "shotSpread";
		simulationStep = 0.05;
		timeToLive = 3.0;
		explosive = 0.0;
		soundHit1[] = {"",0.031622775,1};
		soundHit2[] = {"",0.031622775,1};
		soundHit3[] = {"",0.031622775,1};
		soundHitMan1[] = {"",0.012589254,1};
		soundHitMan2[] = {"",0.012589254,1};
		soundHitArmor1[] = {"",0.031622775,1};
		soundHitArmor2[] = {"",0.031622775,1};
		soundHitBuilding1[] = {"",0.031622775,1};
		soundHitBuilding2[] = {"",0.031622775,1};
		hitGround[] = {"soundHit1",0.33,"soundHit2",0.33,"soundHit3",0.33};
		hitMan[] = {"soundHitMan1",0.5,"soundHitMan2",0.5};
		hitArmor[] = {"soundHitArmor1",0.7,"soundHitArmor2",0.3};
		hitBuilding[] = {"soundHitBuilding1",0.5,"soundHitBuilding2",0.5};
		soundFly[] = {"",0.25118864,0.7};
	};
};
class CfgMagazines
{
	class DefaultMagazine
	{
		scope = 0;
		model = "";
		simulation = "ProxyMagazines";
		reversed = 0;
		physLayer = "item_small";
		displayName = "";
		destrType = "DestructDefault";
		maxSpeed = 80;
		inventorySlot = "";
		itemSize[] = {1,1};
		cargoClass = "";
		itemsCargoSize[] = {0,0};
		attachments[] = {};
		clothingType = "";
		hiddenSelections[] = {};
		hiddenSelectionsTextures[] = {};
		soundEngine[] = {"",1,1};
		soundCrash[] = {"",0.31622776,1};
		soundLandCrash[] = {"",1.0,1};
		soundWaterCrash[] = {"",0.17782794,1};
		class Reflectors{};
		aggregateReflectors[] = {};
		selectionDamage = "zbytek";
		selectionFireAnim = "";
		type = "WeaponNoSlot";
		count = 1;
		simpleHeap = 0;
		modelSpecial = "";
		ammo = "";
		armorLights = 0.4;
		class ViewPilot
		{
			initAngleX = 5;
			minAngleX = -85;
			maxAngleX = 85;
			initAngleY = 0;
			minAngleY = -150;
			maxAngleY = 150;
			initFov = 0.9;
			minFov = 0.42;
			maxFov = 0.9;
			minMoveX = 0;
			maxMoveX = 0;
			minMoveY = 0;
			maxMoveY = 0;
			minMoveZ = 0;
			maxMoveZ = 0;
		};
	};
};
class CfgCloudlets
{
	access = 0;
	class Default
	{
		particleFSNtieth = 1;
		particleFSIndex = 0;
		particleFSFrameCount = 1;
		particleFSLoop = 1;
		angle = 0;
		angleVar = 0;
	};
	class Explosion
	{
		access = 0;
		cloudletDuration = 0.2;
		cloudletAnimPeriod = 0.5;
		cloudletSize = 1.0;
		cloudletAlpha = 1.0;
		cloudletGrowUp = 0.05;
		cloudletFadeIn = 0.01;
		cloudletFadeOut = 0.2;
		cloudletAccY = -0.2;
		cloudletMinYSpeed = 0;
		cloudletMaxYSpeed = 6;
		cloudletShape = "cloudletExplosion";
		cloudletColor[] = {1,1,1,0};
		interval = 0.001;
		size = 4.0;
		sourceSize = 3.0;
		timeToLive = 0;
		initT = 2500;
		deltaT = -4000;
		class Table
		{
			class T14
			{
				maxT = 1400;
				color[] = {0.91,0.5,0.17,0};
			};
			class T15
			{
				maxT = 1500;
				color[] = {1,0.6,0.2,0};
			};
			class T16
			{
				maxT = 1600;
				color[] = {1,0.71,0.3,0};
			};
			class T17
			{
				maxT = 1700;
				color[] = {0.98,0.83,0.41,0};
			};
			class T18
			{
				maxT = 1800;
				color[] = {0.98,0.91,0.54,0};
			};
			class T19
			{
				maxT = 1900;
				color[] = {0.98,0.99,0.6,0};
			};
			class T20
			{
				maxT = 2000;
				color[] = {0.96,0.99,0.72,0};
			};
			class T21
			{
				maxT = 2100;
				color[] = {1,0.98,0.91,0};
			};
			class T22
			{
				maxT = 2200;
				color[] = {1,1,1,0};
			};
		};
	};
	class CraterSmoke1
	{
		access = 0;
		interval = "0.05 / 0.8";
		cloudletAnimPeriod = "1 * 0.8";
		cloudletSize = 2.0;
		cloudletAlpha = 1.0;
		cloudletGrowUp = "1.0 * 0.8";
		cloudletFadeIn = "0.1 * 0.8";
		cloudletDuration = "3.0 * 0.8";
		cloudletFadeOut = "1.5 * 0.8";
		cloudletAccY = -0.1;
		cloudletMinYSpeed = "0.0 / 0.8";
		cloudletMaxYSpeed = "5.0 / 0.8";
		cloudletColor[] = {1,1,1,0};
		initT = 500;
		deltaT = "-50 * 0.8";
		class Table
		{
			class T0
			{
				maxT = 0;
				color[] = {1,1,1,0};
			};
			class T1
			{
				maxT = 500;
				color[] = {0.5,0.5,0.5,0};
			};
		};
		cloudletShape = "cloudletSmoke";
		density = "1.0 / 0.7";
		size = 1.0;
		timeToLive = "0.4 * 0.8";
		in = "0.0 * 0.8";
		out = "0.0 * 0.8";
		initYSpeed = "5.0 / 0.8";
	};
	class CraterSmoke2
	{
		access = 0;
		interval = "0.1 / 0.8";
		cloudletAnimPeriod = "1 * 0.8";
		cloudletSize = 2.0;
		cloudletAlpha = 1.0;
		cloudletGrowUp = "1.0 * 0.8";
		cloudletFadeIn = "0.1 * 0.8";
		cloudletDuration = "2.5 * 0.8";
		cloudletFadeOut = "1.5 * 0.8";
		cloudletAccY = -0.1;
		cloudletMinYSpeed = "0.0 / 0.8";
		cloudletMaxYSpeed = "2.0 / 0.8";
		cloudletColor[] = {1,1,1,0};
		initT = 0;
		deltaT = "0 * 0.8";
		class Table
		{
			class T0
			{
				maxT = 0;
				color[] = {1,1,1,0};
			};
		};
		cloudletShape = "cloudletSmoke";
		density = "1.0 / 0.7";
		size = 1.0;
		timeToLive = "1.0 * 0.8";
		in = "0.0 * 0.8";
		out = "2.0 * 0.8";
		initYSpeed = "0 / 0.8";
	};
	class CraterSmoke3
	{
		access = 0;
		interval = "0.1 / 0.8";
		cloudletAnimPeriod = "1 * 0.8";
		cloudletSize = 1.0;
		cloudletAlpha = 0.3;
		cloudletGrowUp = "1.0 * 0.8";
		cloudletFadeIn = "0.5 * 0.8";
		cloudletDuration = "3 * 0.8";
		cloudletFadeOut = "1 * 0.8";
		cloudletAccY = "-0.1 * 0.8";
		cloudletMinYSpeed = "0.0 / 0.8";
		cloudletMaxYSpeed = "5.0 / 0.8";
		cloudletColor[] = {1,1,1,0};
		initT = 500;
		deltaT = "-80 * 0.8";
		class Table
		{
			class T0
			{
				maxT = 0;
				color[] = {1,1,1,0};
			};
		};
		cloudletShape = "cloudletSmoke";
		density = "0.5 / 0.7";
		size = 1.0;
		timeToLive = "2.0 * 0.8";
		in = "0.2 * 0.8";
		out = "0.0 * 0.8";
		initYSpeed = "5.0 / 0.8";
	};
	class CraterDustSmall
	{
		access = 0;
		interval = 0.01;
		cloudletSize = 1;
		cloudletAlpha = 0.6;
		cloudletDuration = 0.2;
		cloudletAnimPeriod = 1;
		cloudletGrowUp = 0.6;
		cloudletFadeIn = 0;
		cloudletFadeOut = 0.6;
		cloudletAccY = -3.5;
		cloudletMinYSpeed = -20;
		cloudletMaxYSpeed = 10;
		cloudletColor[] = {0.25,0.23,0.16,0};
		initT = 0;
		deltaT = 0;
		class Table
		{
			class T0
			{
				maxT = 0;
				color[] = {1,1,1,0};
			};
		};
		cloudletShape = "cloudletDust";
		size = 0.2;
		sourceSize = 0.02;
	};
	class CraterBlood: CraterDustSmall
	{
		access = 0;
		interval = 0.005;
		cloudletAlpha = 0.5;
		cloudletDuration = 0.1;
		cloudletAnimPeriod = 1;
		cloudletGrowUp = 0.3;
		cloudletFadeIn = 0;
		cloudletFadeOut = 0.3;
		cloudletAccY = -1;
		cloudletMinYSpeed = -10;
		cloudletMaxYSpeed = 10;
		cloudletShape = "cloudletBlood";
		cloudletColor[] = {0.35,0.0,0.05,0};
		size = 0.15;
		sourceSize = 0.05;
	};
	class CraterWater: CraterDustSmall
	{
		access = 0;
		interval = 0.01;
		cloudletAlpha = 1;
		cloudletDuration = 0.3;
		cloudletAnimPeriod = 1;
		cloudletGrowUp = 0.3;
		cloudletFadeIn = 0;
		cloudletFadeOut = 0.2;
		cloudletAccY = -10;
		cloudletMinYSpeed = -100;
		cloudletMaxYSpeed = 100;
		cloudletShape = "cloudletWater";
		cloudletColor[] = {0.54,0.69,0.645,0};
		size = 0.02;
		sourceSize = 0.02;
	};
	class CraterDustBig: CraterDustSmall
	{
		access = 0;
		cloudletDuration = 2;
		cloudletGrowUp = 0.2;
		cloudletFadeIn = 0.2;
		cloudletFadeOut = 1.5;
		cloudletAccY = -8;
		cloudletMinYSpeed = -20;
		cloudletMaxYSpeed = 10;
	};
	class DefaultSmoke
	{
		interval = 0.3;
		cloudletDuration = 1;
		cloudletAnimPeriod = 3;
		cloudletSize = 1;
		cloudletAlpha = 1;
		cloudletGrowUp = 0.3;
		cloudletFadeIn = 0.5;
		cloudletFadeOut = 2.0;
		cloudletAccY = 0;
		cloudletMinYSpeed = -10;
		cloudletMaxYSpeed = 10;
		cloudletColor[] = {1,1,1,1};
		initT = 0;
		deltaT = 0;
		class Table{};
		cloudletShape = "cloudletSmoke";
		density = 1;
		size = 1;
		timeToLive = 30;
		in = 1;
		out = 1;
		initYSpeed = 3.5;
	};
	class DestructedObjectDust
	{
		interval = 0.15;
		cloudletDuration = 0.5;
		cloudletAnimPeriod = 1;
		cloudletSize = 0.5;
		cloudletAlpha = 1;
		cloudletGrowUp = 0.4;
		cloudletFadeIn = 0.2;
		cloudletFadeOut = 1.5;
		cloudletAccY = -0.5;
		cloudletMinYSpeed = -1;
		cloudletMaxYSpeed = 1;
		cloudletColor[] = {0.25,0.23,0.16,1};
		initT = 0;
		deltaT = 0;
		class Table{};
		cloudletShape = "cloudletSmoke";
		density = 2;
		size = 0.5;
		timeToLive = 0.4;
		in = 0.8;
		out = 0.8;
		initYSpeed = 2.5;
	};
	class DestructedEngineSmoke
	{
		interval = 0.3;
		cloudletDuration = 0.5;
		cloudletAnimPeriod = 3;
		cloudletSize = 1;
		cloudletAlpha = 1;
		cloudletGrowUp = 0.5;
		cloudletFadeIn = 0.5;
		cloudletFadeOut = 3.0;
		cloudletAccY = -0.8;
		cloudletMinYSpeed = 0;
		cloudletMaxYSpeed = 5;
		cloudletColor[] = {0.15,0.15,0.1,1};
		initT = 0;
		deltaT = 0;
		class Table{};
		cloudletShape = "cloudletSmoke";
		density = 1;
		size = 1;
		timeToLive = 6;
		in = 1;
		out = 6;
		initYSpeed = 3.5;
	};
};
class CfgOpticsEffect{};
class ExplosionEffects{};
class CfgVehicles
{
	access = 1;
	class All
	{
		access = 0;
		displayName = "$STR_DN_UNKNOWN";
		nameSound = "unknown";
		vehicleClass = "";
		simulation = "";
		scope = 0;
		reversed = 1;
		autocenter = 1;
		animated = 1;
		shadow = 1;
		insideSoundCoef = 0.5;
		outsideSoundFilter = 0;
		occludeSoundsWhenIn = 0.31622776;
		obstructSoundsWhenIn = 0.56234133;
		obstructSoundLFRatio = 0;
		occludeSoundLFRatio = 0.25;
		model = "bmp";
		destrType = "DestructDefault";
		armorLights = 0.4;
		class MarkerLights{};
		soundEngine[] = {"",1,1};
		soundCrash[] = {"",0.31622776,1};
		soundLandCrash[] = {"",1.0,1};
		soundWaterCrash[] = {"",0.17782794,1};
		class Reflectors{};
		aggregateReflectors[] = {};
		hiddenSelections[] = {};
		hiddenSelectionsTextures[] = {};
		hiddenSelectionsMaterials[] = {};
		class FxExplo
		{
			access = 1;
		};
		class AnimationSources{};
		selectionDamage = "zbytek";
	};
	class Transport: All{};
	class Car: Transport
	{
		displayName = "$STR_DN_CAR";
		nameSound = "veh_car";
		vehicleClass = "Car";
		simulation = "car";
		fuelCapacity = 100;
		brakeFluidCapacity = 5.1;
		oilCapacity = 4.2;
		coolantCapacity = 3.5;
		canFloat = 0;
		armorLights = 0.4;
		occludeSoundsWhenIn = 0.1;
		obstructSoundsWhenIn = 0.31622776;
		selectionBrakeLights = "brzdove svetlo";
		class Reflectors
		{
			class Left
			{
				color[] = {0.9,0.8,0.8,1.0};
				ambient[] = {0.1,0.1,0.1,1.0};
				position = "L svetlo";
				direction = "konec L svetla";
				hitpoint = "L svetlo";
				selection = "L svetlo";
				size = 0.5;
				brightness = 0.5;
			};
			class Right
			{
				color[] = {0.9,0.8,0.8,1.0};
				ambient[] = {0.1,0.1,0.1,1.0};
				position = "P svetlo";
				direction = "konec P svetla";
				hitpoint = "P svetlo";
				selection = "P svetlo";
				size = 0.5;
				brightness = 0.5;
			};
		};
		aggregateReflectors[] = {{"Left","Right"}};
		soundEngine[] = {"",1.7782794,0.9};
	};
	class Air: Transport
	{
		displayName = "$STR_DN_HELICOPTER";
		nameSound = "veh_aircraft";
		fuelCapacity = 1000;
		maxSpeed = 400;
		insideSoundCoef = 0.5;
		outsideSoundFilter = 1;
		occludeSoundsWhenIn = 0.031622775;
		obstructSoundsWhenIn = 0.17782794;
		audible = 10;
		driverAction = "";
		class MarkerLights
		{
			class RedStill
			{
				name = "cerveny pozicni";
				color[] = {0.3,0.03,0.03,1};
				ambient[] = {0.03,0.003,0.003,1};
				brightness = 0.01;
				blinking = 0;
			};
			class GreenStill
			{
				name = "zeleny pozicni";
				color[] = {0.03,0.3,0.03,1};
				ambient[] = {0.003,0.03,0.003,1};
				brightness = 0.01;
				blinking = 0;
			};
			class WhiteStill
			{
				name = "bily pozicni";
				color[] = {0.3,0.3,0.3,1};
				ambient[] = {0.03,0.03,0.03,1};
				brightness = 0.01;
				blinking = 0;
			};
			class WhiteBlinking
			{
				name = "bily pozicni blik";
				color[] = {1.0,1.0,1.0,1};
				ambient[] = {0.1,0.1,0.1,1};
				brightness = 0.01;
				blinking = 1;
			};
			class RedBlinking
			{
				name = "cerveny pozicni blik";
				color[] = {0.5,0.05,0.05,1};
				ambient[] = {0.05,0.005,0.005,1};
				brightness = 0.01;
				blinking = 1;
			};
		};
	};
	class Helicopter: Air
	{
		displayName = "$STR_DN_HELICOPTER";
		nameSound = "veh_helicopter";
		vehicleClass = "Air";
		simulation = "helicopter";
		gearRetracting = 0;
		gearUpTime = 3.33;
		gearDownTime = 2.0;
		class ViewPilot
		{
			initFov = 1.1;
			minFov = 0.57;
			maxFov = 1.1;
			initAngleX = 10;
			minAngleX = -85;
			maxAngleX = 85;
			initAngleY = 0;
			minAngleY = -150;
			maxAngleY = 150;
			minMoveX = -0.35;
			maxMoveX = 0.35;
			minMoveY = -0.5;
			maxMoveY = 0.2;
			minMoveZ = -0.3;
			maxMoveZ = 0.5;
		};
		class CargoSpec
		{
			class Cargo1
			{
				showHeadPhones = 1;
			};
			class Cargo2
			{
				showHeadPhones = 0;
			};
		};
		mainRotorSpeed = 1.0;
		backRotorSpeed = 1.5;
		maxMainRotorDive = 0;
		maxBackRotorDive = 0;
		minMainRotorDive = 0;
		minBackRotorDive = 0;
		neutralBackRotorDive = 0;
		neutralMainRotorDive = 0;
		selectionHRotorStill = "velka vrtule staticka";
		selectionHRotorMove = "velka vrtule blur";
		selectionVRotorStill = "mala vrtule staticka";
		selectionVRotorMove = "mala vrtule blur";
		memoryPointLMissile = "L strela";
		memoryPointRMissile = "P strela";
		memoryPointLRocket = "L raketa";
		memoryPointRRocket = "P raketa";
		memoryPointGun = "";
		memoryPointPilot = "pilot";
		selectionFireAnim = "zasleh";
		maxSpeed = 300;
		enableSweep = 1;
		envelope[] = {0.0,0.2,0.9,2.1,2.5,3.3,3.5,3.6,3.7,3.8,3.8,3.0,0.9,0.7,0.5};
		dammageHalf[] = {"jeep_kab_sklo1.paa","jeep_kab_sklo1B.paa","uh60_kab_sklo2.paa","uh60_kab_sklo2B.paa","uh60_gunner_okna.paa","uh60_gunner_oknaB.paa","ah-1_kabina_predokno.paa","ah-1_kabina_predoknoB.paa","ah-1_kabina_zadokno.paa","ah-1_kabina_zadoknoB.paa","ah-1_kabina_topokno.paa","ah-1_kabina_topoknoB.paa"};
		dammageFull[] = {"jeep_kab_sklo1.paa","jeep_kab_sklo1C.paa","uh60_kab_sklo2.paa","uh60_kab_sklo2C.paa","uh60_gunner_okna.paa","uh60_gunner_oknaC.paa","ah-1_kabina_predokno.paa","ah-1_kabina_predoknoC.paa","ah-1_kabina_zadokno.paa","ah-1_kabina_zadoknoC.paa","ah-1_kabina_topokno.paa","ah-1_kabina_topoknoC.paa"};
		class Reflectors
		{
			class Reflector
			{
				color[] = {0.8,0.8,1.0,1.0};
				ambient[] = {0.07,0.07,0.07,1.0};
				position = "L svetlo";
				direction = "konec L svetla";
				hitpoint = "L svetlo";
				selection = "L svetlo";
				size = 0.5;
				brightness = 2;
			};
		};
		soundLandingGear[] = {"",1,1};
		class RotorLibHelicopterProperties
		{
			RTDconfig = "";
			hasAPU = 0;
			maxTorque = 10000;
			maxBatteryCharge = 100.0;
			starterBatteryDrain = 2.0;
			electricityBatteryDrain = 0.1;
			engineBatteryRecharge = 0.5;
			autoHoverCorrection[] = {0,0,0};
			maxMainRotorStress = 10000;
			maxTailRotorStress = 10000;
			maxHorizontalStabilizerLeftStress = 10000;
			maxHorizontalStabilizerRightStress = 10000;
			maxVerticalStabilizerStress = 10000;
			stressDamagePerSec = 0.01;
			temperatureEffects[] = {{0,-25,0,-15},{850,250,-400,-20},{1350,250,-600,-20}};
			maxEngineTemperature = 1000;
			hotStartTemperature = 200;
			retreatBladeStallWarningSpeed = 69.4;
			horizontalWingsAngleCollMin = 0;
			horizontalWingsAngleCollMax = 0;
			defaultCollective = 0.7;
		};
	};
	class Man: All
	{
		displayName = "$STR_DN_MAN";
		nameSound = "veh_man";
		vehicleClass = "Men";
		simulation = "soldier";
		autocenter = 0;
		clothingType = "male";
		class Wounds{};
		model = "";
		selectionHeadWound = "head injury";
		selectionBodyWound = "body injury";
		selectionLArmWound = "l arm injury";
		selectionRArmWound[] = {"r arm injury","p arm injury"};
		selectionLLegWound = "l leg injury";
		selectionRLegWound[] = {"r leg injury","p leg injury"};
		selectionHeadHide = "";
		memoryPointPilot = "pilot";
		memoryPointLStep = "stopaL";
		memoryPointRStep = "stopaP";
		memoryPointAim = "zamerny";
		memoryPointCameraTarget = "zamerny";
		memoryPointAimingAxis = "osa mireni";
		memoryPointLeaningAxis = "osa naklaneni";
		memoryPointHeadAxis = "osa otaceni";
		memoryPointHandGrenade = "granat";
		memoryPointCommonDamage = "zamerny";
		selectionPersonality = "osobnost";
		selectionLBrow = "loboci";
		selectionMBrow = "soboci";
		selectionRBrow = "poboci";
		selectionLMouth = "lkoutek";
		selectionMMouth = "skoutek";
		selectionRMouth = "pkoutek";
		selectionEyelid = "vicka";
		selectionLip = "spodni ret";
		emptySound[] = {"",0,1};
		class Reflectors{};
		class InventorySlots{};
		weaponBone = "";
		launcherBone = "";
		handGunBone = "";
		characterID = -1;
		emptyEyewear = "";
		emptyHeadgear = "";
		emptyArmband = "";
		emptyBody = "";
		emptyLegs = "";
		emptyFeet = "";
		emptyVest = "";
		emptyGloves = "";
		emptyBack = "";
		emptyShoulder = "";
		emptyMelee = "";
		emptyMask = "";
	};
	class Animal: Man
	{
		displayName = "$STR_DN_ANIMAL";
		nameSound = "veh_animal";
		vehicleClass = "Animals";
	};
	class Static: All
	{
		reversed = 0;
		hasDriver = 0;
		icon = "iconStaticObject";
		displayName = "$STR_DN_UNKNOWN";
		nameSound = "obj_object";
		accuracy = 0.005;
		simulation = "house";
		picture = "pictureStaticObject";
		targetCategory = "building";
		maxSpeed = 0;
		coefInside = 1;
		coefInsideHeur = 4;
		windSockExist = 0;
	};
	class Fortress: Static
	{
		displayName = "$STR_DN_BUNKER";
		nameSound = "obj_Bunker";
		cost = 1000000;
		accuracy = 0.2;
	};
	class Building: Static
	{
		scope = 1;
		displayName = "$STR_DN_BUILDING";
		nameSound = "obj_building";
		accuracy = 0.1;
	};
	class NonStrategic: Building
	{
		ladders[] = {};
	};
	class Strategic: Building
	{
		cost = 1000000;
		ladders[] = {};
	};
	class FlagCarrierCore: Strategic
	{
		scope = 1;
		animated = 0;
		vehicleClass = "Objects";
		icon = "";
		displayName = "$STR_DN_FLAG";
		simulation = "flagcarrier";
		model = "";
		placement = "vertical";
		animationFlag = "";
	};
	class Land_VASICore: NonStrategic
	{
		scope = 1;
		animated = 0;
		reversed = 0;
		vehicleClass = "Objects";
		icon = "";
		model = "";
		displayName = "VASI";
		accuracy = 0.2;
		typicalCargo[] = {};
		destrType = "DestructBuilding";
		selectionWhiteLight = "light-white";
		selectionRedLight = "light-red";
		selectionOffLight = "light-off";
		simulation = "vasi";
		enabled = 0;
		vasiRed[] = {1,0,0};
		vasiWhite[] = {1,1,1};
		vasiSlope = 0.08;
	};
	class Thing: All
	{
		reversed = 0;
		animated = 0;
		icon = "iconThing";
		vehicleClass = "Objects";
		displayName = "$STR_DN_UNKNOWN";
		nameSound = "obj_object";
		accuracy = 0.005;
		simulation = "thing";
		weight = 0;
		class InventoryPlacements{};
		submerged = 0;
		submergeSpeed = 0;
		airFriction2[] = {0.01,0.01,0.01};
		airFriction1[] = {0.01,0.01,0.01};
		airFriction0[] = {0.01,0.01,0.01};
		airRotation = 0;
		gravityFactor = 1;
		timeToLive = 1e+010;
		disappearAtContact = 0;
		hasDriver = 0;
		minHeight = 0.1;
		avgHeight = 0.2;
		maxHeight = 0.4;
		maxSpeed = 0;
	};
	class ThingEffect: Thing
	{
		scope = 1;
		simulation = "thingeffect";
		submerged = -0.5;
		submergeSpeed = 0.25;
		timeToLive = 20;
	};
	class ThingEffectLight: ThingEffect
	{
		scope = 0;
		airFriction2[] = {1,1,8};
		airFriction1[] = {1,1,4};
		airFriction0[] = {0.1,0.1,0.1};
		airRotation = 0.1;
		submergeSpeed = 0;
		minHeight = 0.1;
		avgHeight = 0.2;
		maxHeight = 0.4;
	};
	class ThingEffectFeather: ThingEffectLight
	{
		airFriction2[] = {16,16,16};
		airFriction1[] = {16,16,16};
		airFriction0[] = {0.1,0.1,0.1};
		gravityFactor = 0.05;
		minHeight = 0.5;
		avgHeight = 1.8;
		maxHeight = 3;
	};
	class FxExploArmor1: ThingEffect
	{
		access = 0;
		model = "";
		displayName = "Internal: FxExploArmor1";
	};
	class FxExploArmor2: ThingEffect
	{
		access = 0;
		model = "";
		displayName = "Internal: FxExploArmor2";
	};
	class FxExploArmor3: ThingEffect
	{
		access = 0;
		model = "";
		displayName = "Internal: FxExploArmor3";
	};
	class FxExploArmor4: ThingEffect
	{
		access = 0;
		model = "";
		displayName = "Internal: FxExploArmor4";
	};
	class FxCartridge: ThingEffect
	{
		access = 0;
		model = "";
		displayName = "$STR_DN_FX_CARTRIDGE";
		submerged = 0;
		submergeSpeed = 0;
		timeToLive = 5;
		disappearAtContact = 1;
	};
};
class CfgNonAIVehicles
{
	access = 0;
	class StaticObject
	{
		access = 0;
		simulation = "staticobject";
	};
	class Plant: StaticObject
	{
		access = 0;
	};
	class TreeHard: Plant
	{
		access = 0;
	};
	class TreeSoft: Plant
	{
		access = 0;
	};
	class BushHard: Plant
	{
		access = 0;
	};
	class BushSoft: Plant
	{
		access = 0;
	};
	class EmptyDetector
	{
		scope = 2;
		displayName = "$STR_DN_EMPTY";
		simulation = "detector";
		model = "";
		selectionFabric = "latka";
	};
	class StreetLamp
	{
		model = "";
		destrType = "DestructTree";
		simulation = "StreetLamp";
		animated = 0;
		colorDiffuse[] = {0.9,0.8,0.6};
		colorAmbient[] = {0.1,0.1,0.1};
		brightness = 0.2;
		class Reflectors
		{
			class LampLight
			{
				color[] = {0.9,0.8,0.6,1.0};
				ambient[] = {0.1,0.1,0.1,1.0};
				position = "Light";
				direction = "";
				hitpoint = "lampa";
				selection = "";
				size = 0.5;
				brightness = 0.2;
			};
		};
		aggregateReflectors[] = {};
		armorLights = 1;
	};
	class EditCursor
	{
		model = "\core\cursor\cursor.p3d";
		simulation = "EditCursor";
	};
	class ObjView
	{
		scope = 2;
		model = "";
		simulation = "ObjView";
	};
	class Temp
	{
		scope = 2;
		model = "";
		simulation = "Temp";
	};
	class Bird
	{
		scope = 0;
		model = "";
		animated = 0;
		simulation = "SeaGull";
		reversed = 0;
		minHeight = 5;
		avgHeight = 10;
		maxHeight = 50;
		minSpeed = -0.5;
		maxSpeed = 20;
		acceleration = 7;
		turning = 1;
		straightDistance = 50;
		flySound[] = {"",0.031622775,1,1};
		singSound[] = {"",0.031622775,1,1};
		canBeShot = 1;
		airFriction2[] = {25,12,2.5};
		airFriction1[] = {1500,700,100};
		airFriction0[] = {40,20,60};
	};
	class Insect: Bird
	{
		animated = 0;
		minHeight = -0.1;
		avgHeight = 1.2;
		maxHeight = 2.0;
		minSpeed = -0.1;
		maxSpeed = 5;
		acceleration = 25;
		straightDistance = 2;
		turning = 2;
		flySound[] = {"",0.031622775,1,1};
		singSound[] = {"",0.031622775,1,1};
		canBeShot = 0;
		airFriction2[] = {125,12,2.5};
		airFriction1[] = {7500,700,100};
		airFriction0[] = {200,20,60};
	};
	class SeaGull: Bird
	{
		scope = 2;
		model = "\core\default\default.p3d";
		reversed = 0;
	};
	class StaticCamera
	{
		scope = 2;
		model = "";
		simulation = "StaticCamera";
	};
	class FreeDebugCamera
	{
		scope = 2;
		model = "";
		simulation = "FreeDebugCamera";
	};
	class ProxyHands
	{
		scope = 2;
		simulation = "ProxyInventory";
		inventorySlot = "Hands";
		autocenter = 0;
		animated = 0;
		model = "";
		shadow = 1;
		reversed = 1;
	};
	class ProxyEyewear
	{
		scope = 2;
		simulation = "ProxyInventory";
		inventorySlot = "Eyewear";
		autocenter = 0;
		animated = 0;
		model = "";
		shadow = 1;
		reversed = 1;
	};
	class ProxyHeadgear
	{
		scope = 2;
		simulation = "ProxyInventory";
		inventorySlot = "Headgear";
		autocenter = 0;
		animated = 0;
		model = "";
		shadow = 1;
		reversed = 1;
	};
	class ProxyArmband
	{
		scope = 2;
		simulation = "ProxyInventory";
		inventorySlot = "Armband";
		autocenter = 0;
		animated = 0;
		model = "";
		shadow = 1;
		reversed = 1;
	};
	class ProxyBody
	{
		scope = 2;
		simulation = "ProxyInventory";
		inventorySlot = "Body";
		autocenter = 0;
		animated = 0;
		model = "";
		shadow = 1;
		reversed = 1;
	};
	class ProxyLegs
	{
		scope = 2;
		simulation = "ProxyInventory";
		inventorySlot = "Legs";
		autocenter = 0;
		animated = 0;
		model = "";
		shadow = 1;
		reversed = 1;
	};
	class ProxyFeet
	{
		scope = 2;
		simulation = "ProxyInventory";
		inventorySlot = "Feet";
		autocenter = 0;
		animated = 0;
		model = "";
		shadow = 1;
		reversed = 1;
	};
	class ProxyVest
	{
		scope = 2;
		simulation = "ProxyInventory";
		inventorySlot = "Vest";
		autocenter = 0;
		animated = 0;
		model = "";
		shadow = 1;
		reversed = 1;
	};
	class ProxyGloves
	{
		scope = 2;
		simulation = "ProxyInventory";
		inventorySlot = "Gloves";
		autocenter = 0;
		animated = 0;
		model = "";
		shadow = 1;
		reversed = 1;
	};
	class ProxyBack
	{
		scope = 2;
		simulation = "ProxyInventory";
		inventorySlot = "Back";
		autocenter = 0;
		animated = 0;
		model = "";
		shadow = 1;
		reversed = 1;
	};
	class ProxyShoulder
	{
		scope = 2;
		simulation = "ProxyInventory";
		inventorySlot = "Shoulder";
		autocenter = 0;
		animated = 0;
		model = "";
		shadow = 1;
		reversed = 1;
	};
	class ProxyBow
	{
		scope = 2;
		simulation = "ProxyInventory";
		inventorySlot = "Bow";
		autocenter = 0;
		animated = 0;
		model = "";
		shadow = 1;
		reversed = 1;
	};
	class ProxyHips
	{
		scope = 2;
		simulation = "ProxyInventory";
		inventorySlot = "Hips";
		autocenter = 0;
		animated = 0;
		model = "";
		shadow = 1;
		reversed = 1;
	};
	class ProxyMelee
	{
		scope = 2;
		simulation = "ProxyInventory";
		inventorySlot = "Melee";
		autocenter = 0;
		animated = 0;
		model = "";
		shadow = 1;
		reversed = 1;
	};
	class ProxyMask
	{
		scope = 2;
		simulation = "ProxyInventory";
		inventorySlot = "Mask";
		autocenter = 0;
		animated = 0;
		model = "";
		shadow = 1;
		reversed = 1;
	};
	class ProxyAttachment
	{
		scope = 0;
		simulation = "ProxyInventory";
		inventorySlot = "";
		autocenter = 0;
		animated = 0;
		model = "";
		shadow = 1;
		reversed = 1;
	};
	class Proxyus_bag: ProxyBack{};
	class ProxyHide
	{
		autocenter = 0;
		scope = 2;
		animated = 0;
		model = "";
		simulation = "alwayshide";
	};
	class ProxyWreck
	{
		autocenter = 0;
		scope = 0;
		animated = 0;
		model = "";
		simulation = "alwaysshow";
	};
	class ProxyFlag
	{
		autocenter = 0;
		scope = 2;
		reversed = 0;
		model = "";
		shadow = 1;
		simulation = "flag";
		selectionFabric = "latka";
	};
	class ProxyAmmoInTruck
	{
		autocenter = 0;
		scope = 2;
		reversed = 0;
		animated = 0;
		shadow = 1;
		model = "";
		simulation = "alwaysshow";
	};
};
class PreloadVehicles
{
	access = 1;
};
class CfgVoice
{
	access = 0;
	voices[] = {"NoVoice"};
	femaleVoices[] = {};
	voicePlayer = "NoVoice";
	micOuts[] = {};
	preview = "";
	default = "NoVoice";
	class NoVoice
	{
		protocol = "RadioProtocolBase";
		variants[] = {1};
		directories[] = {"",""};
		identityTypes[] = {"Default"};
		scope = 2;
		voiceType = "";
	};
};
class CfgVoiceTypes
{
	class NoVoice
	{
		name = "No voice";
		voices[] = {"NoVoice"};
		preview = "NoVoice";
		alternative = "";
	};
};
class CfgCoreData
{
	access = 0;
	textureDefault = "#(argb,1,1,1)color(1,1,1,1)";
	textureBlack = "#(argb,1,1,1)color(0,0,0,1)";
	textureHalf = "#(argb,1,1,1)color(0.5,0.5,0.5,1,dt)";
	textureZero = "#(argb,1,1,1)color(0,0,0,0)";
	textureLine = "#(argb,1,1,1)color(1,1,1,1)";
	textureLine3D = "#(argb,1,1,1)color(1,1,1,1)";
	textureTIConversion = "core\data\ticonversion.tga";
	textureTrack = "#(argb,1,1,1)color(1,1,1,1)";
	textureTrackFour = "#(argb,1,1,1)color(1,1,1,1)";
	maskTextureFlare = "#(argb,1,1,1)color(1,1,1,0)";
	eyeFlare = "#(argb,1,1,1)color(1,1,1,0)";
	lodTransitionSpeed = 2;
	craterShell = "core\default\default.p3d";
	craterBullet = "core\default\default.p3d";
	slopBlood = "core\default\default.p3d";
	cloudletBasic = "core\default\default.p3d";
	cloudletFire = "core\default\default.p3d";
	cloudletFireD = "core\default\default.p3d";
	cloudletWater = "core\default\default.p3d";
	cloudletMissile = "core\default\default.p3d";
	cobraLight = "core\default\default.p3d";
	sphereLight = "core\default\default.p3d";
	halfLight = "core\default\default.p3d";
	marker = "core\default\default.p3d";
	footStepL = "core\default\default.p3d";
	footStepR = "core\default\default.p3d";
	forceArrowModel = "core\cursor\forcearrowmodel.p3d";
	forceArrowModelBuld = "core\cursor\forcearrowmodelbuld.p3d";
	halfspaceModel = "core\default\default.p3d";
	sphereModel = "core\Sphere\koule.p3d";
	rectangleModel = "core\Rectangle\rect.p3d";
	horizontObject = "core\default\default.p3d";
	collisionShape = "core\default\default.p3d";
	rayModel = "core\cursor\forcearrowmodel.p3d";
	gunLightModel = "core\cursor\forcearrowmodel.p3d";
};
class CfgVehicleIcons
{
	iconObject = "#(argb,1,1,1)color(1,1,1,1)";
	iconLogic = "#(argb,1,1,1)color(1,1,1,1)";
	iconVehicle = "#(argb,1,1,1)color(1,1,1,1)";
	iconCar = "#(argb,1,1,1)color(1,1,1,1)";
	iconMotorcycle = "#(argb,1,1,1)color(1,1,1,1)";
	iconTank = "#(argb,1,1,1)color(1,1,1,1)";
	iconAPC = "#(argb,1,1,1)color(1,1,1,1)";
	iconMan = "#(argb,1,1,1)color(1,1,1,1)";
	iconAnimal = "#(argb,1,1,1)color(1,1,1,1)";
	iconAir = "#(argb,1,1,1)color(1,1,1,1)";
	iconHelicopter = "#(argb,1,1,1)color(1,1,1,1)";
	iconPlane = "#(argb,1,1,1)color(1,1,1,1)";
	iconShip = "#(argb,1,1,1)color(1,1,1,1)";
	iconParachute = "#(argb,1,1,1)color(1,1,1,1)";
	iconStaticObject = "#(argb,1,1,1)color(1,1,1,1)";
	iconThing = "#(argb,1,1,1)color(1,1,1,1)";
	iconLaserTarget = "#(argb,1,1,1)color(1,1,1,1)";
	pictureLogic = "#(argb,1,1,1)color(1,1,1,1)";
	pictureParachute = "#(argb,1,1,1)color(1,1,1,1)";
	pictureLaserTarget = "#(argb,1,1,1)color(1,1,1,1)";
	pictureStaticObject = "#(argb,1,1,1)color(1,1,1,1)";
	pictureThing = "#(argb,1,1,1)color(1,1,1,1)";
};
class CfgCloudletShapes
{
	cloudletExplosion = "\core\default\default.p3d";
	cloudletSmoke = "\core\default\default.p3d";
	cloudletDust = "\core\default\default.p3d";
	cloudletBlood = "\core\default\default.p3d";
	cloudletWater = "\core\default\default.p3d";
	cloudletMissile = "\core\default\default.p3d";
	cloudletFire = "\core\default\default.p3d";
	cloudletClouds = "\core\default\default.p3d";
};
class CfgSaveThumbnails
{
	saveSingleMission = "core\all\todo.png";
	saveMPMission = "core\all\todo.png";
	saveCampaign = "core\all\todo.png";
	userMissionSP = "core\all\todo.png";
	userMissionMP = "core\all\todo.png";
};
class CfgVideoOptions
{
	class Visibility
	{
		minValue = 500;
		maxValue = 12000;
	};
	class ObjectsVisibility
	{
		minValue = 500;
		maxValue = 12000;
	};
	class TextureDetail
	{
		class VeryLow
		{
			value = 3.0;
		};
		class Low
		{
			value = 2.5;
		};
		class Normal
		{
			value = 2.0;
		};
		class High
		{
			value = 1.5;
		};
		class VeryHigh
		{
			value = 1.0;
		};
	};
	class ObjectDetail
	{
		class VeryLow
		{
			value = 200000;
		};
		class Low
		{
			value = 300000;
		};
		class Normal
		{
			value = 500000;
		};
		class High
		{
			value = 750000;
		};
		class VeryHigh
		{
			value = 1000000;
		};
	};
	class TerrainDetail
	{
		class VeryLow
		{
			value = 50.0;
		};
		class Low
		{
			value = 25.0;
		};
		class Normal
		{
			value = "12.5f";
		};
		class High
		{
			value = "6.25f";
		};
		class VeryHigh
		{
			value = "3.125f";
		};
	};
	class CloudsDetail
	{
		class VeryLow
		{
			value = 32;
		};
		class Low
		{
			value = 48;
		};
		class Normal
		{
			value = 64;
		};
		class High
		{
			value = 96;
		};
		class VeryHigh
		{
			value = 128;
		};
	};
	class DefaultSettings
	{
		Visibility = 1600;
		ObjectsVisibility = 1200;
		ObjectDetail = 2;
		TerrainDetail = 3;
		TextureDetail = 3;
		CloudsDetail = 2;
		ShadowDetail = 2;
		TextureFiltering = 1;
		TerrainSurface = 2;
		FXAA = 2;
		MSAA = 0;
		ATOC = 0;
		FXAO = 1;
		FXQuality = 1;
	};
	class OverallSettings
	{
		class VeryLow: DefaultSettings
		{
			Visibility = 1000;
			ObjectsVisibility = 800;
			ObjectDetail = 0;
			TerrainDetail = 0;
			TextureDetail = 0;
			CloudsDetail = 0;
			ShadowDetail = 0;
			TextureFiltering = 0;
			TerrainSurface = 0;
			FXAA = 0;
			MSAA = 0;
			ATOC = 0;
			FXAO = 0;
			FXQuality = 0;
		};
		class Low: DefaultSettings
		{
			Visibility = 1600;
			ObjectsVisibility = 1300;
			ObjectDetail = 1;
			TerrainDetail = 1;
			TextureDetail = 1;
			CloudsDetail = 1;
			ShadowDetail = 1;
			TextureFiltering = 1;
			TerrainSurface = 2;
			FXAA = 2;
			MSAA = 0;
			ATOC = 0;
			FXAO = 0;
			FXQuality = 1;
		};
		class Normal: DefaultSettings
		{
			Visibility = 1600;
			ObjectsVisibility = 1200;
			ObjectDetail = 2;
			TerrainDetail = 3;
			TextureDetail = 3;
			CloudsDetail = 2;
			ShadowDetail = 2;
			TextureFiltering = 2;
			TerrainSurface = 2;
			FXAA = 2;
			MSAA = 0;
			ATOC = 0;
			FXAO = 2;
			FXQuality = 2;
		};
		class High: DefaultSettings
		{
			Visibility = 2500;
			ObjectsVisibility = 1800;
			ObjectDetail = 3;
			TerrainDetail = 3;
			TextureDetail = 3;
			CloudsDetail = 3;
			ShadowDetail = 3;
			TextureFiltering = 2;
			TerrainSurface = 2;
			FXAA = 3;
			MSAA = 1;
			ATOC = 1;
			FXAO = 3;
			FXQuality = 2;
		};
		class VeryHigh: DefaultSettings
		{
			Visibility = 3800;
			ObjectsVisibility = 3200;
			ObjectDetail = 4;
			TerrainDetail = 4;
			TextureDetail = 4;
			CloudsDetail = 4;
			ShadowDetail = 4;
			TextureFiltering = 2;
			TerrainSurface = 3;
			FXAA = 4;
			MSAA = 3;
			ATOC = 1;
			FXAO = 4;
			FXQuality = 2;
		};
	};
	class Benchmark
	{
		defaultResult = 1000;
		resultLimits[] = {300,150,120,90,0};
	};
};
class CfgLanguages
{
	class Original
	{
		name = "Original";
	};
	class English
	{
		name = "$STR_LANG_ENGLISH";
	};
};
class CfgSurfaceCharacters
{
	class Empty
	{
		probability[] = {};
		names[] = {};
	};
};
class CfgSurfaces
{
	class Default
	{
		access = 2;
		files = "default";
		rough = 0.075;
		dust = 0.1;
		isLiquid = 0;
		friction = 0.9;
		restitution = 0;
		soundEnviron = "normalExt";
		character = "Empty";
		visibility = 1;
		audibility = 1;
		impact = "default_Mat";
		transparency = -1;
	};
	class Water
	{
		access = 2;
		files = "more_anim*";
		rough = 0.0;
		dust = 0.0;
		soundEnviron = "water";
		friction = 0.9;
		restitution = 0;
		isLiquid = 1;
		character = "Empty";
		impact = "default_Mat";
	};
};
class CfgDefaultSettings
{
	defaultVisibility = 1600;
	defaultTerrainGrid = 10;
	defaultObjectViewDistance = 1600;
	hazeDefaultDistance = -1;
	class UserInfo
	{
		version = 1;
		blood = 1;
		terrainGrid = 10.0;
		volumeCD = 5;
		volumeFX = 5;
		volumeSpeech = 5;
		singleVoice = 0;
		gamma = 1.0;
		brightness = 1.0;
	};
};
class CfgPatches
{
	access = 1;
};
class CfgFontFamilies
{
	access = 0;
	class LucidaConsoleB
	{
		fonts[] = {"\core\data\fonts\lucidaConsoleB8","\core\data\fonts\lucidaConsoleB11"};
	};
	class TahomaB
	{
		fonts[] = {"\core\data\fonts\tahomab16"};
	};
};
class CfgFonts{};
overviewLockedMission = "dtaext\lockedmission";
overviewMyMissions = "dtaext\mymissions";
overviewNewMission = "dtaext\newmission";
fontPlate = "TahomaB";
fontHelicopterHUD = "TahomaB";
fontClanName = "TahomaB";
class CfgEditCamera
{
	speedFwdBack = 1.0;
	speedLeftRight = 1.0;
	speedUpDown = 1.0;
	speedRotate = 1.0;
	speedElevation = 1.0;
	speedTurboMultiplier = 4.0;
	iconSelect = "";
	iconSelectColor[] = {1,1,0,1};
	iconSelectSizeX = 0.75;
	iconSelectSizeY = 1;
};
class CfgWrapperUI
{
	access = 0;
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
			texture = "Core\Cursor\Data\arrow_raw.paa";
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
class CfgInGameUI
{
	access = 0;
	imageCornerElement = "#(argb,8,8,3)color(1,1,1,1)";
	xboxStyle = 1;
	colorBackground[] = {0.2,0.15,0.1,0.8};
	colorBackgroundCommand[] = {0,0,0,0.3};
	colorBackgroundHelp[] = {0.2,0.15,0.1,0.8};
	colorText[] = {0.8,0.8,0.8,1};
	shadow = 0;
	class PlayerColors
	{
		class ColNone
		{
			texture = "#(argb,8,8,3)color(0,0,0,0)";
			text = "None";
		};
		class ColWhite
		{
			texture = "#(argb,8,8,3)color(1,1,1,1)";
			text = "White";
		};
		class ColRed
		{
			texture = "#(argb,8,8,3)color(1,0,0,1)";
			text = "Red";
		};
		class ColOrange
		{
			texture = "#(argb,8,8,3)color(1,0.53,0.12,1)";
			text = "Orange";
		};
		class ColYellow
		{
			texture = "#(argb,8,8,3)color(1,1,0,1)";
			text = "Yellow";
		};
		class ColGreen
		{
			texture = "#(argb,8,8,3)color(0,1,0,1)";
			text = "Green";
		};
		class ColAqua
		{
			texture = "#(argb,8,8,3)color(0,1,1,1)";
			text = "Aqua";
		};
		class ColBlue
		{
			texture = "#(argb,8,8,3)color(0,0,1,1)";
			text = "Blue";
		};
		class ColPurple
		{
			texture = "#(argb,8,8,3)color(0.75,0,0.75,1)";
			text = "Purple";
		};
		class ColGrey
		{
			texture = "#(argb,8,8,3)color(0.3,0.3,0.3,1)";
			text = "Grey";
		};
		class ColBlack
		{
			texture = "#(argb,8,8,3)color(0,0,0,1)";
			text = "Black";
		};
	};
	class MPTable
	{
		color[] = {0.7,0.7,0.7,1};
		colorTitleBg[] = {0.1,0.15,0.15,1};
		colorBg[] = {0.1,0.15,0.1,0.9};
		colorSelected[] = {0.7,0.7,0.7,0.4};
		colorWest[] = {0.7,0.95,0.7,1};
		colorEast[] = {0.95,0.7,0.7,1};
		colorCiv[] = {0.8,0.8,0.8,1};
		colorRes[] = {0.7,0.7,0.95,1};
		font = "TahomaB";
		size = "( 21 / 408 )";
		shadow = 0;
		class Columns
		{
			class Order
			{
				width = 0.046;
				colorBg[] = {0.1,0.27,0.1,0.8};
				doubleLine = 0;
			};
			class Player
			{
				width = 0.25;
				colorBg[] = {0.1,0.23,0.1,0.8};
				doubleLine = 1;
			};
			class KillsInfantry
			{
				width = 0.11;
				doubleLine = 0;
				colorBg[] = {0.1,0.15,0.1,0.8};
				picture = "#(argb,8,8,3)color(1,1,1,1)";
			};
			class KillsSoft
			{
				width = 0.1;
				doubleLine = 0;
				colorBg[] = {0.1,0.15,0.1,0.8};
				picture = "#(argb,8,8,3)color(1,1,1,1)";
			};
			class KillsArmor
			{
				width = 0.11;
				doubleLine = 0;
				colorBg[] = {0.1,0.15,0.1,0.8};
				picture = "#(argb,8,8,3)color(1,1,1,1)";
			};
			class KillsAir
			{
				width = 0.1;
				doubleLine = 1;
				colorBg[] = {0.1,0.15,0.1,0.8};
				picture = "#(argb,8,8,3)color(1,1,1,1)";
			};
			class Killed
			{
				width = 0.1;
				doubleLine = 1;
				colorBg[] = {0.1,0.15,0.1,0.8};
				picture = "#(argb,8,8,3)color(1,1,1,1)";
			};
			class KillsTotal
			{
				width = 0.1;
				doubleLine = 0;
				colorBg[] = {0.1,0.35,0.1,0.9};
				picture = "#(argb,8,8,3)color(1,1,1,1)";
			};
		};
	};
	class TankDirection
	{
		left = 0.035;
		top = 0.16;
		width = 0.18;
		height = 0.26;
		color[] = {0.8,0.8,0.8,1};
		colorHalfDammage[] = {0.8,0.6,0.0,1};
		colorFullDammage[] = {0.7,0.1,0.0,1};
		imageTower = "#(argb,8,8,3)color(1,1,1,1)";
		imageTurret = "#(argb,8,8,3)color(0,0,0,1)";
		imageGun = "#(argb,8,8,3)color(0.3,0.3,0.3,1)";
		imageObsTurret = "#(argb,8,8,3)color(1,0,0,1)";
		imageEngine = "#(argb,8,8,3)color(0,1,0,1)";
		imageHull = "#(argb,8,8,3)color(0,0,1,1)";
		imageLTrack = "#(argb,8,8,3)color(1,0.53,0.12,1)";
		imageRTrack = "#(argb,8,8,3)color(0,0,0,1)";
		shadow = 0;
	};
	class HelicopterHUD
	{
		shadow = 0;
		font = "TahomaB";
		SizeExNormal = 0.035;
		SizeExSmall = 0.02;
		attitudeElemmentsSize = 0.1;
		attitudeFOV = 1.04719;
		analogueSpeedAngleOffset = 2.094395;
		analogueAltitudeAngleOffset = 2.094395;
		analogueSpeedAngleRange = 5.934119;
		analogueAltitudeAngleRange = 5.934119;
		HUDLimitsColor[] = {0.0,0.6,0.0,1};
		color[] = {0.0,0.6,0.0,1};
		windDirection = "#(argb,8,8,3)color(0,1,0,1)";
		stabilityVector = "#(argb,8,8,3)color(0,1,0,1)";
		stabilityGrid = "#(argb,8,8,3)color(0,1,0,1)";
		axis = "#(argb,8,8,3)color(0,1,0,1)";
		indicator = "#(argb,8,8,3)color(0,1,0,1)";
		horizonAxes = "#(argb,8,8,3)color(0,1,0,1)";
		horizonVector = "#(argb,8,8,3)color(0,1,0,1)";
		horizonAircraft = "#(argb,8,8,3)color(0,1,0,1)";
		statusOff[] = {0.8,0.8,0.8,1};
		statusOn[] = {0.0,0.6,0.0,1};
		statusDamaged[] = {0.8,0.6,0.0,1};
		statusDestroyed[] = {0.7,0.1,0.0,1};
	};
	class FLIRModeNames
	{
		FLIRModeName[] = {"WHOT","BHOT","HOT","HOT","RBHOT","BRHOT"};
	};
	class Capture
	{
		colorBackground[] = {0,0,0,0.93};
		colorText[] = {0.8,0.6,0.0,1};
		colorLine[] = {0.8,0.8,0.8,1};
		shadow = 0;
	};
	class Picture
	{
		color[] = {0.8,0.8,0.8,1};
		colorProblems[] = {0.7,0.1,0.0,1};
		imageBusy = "#(argb,8,8,3)color(1,1,1,1)";
		imageWaiting = "#(argb,8,8,3)color(1,1,1,1)";
		imageCommand = "#(argb,8,8,3)color(1,1,1,1)";
		shadow = 0;
	};
	class Bar
	{
		imageBar = "#(argb,8,8,3)color(1,1,1,1)";
		colorBackground[] = {0.1,0.4,0.1,0.7};
		colorGreen[] = {0.0,0.6,0.0,1.0};
		colorYellow[] = {0.8,0.6,0.0,1.0};
		colorRed[] = {0.7,0.1,0.0,0.9};
		colorBlinkOn[] = {1,0.2,0.2,1};
		colorBlinkOff[] = {0.7,0.1,0.0,0.9};
		height = 0.01;
		shadow = 0;
	};
	class ProgressFont
	{
		font = "TahomaB";
		size = "( 21 / 408 )";
		shadow = 0;
	};
	class DebugFont
	{
		font = "LucidaConsoleB";
		size = 0.02;
	};
	class CheatXFont
	{
		font = "LucidaConsoleB";
		size = 0.0378;
	};
	class FadeFont
	{
		font = "LucidaConsoleB";
		size = 0.0378;
		shadow = 0;
	};
	class DragAndDropFont
	{
		font = "TahomaB";
		size = "( 16 / 408 )";
		colorEnabled[] = {0.8,0.8,0.8,0.75};
		colorDisabled[] = {0.7,0.1,0.0,0.75};
		hideCursor = 0;
		shadow = 0;
	};
	class TooltipFont
	{
		font = "TahomaB";
		size = "( 16 / 408 )";
		shadow = 0;
	};
	class Compass
	{
		left = 0.0;
		top = 0.0;
		width = 1.0;
		height = 0.04;
		color[] = {0.8,0.8,0.8,1};
		dirColor[] = {0.8,0.8,0.8,1};
		turretDirColor[] = {0.8,0.6,0.0,1};
		texture0 = "#(argb,8,8,3)color(1,1,1,1)";
		texture90 = "#(argb,8,8,3)color(1,1,1,1)";
		texture180 = "#(argb,8,8,3)color(1,1,1,1)";
		texture270 = "#(argb,8,8,3)color(1,1,1,1)";
		shadow = 0;
	};
	class PlayerInfo
	{
		top = 0.02;
		class HealthBar
		{
			stallWarning = 0.2;
		};
		dimmStartTime = 5;
		dimmEndTime = 10;
	};
	class Hint
	{
		dimmStartTime = 30;
		dimmEndTime = 35;
		sound[] = {"",0.31622776,1};
	};
	class TaskHint
	{
		dimmStartTime = 1;
		dimShowTime = 4;
		dimmEndTime = 5;
	};
	class Chat
	{
		sound[] = {"",0.31622776,1};
	};
	class Actions
	{
		font = "TahomaB";
		size = "( 16 / 408 )";
		right = 1.0;
		bottom = 0.81;
		rows = 4;
		arrowWidth = 0.0225;
		arrowHeight = 0.03;
		iconArrowUp = "#(argb,8,8,3)color(1,1,1,1)";
		iconArrowDown = "#(argb,8,8,3)color(1,1,1,1)";
		colorBackground[] = {0.2,0.15,0.1,0.8};
		colorBackgroundSelected[] = {0,0,0,0};
		colorText[] = {0.8,0.8,0.8,1};
		colorSelect[] = {0.2,0.8,0.2,1};
		background = "#(argb,8,8,3)color(0,0,0,1)";
		underlineSelected = 1;
		shadow = 0;
	};
	class DefaultAction
	{
		showHint = 1;
		showNext = 1;
		showLine = 1;
		font = "TahomaB";
		size = "( 21 / 408 )";
		fontNext = "TahomaB";
		sizeNext = "( 16 / 408 )";
		offsetX = 0;
		offsetY = 0;
		relativeToCursor = 1;
		hotspotX = 0.0;
		hotspotY = 0.0;
		colorText[] = {1,1,1,1};
		background = "#(argb,8,8,3)color(0,0,0,0)";
		shadow = 0;
		textTipFade = 1;
		textTipDelay = 1.5;
	};
	class GroupInfo
	{
		imageDefaultWeapons = "#(argb,8,8,3)color(1,1,1,1)";
		imageNoWeapons = "#(argb,8,8,3)color(1,1,1,1)";
	};
	class ConnectionLost
	{
		left = 0.0;
		top = 0.45;
		width = 1.0;
		height = 0.1;
		font = "TahomaB";
		size = "( 16 / 408 )";
		color[] = {1.0,0.5,0.25,1.0};
		shadow = 0;
	};
	class Cursor
	{
		aim = "#(argb,8,8,3)color(1,1,1,1)";
		weapon = "#(argb,8,8,3)color(1,1,1,1)";
		freelook = "#(argb,8,8,3)color(1,1,1,1)";
		outArrow = "#(argb,8,8,3)color(1,1,1,1)";
		select_target = "#(argb,8,8,3)color(1,1,1,1)";
		known_target = "#(argb,8,8,3)color(1,1,1,1)";
		lock_target = "#(argb,8,8,3)color(1,1,1,1)";
		gunner_lock = "#(argb,8,8,3)color(1,1,1,1)";
		dimmCmdStartTime = 5;
		dimmCmdEndTime = 10;
		mission = "#(argb,8,8,3)color(1,1,1,1)";
		missionFade = 0.3;
		missionColor1[] = {0.8,0.6,0.0,0.5};
		missionColor2[] = {0.8,0.6,0.0,1.0};
		customMark = "#(argb,8,8,3)color(1,0.53,0.12,1)";
		customMarkColor[] = {0.8,0.8,0.8,1.0};
		blinkingPeriod = 2.0;
		freeLookActionColor[] = {0.7,0.1,0.0,1.0};
		freeLookActionColorSelected[] = {0.0,0.6,0.0,1.0};
		freeLookActionColorAvailable[] = {0.1,0.1,0.9,1.0};
		shadow = 0;
		infoTextShadow = 0;
		font = "TahomaB";
		size = "( 16 / 408 )";
		tactical = "#(argb,8,8,3)color(1,1,1,1)";
		move = "#(argb,8,8,3)color(1,1,1,1)";
		color[] = {0.8,0.8,0.8,1};
		colorBackground[] = {0,0,0,0.65};
		colorLocked[] = {0.7,0.1,0.0,1};
		dimm = 0.15;
		activeWidth = 0.1875;
		activeHeight = 0.25;
		activeMinimum = 0.07;
		activeMaximum = 0.12;
		throwCursorMinScale = 1;
		throwCursorMaxScale = 2;
		throwCursorFadeSpeed = 4;
	};
	class PeripheralVision
	{
		cueTexture = "#(argb,8,8,3)color(1,1,1,1)";
		bloodTexture = "#(argb,8,8,3)color(1,1,1,1)";
		bloodColor[] = {0.8,0.1,0.15,1};
		cueColor[] = {1,1,1,0.7};
		cueEnemyColor[] = {1,0.3,0.3,1};
		cueFriendlyColor[] = {0.5,1,0.5,0.7};
		shadow = 0;
	};
	class HitZones
	{
		hitZonesTexture = "#(argb,8,8,3)color(1,1,1,1)";
		shadow = 0;
	};
};
class CfgDiary
{
	class FixedPages
	{
		class Tasks
		{
			type = "DiaryPageTasks";
			displayName = "$STR_LOGSUBJECT_BRIEFING";
			picture = "#(argb,8,8,3)color(1,1,1,1)";
			shortcuts[] = {};
			showEmpty = 0;
			indexTitle = "%TASK_DESCRIPTION_SHORT";
			indexIcon = "%ICON_TASK_STATE";
			recordTitle = "%DATE, %TIME";
			text = "%TASK_DESCRIPTION %LINK_SET_CURRENT_TASK";
		};
		class Diary
		{
			type = "DiaryPageDiary";
			displayName = "$STR_LOGSUBJECT_DIARY";
			picture = "#(argb,8,8,3)color(1,1,1,1)";
			shortcuts[] = {};
			showEmpty = 0;
			indexTitle = "%TITLE";
			indexIcon = "";
			recordTitle = "%DATE, %TIME";
			text = "%TEXT";
		};
		class Conversation
		{
			type = "DiaryPageConversation";
			displayName = "$STR_LOGSUBJECT_CONVERSATION";
			picture = "#(argb,8,8,3)color(1,1,1,1)";
			shortcuts[] = {};
			showEmpty = 0;
			indexTitle = "%UNIT_NAME";
			indexIcon = "";
			recordTitle = "%TARGET_NAME";
			text = "%TEXT";
		};
		class Units
		{
			type = "DiaryPageUnits";
			displayName = "$STR_DISP_SRVSETUP_UNITS";
			picture = "#(argb,8,8,3)color(1,1,1,1)";
			shortcuts[] = {};
			showEmpty = 0;
			indexTitle = "%UNIT_NAME";
			indexIcon = "%ICON_UNIT_TYPE";
			recordTitle = "%UNIT_NAME";
			text = "%UNIT_GRP_NAME %UNIT_ID%UNIT_GRP_LEADER<br/>%$STR_GEAR_VEHICLE %UNIT_VEH_NAME %UNIT_VEH_POSITION<br/><br/>%LINK_UNIT_GEAR%LINK_UNIT_TEAMSWITCH%LINK_UNIT_CONVERSATION";
			skill = " - %SKILL_NAME ... %SKILL_LEVEL<br/>";
		};
		class Players
		{
			type = "DiaryPagePlayers";
			displayName = "$STR_LOGSUBJECT_PLAYERS";
			picture = "#(argb,8,8,3)color(1,1,1,1)";
			shortcuts[] = {};
			showEmpty = 0;
			indexTitle = "%PLAYER_NAME";
			indexIcon = "%ICON_PLAYERS_STATE";
			recordTitle = "%PLAYER_NAME";
			text = "%$STR_DISP_MP_PL_NAME %PLAYER_FULLNAME<br/>%$STR_DISP_MP_PL_MAIL %PLAYER_EMAIL<br/>%$STR_DISP_MP_PL_ICQ %PLAYER_ICQ<br/>%$STR_DISP_MP_PL_REMARK %PLAYER_REMARK<br/><br/>%$STR_DISP_MP_PING %PLAYER_PING_MIN %PLAYER_PING_AVG %PLAYER_PING_MAX<br/>%$STR_DISP_MP_BANDWIDTH %PLAYER_BANDWIDTH_MIN %PLAYER_BANDWIDTH_AVG %PLAYER_BANDWIDTH_MAX<br/>%$STR_DISP_MP_DESYNC %PLAYER_DESYNC<br/><br/>%PLAYER_SQUAD<br/>%LINK_PLAYER_KICK%LINK_PLAYER_BAN%LINK_PLAYER_MUTE";
			squad = "%$STR_DISP_MP_SQ<br/>  %$STR_DISP_MP_SQ_NAME %SQUAD_NAME<br/>  %$STR_DISP_MP_SQ_ID %SQUAD_ID<br/>  %$STR_DISP_MP_SQ_MAIL %SQUAD_EMAIL<br/>  %$STR_DISP_MP_SQ_WEB %SQUAD_WEB<br/>  <img image width=80 height=80 image='%SQUAD_PICTURE'><br/>%SQUAD_TITLE";
		};
		class Statistics
		{
			type = "DiaryPageStatistics";
			displayName = "$STR_LOGSUBJECT_STATISTICS";
			picture = "#(argb,8,8,3)color(1,1,1,1)";
			shortcuts[] = {};
			showEmpty = 0;
			indexTitle = "%$STR_LOGSUBJECT_STATISTICS";
			indexIcon = "";
			recordTitle = "%$STR_STAT_MISSION";
			text = "%$STR_BRIEF_YOURKILLS<br/>%STAT_KILLS_ENEMY<br/>%$STR_BRIEF_YOURKILLS_FRIENDLY<br/>%STAT_KILLS_FRIENDLY<br/>%$STR_BRIEF_YOURKILLS_CIVIL<br/>%STAT_KILLS_CIVIL%<br/>%$STR_BRIEF_CASUALTIES<br/>%STAT_CASUALTIES";
			killsOnce = "  %NAME<br/>";
			kills = "  %COUNT x %NAME<br/>";
			casualtiesPlayerTotalOnce = "  You (%NAME)<br/>";
			casualtiesPlayerTotal = "  %COUNT x you (%NAME)<br/>";
			casualtiesPlayerOnce = "  - by %NAME<br/>";
			casualtiesPlayer = "  - %COUNT x by %NAME<br/>";
			casualtiesOnce = "  %NAME<br/>";
			casualties = "  %COUNT x %NAME<br/>";
		};
	};
	class Icons
	{
		unitNone = "#(argb,8,8,3)color(0,0,0,0)";
		unitGroup = "#(argb,8,8,3)color(0,1,0,1)";
		unitPlayable = "#(argb,8,8,3)color(1,0,0,1)";
		unitGroupPlayable = "#(argb,8,8,3)color(1,0.53,0.12,1)";
		taskNone = "#(argb,8,8,3)color(0,0,0,0)";
		taskCreated = "#(argb,8,8,3)color(0,0,0,1)";
		taskAssigned = "#(argb,8,8,3)color(1,1,1,1)";
		taskSucceeded = "#(argb,8,8,3)color(0,1,0,1)";
		taskFailed = "#(argb,8,8,3)color(1,0,0,1)";
		taskCanceled = "#(argb,8,8,3)color(1,0.53,0.12,1)";
		playerWest = "#(argb,8,8,3)color(0,0,1,1)";
		playerEast = "#(argb,8,8,3)color(1,0,0,1)";
		playerCiv = "#(argb,8,8,3)color(1,1,1,1)";
		playerGuer = "#(argb,8,8,3)color(0,1,0,1)";
		playerUnknown = "#(argb,8,8,3)color(0,0,0,1)";
		playerBriefWest = "#(argb,8,8,3)color(0,0,1,1)";
		playerBriefEast = "#(argb,8,8,3)color(1,0,0,1)";
		playerBriefGuer = "#(argb,8,8,3)color(0,1,0,1)";
		playerBriefCiv = "#(argb,8,8,3)color(1,1,1,1)";
		playerBriefUnknown = "#(argb,8,8,3)color(0,0,0,1)";
		playerConnecting = "#(argb,8,8,3)color(0,0,0,1)";
	};
};
class PreloadTextures
{
	class CfgInGameUI
	{
		imageCornerElement = "*";
		class PeripheralVision
		{
			cueTexture = "\*";
			bloodTexture = "\*";
		};
		class Cursor
		{
			aim = "*";
			weapon = "*";
			select_target = "*";
			lock_target = "*";
			mission = "*";
			tactical = "*";
			move = "*";
			outArrow = "*";
		};
	};
	class CfgCloudletShapes
	{
		cloudletSmoke = "@*";
		cloudletWater = "@*";
		cloudletFire = "@*";
	};
};
class CfgMissions
{
	class Cutscenes{};
	class Missions{};
	class MPMissions{};
	class Templates{};
	class MPTemplates{};
};
pboTryEntity = "textLog ""%1""";
pboTryWeapon = "textLog ""%1""";
pboIsEntityLocked = "false";
pboIsWeaponLocked = "false";
class JoystickSchemes
{
	class Joystick1
	{
		name = "$STR_CONTROLLER_SCHEME_GENERIC_STICK";
		class ActionsMapping
		{
			keyHeliCyclicForward[] = {"0x00030000 +8+1"};
			keyHeliCyclicBack[] = {"0x00030000 +1"};
			keyHeliCyclicLeft[] = {"0x00030000 +8+0"};
			keyHeliCyclicRight[] = {"0x00030000 +0"};
			keyHeliCollectiveRaiseCont[] = {"0x00030000 +8+6"};
			keyHeliCollectiveLowerCont[] = {"0x00030000 +6"};
			keyAirBankLeft[] = {"0x00030000 +8+0"};
			keyAirBankRight[] = {"0x00030000 +0"};
			keyHeliForward[] = {"0x00030000 +8+1"};
			keyHeliBack[] = {"0x00030000 +1"};
			keySeagullUp[] = {"0x00030000 +1"};
			keySeagullDown[] = {"0x00030000 +8+1"};
			keyCarLeft[] = {"0x00030000 +8+0"};
			keyCarRight[] = {"0x00030000 +8+1"};
			keyCarForward[] = {"0x00030000 +1"};
			keyCarBack[] = {"0x00030000 +1"};
			keyVehLockTargets[] = {"0x00020000 +1"};
			keyToggleWeapons[] = {"0x00020000 +2"};
			keyDefaultAction[] = {"0x00020000 +0"};
			keyLockTargets[] = {"0x00020000 +1"};
			keyPrevAction[] = {"0x00020000 +6"};
			keyNextAction[] = {"0x00020000 +4"};
			keyAction[] = {"0x00020000 +5"};
			keyActionContext[] = {"0x00020000 +0"};
			keyActionFreeLook[] = {"0x00020000 +0"};
			keyZoomIn[] = {"0x00020000 +3"};
			keyLookLeftDown[] = {"0x00040000 +5"};
			keyLookDown[] = {"0x00040000 +4"};
			keyLookRightDown[] = {"0x00040000 +3"};
			keyLookLeft[] = {"0x00040000 +6"};
			keyLookRight[] = {"0x00040000 +2"};
			keyLookLeftUp[] = {"0x00040000 +7"};
			keyLookUp[] = {"0x00040000 +0"};
			keyLookRightUp[] = {"0x00040000 +1"};
		};
	};
	class Joystick2
	{
		name = "$STR_CONTROLLER_SCHEME_GENERIC_THROTTLE";
		class ActionsMapping
		{
			keyHeliCollectiveRaiseCont[] = {"0x00030000 +2"};
			keyHeliCollectiveLowerCont[] = {"0x00030000 +8+2"};
			keyLookLeftDown[] = {"0x00040000 +5"};
			keyLookDown[] = {"0x00040000 +4"};
			keyLookRightDown[] = {"0x00040000 +3"};
			keyLookLeft[] = {"0x00040000 +6"};
			keyLookRight[] = {"0x00040000 +2"};
			keyLookLeftUp[] = {"0x00040000 +7"};
			keyLookUp[] = {"0x00040000 +0"};
			keyLookRightUp[] = {"0x00040000 +1"};
		};
	};
	class Joystick3
	{
		name = "$STR_CONTROLLER_SCHEME_GENERIC_PEDALS";
		class ActionsMapping
		{
			keyHeliRudderLeft[] = {"0x00030000 +8+2"};
			keyHeliRudderRight[] = {"0x00030000 +2"};
		};
	};
	class Joystick4
	{
		name = "TrackIR";
		class ActionsMapping
		{
			keyLeanLeft[] = {"0x00080000 +3"};
			keyLeanRight[] = {"0x00080000 +9"};
			keyZoomContIn[] = {"0x00080000 +11"};
			keyZoomContOut[] = {"0x00080000 +5"};
			keyLookLeftCont[] = {"0x00080000 +1"};
			keyLookRightCont[] = {"0x00080000 +7"};
			keyLookDownCont[] = {"0x00080000 +0"};
			keyLookUpCont[] = {"0x00080000 +6"};
			keyLookShiftLeftCont[] = {"0x00080000 +3"};
			keyLookShiftRightCont[] = {"0x00080000 +9"};
			keyLookRollLeftCont[] = {"0x00080000 +2"};
			keyLookRollRightCont[] = {"0x00080000 +8"};
		};
	};
};
DoubleTapAndHoldActions[] = {"moveForward","moveBack","turnLeft","turnRight","moveFastForward","moveSlowForward","moveLeft","moveRight","defaultAction","tempRaiseWeapon","compass","watch","lookAround","minimap","zoomIn","zoomOut"};
class DefaultAnalogCurveDefs
{
	class MoveBack
	{
		deadZone = 0.1;
		curve[] = {"Gamma",1,4};
	};
	class MoveFastForward
	{
		deadZone = 0.1;
		curve[] = {"Gamma",1,4};
	};
	class TurnLeft
	{
		deadZone = 0.1;
		curve[] = {"Gamma",1,2};
	};
	class TurnRight
	{
		deadZone = 0.1;
		curve[] = {"Gamma",1,2};
	};
	class AimUp
	{
		deadZone = 0;
		curve[] = {"LinRampZoom",{1.0,0.2,0.05,0.99,0.8,1.0,1.8},{0.7,0.2,0.03,0.99,0.6,1.0,1.6},{0.3,0.2,0.02,0.99,0.4,1.0,1.0}};
	};
	class AimDown
	{
		deadZone = 0;
		curve[] = {"LinRampZoom",{1.0,0.2,0.05,0.99,0.8,1.0,1.8},{0.7,0.2,0.03,0.99,0.6,1.0,1.6},{0.3,0.2,0.02,0.99,0.4,1.0,1.0}};
	};
	class AimLeft
	{
		deadZone = 0;
		curve[] = {"LinRampZoom",{1.0,0.4,0.1,0.9,0.9,0.99,1.8,1.0,3.0},{0.7,0.4,0.1,0.9,0.75,0.99,1.5,1.0,2.5},{0.3,0.4,0.1,0.9,0.6,0.99,0.9,1.0,1.2}};
	};
	class AimRight
	{
		deadZone = 0;
		curve[] = {"LinRampZoom",{1.0,0.4,0.1,0.9,0.9,0.99,1.8,1.0,3.0},{0.7,0.4,0.1,0.9,0.75,0.99,1.5,1.0,2.5},{0.3,0.4,0.1,0.9,0.6,0.99,0.9,1.0,1.2}};
	};
	class AimHeadUp
	{
		deadZone = 0;
		curve[] = {"Gamma",1,2.5};
	};
	class AimHeadDown
	{
		deadZone = 0;
		curve[] = {"Gamma",1,2.5};
	};
	class AimHeadLeft
	{
		deadZone = 0;
		curve[] = {"Gamma",2,4};
	};
	class AimHeadRight
	{
		deadZone = 0;
		curve[] = {"Gamma",2,4};
	};
	class CarLeft
	{
		deadZone = 0;
		curve[] = {"Gamma",2,3};
	};
	class CarRight
	{
		deadZone = 0;
		curve[] = {"Gamma",2,3};
	};
	class CarBack
	{
		deadZone = 0;
		curve[] = {"Gamma",1,1.5};
	};
	class CarFastForward
	{
		deadZone = 0;
		curve[] = {"Gamma",1,1.5};
	};
	class CarAimUp
	{
		deadZone = 0;
		curve[] = {"LinRampZoom",{1.0,0.2,0.05,0.99,1.8,1.0,5.4},{0.7,0.2,0.03,0.99,1.2,1.0,4.8},{0.3,0.2,0.02,0.99,1.8,1.0,3.0}};
	};
	class CarAimDown
	{
		deadZone = 0;
		curve[] = {"LinRampZoom",{1.0,0.2,0.05,0.99,1.8,1.0,5.4},{0.7,0.2,0.03,0.99,1.2,1.0,4.8},{0.3,0.2,0.02,0.99,1.8,1.0,3.0}};
	};
	class CarAimLeft
	{
		deadZone = 0;
		curve[] = {"LinRampZoom",{1.0,0.4,0.1,0.9,0.9,0.99,3.6,1.0,9.0},{0.7,0.4,0.1,0.9,0.75,0.99,3.0,1.0,8.0},{0.3,0.4,0.1,0.9,0.6,0.99,1.8,1.0,5.0}};
	};
	class CarAimRight
	{
		deadZone = 0;
		curve[] = {"LinRampZoom",{1.0,0.4,0.1,0.9,0.9,0.99,3.6,1.0,9.0},{0.7,0.4,0.1,0.9,0.75,0.99,3.0,1.0,8.0},{0.3,0.4,0.1,0.9,0.6,0.99,1.8,1.0,5.0}};
	};
	class HeliUp
	{
		deadZone = 0;
		curve[] = {"Gamma",1,1.5};
	};
	class HeliDown
	{
		deadZone = 0;
		curve[] = {"Gamma",1,1.5};
	};
	class HeliCyclicLeft
	{
		deadZone = 0;
		curve[] = {"Gamma",1,1.5};
	};
	class HeliCyclicRight
	{
		deadZone = 0;
		curve[] = {"Gamma",1,1.5};
	};
	class HeliRudderLeft
	{
		deadZone = 0;
		curve[] = {"Gamma",1,1.5};
	};
	class HeliRudderRight
	{
		deadZone = 0;
		curve[] = {"Gamma",1,1.5};
	};
	class HeliBack
	{
		deadZone = 0;
		curve[] = {"Gamma",1,1.5};
	};
	class HeliFastForward
	{
		deadZone = 0;
		curve[] = {"Gamma",1,1.5};
	};
	class SeagullUp
	{
		deadZone = 0;
		curve[] = {"Gamma",1,1.5};
	};
	class SeagullDown
	{
		deadZone = 0;
		curve[] = {"Gamma",1,1.5};
	};
	class SeagullBack
	{
		deadZone = 0;
		curve[] = {"Gamma",1,1.5};
	};
	class SeagullFastForward
	{
		deadZone = 0;
		curve[] = {"Gamma",1,1.5};
	};
};
class DefaultMouseCurveDefs{};
class CfgFaceWounds
{
	access = 1;
	wounds[] = {"xicht_a.paa","xicht_a_zranen","xicht_b.paa","xicht_a_zranen","xicht_c.paa","xicht_a_zranen","xicht_d.paa","xicht_a_zranen","xicht_e.paa","xicht_e_zranen","xicht_f.paa","xicht_a_zranen","xicht_g.paa","xicht_a_zranen","xicht_h.paa","xicht_a_zranen","xicht_i.paa","xicht_a_zranen","xicht_j.paa","xicht_a_zranen","xicht_k.paa","xicht_a_zranen","xicht_l.paa","xicht_a_zranen","xicht_m.paa","xicht_a_zranen","xicht_n.paa","xicht_a_zranen","xicht_o.paa","xicht_o_zranen","xicht_p.paa","xicht_a_zranen","xicht_q.paa","xicht_a_zranen","xicht_r.paa","xicht_a_zranen","xicht_s.paa","xicht_a_zranen","xicht_t.paa","xicht_a_zranen","xicht_u.paa","xicht_a_zranen","xicht_v.paa","xicht_v_zranen","xicht_w.paa","xicht_w_zranen","xicht_x.paa","xicht_a_zranen","xicht_y.paa","xicht_a_zranen","xicht_z.paa","xicht_a_zranen","xicht_2a.paa","xicht_a_zranen","xicht_2b.paa","xicht_w_zranen","xicht_2c.paa","xicht_a_zranen","xicht_2d.paa","xicht_v_zranen","xicht_2e.paa","xicht_a_zranen","xicht_2f.paa","xicht_a_zranen","xicht_2g.paa","xicht_w_zranen","xicht_2h.paa","xicht_a_zranen","xicht_2i.paa","xicht_a_zranen","xicht_2j.paa","xicht_a_zranen","xicht_2k.paa","xicht_a_zranen","xicht_2l.paa","xicht_a_zranen","xicht_2m.paa","xicht_a_zranen","xicht_2n.paa","xicht_a_zranen","xicht_2o.paa","xicht_a_zranen","xicht_2p.paa","xicht_2p_zranen","xicht_2q.paa","xicht_a_zranen","xicht_2r.paa","xicht_e_zranen","xicht_2s.paa","xicht_a_zranen","xicht_2t.paa","xicht_a_zranen","xicht_2u.paa","xicht_a_zranen","xicht_2v.paa","xicht_a_zranen","xicht_2w.paa","xicht_w_zranen","xicht_2x.paa","xicht_a_zranen","xicht_2y.paa","xicht_a_zranen","xicht_2z.paa","xicht_a_zranen","\o\char\faceR01.paa","\o\char\faceR01_d.pac","\o\misc\eva.pac","\o\misc\eva_d.pac","\o\misc\kamila.pac","\o\misc\kamila_d.pac","\o\misc\lada.pac","\o\misc\lada_d.pac","\o\misc\lucie.pac","\o\misc\lucie_d.pac","\o\misc\marketa.pac","\o\misc\marketa_d.pac","\o\misc\nada.pac","\o\misc\nada_d.pac","armstrong_hh.pac","armstrong_hi.pac","blake_hh.pac","blake_hi.pac","gastovski_hh.pac","gastovski_hh.pac","geronimo_hh.pac","geronimo_hi.pac","gray_beard_hh.pac","gray_beard_hi.pac","guba_hh.pac","guba_hi.pac","mr_black_hh.pac","mr_black_hi.pac","troska_hh.pac","troska_hi.pac","Adam_hh.pac","blackhair_shaved_HI.pac","Andrew_hh.pac","brown_shaved_HI.pac","Andy_hh.pac","brown_shaved_HI.pac","Armstrong_HH.pac","armstrong_HI.pac","Baldhead_hh.pac","baldhead_oholen_HI.pac","Bart_hh.pac","blackhair_shaved_HI.pac","Black_beard_hh.pac","blackhair_beard_HI.pac","Black_shaved_hh.pac","blackhair_shaved_HI.pac","Blake_hh.pac","blake_HI.pac","Brown_beard_hh.pac","brown_shaved_HI.pac","Brown_Shaved_hh.pac","brown_shaved_HI.pac","Bud_beard_hh.pac","blackhair_fullbea_HI.pac","Earl_black_hh.pac","blackhair_shaved_HI.pac","Earl_brown_hh.pac","brown_shaved_HI.pac","George_black_hh.pac","baldhead_oholen_HI.pac","George_brown_hh.pac","brown_shaved_HI.pac","Gray_beard_hh.pac","gray_beard_HI.pac","Charles_black_hh.pac","blackhair_shaved_HI.pac","Charles_gray_hh.pac","gray_shaved_HI.pac","Charles_scar_hh.pac","brown_shaved_HI.pac","Jack_brown_hh.pac","brown_shaved_HI.pac","Jack_gray_hh.pac","gray_shaved_HI.pac","John_hh.pac","blackhair_fullbea_HI.pac","Joris_HH.pac","baldhead_oholen_HI.pac","Luke_hh.pac","blackhair_beard_HI.pac","MarekPetr_HH.pac","baldhead_unshaved_HI.pac","mareks_hh.pac","baldhead_oholen_HI.pac","MarekTomas_HH.pac","blackhair_shaved_HI.pac","Markus_hh.pac","blackhair_beard_HI.pac","Michael_hh.pac","blackhair_fullbea_HI.pac","Mr_Black_HH.pac","Mr_Black_HI.pac","Newman_black_hh.pac","blackhair_shaved_HI.pac","Newman_shaved_hh.pac","baldhead_oholen_HI.pac","Pete_brown_hh.pac","brown_shaved_HI.pac","Peterp_hh.pac","baldhead_unshaved_HI.pac","PetrxMarek_HH.pac","baldhead_oholen_HI.pac","Rasta_face_HH.paa","baldhead_beard_HI.pac","Rasta_face_HH.pac","baldhead_beard_HI.pac","Sebastian_bird_hh.pac","baldhead_oholen_HI.pac","Sebastian_black_hh.pac","blackhair_shaved_HI.pac","Tom_hh.pac","blackhair_shaved_HI.pac","Tomas_HH.pac","blackhair_beard_HI.pac","TomasMarek_HH.pac","baldhead_oholen_HI.pac","Troska_hh.pac","troska_HI.pac","Waldez_hh.pac","brown_shaved_HI.pac","Young_beaver_hh.pac","blackhair_shaved_HI.pac"};
};
class CfgFaces
{
	class Default
	{
		class Default
		{
			name = "";
			head = "";
			material = "";
			texture = "#(rgb,8,8,3)color(0.5,0.5,1,1)";
			east = 0;
			west = 0;
			identityTypes[] = {"Default"};
		};
		class Custom
		{
			name = "";
			head = "";
			material = "";
			texture = "#(rgb,8,8,3)color(1,1,1,1)";
			front = "#(rgb,8,8,3)color(1,1,1,1)";
			side = "#(rgb,8,8,3)color(1,1,1,1)";
			back = "#(rgb,8,8,3)color(1,1,1,1)";
			east = 0;
			west = 0;
			identityTypes[] = {};
		};
	};
};
class CfgEnvSounds
{
	class Default
	{
		name = "$STR_CFG_ENVSOUNDS_DEFAULT";
		sound[] = {"$DEFAULT$",0,1};
		soundNight[] = {"$DEFAULT$",0,1};
	};
	class Rain
	{
		name = "";
		sound[] = {"",0.0017782794,1};
		volume = "rain";
	};
	class Sea
	{
		name = "";
		sound[] = {"",0.00031622776,1};
		volume = "sea";
	};
	class Meadows
	{
		name = "";
		sound[] = {"",5.6234134e-005,1};
		volume = "meadow*(1-rain)*(1-night)";
	};
	class Trees
	{
		name = "";
		sound[] = {"",0.00017782794,1};
		volume = "trees*(1-rain)*(1-night)";
	};
	class MeadowsNight
	{
		name = "";
		sound[] = {"",5.6234134e-005,1};
		volume = "meadow*(1-rain)*night";
	};
	class TreesNight
	{
		name = "";
		sound[] = {"",0.00017782794,1};
		volume = "trees*(1-rain)*night";
	};
	class Hills
	{
		name = "";
		sound[] = {"",0.00017782794,1};
		volume = "hills";
	};
	class Wind
	{
		name = "";
		sound[] = {"",0.00017782794,1};
		volume = "(1-hills)*windy*0.5";
	};
};
class CfgHQIdentities
{
	access = 0;
	class Base
	{
		name = "$STR_CFG_PAPABEAR";
		speaker = "NoVoice";
		pitch = 0.95;
	};
	class HQ
	{
		name = "$STR_CFG_PAPABEAR";
		speaker = "NoVoice";
		pitch = 1.05;
	};
	class PAPA_BEAR
	{
		name = "$STR_CFG_PAPABEAR";
		speaker = "NoVoice";
		pitch = 1.05;
	};
	class AirBase
	{
		name = "$STR_CFG_FIREFLYBASE";
		speaker = "NoVoice";
		pitch = 1.05;
	};
};
class CfgHeads
{
	access = 1;
	class Air
	{
		friction = 10;
		movement = 160;
		maxAmp = 0.05;
		maxSpeed = 3;
		radius = 0.2;
	};
	class Land
	{
		friction = 20;
		movement = 260;
		maxAmp = 0.1;
		maxSpeed = 4;
		radius = 0.3;
	};
};
class CfgSounds
{
	access = 1;
};
class CfgSoundSets
{
	access = 1;
};
class CfgSoundShaders
{
	access = 1;
};
class CfgWhistleSound
{
	sound[] = {"",1,1};
	downTime = 0.5;
	silentTime = 1;
	upTime = 4;
};
class CfgTitles
{
	access = 1;
	defaultSpeed = 1;
	defaultIn = 0.5;
	defaultTime = 10;
	defaultOut = 0.5;
	titles[] = {"Sphere","BISLogo","TVSet"};
	class Sphere
	{
		access = 0;
		name = "$STR_CFG_TITLES_SPHERE";
		model = "koule.p3d";
		duration = 5;
		camera[] = {0,0,-10};
	};
	class BISLogo
	{
		access = 0;
		name = "$STR_CFG_TITLES_BISLOGO";
		model = "bohemiaolor2.p3d";
		duration = 3;
		camera[] = {0,0,-200};
	};
	class TVSet
	{
		access = 0;
		name = "$STR_CFG_TITLES_TVSET";
		duration = 1000;
		model = "TVhi.p3d";
		camera[] = {0,0,-1.2};
	};
};
class CfgLocationTypes
{
	class Mount
	{
		name = "$STR_GETIN";
		drawStyle = "mount";
		texture = "";
		color[] = {0,0,0,1};
		size = 0;
		font = "TahomaB";
		textSize = 0.04;
		shadow = 1;
	};
	class Name
	{
		name = "$STR_NAME";
		drawStyle = "name";
		texture = "";
		color[] = {0,0,0,1};
		size = 0;
		font = "TahomaB";
		textSize = 0.04;
		shadow = 1;
	};
	class Strategic: Name
	{
		name = "Strategic key point";
		texture = "#(argb,8,8,3)color(1,1,1,1)";
		color[] = {0.25,0.4,0.2,1};
		size = 16;
		textSize = 0.05;
	};
	class StrongpointArea: Strategic
	{
		name = "Strongpoint area";
	};
	class FlatArea: Strategic
	{
		name = "Flat area";
	};
	class FlatAreaCity: FlatArea
	{
		name = "Flat area in city";
	};
	class FlatAreaCitySmall: FlatAreaCity
	{
		name = "Flat area in city - small";
	};
	class CityCenter: Strategic
	{
		name = "Center of the village/town/city";
	};
	class Airport: Strategic
	{
		name = "Airport";
		texture = "#(argb,8,8,3)color(1,1,1,1)";
		importance = 20;
	};
	class NameMarine: Name
	{
		name = "$STR_NAME_MARINE";
		color[] = {0,0.5,0.95,0.5};
		textSize = 0.05;
		importance = 3;
	};
	class NameCityCapital: Name
	{
		name = "$STR_NAME_CAPITAL";
		textSize = 0.07;
		importance = 7;
	};
	class NameCity: Name
	{
		name = "$STR_NAME_CITY";
		textSize = 0.06;
		importance = 6;
	};
	class NameVillage: Name
	{
		name = "$STR_NAME_VILLAGE";
		textSize = 0.05;
		importance = 5;
	};
	class NameLocal: Name
	{
		name = "$STR_NAME_LOCALNAME";
		color[] = {0,0,0,0.5};
		textSize = 0.05;
		importance = 4;
	};
	class Hill: Name
	{
		name = "$STR_NAME_HILL";
		drawStyle = "icon";
		texture = "#(argb,8,8,3)color(1,1,1,1)";
		color[] = {0,0,0,1};
		size = 14;
		textSize = 0.04;
		shadow = 0;
		importance = 2;
	};
	class ViewPoint: Hill
	{
		name = "$STR_NAME_VIEWPOINT";
		drawStyle = "icon";
		texture = "#(argb,8,8,3)color(1,1,1,1)";
		color[] = {0.78,0,0.05,1};
		size = 12;
		textSize = 0.04;
		shadow = 0;
		importance = 1;
	};
	class RockArea: Hill
	{
		name = "$STR_NAME_ROCKAREA";
		texture = "#(argb,8,8,3)color(1,1,1,1)";
		color[] = {0,0,0,1};
		size = 12;
		shadow = 0;
		importance = 2;
	};
	class BorderCrossing: Hill
	{
		name = "$STR_NAME_BCROSS";
		texture = "#(argb,8,8,3)color(1,1,1,1)";
		color[] = {0.78,0,0.05,1};
		size = 16;
		shadow = 0;
		importance = 1;
	};
	class VegetationBroadleaf: Hill
	{
		name = "$STR_NAME_VEGB";
		texture = "#(argb,8,8,3)color(1,1,1,1)";
		color[] = {0.25,0.4,0.2,1};
		size = 18;
		shadow = 0;
		importance = 2;
	};
	class VegetationFir: Hill
	{
		name = "$STR_NAME_VEGF";
		texture = "#(argb,8,8,3)color(1,1,1,1)";
		color[] = {0.25,0.4,0.2,1};
		size = 18;
		shadow = 0;
		importance = 2;
	};
	class VegetationPalm: Hill
	{
		name = "$STR_NAME_VEGP";
		texture = "#(argb,8,8,3)color(1,1,1,1)";
		color[] = {0.25,0.4,0.2,1};
		size = 18;
		shadow = 0;
		importance = 2;
	};
	class VegetationVineyard: Hill
	{
		name = "$STR_NAME_VEGV";
		texture = "#(argb,8,8,3)color(1,1,1,1)";
		color[] = {0.25,0.4,0.2,1};
		size = 16;
		shadow = 0;
		importance = 2;
	};
};
class CfgWorlds
{
	access = 0;
	class DefaultLighting
	{
		access = 0;
		groundReflection[] = {0.085,0.068,0.034};
		moonObjectColorFull[] = {0.9,0.9,1.0,0.7};
		moonHaloObjectColorFull[] = {0.9,0.9,1.0,0.01};
		moonsetObjectColor[] = {0.9,0.75,0.4};
		moonsetHaloObjectColor[] = {0.9,0.5,0.2};
		nightAngle = 5;
		sunSunset = 20;
		endSunset = 10;
	};
	class DefaultWorld
	{
		access = 0;
		centerPosition[] = {6400,6400,0};
		latitude = -40;
		longitude = 15;
		class EnvSounds: CfgEnvSounds{};
		cutscenes[] = {"intro"};
		class ReplaceObjects{};
		landGrid = 50;
		gridNumbersOverLines = 0;
		class Grid
		{
			offsetX = 0;
			offsetY = 0;
			class Zoom1
			{
				zoomMax = 0.1;
				format = "XY";
				formatX = "Aa";
				formatY = "00";
				stepX = 128;
				stepY = 128;
			};
			class Zoom2
			{
				zoomMax = 1e+030;
				format = "XY";
				formatX = "A";
				formatY = "0";
				stepX = 1280;
				stepY = 1280;
			};
		};
		soundMapAttenCoef = 0.01;
		class SoundMapValues
		{
			treehard = 0.03;
			treesoft = 0.03;
			bushhard = 0.0;
			bushsoft = 0.0;
			forest = 1.0;
			house = 0.3;
			church = 0.5;
		};
		startTime = "16:45";
		startDate = "17/11/2006";
		class Lighting: DefaultLighting{};
		class Weather
		{
			class LightingNew
			{
				class C_Day60
				{
					height = 0;
					overcast = 0.5;
					sunAngle = 60;
					sunOrMoon = 1;
					diffuse[] = {{1,0.87,0.85},13.8};
					diffuseCloud[] = {{1,0.87,0.85},13.8};
					bidirect[] = {0.08,0.08,0.07};
					bidirectCloud[] = {0.08,0.08,0.07};
					ambient[] = {{0.12,0.18,0.22},11.8};
					ambientCloud[] = {{0.12,0.18,0.22},11.8};
					groundReflection[] = {0.0,0.0,0.0};
					groundReflectionCloud[] = {0.0,0.0,0.0};
					sky[] = {{0.5,0.64,1},12.6};
					skyAroundSun[] = {{1.0,1.0,1.0},13.0};
					desiredLuminanceCoef = 0.72;
					desiredLuminanceCoefCloud = 0.72;
					EVMin = -2.0;
					EVMax = 1.0;
					filmGrainIntensity = 0.0;
					luminanceRectCoef = 0.0;
					luminanceRectCoefCloud = 0.0;
					rayleigh[] = {0.0,0.0,0.0};
					mie[] = {0.0,0.0,0.0};
					cloudsColor[] = {0.0,0.0,0.0};
					swBrightness = 0;
				};
			};
			class VolFog
			{
				CameraFog = 0;
				Item1[] = {0.0,0.0,0.0,0.0,0.0};
			};
			class Overcast
			{
				class Weather1
				{
					overcast = 0;
					sky = "#(argb,8,8,3)color(0.18,0,0.84,0.676)";
					skyR = "#(argb,8,8,3)color(0.18,0,0.84,0.676)";
					horizon = "#(argb,8,8,3)color(0.35,1,0.66,0.53)";
					alpha = 0;
					bright = 0.5;
					speed = 0.2;
					size = 0.2;
					height = 1.0;
					through = 1.0;
					lightingOvercast = 0;
					diffuse = 1.0;
					cloudDiffuse = 1.0;
					waves = 0.15;
				};
				class Weather2
				{
					overcast = 0.1;
					sky = "#(argb,8,8,3)color(0.18,0,0.84,0.676)";
					skyR = "#(argb,8,8,3)color(0.18,0,0.84,0.676)";
					horizon = "#(argb,8,8,3)color(0.35,1,0.66,0.53)";
					alpha = 0.3;
					size = 0.3;
					height = 0.9;
					bright = 0.5;
					speed = 0.25;
					through = 1.0;
					lightingOvercast = 0.1;
					diffuse = 1.0;
					cloudDiffuse = 0.9;
					waves = 0.22;
				};
				class Weather3
				{
					overcast = 0.4;
					sky = "#(argb,8,8,3)color(0.18,0,0.84,0.676)";
					skyR = "#(argb,8,8,3)color(0.18,0,0.84,0.676)";
					horizon = "#(argb,8,8,3)color(0.35,1,0.66,0.53)";
					alpha = 0.98;
					size = 0.5;
					height = 0.8;
					bright = 0.45;
					speed = 0.4;
					through = 0.8;
					lightingOvercast = 0.6;
					diffuse = 0.7;
					cloudDiffuse = 0.4;
					waves = 0.5;
				};
				class Weather4
				{
					overcast = 0.7;
					sky = "#(argb,8,8,3)color(0.18,0,0.84,0.676)";
					skyR = "#(argb,8,8,3)color(0.18,0,0.84,0.676)";
					horizon = "#(argb,8,8,3)color(0.35,1,0.66,0.53)";
					alpha = 0.97;
					size = 0.75;
					height = 0.75;
					bright = 0.45;
					speed = 0.7;
					through = 0.2;
					diffuse = 0.4;
					lightingOvercast = 0.9;
					cloudDiffuse = 0.75;
					waves = 0.6;
				};
				class Weather5
				{
					overcast = 1.0;
					sky = "#(argb,8,8,3)color(0.18,0,0.84,0.676)";
					skyR = "#(argb,8,8,3)color(0.18,0,0.84,0.676)";
					horizon = "#(argb,8,8,3)color(0.35,1,0.66,0.53)";
					alpha = 0.98;
					size = 0.9;
					height = 0.7;
					bright = 0.45;
					speed = 1.0;
					through = 0.0;
					diffuse = 0.2;
					cloudDiffuse = 0.95;
					waves = 0.7;
					lightingOvercast = 1.0;
				};
			};
			class ThunderboltNorm
			{
				model = "\core\default\default.p3d";
				soundSetNear[] = {"",0.31622776,1};
				soundSetFar[] = {"",0.31622776,1};
			};
			class ThunderboltHeavy
			{
				model = "\core\default\default.p3d";
				soundSetNear[] = {"",0.31622776,1};
				soundSetFar[] = {"",0.31622776,1};
			};
		};
		class Rain
		{
			texture = "core\default_co.paa";
			speed = 1;
			levels[] = {8,2};
			raindrop = "\core\default\default.p3d";
		};
		class SimulWeather
		{
			noiseTexture = "core\data\noise_raw.paa";
			numKeyframesPerDay = 48;
			windSpeedCoef = "10.0f";
			moonIrradianceCoef = "10.0f";
			fadeMaxDistanceKm = 300.0;
			fadeMaxAltitudeKm = 15.0;
			fadeNumAltitudes = 4;
			fadeNumElevations = 8;
			fadeNumDistances = 8;
			fadeEarthTest = 0;
			autoBrightness = 1;
			autoBrightnessStrength = 0.1;
			cloudGridWidth = 128;
			cloudGridLength = 128;
			cloudGridHeight = 16;
			helperGridElevationSteps = 24;
			helperGridAzimuthSteps = 15;
			helperEffectiveEarthRadius = 6378000;
			helperCurvedEarth = 1;
			helperAdjustCurvature = 0;
			helperNumLayers = 64;
			helperMaxDistance = 200000;
			helperNearCloudFade = 0.5;
			helperChurn = 10;
			cloudWidth = 60000;
			cloudLength = 60000;
			wrapClouds = 1;
			noiseResolution = 8;
			noisePeriod = 4.0;
			opticalDensity = 1.8;
			alphaSharpness = 0.15;
			selfShadowScale = 0.001;
			mieAsymmetry = 0.87;
			minimumLightElevationDegrees = 3.0;
			directLightCoef = 0.25;
			indirectLightCoef = 0.01;
			fogStart = 200000;
			fogEnd = 300000;
			class DefaultKeyframe
			{
				rayleigh[] = {0.00749,0.01388,0.02878};
				mie[] = {0.0046,0.0046,0.0046};
				haze = 1.0;
				hazeBaseKm = 1.0;
				hazeScaleKm = 0.5;
				hazeEccentricity = 0.82;
				brightnessAdjustment = 1.0;
				cloudiness = 0.5;
				cloudBaseKm = 3.2;
				cloudHeightKm = 6;
				directLight = 1.0;
				indirectLight = 1.0;
				ambientLight = 1.0;
				noiseOctaves = 3;
				noisePersistence = 0.55;
				fractalAmplitude = 2.2;
				fractalWavelength = 220.0;
				extinction = 1.8;
				diffusivity = 0.01;
			};
			class Overcast
			{
				class Weather1: DefaultKeyframe
				{
					overcast = 0.0;
					cloudiness = 0.0;
				};
				class Weather2: DefaultKeyframe
				{
					overcast = 0.2;
					cloudiness = 0.1;
				};
				class Weather3: DefaultKeyframe
				{
					overcast = 0.4;
					cloudiness = 0.2;
				};
				class Weather4: DefaultKeyframe
				{
					overcast = 0.6;
					cloudiness = 0.4;
				};
				class Weather5: DefaultKeyframe
				{
					overcast = 0.8;
					cloudiness = 0.5;
				};
				class Weather6: DefaultKeyframe
				{
					overcast = 1.0;
					cloudiness = 0.6;
				};
			};
		};
		skyTexture = "#(argb,8,8,3)color(0.18,0,0.84,0.676)";
		skyTextureR = "#(argb,8,8,3)color(0.18,0,0.84,0.676)";
		seaTexture = "#(rgb,8,8,3)color(0,0,0,1)";
		midDetailTexture = "#(rgb,1,1,1)color(0.5,0.5,0.5,1,cdt)";
		clouds[] = {"core\default\default.p3d","core\default\default.p3d","core\default\default.p3d","core\default\default.p3d"};
		noDetailDist = 50;
		fullDetailDist = 20;
		satelliteNormalBlendStart = 80;
		satelliteNormalBlendEnd = 100;
		hazeDistCoef = -1.0;
		hazeFogCoef = -1.0;
		clutterGrid = 2;
		clutterDist = 50;
		clutterRadius = 1.0;
		class DefaultClutter
		{
			affectedByWind = 0;
			scaleMin = 0.5;
			scaleMax = 1.0;
			swLighting = 1;
			noSatColor = 0;
		};
		class Clutter{};
		flareMinDistance = 1.0;
		flareMinDistanceLerp = 0.5;
		skyObject = "core\skyobject\skyobject.p3d";
		starsObject = "core\default\default.p3d";
		pointObject = "core\default\default.p3d";
		horizontObject = "core\default\default.p3d";
		haloObject = "core\default\default.p3d";
		sunObject = "core\default\default.p3d";
		rainbowObject = "core\default\default.p3d";
		moonObject = "core\default\default.p3d";
		starsIntensity = 0.01;
		envTexture = "";
		satelliteMap = "";
		layerMask = "";
		seaMaterial = "#water";
		shoreMaterial = "#shore";
		shoreFoamMaterial = "#shoreFoam";
		shoreWetMaterial = "#shoreWet";
		terrainMaterial = "#terrain";
		class Subdivision
		{
			class Fractal
			{
				rougness = 10;
				maxRoad = 0.2;
				maxTrack = 1.0;
				maxSlopeFactor = 0.05;
			};
			class WhiteNoise
			{
				rougness = 5;
				maxRoad = 0.1;
				maxTrack = 0.5;
				maxSlopeFactor = 0.025;
			};
			minY = -0.0;
			minSlope = 0.02;
		};
		class Ambient{};
	};
	initWorld = "";
};
class CfgAddons
{
	access = 1;
	class PreloadBanks{};
	class PreloadAddons{};
};
class CfgLiveStats
{
	class TrueSkill
	{
		name = "TrueSkill™ rankings";
		board = -65535;
		class Columns
		{
			class Rank
			{
				id = -1;
				name = "$STR_LIVE_STATS_RANK";
				width = 0.1;
				format = "%d.";
				align = 1;
			};
			class Gamertag
			{
				id = -2;
				name = "$STR_LIVE_STATS_NAME";
				width = 0.5;
				format = "%s";
				align = 0;
			};
			class Skill
			{
				id = 61;
				name = "TrueSkill™ rank";
				width = 0.2;
				format = "%d";
				align = 1;
			};
			class GamesPlayed
			{
				id = 62;
				name = "Games played";
				width = 0.2;
				format = "%d";
				align = 1;
			};
		};
	};
	class StandardDM
	{
		name = "Standard - Death Match";
		board = 1;
		algorithm = 2;
		dropouts = 1;
		coefWin = 10;
		coefLoose = -10;
		coefM1 = 1;
		coefS1 = 100;
		coefM2 = 1;
		coefS2 = 100;
		coefMin = 0.1;
		coefMax = 10.0;
		class Columns
		{
			class Rank
			{
				id = -1;
				name = "$STR_LIVE_STATS_RANK";
				width = 0.1;
				format = "%d.";
				align = 1;
			};
			class Gamertag
			{
				id = -2;
				name = "$STR_LIVE_STATS_NAME";
				width = 0.5;
				format = "%s";
				align = 0;
			};
			class Score
			{
				id = -3;
				name = "Score";
				width = 0.2;
				format = "%I64d";
				align = 1;
			};
			class GamesPlayed
			{
				id = 1;
				name = "Games played";
				width = 0.2;
				format = "%d";
				align = 1;
			};
		};
	};
	class StandardCTF
	{
		name = "Standard - Capture The Flag";
		board = 2;
		algorithm = 3;
		dropouts = 1;
		coefWin = 10;
		coefLoose = -10;
		coefM1 = 1;
		coefS1 = 100;
		coefM2 = 1;
		coefS2 = 100;
		coefMin = 0.1;
		coefMax = 10.0;
		coefAI = 0.5;
		class Columns
		{
			class Rank
			{
				id = -1;
				name = "$STR_LIVE_STATS_RANK";
				width = 0.1;
				format = "%d.";
				align = 1;
			};
			class Gamertag
			{
				id = -2;
				name = "$STR_LIVE_STATS_NAME";
				width = 0.5;
				format = "%s";
				align = 0;
			};
			class Score
			{
				id = -3;
				name = "Score";
				width = 0.2;
				format = "%I64d";
				align = 1;
			};
			class GamesPlayed
			{
				id = 1;
				name = "Games played";
				width = 0.2;
				format = "%d";
				align = 1;
			};
		};
	};
	class StandardFF: StandardDM
	{
		name = "Standard - Flag Fight";
		board = 3;
	};
	class StandardTeam: StandardCTF
	{
		name = "Standard - Team Mission";
		board = 4;
	};
	class StandardSControl: StandardCTF
	{
		name = "Standard - Sector Control";
		board = 5;
	};
	class StandardHold: StandardCTF
	{
		name = "Standard - Hold Location";
		board = 6;
	};
	class StandardUnknown: StandardDM
	{
		name = "Standard - Unknown";
		board = 7;
	};
	class RankedDM: StandardDM
	{
		name = "Ranked - Death Match";
		board = 8;
	};
	class RankedCTF: StandardCTF
	{
		name = "Ranked - Capture The Flag";
		board = 9;
	};
	class RankedFF: StandardFF
	{
		name = "Ranked - Flag Fight";
		board = 10;
	};
	class RankedTeam: StandardTeam
	{
		name = "Ranked - Team Mission";
		board = 11;
	};
	class RankedSControl: StandardSControl
	{
		name = "Ranked - Sector Control";
		board = 12;
	};
	class RankedHold: StandardHold
	{
		name = "Ranked - Hold Location";
		board = 13;
	};
	class RankedUnknown: StandardUnknown
	{
		name = "Ranked - Unknown";
		board = 14;
	};
};
class CfgVoiceMask
{
	class None
	{
		name = "$STR_VOICE_MASK_NONE";
		specEnergyWeight = -1;
		pitchScale = -1;
		whisperValue = -1;
		roboticValue = -1;
	};
	class Anonymous
	{
		name = "$STR_VOICE_MASK_ANONYMOUS";
		specEnergyWeight = 0.95;
		pitchScale = 0.5;
		whisperValue = 0.35;
		roboticValue = -1;
	};
	class Cartoon
	{
		name = "$STR_VOICE_MASK_CARTOON";
		specEnergyWeight = 0.1;
		pitchScale = -1;
		whisperValue = -1;
		roboticValue = -1;
	};
	class BigGuy
	{
		name = "$STR_VOICE_MASK_BIGGUY";
		specEnergyWeight = 0.9;
		pitchScale = 0.05;
		whisperValue = -1;
		roboticValue = -1;
	};
	class Child
	{
		name = "$STR_VOICE_MASK_CHILD";
		specEnergyWeight = 0.1;
		pitchScale = 0.7;
		whisperValue = -1;
		roboticValue = -1;
	};
	class Robot
	{
		name = "$STR_VOICE_MASK_ROBOT";
		specEnergyWeight = 0.5;
		pitchScale = -1;
		whisperValue = -1;
		roboticValue = 0.05;
	};
	class DarkMaster
	{
		name = "$STR_VOICE_MASK_DARKMASTER";
		specEnergyWeight = 1;
		pitchScale = 0;
		whisperValue = -1;
		roboticValue = -1;
	};
	class Whisper
	{
		name = "$STR_VOICE_MASK_WHISPER";
		specEnergyWeight = 0.5;
		pitchScale = -1;
		whisperValue = 0.01;
		roboticValue = -1;
	};
};
class CfgRumble
{
	coefEngineToLeft = "1.5*0.9";
	coefEngineToRight = "1.2*0.9";
	coefSurfaceToLeft = 0.25;
	coefSurfaceToRight = 0.45;
	coefWeaponToLeft = 4;
	coefWeaponToRight = 4;
};
class ButtonDeadZonesDefault
{
	deadZone_A[] = {64,48};
	deadZone_B[] = {64,48};
	deadZone_X[] = {64,48};
	deadZone_Y[] = {64,48};
	deadZone_Up[] = {64,48};
	deadZone_Down[] = {64,48};
	deadZone_Left[] = {64,48};
	deadZone_Right[] = {64,48};
	deadZone_Start[] = {64,48};
	deadZone_Back[] = {64,48};
	deadZone_LeftBumper[] = {64,48};
	deadZone_RightBumper[] = {64,48};
	deadZone_LeftThumb[] = {64,48};
	deadZone_RightThumb[] = {64,48};
};
class ControllerTypes
{
	class Gamepad
	{
		resource = "RscDisplayProfileController";
		hint = "$STR_XBOX_GAMEPAD";
		imageRightA = 0;
		imageRightB = 0;
		imageRightY = 0;
		imageRightX = 0;
		imageRightWhite = 0;
		imageRightBlack = 0;
		imageRightLeft = 1;
		imageRightRight = 1;
		imageRightUp = 1;
		imageRightDown = 1;
		imageRightBack = 1;
		imageRightStart = 1;
	};
	class Joystick
	{
		resource = "RscDisplayProfileControllerJoystick";
		hint = "$STR_XBOX_JOYSTICK";
		imageRightA = 0;
		imageRightB = 0;
		imageRightY = 1;
		imageRightX = 1;
		imageRightWhite = 1;
		imageRightBlack = 1;
		imageRightLeft = 1;
		imageRightRight = 1;
		imageRightUp = 1;
		imageRightDown = 1;
		imageRightBack = 0;
		imageRightStart = 0;
	};
	class Wheel
	{
		resource = "RscDisplayProfileControllerWheel";
		hint = "$STR_XBOX_WHEEL";
		imageRightA = 0;
		imageRightB = 0;
		imageRightY = 0;
		imageRightX = 0;
		imageRightWhite = 0;
		imageRightBlack = 0;
		imageRightLeft = 1;
		imageRightRight = 1;
		imageRightUp = 1;
		imageRightDown = 1;
		imageRightBack = 1;
		imageRightStart = 1;
	};
};
class ControllerSchemes
{
	defaultScheme = "Default";
	defaultSchemeMovementLeftBrakeTriggerAccTrigger = "Default";
	defaultSchemeMovementLeftBrakeTriggerAccButton = "Default";
	defaultSchemeMovementLeftBrakeButtonAccTrigger = "Default";
	defaultSchemeMovementLeftBrakeButtonAccButton = "Default";
	defaultSchemeMovementRightBrakeTriggerAccTrigger = "Default";
	defaultSchemeMovementRightBrakeTriggerAccButton = "Default";
	defaultSchemeMovementRightBrakeButtonAccTrigger = "Default";
	defaultSchemeMovementRightBrakeButtonAccButton = "Default";
	class Default
	{
		name = "$STR_XBOX_CONTROLER_SCHEME_DEFAULT";
		class Gamepad
		{
			class ButtonDeadZones: ButtonDeadZonesDefault
			{
				deadZone_LeftTrigger[] = {192,128};
				deadZone_RightTrigger[] = {80,64};
			};
			class ThumbStickDeadZones
			{
				leftX = 0.21;
				leftY = 0.23;
				rightX = 0.21;
				rightY = 0.23;
			};
			class Actions
			{
				ToggleWeapons[] = {"0x00050000 + 3"};
				DefaultAction[] = {"0x00050000 + 13"};
				ReloadMagazine[] = {"0x00050000 + 2"};
				LockTarget[] = {};
				VehLockTargets[] = {"0x00050000 + 14"};
				PrevAction[] = {"0x00050000 + 4"};
				NextAction[] = {"0x00050000 + 5"};
				Action[] = {"0x00050000 + 0"};
				MenuSelect[] = {"0x00050000 + 7"};
				MenuBack[] = {"0x00050000 + 6"};
				CancelAction[] = {"0x00050000 + 2"};
				Diary[] = {};
				ShowMap[] = {"0x00050000 + 11"};
				HideMap[] = {};
				ZoomContIn[] = {"0x00050000 + 12"};
				PersonView[] = {"0x00050000 + 9"};
				IngamePause[] = {"0x00050000 + 8"};
				Optics[] = {"0x00050000 + 15"};
				class CommandLeft
				{
					keys[] = {"0x00050000 + 20"};
					deadZone = 0;
					curveLow[] = {"Gamma",2,3.0};
					curveMedium[] = {"Gamma",2,3.0};
					curveHigh[] = {"Gamma",2,3.0};
				};
				class CommandRight
				{
					keys[] = {"0x00050000 + 16"};
					deadZone = 0;
					curveLow[] = {"Gamma",2,3.0};
					curveMedium[] = {"Gamma",2,3.0};
					curveHigh[] = {"Gamma",2,3.0};
				};
				class CommandForward
				{
					keys[] = {"0x00050000 + 17"};
					deadZone = 0;
					curveLow[] = {"Gamma",1,1.5};
					curveMedium[] = {"Gamma",1,1.5};
					curveHigh[] = {"Gamma",1,1.5};
				};
				class CommandBack
				{
					keys[] = {"0x00050000 + 21"};
					deadZone = 0;
					curveLow[] = {"Gamma",1,1.5};
					curveMedium[] = {"Gamma",1,1.5};
					curveHigh[] = {"Gamma",1,1.5};
				};
				CommandFast[] = {};
				CommandSlow[] = {};
			};
		};
		class Joystick
		{
			class ButtonDeadZones: ButtonDeadZonesDefault
			{
				deadZone_LeftTrigger[] = {192,128};
				deadZone_RightTrigger[] = {80,64};
			};
			class ThumbStickDeadZones
			{
				leftX = 0.21;
				leftY = 0.23;
				rightX = 0.21;
				rightY = 0.23;
			};
			class Actions
			{
				ToggleWeapons[] = {"0x00050000 + 3"};
				DefaultAction[] = {"0x00050000 + 0"};
				ReloadMagazine[] = {"0x00050000 + 2"};
				LookAround[] = {"0x00050000 + 15"};
				LockTarget[] = {};
				VehLockTargets[] = {"0x00050000 + 11"};
				PrevAction[] = {"0x00050000 + 4"};
				NextAction[] = {"0x00050000 + 5"};
				Action[] = {"0x00050000 + 14"};
				MenuSelect[] = {"0x00050000 + 7"};
				MenuBack[] = {"0x00050000 + 6"};
				CancelAction[] = {"0x00050000 + 2"};
				Diary[] = {"0x00050000 + 11"};
				ShowMap[] = {};
				HideMap[] = {};
				ZoomContIn[] = {"0x00050000 + 15"};
				PersonView[] = {"0x00050000 + 9"};
				IngamePause[] = {"0x00050000 + 8"};
				Optics[] = {};
				class CommandLeft
				{
					keys[] = {"0x00050000 + 22"};
					deadZone = 0;
					curveLow[] = {"Gamma",2,3.0};
					curveMedium[] = {"Gamma",2,3.0};
					curveHigh[] = {"Gamma",2,3.0};
				};
				class CommandRight
				{
					keys[] = {"0x00050000 + 18"};
					deadZone = 0;
					curveLow[] = {"Gamma",2,3.0};
					curveMedium[] = {"Gamma",2,3.0};
					curveHigh[] = {"Gamma",2,3.0};
				};
				class CommandForward
				{
					keys[] = {"0x00050000 + 13"};
					deadZone = 0;
					curveLow[] = {"Gamma",1,1.5};
					curveMedium[] = {"Gamma",1,1.5};
					curveHigh[] = {"Gamma",1,1.5};
				};
				class CommandBack
				{
					keys[] = {"0x00050000 + 12"};
					deadZone = 0;
					curveLow[] = {"Gamma",1,1.5};
					curveMedium[] = {"Gamma",1,1.5};
					curveHigh[] = {"Gamma",1,1.5};
				};
				CommandFast[] = {};
				CommandSlow[] = {};
			};
		};
		class Wheel
		{
			class ButtonDeadZones: ButtonDeadZonesDefault
			{
				deadZone_LeftTrigger[] = {192,128};
				deadZone_RightTrigger[] = {80,64};
			};
			class ThumbStickDeadZones
			{
				leftX = 0.21;
				leftY = 0.23;
				rightX = 0.21;
				rightY = 0.23;
			};
			class Actions
			{
				ToggleWeapons[] = {"0x00050000 + 3"};
				DefaultAction[] = {"0x00050000 + 10"};
				ReloadMagazine[] = {"0x00050000 + 2"};
				LookAround[] = {"0x00050000 + 11"};
				LockTarget[] = {};
				VehLockTargets[] = {};
				PrevAction[] = {"0x00050000 + 4"};
				NextAction[] = {"0x00050000 + 5"};
				Action[] = {"0x00050000 + 0"};
				MenuSelect[] = {"0x00050000 + 7"};
				MenuBack[] = {"0x00050000 + 6"};
				CancelAction[] = {"0x00050000 + 2"};
				Diary[] = {"0x00050000 + 11"};
				ShowMap[] = {};
				HideMap[] = {};
				ZoomContIn[] = {"0x00050000 + 11"};
				PersonView[] = {"0x00050000 + 9"};
				Optics[] = {};
				IngamePause[] = {"0x00050000 + 8"};
				class CommandLeft
				{
					keys[] = {"0x00050000 + 20"};
					deadZone = 0;
					curveLow[] = {"Gamma",2,3.0};
					curveMedium[] = {"Gamma",2,3.0};
					curveHigh[] = {"Gamma",2,3.0};
				};
				class CommandRight
				{
					keys[] = {"0x00050000 + 16"};
					deadZone = 0;
					curveLow[] = {"Gamma",2,3.0};
					curveMedium[] = {"Gamma",2,3.0};
					curveHigh[] = {"Gamma",2,3.0};
				};
				class CommandForward
				{
					keys[] = {"0x00050000 + 17"};
					deadZone = 0;
					curveLow[] = {"Gamma",1,1.5};
					curveMedium[] = {"Gamma",1,1.5};
					curveHigh[] = {"Gamma",1,1.5};
				};
				class CommandBack
				{
					keys[] = {"0x00050000 + 21"};
					deadZone = 0;
					curveLow[] = {"Gamma",1,1.5};
					curveMedium[] = {"Gamma",1,1.5};
					curveHigh[] = {"Gamma",1,1.5};
				};
				CommandFast[] = {};
				CommandSlow[] = {};
			};
		};
		class Vehicles
		{
			class Characters
			{
				name = "$STR_XBOX_CONTROLER_CHARACTERS";
				axisY = 0;
				class Gamepad
				{
					textDPad = "$STR_XBOX_CONTROLER_DP_MENU";
					textLThumb = "$STR_XBOX_CONTROLER_MOVEMENT";
					textLThumbUD = "$STR_XBOX_CONTROLER_LS_MOVE";
					textLThumbLR = "$STR_XBOX_CONTROLER_LS_STRAFE";
					textLThumbPS = "$STR_XBOX_CONTROLER_LS_UP";
					textRThumb = "$STR_XBOX_CONTROLER_AIM";
					textRThumbUD = "$STR_XBOX_CONTROLER_RS_UD_AIM";
					textRThumbLR = "$STR_XBOX_CONTROLER_RS_LR_AIM";
					textRThumbPS = "$STR_XBOX_CONTROLER_RS_OPTICS";
					class Actions
					{
						class MoveBack
						{
							keys[] = {"0x00050000 + 21"};
							deadZone = 0.1;
							curveLow[] = {"Gamma",1,4};
							curveMedium[] = {"Gamma",1,4};
							curveHigh[] = {"Gamma",1,4};
						};
						class MoveFastForward
						{
							keys[] = {"0x00050000 + 17"};
							deadZone = 0.1;
							curveLow[] = {"Gamma",1,4};
							curveMedium[] = {"Gamma",1,4};
							curveHigh[] = {"Gamma",1,4};
						};
						class TurnLeft
						{
							keys[] = {"0x00050000 + 20"};
							deadZone = 0.1;
							curveLow[] = {"Gamma",1,2};
							curveMedium[] = {"Gamma",1,2};
							curveHigh[] = {"Gamma",1,2};
						};
						class TurnRight
						{
							keys[] = {"0x00050000 + 16"};
							deadZone = 0.1;
							curveLow[] = {"Gamma",1,2};
							curveMedium[] = {"Gamma",1,2};
							curveHigh[] = {"Gamma",1,2};
						};
						MoveUp[] = {"0x00050000 + 14"};
						MoveDown[] = {"0x00050000 + 1"};
						class AimUp
						{
							actionNameYAxis = "AimDown";
							keys[] = {"0x00050000 + 19"};
							deadZone = 0;
							curveLow[] = {"LinRampZoom",{1.0,0.2,0.05,0.99,0.8,1.0,1.8},{0.7,0.2,0.03,0.99,0.6,1.0,1.6},{0.3,0.2,0.02,0.99,0.4,1.0,1.0}};
							curveMedium[] = {"LinRampZoom",{1.0,0.2,0.05,0.99,0.8,1.0,1.8},{0.7,0.2,0.03,0.99,0.6,1.0,1.6},{0.3,0.2,0.02,0.99,0.4,1.0,1.0}};
							curveHigh[] = {"LinRampZoom",{1.0,0.2,0.05,0.99,0.8,1.0,1.8},{0.7,0.2,0.03,0.99,0.6,1.0,1.6},{0.3,0.2,0.02,0.99,0.4,1.0,1.0}};
						};
						class AimDown
						{
							actionNameYAxis = "AimUp";
							keys[] = {"0x00050000 + 23"};
							deadZone = 0;
							curveLow[] = {"LinRampZoom",{1.0,0.2,0.05,0.99,0.8,1.0,1.8},{0.7,0.2,0.03,0.99,0.6,1.0,1.6},{0.3,0.2,0.02,0.99,0.4,1.0,1.0}};
							curveMedium[] = {"LinRampZoom",{1.0,0.2,0.05,0.99,0.8,1.0,1.8},{0.7,0.2,0.03,0.99,0.6,1.0,1.6},{0.3,0.2,0.02,0.99,0.4,1.0,1.0}};
							curveHigh[] = {"LinRampZoom",{1.0,0.2,0.05,0.99,0.8,1.0,1.8},{0.7,0.2,0.03,0.99,0.6,1.0,1.6},{0.3,0.2,0.02,0.99,0.4,1.0,1.0}};
						};
						class AimLeft
						{
							keys[] = {"0x00050000 + 22"};
							deadZone = 0;
							curveLow[] = {"LinRampZoom",{1.0,0.4,0.1,0.8,1.44,0.99,2.88,1.0,3.9},{0.7,0.4,0.1,0.8,1.2,0.99,2.4,1.0,3.25},{0.3,0.4,0.1,0.8,0.96,0.99,1.44,1.0,1.56}};
							curveMedium[] = {"LinRampZoom",{1.0,0.4,0.1,0.8,1.44,0.99,2.88,1.0,3.9},{0.7,0.4,0.1,0.8,1.2,0.99,2.4,1.0,3.25},{0.3,0.4,0.1,0.8,0.96,0.99,1.44,1.0,1.56}};
							curveHigh[] = {"LinRampZoom",{1.0,0.4,0.1,0.8,1.44,0.99,2.88,1.0,3.9},{0.7,0.4,0.1,0.8,1.2,0.99,2.4,1.0,3.25},{0.3,0.4,0.1,0.8,0.96,0.99,1.44,1.0,1.56}};
						};
						class AimRight
						{
							keys[] = {"0x00050000 + 18"};
							deadZone = 0;
							curveLow[] = {"LinRampZoom",{1.0,0.4,0.1,0.8,1.44,0.99,2.88,1.0,3.9},{0.7,0.4,0.1,0.8,1.2,0.99,2.4,1.0,3.25},{0.3,0.4,0.1,0.8,0.96,0.99,1.44,1.0,1.56}};
							curveMedium[] = {"LinRampZoom",{1.0,0.4,0.1,0.8,1.44,0.99,2.88,1.0,3.9},{0.7,0.4,0.1,0.8,1.2,0.99,2.4,1.0,3.25},{0.3,0.4,0.1,0.8,0.96,0.99,1.44,1.0,1.56}};
							curveHigh[] = {"LinRampZoom",{1.0,0.4,0.1,0.8,1.44,0.99,2.88,1.0,3.9},{0.7,0.4,0.1,0.8,1.2,0.99,2.4,1.0,3.25},{0.3,0.4,0.1,0.8,0.96,0.99,1.44,1.0,1.56}};
						};
						class AimHeadUp
						{
							actionNameYAxis = "AimHeadDown";
							keys[] = {"0x00050000 + 19"};
							deadZone = 0;
							curveLow[] = {"Gamma",6,3};
							curveMedium[] = {"Gamma",6,3};
							curveHigh[] = {"Gamma",6,3};
						};
						class AimHeadDown
						{
							actionNameYAxis = "AimHeadUp";
							keys[] = {"0x00050000 + 23"};
							deadZone = 0;
							curveLow[] = {"Gamma",6,3};
							curveMedium[] = {"Gamma",6,3};
							curveHigh[] = {"Gamma",6,3};
						};
						class AimHeadLeft
						{
							keys[] = {"0x00050000 + 22"};
							deadZone = 0;
							curveLow[] = {"Gamma",8,3};
							curveMedium[] = {"Gamma",8,3};
							curveHigh[] = {"Gamma",8,3};
						};
						class AimHeadRight
						{
							keys[] = {"0x00050000 + 18"};
							deadZone = 0;
							curveLow[] = {"Gamma",8,3};
							curveMedium[] = {"Gamma",8,3};
							curveHigh[] = {"Gamma",8,3};
						};
					};
				};
				class Joystick
				{
					textDPad = "$STR_XBOX_CONTROLER_DP_MENU";
					textLThumb = "$STR_XBOX_CONTROLER_MOVEMENT";
					textLThumbUD = "$STR_XBOX_CONTROLER_LS_MOVE";
					textLThumbLR = "$STR_XBOX_CONTROLER_RS_STRAFE";
					textLThumbPS = "$STR_XBOX_CONTROLER_RS_KNEEL";
					textRThumb = "$STR_XBOX_CONTROLER_AIM";
					textRThumbUD = "$STR_XBOX_CONTROLER_RS_UD_AIM";
					textRThumbLR = "$STR_XBOX_CONTROLER_RS_LR_AIM";
					textRThumbPS = "$STR_XBOX_CONTROLER_LS_ZOOM";
					class Actions
					{
						class MoveBack
						{
							keys[] = {"0x00050000 + 12"};
							deadZone = 0.1;
							curveLow[] = {"Gamma",1,4};
							curveMedium[] = {"Gamma",1,4};
							curveHigh[] = {"Gamma",1,4};
						};
						class MoveFastForward
						{
							keys[] = {"0x00050000 + 13"};
							deadZone = 0.1;
							curveLow[] = {"Gamma",1,4};
							curveMedium[] = {"Gamma",1,4};
							curveHigh[] = {"Gamma",1,4};
						};
						class TurnLeft
						{
							keys[] = {"0x00050000 + 22"};
							deadZone = 0.1;
							curveLow[] = {"Gamma",1,2};
							curveMedium[] = {"Gamma",1,2};
							curveHigh[] = {"Gamma",1,2};
						};
						class TurnRight
						{
							keys[] = {"0x00050000 + 18"};
							deadZone = 0.1;
							curveLow[] = {"Gamma",1,2};
							curveMedium[] = {"Gamma",1,2};
							curveHigh[] = {"Gamma",1,2};
						};
						MoveUp[] = {};
						MoveDown[] = {"0x00050000 + 1"};
						class AimUp
						{
							actionNameYAxis = "AimDown";
							keys[] = {"0x00050000 + 17"};
							deadZone = 0;
							curveLow[] = {"LinRampZoom",{1.0,0.2,0.05,0.99,0.8,1.0,1.8},{0.7,0.2,0.03,0.99,0.6,1.0,1.6},{0.3,0.2,0.02,0.99,0.4,1.0,1.0}};
							curveMedium[] = {"LinRampZoom",{1.0,0.2,0.05,0.99,0.8,1.0,1.8},{0.7,0.2,0.03,0.99,0.6,1.0,1.6},{0.3,0.2,0.02,0.99,0.4,1.0,1.0}};
							curveHigh[] = {"LinRampZoom",{1.0,0.2,0.05,0.99,0.8,1.0,1.8},{0.7,0.2,0.03,0.99,0.6,1.0,1.6},{0.3,0.2,0.02,0.99,0.4,1.0,1.0}};
						};
						class AimDown
						{
							actionNameYAxis = "AimUp";
							keys[] = {"0x00050000 + 21"};
							deadZone = 0;
							curveLow[] = {"LinRampZoom",{1.0,0.2,0.05,0.99,0.8,1.0,1.8},{0.7,0.2,0.03,0.99,0.6,1.0,1.6},{0.3,0.2,0.02,0.99,0.4,1.0,1.0}};
							curveMedium[] = {"LinRampZoom",{1.0,0.2,0.05,0.99,0.8,1.0,1.8},{0.7,0.2,0.03,0.99,0.6,1.0,1.6},{0.3,0.2,0.02,0.99,0.4,1.0,1.0}};
							curveHigh[] = {"LinRampZoom",{1.0,0.2,0.05,0.99,0.8,1.0,1.8},{0.7,0.2,0.03,0.99,0.6,1.0,1.6},{0.3,0.2,0.02,0.99,0.4,1.0,1.0}};
						};
						class AimLeft
						{
							keys[] = {"0x00050000 + 20"};
							deadZone = 0;
							curveLow[] = {"LinRampZoom",{1.0,0.4,0.1,0.8,1.44,0.99,2.88,1.0,3.9},{0.7,0.4,0.1,0.8,1.2,0.99,2.4,1.0,3.25},{0.3,0.4,0.1,0.8,0.96,0.99,1.44,1.0,1.56}};
							curveMedium[] = {"LinRampZoom",{1.0,0.4,0.1,0.8,1.44,0.99,2.88,1.0,3.9},{0.7,0.4,0.1,0.8,1.2,0.99,2.4,1.0,3.25},{0.3,0.4,0.1,0.8,0.96,0.99,1.44,1.0,1.56}};
							curveHigh[] = {"LinRampZoom",{1.0,0.4,0.1,0.8,1.44,0.99,2.88,1.0,3.9},{0.7,0.4,0.1,0.8,1.2,0.99,2.4,1.0,3.25},{0.3,0.4,0.1,0.8,0.96,0.99,1.44,1.0,1.56}};
						};
						class AimRight
						{
							keys[] = {"0x00050000 + 16"};
							deadZone = 0;
							curveLow[] = {"LinRampZoom",{1.0,0.4,0.1,0.8,1.44,0.99,2.88,1.0,3.9},{0.7,0.4,0.1,0.8,1.2,0.99,2.4,1.0,3.25},{0.3,0.4,0.1,0.8,0.96,0.99,1.44,1.0,1.56}};
							curveMedium[] = {"LinRampZoom",{1.0,0.4,0.1,0.8,1.44,0.99,2.88,1.0,3.9},{0.7,0.4,0.1,0.8,1.2,0.99,2.4,1.0,3.25},{0.3,0.4,0.1,0.8,0.96,0.99,1.44,1.0,1.56}};
							curveHigh[] = {"LinRampZoom",{1.0,0.4,0.1,0.8,1.44,0.99,2.88,1.0,3.9},{0.7,0.4,0.1,0.8,1.2,0.99,2.4,1.0,3.25},{0.3,0.4,0.1,0.8,0.96,0.99,1.44,1.0,1.56}};
						};
						class AimHeadUp
						{
							actionNameYAxis = "AimHeadDown";
							keys[] = {"0x00050000 + 17"};
							deadZone = 0;
							curveLow[] = {"Gamma",6,3};
							curveMedium[] = {"Gamma",6,3};
							curveHigh[] = {"Gamma",6,3};
						};
						class AimHeadDown
						{
							actionNameYAxis = "AimHeadUp";
							keys[] = {"0x00050000 + 21"};
							deadZone = 0;
							curveLow[] = {"Gamma",6,3};
							curveMedium[] = {"Gamma",6,3};
							curveHigh[] = {"Gamma",6,3};
						};
						class AimHeadLeft
						{
							keys[] = {"0x00050000 + 20"};
							deadZone = 0;
							curveLow[] = {"Gamma",8,3};
							curveMedium[] = {"Gamma",8,3};
							curveHigh[] = {"Gamma",8,3};
						};
						class AimHeadRight
						{
							keys[] = {"0x00050000 + 16"};
							deadZone = 0;
							curveLow[] = {"Gamma",8,3};
							curveMedium[] = {"Gamma",8,3};
							curveHigh[] = {"Gamma",8,3};
						};
					};
				};
				class Wheel
				{
					textDPad = "$STR_XBOX_CONTROLER_DP_MENU";
					textLThumb = "$STR_XBOX_CONTROLER_MOVEMENT";
					textLThumbUD = "$STR_XBOX_CONTROLER_LS_MOVE";
					textLThumbLR = "$STR_XBOX_CONTROLER_LS_STRAFE";
					textLThumbPS = "";
					textRThumb = "";
					textRThumbLR = "";
					textRThumbUD = "";
					textRThumbPS = "";
					class Actions
					{
						class MoveBack
						{
							keys[] = {"0x00050000 + 12"};
							deadZone = 0.1;
							curveLow[] = {"Gamma",1,4};
							curveMedium[] = {"Gamma",1,4};
							curveHigh[] = {"Gamma",1,4};
						};
						class MoveFastForward
						{
							keys[] = {"0x00050000 + 13"};
							deadZone = 0.1;
							curveLow[] = {"Gamma",1,4};
							curveMedium[] = {"Gamma",1,4};
							curveHigh[] = {"Gamma",1,4};
						};
						class TurnLeft
						{
							keys[] = {"0x00050000 + 20"};
							deadZone = 0;
							curveLow[] = {"Gamma",1.5,4};
							curveMedium[] = {"Gamma",1.5,4};
							curveHigh[] = {"Gamma",1.5,4};
						};
						class TurnRight
						{
							keys[] = {"0x00050000 + 16"};
							deadZone = 0;
							curveLow[] = {"Gamma",1.5,4};
							curveMedium[] = {"Gamma",1.5,4};
							curveHigh[] = {"Gamma",1.5,4};
						};
						MoveUp[] = {};
						MoveDown[] = {};
						AimUp[] = {};
						AimDown[] = {};
						AimLeft[] = {};
						AimRight[] = {};
						AimHeadUp[] = {};
						AimHeadDown[] = {};
						class AimHeadLeft
						{
							keys[] = {"0x00050000 + 20"};
							deadZone = 0;
							curveLow[] = {"Gamma",8,3};
							curveMedium[] = {"Gamma",8,3};
							curveHigh[] = {"Gamma",8,3};
						};
						class AimHeadRight
						{
							keys[] = {"0x00050000 + 16"};
							deadZone = 0;
							curveLow[] = {"Gamma",8,3};
							curveMedium[] = {"Gamma",8,3};
							curveHigh[] = {"Gamma",8,3};
						};
					};
				};
			};
			class Ground
			{
				name = "$STR_XBOX_CONTROLER_VEHICLE_GROUND";
				axisY = 0;
				class Gamepad
				{
					textDPad = "$STR_XBOX_CONTROLER_DP_MENU";
					textLThumb = "$STR_XBOX_CONTROLER_MOVEMENT";
					textLThumbUD = "$STR_XBOX_CONTROLER_LS_MOVE";
					textLThumbLR = "";
					textLThumbPS = "";
					textRThumb = "$STR_XBOX_CONTROLER_MOVEMENT";
					textRThumbUD = "";
					textRThumbLR = "$STR_XBOX_CONTROLER_RS_TURN";
					textRThumbPS = "";
					class Actions
					{
						class CarLeft
						{
							keys[] = {"0x00050000 + 22"};
							deadZone = 0;
							curveLow[] = {"Gamma",2,3.0};
							curveMedium[] = {"Gamma",2,3.0};
							curveHigh[] = {"Gamma",2,3.0};
						};
						class CarRight
						{
							keys[] = {"0x00050000 + 18"};
							deadZone = 0;
							curveLow[] = {"Gamma",2,3.0};
							curveMedium[] = {"Gamma",2,3.0};
							curveHigh[] = {"Gamma",2,3.0};
						};
						CarForward[] = {};
						class CarBack
						{
							keys[] = {"0x00050000 + 21"};
							deadZone = 0;
							curveLow[] = {"Gamma",1,1.5};
							curveMedium[] = {"Gamma",1,1.5};
							curveHigh[] = {"Gamma",1,1.5};
						};
						class CarFastForward
						{
							keys[] = {"0x00050000 + 17"};
							deadZone = 0;
							curveLow[] = {"Gamma",1,1.5};
							curveMedium[] = {"Gamma",1,1.5};
							curveHigh[] = {"Gamma",1,1.5};
						};
						CarSlowForward[] = {};
						class CarAimUp
						{
							actionNameYAxis = "CarAimDown";
							keys[] = {"0x00050000 + 19"};
							deadZone = 0;
							curveLow[] = {"LinRampZoom",{1.0,0.8,0.1,0.9,0.14,1.0,1.0},{0.7,0.8,0.08,0.9,0.12,1.0,0.8},{0.3,0.8,0.06,0.9,0.09,1.0,0.6}};
							curveMedium[] = {"LinRampZoom",{1.0,0.8,0.1,0.9,0.14,1.0,1.0},{0.7,0.8,0.08,0.9,0.12,1.0,0.8},{0.3,0.8,0.06,0.9,0.09,1.0,0.6}};
							curveHigh[] = {"LinRampZoom",{1.0,0.8,0.1,0.9,0.14,1.0,1.0},{0.7,0.8,0.08,0.9,0.12,1.0,0.8},{0.3,0.8,0.06,0.9,0.09,1.0,0.6}};
						};
						class CarAimDown
						{
							actionNameYAxis = "CarAimUp";
							keys[] = {"0x00050000 + 23"};
							deadZone = 0;
							curveLow[] = {"LinRampZoom",{1.0,0.8,0.1,0.9,0.14,1.0,1.0},{0.7,0.8,0.08,0.9,0.12,1.0,0.8},{0.3,0.8,0.06,0.9,0.09,1.0,0.6}};
							curveMedium[] = {"LinRampZoom",{1.0,0.8,0.1,0.9,0.14,1.0,1.0},{0.7,0.8,0.08,0.9,0.12,1.0,0.8},{0.3,0.8,0.06,0.9,0.09,1.0,0.6}};
							curveHigh[] = {"LinRampZoom",{1.0,0.8,0.1,0.9,0.14,1.0,1.0},{0.7,0.8,0.08,0.9,0.12,1.0,0.8},{0.3,0.8,0.06,0.9,0.09,1.0,0.6}};
						};
						class CarAimLeft
						{
							keys[] = {"0x00050000 + 22"};
							deadZone = 0;
							curveLow[] = {"LinRampZoom",{1.0,0.4,0.1,0.9,"0.90 0.99",3.6,1.0,9.0},{0.7,0.4,0.1,0.9,0.75,0.99,3.0,1.0,8.0},{0.3,0.4,0.1,0.9,0.6,0.99,1.8,1.0,5.0}};
							curveMedium[] = {"LinRampZoom",{1.0,0.4,0.1,0.9,"0.90 0.99",3.6,1.0,9.0},{0.7,0.4,0.1,0.9,0.75,0.99,3.0,1.0,8.0},{0.3,0.4,0.1,0.9,0.6,0.99,1.8,1.0,5.0}};
							curveHigh[] = {"LinRampZoom",{1.0,0.4,0.1,0.9,"0.90 0.99",3.6,1.0,9.0},{0.7,0.4,0.1,0.9,0.75,0.99,3.0,1.0,8.0},{0.3,0.4,0.1,0.9,0.6,0.99,1.8,1.0,5.0}};
						};
						class CarAimRight
						{
							keys[] = {"0x00050000 + 18"};
							deadZone = 0;
							curveLow[] = {"LinRampZoom",{1.0,0.4,0.1,0.9,"0.90 0.99",3.6,1.0,9.0},{0.7,0.4,0.1,0.9,0.75,0.99,3.0,1.0,8.0},{0.3,0.4,0.1,0.9,0.6,0.99,1.8,1.0,5.0}};
							curveMedium[] = {"LinRampZoom",{1.0,0.4,0.1,0.9,"0.90 0.99",3.6,1.0,9.0},{0.7,0.4,0.1,0.9,0.75,0.99,3.0,1.0,8.0},{0.3,0.4,0.1,0.9,0.6,0.99,1.8,1.0,5.0}};
							curveHigh[] = {"LinRampZoom",{1.0,0.4,0.1,0.9,"0.90 0.99",3.6,1.0,9.0},{0.7,0.4,0.1,0.9,0.75,0.99,3.0,1.0,8.0},{0.3,0.4,0.1,0.9,0.6,0.99,1.8,1.0,5.0}};
						};
						class AimHeadUp
						{
							actionNameYAxis = "AimHeadDown";
							keys[] = {"0x00050000 + 19"};
							deadZone = 0;
							curveLow[] = {"Gamma",6,3};
							curveMedium[] = {"Gamma",6,3};
							curveHigh[] = {"Gamma",6,3};
						};
						class AimHeadDown
						{
							actionNameYAxis = "AimHeadUp";
							keys[] = {"0x00050000 + 23"};
							deadZone = 0;
							curveLow[] = {"Gamma",6,3};
							curveMedium[] = {"Gamma",6,3};
							curveHigh[] = {"Gamma",6,3};
						};
						class AimHeadLeft
						{
							keys[] = {"0x00050000 + 22"};
							deadZone = 0;
							curveLow[] = {"Gamma",8,3};
							curveMedium[] = {"Gamma",8,3};
							curveHigh[] = {"Gamma",8,3};
						};
						class AimHeadRight
						{
							keys[] = {"0x00050000 + 18"};
							deadZone = 0;
							curveLow[] = {"Gamma",8,3};
							curveMedium[] = {"Gamma",8,3};
							curveHigh[] = {"Gamma",8,3};
						};
						SwapGunner[] = {"0x00050000 + 1"};
					};
				};
				class Joystick
				{
					textDPad = "$STR_XBOX_CONTROLER_DP_MENU";
					textLThumb = "$STR_XBOX_CONTROLER_MOVEMENT";
					textLThumbUD = "$STR_XBOX_CONTROLER_LS_MOVE";
					textLThumbLR = "";
					textLThumbPS = "";
					textRThumb = "$STR_XBOX_CONTROLER_MOVEMENT";
					textRThumbUD = "";
					textRThumbLR = "$STR_XBOX_CONTROLER_RS_TURN";
					textRThumbPS = "";
					class Actions
					{
						class CarLeft
						{
							keys[] = {"0x00050000 + 20"};
							deadZone = 0;
							curveLow[] = {"Gamma",2,3.0};
							curveMedium[] = {"Gamma",2,3.0};
							curveHigh[] = {"Gamma",2,3.0};
						};
						class CarRight
						{
							keys[] = {"0x00050000 + 16"};
							deadZone = 0;
							curveLow[] = {"Gamma",2,3.0};
							curveMedium[] = {"Gamma",2,3.0};
							curveHigh[] = {"Gamma",2,3.0};
						};
						CarForward[] = {};
						class CarBack
						{
							keys[] = {"0x00050000 + 12"};
							deadZone = 0;
							curveLow[] = {"Gamma",1,1.5};
							curveMedium[] = {"Gamma",1,1.5};
							curveHigh[] = {"Gamma",1,1.5};
						};
						class CarFastForward
						{
							keys[] = {"0x00050000 + 13"};
							deadZone = 0;
							curveLow[] = {"Gamma",1,1.5};
							curveMedium[] = {"Gamma",1,1.5};
							curveHigh[] = {"Gamma",1,1.5};
						};
						CarSlowForward[] = {};
						class CarAimUp
						{
							actionNameYAxis = "CarAimDown";
							keys[] = {"0x00050000 + 17"};
							deadZone = 0;
							curveLow[] = {"LinRampZoom",{1.0,0.8,0.1,0.9,0.14,1.0,1.0},{0.7,0.8,0.08,0.9,0.12,1.0,0.8},{0.3,0.8,0.06,0.9,0.09,1.0,0.6}};
							curveMedium[] = {"LinRampZoom",{1.0,0.8,0.1,0.9,0.14,1.0,1.0},{0.7,0.8,0.08,0.9,0.12,1.0,0.8},{0.3,0.8,0.06,0.9,0.09,1.0,0.6}};
							curveHigh[] = {"LinRampZoom",{1.0,0.8,0.1,0.9,0.14,1.0,1.0},{0.7,0.8,0.08,0.9,0.12,1.0,0.8},{0.3,0.8,0.06,0.9,0.09,1.0,0.6}};
						};
						class CarAimDown
						{
							actionNameYAxis = "CarAimUp";
							keys[] = {"0x00050000 + 21"};
							deadZone = 0;
							curveLow[] = {"LinRampZoom",{1.0,0.8,0.1,0.9,0.14,1.0,1.0},{0.7,0.8,0.08,0.9,0.12,1.0,0.8},{0.3,0.8,0.06,0.9,0.09,1.0,0.6}};
							curveMedium[] = {"LinRampZoom",{1.0,0.8,0.1,0.9,0.14,1.0,1.0},{0.7,0.8,0.08,0.9,0.12,1.0,0.8},{0.3,0.8,0.06,0.9,0.09,1.0,0.6}};
							curveHigh[] = {"LinRampZoom",{1.0,0.8,0.1,0.9,0.14,1.0,1.0},{0.7,0.8,0.08,0.9,0.12,1.0,0.8},{0.3,0.8,0.06,0.9,0.09,1.0,0.6}};
						};
						class CarAimLeft
						{
							keys[] = {"0x00050000 + 20"};
							deadZone = 0;
							curveLow[] = {"LinRampZoom",{1.0,0.4,0.1,0.9,"0.90 0.99",3.6,1.0,9.0},{0.7,0.4,0.1,0.9,0.75,0.99,3.0,1.0,8.0},{0.3,0.4,0.1,0.9,0.6,0.99,1.8,1.0,5.0}};
							curveMedium[] = {"LinRampZoom",{1.0,0.4,0.1,0.9,"0.90 0.99",3.6,1.0,9.0},{0.7,0.4,0.1,0.9,0.75,0.99,3.0,1.0,8.0},{0.3,0.4,0.1,0.9,0.6,0.99,1.8,1.0,5.0}};
							curveHigh[] = {"LinRampZoom",{1.0,0.4,0.1,0.9,"0.90 0.99",3.6,1.0,9.0},{0.7,0.4,0.1,0.9,0.75,0.99,3.0,1.0,8.0},{0.3,0.4,0.1,0.9,0.6,0.99,1.8,1.0,5.0}};
						};
						class CarAimRight
						{
							keys[] = {"0x00050000 + 16"};
							deadZone = 0;
							curveLow[] = {"LinRampZoom",{1.0,0.4,0.1,0.9,"0.90 0.99",3.6,1.0,9.0},{0.7,0.4,0.1,0.9,0.75,0.99,3.0,1.0,8.0},{0.3,0.4,0.1,0.9,0.6,0.99,1.8,1.0,5.0}};
							curveMedium[] = {"LinRampZoom",{1.0,0.4,0.1,0.9,"0.90 0.99",3.6,1.0,9.0},{0.7,0.4,0.1,0.9,0.75,0.99,3.0,1.0,8.0},{0.3,0.4,0.1,0.9,0.6,0.99,1.8,1.0,5.0}};
							curveHigh[] = {"LinRampZoom",{1.0,0.4,0.1,0.9,"0.90 0.99",3.6,1.0,9.0},{0.7,0.4,0.1,0.9,0.75,0.99,3.0,1.0,8.0},{0.3,0.4,0.1,0.9,0.6,0.99,1.8,1.0,5.0}};
						};
						SwapGunner[] = {"0x00050000 + 1"};
					};
				};
				class Wheel
				{
					textDPad = "$STR_XBOX_CONTROLER_DP_MENU";
					textLThumb = "$STR_XBOX_CONTROLER_MOVEMENT";
					textLThumbLR = "$STR_XBOX_CONTROLER_LS_STRAFE";
					textLThumbUD = "$STR_XBOX_CONTROLER_LS_MOVE";
					textLThumbPS = "";
					textRThumb = "";
					textRThumbLR = "";
					textRThumbUD = "";
					textRThumbPS = "";
					class Actions
					{
						class CarLeft
						{
							keys[] = {"0x00050000 + 20"};
							deadZone = 0;
							curveLow[] = {"Gamma",2,3.0};
							curveMedium[] = {"Gamma",2,3.0};
							curveHigh[] = {"Gamma",2,3.0};
						};
						class CarRight
						{
							keys[] = {"0x00050000 + 16"};
							deadZone = 0;
							curveLow[] = {"Gamma",2,3.0};
							curveMedium[] = {"Gamma",2,3.0};
							curveHigh[] = {"Gamma",2,3.0};
						};
						CarForward[] = {};
						class CarBack
						{
							keys[] = {"0x00050000 + 12"};
							deadZone = 0;
							curveLow[] = {"Gamma",1,1.5};
							curveMedium[] = {"Gamma",1,1.5};
							curveHigh[] = {"Gamma",1,1.5};
						};
						class CarFastForward
						{
							keys[] = {"0x00050000 + 13"};
							deadZone = 0;
							curveLow[] = {"Gamma",1,1.5};
							curveMedium[] = {"Gamma",1,1.5};
							curveHigh[] = {"Gamma",1,1.5};
						};
						CarSlowForward[] = {};
						CarAimUp[] = {};
						CarAimDown[] = {};
						class CarAimLeft
						{
							keys[] = {"0x00050000 + 20"};
							deadZone = 0;
							curveLow[] = {"Gamma",8,3};
							curveMedium[] = {"Gamma",8,3};
							curveHigh[] = {"Gamma",8,3};
						};
						class CarAimRight
						{
							keys[] = {"0x00050000 + 16"};
							deadZone = 0;
							curveLow[] = {"Gamma",8,3};
							curveMedium[] = {"Gamma",8,3};
							curveHigh[] = {"Gamma",8,3};
						};
						SwapGunner[] = {"0x00050000 + 0"};
					};
				};
			};
			class Aircraft
			{
				name = "$STR_XBOX_CONTROLER_AIR";
				axisY = 1;
				class Gamepad
				{
					textDPad = "$STR_XBOX_CONTROLER_DP_MENU";
					textLThumb = "$STR_XBOX_CONTROLER_MOVEMENT";
					textLThumbUD = "$STR_XBOX_CONTROLER_LS_FLY";
					textLThumbLR = "$STR_XBOX_CONTROLER_LS_RUDDER";
					textLThumbPS = "$STR_XBOX_CONTROLER_LS_LOCK";
					textRThumb = "$STR_XBOX_CONTROLER_MOVEMENT";
					textRThumbUD = "$STR_XBOX_CONTROLER_RS_TILT_MOVE";
					textRThumbLR = "$STR_XBOX_CONTROLER_RS_TILT";
					textRThumbPS = "";
					class Actions
					{
						class HeliCyclicBack
						{
							actionNameYAxis = "HeliCyclicForward";
							keys[] = {"0x00050000 + 17"};
							deadZone = 0;
							curveLow[] = {"Gamma",1,1.5};
							curveMedium[] = {"Gamma",1,1.5};
							curveHigh[] = {"Gamma",1,1.5};
						};
						class HeliCyclicForward
						{
							actionNameYAxis = "HeliCyclicBack";
							keys[] = {"0x00050000 + 21"};
							deadZone = 0;
							curveLow[] = {"Gamma",1,1.5};
							curveMedium[] = {"Gamma",1,1.5};
							curveHigh[] = {"Gamma",1,1.5};
						};
						class HeliCyclicLeft
						{
							keys[] = {"0x00050000 + 20"};
							deadZone = 0;
							curveLow[] = {"Gamma",1,1.5};
							curveMedium[] = {"Gamma",1,1.5};
							curveHigh[] = {"Gamma",1,1.5};
						};
						class HeliCyclicRight
						{
							keys[] = {"0x00050000 + 16"};
							deadZone = 0;
							curveLow[] = {"Gamma",1,1.5};
							curveMedium[] = {"Gamma",1,1.5};
							curveHigh[] = {"Gamma",1,1.5};
						};
						class HeliRudderLeft
						{
							keys[] = {"0x00050000 + 12"};
							deadZone = 0;
							curveLow[] = {"Gamma",1,1.5};
							curveMedium[] = {"Gamma",1,1.5};
							curveHigh[] = {"Gamma",1,1.5};
						};
						class HeliRudderRight
						{
							keys[] = {"0x00050000 + 13"};
							deadZone = 0;
							curveLow[] = {"Gamma",1,1.5};
							curveMedium[] = {"Gamma",1,1.5};
							curveHigh[] = {"Gamma",1,1.5};
						};
						class HeliCollectiveRaise
						{
							keys[] = {"0x00050000 + 11"};
							deadZone = 0;
							curveLow[] = {"Gamma",1,1.5};
							curveMedium[] = {"Gamma",1,1.5};
							curveHigh[] = {"Gamma",1,1.5};
						};
						class HeliCollectiveLower
						{
							keys[] = {"0x00050000 + 10"};
							deadZone = 0;
							curveLow[] = {"Gamma",1,1.5};
							curveMedium[] = {"Gamma",1,1.5};
							curveHigh[] = {"Gamma",1,1.5};
						};
						HeliBack[] = {};
						HeliFastForward[] = {};
						HeliForward[] = {};
						class SeagullUp
						{
							keys[] = {"0x00050000 + 17"};
							deadZone = 0;
							curveLow[] = {"Gamma",1,1.5};
							curveMedium[] = {"Gamma",1,1.5};
							curveHigh[] = {"Gamma",1,1.5};
						};
						class SeagullDown
						{
							keys[] = {"0x00050000 + 21"};
							deadZone = 0;
							curveLow[] = {"Gamma",1,1.5};
							curveMedium[] = {"Gamma",1,1.5};
							curveHigh[] = {"Gamma",1,1.5};
						};
						class SeagullBack
						{
							actionNameYAxis = "SeagullFastForward";
							keys[] = {"0x00050000 + 19"};
							deadZone = 0;
							curveLow[] = {"Gamma",1,1.5};
							curveMedium[] = {"Gamma",1,1.5};
							curveHigh[] = {"Gamma",1,1.5};
						};
						class SeagullFastForward
						{
							actionNameYAxis = "SeagullBack";
							keys[] = {"0x00050000 + 23"};
							deadZone = 0;
							curveLow[] = {"Gamma",1,1.5};
							curveMedium[] = {"Gamma",1,1.5};
							curveHigh[] = {"Gamma",1,1.5};
						};
						class AimHeadUp
						{
							actionNameYAxis = "AimHeadDown";
							keys[] = {"0x00050000 + 19"};
							deadZone = 0;
							curveLow[] = {"Gamma",6,3};
							curveMedium[] = {"Gamma",6,3};
							curveHigh[] = {"Gamma",6,3};
						};
						class AimHeadDown
						{
							actionNameYAxis = "AimHeadUp";
							keys[] = {"0x00050000 + 23"};
							deadZone = 0;
							curveLow[] = {"Gamma",6,3};
							curveMedium[] = {"Gamma",6,3};
							curveHigh[] = {"Gamma",6,3};
						};
						class AimHeadLeft
						{
							keys[] = {"0x00050000 + 22"};
							deadZone = 0;
							curveLow[] = {"Gamma",8,3};
							curveMedium[] = {"Gamma",8,3};
							curveHigh[] = {"Gamma",8,3};
						};
						class AimHeadRight
						{
							keys[] = {"0x00050000 + 18"};
							deadZone = 0;
							curveLow[] = {"Gamma",8,3};
							curveMedium[] = {"Gamma",8,3};
							curveHigh[] = {"Gamma",8,3};
						};
						class AimDown
						{
							actionNameYAxis = "AimUp";
							keys[] = {"0x00050000 + 19"};
							deadZone = 0;
							curveLow[] = {"Gamma",6,3};
							curveMedium[] = {"Gamma",6,3};
							curveHigh[] = {"Gamma",6,3};
						};
						class AimUp
						{
							actionNameYAxis = "AimDown";
							keys[] = {"0x00050000 + 23"};
							deadZone = 0;
							curveLow[] = {"Gamma",6,3};
							curveMedium[] = {"Gamma",6,3};
							curveHigh[] = {"Gamma",6,3};
						};
						class AimLeft
						{
							keys[] = {"0x00050000 + 22"};
							deadZone = 0;
							curveLow[] = {"Gamma",8,3};
							curveMedium[] = {"Gamma",8,3};
							curveHigh[] = {"Gamma",8,3};
						};
						class AimRight
						{
							keys[] = {"0x00050000 + 18"};
							deadZone = 0;
							curveLow[] = {"Gamma",8,3};
							curveMedium[] = {"Gamma",8,3};
							curveHigh[] = {"Gamma",8,3};
						};
						SeagullForward[] = {};
						HeliManualFire[] = {"0x00050000 + 1"};
						Diary[] = {};
						ZoomContIn[] = {};
						LookAround[] = {};
						ShowMap[] = {};
						keyLookCenter[] = {"0x00050000 + 15"};
						AutoHover[] = {"0x00050000 + 2"};
						AutoHoverCancel[] = {"0x00050000 + 2"};
						LookAroundToggle[] = {"0x00050000 + 1"};
					};
				};
				class Joystick
				{
					textDPad = "$STR_XBOX_CONTROLER_DP_MENU";
					textLThumb = "$STR_XBOX_CONTROLER_MOVEMENT";
					textLThumbUD = "$STR_XBOX_CONTROLER_LS_FLY";
					textLThumbLR = "$STR_XBOX_CONTROLER_LS_RUDDER";
					textLThumbPS = "$STR_XBOX_CONTROLER_LS_LOCK";
					textRThumb = "$STR_XBOX_CONTROLER_MOVEMENT";
					textRThumbUD = "$STR_XBOX_CONTROLER_RS_TILT_MOVE";
					textRThumbLR = "$STR_XBOX_CONTROLER_RS_TILT";
					textRThumbPS = "";
					class Actions
					{
						class HeliUp
						{
							keys[] = {"0x00050000 + 13"};
							deadZone = 0;
							curveLow[] = {"Gamma",1,1.5};
							curveMedium[] = {"Gamma",1,1.5};
							curveHigh[] = {"Gamma",1,1.5};
						};
						class HeliDown
						{
							keys[] = {"0x00050000 + 12"};
							deadZone = 0;
							curveLow[] = {"Gamma",1,1.5};
							curveMedium[] = {"Gamma",1,1.5};
							curveHigh[] = {"Gamma",1,1.5};
						};
						class HeliCyclicLeft
						{
							keys[] = {"0x00050000 + 22"};
							deadZone = 0;
							curveLow[] = {"Gamma",1,1.5};
							curveMedium[] = {"Gamma",1,1.5};
							curveHigh[] = {"Gamma",1,1.5};
						};
						class HeliCyclicRight
						{
							keys[] = {"0x00050000 + 18"};
							deadZone = 0;
							curveLow[] = {"Gamma",1,1.5};
							curveMedium[] = {"Gamma",1,1.5};
							curveHigh[] = {"Gamma",1,1.5};
						};
						class HeliRudderLeft
						{
							keys[] = {"0x00050000 + 20"};
							deadZone = 0;
							curveLow[] = {"Gamma",1,1.5};
							curveMedium[] = {"Gamma",1,1.5};
							curveHigh[] = {"Gamma",1,1.5};
						};
						class HeliRudderRight
						{
							keys[] = {"0x00050000 + 16"};
							deadZone = 0;
							curveLow[] = {"Gamma",1,1.5};
							curveMedium[] = {"Gamma",1,1.5};
							curveHigh[] = {"Gamma",1,1.5};
						};
						class HeliBack
						{
							actionNameYAxis = "HeliFastForward";
							keys[] = {"0x00050000 + 17"};
							deadZone = 0;
							curveLow[] = {"Gamma",1,1.5};
							curveMedium[] = {"Gamma",1,1.5};
							curveHigh[] = {"Gamma",1,1.5};
						};
						class HeliFastForward
						{
							actionNameYAxis = "HeliBack";
							keys[] = {"0x00050000 + 21"};
							deadZone = 0;
							curveLow[] = {"Gamma",1,1.5};
							curveMedium[] = {"Gamma",1,1.5};
							curveHigh[] = {"Gamma",1,1.5};
						};
						HeliForward[] = {};
						HeliManualFire[] = {"0x00050000 + 1"};
						class SeagullUp
						{
							keys[] = {"0x00050000 + 13"};
							deadZone = 0;
							curveLow[] = {"Gamma",1,1.5};
							curveMedium[] = {"Gamma",1,1.5};
							curveHigh[] = {"Gamma",1,1.5};
						};
						class SeagullDown
						{
							keys[] = {"0x00050000 + 12"};
							deadZone = 0;
							curveLow[] = {"Gamma",1,1.5};
							curveMedium[] = {"Gamma",1,1.5};
							curveHigh[] = {"Gamma",1,1.5};
						};
						class SeagullBack
						{
							actionNameYAxis = "SeagullFastForward";
							keys[] = {"0x00050000 + 17"};
							deadZone = 0;
							curveLow[] = {"Gamma",1,1.5};
							curveMedium[] = {"Gamma",1,1.5};
							curveHigh[] = {"Gamma",1,1.5};
						};
						class SeagullFastForward
						{
							actionNameYAxis = "SeagullBack";
							keys[] = {"0x00050000 + 21"};
							deadZone = 0;
							curveLow[] = {"Gamma",1,1.5};
							curveMedium[] = {"Gamma",1,1.5};
							curveHigh[] = {"Gamma",1,1.5};
						};
						SeagullForward[] = {};
					};
				};
				class Wheel
				{
					textDPad = "$STR_XBOX_CONTROLER_DP_MENU";
					textLThumb = "$STR_XBOX_CONTROLER_MOVEMENT";
					textLThumbLR = "$STR_XBOX_CONTROLER_LS_TURN";
					textLThumbUD = "";
					textLThumbPS = "";
					textRThumb = "";
					textRThumbLR = "";
					textRThumbUD = "";
					textRThumbPS = "";
					class Actions
					{
						HeliUp[] = {};
						HeliDown[] = {};
						HeliCyclicLeft[] = {};
						HeliCyclicRight[] = {};
						class HeliRudderLeft
						{
							keys[] = {"0x00050000 + 20"};
							deadZone = 0;
							curveLow[] = {"Gamma",1,1.5};
							curveMedium[] = {"Gamma",1,1.5};
							curveHigh[] = {"Gamma",1,1.5};
						};
						class HeliRudderRight
						{
							keys[] = {"0x00050000 + 16"};
							deadZone = 0;
							curveLow[] = {"Gamma",1,1.5};
							curveMedium[] = {"Gamma",1,1.5};
							curveHigh[] = {"Gamma",1,1.5};
						};
						class HeliBack
						{
							actionNameYAxis = "HeliFastForward";
							keys[] = {"0x00050000 + 12"};
							deadZone = 0;
							curveLow[] = {"Gamma",1,1.5};
							curveMedium[] = {"Gamma",1,1.5};
							curveHigh[] = {"Gamma",1,1.5};
						};
						class HeliFastForward
						{
							actionNameYAxis = "HeliBack";
							keys[] = {"0x00050000 + 13"};
							deadZone = 0;
							curveLow[] = {"Gamma",1,1.5};
							curveMedium[] = {"Gamma",1,1.5};
							curveHigh[] = {"Gamma",1,1.5};
						};
						HeliForward[] = {};
						HeliManualFire[] = {"0x00050000 + 0"};
						SeagullUp[] = {};
						SeagullDown[] = {};
						class SeagullBack
						{
							actionNameYAxis = "SeagullFastForward";
							keys[] = {"0x00050000 + 12"};
							deadZone = 0;
							curveLow[] = {"Gamma",1,1.5};
							curveMedium[] = {"Gamma",1,1.5};
							curveHigh[] = {"Gamma",1,1.5};
						};
						class SeagullFastForward
						{
							actionNameYAxis = "SeagullBack";
							keys[] = {"0x00050000 + 13"};
							deadZone = 0;
							curveLow[] = {"Gamma",1,1.5};
							curveMedium[] = {"Gamma",1,1.5};
							curveHigh[] = {"Gamma",1,1.5};
						};
						SeagullForward[] = {};
					};
				};
			};
		};
	};
	class LeftHanded: Default
	{
		name = "Left Handed";
		class Gamepad
		{
			class ButtonDeadZones: ButtonDeadZonesDefault
			{
				deadZone_LeftTrigger[] = {192,128};
				deadZone_RightTrigger[] = {80,64};
			};
			class ThumbStickDeadZones
			{
				leftX = 0.21;
				leftY = 0.23;
				rightX = 0.21;
				rightY = 0.23;
			};
			class Actions
			{
				ToggleWeapons[] = {"0x00050000 + 3"};
				DefaultAction[] = {"0x00050000 + 12"};
				ReloadMagazine[] = {"0x00050000 + 2"};
				LookAround[] = {"0x00050000 + 13"};
				LockTarget[] = {};
				VehLockTargets[] = {"0x00050000 + 15"};
				PrevAction[] = {"0x00050000 + 4"};
				NextAction[] = {"0x00050000 + 5"};
				Action[] = {"0x00050000 + 0"};
				MenuSelect[] = {"0x00050000 + 7"};
				MenuBack[] = {"0x00050000 + 6"};
				CancelAction[] = {"0x00050000 + 2"};
				Diary[] = {"0x00050000 + 11"};
				ShowMap[] = {};
				HideMap[] = {};
				ZoomContIn[] = {"0x00050000 + 13"};
				PersonView[] = {"0x00050000 + 9"};
				IngamePause[] = {"0x00050000 + 8"};
				Optics[] = {"0x00050000 + 14"};
				class CommandLeft
				{
					keys[] = {"0x00050000 + 22"};
					deadZone = 0;
					curveLow[] = {"Gamma",2,3.0};
					curveMedium[] = {"Gamma",2,3.0};
					curveHigh[] = {"Gamma",2,3.0};
				};
				class CommandRight
				{
					keys[] = {"0x00050000 + 18"};
					deadZone = 0;
					curveLow[] = {"Gamma",2,3.0};
					curveMedium[] = {"Gamma",2,3.0};
					curveHigh[] = {"Gamma",2,3.0};
				};
				class CommandForward
				{
					keys[] = {"0x00050000 + 19"};
					deadZone = 0;
					curveLow[] = {"Gamma",1,1.5};
					curveMedium[] = {"Gamma",1,1.5};
					curveHigh[] = {"Gamma",1,1.5};
				};
				class CommandBack
				{
					keys[] = {"0x00050000 + 23"};
					deadZone = 0;
					curveLow[] = {"Gamma",1,1.5};
					curveMedium[] = {"Gamma",1,1.5};
					curveHigh[] = {"Gamma",1,1.5};
				};
				CommandFast[] = {};
				CommandSlow[] = {};
			};
		};
		class Joystick
		{
			class ButtonDeadZones: ButtonDeadZonesDefault
			{
				deadZone_LeftTrigger[] = {192,128};
				deadZone_RightTrigger[] = {80,64};
			};
			class ThumbStickDeadZones
			{
				leftX = 0.21;
				leftY = 0.23;
				rightX = 0.21;
				rightY = 0.23;
			};
			class Actions
			{
				ToggleWeapons[] = {"0x00050000 + 3"};
				DefaultAction[] = {"0x00050000 + 3"};
				ReloadMagazine[] = {"0x00050000 + 2"};
				LookAround[] = {"0x00050000 + 12"};
				LockTarget[] = {};
				VehLockTargets[] = {};
				PrevAction[] = {"0x00050000 + 4"};
				NextAction[] = {"0x00050000 + 5"};
				Action[] = {"0x00050000 + 0"};
				MenuSelect[] = {"0x00050000 + 7"};
				MenuBack[] = {"0x00050000 + 6"};
				CancelAction[] = {"0x00050000 + 2"};
				Diary[] = {"0x00050000 + 11"};
				ShowMap[] = {};
				HideMap[] = {};
				ZoomContIn[] = {};
				PersonView[] = {"0x00050000 + 9"};
				Optics[] = {"0x00050000 + 10"};
				IngamePause[] = {"0x00050000 + 8"};
				class CommandLeft
				{
					keys[] = {"0x00050000 + 20"};
					deadZone = 0;
					curveLow[] = {"Gamma",2,3.0};
					curveMedium[] = {"Gamma",2,3.0};
					curveHigh[] = {"Gamma",2,3.0};
				};
				class CommandRight
				{
					keys[] = {"0x00050000 + 16"};
					deadZone = 0;
					curveLow[] = {"Gamma",2,3.0};
					curveMedium[] = {"Gamma",2,3.0};
					curveHigh[] = {"Gamma",2,3.0};
				};
				class CommandForward
				{
					keys[] = {"0x00050000 + 17"};
					deadZone = 0;
					curveLow[] = {"Gamma",1,1.5};
					curveMedium[] = {"Gamma",1,1.5};
					curveHigh[] = {"Gamma",1,1.5};
				};
				class CommandBack
				{
					keys[] = {"0x00050000 + 21"};
					deadZone = 0;
					curveLow[] = {"Gamma",1,1.5};
					curveMedium[] = {"Gamma",1,1.5};
					curveHigh[] = {"Gamma",1,1.5};
				};
				CommandFast[] = {};
				CommandSlow[] = {};
			};
		};
		class Wheel
		{
			class ButtonDeadZones: ButtonDeadZonesDefault
			{
				deadZone_LeftTrigger[] = {192,128};
				deadZone_RightTrigger[] = {80,64};
			};
			class ThumbStickDeadZones
			{
				leftX = 0.21;
				leftY = 0.23;
				rightX = 0.21;
				rightY = 0.23;
			};
			class Actions
			{
				ToggleWeapons[] = {"0x00050000 + 3"};
				DefaultAction[] = {"0x00050000 + 10"};
				ReloadMagazine[] = {"0x00050000 + 2"};
				LookAround[] = {"0x00050000 + 11"};
				LockTarget[] = {};
				VehLockTargets[] = {};
				PrevAction[] = {"0x00050000 + 4"};
				NextAction[] = {"0x00050000 + 5"};
				Action[] = {"0x00050000 + 0"};
				MenuSelect[] = {"0x00050000 + 7"};
				MenuBack[] = {"0x00050000 + 6"};
				CancelAction[] = {"0x00050000 + 2"};
				Diary[] = {"0x00050000 + 11"};
				ShowMap[] = {};
				HideMap[] = {};
				ZoomContIn[] = {"0x00050000 + 11"};
				PersonView[] = {"0x00050000 + 9"};
				Optics[] = {};
				IngamePause[] = {"0x00050000 + 8"};
				class CommandLeft
				{
					keys[] = {"0x00050000 + 20"};
					deadZone = 0;
					curveLow[] = {"Gamma",2,3.0};
					curveMedium[] = {"Gamma",2,3.0};
					curveHigh[] = {"Gamma",2,3.0};
				};
				class CommandRight
				{
					keys[] = {"0x00050000 + 16"};
					deadZone = 0;
					curveLow[] = {"Gamma",2,3.0};
					curveMedium[] = {"Gamma",2,3.0};
					curveHigh[] = {"Gamma",2,3.0};
				};
				class CommandForward
				{
					keys[] = {"0x00050000 + 17"};
					deadZone = 0;
					curveLow[] = {"Gamma",1,1.5};
					curveMedium[] = {"Gamma",1,1.5};
					curveHigh[] = {"Gamma",1,1.5};
				};
				class CommandBack
				{
					keys[] = {"0x00050000 + 21"};
					deadZone = 0;
					curveLow[] = {"Gamma",1,1.5};
					curveMedium[] = {"Gamma",1,1.5};
					curveHigh[] = {"Gamma",1,1.5};
				};
				CommandFast[] = {};
				CommandSlow[] = {};
			};
		};
		class Vehicles: Vehicles
		{
			class Characters: Characters
			{
				name = "characTers";
				axisY = 0;
				class Gamepad
				{
					textDPad = "$STR_XBOX_CONTROLER_DP_MENU";
					textLThumb = "$STR_XBOX_CONTROLER_AIM";
					textLThumbLR = "$STR_XBOX_CONTROLER_LS_LR_AIM";
					textLThumbUD = "$STR_XBOX_CONTROLER_LS_UD_AIM";
					textLThumbPS = "$STR_XBOX_CONTROLER_LS_OPTICS";
					textRThumb = "$STR_XBOX_CONTROLER_MOVEMENT";
					textRThumbLR = "$STR_XBOX_CONTROLER_RS_STRAFE";
					textRThumbUD = "$STR_XBOX_CONTROLER_RS_MOVE";
					textRThumbPS = "$STR_XBOX_CONTROLER_RS_UP";
					class Actions
					{
						class MoveBack
						{
							keys[] = {"0x00050000 + 23"};
							deadZone = 0.1;
							curveLow[] = {"Gamma",1,4};
							curveMedium[] = {"Gamma",1,4};
							curveHigh[] = {"Gamma",1,4};
						};
						class MoveFastForward
						{
							keys[] = {"0x00050000 + 19"};
							deadZone = 0.1;
							curveLow[] = {"Gamma",1,4};
							curveMedium[] = {"Gamma",1,4};
							curveHigh[] = {"Gamma",1,4};
						};
						class TurnLeft
						{
							keys[] = {"0x00050000 + 22"};
							deadZone = 0.1;
							curveLow[] = {"Gamma",1,2};
							curveMedium[] = {"Gamma",1,2};
							curveHigh[] = {"Gamma",1,2};
						};
						class TurnRight
						{
							keys[] = {"0x00050000 + 18"};
							deadZone = 0.1;
							curveLow[] = {"Gamma",1,2};
							curveMedium[] = {"Gamma",1,2};
							curveHigh[] = {"Gamma",1,2};
						};
						MoveUp[] = {"0x00050000 + 15"};
						MoveDown[] = {"0x00050000 + 1"};
						class AimUp
						{
							actionNameYAxis = "AimDown";
							keys[] = {"0x00050000 + 17"};
							deadZone = 0;
							curveLow[] = {"LinRampZoom",{1.0,0.2,0.05,0.99,0.8,1.0,1.8},{0.7,0.2,0.03,0.99,0.6,1.0,1.6},{0.3,0.2,0.02,0.99,0.4,1.0,1.0}};
							curveMedium[] = {"LinRampZoom",{1.0,0.2,0.05,0.99,0.8,1.0,1.8},{0.7,0.2,0.03,0.99,0.6,1.0,1.6},{0.3,0.2,0.02,0.99,0.4,1.0,1.0}};
							curveHigh[] = {"LinRampZoom",{1.0,0.2,0.05,0.99,0.8,1.0,1.8},{0.7,0.2,0.03,0.99,0.6,1.0,1.6},{0.3,0.2,0.02,0.99,0.4,1.0,1.0}};
						};
						class AimDown
						{
							actionNameYAxis = "AimUp";
							keys[] = {"0x00050000 + 21"};
							deadZone = 0;
							curveLow[] = {"LinRampZoom",{1.0,0.2,0.05,0.99,0.8,1.0,1.8},{0.7,0.2,0.03,0.99,0.6,1.0,1.6},{0.3,0.2,0.02,0.99,0.4,1.0,1.0}};
							curveMedium[] = {"LinRampZoom",{1.0,0.2,0.05,0.99,0.8,1.0,1.8},{0.7,0.2,0.03,0.99,0.6,1.0,1.6},{0.3,0.2,0.02,0.99,0.4,1.0,1.0}};
							curveHigh[] = {"LinRampZoom",{1.0,0.2,0.05,0.99,0.8,1.0,1.8},{0.7,0.2,0.03,0.99,0.6,1.0,1.6},{0.3,0.2,0.02,0.99,0.4,1.0,1.0}};
						};
						class AimLeft
						{
							keys[] = {"0x00050000 + 20"};
							deadZone = 0;
							curveLow[] = {"LinRampZoom",{1.0,0.4,0.1,0.8,1.44,0.99,2.88,1.0,3.9},{0.7,0.4,0.1,0.8,1.2,0.99,2.4,1.0,3.25},{0.3,0.4,0.1,0.8,0.96,0.99,1.44,1.0,1.56}};
							curveMedium[] = {"LinRampZoom",{1.0,0.4,0.1,0.8,1.44,0.99,2.88,1.0,3.9},{0.7,0.4,0.1,0.8,1.2,0.99,2.4,1.0,3.25},{0.3,0.4,0.1,0.8,0.96,0.99,1.44,1.0,1.56}};
							curveHigh[] = {"LinRampZoom",{1.0,0.4,0.1,0.8,1.44,0.99,2.88,1.0,3.9},{0.7,0.4,0.1,0.8,1.2,0.99,2.4,1.0,3.25},{0.3,0.4,0.1,0.8,0.96,0.99,1.44,1.0,1.56}};
						};
						class AimRight
						{
							keys[] = {"0x00050000 + 16"};
							deadZone = 0;
							curveLow[] = {"LinRampZoom",{1.0,0.4,0.1,0.8,1.44,0.99,2.88,1.0,3.9},{0.7,0.4,0.1,0.8,1.2,0.99,2.4,1.0,3.25},{0.3,0.4,0.1,0.8,0.96,0.99,1.44,1.0,1.56}};
							curveMedium[] = {"LinRampZoom",{1.0,0.4,0.1,0.8,1.44,0.99,2.88,1.0,3.9},{0.7,0.4,0.1,0.8,1.2,0.99,2.4,1.0,3.25},{0.3,0.4,0.1,0.8,0.96,0.99,1.44,1.0,1.56}};
							curveHigh[] = {"LinRampZoom",{1.0,0.4,0.1,0.8,1.44,0.99,2.88,1.0,3.9},{0.7,0.4,0.1,0.8,1.2,0.99,2.4,1.0,3.25},{0.3,0.4,0.1,0.8,0.96,0.99,1.44,1.0,1.56}};
						};
						class AimHeadUp
						{
							actionNameYAxis = "AimHeadDown";
							keys[] = {"0x00050000 + 17"};
							deadZone = 0;
							curveLow[] = {"Gamma",6,3};
							curveMedium[] = {"Gamma",6,3};
							curveHigh[] = {"Gamma",6,3};
						};
						class AimHeadDown
						{
							actionNameYAxis = "AimHeadUp";
							keys[] = {"0x00050000 + 21"};
							deadZone = 0;
							curveLow[] = {"Gamma",6,3};
							curveMedium[] = {"Gamma",6,3};
							curveHigh[] = {"Gamma",6,3};
						};
						class AimHeadLeft
						{
							keys[] = {"0x00050000 + 20"};
							deadZone = 0;
							curveLow[] = {"Gamma",8,3};
							curveMedium[] = {"Gamma",8,3};
							curveHigh[] = {"Gamma",8,3};
						};
						class AimHeadRight
						{
							keys[] = {"0x00050000 + 16"};
							deadZone = 0;
							curveLow[] = {"Gamma",8,3};
							curveMedium[] = {"Gamma",8,3};
							curveHigh[] = {"Gamma",8,3};
						};
					};
				};
				class Joystick: Joystick{};
				class Wheel: Wheel{};
			};
			class Ground: Ground
			{
				name = "groUnd";
				axisY = 0;
				class Gamepad
				{
					textDPad = "$STR_XBOX_CONTROLER_DP_MENU";
					textLThumb = "$STR_XBOX_CONTROLER_MOVEMENT";
					textLThumbLR = "$STR_XBOX_CONTROLER_LS_TURN";
					textLThumbUD = "";
					textLThumbPS = "";
					textRThumb = "$STR_XBOX_CONTROLER_MOVEMENT";
					textRThumbLR = "";
					textRThumbUD = "$STR_XBOX_CONTROLER_RS_MOVE";
					textRThumbPS = "";
					class Actions
					{
						class CarLeft
						{
							keys[] = {"0x00050000 + 20"};
							deadZone = 0;
							curveLow[] = {"Gamma",2,3.0};
							curveMedium[] = {"Gamma",2,3.0};
							curveHigh[] = {"Gamma",2,3.0};
						};
						class CarRight
						{
							keys[] = {"0x00050000 + 16"};
							deadZone = 0;
							curveLow[] = {"Gamma",2,3.0};
							curveMedium[] = {"Gamma",2,3.0};
							curveHigh[] = {"Gamma",2,3.0};
						};
						CarForward[] = {};
						class CarBack
						{
							keys[] = {"0x00050000 + 23"};
							deadZone = 0;
							curveLow[] = {"Gamma",1,1.5};
							curveMedium[] = {"Gamma",1,1.5};
							curveHigh[] = {"Gamma",1,1.5};
						};
						class CarFastForward
						{
							keys[] = {"0x00050000 + 19"};
							deadZone = 0;
							curveLow[] = {"Gamma",1,1.5};
							curveMedium[] = {"Gamma",1,1.5};
							curveHigh[] = {"Gamma",1,1.5};
						};
						CarSlowForward[] = {};
						class CarAimUp
						{
							actionNameYAxis = "CarAimDown";
							keys[] = {"0x00050000 + 17"};
							deadZone = 0;
							curveLow[] = {"LinRampZoom",{1.0,0.8,0.1,0.9,0.14,1.0,1.0},{0.7,0.8,0.08,0.9,0.12,1.0,0.8},{0.3,0.8,0.06,0.9,0.09,1.0,0.6}};
							curveMedium[] = {"LinRampZoom",{1.0,0.8,0.1,0.9,0.14,1.0,1.0},{0.7,0.8,0.08,0.9,0.12,1.0,0.8},{0.3,0.8,0.06,0.9,0.09,1.0,0.6}};
							curveHigh[] = {"LinRampZoom",{1.0,0.8,0.1,0.9,0.14,1.0,1.0},{0.7,0.8,0.08,0.9,0.12,1.0,0.8},{0.3,0.8,0.06,0.9,0.09,1.0,0.6}};
						};
						class CarAimDown
						{
							actionNameYAxis = "CarAimUp";
							keys[] = {"0x00050000 + 21"};
							deadZone = 0;
							curveLow[] = {"LinRampZoom",{1.0,0.8,0.1,0.9,0.14,1.0,1.0},{0.7,0.8,0.08,0.9,0.12,1.0,0.8},{0.3,0.8,0.06,0.9,0.09,1.0,0.6}};
							curveMedium[] = {"LinRampZoom",{1.0,0.8,0.1,0.9,0.14,1.0,1.0},{0.7,0.8,0.08,0.9,0.12,1.0,0.8},{0.3,0.8,0.06,0.9,0.09,1.0,0.6}};
							curveHigh[] = {"LinRampZoom",{1.0,0.8,0.1,0.9,0.14,1.0,1.0},{0.7,0.8,0.08,0.9,0.12,1.0,0.8},{0.3,0.8,0.06,0.9,0.09,1.0,0.6}};
						};
						class CarAimLeft
						{
							keys[] = {"0x00050000 + 20"};
							deadZone = 0;
							curveLow[] = {"LinRampZoom",{1.0,0.4,0.1,0.9,"0.90 0.99",3.6,1.0,9.0},{0.7,0.4,0.1,0.9,0.75,0.99,3.0,1.0,8.0},{0.3,0.4,0.1,0.9,0.6,0.99,1.8,1.0,5.0}};
							curveMedium[] = {"LinRampZoom",{1.0,0.4,0.1,0.9,"0.90 0.99",3.6,1.0,9.0},{0.7,0.4,0.1,0.9,0.75,0.99,3.0,1.0,8.0},{0.3,0.4,0.1,0.9,0.6,0.99,1.8,1.0,5.0}};
							curveHigh[] = {"LinRampZoom",{1.0,0.4,0.1,0.9,"0.90 0.99",3.6,1.0,9.0},{0.7,0.4,0.1,0.9,0.75,0.99,3.0,1.0,8.0},{0.3,0.4,0.1,0.9,0.6,0.99,1.8,1.0,5.0}};
						};
						class CarAimRight
						{
							keys[] = {"0x00050000 + 16"};
							deadZone = 0;
							curveLow[] = {"LinRampZoom",{1.0,0.4,0.1,0.9,"0.90 0.99",3.6,1.0,9.0},{0.7,0.4,0.1,0.9,0.75,0.99,3.0,1.0,8.0},{0.3,0.4,0.1,0.9,0.6,0.99,1.8,1.0,5.0}};
							curveMedium[] = {"LinRampZoom",{1.0,0.4,0.1,0.9,"0.90 0.99",3.6,1.0,9.0},{0.7,0.4,0.1,0.9,0.75,0.99,3.0,1.0,8.0},{0.3,0.4,0.1,0.9,0.6,0.99,1.8,1.0,5.0}};
							curveHigh[] = {"LinRampZoom",{1.0,0.4,0.1,0.9,"0.90 0.99",3.6,1.0,9.0},{0.7,0.4,0.1,0.9,0.75,0.99,3.0,1.0,8.0},{0.3,0.4,0.1,0.9,0.6,0.99,1.8,1.0,5.0}};
						};
						SwapGunner[] = {"0x00050000 + 1"};
					};
				};
				class Joystick: Joystick{};
				class Wheel: Wheel{};
			};
			class Aircraft: Aircraft
			{
				name = "aIr";
				axisY = 1;
				class Gamepad
				{
					textDPad = "$STR_XBOX_CONTROLER_DP_MENU";
					textLThumb = "$STR_XBOX_CONTROLER_MOVEMENT";
					textLThumbLR = "$STR_XBOX_CONTROLER_LS_TILT";
					textLThumbUD = "$STR_XBOX_CONTROLER_LS_TILT_MOVE";
					textLThumbPS = "";
					textRThumb = "$STR_XBOX_CONTROLER_MOVEMENT";
					textRThumbLR = "$STR_XBOX_CONTROLER_RS_FLY";
					textRThumbUD = "$STR_XBOX_CONTROLER_RS_RUDDER";
					textRThumbPS = "$STR_XBOX_CONTROLER_RS_LOCK";
					class Actions
					{
						class HeliUp
						{
							keys[] = {"0x00050000 + 19"};
							deadZone = 0;
							curveLow[] = {"Gamma",1,1.5};
							curveMedium[] = {"Gamma",1,1.5};
							curveHigh[] = {"Gamma",1,1.5};
						};
						class HeliDown
						{
							keys[] = {"0x00050000 + 23"};
							deadZone = 0;
							curveLow[] = {"Gamma",1,1.5};
							curveMedium[] = {"Gamma",1,1.5};
							curveHigh[] = {"Gamma",1,1.5};
						};
						class HeliCyclicLeft
						{
							keys[] = {"0x00050000 + 20"};
							deadZone = 0;
							curveLow[] = {"Gamma",1,1.5};
							curveMedium[] = {"Gamma",1,1.5};
							curveHigh[] = {"Gamma",1,1.5};
						};
						class HeliCyclicRight
						{
							keys[] = {"0x00050000 + 18"};
							deadZone = 0;
							curveLow[] = {"Gamma",1,1.5};
							curveMedium[] = {"Gamma",1,1.5};
							curveHigh[] = {"Gamma",1,1.5};
						};
						class HeliRudderLeft
						{
							keys[] = {"0x00050000 + 20"};
							deadZone = 0;
							curveLow[] = {"Gamma",1,1.5};
							curveMedium[] = {"Gamma",1,1.5};
							curveHigh[] = {"Gamma",1,1.5};
						};
						class HeliRudderRight
						{
							keys[] = {"0x00050000 + 18"};
							deadZone = 0;
							curveLow[] = {"Gamma",1,1.5};
							curveMedium[] = {"Gamma",1,1.5};
							curveHigh[] = {"Gamma",1,1.5};
						};
						class HeliBack
						{
							actionNameYAxis = "HeliFastForward";
							keys[] = {"0x00050000 + 17"};
							deadZone = 0;
							curveLow[] = {"Gamma",1,1.5};
							curveMedium[] = {"Gamma",1,1.5};
							curveHigh[] = {"Gamma",1,1.5};
						};
						class HeliFastForward
						{
							actionNameYAxis = "HeliBack";
							keys[] = {"0x00050000 + 21"};
							deadZone = 0;
							curveLow[] = {"Gamma",1,1.5};
							curveMedium[] = {"Gamma",1,1.5};
							curveHigh[] = {"Gamma",1,1.5};
						};
						HeliForward[] = {};
						HeliManualFire[] = {"0x00050000 + 1"};
						class SeagullUp
						{
							keys[] = {"0x00050000 + 19"};
							deadZone = 0;
							curveLow[] = {"Gamma",1,1.5};
							curveMedium[] = {"Gamma",1,1.5};
							curveHigh[] = {"Gamma",1,1.5};
						};
						class SeagullDown
						{
							keys[] = {"0x00050000 + 23"};
							deadZone = 0;
							curveLow[] = {"Gamma",1,1.5};
							curveMedium[] = {"Gamma",1,1.5};
							curveHigh[] = {"Gamma",1,1.5};
						};
						class SeagullBack
						{
							actionNameYAxis = "SeagullFastForward";
							keys[] = {"0x00050000 + 17"};
							deadZone = 0;
							curveLow[] = {"Gamma",1,1.5};
							curveMedium[] = {"Gamma",1,1.5};
							curveHigh[] = {"Gamma",1,1.5};
						};
						class SeagullFastForward
						{
							actionNameYAxis = "SeagullBack";
							keys[] = {"0x00050000 + 21"};
							deadZone = 0;
							curveLow[] = {"Gamma",1,1.5};
							curveMedium[] = {"Gamma",1,1.5};
							curveHigh[] = {"Gamma",1,1.5};
						};
						SeagullForward[] = {};
					};
				};
				class Joystick: Joystick{};
				class Wheel: Wheel{};
			};
		};
	};
	class SpecialSoldier: Default
	{
		name = "Special Soldier";
		class Gamepad: Gamepad{};
		class Joystick: Joystick{};
		class Wheel: Wheel{};
		class Vehicles: Vehicles
		{
			class Characters: Characters
			{
				class Gamepad
				{
					textDPad = "$STR_XBOX_CONTROLER_DP_MENU";
					textLThumb = "$STR_XBOX_CONTROLER_AIM";
					textLThumbLR = "$STR_XBOX_CONTROLER_LS_LR_AIM";
					textLThumbUD = "$STR_XBOX_CONTROLER_LS_UD_AIM";
					textLThumbPS = "$STR_XBOX_CONTROLER_LS_UP";
					textRThumb = "$STR_XBOX_CONTROLER_MOVEMENT";
					textRThumbLR = "$STR_XBOX_CONTROLER_RS_STRAFE";
					textRThumbUD = "$STR_XBOX_CONTROLER_RS_MOVE";
					textRThumbPS = "$STR_XBOX_CONTROLER_RS_OPTICS";
					class Actions
					{
						class MoveBack
						{
							keys[] = {"0x00050000 + 23"};
							deadZone = 0.1;
							curveLow[] = {"Gamma",1,4};
							curveMedium[] = {"Gamma",1,4};
							curveHigh[] = {"Gamma",1,4};
						};
						class MoveFastForward
						{
							keys[] = {"0x00050000 + 19"};
							deadZone = 0.1;
							curveLow[] = {"Gamma",1,4};
							curveMedium[] = {"Gamma",1,4};
							curveHigh[] = {"Gamma",1,4};
						};
						class TurnLeft
						{
							keys[] = {"0x00050000 + 22"};
							deadZone = 0.1;
							curveLow[] = {"Gamma",1,2};
							curveMedium[] = {"Gamma",1,2};
							curveHigh[] = {"Gamma",1,2};
						};
						class TurnRight
						{
							keys[] = {"0x00050000 + 18"};
							deadZone = 0.1;
							curveLow[] = {"Gamma",1,2};
							curveMedium[] = {"Gamma",1,2};
							curveHigh[] = {"Gamma",1,2};
						};
						MoveUp[] = {"0x00050000 + 14"};
						MoveDown[] = {"0x00050000 + 1"};
						class AimUp
						{
							actionNameYAxis = "AimDown";
							keys[] = {"0x00050000 + 17"};
							deadZone = 0;
							curveLow[] = {"LinRampZoom",{1.0,0.2,0.05,0.99,0.8,1.0,1.8},{0.7,0.2,0.03,0.99,0.6,1.0,1.6},{0.3,0.2,0.02,0.99,0.4,1.0,1.0}};
							curveMedium[] = {"LinRampZoom",{1.0,0.2,0.05,0.99,0.8,1.0,1.8},{0.7,0.2,0.03,0.99,0.6,1.0,1.6},{0.3,0.2,0.02,0.99,0.4,1.0,1.0}};
							curveHigh[] = {"LinRampZoom",{1.0,0.2,0.05,0.99,0.8,1.0,1.8},{0.7,0.2,0.03,0.99,0.6,1.0,1.6},{0.3,0.2,0.02,0.99,0.4,1.0,1.0}};
						};
						class AimDown
						{
							actionNameYAxis = "AimUp";
							keys[] = {"0x00050000 + 21"};
							deadZone = 0;
							curveLow[] = {"LinRampZoom",{1.0,0.2,0.05,0.99,0.8,1.0,1.8},{0.7,0.2,0.03,0.99,0.6,1.0,1.6},{0.3,0.2,0.02,0.99,0.4,1.0,1.0}};
							curveMedium[] = {"LinRampZoom",{1.0,0.2,0.05,0.99,0.8,1.0,1.8},{0.7,0.2,0.03,0.99,0.6,1.0,1.6},{0.3,0.2,0.02,0.99,0.4,1.0,1.0}};
							curveHigh[] = {"LinRampZoom",{1.0,0.2,0.05,0.99,0.8,1.0,1.8},{0.7,0.2,0.03,0.99,0.6,1.0,1.6},{0.3,0.2,0.02,0.99,0.4,1.0,1.0}};
						};
						class AimLeft
						{
							keys[] = {"0x00050000 + 20"};
							deadZone = 0;
							curveLow[] = {"LinRampZoom",{1.0,0.4,0.1,0.8,1.44,0.99,2.88,1.0,3.9},{0.7,0.4,0.1,0.8,1.2,0.99,2.4,1.0,3.25},{0.3,0.4,0.1,0.8,0.96,0.99,1.44,1.0,1.56}};
							curveMedium[] = {"LinRampZoom",{1.0,0.4,0.1,0.8,1.44,0.99,2.88,1.0,3.9},{0.7,0.4,0.1,0.8,1.2,0.99,2.4,1.0,3.25},{0.3,0.4,0.1,0.8,0.96,0.99,1.44,1.0,1.56}};
							curveHigh[] = {"LinRampZoom",{1.0,0.4,0.1,0.8,1.44,0.99,2.88,1.0,3.9},{0.7,0.4,0.1,0.8,1.2,0.99,2.4,1.0,3.25},{0.3,0.4,0.1,0.8,0.96,0.99,1.44,1.0,1.56}};
						};
						class AimRight
						{
							keys[] = {"0x00050000 + 16"};
							deadZone = 0;
							curveLow[] = {"LinRampZoom",{1.0,0.4,0.1,0.8,1.44,0.99,2.88,1.0,3.9},{0.7,0.4,0.1,0.8,1.2,0.99,2.4,1.0,3.25},{0.3,0.4,0.1,0.8,0.96,0.99,1.44,1.0,1.56}};
							curveMedium[] = {"LinRampZoom",{1.0,0.4,0.1,0.8,1.44,0.99,2.88,1.0,3.9},{0.7,0.4,0.1,0.8,1.2,0.99,2.4,1.0,3.25},{0.3,0.4,0.1,0.8,0.96,0.99,1.44,1.0,1.56}};
							curveHigh[] = {"LinRampZoom",{1.0,0.4,0.1,0.8,1.44,0.99,2.88,1.0,3.9},{0.7,0.4,0.1,0.8,1.2,0.99,2.4,1.0,3.25},{0.3,0.4,0.1,0.8,0.96,0.99,1.44,1.0,1.56}};
						};
						class AimHeadUp
						{
							actionNameYAxis = "AimHeadDown";
							keys[] = {"0x00050000 + 17"};
							deadZone = 0;
							curveLow[] = {"Gamma",6,3};
							curveMedium[] = {"Gamma",6,3};
							curveHigh[] = {"Gamma",6,3};
						};
						class AimHeadDown
						{
							actionNameYAxis = "AimHeadUp";
							keys[] = {"0x00050000 + 21"};
							deadZone = 0;
							curveLow[] = {"Gamma",6,3};
							curveMedium[] = {"Gamma",6,3};
							curveHigh[] = {"Gamma",6,3};
						};
						class AimHeadLeft
						{
							keys[] = {"0x00050000 + 20"};
							deadZone = 0;
							curveLow[] = {"Gamma",8,3};
							curveMedium[] = {"Gamma",8,3};
							curveHigh[] = {"Gamma",8,3};
						};
						class AimHeadRight
						{
							keys[] = {"0x00050000 + 16"};
							deadZone = 0;
							curveLow[] = {"Gamma",8,3};
							curveMedium[] = {"Gamma",8,3};
							curveHigh[] = {"Gamma",8,3};
						};
					};
				};
				class Joystick: Joystick{};
				class Wheel: Wheel{};
			};
			class Ground: Ground
			{
				class Gamepad: Gamepad{};
				class Joystick: Joystick{};
				class Wheel: Wheel{};
			};
			class Aircraft: Aircraft
			{
				class Gamepad: Gamepad{};
				class Joystick: Joystick{};
				class Wheel: Wheel{};
			};
		};
	};
};
class PreloadConfig
{
	CfgVoice = "*";
	class CfgCloudlets
	{
		CraterBlood = ".";
		CraterDustSmall = "*";
		CraterDustBig = "*";
		CraterSmoke1 = "*";
		CraterSmoke2 = "*";
		CraterSmoke3 = "*";
		CraterWater = "*";
		Explosion = "*";
	};
	CfgCloudletShapes = "*";
	CfgVehicles = "fastFind";
	CfgNonAIVehicles = "fastFind";
	CfgAmmo = "fastFind";
	CfgTitles = "*";
	CfgFonts = "*";
	CfgFontFamilies = "*";
	CfgHQIdentities = "*";
};
