# InfectionSimulator
A program that simulates the spread of an infection on a grid or map, where each cell can be in one of several states, represented by different characters:

- `.` represents an empty cell.
- `p` represents a person who is not infected.
- `v` represents an infected person.
- `A` to `I` represent doctors with varying levels of power.

The `main` function prompts the user to select a test case, each of which sets up a different initial state for the map and then runs the simulation. Here's what each test case does:

The `infect` function simulates an infection spreading from a specific cell. If the cell contains a person (`p`), it changes that person to an infected state (`v`) and then recursively tries to infect its neighbouring cells.

The `infectWithProbability` function is similar but also takes into account a power level and uses random numbers to determine whether each neighbouring cell gets infected.

The `random` function generates random numbers using the middle square method, which involves squaring the seed, extracting the middle digits of the result, and using them as the new seed. This process is repeated a specified number of times.

The `isDoctor` and `isInfected` functions check whether a given cell contains a doctor or an infected person, respectively.

The `getProtectionLevel` function calculates the protection level of a cell based on its neighbouring cells.

The `printMap` function prints out the current state of the map.

The `countCharacter` function counts how many times a specific character appears on the map. This could be used to count how many people are infected or how many doctors are present, for example. 

For example, if you run the simulation with the following setup:

```cpp
int width = 8;
int height = 8;
char map[MAX_SIZE][MAX_SIZE] = {
    {'p', 'p', 'p', 'p', 'p', 'p', 'p', 'p'},
    {'p', 'p', 'p', 'p', 'p', 'p', 'p', 'p'},
    {'p', 'p', 'p', 'p', 'p', 'p', 'p', 'p'},
    {'p', 'p', 'p', 'p', 'C', 'C', '.', '.'},
    {'.', '.', '.', '.', '.', '.', '.', '.'},
    {'.', '.', '.', '.', '.', '.', '.', '.'}
};
cout << "========================" << endl;
printMap(map, width, height);
cout << "========================" << endl;
infectWithPower(map, width, height, 3, 3, 8);
cout << "========================" << endl;
printMap(map, width, height);
cout << "========================" << endl;
```

The output will be:
```
========================
p p p p p p p p 
p p p p p p p p 
p p p p p p p p 
p p p p p p p p 
p p p p p p p p 
p p p p p C p p 
p p p p p p p p 
p p p p p p p p 
========================
========================
2 3 4 5 4 3 2 1 
3 4 5 6 5 4 3 2 
4 5 6 7 6 5 4 3 
5 6 7 8 7 6 5 4 
4 5 6 7 6 5 4 3 
3 4 5 6 5 C p 2 
2 3 4 5 4 p p 1 
1 2 3 4 3 2 1 p 
========================
```
This shows that the infectWithPower function has spread the infection from the cell at (3,3) with a power level of 8.
