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
    int opt, i, year, type, sub;
    double IntRate, PV, period, freq, prin, IntPmt, fltmean, fltstd, margin, month, PMT, temp;

    do {
        cout << "1: Fixed rate" << endl
             << "2: Floating rate" << endl
             << "3: Fixed rate, fixed instalments" << endl
             << "What payment method do you want to apply? ";
        cin >> opt;
    } while (opt != 1 && opt != 2 && opt != 3);

    if (opt == 3) {
        cout << "Please choose the case: "<< endl
             << "1: Want to compute payment" << endl
             << "2: Want to compute Loan amount" << endl
             << "3: Want to compute number of years" << endl
             << "4: Want to compute interest rate " << endl;
        cin >> sub;

        cout << "Please provide: " << endl;
        if (sub == 1){
            do {
                cout << "Loan amount[should be positive!]:" << endl;
                cin >> PV;
            } while (PV <= 0);

            do {
                cout << "Number of payments [should be positive!]:" << endl;
                cin >> period;
            } while (period <= 0);

            do {
                cout << "Payment freq [1 (annually), 2 (semiannually), 4 (quarterly), 12 (monthhly)!]:" << endl;
                cin >> freq;
            } while (freq != 1 && freq != 2 && freq != 4 && freq != 12);

            do {
                cout << "Yearly interest rate [should be positive and in percentage!]:" << endl;
                cin >> IntRate;
            } while (IntRate <= 0);

            IntRate = IntRate/100/freq;

            temp=1;

            while (period !=0)
            {
                temp *= 1+IntRate;
                --period;
            }

            PMT= IntRate*PV*(1+1/(temp-1));

            cout << "Payment is "<< PMT<<endl;
        }
        if (sub == 2){
            do {
                cout << "Payment amount[should be positive!]:" << endl;
                cin >> PMT;
            } while (PMT <= 0);

            do {
                cout << "Number of payments [should be positive!]:" << endl;
                cin >> period;
            } while (period <= 0);

            do {
                cout << "Payment freq [1 (annually), 2 (semiannually), 4 (quarterly), 12 (monthhly)!]:" << endl;
                cin >> freq;
            } while (freq != 1 && freq != 2 && freq != 4 && freq != 12);

            do {
                cout << "Yearly interest rate [should be positive and in percentage!]:" << endl;
                cin >> IntRate;
            } while (IntRate <= 0);

            IntRate = IntRate/100/freq;

            temp = 1;

            while (period !=0){
                temp *= 1+IntRate;
                --period;
            }

            PV = PMT/(IntRate*(1+1/(temp-1)));

            cout << "Loan amount is "<< PV << endl;
        }
        if (sub == 3){
            do {
                cout << "Loan amount[should be positive!]:" << endl;
                cin >> PV;
            } while (PV <= 0);

            do {
                cout << "Payment amount[should be positive!]:" << endl;
                cin >> PMT;
            } while (PMT <= 0);

            do {
                cout << "Payment freq [1 (annually), 2 (semiannually), 4 (quarterly), 12 (monthhly)!]:" << endl;
                cin >> freq;
            } while (freq != 1 && freq != 2 && freq != 4 && freq != 12);

            do {
                cout << "Yearly interest rate [should be positive and in percentage!]:" << endl;
                cin >> IntRate;
            } while (IntRate <= 0);

            IntRate = IntRate/100/freq;

           temp = 1/( PMT / (PV*IntRate)-1)+1;

           period = 0;

           while (temp > (1+IntRate)){
               temp /= 1 + IntRate;
               ++period;
           }

            cout << "Number of payment is "<< period << endl;
        }
        else {
//            Compute Interest rate
        }
    } else {

        cout << "Please provide: " << endl;

        do {
            cout << "Loan amount[should be positive!]:" << endl;
            cin >> PV;
        } while (PV <= 0);

        do {
            cout << "Number of payments [should be positive!]:" << endl;
            cin >> period;
        } while (period <= 0);

        do {
            cout << "Payment freq [1 (annually), 2 (semiannually), 4 (quarterly), 12 (monthhly)!]:" << endl;
            cin >> freq;
        } while (freq != 1 && freq != 2 && freq != 4 && freq != 12);

        do {
            cout << "Starting month [should be positive!]:" << endl;
            cin >> month;
        } while (month <= 0);

        do {
            cout << "Starting year [should be positive!]:" << endl;
            cin >> year;
        } while (year <= 0);

        if (opt == 1) {
            do {
                cout << "Yearly interest rate [should be positive and in percentage!]:" << endl;
                cin >> IntRate;
            } while (IntRate <= 0);
        }
        else {
            do {
                cout << "Floating rate mean [should be positive and in percentage!]:" << endl;
                cin >> fltmean;
            } while (fltmean <= 0);

            do {
                cout << "Floating rate standard deviation [should be positive and in percentage!]:" << endl;
                cin >> fltstd;
            } while (fltstd <= 0);

            do {
                cout << "Margin [should be positive and in percentage!]:" << endl;
                cin >> margin;
            } while (margin <= 0);
        }

        prin = PV / period;

        cout << "Principle payment each period is " << prin << endl;

        for (i = 0; i < period; ++i) {

            if (opt == 2) {
                IntRate = boxMuller(fltmean, fltstd) + margin;
                cout << "Payment " << i + 1 << " has interest rate of " << IntRate << endl;
            }
            IntPmt = Interest(IntRate, PV, prin, freq, month, year, i);

            PV = PV - prin;

            if (month + (12 / freq) > 12) {
                month = month + (12 / freq) - 12;
                year = year + 1;
            } else {
                month = month + (12 / freq);
            }
        }

        return 0;
    }
}
