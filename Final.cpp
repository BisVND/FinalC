/* Outline:
Functions:
 - boxMuller: for normal distribution
 - biSearch: Binary search
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

double boxMuller(double mean , double std) {
    double x , y , s , z , p;
    do {
        x = ((double) rand() * 2 / RAND_MAX) - 1;
        y = ((double) rand() * 2 / RAND_MAX) - 1;
        s = x * x + y * y;
    } while (s > 1);

    z = x * sqrt(-2 * log(s) / s);
    p = std * z + mean;
    return p;
}

double biSearch(double PV , int period , double PMT , double freq) {
    double ubound = 1 , lbound = 0 , intRate , PMTtemp;
    do {
        intRate = lbound + (ubound - lbound) / 2;
        PMTtemp = intRate / freq * PV * (1 + 1 / (pow(1 + intRate / freq , period) - 1));

        if (PMTtemp > PMT) {
            ubound = intRate;
        } else {
            lbound = intRate;
        }
    } while (abs(ubound - lbound) > 0.0000000001);
    return intRate;
}


main() {
    int opt , subOpt , sub , i , month , year , 
        period = 0;
    double intPmt , intRate , PV , PMT , freq , prin , fltMean , fltStd , margin ,
           accumPrin = 0;
    ofstream csvFile;
    char separator = ';';

    //************************************OPTION************************************//
    do {
        cout << "1: Fixed rate" << endl
             << "2: Floating rate" << endl
             << "3: Fixed rate, fixed instalments" << endl
             << "What payment method do you want to apply? ";
        cin >> opt;
    } while (opt != 1 && opt != 2 && opt != 3);

    if (opt == 3) {
        cout << "Please choose the case: " << endl
             << "1: Want to compute payment" << endl
             << "2: Want to compute Loan amount" << endl
             << "3: Want to compute number of payments" << endl
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
                cin >> sub;
                if (sub == 1) {
                    intRate = intRate * 100;
                }
            }
        } while (intRate <= 0);
    } else if (opt == 2) {
        do {
            cout << "Margin [should be positive and in percentage!]: " << endl;
            cin >> margin;
        } while (margin <= 0);
        do {
            cout << "Floating rate mean [should be positive and in percentage!]: " << endl;
            cin >> fltMean;
        } while (fltMean <= 0);
        do {
            cout << "Floating rate standard deviation [should be positive and in percentage!]: " << endl;
            cin >> fltStd;
        } while (fltStd <= 0);
    }
    // input freq, starting year and starting month
    do {
        cout << "Number of payment within a year [should be positive and within 12 months!]: " << endl;
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
    double fltRate[period];
    intRate = intRate / 100 / freq;

    if (opt == 1 || opt == 2 || subOpt == 1) {
        if (opt == 3) {
            PMT = intRate * PV * (1 + 1 / (pow(1 + intRate , period) - 1));
            cout << "Payment is " << PMT << endl;
        } else {
            prin = PV / period;
            for (i = 0 ; i < period ; ++i) {
                if (opt == 2) {
                    fltRate[i] = boxMuller(fltMean , fltStd) + margin;
                    intRate = fltRate[i] / 100;
                    cout << "Payment " << i + 1 << " has interest rate of " << intRate << endl;
                }
                intPmt = intRate * (PV - prin * i);
                cout << "Payment " << i + 1 << " occures in " << month << "/" << year << " has interest of " << intPmt
                     << " and total installment is " << intPmt + prin << endl;
            }
        }
    }

    if (subOpt == 2) {
        PV = PMT / (intRate * (1 + 1 / (pow(1 + intRate , period) - 1)));
        cout << "Loan amount is " << PV << endl;
    }

    if (subOpt == 3) {
        period = log(1 / (PMT / (PV * intRate) - 1) + 1) / log(1 + intRate);
        cout << "Total number of payment is " << round(period) << endl;
    }

    if (subOpt == 4) {
        intRate = biSearch(PV , period , PMT , freq);
        cout << "Interest rate is " << round(intRate * 10000) / 100 << endl;
    }

    //************************************SAVE************************************//
    cout << "Do you want to save file? " << endl
         << "1.Yes" << endl
         << "2.No" << endl;
    cin >> sub;

    if (sub == 1) {
        csvFile.open("output.csv");
        if (month + (12 / freq) > 12) {
            month = month + (12 / freq) - 12;
            year = year + 1;
        } else {
            month = month + (12 / freq);
        }

        if (opt == 1) {
            prin = PV / period;
            csvFile << "Seq" << separator << "Period" << separator << "Opening Balance" << separator << "Principal"
                    << separator << "periodic interest rate" << separator << "interest" << separator << "instalment"
                    << separator << "closing balance\n";
            for (i = 0 ; i < period ; i++) {
                intPmt = intRate * (PV - prin * i);
                csvFile << i + 1 << separator << month << "/" << year << separator << PV - prin * i << separator << prin
                        << separator << intRate / freq << separator << intPmt << separator << prin + intPmt
                        << separator << PV - prin * (i + 1) << "\n";
            }
        }
        if (opt == 2) {
            csvFile << "Seq" << separator << "Period" << separator << "Opening Balance" << separator << "Principal"
                    << separator << "floating rate" << separator << "periodic interest rate" << separator
                    << "interest" << separator << "instalment" << separator << "closing balance\n";
            for (i = 0 ; i < period ; i++) {
                intPmt = fltRate[i] * (PV - prin * i);

                csvFile << i + 1 << separator << month << "/" << year << separator << PV - prin * i << separator
                        << prin << separator << fltRate[i] << separator << fltRate[i] / freq << separator << intPmt
                        << separator << prin + intPmt << separator << PV - prin * (i + 1) << "\n";
            }
        }
        if (opt == 3) {
            csvFile << "Seq" << separator << "Period" << separator << "Opening Balance" << separator << "Principal"
                    << separator << "periodic interest rate" << separator << "interest" << separator << "instalment"
                    << separator << "closing balance\n";
            for (i = 0 ; i < period ; i++) {
                accumPrin += prin;
                intPmt = intRate / freq * (PV - accumPrin);
                prin = PMT - intPmt;
                csvFile << i + 1 << separator << month << "/" << year << separator << PV - accumPrin << separator
                        << prin << separator << intRate / freq << separator << intPmt << separator << PMT << separator
                        << PV - accumPrin - prin << "\n";
            }
        }
        csvFile.close();
        cout << "Files saved!" << endl;
    } else {
        cout << "The program end here!";
        return 0;
    }
}
