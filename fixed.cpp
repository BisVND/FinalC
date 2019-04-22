#include<iostream>
#include<cmath>

using namespace std;

main () {
    int t, i, month, year, type;
    double IntRate, x, os, td, irpd, prin, IntPmt, fltmean, fltstd, margin;

    cout << "Please provide: " << endl;

    do {
        cout << "Loan amount[should be positive!]:" << endl;
        cin >> os;
    } while (os <= 0);

    do {
        cout << "Number of payments [should be positive!]:" << endl;
        cin >> td;
    } while (td <= 0);

    do {
        cout << "Payment frequency [1 (annually), 2 (semiannually), 4 (quarterly), 12 (monthhly)!]:" << endl;
        cin >> irpd;
    } while (irpd <= 0 || irpd > 12);

    do {
        cout << "Starting month [should be positive!]:" << endl;
        cin >> month;
    } while (month <= 0);

    do {
        cout << "Starting year [should be positive!]:" << endl;
        cin >> year;
    } while (year <= 0);

    do {
        cout << "Fixed rate or Floating rate [ 1 if fixed, 0 if float ]:" << endl;
        cin >> type;
    } while (type < > 0 || type < > 1);

    if (type = 1)
    {
        do {
            cout << "Yearly interest rate [should be positive and in percentage (5%)!]:" << endl;
            cin >> IntRate;
        }
    while (IntRate <= 0);

    prin = os / td;
    cout << "Principle payment each period is: " << prin << endl;
    for (i = 0; i < td; i++) {
        IntPmt = IntRate * os / irpd / 100;
        cout << "Payment " << i + 1 << " occured in " << month << "/" << year << " has interest of " << IntPmt
             << " and total installment is " << IntPmt + prin << endl;
        os = os - prin;
        if (month + 3 > 12) {
            month = month + 3 - 12;
            year = year + 1;
        }
        else { month = month + 3; }

    }
}
    else {
            do {
                cout << "Floating rate mean [should be positive and in percentage (5%)!]:" << endl;
                cin >> fltmean;
            }
            while (IntRate <= 0);
        do {
            cout << "Floating rate standard deviation [should be positive and in percentage (5%)!]:" << endl;
            cin >> fltstd;
        }
        while (IntRate <= 0);
        do {
            cout << "Margin [should be positive and in percentage (5%)!]:" << endl;
            cin >> margin;
        }
        while (margin <= 0);

    }
}
