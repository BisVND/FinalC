#include <iostream>
#include <cmath>
using namespace std;

int pd(){
    
    int opt, tn;
    int k[5] = {1, 2, 3, 6, 12};
    cout << "1: Monthly (every month)" << endl
         << "2: Bi-monthly (every 2 months)" << endl
         << "3: Quarterly (every 3 months)" << endl
         << "4: Semi-annually (every 6 months)" << endl
         << "5: Annually (yearly)" << endl
         << "Please pick the payment period: ";
    cin >> opt;
    
    cout << "How many year the payment is? ";
    cin >> tn;
    return tn*k[opt-1];
}

int opt3_1(irPd){
    double PV, irPd;

}






int main() {
    
    int opt, irPd;
    cout << "1: Fixed rate" << endl
         << "2: Floating rate" << endl
         << "3: Fixed rate, fixed instalments" << endl
         << "Which payment method do you want to apply? ";
    cin >> opt;

    if(opt == 3)
    {
        cout << "1: n, PV, r" << endl
             << "2: PMT, n, r" << endl
             << "3: PMT, PV, r" << endl
             << "4: PMT, n, PV " << endl
             << "Please choose given variables: ";
        cin >> opt;
        if(opt != 3)
        {
            irPd = optpd();
        }
        else
        {

        }
    }
    else if(opt == 1)
    {
        irPd = optpd();
    }
    else if(opt == 2)
    {
        irPd = optpd();
    }
    
}
