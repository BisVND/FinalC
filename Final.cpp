/* Outline:
Functions:
 - boxMuller: for normal distribution
 - biSearch: Binary search
 - interest: calculating interest for opt 2
 - saveToFile: save File
Main:
 - Option
 - Input
 - Calculation
 - Save
*/

#include<iostream>
#include<cmath>
#include<fstream>

using namespace std;

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

double biSearch(double PV, double period, double PMT) {
    double ubound = 1 , lbound = 0;
    double intRate, PMTtemp;
    do {
        intRate = lbound + (ubound - lbound) / 2;
        PMTtemp = intRate * PV * (1 + 1 / (pow(intRate , period) - 1));

        if (PMTtemp < PMT) {
            ubound = intRate;
        } else {
            lbound = intRate;
        }
    } while (abs(ubound - lbound) > 0.0001);
    return intRate;
}

double interest(double intRate, double PV, double period, double freq, double month, int year, int i) {
    double intPmt , prin;

    intPmt = intRate * PV;
    cout << "Payment " << i + 1 << " occures in " << month << "/" << year << " has interest of " << intPmt
         << " and total installment is " << intPmt + prin << endl;

    return intPmt;
}

void saveToFile() {
    char listSeparator=';';

    ofstream csvFile;
    csvFile.open ("output.csv");
    csvFile << "col1"<< listSeparator <<"col2"<< listSeparator <<"col3\n";
    csvFile.close();

    cout << "Files saved!" << endl;
}



main () {
    int opt , subOpt , i , month , year, temp;
    double intRate , PV , PMT , period , freq , prin , intPmt , fltMean , fltStd , margin ;

    //************************************OPTION************************************//
    do {
        cout << "1: Fixed rate" << endl
             << "2: Floating rate" << endl
             << "3: Fixed rate, fixed instalments" << endl
             << "What payment method do you want to apply? ";
        cin >> opt;
    } while (opt != 1 && opt != 2 && opt != 3 );

    if (opt == 3) {
        cout << "Please choose the case: " << endl
             << "1: Want to compute payment" << endl
             << "2: Want to compute Loan amount" << endl
             << "3: Want to compute number of years" << endl
             << "4: Want to compute interest rate " << endl;
        cin >> subOpt;
    }

    //************************************INPUT************************************//
    cout << "Please provide: " << endl;
    //input PMT
    if (opt != 1 && opt != 2 && subOpt != 1) {
        do {
            cout << "Payment amount [should be positive!]: " << endl;
            cin >> PMT;
        } while (PMT <= 0);
    }
    // input PV
    if (subOpt != 2) {
        do {
            cout << "Loan amount [should be positive!]: " << endl;
            cin >> PV;
        } while (PV <= 0);
    }
    // input period
    if (subOpt != 3) {
        do {
            cout << "Total number of payments [should be positive!]: " << endl;
            cin >> period;
        } while (period <= 0);
    }
    // input intRate
    if (opt != 2 && subOpt != 4) {
        do {
            cout << "Yearly interest rate [should be positive!]: " << endl;
            cin >> intRate;
            if (intRate > 0 && intRate <= 1) {
                cout << "Do you mean the interest is " << intRate * 100 << " ?" << endl
                     << "1. Yes" << endl
                     << "2. No" << endl;
                cin >> temp;
                if (temp == 1) {
                    intRate = intRate * 100;
                }
            }
        } while (intRate <= 0);
    } else if (opt == 2) {
        do {
            cout << "Margin [should be positive and in percentage!]: "<< endl;
            cin >> margin;
        } while (margin <= 0);
        do {
            cout << "Floating rate mean [should be positive and in percentage!]: " << endl;
            cin >> fltMean;
        } while (fltMean <= 0);
        do {
            cout << "Floating rate standard deviation [should be positive and in percentage!]: "<< endl;
            cin >> fltStd;
        } while (fltStd <= 0);
    }
    // input freq, starting year and starting month
    do {
        cout << "Number of payment made within a year [should be positive and within 12 months!]: "<< endl;
        cin >> freq;
    } while (freq <= 0 || freq > 12);
    do {
        cout << "Starting month [should be positive!]:" << endl;
        cin >> month;
    } while (month <= 0);
    do {
        cout << "Starting year [should be positive!]:" << endl;
        cin >> year;
    } while (year <= 0);

    //************************************CALCULATION************************************//
    intRate = intRate / 100 / freq;

    if (opt == 1 || opt == 2 || subOpt == 1) {
        if (opt == 3) {
            PMT = intRate * PV * (1 + 1 / (pow(1 + intRate , period) - 1));
            cout << "Payment is " << PMT << endl;
        } else {
            prin = PV / period;

            cout << "Principle payment each period is " << prin << endl;
            for (i = 0; i < period; ++i) {
                if (opt == 2) {
                    intRate = boxMuller(fltMean, fltStd) + margin;
                    cout << "Payment " << i + 1 << " has interest rate of " << intRate << endl;
                }
                intPmt = interest(intRate, PV, period, freq, month, year, i);
                PV = PV - prin;

                if (month + (12 / freq) > 12) {
                    month = month + (12 / freq) - 12;
                    year = year + 1;
                } else {
                    month = month + (12 / freq);
                }
            }
        }
    }

    if (subOpt == 2) {
        PV = PMT / (intRate * (1 + 1 / (pow(1 + intRate , period) - 1)));
        cout << "Loan amount is " << PV << endl;
    }

    if (subOpt == 3) {
        temp = 1 / (PMT / (PV * intRate) - 1) + 1;
        while (temp > (1 + intRate)) {
            temp /= 1 + intRate;
            ++period;
        }
        cout << "Number of payment is " << period << endl;
    }

    if (subOpt == 4) {
        intRate = biSearch(PV , period , PMT);
        cout << "Interest rate is " << intRate << endl;
    }

    //************************************SAVE************************************//
    saveToFile();
}


//        period = 0;
//        while (temp > (1+intRate)){
//            temp /= 1 + intRate;
//            ++period;
//        }