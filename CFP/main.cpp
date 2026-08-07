#include "src/models/Member_Achievements_Model.h"
#include "src/models/Member_Stats_Model.h"

int main()
{
	Member_Stats_Model mod;
	if (mod.start())
	{
		printf("started\n");
		
		//mod.set_value("SnifflyFox", "correct_by_correct", 1);
		int val = mod.get_value("SnifflyFox", "correct_by_correct");
		if (val == 1)
		{
			mod.set_value("Arter", "day_wa", 2);
		}

		mod.stop();
	}
}