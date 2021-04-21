#include <fstream>
#include <map>
#include "NumberWithUnits.hpp"
using namespace std;

namespace ariel{
    static map<string, map<string, double> > units_map;

    double connect(double value, const string src, const string dest){
        if (src == dest){return value;}
        try {
            return  value * units_map.at(src).at(dest);
        }
        catch (const exception& e)   {
            throw invalid_argument{"Units do not match ["+ src + "] can't be converted to [" + dest +"]"};
        }
    }


    void func(const string str1 ,const string str2){
        for (auto [key,value] : units_map[str2])
        {
            double val  = units_map[str1][str2] * value;
            units_map[str1][key]= val;
            units_map[key][str1]= 1/val;
        }
    }


    void NumberWithUnits::read_units(ifstream &units_file) {

        double temp1=0,temp2=0;
        string str1 , str2, buff;

        while (units_file >> temp1 >> str1 >> buff >> temp2 >> str2){
            units_map[str1][str2] = temp2;
            units_map[str2][str1] = 1/temp2;
            func(str1,str2);
            func(str2,str1);
        }
    }


    /****************************  OverLoading Input&Output Operators ****************************************/

     ostream& operator<<(ostream &out, const NumberWithUnits& num){
         out << num.unit_val << "[" << num.unit_str << "]";
        return out;
     }

     istream& operator>>(istream &in,NumberWithUnits& num){
         string str;
         in >> num.unit_val >> str >> num.unit_str;
         return in;
     }
    /*********************************************************************************************************/

    /***************** OverLoading Arithmetic Operators Such As : {+,+=,-,-=,*,*=}  **************************/
    NumberWithUnits operator+(const NumberWithUnits& num1, const NumberWithUnits& num2)  {
        double val = connect(num2.unit_val,num2.unit_str,num1.unit_str);
        return NumberWithUnits(num1.unit_val + val , num1.unit_str);
    }
    NumberWithUnits operator+(const NumberWithUnits& num, double value){
        return NumberWithUnits(num.unit_val + value , num.unit_str);
    }
    NumberWithUnits operator+=(NumberWithUnits& num1, const NumberWithUnits& num2){
        num1.unit_val += connect(num2.unit_val,num2.unit_str,num1.unit_str);
        return num1;
    }
    NumberWithUnits operator-(const NumberWithUnits& num1, const NumberWithUnits& num2){
        double val = connect(num2.unit_val,num2.unit_str,num1.unit_str);
        return NumberWithUnits(num1.unit_val - val,num1.unit_str);
    }
    NumberWithUnits operator-(const NumberWithUnits& num){
        return NumberWithUnits(-num.unit_val,num.unit_str);
    }
    NumberWithUnits operator-=(NumberWithUnits& num1, const NumberWithUnits& num2){
        num1.unit_val -= connect(num2.unit_val,num2.unit_str,num1.unit_str);
        return num1;
    }
    NumberWithUnits operator*(NumberWithUnits& num, double val){
        return NumberWithUnits(num.unit_val * val,num.unit_str);
    }
    NumberWithUnits operator*(double val, NumberWithUnits& num){
        return NumberWithUnits(num.unit_val*val,num.unit_str);
    }
    NumberWithUnits operator*=(NumberWithUnits& num, double val){
        return NumberWithUnits(num.unit_val *= val,num.unit_str);
    }
    NumberWithUnits operator*=(double val, NumberWithUnits& num){
        return NumberWithUnits(val *= num.unit_val,num.unit_str);
    }



    /***************** OverLoading Incrementation&Decrementation Operators Such As : {++a,a++,--a,a--} *******/
    NumberWithUnits operator++(NumberWithUnits& num){return NumberWithUnits(++num.unit_val,num.unit_str);}

    NumberWithUnits operator++(NumberWithUnits& num, int){return NumberWithUnits(num.unit_val++,num.unit_str);}

    NumberWithUnits operator--(NumberWithUnits& num){return NumberWithUnits(--num.unit_val,num.unit_str);}

    NumberWithUnits operator--(NumberWithUnits& num, int){return NumberWithUnits(num.unit_val--,num.unit_str);}
    /*********************************************************************************************************/




    /****************  OverLoading Comparison Operators Such As : {<,<=,>,>=,==,!=}  *************************/

    int comparison(const NumberWithUnits& num1, const NumberWithUnits& num2){
        double epsilon = 0.00001;
        double a = num1.unit_val - connect(num2.unit_val,num2.unit_str,num1.unit_str);
        double b = connect(num2.unit_val,num2.unit_str,num1.unit_str) - num1.unit_val  ;
        if (a > epsilon){return 1;}
        else if(b > epsilon){return -1;}
        return 0;
    }

    bool operator>(const NumberWithUnits& num1, const NumberWithUnits& num2) {return comparison(num1,num2)>0;}
    bool operator>=(const NumberWithUnits& num1, const NumberWithUnits& num2){return comparison(num1,num2)>=0;}
    bool operator<(const NumberWithUnits& num1, const NumberWithUnits& num2) {return comparison(num1,num2)< 0;}
    bool operator<=(const NumberWithUnits& num1, const NumberWithUnits& num2){return comparison(num1,num2) <=0;}
    bool operator==(const NumberWithUnits& num1, const NumberWithUnits& num2){return comparison(num1,num2) == 0;}
    bool operator!=(const NumberWithUnits& num1, const NumberWithUnits& num2){return comparison(num1,num2) !=0;}
    /*********************************************************************************************************/





}