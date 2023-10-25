#include <iostream>
#include "infection.h"
using namespace std;

//this function simply returns you the maximum of the two given integers a and b
int max(int a, int b)
{
    return a>b?a:b;
}

//this function returns true if the given cell (x,y) is a doctor (for the infectWithPower simulation) and returns false otherwise
bool isDoctor(char map[][MAX_SIZE], int width, int height, int x, int y)
{
    if(x<0 || x>=width || y<0 || y>=height)
        return false;
    else
        return map[y][x] >= 'A' && map[y][x] <= 'I';
}

//this function returns true if the given cell (x,y) is infected (for the infectWithPower simulation) and returns false otherwise
bool isInfected(char map[][MAX_SIZE], int width, int height, int x, int y)
{
    if(x<0 || x>=width || y<0 || y>=height)
        return false;
    return map[y][x] >= '0' && map[y][x] <= '9';
}


void printMap(char map[][MAX_SIZE], int width, int height, int x, int y)
{
    // base case 
    if (y == height) {
        return;
    }
    cout << map[y][x] << " ";
    if (x < width - 1){
        printMap(map, width, height, x+1, y);
    }
    else {
        cout << endl;
        printMap(map, width, height, 0, y+1);
    }
}

int countCharacter(char map[][MAX_SIZE], int width, int height, char c, int x, int y)
{
    // base case 
    if (y == height) {
        return 0;
    }
    else {
        if (x < width - 1){
            if (map[y][x] == c){
                return 1 + countCharacter(map, width, height, c, x+1, y);
            }
            else {
                return 0 + countCharacter(map, width, height, c, x+1, y);
            }
        }
        else {
            if (map[y][x] == c){
                return 1 + countCharacter(map, width, height, c, 0, y+1);
            }
            else {
                return 0 + countCharacter(map, width, height, c, 0, y+1);
            }
        }
    }
}

int infect(char map[][MAX_SIZE], int width, int height, int x, int y)
{
    if ((x < 0 || y < 0) || (x >= width || y >= height) || map [y][x] != 'p'){
        return 0;
    }
    else{
        map[y][x] = 'v';
        return infect(map, width, height, x+1, y), infect(map, width, height, x, y-1), infect(map, width, height, x-1, y), infect(map, width, height, x, y+1), countCharacter(map, width, height, 'v');
    }
}

int getProtectionLevel(char map[][MAX_SIZE], int width, int height, int x, int y)
{
    // a cell that is outside of the world
    if ((x < 0 || y < 0) || (x >= width || y >= height)){
        return 0;
    }
    // a cell that is not 'p'
    else if (map [y][x] != 'p'){
        return 0;
    }
    // return the maximum value of all protection levels this cell can get
    else {
        int up_power = 0, down_power = -1, right_power = -2, left_power = -3, max_power = 0;
        // right
        if (y >= 0 && y < height && x+1 >= 0 && x+1 < width){
            if (int(map[y][x+1]) < 74 && int(map [y][x+1]) > 64){
                right_power = int(map[y][x+1]) - 64;
            }
        }
        // up
        if (y-1 >= 0 && y-1 < height && x >= 0 && x < width){
            if (int(map[y-1][x]) < 74 && int(map [y-1][x]) > 64){
                up_power = int(map[y-1][x]) - 64;
            }
        }
        // left
        if (y >= 0 && y < height && x-1 >= 0 && x-1 < width){
            if (int(map[y][x-1]) < 74 && int(map [y][x-1]) > 64){
                left_power = int(map[y][x-1]) - 64;
            }
        }
        // down
        if (y+1 >= 0 && y+1 < height && x >= 0 && x < width){
            if (int(map[y+1][x]) < 74 && int(map [y+1][x]) > 64){
                down_power = int(map[y+1][x]) -64;
            }
        }
        // take the max power
        max_power = (up_power>down_power)?(up_power>right_power)?(up_power>left_power)?up_power:left_power:(right_power>left_power)?right_power:left_power:(down_power>right_power)?(down_power>left_power)?down_power:left_power:(right_power>left_power)?right_power:left_power; 
        return max_power;
    }
}

void infectWithPower(char map[][MAX_SIZE], int width, int height, int x, int y, int power)
{
    if (power <= 1){
        return;
    }
    // turn int 1 to character '1'
    char power_current = char(power+48);
    char power_neighbour = power_current - 1; 
     // a cell that is outside of the world
    if ((x < 0 || y < 0) || (x >= width || y >= height)){
        return;
    }
    // If the cell is empty or is a doctor cell,
    else if (isDoctor(map, width, height, x, y) || map[y][x] == '.' || int(map[y][x] == 0)){
        return;
    }

    else if (power < getProtectionLevel(map, width, height, x, y)){
        return;
    }

    else {
        if (map[y][x] == 'p' && power > getProtectionLevel(map, width, height, x, y)){
            map[y][x] = power_current;
        }

        if (map[y][x] == 'p'){
            return;
        }

        bool right = false, left = false, up = false, down = false;
        // find for neighbouring people to infect in the order of R -> U -> L -> D
        // right
        if (y >= 0 && y < height && x+1 >= 0 && x+1 < width){
            if ((map[y][x+1] == 'p' && (power-1) > getProtectionLevel(map, width, height, x+1, y)) || (map[y][x+1] >= '1' && map[y][x+1] < '9' && map[y][x+1] < power_neighbour)){
                map[y][x+1] = power_neighbour;
                right = true;
            }
        }
        // up
        if (y-1 >= 0 && y-1 < height && x >= 0 && x < width){
            if ((map[y-1][x] == 'p' && (power-1) > getProtectionLevel(map, width, height, x, y-1)) || (map[y-1][x] >= '1' && map[y-1][x] < '9' && map[y-1][x] < power_neighbour)){
                map[y-1][x] = power_neighbour;
                up = true;
            }
        }
        // left
        if (y >= 0 && y < height && x-1 >= 0 && x-1 < width){
            if ((map[y][x-1] == 'p' && (power-1) > getProtectionLevel(map, width, height, x-1, y)) || (map[y][x-1] >= '1' && map[y][x-1] < '9' && map[y][x-1] < power_neighbour)){
                map[y][x-1] = power_neighbour;
                left = true;
            }
        }
        // down
        if (y+1 >= 0 && y+1 < height && x >= 0 && x < width){
            if ((map[y+1][x] == 'p' && (power-1) > getProtectionLevel(map, width, height, x, y+1)) || (map[y+1][x] >= '1' && map[y+1][x] < '9' && map[y+1][x] < power_neighbour)){
                map[y+1][x] = power_neighbour;
                down = true;
            }
        }
        if (right || left || up || down){
            return infectWithPower(map, width, height, x+1, y, power-1), infectWithPower(map, width, height, x , y-1, power-1), infectWithPower(map, width, height, x-1, y, power-1), infectWithPower(map, width, height, x, y+1, power-1);
        }
        else{
            return ;
        }
    }
}

int random(int seed, int n)
{
    if (n <= 0){
        return seed;
    }

    int number_8digits [8] = {0, 0, 0, 0, 0, 0 ,0, 0};
    int square = seed*seed;

    if (square > 0){
        number_8digits [7] = square % 10;
        square /= 10;
    }
    if (square > 0){
        number_8digits [6] = square % 10;
        square /= 10;
    }
    if (square > 0){
        number_8digits [5] = square % 10;
        square /= 10;
    }
    if (square > 0){
        number_8digits [4] = square % 10;
        square /= 10;
    }
    if (square > 0){
        number_8digits [3] = square % 10;
        square /= 10;
    }
    if (square > 0){
        number_8digits [2] = square % 10;
        square /= 10;
    }
    if (square > 0){
        number_8digits [1] = square % 10;
        square /= 10;
    }
    if (square > 0){
        number_8digits [0] = square % 10;
    }

    return random(1000*number_8digits[2] + 100*number_8digits[3] + 10*number_8digits[4] + number_8digits[5], n - 1);

    
}

void infectWithProbability(char map[][MAX_SIZE], int width, int height, int x, int y, int threshold, int seed, int n)
{
    
    // turn int 1 to character '1'
    char n_current = char(n+48);
    char n_neighbour = n_current + 1; 

     // a cell that is outside of the world
    if ((x < 0 || y < 0) || (x >= width || y >= height) || map [y][x] == '.'){
        return;
    }

    else {
        if (map[y][x] == 'p'){
            map[y][x] = n_current;
        }

        int rand_seed = random(seed, n);

        if (rand_seed <= threshold){
            return;
        }
        // find for neighbouring people to infect in the order of R -> U -> L -> D
        // right
        if ((map[y][x+1] == 'p') || (map[y][x+1] >= '1' && map[y][x+1] <= '9' && map[y][x+1] > n_neighbour)){
            map[y][x+1] = n_neighbour;
        }
        // up
        if ((map[y-1][x] == 'p') || (map[y-1][x] >= '1' && map[y-1][x] <= '9' && map[y-1][x] > n_neighbour)){
            map[y-1][x] = n_neighbour;
        }
        // left
        if ((map[y][x-1] == 'p') || (map[y][x-1] >= '1' && map[y][x-1] <= '9' && map[y][x-1] > n_neighbour)){
            map[y][x-1] = n_neighbour;
        }
        // down
        if ((map[y+1][x] == 'p') || (map[y+1][x] >= '1' && map[y+1][x] <= '9' && map[y+1][x] > n_neighbour)){
            map[y+1][x] = n_neighbour;
        }
        return infectWithProbability(map, width, height, x+1, y, threshold, seed, n+1), infectWithProbability(map, width, height, x , y-1, threshold, seed, n+1), infectWithProbability(map, width, height, x-1, y, threshold, seed, n+1), infectWithProbability(map, width, height, x, y+1, threshold, seed, n+1);        
    }
}

int main()
{
    cout << "Welcome to the infection simulator!" << endl;
    cout << "Which test case do you want to run?" << endl;
    int testCaseNumber = 0;
    cin >> testCaseNumber;

    cout << "Running test case " << testCaseNumber << "... If you do not see a complete output below, that could mean runtime errors happened (e.g. infinite recursion). Check your code carefully." << endl;

    if(testCaseNumber == 1)
    {
        int width = 6;
        int height = 5;
        char map[MAX_SIZE][MAX_SIZE] = {
            {'.', 'p', '.', 'p', '.', '.'},
            {'p', 'p', 'p', '.', 'p', '.'},
            {'.', 'p', '.', 'p', 'p', '.'},
            {'p', 'p', '.', '.', '.', 'p'},
            {'.', 'p', '.', '.', 'p', '.'}
        };
        cout << "========================" << endl;
        printMap(map, width, height);
        cout << "========================" << endl;
    }
    else if(testCaseNumber == 2)
    {
        int width = 5;
        int height = 6;
        char map[MAX_SIZE][MAX_SIZE] = {
            {'.', 'p', '.', 'p', '.'},
            {'p', 'p', 'p', '.', 'p'},
            {'.', 'p', '.', 'p', 'p'},
            {'p', 'p', '.', '.', '.'},
            {'.', 'p', '.', '.', 'p'},
            {'p', 'p', 'p', 'p', 'p'}
        };
        cout << "========================" << endl;
        printMap(map, width, height);
        cout << "========================" << endl;
    }
    else if(testCaseNumber == 3)
    {
        int width = 5;
        int height = 6;
        char map[MAX_SIZE][MAX_SIZE] = {
            {'.', 'p', 'p', 'p', 'p'},
            {'p', 'p', 'p', 'p', 'p'},
            {'p', 'p', '.', 'p', 'p'},
            {'p', 'p', 'p', 'p', 'p'},
            {'p', 'p', '.', 'p', 'p'},
            {'p', 'p', 'p', 'p', 'p'}
        };
        cout << "========================" << endl;
        printMap(map, width, height);
        cout << "========================" << endl;
        cout << "#infected = " << infect(map, width, height, 1, 1) << endl;
        cout << "========================" << endl;
        printMap(map, width, height);
        cout << "========================" << endl;
    }
    else if(testCaseNumber == 4)
    {
        int width = 5;
        int height = 6;
        char map[MAX_SIZE][MAX_SIZE] = {
            {'.', 'p', 'p', 'p', 'p'},
            {'p', 'p', 'p', 'p', 'p'},
            {'p', 'p', 'p', 'p', 'p'},
            {'p', 'p', 'p', 'p', 'p'},
            {'p', 'p', '.', 'p', 'p'},
            {'p', 'p', 'p', 'p', 'p'}
        };
        cout << "========================" << endl;
        printMap(map, width, height);
        cout << "========================" << endl;
        infect(map, width, height, 1, 1); 
        //this test case is very similar to the previous test case
        //the only difference is that we do not output the return value of the infect function
        //this is to give partial credits to students who could only modify the map correctly
        //but not getting a correct return value
        cout << "========================" << endl;
        printMap(map, width, height);
        cout << "========================" << endl;
    }
    else if(testCaseNumber == 5)
    {
        int width = 5;
        int height = 6;
        char map[MAX_SIZE][MAX_SIZE] = {
            {'p', 'p', '.', 'p', 'p'},
            {'p', 'p', 'p', '.', '.'},
            {'p', 'p', '.', 'p', 'p'},
            {'p', 'p', 'p', 'p', 'p'},
            {'p', '.', '.', '.', '.'},
            {'p', 'p', 'p', 'p', 'p'}
        };
        cout << "========================" << endl;
        printMap(map, width, height);
        cout << "========================" << endl;
        cout << "#infected = " << infect(map, width, height, 4, 5) << endl;
        cout << "========================" << endl;
        printMap(map, width, height);
        cout << "========================" << endl;
    }
    else if(testCaseNumber == 6)
    {
        int width = 5;
        int height = 6;
        char map[MAX_SIZE][MAX_SIZE] = {
            {'.', 'p', '.', 'p', '.'},
            {'p', 'p', 'p', '.', 'p'},
            {'.', 'p', '.', 'p', 'p'},
            {'p', 'p', '.', '.', '.'},
            {'.', 'p', '.', '.', 'p'},
            {'p', 'p', 'p', 'p', 'p'}
        };
        cout << "========================" << endl;
        printMap(map, width, height);
        cout << "========================" << endl;
        cout << "#infected = " << infect(map, width, height, 0, 0) << endl;
        cout << "========================" << endl;
        printMap(map, width, height);
        cout << "========================" << endl;
    }
    else if(testCaseNumber == 7)
    {
        int width = 5;
        int height = 6;
        char map[MAX_SIZE][MAX_SIZE] = {
            {'.', 'p', '.', 'p', '.'},
            {'p', 'p', 'p', '.', 'v'},
            {'.', 'p', '.', 'v', 'v'},
            {'p', 'p', '.', '.', '.'},
            {'.', 'p', '.', '.', 'p'},
            {'p', 'p', 'p', 'p', 'p'}
        };
        cout << "========================" << endl;
        printMap(map, width, height);
        cout << "========================" << endl;
        cout << "# of p = " << countCharacter(map, width, height, 'p') << endl;
        cout << "# of v = " << countCharacter(map, width, height, 'v') << endl;
        cout << "# of . = " << countCharacter(map, width, height, '.') << endl;
        cout << "========================" << endl;
    }
    else if(testCaseNumber == 8)
    {
        int width = 8;
        int height = 5;
        char map[MAX_SIZE][MAX_SIZE] = {
            {'.', 'p', '.', 'p', '.', '.', '.', 'p'},
            {'p', 'p', 'p', 'p', 'p', '.', '.', '.'},
            {'.', 'p', 'p', 'B', 'p', '.', '.', 'p'},
            {'.', '.', '.', '.', 'p', 'p', '.', 'p'},
            {'.', '.', '.', '.', 'p', '.', '.', '.'}
        };
        cout << "========================" << endl;
        cout << "getProtectionLevel at (3,2) = " << getProtectionLevel(map, width, height, 3, 2) << endl;
        cout << "getProtectionLevel at (2,2) = " << getProtectionLevel(map, width, height, 2, 2) << endl;
        cout << "getProtectionLevel at (4,2) = " << getProtectionLevel(map, width, height, 4, 2) << endl;
        cout << "getProtectionLevel at (3,1) = " << getProtectionLevel(map, width, height, 3, 1) << endl;
        cout << "getProtectionLevel at (3,3) = " << getProtectionLevel(map, width, height, 3, 3) << endl;
        cout << "========================" << endl;
    }
    else if(testCaseNumber == 9)
    {
        int width = 8;
        int height = 5;
        char map[MAX_SIZE][MAX_SIZE] = {
            {'.', 'p', '.', 'C', '.', '.', '.', 'p'},
            {'p', 'p', 'p', 'p', 'p', '.', '.', '.'},
            {'.', 'p', 'A', 'B', 'p', '.', '.', 'p'},
            {'.', '.', '.', '.', 'p', 'p', '.', 'p'},
            {'.', '.', '.', '.', 'p', '.', '.', '.'}
        };
        cout << "========================" << endl;
        cout << "getProtectionLevel at (3,2) = " << getProtectionLevel(map, width, height, 3, 2) << endl;
        cout << "getProtectionLevel at (2,2) = " << getProtectionLevel(map, width, height, 2, 2) << endl;
        cout << "getProtectionLevel at (4,2) = " << getProtectionLevel(map, width, height, 4, 2) << endl;
        cout << "getProtectionLevel at (3,1) = " << getProtectionLevel(map, width, height, 3, 1) << endl;
        cout << "getProtectionLevel at (3,3) = " << getProtectionLevel(map, width, height, 3, 3) << endl;
        cout << "========================" << endl;
    }
    else if(testCaseNumber == 10)
    {
        int width = 8;
        int height = 5;
        char map[MAX_SIZE][MAX_SIZE] = {
            {'.', 'p', '.', 'p', '.', '.', '.', 'p'},
            {'p', 'p', 'p', 'p', 'p', '.', '.', '.'},
            {'.', 'p', 'p', 'p', 'p', '.', '.', 'p'},
            {'.', '.', '.', '.', 'p', 'p', '.', 'p'},
            {'.', '.', '.', '.', 'p', '.', '.', '.'}
        };
        cout << "========================" << endl;
        printMap(map, width, height);
        cout << "========================" << endl;
        infectWithPower(map, width, height, 1, 1, 3);
        cout << "========================" << endl;
        printMap(map, width, height);
        cout << "========================" << endl;
    }
    else if(testCaseNumber == 11)
    {
        int width = 8;
        int height = 8;
        char map[MAX_SIZE][MAX_SIZE] = {
            {'p', 'p', 'p', 'p', 'p', 'p', 'p', 'p'},
            {'p', 'p', 'p', 'p', 'p', 'p', 'p', 'p'},
            {'p', 'p', 'p', 'p', 'p', 'p', 'p', 'p'},
            {'p', 'p', 'p', 'p', 'p', 'p', 'p', 'p'},
            {'p', 'p', 'p', 'p', 'p', 'p', 'p', 'p'},
            {'p', 'p', 'p', 'p', 'p', 'p', 'p', 'p'},
            {'p', 'p', 'p', 'p', 'p', 'p', 'p', 'p'},
            {'p', 'p', 'p', 'p', 'p', 'p', 'p', 'p'},
        };
        cout << "========================" << endl;
        printMap(map, width, height);
        cout << "========================" << endl;
        infectWithPower(map, width, height, 3, 3, 8);
        cout << "========================" << endl;
        printMap(map, width, height);
        cout << "========================" << endl;
    }
    else if(testCaseNumber == 12)
    {
        int width = 8;
        int height = 8;
        char map[MAX_SIZE][MAX_SIZE] = {
            {'p', 'p', 'p', 'p', 'p', 'p', 'p', 'p' },
            {'p', 'p', 'p', 'p', 'p', 'p', 'p', 'p'},
            {'p', 'p', 'p', 'p', 'p', 'p', 'p', 'p'},
            {'p', 'p', 'p', 'p', 'p', 'p', 'p', 'p'},
            {'p', 'p', 'p', 'p', 'p', 'p', 'p', 'p'},
            {'p', 'p', 'p', 'p', 'p', 'C', 'p', 'p'},
            {'p', 'p', 'p', 'p', 'p', 'p', 'p', 'p'},
            {'p', 'p', 'p', 'p', 'p', 'p', 'p', 'p'},
        };
        cout << "========================" << endl;
        printMap(map, width, height);
        cout << "========================" << endl;
        infectWithPower(map, width, height, 3, 3, 8);
        cout << "========================" << endl;
        printMap(map, width, height);
        cout << "========================" << endl;
    }
    else if(testCaseNumber == 13)
    {
        cout << "========================" << endl;
        cout << "random(1234, 1) = " << random(1234, 1) << endl;
        cout << "random(1234, 2) = " << random(1234, 2) << endl;
        cout << "random(1234, 3) = " << random(1234, 3) << endl;
        cout << "random(1234, 4) = " << random(1234, 4) << endl;
        cout << "========================" << endl;
    }
    else if(testCaseNumber == 14)
    {
        cout << "========================" << endl;
        cout << "random(1001, 1) = " << random(1001, 1) << endl;
        cout << "random(1001, 2) = " << random(1001, 2) << endl;
        cout << "random(1001, 3) = " << random(1001, 3) << endl;
        cout << "random(1001, 4) = " << random(1001, 4) << endl;
        cout << "========================" << endl;
    }
    else if(testCaseNumber == 15)
    {
        int width = 8;
        int height = 8;
        char map[MAX_SIZE][MAX_SIZE] = {
            {'p', 'p', 'p', 'p', 'p', 'p', 'p', 'p'},
            {'p', 'p', 'p', 'p', 'p', 'p', 'p', 'p'},
            {'p', 'p', 'p', 'p', 'p', 'p', 'p', 'p'},
            {'p', 'p', 'p', 'p', 'p', 'p', 'p', 'p'},
            {'p', 'p', 'p', 'p', 'p', 'p', 'p', 'p'},
            {'p', 'p', 'p', 'p', 'p', 'p', 'p', 'p'},
            {'p', 'p', 'p', 'p', 'p', 'p', 'p', 'p'},
            {'p', 'p', 'p', 'p', 'p', 'p', 'p', 'p'},
        };
        cout << "========================" << endl;
        printMap(map, width, height);
        cout << "========================" << endl;
        infectWithProbability(map, width, height, 4, 4, 3200, 1234);
        cout << "========================" << endl;
        printMap(map, width, height);
        cout << "========================" << endl;
    }
    else if(testCaseNumber == 16)
    {
        int width = 8;
        int height = 8;
        char map[MAX_SIZE][MAX_SIZE] = {
            {'p', 'p', 'p', 'p', 'p', 'p', 'p', 'p'},
            {'p', 'p', 'p', 'p', 'p', 'p', 'p', 'p'},
            {'p', 'p', 'p', 'p', 'p', 'p', 'p', 'p'},
            {'p', 'p', 'p', 'p', 'p', 'p', 'p', 'p'},
            {'p', 'p', 'p', 'p', 'p', 'p', 'p', 'p'},
            {'p', 'p', 'p', '.', '.', 'p', 'p', 'p'},
            {'p', 'p', 'p', 'p', 'p', 'p', 'p', 'p'},
            {'p', 'p', 'p', 'p', 'p', 'p', 'p', 'p'},
        };
        cout << "========================" << endl;
        printMap(map, width, height);
        cout << "========================" << endl;
        infectWithProbability(map, width, height, 4, 4, 3200, 1234);
        cout << "========================" << endl;
        printMap(map, width, height);
        cout << "========================" << endl;
    }

    return 0;
}