static int CF_XOR(int x, int y)
{
	int a = (x | y);
	int b = ~x;
	int c = ~y;
	int d = (b | c);
	return (a & d);
}
