#include <iostream>
#include "aisspace.h"
#include <time.h>

using namespace std;

using namespace AISSpace;

// In the main function
int main(int argc, char* argv[]) {
    srand(time(nullptr));

    int num_Row, num_Col, num_Det;
    int Prow = -1, Pcol = -1; // Initialize pathogen position
    int has_path=0;

    if (argc != 4) {
        cout << "Invalid number of arguments." << endl;
        exit(ERR_ARG);
    } else {
        num_Row = string_to_integer(argv[1]);
        num_Col = string_to_integer(argv[2]);
        num_Det = string_to_integer(argv[3]);
    }

    cout << "Number of Rows: " << num_Row << endl;
    cout << "Number of Columns: " << num_Col << endl;
    cout << "Number of initial detectors: " << num_Det << endl;

    TwoD_Array Imm_sys = alloc2D(num_Row, num_Col);
    init_Array(Imm_sys, num_Row, num_Col, num_Det);

    bool sim_continue = true;

        char select;

        cout << "There is no pathogen in the system" << endl
             << "Select one of the options to continue" << endl << endl
             << "Option 1: Introduce a pathogen" << endl
             << "Option 2: Quit" << endl << endl;
        Display(Imm_sys, num_Row, num_Col);
        cin >> select;

        switch (select) {
            case '1':
                    Place_pathogen(Imm_sys, num_Row, num_Col, Prow, Pcol);
                    has_path =1;
                    Run_sim(Imm_sys, num_Row, num_Col, Prow, Pcol);
                    dealloc(Imm_sys, num_Row);
                break;
            case '2':
                cout << "You have successfully quit the simulation" << endl;
                dealloc(Imm_sys, num_Row);
                sim_continue = false;
                break;
            default:
                cout << "Invalid selection, enter a valid selection" << endl;
                Pause();
                break;
        }
    return 0;
}
