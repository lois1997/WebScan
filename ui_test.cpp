/* Change console text color, then restore it back to normal. */
/* https://stackoverflow.com/questions/9203362/c-color-text-in-terminal-applications-in-windows */
#include <stdio.h>
#include <windows.h>

HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
CONSOLE_SCREEN_BUFFER_INFO consoleInfo;
WORD saved_attributes;

void printBanner() {
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


int main() {
	/* Save current attributes */
	GetConsoleScreenBufferInfo(hConsole, &consoleInfo);
	saved_attributes = consoleInfo.wAttributes;
	
	/* Print Banner */
	printBanner();
	/* Print Function */
	char *func = "Port";
	printStartScan(func);
	char *log = "Port from 80-8000";
	char *succ = "80:WEB";
	char *alert = "Nothing found!";
	printLog(log);
	printLog(log);
	printSucc(succ);
	printAlert(alert);
	return 0;
}
