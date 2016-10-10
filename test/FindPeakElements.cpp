#include <iostream>
#include <vector>
using namespace std;

//
//C++实现求一维离散数据极值（波峰、波谷）
//
//参数：数组，数组大小
void findPeaks(int *num,int count)
{
    vector<int> sign;
    for(int i = 1 ;i < count; i++)
    {
        /*相邻值做差：
         *小于0，赋-1
         *大于0，赋1
         *等于0，赋0
         */
        int diff = num[i] - num[i-1];
        if(diff>0)
        {
            sign.push_back(1);
        }
        else if(diff<0)
        {
            sign.push_back(-1);
        }
        else
        {
            sign.push_back(0);
        }
    }
    //再对sign相邻位做差
    //保存极大值和极小值的位置
    vector<int> indMax;
    vector<int> indMin;
    
    for(int j = 1;j<sign.size();j++)
    {
        int diff = sign[j]-sign[j-1];
        if(diff<0)
        {
            indMax.push_back(j);
        }
        else if(diff>0)
        {
            indMin.push_back(j);
        }
    }
    cout<<"极大值为:"<<endl;
    for(int m = 0;m<indMax.size();m++)
    {
        cout<<num[indMax[m]]<<"  ";
    }
    cout<<endl;
    cout<<"极小值为："<<endl;
    for(int n = 0;n<indMin.size();n++)
    {
        cout<<num[indMin[n]]<<"  ";
    }
}

int main()
{
    int a[] = {30,2,10,11,6,4,8,10,23,0};
    findPeaks(a,10);
    return 0;
}
