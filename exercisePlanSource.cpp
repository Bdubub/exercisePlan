#include <string>
#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;

struct Session
{
    string desc; // description of exercises in the session
    bool lowBack; //  true if session will fatigue lower back (spinal erectors)
    bool lowBody; // true if session will fatigue lower body muscles
    bool upBody; // true if session will fatigue upper body muscles
};

// tests if two adjacent sessions are compatible
// if both fatigue the same muscles then not compatible
bool compatible(Session aDay, Session otherDay)
{
    if (aDay.lowBack && otherDay.lowBack) { return false; }
    else if (aDay.lowBody && otherDay.lowBody) { return false; }
    else if (aDay.upBody && otherDay.upBody) { return false; }
    else { return true; }
}

// displays a week day paired with description of the session for that day
void displayDay(int weekDay, Session lift)
{
    cout << "\t";

    switch (weekDay)
    {
    case 0:
        cout << "Sunday";
        break;
    case 1:
        cout << "Monday";
        break;
    case 2:
        cout << "Tuesday";
        break;
    case 3:
        cout << "Wednesday";
        break;
    case 4:
        cout << "Thursday";
        break;
    case 5:
        cout << "Friday";
        break;
    case 6:
        cout << "Saturday";
        break;
    }
    cout << ": " << lift.desc << endl;
}

// main function finds all permutations of exercise sessions in a week
// and displays the ones where every pair of adjacent days is compatible
int main()
{
    // declare and define an array of Session structs for the seven week days (no particular order)
    Session liftPlan[7];

    liftPlan[0] = { "rest", false, false, false };
    liftPlan[1] = { "deadlift + leg press", true, true, false };
    liftPlan[2] = { "squat + RDL", true, true, false };
    liftPlan[3] = { "lunge", false, true, false };
    liftPlan[4] = { "OHP + pull up", false, false, true };
    liftPlan[5] = { "row + bench", true, false, true };
    liftPlan[6] = { "arms", false, false, true };

    // initialize vector with indexes of sessions to be changed each permutation
    // vector has all indexes except 0 (rest), so rest day will always be first across all options displayed
    vector<int> v = { 1, 2, 3, 4, 5, 6 };
    // planCount keeps track of valid permutations found so they can have different labels (Plan A, Plan B, etc)
    int planCount = 0;

    // loop through all the permutations
    // if they are valid then output
    do {
        // check if first day is compatible with last day and first day is compatible with second day (first value in vector)
        // (rest day is compatible with everything, so this if statement is just for safety if program is changed later)
        if (compatible(liftPlan[0], liftPlan[v.back()]) && compatible(liftPlan[0], liftPlan[v[0]]))
        {
            // initialize valid as true, only change to false if something incompatible is found
            bool valid = true;
            // loop through vector, check if liftPlan at current index is compatible with next index
            for (int i = 0; i < v.size() - 1; i++)
            {
                if (!compatible(liftPlan[v[i]], liftPlan[v[i + 1]]))
                {
                    valid = false;
                    // if one incompatibility is found, break loop to avoid wasting time on checking other days
                    break;
                }
            }

            // if valid permutation is found, display all days/sessions in order and add one to planCount
            if (valid)
            {
                // static cast int to char, adding 65 so that 0 is 'A', 1 is 'B', etc
                // check out this chart: https://en.cppreference.com/w/cpp/language/ascii.html
                cout << "Plan " << static_cast<char>(planCount + 65) << endl;
                displayDay(0, liftPlan[0]);
                for (int i = 0; i < v.size(); i++)
                {
                    displayDay(i + 1, liftPlan[v[i]]);
                }
                cout << endl;

                planCount++;
            }
        }
        // loops while there is another permutation that hasn't been tried yet
        // check out this example: https://www.geeksforgeeks.org/stdnext_permutation-prev_permutation-c/
    } while (next_permutation(v.begin(), v.end()));

    return 0;
}