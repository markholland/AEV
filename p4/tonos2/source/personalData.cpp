// #include <nds.h>

// #include <stdio.h>
// #include <stdlib.h>

// #include <system.h>
// #include <inttypes.h>

// #define Color_Title "\x1b[32m" // Color Green
// #define Color_Value "\x1b[38m"  // Color Grey

// void topScreenAndConsole(void) {

// 	videoSetMode(MODE_0_2D);
// 	consoleInit(0,0,BgType_Text4bpp, BgSize_T_256x256, 31,0, true, true);	
// }

// void dropCursorToCenter(void) {

// 	printf("\n\n\n\n\n\n\n\n\n\t");
// }

// void UsersName(void) {

// 	topScreenAndConsole();
// 	dropCursorToCenter();
// 	char name[11] = {0};
// 	printf("%sUsers name:%s ", Color_Title, Color_Value);
// 	for(int i=0; i<PersonalData->nameLen; i++) {
// 		name[i] = (char)(PersonalData->name[i] & 255); // get ascii-bits from utf-16 name
// 		printf("%s", &name[i]);
// 	}
// 	printf("\n");
// }
// void AlarmHour(void) {
// 	topScreenAndConsole();
// 	dropCursorToCenter();
// 	printf("%sAlarm hour:%s %u\n", Color_Title, Color_Value, PersonalData->alarmHour);
// }
// void AlarmMinute(void) {
// 	topScreenAndConsole();
// 	dropCursorToCenter();
// 	printf("%sAlarm minute:%s %u\n", Color_Title, Color_Value, PersonalData->alarmMinute);
// }
// void BirthDay(void) {
// 	topScreenAndConsole();
// 	dropCursorToCenter();
// 	printf("%sBirth Day:%s %u\n", Color_Title, Color_Value, PersonalData->birthDay);
// }
// void BirthMonth(void) {
// 	topScreenAndConsole();
// 	dropCursorToCenter();
// 	printf("%sBirth Month:%s %u\n", Color_Title, Color_Value, PersonalData->birthMonth);
// }
// void RTCoffset(void) {
// 	topScreenAndConsole();
// 	dropCursorToCenter();
// 	printf("%sRTC offset:%s %" PRIu32 "\n", Color_Title, Color_Value, PersonalData->rtcOffset);	
// }
// void Theme(void) {
// 	topScreenAndConsole();
// 	dropCursorToCenter();
// 	printf("%sTheme:%s %u\n", Color_Title, Color_Value, PersonalData->theme);
// }
// void UsersMessage(void) {
// 	topScreenAndConsole();
// 	dropCursorToCenter();
// 	char message[27];
// 	printf("%sUsers message:%s \n", Color_Title, Color_Value);
// 	for(int i=0; i<PersonalData->messageLen; i++) {
// 		message[i] = (char)(PersonalData->message[i] & 255);
// 		printf("%s", &message[i]);
// 	}
// 	printf("\n");

// }



