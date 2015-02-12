/*---------------------------------------------------------------------------------

	Basic template code for starting a DS app

---------------------------------------------------------------------------------*/
#include <nds.h>
#include <stdio.h>
#include <system.h>
#include <inttypes.h>

#define Color_Title "\x1b[31m" // Color Red
#define Color_Value "\x1b[36m"  // To flush out prev settings
//---------------------------------------------------------------------------------
int main(void) {
//---------------------------------------------------------------------------------
	consoleDemoInit();

	char name[11] = {0};
	int i;

	printf("%sUsers name:%s ", Color_Title, Color_Value);
	for(i=0; i<PersonalData->nameLen; i++) {
		name[i] = (char)(PersonalData->name[i] & 255); // get ascii-bits from utf-16 name
		printf("%s", &name[i]);
	}
	printf("\n");

	printf("%sAlarm hour:%s %u\n", Color_Title, Color_Value, PersonalData->alarmHour);
	printf("%sAlarm minute:%s %u\n", Color_Title, Color_Value, PersonalData->alarmMinute);
	printf("%sBirth Day:%s %u\n", Color_Title, Color_Value, PersonalData->birthDay);
	printf("%sBirth Month:%s %u\n", Color_Title, Color_Value, PersonalData->birthMonth);

	printf("%scalX1:%s %" PRIu16 "\n", Color_Title, Color_Value, PersonalData->calX1);
	printf("%scalX1px:%s %u\n", Color_Title, Color_Value, PersonalData->calX1px);
	printf("%scalX2:%s %" PRIu16 "\n", Color_Title, Color_Value, PersonalData->calX2);
	printf("%scalX2px:%s %u\n", Color_Title, Color_Value, PersonalData->calX2px);
	printf("%scalY1:%s %" PRIu16 "\n", Color_Title, Color_Value, PersonalData->calY1);
	printf("%scalY1px:%s %u\n", Color_Title, Color_Value, PersonalData->calY1px);
	printf("%scalY2:%s %" PRIu16 "\n", Color_Title, Color_Value, PersonalData->calY2);
	printf("%scalY2px:%s %u\n", Color_Title, Color_Value, PersonalData->calY2px);

	char message[27];
	printf("%sUsers message:%s \n", Color_Title, Color_Value);
	for(i=0; i<PersonalData->messageLen; i++) {
		message[i] = (char)(PersonalData->message[i] & 255);
		printf("%s", &message[i]);
	}
	printf("\n");

	printf("%sRTC offset:%s %" PRIu32 "\n", Color_Title, Color_Value, PersonalData->rtcOffset);
	printf("%sTheme:%s %u\n", Color_Title, Color_Value, PersonalData->theme);

	while(1) {
		swiWaitForVBlank();
	}

}
