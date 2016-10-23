
#include <iostream>
#include <memory>
#include <string>

using namespace std;


class Person
{
public:
    Person()
    {
        cout << "Person Construction" <<endl;
    };
    Person(string name)
    {
        this->name = name;
        cout << "Person Construction with name: " << name <<endl;
    };
    ~Person(){};
    
    void showName()
    {
        cout << "The name is " << name << endl;
    };
    void setName(string name)
    {
        this->name = name;
    };
private:
    string name;
};

void changeName(shared_ptr<Person> whoever, string newName)
{
    whoever->setName(newName);
    cout << "changeName => intance count: "<< whoever.use_count() << endl;
}

int main()
{
    shared_ptr<Person> jack = make_shared<Person>("jack");
    
    jack->showName();
    cout << "intance count: "<< jack.use_count() << endl;
    changeName(jack, "newJack");
    cout << "intance count: "<< jack.use_count() << endl;
    jack->showName();
    
    return 0;
}
