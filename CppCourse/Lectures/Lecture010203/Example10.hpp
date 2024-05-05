#include <iostream>
#include <vector>


void Example10(){

	header(10);
	
	// C++11 features
	// initializing with initializer list
	std::vector<int> vec1{3, 14, 15, 92, 65};
	std::vector<int> vec2 = {2, 71, 82, 81, 82, 84};

	// range based for loop and using auto -- capturing elements by value by value
	std::cout << "Values printed from the first for loop: ";	
	for(auto i : vec1){ std::cout << ++i << " "; }
	std::cout << std::endl << "Values of vec1 after the first for loop: ";
	for(const auto i : vec1){	std::cout << i << " "; }

	// range based for loop and using auto -- capturing elements by value by reference
	std::cout << std::endl << "Values printed from the third for loop: ";	
	for(auto& i : vec2){ std::cout << ++i << " "; }
	std::cout << std::endl << "Values of vec2 after the third for loop: ";
	for(const auto& i : vec2){ std::cout << i << " ";	}
	std::cout << std::endl;

}

/*
Values printed from the first for loop: 4 15 16 93 66
Values of vec1 after the first for loop: 3 14 15 92 65
Values printed from the third for loop: 3 72 83 82 83 85
Values of vec2 after the third for loop: 3 72 83 82 83 85
*/