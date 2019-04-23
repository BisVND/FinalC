#include<iostream>
#include<cmath>

using namespace std;
double Interest(double IntRate, double outstanding, double principle, double frequency, double month, int year, int i){

    int IntPmt;

        IntPmt = IntRate*outstanding/frequency/100;
        cout << "Payment " << i + 1 << " occures in " << month << "/" << year << " has interest of " << IntPmt
         << " and total installment is " << IntPmt + principle<< endl;

    return IntPmt;
}
double boxMuller(double mean, double std) {

    double x, y, s, z, p;

    do {
        x = ((double) rand() * 2 / RAND_MAX) - 1;
        y = ((double) rand() * 2 / RAND_MAX) - 1;
        s = x * x + y * y;
    } while (s > 1);

    z = x * sqrt(-2 * log(s) / s);
    p = std * z + mean;
        return p;
}

main () {
    int i, year, type;
    double IntRate, outstanding, period, freq, prin, IntPmt, fltmean, fltstd, margin, month;

    cout << "Please provide: " << endl;

    do {
        cout << "Loan amount[should be positive!]:" << endl;
        cin >> outstanding;
    } while (outstanding <= 0);

    do {
        cout << "Number of payments [should be positive!]:" << endl;
        cin >> period;
    } while (period <= 0);

    do {
        cout << "Payment freq [1 (annually), 2 (semiannually), 4 (quarterly), 12 (monthhly)!]:" << endl;
        cin >> freq;
    } while (freq != 0 && freq != 2 && freq != 4 && freq != 12);

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
    } while (type != 0 && type != 1);

    if (type == 1) {
        do {
            cout << "Yearly interest rate [should be positive and in percentage!]:" << endl;
            cin >> IntRate;
        } while (IntRate <= 0);
    } else {
        do {
            cout << "Floating rate mean [should be positive and in percentage!]:" << endl;
            cin >> fltmean;
        } while (IntRate <= 0);

        do {
            cout << "Floating rate standard deviation [should be positive and in percentage!]:" << endl;
            cin >> fltstd;
        } while (IntRate <= 0);

        do {
            cout << "Margin [should be positive and in percentage!]:" << endl;
            cin >> margin;
        } while (margin <= 0);
    }

    prin = outstanding/period;
    cout << "Principle payment each period is " << prin << endl;

        for (i = 0; i < period; ++i) {
            if (type == 0){
                IntRate = boxMuller(fltmean, fltstd)+ margin;
                cout << "Payment " << i + 1 << " has interest rate of " << IntRate << endl;
            }
            IntPmt = Interest(IntRate, outstanding, prin, freq, month, year, i);

            outstanding = outstanding - prin;

            if (month + (12 / freq) > 12) {
                month = month + (12 / freq) - 12;
                year = year + 1;
            } else {
                month = month + (12 / freq);
            }
        }

    return 0;
}
