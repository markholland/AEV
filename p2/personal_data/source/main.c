/*---------------------------------------------------------------------------------

	Personal Data App

---------------------------------------------------------------------------------*/
#include <nds.h>
#include <stdio.h>
#include <system.h>
#include <inttypes.h>

#define Color_Title "\x1b[32m" // Color Green
#define Color_Value "\x1b[38m"  // Color Grey
//---------------------------------------------------------------------------------
int main(void) {
//---------------------------------------------------------------------------------
	consoleDemoInit();

	char name[11] = {0};
	int i;

	printf("%sUsers name:%9.9s ", Color_Title, Color_Value);
	for(i=0; i<PersonalData->nameLen; i++) {
		name[i] = (char)(PersonalData->name[i] & 255); // get ascii-bits from utf-16 name
		printf("%s", &name[i]);
	}
	printf("\n");

	printf("%sAlarm hour:%9s %u\n", Color_Title, Color_Value, PersonalData->alarmHour);
	printf("%sAlarm minute:%7s %u\n", Color_Title, Color_Value, PersonalData->alarmMinute);
	printf("%sBirth Day:%10s %u\n", Color_Title, Color_Value, PersonalData->birthDay);
	printf("%sBirth Month:%8s %u\n", Color_Title, Color_Value, PersonalData->birthMonth);

	printf("%scalX1:%14s %" PRIu16 "\n", Color_Title, Color_Value, PersonalData->calX1);
	printf("%scalX1px:%12s %u\n", Color_Title, Color_Value, PersonalData->calX1px);
	printf("%scalX2:%14s %" PRIu16 "\n", Color_Title, Color_Value, PersonalData->calX2);
	printf("%scalX2px:%12s %u\n", Color_Title, Color_Value, PersonalData->calX2px);
	printf("%scalY1:%14s %" PRIu16 "\n", Color_Title, Color_Value, PersonalData->calY1);
	printf("%scalY1px:%12s %u\n", Color_Title, Color_Value, PersonalData->calY1px);
	printf("%scalY2:%14s %" PRIu16 "\n", Color_Title, Color_Value, PersonalData->calY2);
	printf("%scalY2px:%12s %u\n", Color_Title, Color_Value, PersonalData->calY2px);

	printf("%sRTC offset:%9s %" PRIu32 "\n", Color_Title, Color_Value, PersonalData->rtcOffset);
	printf("%sTheme:%14s %u\n", Color_Title, Color_Value, PersonalData->theme);

	//Print last because ugly defulat message on DeSmuMe
	char message[27];
	printf("%sUsers message:%s \n", Color_Title, Color_Value);
	for(i=0; i<PersonalData->messageLen; i++) {
		message[i] = (char)(PersonalData->message[i] & 255);
		printf("%s", &message[i]);
	}
	printf("\n");

	while(1) {
		swiWaitForVBlank();
	}

}
