#pragma once
struct zad
{
	int czas_op1,
		czas_op2,
		maszyna_op1,
		maszyna_op2,
		czas_konca;
	bool op1 = false,
		 op2 = false;
};

struct konserwacja
{
	int time,
		begin,
		end;
};

struct czasOperacji
{
	int begin,
		time,
		end,
		czasKoncaOperacj1;
};

struct task
{
	int zdanie;
	int operacja;
	
};

struct iddleTime
{
	int begin,
		time,
		end;
};