#include "aisspace.h"


namespace AISSpace
{
    int string_to_integer(string str)
    {
        int res;
        stringstream ss(str);
        ss>>res;

        if(ss.fail())
        {
            cerr << "Error " << str << " cannot be converted to an integer" << endl;
            exit(ERR_CONV);
        }
        return res;
    }

    int gen_rand(int low,int high)
    {
        int rand_num;
        rand_num = (low+rand()%(high-low+1));
        return rand_num;
    }

    TwoD_Array alloc2D(int row, int col)
    {
        TwoD_Array newArray;
        newArray = new OneD_Array[row];
        for(int r=0;r<row;r++)
        {
            newArray[r] = new char [col];
        }
        return newArray;
    }

    void init_Array(TwoD_Array &arr, int row,int col,int num_det)
    {
        for(int r=0;r<row;r++)
        {
            for(int c=0;c<col;c++)
            {
                arr[r][c] = blank;
            }
        }
        Place_dectectors(arr,row,col,detectors,num_det);
    }

    void Display(TwoD_Array &arr, int row,int col)
    {
        for(int r=0;r<row;r++)
        {
            for(int c=0;c<col; c++)
            {
                cout << arr[r][c] << " ";
            }
            cout << endl;
        }
    }

    void Place_dectectors(TwoD_Array &arr, int row, int col, char piece, int num)
    {
        int r, c;
        for (int i = 0; i < num; ++i)
        {
            do
            {
                r = gen_rand(0, row - 1);
                c = gen_rand(0, col - 1);
            } while (arr[r][c] != blank); // Repeat until an empty cell is found

            arr[r][c] = piece;

        }
    }

    void clone_dectectors(TwoD_Array &arr, int row, int col, int detR, int detC)
    {
        // Counter to keep track of cloned detectors
        int clonedCount = 0;

        // Maximum number of attempts to clone detectors
        int maxAttempts = 1000;
        int attemptCount = 0;

        // Loop until two detectors are successfully cloned or maximum attempts reached
        while (clonedCount < 2 && attemptCount < maxAttempts)
        {
            int r = gen_rand(detR - 1, detR + 1);
            int c = gen_rand(detC - 1, detC + 1);

            // Ensure r and c are within the array bounds
            if (r >= 0 && r < row && c >= 0 && c < col)
            {
                // Check if the cell is blank (empty)
                if (arr[r][c] == blank)
                {
                    // Clone a detector at the empty cell
                    arr[r][c] = detectors;
                    clonedCount++; // Increment the cloned detectors count
                }
            }

            attemptCount++; // Increment the attempt count
        }

        // Output error message if cloning process failed after maximum attempts
        if (clonedCount < 2)
        {
            cerr << "Error: Failed to clone detectors after " << maxAttempts << " attempts." << endl;
        }
    }



    void Place_pathogen(TwoD_Array &arr, int row, int col,int &RowP,int &ColP)
    {
        int r, c;
        do
        {
            r = gen_rand(0, row - 1);
            c = gen_rand(0, col - 1);
        } while (arr[r][c] != blank && arr[r][c] != detectors); // Repeat until an empty cell is found

        arr[r][c] = pathogen;
        RowP = r;
        ColP = c;
    }

    void dealloc(TwoD_Array arr, int row)
    {
        for(int r=0; r<row; r++)
        {
            delete[] arr[r];
        }
        delete[] arr;
        arr=nullptr;
    }
    void Pause() //Pause function
     {
        cin.ignore(100, '\n');
        cout << "Press Enter to continue." << endl;
        cin.get();
     }

    void Run_sim(TwoD_Array arr, int row, int col, int &RowP, int &ColP)
    {
        int temp = 0;
        int minR=0,minC=0,maxR=0,maxC=0;

        bool sim_continue = true;
        char select;

        do
        {
            system("cls");

            Display(arr, row, col);
            cout << temp << endl;
            cout << "Select one of the options to continue" << endl << endl
                     << "Option 1: Continue the simulation" << endl
                     << "Option 2: Quit" << endl << endl;
            cin >> select;

            switch (select)
            {
                case '1':
                        // Step 1: Create copies of detectors
                        minR = RowP-stimulation_threshold;
                        if(minR<0){minR = 0;}
                        minC = ColP-stimulation_threshold;
                        if(minC<0){minC = 0;}
                        maxR = RowP+stimulation_threshold;
                        if(maxR>row){maxR = row;}
                        maxC = ColP+stimulation_threshold;
                        if(maxC<0){maxC = col;}

                        int r,c;
                        do{
                                r = gen_rand(minR,maxR-1);
                                c = gen_rand(minC,maxC-1);
                            }while(arr[r][c]==detectors);

                        clone_dectectors(arr,row,col,r,c);


                        //Step 2: Update the detector population
                        for (int i = 0; i < N; ++i)
                        {
                            //int farthest_distance = -1;
                            int farthest_r, farthest_c;

                            // Find the farthest detector from the pathogen
                            for (int r = 0; r < row; ++r)
                            {
                                for (int c = 0; c < col; ++c)
                                {
                                    //if
                                    if (arr[r][c] == detectors)
                                    {
                                        double distance = sqrt(pow(RowP - r, 2) + pow(ColP - c, 2));
                                        temp=distance;
                                        if (distance > stimulation_threshold)
                                        {
                                            //farthest_distance = distance;
                                            farthest_r = r;
                                            farthest_c = c;
                                        }
                                    }
                                }
                            }

                            // Remove the farthest detector
                            if((farthest_r>=0 && farthest_c<row)&&
                               (farthest_c>=0 && farthest_c<col)){
                            arr[farthest_r][farthest_c] = blank;}
                        }
                    break;
                case '2':
                    cout << "You have successfully quit the simulation" << endl;
                    Pause();
                    sim_continue = false;
                    break;
                default:
                    cout << "Invalid selection, enter a valid selection" << endl;
                    Pause();
                    break;
            }
        } while (sim_continue);
    }
}



