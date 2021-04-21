#include <iostream>
#include <map>
#include <string>


using namespace std;

namespace ariel{

    class NumberWithUnits{
    private:
        double unit_val;
        string unit_str;

    public:
        NumberWithUnits(double value,string unit){
            this->unit_val = value;
            this->unit_str = unit;
        }
        ~NumberWithUnits(){}

        static void read_units(ifstream& units_file);
        friend int comparison(const NumberWithUnits& num1, const NumberWithUnits& num2);


        /****************************  OverLoading Input&Output Operators ****************************************/

        friend ostream& operator<<(ostream &out, const NumberWithUnits& num);

        friend istream& operator>>(istream &in,NumberWithUnits& num);
        /*********************************************************************************************************/





        /***************** OverLoading Arithmetic Operators Such As : {+,+=,-,-=,*,*=}  **************************/
        friend NumberWithUnits operator+(const NumberWithUnits& num1, const NumberWithUnits& num2);
        friend NumberWithUnits operator+(const NumberWithUnits& num, double value);
        friend NumberWithUnits operator+=(NumberWithUnits& num1, const NumberWithUnits& num2);
        friend NumberWithUnits operator-(const NumberWithUnits& num1, const NumberWithUnits& num2);
        friend NumberWithUnits operator-(const NumberWithUnits& num);
        friend NumberWithUnits operator-=(NumberWithUnits& num1, const NumberWithUnits& num2);
        friend NumberWithUnits operator*(NumberWithUnits& num, double val);
        friend NumberWithUnits operator*(double val, NumberWithUnits& num);
        friend NumberWithUnits operator*=(NumberWithUnits& num, double val);
        friend NumberWithUnits operator*=(double val, NumberWithUnits& num);
        /*********************************************************************************************************/


        /***************** OverLoading Incrementation&Decrementation Operators Such As : {++a,a++,--a,a--} *******/
        friend NumberWithUnits operator++(NumberWithUnits& num);
                                                           
        friend NumberWithUnits operator++(NumberWithUnits& num, int);
                                                           
        friend NumberWithUnits operator--(NumberWithUnits& num);
                                                           
        friend NumberWithUnits operator--(NumberWithUnits& num, int);
        /*********************************************************************************************************/





        /****************  OverLoading Comparison Operators Such As : {<,<=,>,>=,==,!=}  *************************/

        friend bool operator>(const NumberWithUnits& num1, const NumberWithUnits& num2);
        friend bool operator>=(const NumberWithUnits& num1, const NumberWithUnits& num2);
        friend bool operator<(const NumberWithUnits& num1, const NumberWithUnits& num2);
        friend bool operator<=(const NumberWithUnits& num1, const NumberWithUnits& num2);
        friend bool operator==(const NumberWithUnits& num1, const NumberWithUnits& num2);
        friend bool operator!=(const NumberWithUnits& num1, const NumberWithUnits& num2);
        /*********************************************************************************************************/



    };










}
