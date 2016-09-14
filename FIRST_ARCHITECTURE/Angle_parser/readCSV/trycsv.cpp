//code to test readCSV.cpp
#include "readCSV.cpp"
#include <typeinfo>
int main()
{
readCSV i;
std::vector<std::string>  v;
std::vector<int> vect;
std::stringstream ss(v.at(5));
int m;
v=i.storeCSV2array("ang1.csv",3,3);
//for (int j=0;j<v.size();j++)
//{

  //  char *c = const_cast<char*>(v.at(i).c_str());
  std::cout << v.at(5) << "\n";


    std::cout<<"a is of type: "<<typeid(v.at(1)).name()<<std::endl; 
 //   std::stringstream stream(v.at(1));
while (ss >> m)
    {
        vect.push_back(m);

        if (ss.peek() == ',')
            ss.ignore();
    }

    for (int h=0; h< vect.size();h++)
        std::cout << vect.at(h)<<std::endl;



//std::cout <<"\n";
//}


}
