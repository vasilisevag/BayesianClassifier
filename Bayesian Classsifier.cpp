#include <iostream>
#include <utility>
#include <vector>
#include <algorithm>
#include <tuple>
using namespace std;

template <typename T, typename... Args>
class BayesClassifier{
	public:
		BayesClassifier(const std::vector<std::tuple<Args..., T>>& data) : data(data) {}

		T TakeDecision(const std::tuple<Args...>& args){
			std::vector<T> classes = FindClasses();
			
			double maxPossibility = 0;
			T maxPossibilityClass = classes[0];
			for(auto classe : classes){
				double classFrequency = CalculateClassFrequency(classe);
				double posibility = 1;
				int counter = 0;
				int classCounter = 0;
				for(int i = 0; i < sizeof...(Args); i++){
					counter = 0;
					classCounter = 0;
					for(int j = 0; j < data.size(); j++){
						if(get<sizeof...(Args)>(data[j]) == classe) classCounter++;
						switch(i){
							case 0: if(get<sizeof...(Args)>(data[j]) == classe && get<0>(args) == get<0>(data[j]))
								counter++; break;
							case 1: if(get<sizeof...(Args)>(data[j]) == classe && get<1>(args) == get<1>(data[j]))
								counter++; break;
							//case 2: if(get<sizeof...(Args)>(data[i]) == classe && get<2>(args) == get<2>(data[i]))
							//	counter++; break;
							//case 3: if(get<sizeof...(Args)>(data[i]) == classe && get<3>(args) == get<3>(data[i]))
							//	counter++; break;
							//case 4: if(get<sizeof...(Args)>(data[i]) == classe && get<4>(args) == get<4>(data[i]))
							//	counter++; break;
						}
					}
					cout << counter << " " << classCounter << endl;
					posibility *= counter / (float)classCounter;
				}
				posibility *= classFrequency;
				if(posibility > maxPossibility){
					maxPossibility = posibility;
					maxPossibilityClass = classe;
				}
			}
			cout << maxPossibility << ' ' << maxPossibilityClass << endl;
			return maxPossibilityClass;
		}
	private: 
		std::vector<T> FindClasses(){
			std::vector<T> classes;
			for(auto arguments : data){
				if(find(classes.begin(), classes.end(), get<sizeof...(Args)>(arguments)) == classes.end())
					classes.push_back(get<sizeof...(Args)>(arguments));
			}
		
			return classes;
		}

		double CalculateClassFrequency(const T& classe){
			double classCount = 0;
			for(auto arguments : data)
				if(get<sizeof...(Args)>(arguments) == classe)
					classCount++;
			return classCount / data.size();
		}

		std::vector<std::tuple<Args..., T>> data;
};

int main(){
	BayesClassifier<char, int, std::string> bc(vector<tuple<int, std::string, char>>{std::tuple<int, std::string, char>(1, "goal", 'y'), 
																					 std::tuple<int, std::string, char>(2, "goal", 'y'),
																					 std::tuple<int, std::string, char>(1, "no goals", 'n'),
																					 std::tuple<int, std::string, char>(1, "no goals", 'n'),
																					 std::tuple<int, std::string, char>(1, "no goals", 'n'),
																					 std::tuple<int, std::string, char>(1, "no goals", 'n'),
																					 std::tuple<int, std::string, char>(1, "no goals", 'n'),
																					 std::tuple<int, std::string, char>(1, "no goals", 'n')});
	bc.TakeDecision(std::tuple<int, std::string>{1, "no goals"});
}