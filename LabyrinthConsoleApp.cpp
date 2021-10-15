// LabyrinthConsoleApp.cpp


#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <list>

#define DEBUG 0

using namespace std;

struct pos
{
    unsigned int floor;
    unsigned int row;
    unsigned int column;
};

typedef vector<string> Floor_Type;
typedef vector<Floor_Type> Labyrinth_Type;
typedef list<Labyrinth_Type> LabyrinthList_Type;


class Labyrinth {
private:
    pos currentPos_ = {0, 0, 0};
    Floor_Type Floor_;
    Labyrinth_Type Labyrinth_;
    LabyrinthList_Type LabyrinthList_;
    int steps;
    bool foundExit;
    char neighbour_symbol;
    void findPath();
    void takeStep();

public:
    void readInput(string filename);
    void explore();
};

void Labyrinth::takeStep()
{
    if (neighbour_symbol == 'E')
        foundExit = true;
   
    steps++;
    Labyrinth_.at(currentPos_.floor).at(currentPos_.row).at(currentPos_.column) = 'v'; // mark visited path (to not go back and forth)
    findPath();
}


// This recursive function uses trial and error for all directions to find the correct path
void Labyrinth::findPath()  
{
    if (foundExit)
        return;

    // move up (if possible)
    if (currentPos_.floor < Labyrinth_.size() - 1) // if not last/highest floor
    {
        neighbour_symbol = Labyrinth_.at(currentPos_.floor + 1).at(currentPos_.row).at(currentPos_.column); 
        if (neighbour_symbol == '.' || neighbour_symbol == 'E') // if above can be traversed
        {
            currentPos_.floor += 1;
            takeStep();
        }
    }
    if (foundExit) 
        return;
        

    // move east
    if (currentPos_.column < Labyrinth_.at(currentPos_.floor).at(currentPos_.row).size() - 1) // not in last column
    {
        neighbour_symbol = Labyrinth_.at(currentPos_.floor).at(currentPos_.row).at(currentPos_.column + 1);
        if (neighbour_symbol == '.' || neighbour_symbol == 'E') // if east can be traversed
        {
            currentPos_.column += 1;
            takeStep();
        }
    }
    if (foundExit)
        return;


    // move south
    if (currentPos_.row < Labyrinth_.at(currentPos_.floor).size() - 1) // not in last row
    {
        neighbour_symbol = Labyrinth_.at(currentPos_.floor).at(currentPos_.row + 1).at(currentPos_.column);
        if (neighbour_symbol == '.' || neighbour_symbol == 'E') // if south can be traversed
        {
            currentPos_.row += 1;
            takeStep();
        }
    }
    if (foundExit)
        return;
            

    // move west
    if (currentPos_.column > 0) // not in first column
    {
        neighbour_symbol = Labyrinth_.at(currentPos_.floor).at(currentPos_.row).at(currentPos_.column - 1);
        if (neighbour_symbol == '.' || neighbour_symbol == 'E') // if west can be traversed
        {
            currentPos_.column -= 1;
            takeStep();
        }
    }
    if (foundExit)
        return;


    // move north
    if (currentPos_.row > 0) // not in first row
    {
        neighbour_symbol = Labyrinth_.at(currentPos_.floor).at(currentPos_.row - 1).at(currentPos_.column);
        if (neighbour_symbol == '.' || neighbour_symbol == 'E') // if north can be traversed
        {
            currentPos_.row -= 1;
            takeStep();
        }
    }
    if (foundExit)
        return;


    // move down
    if (currentPos_.floor > 0) // if not first/lowest floor
    {
        neighbour_symbol = Labyrinth_.at(currentPos_.floor - 1).at(currentPos_.row).at(currentPos_.column);
        if (neighbour_symbol == '.' || neighbour_symbol == 'E')// if below can be traversed
        {
            currentPos_.floor -= 1;
            takeStep();
        }
    }
    if (foundExit)
        return;
        
    steps--; // if no direction worked, take a step back

    return;
}


// The explore() function iterates through every 3D Labyrinth in the list and calls findPath() to calculate the path for each one
void Labyrinth::explore()
{
    LabyrinthList_Type::iterator currentLab;
    for (currentLab = LabyrinthList_.begin(); currentLab != LabyrinthList_.end(); currentLab++)
    {
        currentPos_ = { 0,0,currentLab->front().front().find('S')}; // assuming the start is somewhere in the first row}
        Labyrinth_ = *currentLab;
        steps = 0;
        foundExit = false;

        findPath();
        if (foundExit)
            cout << "Entkommen in " << steps << " Minute(n)!" << endl;
        else
            cout << "Gefangen :-(" << endl;
    }
}


// This function reads a labyrinth describing file and saves the input to an object of the Labyrinth class
void Labyrinth::readInput(string path)
{
    ifstream file;
    string line;
    bool nextLabyrinth = false;
    file.open(path); 
    if (file.is_open())
    {
        while(getline(file, line))
        {
            if (line[0] >= '1' && line[0] <= '9')
            {
                if (nextLabyrinth)
                    LabyrinthList_.push_back(Labyrinth_);
                nextLabyrinth = true;
                Labyrinth_.clear();
                if (DEBUG)
                    cout << "read sizes of the labyrinth (not used) " << endl;
            }
            else if (line[0] == '0')
            {
                LabyrinthList_.push_back(Labyrinth_);
                if (DEBUG)
                    cout << "read 0s (end of input)" << endl;
                return;
            }
            else if (line.length() == 0) // empty line ends floor
            {
                Labyrinth_.push_back(Floor_);
                Floor_.clear();
                if (DEBUG)
                    cout << "read empty line (new floor)" << endl;
            }
            else if (line[0] == 'E' || line[0] == 'S' || line[0] == '#' || line[0] == '.')
            { 
                Floor_.push_back(line); // add line to floor
                if(DEBUG)
                    cout << "read normal floor line" << endl;
            }
            else
            {
                cerr << "unknown input symbol" << endl;
            }
        }
    }
    else
    {
        cerr << "Error while trying to open the input file!";
    }
}


int main()
{
    Labyrinth lab;
    lab.readInput("labyrinth.txt"); // labyrinth.txt (the input) is located in the local folder
    lab.explore();
    return 0;
}