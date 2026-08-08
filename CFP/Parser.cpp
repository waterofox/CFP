#include "Parser.h"

void Parser::start()
{
	bool models_started_flag = true;
	if (!member_achivments.start())
	{
		models_started_flag = false;
	}
	else
	{
		printf("member achivments model started\n");
	}
	
	if (!member_stats.start())
	{
		models_started_flag = false;
	}
	else
	{
		printf("member stats model started\n");
	}

	if (!models_started_flag) 
	{
		printf("PARSER ERROR: failed to start models\n");
		return;
	}

	XLDocument cf_status;
	cf_status.open("cf_status.xlsx");
	if (!cf_status.isOpen())
	{
		printf("PARSER ERROR: falied to open cf table\n");
		return;
	}


	cf_status.close();
}
