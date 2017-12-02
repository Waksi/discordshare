#define _XOPEN_SOURCE
#include <unistd.h>
#include <stdio.h>
#include <cs50.h>
#include <string.h>
#include <ctype.h>

// clang -ggdb3 -O0 -std=c11 -Wall -Werror -Wshadow crack.c -lcrypt -lcs50 -lm -o crack // used to compile this code

bool oneChar(string argvHash, char* checkString);
bool twoChar(string argvHash, char* checkString);
bool threeChar(string argvHash, char* checkString);
bool fourChar(string argvHash, char* checkString);

int main (int argc, string argv[])
{
    if (argc != 2 || strlen(argv[1]) != 13)
    {
        printf("Error: missing command line argument or hash is not length == 13\n");
        return 1;
    }
    string hash = argv[1];
    char* pwbuff = malloc(sizeof(char) * 5);
    if (oneChar(hash, pwbuff)) // check hash against 1 char length hashes
    {
        printf("%s\n", pwbuff);
        return 0;
    }
    else if (twoChar(hash, pwbuff)) // check hash against 2 char length hashes
    {
        printf("%s\n", pwbuff);
        return 0;
    }
    else if (threeChar(hash, pwbuff)) // as above but with 3 char
    {
        printf("%s\n", pwbuff);
        return 0;
    }
    else if (fourChar(hash, pwbuff)) // 4 char
    {
        printf("%s\n", pwbuff);
        return 0;
    }
}

bool fourChar(string argvHash, char* checkString)
{
    bool innerMatching = false;
    checkString[4] = '\0';
    for (char i = 'A'; i <= 'z'; i++) // nested for loops to go through cyclicly, AAAA, AAAB...AAAz, AABA...AAzz etc
    {                                   // resulting in a password generation to then use as the hash key
        if (i == 'Z')
        {
            i+= 6;
        }
        checkString[0] = i;
        for (char o = 'A'; o <= 'z'; o++)
        {
            if (o == 'Z')
            {
                o+= 6;
            }
            checkString[1] = o;
            for (char t = 'A'; t <= 'z'; t++)
            {
                if (t == 'Z')
                {
                    t+= 6;
                }
                checkString[2] = t;
                for (char n = 'A'; n <= 'z'; n++)
                {
                    if (n == 'Z')
                    {
                        n+= 6;
                    }
                    checkString[3] = n;
                    if (strcmp(crypt(checkString, "50"), argvHash) == 0) // this is where the current generated PW
                    {                                                   // is hashed and checked against the inputted hash.
                        innerMatching = true;                           // If it matches using strcmp a bool of true is
                        break;                                          // assigned and used to break out of the loops
                    }                                                   // and returned and used as the trigger for the if
                }                                                       // statements in main(), signalling to printf and end.
                if (innerMatching == true)
                {
                    break;
                }
            }
            if (innerMatching == true)
            {
                break;
            }
        }
        if (innerMatching == true)
        {
            break;
        }
    }
    return innerMatching;
}

bool threeChar(string argvHash, char* checkString)
{
    bool innerMatching = false;
    checkString[3] = '\0';
    for (char i = 'A'; i <= 'z'; i++)
    {
        if (i == 'Z')
        {
            i+= 6;
        }
        checkString[0] = i;
        for (char o = 'A'; o <= 'z'; o++)
        {
            if (o == 'Z')
            {
                o+= 6;
            }
            checkString[1] = o;
            for (char t = 'A'; t <= 'z'; t++)
            {
                if (t == 'Z')
                {
                    t+= 6;
                }
                checkString[2] = t;
                if (strcmp(crypt(checkString, "50"), argvHash) == 0)
                {
                    innerMatching = true;
                    break;
                }
            }
            if (innerMatching == true)
            {
                break;
            }
        }
        if (innerMatching == true)
        {
            break;
        }
    }
    return innerMatching;
}

bool oneChar(string argvHash, char* checkString)
{
    checkString[1] = '\0';
    bool innerMatching = false;
    for (char i = 'A'; i <= 'z'; i++)
    {
        if (i == 'Z')
        {
            i+= 6;
        }
        checkString[0] = i;
        if (strcmp(crypt(checkString, "50"), argvHash) == 0)
        {
            innerMatching = true;
            break;
        }
    }
    return innerMatching;
}

bool twoChar(string argvHash, char* checkString)
{
    bool innerMatching = false;
    int y;
    for (y = 0; y < 3; y++)
    checkString[2] = '\0';
    for (char i = 'A'; i <= 'z'; i++)
    {
        if (i == 'Z')
        {
            i+= 6;
        }
        checkString[0] = i;
        for (char o = 'A'; o <= 'z'; o++)
        {
            if (i == 'Z')
            {
                i+= 6;
            }
            checkString[1] = o;
            if (strcmp(crypt(checkString, "50"), argvHash) == 0)
            {
                innerMatching = true;
                break;
            }
        }
        if (innerMatching == true)
        {
            break;
        }
    }
    return innerMatching;
}

//50fkUxYHbnXGw == rofl
//50J/OSS0eeYfw == g
//504vM.zaIrWE. == i
//503ri32DnOw4o == gg
//50H754xY4txkg == Ap
//507wygxQdH/S. == hHh
//50SbnoOMMFM66 == Aaz
//50Q1pzlmX3tBU == jCzP
//500MuSTiEMnNQ == aDaM

/*
andi:50.jPgLzVirkc
jason:50YHuxoCN9Jkc
malan:50QvlJWn2qJGE
mzlatkova:50CPlMDLT06yY
patrick:50WUNAFdX/yjA
rbowden:50fkUxYHbnXGw
summer:50C6B0oz0HWzo
stelios:50nq4RV/NVU0I
wmartin:50vtwu4ujL.Dk
zamyla:50i2t3sOSAZtk
*/
