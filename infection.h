#ifndef INFECTION_H
#define INFECTION_H

const int MAX_SIZE = 12;
int max(int a, int b);
bool isDoctor(char map[][MAX_SIZE], int width, int height, int x, int y);
bool isInfected(char map[][MAX_SIZE], int width, int height, int x, int y);
void printMap(char map[][MAX_SIZE], int width, int height, int x=0, int y=0);
int countCharacter(char map[][MAX_SIZE], int width, int height, char c, int x=0, int y=0);
int infect(char map[][MAX_SIZE], int width, int height, int x, int y);
int getProtectionLevel(char map[][MAX_SIZE], int width, int height, int x, int y);
void infectWithPower(char map[][MAX_SIZE], int width, int height, int x, int y, int power);
int random(int seed, int n);
void infectWithProbability(char map[][MAX_SIZE], int width, int height, int x, int y, int threshold, int seed, int n=1);

#endif