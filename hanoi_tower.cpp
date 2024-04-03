#include <iostream>
#include <vector>
#include <cstdlib>
#include <string>
using namespace std;

// Initial Game setup
void GameSetup(int& rods, int& disks){
    cout << endl;
    cout << "Welcome to Tower of Hanoi!" << endl;
    cout << "Let's set up the game." << endl<< endl;

    cout << "Total number of rods: ";
    cin >> rods;

    cout << "Total number of disks: ";
    cin >> disks;
    cout << endl;
}


vector<vector<int>> InitializeDisk(int t, int d){
    // Initializing vector of vectors
    vector<vector<int>> result(t); // Initialize result with size t
    
    // Initializing the first vector with disk values
    vector<int> firstVector(d); // Initialize first vector with size d
    for (int i = 0; i < d; i++)
    {
        firstVector[i] = d - i;
    }
    result[0] = firstVector;

    // Leave the rest of the element vectors as empty vectors

    return result;
}


// Print each rods with corresponding disks
void PrintTower(vector<vector<int>> v){
    int numRows = v.size();

    // Iterate through each rod
    for (int r = 0; r < numRows; r++)
    {
        cout << "[" << r + 1 << "] ";

        // Iterate through each disk on the rod
        for (int j = 0; j < v[r].size(); j++)
        {
            if (v[r][j] != 0)
            {
                cout << v[r][j] << " ";
            }
        }
        cout << endl;
    }
    cout << endl;
}



// Function to display prompt for tower input
void DisplayTowerPrompt(int&status, int rods) {
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


// Get peak disk of the rod
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


// Function to move disk from one tower to another
void moveDisk(vector<vector<int>>& v, int from, int to) {
    v[to-1].push_back(v[from-1].back());
    v[from-1].pop_back();
}

// Ask Input to move disk
int AskInput(vector<vector<int>>& v, int& status, int rods) {
    vector<int> target = {3, 2, 1};

    while (1) {
        // Display tower prompt
        DisplayTowerPrompt(status, rods);

        // Get from and to index
        int from, to;
        cin >> from >> to;

        // If index out of range or when trying to move disk at the same rod
        if (from == to || from <= 0 || from > rods || to <= 0 || to > rods) {
            cout << "=> Move failed!" << endl;
        }
        else {
            // Get peak disk of the rod moving from and moving to
            int fromPeakElement = getPeakDisk(v[from - 1]);
            int toPeakElement = getPeakDisk(v[to - 1]);

            // If there's nothing on the rod moving to
            if (fromPeakElement != 0 && toPeakElement == 0) {
                moveDisk(v, from, to);
                cout << "=> Move succeeded!" << endl << endl;
                PrintTower(v);
            }
            // When there's something on the rod moving to
            else if (fromPeakElement != 0 && fromPeakElement < toPeakElement) {
                moveDisk(v, from, to);
                cout << "=> Move succeeded!" << endl << endl;
                PrintTower(v);
            }
            else {
                cout << "Move failed!" << endl;
            }

            // Iterate over the 2D vector
            for (const auto& row : v) {
                // Check if the current row is equal to the target vector
                if (row == target) {
                    cout << "Congratulation! You solved it in " + to_string(status) + " moves!" << endl;
                    return -1;
                }
            }
            status +=1;
        }
    }

    return status;
}


void play_game(){
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
        // When user solved the game
        if (status == -1)
        {
            break; 
        }
        
        status = AskInput(towers, status, rods);
    }
}


void replay()
{
    cout << "Do you want to play again? (Y/N):";
    char replay;
    cin >> replay;
    
    
    if (replay == 'Y' || replay == 'y')
    {
        play_game();    
    }
}


int main()
{
    // 1. Start playing game
    play_game();
    
    // 2. ask for replay
    replay();

 }


    //IsMoveAllowed()
    //    
    //MoveDisk()
 
