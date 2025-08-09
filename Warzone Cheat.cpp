#include <iostream>
#include <vector>
#include <string>
#include <conio.h> // For _getch(), _kbhit()
#include <windows.h> // For SetConsoleTextAttribute and ShellExecute
#include <thread>
#include <chrono>

using namespace std;

// Feature flags
bool aimbot = false;
bool esp = false;
bool wallhack = false;
bool triggerbot = false;
bool norecoil = false;
bool radar = false;

// Function to set console color
void setColor(int color) {
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole, color);
}

// Function to set background and text color
void setTheme() {
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole, 0x0F); // White text on black background
    system("cls"); // Clear screen
}

void showMenu(int selectedOption = 1) {
    setTheme();

    // Dark theme colors
    setColor(12); // Red
    cout << "=============================\n";
    cout << "  Elusion Trainer - Trial Version\n";
    cout << "=============================\n";
    setColor(7); // White
    cout << "Status: Not Running\n";
    cout << "\nFeatures:\n";

    cout << "[1] Aimbot:   " << (aimbot ? "\033[32mON\033[0m" : "\033[31mOFF\033[0m") << endl;
    cout << "[2] ESP:      " << (esp ? "\033[32mON\033[0m" : "\033[31mOFF\033[0m") << endl;
    cout << "[3] Wallhack: " << (wallhack ? "\033[32mON\033[0m" : "\033[31mOFF\033[0m") << endl;
    cout << "[4] TriggerBot: " << (triggerbot ? "\033[32mON\033[0m" : "\033[31mOFF\033[0m") << endl;
    cout << "[5] NoRecoil: " << (norecoil ? "\033[32mON\033[0m" : "\033[31mOFF\033[0m") << endl;
    cout << "[6] Radar:    " << (radar ? "\033[32mON\033[0m" : "\033[31mOFF\033[0m") << endl;

    // Add the Discord link
    cout << "\n[7] Join Discord Server: \033[34mhttps://discord.gg/SfkrK75HNj\033[0m (Click to open)\n";
    cout << "\n[8] Start Trainer\n";
    cout << "[9] Exit\n";
    cout << "\nEnter your choice: ";

    // Highlight selected option
    for (int i = 1; i <= 9; ++i) {
        if (i == selectedOption) {
            setColor(10); // Green
            cout << ">";
        } else {
            cout << " ";
        }
        cout << " " << i << " ";
    }

    cout << "\n";
}

void updateStatus() {
    vector<string> activeFeatures;
    if (aimbot) activeFeatures.push_back("Aimbot");
    if (esp) activeFeatures.push_back("ESP");
    if (wallhack) activeFeatures.push_back("Wallhack");
    if (triggerbot) activeFeatures.push_back("TriggerBot");
    if (norecoil) activeFeatures.push_back("NoRecoil");
    if (radar) activeFeatures.push_back("Radar");

    if (!activeFeatures.empty()) {
        cout << "Status: Running - ";
        for (size_t i = 0; i < activeFeatures.size(); ++i) {
            cout << (i > 0 ? ", " : "") << activeFeatures[i];
        }
        cout << endl;
    } else {
        cout << "Status: Not Running" << endl;
    }
}

int main() {
    int selectedOption = 1;
    char input;

    while (true) {
        showMenu(selectedOption);

        if (_kbhit()) {
            input = _getch();

            if (input == 224) { // Arrow key
                input = _getch();
                switch (input) {
                    case 72: // Up arrow
                        selectedOption = (selectedOption > 1) ? selectedOption - 1 : 1;
                        break;
                    case 80: // Down arrow
                        selectedOption = (selectedOption < 9) ? selectedOption + 1 : 9;
                        break;
                }
            } else if (input == '\r') { // Enter key
                break;
            }
        }

        this_thread::sleep_for(chrono::milliseconds(50));
    }

    int choice = selectedOption;

    switch (choice) {
        case 1:
            aimbot = !aimbot;
            break;
        case 2:
            esp = !esp;
            break;
        case 3:
            wallhack = !wallhack;
            break;
        case 4:
            triggerbot = !triggerbot;
            break;
        case 5:
            norecoil = !norecoil;
            break;
        case 6:
            radar = !radar;
            break;
        case 7:
            ShellExecute(NULL, "open", "https://discord.gg/SfkrK75HNj", NULL, NULL, SW_SHOWNORMAL);
            cout << "Opening Discord server... (Click the link in your browser if it didn't open automatically)\n";
            _getch();
            break;
        case 8:
            if (aimbot || esp || wallhack || triggerbot || norecoil || radar) {
                updateStatus();
                cout << "Status: Trainer Started (Fake!)" << endl;
            } else {
                cout << "\nError: Please enable at least one feature before starting the trainer.\n";
            }
            _getch();
            break;
        case 9:
            cout << "Exiting..." << endl;
            break;
        default:
            cout << "Invalid choice. Try again." << endl;
            _getch();
    }

    return 0;
}