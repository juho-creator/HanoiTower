#include "std_lib_facilities.h"
using namespace std;

/* CODE WORK FLOW */ 
// Play the game
void play_game();

// Greet user with welcome message
void greet_user();

// Set up the game with user input for rods and disks
void setup_game(int& rods, int& disks);

// Initialize game settings with the specified number of rods and disks
vector<vector<int>> initialize_disks(int rods, int disks);

// Print towers with corresponding disks
void print_towers(vector<vector<int>> towers);

// Create target vector for checking if the game is solved
vector<int>create_target_vector(int n);

// Ask user to input disks to move from and to
int ask_input(vector<vector<int>>& towers, int& status, int rods, int disks);

// Get highest disk on rod (for checking if disk can be moved)
int get_peak_disk(const vector<int>& rod);

// Move disk from one rod to another
void move_disk(vector<vector<int>>& towers, int from, int to);

// Display prompt for tower input
void display_tower_prompt(int& status, int rods);

// Check if game has been solved
void checkGameSolved(vector<vector<int>>& v, vector<int>& target, int& status);

// Ask user if they want to replay or exit
void ask_replay();



int main()
{
    play_game();
}




// DEFINITION OF FUNCTIONS
void play_game() {
    int rods;
    int disks;

    // 1. Greet user with a welcome message
    greet_user();

    // 2. Get number of rods and disks from user input
    setup_game(rods, disks);

    // 3. Initialize disks and rods based on user input 
    vector<vector<int>> towers = initialize_disks(rods, disks);

    // 4. Print towers
    print_towers(towers);

    // 5. Keep asking user input for next movement
    int status = 1;
    while (1)
    {
        // 6. When user solved the game, stop asking for next move
        if (status == -1)
        {
            // 7. Clear all rods and disks
            towers.clear();
    
            // 8. Ask user for replay
            ask_replay();
            break;
        }
        // 6. If game is not solved, keep asking user for next move 
        status = ask_input(towers, status, rods, disks);
    }
}

void greet_user(){
    cout << endl;
    cout << "Welcome to Tower of Hanoi!" << endl;
    cout << "Let's set up the game." << endl << endl;
}

void setup_game(int& rods, int& disks) {
    cout << "Total number of rods: ";
    cin >> rods;

    cout << "Total number of disks: ";
    cin >> disks;
    cout << endl;
    
    if (rods < disks)
    {
        // @ DISPLAY ERROR
        cout << "ERROR : Number of rods must be greater or equal to the number of disks!!" << endl;
        setup_game(rods,disks);
    }
}

vector<vector<int>> initialize_disks(int t, int d) {
    // Initialize rods without disks
    vector<vector<int>> towers(t); 

    // Create initial tower
    vector<int> initial_tower(d); 
    for (int i = 0; i < d; i++)
    {
        initial_tower[i] = d - i;
    }
    towers[0] = initial_tower;

    // Leave the rest of the element vectors as empty vectors
    return towers;
}

void print_towers(vector<vector<int>> v) {
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

bool IsMoveAllowed(int to, int from, int rods, const vector<vector<int>>& v) {
    // If index is out of range or when trying to move disk at the same rod
    if (from == to || from <= 0 || from > rods || to <= 0 || to > rods) return false;
    
    // Get peak disk of the rod moving from and moving to
    int fromPeakElement = get_peak_disk(v[from - 1]);
    int toPeakElement = get_peak_disk(v[to - 1]);

    // If there's nothing on the rod moving to or the disk being moved is smaller than the top disk on the rod moving to, return true
    return fromPeakElement != 0 && (toPeakElement == 0 || (fromPeakElement < toPeakElement));
}

int ask_input(vector<vector<int>>& v, int& status, int rods, int disks) {
    // Create target vector
    vector<int> target = create_target_vector(disks);

    // Display tower prompt
    display_tower_prompt(status, rods);

    // Get from and to index
    int from, to;
    cin >> from >> to;

    // Check if move is valid
    bool moveable = IsMoveAllowed(to, from, rods, v);
    
    // Chnage disk location if move is valid
    if (moveable) {
        move_disk(v, from, to);
        cout << "=> Move succeeded!" << endl << endl;
        print_towers(v);
    }
    else {
        cout << "=> Move failed!" << endl;
    }

    // Check if user solved the game
    checkGameSolved(v, target, status);
    return status;
}


void checkGameSolved(vector<vector<int>>& v, vector<int>& target, int& status){
    // Iterate over the 2D vector starting from the second row
    for (auto it = v.begin() + 1; it != v.end(); ++it) {
        // Check if the current row is equal to the target vector
        if (*it == target) {
            cout << "Congratulations! You solved it in " << status << " moves!" << endl;
            status = -1;
            return ;
        }
    }
    
    status += 1;
}

vector<int> create_target_vector(int n) {
    vector<int> target;
    for (int i = n; i >= 1; --i) {
        target.push_back(i);
    }
    return target;
}

void move_disk(vector<vector<int>>& v, int from, int to) {
    v[to - 1].push_back(v[from - 1].back());
    v[from - 1].pop_back();
}

int get_peak_disk(const vector<int>& v) {
    if (v.empty()) {
        // If the vector is empty, return 0 indicating no disk
        return 0;
    }
    // Iterate through the rod vector from the end
    for (int i = v.size() - 1; i >= 0; --i) {
        if (v[i] != 0) {
            // Return the first non-zero element encountered
            return v[i];
        }
    }
    // If all elements are zero, return 0 indicating no disk
    return 0;
}

void display_tower_prompt(int& status, int rods) {
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

void ask_replay() {
    cout << "Do you want to play again? (Y/N):";
    char replay;
    cin >> replay;

    if (replay == 'Y' || replay == 'y')
    {
        play_game();
    }
}
