#include <stdio.h>
#include <windows.h>

HANDLE hConsole;
CONSOLE_SCREEN_BUFFER_INFO consoleInfo;
WORD saved_attributes;

void resetAttributes(){
	hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	/* Save current attributes */
	GetConsoleScreenBufferInfo(hConsole, &consoleInfo);
	saved_attributes = consoleInfo.wAttributes;
}

void printBanner() {
	resetAttributes();
	SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN);
	printf("__          __  _     _____                 \n"
	       "\\ \\        / / | |   / ____|                \n"
	       " \\ \\  /\\  / /__| |__| (___   ___ __ _ _ __  \n"
	       "  \\ \\/  \\/ / _ \\ '_ \\\\___ \\ / __/ _` | '_ \\ \n"
	       "   \\  /\\  /  __/ |_) |___) | (_| (_| | | | |\n"
	       "    \\/  \\/ \\___|_.__/_____/ \\___\\__,_|_| |_|\n"
	       "    From WebScan V1.0 | Built by Group8     \n ");
	printf("\n");
	SetConsoleTextAttribute(hConsole, saved_attributes);
	printf("Welcome To WebScan!!\n");
}

void printStartScan(char *func) {
	SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN);
	printf("[*]Start Scanning %s\n",func);
}

void printLog(char *log) {
	resetAttributes();
	SetConsoleTextAttribute(hConsole, saved_attributes);
	printf("[+]%s\n",log);
}

void printSucc(char *succ) {
	SetConsoleTextAttribute(hConsole, FOREGROUND_GREEN);
	printf("[+]%s\n",succ);
}

void printAlert(char *alert) {
	SetConsoleTextAttribute(hConsole, FOREGROUND_RED);
	printf("[-]%s\n",alert);
}



