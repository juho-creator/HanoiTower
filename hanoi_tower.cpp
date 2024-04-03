#include <iostream>
#include <vector>
#include <cstdlib>
#include <string>

using namespace std;

// CODE WORK FLOW
// 1. Play the game
void play_game();

// 2. Set up the game with user input for rods and disks
void setup_game(int& rods, int& disks);

// 3. Initialize game settings with the specified number of rods and disks
vector<vector<int>> initialize_disks(int rods, int disks); 

// 4. Print towers with corresponding disks
void print_towers(vector<vector<int>> towers);

// 5. Create target vector for checking if the game is solved
vector<int>create_target_vector(int n);

// 6. Ask user to input disks to move from and to
int ask_input(vector<vector<int>>& towers, int& status, int rods, int disks);

// 7. Get highest disk on rod (for checking if disk can be moved)
int get_peak_disk(const vector<int>& rod);

// 8. Move disk from one rod to another
void move_disk(vector<vector<int>>& towers, int from, int to);

// 9. Display prompt for tower input
void display_tower_prompt(int& status, int rods);

// 10. Ask user if they want to replay or exit
void ask_replay();



int main()
{
    play_game();
 }
 
 
// DEFINITION OF FUNCTIONS
void play_game(){
    int rods;
    int disks;
    
    setup_game(rods, disks);
    

    // 1. Initialize disks  
    vector<vector<int>> towers = initialize_disks(rods, disks);


    // 2. Print towers
    print_towers(towers);

    // 3. Ask for input move
    int status = 1;
    while (1)
    {
        // When user solved the game
        if (status == -1)
        {
            break; 
        }
        
        status = ask_input(towers, status, rods, disks);
    }
    ask_replay();
}
 
void setup_game(int& rods, int& disks){
    cout << endl;
    cout << "Welcome to Tower of Hanoi!" << endl;
    cout << "Let's set up the game." << endl<< endl;

    cout << "Total number of rods: ";
    cin >> rods;

    cout << "Total number of disks: ";
    cin >> disks;
    cout << endl;
}

vector<vector<int>> initialize_disks(int t, int d){
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

void print_towers(vector<vector<int>> v){
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

int ask_input(vector<vector<int>>& v, int& status, int rods, int disks) {
    vector<int> target = create_target_vector(disks);

    while (1) {
        // Display tower prompt
        display_tower_prompt(status, rods);

        // Get from and to index
        int from, to;
        cin >> from >> to;

        // If index out of range or when trying to move disk at the same rod
        if (from == to || from <= 0 || from > rods || to <= 0 || to > rods) {
            cout << "=> Move failed!" << endl;
        }
        else {
            // Get peak disk of the rod moving from and moving to
            int fromPeakElement = get_peak_disk(v[from - 1]);
            int toPeakElement = get_peak_disk(v[to - 1]);

            // If there's nothing on the rod moving to
            if (fromPeakElement != 0 && toPeakElement == 0) {
                move_disk(v, from, to);
                cout << "=> Move succeeded!" << endl << endl;
                print_towers(v);
            }
            // When there's something on the rod moving to
            else if (fromPeakElement != 0 && fromPeakElement < toPeakElement) {
                move_disk(v, from, to);
                cout << "=> Move succeeded!" << endl << endl;
                print_towers(v);
            }
            else {
                cout << "Move failed!" << endl;
            }

            // Iterate over the 2D vector starting from the second row
            for (auto it = v.begin() + 1; it != v.end(); ++it) {
                // Check if the current row is equal to the target vector
                if (*it == target) {
                    cout << "Congratulations! You solved it in " << status << " moves!" << endl;
                    return -1;
                }
            }
            status +=1;
        }
    }
    return status;
}

vector<int> create_target_vector(int n) {
    std::vector<int> target;
    for (int i = n; i >= 1; --i) {
        target.push_back(i);
    }
    return target;
}

void move_disk(vector<vector<int>>& v, int from, int to) {
    v[to-1].push_back(v[from-1].back());
    v[from-1].pop_back();
}

int get_peak_disk(const vector<int>& v) {
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

void display_tower_prompt(int&status, int rods) {
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

void ask_replay(){
    cout << "Do you want to play again? (Y/N):";
    char replay;
    cin >> replay;
    
    
    if (replay == 'Y' || replay == 'y')
    {
        play_game();    
    }
}

