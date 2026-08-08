
#include "src/models/Member_Stats_Model.h"
#include "src/models/db/Member_Achievements_Model.h"

int main()
{
	Member_Achievements_Model mod;
	if (mod.start())
	{
		printf("started\n");

		mod.stop();
	}
}