#include <iostream>
#include <vector>
using namespace std;

vector<vector<int>> InitializeDisk(int t, int d)
{
    // 1. Initializing vector
    vector<vector<int>> result(t, vector<int>(d)); // Initialize result with size t x 1
    
    // 2. Initializing rod with disks
    for (int i = 0; i < d; i++)
    {
        result[0][i] = d-i;
    }

    // 3. Initializing rod without disks to zero
    for (int i = 1; i < t; i++) {
        for (int j = 0; j < d; j++)
        {
            result[i][j] = 0;
        }
    }
    return result;
}

void PrintTower(vector<vector<int>> v)
{
    int numRows = v.size();
    int numCols = v[0].size();
    
    for (int r = 0; r < numRows; r++)
    {
        cout << "[" << r + 1 << "] ";
        if (v[r][0] > 0)
        {
            for (int j = 0; j < numCols; j++)
            {
                cout << v[r][j] << " ";
            }
        }

        cout << endl;
    }
    cout << endl;
}

// Function to display prompt for tower input
void DisplayTowerPrompt(int status, int rods) {
    cout << endl;
    cout << "[" << status << "] " << "From which tower will you move a disk to which tower? (from=[1";
    for (int i = 1; i < rods; i++) {
        cout << "|" << i + 1;
    }
    cout << "], to = [1";

    for (int i = 1; i < rods; i++) {
        cout << "|" << i + 1;
    }
    cout << "]):";
}

int getPeakDisk(const vector<int>& v) {
    if (v.empty()) {
        // If the vector is empty, return -1 indicating no disk
        return 0;
    }
    // Iterate through the rod vector from the end
    for (int i = v.size() - 1; i >= 0; --i) {
        if (v[i] != 0) {
            // Return the first non-zero element encountered
            return v[i];
        }
    }
    // If all elements are zero, return -1 indicating no disk
    return 0;
}



int AskInput(vector<vector<int>>& v, int status, int rods) {

    // Display tower prompt
    DisplayTowerPrompt(status, rods);

    int from, to;
    cin >> from >> to;

    // If index out of range or when trying to move disk at the same rod
    if (from == to || from <= 0 || from > rods || to <= 0 || to > rods)
    {
        cout << "=> Move failed!" << endl;
    }
    
    else
    {
        int fromElement = v.at(from - 1).at(0);
        
        int toPeakElement = getPeakDisk(v[to]);
        cout << "toPeakElement : " << toPeakElement;


        // There's disk in the rod moving from and rod moving to has a disk greater than disk being moved
        if (fromElement != 0 && toPeakElement > fromElement) {
            status = status + 1;
        }
    }

    return status;
}

void GameSetup(int& rods, int& disks)
{
    cout << "Welcome to Tower of Hanoi!" << endl;
    cout << "Let's set up the game." << endl<< endl;

    cout << "Total number of rods: ";
    cin >> rods;

    cout << "Total number of disks: ";
    cin >> disks;
    cout << endl;
}



int main()
{
    int rods;
    int disks;
    
    GameSetup(rods, disks);

    // 1. Initialize disks  
    vector<vector<int>> towers = InitializeDisk(rods, disks);
    
    // 2. Print towers
    PrintTower(towers);

    // 3. Ask for input move
    int status = 1;
    while (1)
    {
        status = AskInput(towers, status, rods);
    }

    // 4. Print end Ask replay
    // 5. end
 }


    //IsMoveAllowed()
    //    
    //MoveDisk()
 

