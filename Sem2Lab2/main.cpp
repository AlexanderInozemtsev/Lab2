#include <iostream>
#include <functional>
#include "UI/UI.h"


//std::function<int (int,int)> cmp = [](int a, int b){return  a> b;};

int main() {
    int number;
    do {
        UI ui = UI();
        ui.PrintMainOptions();
        number = ui.GetNumber();

        switch (number){
            case 0:
                ui.Test();
                break;
            case 1:
                ui.CreateRandomBtree();
                ui.PrintBTreeOptions();
                number = ui.GetNumber();
                switch (number) {
                    case 1:
                        ui.InsertVal();
                        break;
                    case 2:
                        ui.DeleteRandomVal();
                        break;
                    case 3:
                        ui.DeleteManualVal();
                        break;
                }
                break;
            case 2:
                ui.CreateRandomDic();
                ui.PrintDicOptions();
                number = ui.GetNumber();
                switch (number){
                    case 1:
                        ui.Add();
                        break;
                    case 2:
                        ui.Delete();
                        break;
                    case 3:
                        ui.Contains();
                        break;
                    case 4:
                        ui.Get();
                        break;
                }
                break;
            case 3:
                ui.CacheDemo();
                break;

        }
        if (number != 4)
            system("pause");
    } while (number != 4);
    return 0;
}








/*auto List = ListSequence<Person>(arr, 1000);
auto cachedList = new CachedList(&List);
for (int k = 0; k < 100000 ; ++k) {
cachedList->Get(rand()%1000);
 Person* arr = new Person[1000];
    for (int j = 0; j < 1000 ; ++j) {
        arr[j] = Person(j);
    }
}
 */
