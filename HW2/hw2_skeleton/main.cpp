////////////////////////////////////////////////////////////////////////////////
// SE271 - Assignment 2: Source file - Main Function for Testing
// YOU WILL NOT submit this file. Again, DO NOT submit.
// Use it for your testing.
////////////////////////////////////////////////////////////////////////////////
#include "hw2.h"

#include <iostream>

void printList(const VariableList& varList) {
    for (unsigned int idx = 0; idx < varList.getSize(); ++idx) {
        DataType curType = varList.getType(idx);
        if (idx > 0)
            std::cout << ", ";

		switch (curType) {
        case DataType::Integer:
			{
				int val;
				if (varList.getValue(idx, val) == false)
					std::cout << "SOMETHING_WRONG";
				else
					std::cout << val;
			}
			break;
        case DataType::Float:
            {
                float val;
                if (varList.getValue(idx, val) == false)
                    std::cout << "SOMETHING_WRONG";
                else
                    std::cout << val;
            }
            break;
        case DataType::Str:
            {
                std::string val;
                if (varList.getValue(idx, val) == false)
                    std::cout << "SOMETHING_WRONG";
                else
                    std::cout << "\"" << val << "\"";
            }
            break;
		default:
			std::cout << "SOMETHING_WRONG";
			break;
		}
    }
    std::cout << std::endl;
}

void simpleTest1() {
    VariableList varList;
    varList.add(1);
    varList.add(3);
    varList.add(5);
    varList.add(7);
    printList(varList);
    
    varList.remove(0);
    printList(varList);
}

void simpleTest2() {
    VariableList varList;
    varList.add(1.0f);
    varList.add("Carrot");
    varList.add(3);
    varList.add(4);
    varList.remove(0);
    varList.remove(0);
    varList.remove(0);
    printList(varList);
    
}

void simpleTest3() {
    VariableList varList;
    VariableList varList2;
    varList.add(1);
    varList.add(2);
    varList.add(3);
    varList2.add(4);
    varList2.add(5.1f);
    varList.append(varList2);
    printList(varList);
}

void simpleTest4() {
    VariableList varList;
    varList.add(1);
    varList.add(2.1f);
    varList.add(3);
    varList.replace(2, "Apple");
    printList(varList);
}

void complexTest() {
    int initialArray[] = { 1, 2, 3, 4 };
    VariableList varList(initialArray, sizeof(initialArray) / sizeof(int));
    printList(varList);

    std::cout << "Add 1" << std::endl;
    varList.add(1);
    printList(varList);

    std::cout << "Add 2.1f" << std::endl;
    varList.add(2.1f);
    printList(varList);

    std::cout << "Appended another list with strings" << std::endl;
    std::string anotherArray[] = { "Apple", "Banana" };
    VariableList anotherVarList(anotherArray, 2);
    varList.append(anotherVarList);
    printList(varList);

    std::string anotherStr = "Cucumber";
    std::cout << "Replace Index=1 element with \"Cucumber\"" << std::endl;
    varList.replace(1, anotherStr);
    printList(varList);

    std::cout << "Replace Index=7 element with 4.5" << std::endl;
    varList.replace(7, 4.5f);
    printList(varList);

    std::cout << "Remove an element of Index=6" << std::endl;
    varList.remove(6);
    printList(varList);

    std::cout << "Remove elements of Index=6 and Index=0 again" << std::endl;
    varList.remove(6);
    varList.remove(0);
    printList(varList);

    std::cout << "Try to replace an element of out-of-index" << std::endl;
    bool ret = varList.replace(5, 1);
    std::cout << "Return value: " << std::boolalpha << ret << std::endl;

    std::cout << "Get the list size" << std::endl;
    std::cout << varList.getSize() << std::endl;

    std::cout << "Change a string already added and add the changed one" << std::endl;
    anotherStr = "Carrot";
    varList.add(anotherStr);
    printList(varList);
}

int main() {
    std::cout << "<<Simple Test 1>>" << std::endl;
    simpleTest1();
    std::cout << "<<Simple Test 2>>" << std::endl;
    simpleTest2();
    std::cout << "<<Simple Test 3>>" << std::endl;
    simpleTest3();

    std::cout << "<<Simple Test 4>>" << std::endl;
    simpleTest4();

    std::cout << std::endl << "<<Complex Test>>" << std::endl;
    complexTest();
    return 0;
}
