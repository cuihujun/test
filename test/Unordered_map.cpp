
#include <iostream>
#include <unordered_map>

using namespace std;


int main()
{
	unordered_map<int, string> umap1 =  {
        { 3,"#FF0000"},
        { 4,"#00FF00"},
        { 5,"#0000FF"}
    };

    unordered_map<string, string> umap2 =  {
        make_pair("first","#FF0000"),
        make_pair("second","#00FF00"),
        make_pair("third","#0000FF")
    };

	unordered_map<string, int> umap3;
	umap3["zero"] = 0;
	umap3["one"] = 1;
	umap3["two"] = 2;
	umap3["three"] = 3;


	for(const auto& value : umap1)
	{
		std::cout << "umap1 Key:[" << value.first << "] Value:[" << value.second << "]" << endl;
	}

	std::cout << umap1[3] << endl;

	std::cout << umap2["second"] << endl;

	for(const auto& value : umap3)
	{
		std::cout << "umap3 Key:[" << value.first << "] Value:[" << value.second << "]" << endl;
	}
	std::cout << umap3["two"] << endl;

	return 0;
}










