#include <iostream>
#include <filesystem>
#include <fstream>
using namespace std;
namespace fs = std::filesystem;

int main() {
    int choice;
    string a, b, perm;
    
    cout << "\n===== LINUX FILE EXPLORER =====\n";

    while (true) {
        cout << "\n1. List Files        (Day 1)";
        cout << "\n2. Change Directory  (Day 2)";
        cout << "\n3. Create File       (Day 3)";
        cout << "\n4. Copy File         (Day 3)";
        cout << "\n5. Move File         (Day 3)";
        cout << "\n6. Delete File       (Day 3)";
        cout << "\n7. Search File       (Day 4)";
        cout << "\n8. Change Permission (Day 5)";
        cout << "\n9. Exit";
        cout << "\nEnter choice: ";
        cin >> choice;

        // ---------- DAY 1 : List Files ----------
        if (choice == 1) {
            cout << "\nFiles in current directory:\n";
            for (auto &file : fs::directory_iterator(fs::current_path()))
                cout << file.path().filename() << endl;
        }

        // ---------- DAY 2 : Change Directory ----------
        else if (choice == 2) {
            cout << "Enter directory name: ";
            cin >> a;
            fs::path newPath = fs::current_path() / a;
            if (fs::exists(newPath) && fs::is_directory(newPath)) {
                fs::current_path(newPath);
                cout << "Entered directory: " << a << endl;
            } else {
                cout << "Directory not found!\n";
            }
        }

        // ---------- DAY 3 : Create File ----------
        else if (choice == 3) {
            cout << "Enter file name to create: ";
            cin >> a;
            ofstream file(a);
            file.close();
            cout << "File created!\n";
        }

        // ---------- DAY 3 : Copy File ----------
        else if (choice == 4) {
            cout << "Copy from: ";
            cin >> a;
            cout << "Copy to: ";
            cin >> b;
            try {
                fs::copy(a, b, fs::copy_options::overwrite_existing);
                cout << "File copied!\n";
            } catch (...) {
                cout << "Copy failed!\n";
            }
        }

        // ---------- DAY 3 : Move File ----------
        else if (choice == 5) {
            cout << "Move from: ";
            cin >> a;
            cout << "Move to: ";
            cin >> b;
            try {
                fs::rename(a, b);
                cout << "File moved!\n";
            } catch (...) {
                cout << "Move failed!\n";
            }
        }

        // ---------- DAY 3 : Delete File ----------
        else if (choice == 6) {
            cout << "Delete file: ";
            cin >> a;
            if (fs::remove(a))
                cout << "File deleted!\n";
            else
                cout << "Delete failed!\n";
        }

        // ---------- DAY 4 : Search File ----------
        else if (choice == 7) {
            cout << "Enter filename to search: ";
            cin >> a;
            bool found = false;
            for (auto &file : fs::recursive_directory_iterator(fs::current_path())) {
                if (file.path().filename() == a) {
                    cout << "Found at: " << file.path() << endl;
                    found = true;
                }
            }
            if (!found) cout << "File not found!\n";
        }

        // ---------- DAY 5 : Change File Permission ----------
        else if (choice == 8) {
            cout << "Enter file name: ";
            cin >> a;
            cout << "Enter permission (Example 755 or 777): ";
            cin >> perm;
            string command = "chmod " + perm + " " + a;
            system(command.c_str());
            cout << "Permission updated!\n";
        }

        // ---------- Exit ----------
        else if (choice == 9) {
            cout << "Exiting...\n";
            break;
        }

        else {
            cout << "Invalid choice!\n";
        }
    }

    return 0;
}
