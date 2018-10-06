void SetRandomHealth(EntityAI itm)
{
	int rndHlt = Math.RandomInt(40,100);
	itm.SetHealth("","",rndHlt);
}

void main()
{
    Print("Test On Init.c");
	if ( GetGame().IsMultiplayer() ) return;
	
	vector player_pos;
	int index;
	TVectorArray positions = {"15135.1 0 13901.1", "15017.8 0 13892.4", "14887.1 0 14547.9", "14749.7 0 13248.7", "14697.6 0 13418.4", "14537.3 0 14755.7", "14415.3 0 14025.2", "14338.0 0 12859.5", "14263.8 0 12748.7", "14172.2 0 12304.9", "14071.4 0 12033.3", "14054.9 0 11341.3", "14017.8 0 2959.1", "13905.5 0 12489.7", "13852.4 0 11686.0", "13846.6 0 12050.0", "13676.0 0 12262.1", "13617.4 0 12759.8", "13610.1 0 11223.6", "13594.3 0 4064.0", "13587.8 0 6026.5", "13571.1 0 3056.8", "13552.6 0 4653.7", "13529.9 0 3968.3", "13520.8 0 4223.7", "13504.0 0 5004.5", "13476.7 0 6136.3", "13441.6 0 5262.2", "13426.6 0 5747.3", "13416.8 0 11840.4", "13400.8 0 4120.7", "13395.8 0 5902.8", "13385.0 0 3946.6", "13374.4 0 6454.3", "13367.1 0 10837.1", "13366.3 0 4906.0", "13337.1 0 5120.8", "13326.7 0 5489.1", "13312.7 0 6771.1", "13288.7 0 11415.1", "13261.6 0 11785.2", "13171.6 0 6534.8", "13159.8 0 5401.7", "13155.2 0 5475.2", "13138.8 0 6737.3", "13112.3 0 11280.7", "13111.7 0 10975.5", "13101.2 0 7657.3", "13099.1 0 6393.0", "13084.9 0 7938.6", "13056.8 0 4848.5", "13048.1 0 8357.6", "13048.1 0 3867.7", "12991.7 0 7287.1", "12983.0 0 5539.1", "12978.9 0 9727.8", "12950.2 0 5226.7", "12942.1 0 8393.1", "12891.5 0 3673.9", "12628.7 0 10495.2", "12574.3 0 3592.8", "12566.3 0 6682.6", "12465.2 0 8009.0", "12354.5 0 3480.0", "13262.8 0 7225.8", "13170.0 0 7406.3", "12936.7 0 10734.0", "12929.7 0 8578.3", "12917.3 0 9356.6", "12889.9 0 8792.8", "12868.7 0 9054.5", "12800.7 0 10542.7", "12796.3 0 10361.3", "12789.2 0 10918.7", "12774.0 0 7792.6", "12729.8 0 11285.5", "12689.8 0 8256.0", "12651.2 0 8914.4", "12614.7 0 7304.6", "12343.6 0 10169.8", "12332.0 0 8170.0", "12221.6 0 8693.6", "12135.7 0 10209.8", "11914.3 0 3402.0", "11846.8 0 3477.8", "11709.4 0 3388.2", "11578.0 0 3159.0", "11439.0 0 3315.2", "11201.5 0 3186.6", "11075.8 0 3031.2", "11049.3 0 2801.6", "10969.2 0 2895.1", "10875.8 0 2518.9", "10820.4 0 2257.4", "10757.4 0 2662.2", "10294.2 0 2822.9", "10032.8 0 2446.5", "9823.2 0 2712.6", "9691.7 0 1750.4", "9529.7 0 1791.2", "9479.7 0 2373.5", "9193.7 0 1935.7"};
	
	TStringArray tops = {"Hoodie_Blue","Hoodie_Black","Hoodie_Brown","Hoodie_Green","Hoodie_Grey","Hoodie_Red"};
	TStringArray pants = {"Jeans_Black","Jeans_BlueDark","Jeans_Blue","Jeans_Brown","Jeans_Green","Jeans_Grey","CanvasPants_Beige","CanvasPants_Blue","CanvasPants_Grey"};
	TStringArray shoes = {"AthleticShoes_Black","AthleticShoes_Blue","AthleticShoes_Brown","AthleticShoes_Green","AthleticShoes_Grey"};
		
	Print(positions);
	
	index = Math.RandomInt(0, positions.Count() );
	

	player_pos = positions.Get(index);
	Print(player_pos);	
	Entity playerEnt = GetGame().CreatePlayer( NULL, GetGame().CreateRandomPlayer(), player_pos, 0, "NONE");

	PlayerBase player = (PlayerBase) playerEnt;

	EntityAI item = player.GetInventory().CreateInInventory(tops.GetRandomElement());
	EntityAI item2 = player.GetInventory().CreateInInventory(pants.GetRandomElement());
	EntityAI item3 = player.GetInventory().CreateInInventory(shoes.GetRandomElement());
	
	EntityAI itemEnt;
	EntityAI itemIn;
	ItemBase itemBs;
	int rndQnt;
	
	itemEnt = player.GetInventory().CreateInInventory("Rag");
	itemBs = ItemBase.Cast(itemEnt);
	itemBs.SetQuantity(4);
	SetRandomHealth(itemEnt);

	itemEnt = player.GetInventory().CreateInInventory("Mag_IJ70_8Rnd");
	SetRandomHealth(itemEnt);

	itemEnt = player.GetInventory().CreateInInventory("HuntingKnife");
	SetRandomHealth(itemEnt);

	itemEnt = player.GetInventory().CreateInInventory("HuntingBag");
	SetRandomHealth(itemEnt);

	itemEnt = player.GetInventory().CreateInInventory("MakarovIJ70");
	SetRandomHealth(itemEnt);
	player.SetQuickBarEntityShortcut(itemEnt, 2);

	itemIn = itemEnt.GetInventory().CreateAttachment("Mag_IJ70_8Rnd");
	SetRandomHealth(itemIn);

	itemEnt = player.GetInventory().CreateInInventory("Izh18");
	SetRandomHealth(itemEnt);
	player.SetQuickBarEntityShortcut(itemEnt, 0);

	itemBs = ItemBase.Cast(itemEnt);
	itemBs.SetQuantity(rndQnt);

	itemEnt = player.GetInventory().CreateInInventory("Ammo_762x39");
	rndQnt = Math.RandomInt(5,20);
	SetRandomHealth(itemEnt);
	player.SetQuickBarEntityShortcut(itemEnt, 1);

	itemEnt = player.GetInventory().CreateInInventory("Ammo_380");
	SetRandomHealth(itemEnt);
	
	GetGame().SelectPlayer(NULL, player);

	//EKONOMIKA
	Hive myHive = CreateHive();
	if( myHive )
	{
		myHive.InitOffline();
	}

	Weather weather = g_Game.GetWeather();

	weather.GetOvercast().SetLimits( 0.0 , 1.0 );
	weather.GetRain().SetLimits( 0.0 , 1.0 );
	weather.GetFog().SetLimits( 0.0 , 0.2 );

	weather.GetOvercast().SetForecastChangeLimits( 0.0, 0.2 );
	weather.GetRain().SetForecastChangeLimits( 0.0, 0.1 );
	weather.GetFog().SetForecastChangeLimits( 0.0, 0.1 );

	weather.GetOvercast().SetForecastTimeLimits( 1800 , 1800 );
	weather.GetRain().SetForecastTimeLimits( 600 , 600 );
	weather.GetFog().SetForecastTimeLimits( 600 , 600 );

	weather.GetOvercast().Set( Math.RandomFloatInclusive(0.0, 0.3), 0, 0);
	weather.GetRain().Set( Math.RandomFloatInclusive(0.0, 0.2), 0, 0);
	weather.GetFog().Set( Math.RandomFloatInclusive(0.0, 0.1), 0, 0);
	
	weather.SetWindMaximumSpeed(5);
	weather.SetWindFunctionParams(0.2, 1.0, 50);
}