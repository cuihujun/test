
#include <iostream>
#include <vector>
#include <string>
#include <sstream>

using namespace std;
template <typename T>
std::ostream& operator<< (std::ostream& out, const std::vector<T>& v)
{
    if ( !v.empty() )
    {
        out << '[';
        std::copy (v.begin(), v.end(), std::ostream_iterator<T>(out, " "));
        out << "\b\b]";
    }
    return out;
}


vector<unsigned long> res;
unsigned long max(unsigned long  a, unsigned long  b)
{
    if(a>b)
    {
        return a;
    }
    else
    {
        return b;
    }
}

unsigned long lcs( vector<string>&X, vector<string>&Y, unsigned long  m, unsigned long  n )
{
    unsigned long length;
    if (m == 0 || n == 0)
        return 0;
    if ((X[m].compare(Y[n]) == 0)&&(m>0&&n>0))
    {
        if(find(res.begin(), res.end(), n)==res.end())
        {
            res.push_back(n);
        }
        length = 1 + lcs(X, Y, m-1, n-1);
    }
    else
    {
        length = max(lcs(X, Y, m, n-1), lcs(X, Y, m-1, n));
    }
    
    return length;
}


 int strlen(char s[])
 {
     int p;
     for(p=1; s[p]!='\0'; p++);
     return p;
 }
 
 void split(const std::string &s, char delim, std::vector<string> &elems)
 {
     std::stringstream ss;
     ss.str(s);
     std::string item;
     while (std::getline(ss, item, delim))
     {
        elems.push_back(item);
     }
 }
 
 std::vector<std::string> split(const std::string &s, char delim)
 {
     std::vector<std::string> elems;
     split(s, delim, elems);
     return elems;
 }


template<typename T>
std::vector<T> split(const std::string& line)
{
    std::istringstream is(line);
    return std::vector<T>(std::istream_iterator<T>(is), std::istream_iterator<T>());
}

int main()
{
    std::string X;
    std::getline(std::cin,X);
    
    std::string Y;
    std::getline(std::cin,Y);
    
    //    for(std::string::size_type i = 0; i < X.size(); ++i)
    //    {
    //        if(X[i] == ' ')
    //            std::cout<<"It is a space!!!"<<std::endl;
    //    }
    
    vector<string> prod = split<string>(X);
    vector<string> label = split<string>(Y);;
    //    vector<string> prod = {"in", "the", "spain"};
    //    vector<string> label = {"the", "weather", "forecast", "in", "that", "the", "rain", "in", "spain", "stays"};
    
    
    unsigned long m = prod.size();
    unsigned long n = label.size();
    
    cout<< lcs(prod, label, m-1, n-1 )<<endl;
    
    sort(res.begin(), res.end());
    cout << res << endl;
    return 0;
}


/*
 INPUT:
 
 in the spain
 the weather forecast in that the rain in spain stays
 
 
 OUTPUT:
 2
 [5 8]
 
 */

























