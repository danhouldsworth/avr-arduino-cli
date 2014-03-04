#include "stdio.h"

#ifndef responseBufferSize
#define responseBufferSize 128
#endif

#ifndef true
#define true 1
#endif

#ifndef false
#define false 0
#endif

char serverResponseByLine[responseBufferSize];
char *serverResponsePtr = serverResponseByLine;
int parseBufferCounter = 0;

char *pretendFile = "The quick red fox jumped over the lazy brown dog.\nStarting to test.\nDJH-RED-LED=ON\nDJH-BLU-LED=OFF\nOver.\n";

// -- Declaration of functions
char parseLineByCharacter(char c);
void checkRecognisedCommand(char *parsedServerResponse);
void resetLineParseBuffer();
int stringCompare(char *first, char *second);
//


int main(){

    printf("\n\n\n---BEGIN---\n\n\n");

    char greet[] = "Hello, world before I test!";

    char *greetPtr = greet;

    *(greetPtr++)='<';
    *(greetPtr++)='!';
    *(greetPtr++)='>';

    printf("Greet : %s, last char = <%d>\n", greet, greet[27]);

    while (parseLineByCharacter(*pretendFile++));

    printf("\n\n\n---END---\n\n\n");
}


char parseLineByCharacter(char c){
    if (c == '\n') {
        // Starting a new line so parse the current line held in reponse buffer
        *serverResponsePtr++ = '\0';
        resetLineParseBuffer();

        printf("\nParsed line : ");
        printf("%s",serverResponseByLine);

        checkRecognisedCommand(serverResponseByLine);
    }
    else {
        *serverResponsePtr++ = c;
        if ( ++parseBufferCounter > responseBufferSize ) {
            printf("Buffer exceeded, current line overwritten");
            resetLineParseBuffer();
        }
    }

    return c;
}

void resetLineParseBuffer(){
    parseBufferCounter = 0;
    serverResponsePtr = serverResponseByLine;
}

void checkRecognisedCommand(char *parsedServerResponse){

    // 1. Take the parsed line from server
    // 2. Check the first 12 digits into a substring
    // 3. Test against a list of known commands : if so output the remaining of string as the result
    // 4. Otherwise output "No command"

    char commandSample[] = "***-***-***=";

    char blueCmd[] = "DJH-BLU-LED=";
    char redCmd[] = "DJH-RED-LED=";
    char onValue[] = "ON";
    char offValue[] = "OFF";

    char* commandSamplePtr = commandSample;

    // -- Copy first 12 characters as potential command
    int counter = 1;
    while ( (counter++ < 12) && (*commandSamplePtr++ = *parsedServerResponse++) );
    // --

    char* parsedValuePtr = parsedServerResponse + 1; // Point to the response immediately after the '='

    // -- Check against known commands
    if ( stringCompare(blueCmd, commandSample) ){
        printf("\n[Yay!!] Found command from server for Blue Build LEDs!!");
        if ( stringCompare( parsedValuePtr, onValue ) ){
            printf("Set the Build LED's to ON (eg digitalWrite(ledPin, true).\n");
        }
        else if ( stringCompare( parsedValuePtr, offValue ) ){
            printf("Set the Build LED's to OFF (eg digitalWrite(ledPin, false).\n");
        }
        else {
            printf("Value unrecognised! : %s\n", parsedValuePtr);
        }
    }
    else if ( stringCompare(redCmd, commandSample) ){

        printf("\n[Yay!!] Found command from server for Red Warning LEDs!!");
        if ( stringCompare( parsedValuePtr, onValue ) ){
            printf("Set the Warning LED's to ON (eg digitalWrite(redLedPin, true).\n");
        }
        else if ( stringCompare( parsedValuePtr, offValue ) ){
            printf("Set the Warning LED's to OFF (eg digitalWrite(redLedPin, false).\n");
        }
        else {
            printf("Value unrecognised! : %s\n", parsedValuePtr);
        }
    }
    else {
        printf("\nIgnore this line from Server response as sample not recognised as command : %s\n", commandSample);
    }
    // --

}

int stringCompare(char *first, char *second){


    // Count along both strings until they deviate OR end of either string
    while ( (*first != '\0') && (*second != '\0') && (*first++ == *second++) );

    // If ended with both terminating then equal ELSE not equal
    if ((*first == '\0') && (*second == '\0')) {
        return true;
    }
    else {
        return false;
    }
}
