// For more information regarding on the code,
// Please refer to my github page
// https://github.com/juho-creator/HanoiTower

#include "std_lib_facilities.h"

using namespace std;

void greet_user();
void clearInputBuffer();
int get_rods();
int get_disks();
void setup_game(int& rods, int& disks);
vector<vector<int>> initialize_disks(int r, int d);
vector<int> create_target_vector(int n);
void print_towers(vector<vector<int>> v);
int get_peak_disk(const vector<int>& v);
bool IsMoveAllowed(int to, int from, int rods, const vector<vector<int>>& v);
void display_prompt(int& num_moves, int rods);
int get_moveFrom();
int get_moveTo();
pair<int, int> get_move(int rods, int& num_moves);
pair<int, int> ask_move(int rods, int& num_moves);
void move_disk(vector<vector<int>>& v, int from, int to);
bool checkGameSolved(vector<vector<int>>& v, vector<int>& target, int& num_moves);
void play_game_loop(vector<vector<int>>& towers, int& num_moves, const int& rods, vector<int>& target);
void play_game();
bool ask_replay();


int main()
{
    bool playing = true;

    while (playing)
    {
        play_game();

        playing = ask_replay();
    }
}



/* MAIN LOGIC OF THE GAME */
void play_game() {
    int rods, disks;
    int num_moves = 0;

    // 1. Greet user with a welcome message
    greet_user();

    // 2. Get number of rods and disks from user input
    setup_game(rods, disks);

    // 3. Initialize disks and rods based on user input 
    vector<vector<int>> towers = initialize_disks(rods, disks);

    // 4. Create target vector
    vector<int> target = create_target_vector(disks);

    // 5. Print towers
    print_towers(towers);

    // 6. Keep asking user input for next move
    play_game_loop(towers, num_moves, rods, target);
}

void play_game_loop(vector<vector<int>>& towers, int& num_moves, const int& rods, vector<int>& target) {
    int to, from;
    bool gameSolved = false;

    // 6. If game is not solved, keep asking user for next move 
    while (!gameSolved)
    {
        pair<int, int> move = ask_move(rods, num_moves);
        to = move.first;
        from = move.second;

        // 7. Check if move is valid
        bool moveable = IsMoveAllowed(to, from, rods, towers);

        // 8. Change disk location if move is valid
        if (moveable) {
            move_disk(towers, from, to);
            cout << "=> Move succeeded!" << endl << endl;
            print_towers(towers);
        }

        // 9. Check if user solved the game
        gameSolved = checkGameSolved(towers, target, num_moves);
    }
    // 10. If game is sovled, clear all rods and disks
    towers.clear();
}

bool ask_replay() {
    cout << "Do you want to play again? (Y/N): "; // Ask user for replay
    char replay;
    cin >> replay;

    replay = tolower(replay); // Convert input to lowercase for case insensitivity

    if (replay == 'y') {
        return true;
    }
    else if (replay == 'n') {
        return false;
    }
    else {
        cout << "Invalid input. Please enter 'Y' or 'N'" << endl << endl;
        return ask_replay(); // Recursively call the function until valid input is received
    }
}



/* other subfunctions */
void greet_user() {
    cout << endl;
    string asciiArt = R"(
 ____      ____  ________  _____       ______    ___   ____    ____  ________                                                          
|_  _|    |_  _||_   __  ||_   _|    .' ___  | .'   `.|_   \  /   _||_   __  |                                                         
  \ \  /\  / /    | |_ \_|  | |     / .'   \_|/  .-.  \ |   \/   |    | |_ \_|                                                         
   \ \/  \/ /     |  _| _   | |   _ | |       | |   | | | |\  /| |    |  _| _                                                          
    \  /\  /     _| |__/ | _| |__/ |\ `.___.'\\  `-'  /_| |_\/_| |_  _| |__/ |                                                         
     \/  \/     |________||________| `.____ .' `.___.'|_____||_____||________|                                                         
                                _________    ___                                                                                       
                               |  _   _  | .'   `.                                                                                     
                               |_/ | | \_|/  .-.  \                                                                                    
                                   | |    | |   | |                                                                                    
                                  _| |_   \  `-'  /                                                                                    
                                 |_____|   `.___.'                                                                                     
 _________    ___   ____      ____  ________  _______           ___   ________     ____  ____       _       ____  _____   ___   _____  
|  _   _  | .'   `.|_  _|    |_  _||_   __  ||_   __ \        .'   `.|_   __  |   |_   ||   _|     / \     |_   \|_   _|.'   `.|_   _| 
|_/ | | \_|/  .-.  \ \ \  /\  / /    | |_ \_|  | |__) |      /  .-.  \ | |_ \_|     | |__| |      / _ \      |   \ | | /  .-.  \ | |   
    | |    | |   | |  \ \/  \/ /     |  _| _   |  __ /       | |   | | |  _|        |  __  |     / ___ \     | |\ \| | | |   | | | |   
   _| |_   \  `-'  /   \  /\  /     _| |__/ | _| |  \ \_     \  `-'  /_| |_        _| |  | |_  _/ /   \ \_  _| |_\   |_\  `-'  /_| |_  
  |_____|   `.___.'     \/  \/     |________||____| |___|     `.___.'|_____|      |____||____||____| |____||_____|\____|`.___.'|_____|                                                                                                                                   
                                                                                                                                           )";

    cout << asciiArt << endl;
    cout << "Let's start by setting up the game!" << endl << endl;
}

void clearInputBuffer() {
    std::cin.clear(); // Clear the input buffer
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Ignore invalid input
}

int get_rods() {
    int rods;
    try {
        cout << "Total number of rods: ";
        cin >> rods;

        // Check that input is integer
        if (!cin)
            error("( Please enter an integer :D )");

        // Check if rods is less than the minimum number of rods, which is 3
        else if (rods < 3)
            throw out_of_range("( Number of rods must be 3 or more )");
    }
    catch (runtime_error& e) {
        cout << "INVALID INPUT " << e.what() << endl << endl;
        clearInputBuffer();// Clear the input buffer
        return get_rods(); // Retry input
    }
    catch (out_of_range& e) {
        cout << "OUT_OF_RANGE : " << e.what() << endl << endl;
        clearInputBuffer();
        return get_rods();
    }
    catch (...) {
        cout << "INVALID INPUT!!" << endl << endl;
        clearInputBuffer();
        return get_rods();
    }
    return rods;
}

int get_disks() {
    int disks;
    try {
        cout << "Total number of disks: ";
        cin >> disks;

        // Check that input is an integer
        if (!cin)
            error("Please enter an integer :)");

        // Check if disks is less than zero
        else if (disks <= 0)
            throw out_of_range("Please enter a positive integer");
    }
    catch (runtime_error& e) {
        cout << "INVALID INPUT : " << e.what() << endl << endl;
        clearInputBuffer();  // Clear the input buffer
        return get_disks(); // Retry input
    }
    catch (out_of_range& e) {
        cout << "OUT_OF_RANGE : " << e.what() << endl << endl;
        clearInputBuffer();
        return get_disks();
    }
    catch (...) {
        cout << "INVALID INPUT!!" << endl << endl;
        clearInputBuffer();
        return get_disks();
    }
    return disks;
}

void setup_game(int& rods, int& disks) {
    // Get number of rods and disks from user
    rods = get_rods();
    disks = get_disks();

    try {
        // Check if number of rods is less than the number of disks
        if (rods < disks) {
            error("( Number of rods must be greater than or equal to the number of disks!! )");
            cout << endl;
        }
    }
    catch (runtime_error& e) {
        cout << "INVALID INPUT " << e.what() << endl << endl;
        setup_game(rods, disks);
    }
    catch (...) {
        cout << "INVALID INPUT!!" << endl << endl;
        setup_game(rods, disks);
    }
    cout << endl << endl;
}

vector<vector<int>> initialize_disks(int r, int d) {
    // Initialize rods without disks
    vector<vector<int>> towers(r);

    // Create initial tower with disks stacked in descending order
    vector<int> initial_tower(d);
    for (int i = 0; i < d; i++)
    {
        initial_tower[i] = d - i;
    }

    // Initialize first rod with disks
    towers[0] = initial_tower;

    // Leave the rest of the rods with no disks
    return towers;
}

vector<int> create_target_vector(int n) {
    vector<int> target;
    for (int i = n; i >= 1; --i) {
        target.push_back(i);
    }
    return target;
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

bool IsMoveAllowed(int to, int from, int rods, const vector<vector<int>>& v) {
    try {

        // Check if index is out of range
        if (from <= 0 || from > rods || to <= 0 || to > rods)
            throw out_of_range("( Rod is out of range )");

        // Get peak disk of the rod moving from and moving to
        int fromPeakElement = get_peak_disk(v[from - 1]);
        int toPeakElement = get_peak_disk(v[to - 1]);


        // Check if disk is being moved to the same rod 
        if (from == to)
            error("( Attempted to place disk on the same rod )");

        // Check if disk does not exist
        else if (fromPeakElement == 0)
            error("( Cannot move from rod with no disks )");

        // Check if disk being moved is larger than the disk at the destination rod
        else if (toPeakElement != 0 && toPeakElement < fromPeakElement)
            error("( Destination rod has a smaller disk than the one being moved )");
        return true;
    }
    catch (out_of_range& e) { // Out of range
        cout << "=> Move failed! " << e.what() << endl;
        return false;

    }
    catch (runtime_error& e) { // Cannot place disk on the same rod
        cout << "=> Move failed! " << e.what() << endl;
        return false;

    }
    catch (...) {
        cout << "= > Move failed!!!" << endl;
        return false;
    }
}

void display_prompt(int& num_moves, int rods) {
    cout << endl;

    // Create a string of index lists
    string indices = "[1";
    for (int i = 1; i < rods; i++) {
        indices += "|" + to_string(i + 1);
    }
    indices += "]";

    // Display prompt with index list

    cout << "[" << num_moves << "] From which tower will you move a disk to which tower? (from="
        << indices << ", to=" << indices << "): ";
}

int get_moveFrom() {
    int from;
    cin >> from;

    // Check if input is integer
    if (!cin)
        error("( Please enter an integer :D )");
    // Check if move is greater than zero
    else if (from <= 0)
        throw out_of_range("( Please enter move within the range )");

    return from;
}

int get_moveTo() {
    int to;
    cin >> to;

    // Check if input is integer
    if (!cin)
        error("( Please enter an integer :D )");
    // Check if move is greater than zero
    else if (to <= 0)
        throw out_of_range("( Please enter move within the range )");
    return to;
}

pair<int, int> get_move(int rods, int& num_moves) {
    try {

        int from = get_moveFrom();
        int to = get_moveTo();
        return { to, from };
    }
    catch (out_of_range& e) {
        cout << "=> Move failed! " << e.what() << endl;
        clearInputBuffer();
        return ask_move(rods, num_moves);
    }
    catch (runtime_error& e) {
        cout << "=> Move failed! " << e.what() << endl;
        clearInputBuffer();
        return ask_move(rods, num_moves);
    }
    catch (...) {
        cout << "=> Move failed! " << endl;
        clearInputBuffer();
        return ask_move(rods, num_moves);
    }
}

pair<int, int> ask_move(int rods, int& num_moves) {
    num_moves += 1;
    display_prompt(num_moves, rods);
    return get_move(rods, num_moves);
}

void move_disk(vector<vector<int>>& v, int from, int to) {
    v[to - 1].push_back(v[from - 1].back());
    v[from - 1].pop_back();
}

bool checkGameSolved(vector<vector<int>>& v, vector<int>& target, int& num_moves) {
    // Iterate over the rods starting from the second rod
    for (auto it = v.begin() + 1; it != v.end(); ++it) {
        // Check if the each rod is equal to the target vector
        if (*it == target) {
            cout << "Congratulations! You solved it in " << num_moves << " moves!" << endl;
            return true;
        }
    }
    return false;
}
