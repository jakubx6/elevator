#include <iostream>
#include "elevator.h"
using namespace std;

int main()
{
    int n, o, p;
    char id;
    cout << "==========\n";
    cout << " Elevator\n Set amount of elevator cabs (1-16): ";
    cin >> n;
    cout << "\n==========\n";

    while (n < 1 || n > 16) {
        cout << " Set correct amount of elevator cabs (1-16): ";
        cin >> n;
        cout << "\n==========\n";
    }

    Elevator* e = (Elevator*)malloc(sizeof(Elevator) * n);
    for (int i = 0; i < n; i++) {
        e[i] = Elevator(i + 65);
    }
    e->status(e, n);

    while (1) {
        cout << "==========\n";
        cout << " 1 - Step\n 2 - Pickup\n 3 - Request\n 4 - Update\n 5 - Status\n 6 - Close\n";
        cout << "==========\n";
        cin >> p;
        cout << "==========\n";

        switch (p) {
        case 1:
            e->step(e, n);
            e->status(e, n);
            break;
        case 2:
            cout << " Set current floor: ";
            cin >> o;
            cout << " Set target floor: ";
            cin >> p;
            e->pickup(e, n, o, p);
            break;
        case 3:
            cout << " Set elevator ID: ";
            cin >> id;
            cout << " Set target floor: ";
            cin >> o;
            e->request(e, n, id, o);
            break;
        case 4:
            cout << " Set elevator ID: ";
            cin >> id;
            cout << " Set target floor: ";
            cin >> o;
            cout << " Set direction: ";
            cin >> p;
            e->update(e, n, id, o, p);
            break;
        case 5:
            e->status(e, n);
            break;
        case 6:
            delete e;
            return 0;
        }
    }
}