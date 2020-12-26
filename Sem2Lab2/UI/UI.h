

#ifndef SEM2LAB2_UI_H
#define SEM2LAB2_UI_H

#include <iostream>
#include "../BTree/BTree.h"
#include <ctime>
#include <exception>
#include "../Test/BTreeTest.h"
#include "../Test/DictionaryTest.h"
#include "../CachedList/Person .h"
#include "../CachedList/CachedList.h"

class UI {
    std::function<int (int,int)> cmp = [](int a, int b){return  a> b;};
    BTree<int>* Btree = new BTree<int>(cmp);
    BTreeDictionary<int,int>* dic = new BTreeDictionary<int,int>(cmp);

public:


    void Test(){
        btreeTest::Insert();
        btreeTest::NotContains();
        btreeTest::Contains();
        btreeTest::FindMissingElement();
        btreeTest::GetFromEmpty();
        btreeTest::DeleteInEmpty();
        btreeTest::DeleteFromNonLeaf();
        btreeTest::DeleteFromLeaf();
        std::cout << "Btree tests passed" << std::endl;

        dictionaryTest::Add();
        dictionaryTest::AddExisting();
        dictionaryTest::NotContains();
        dictionaryTest::Contains();
        dictionaryTest::Get();
        dictionaryTest::GetMissingElem();
        dictionaryTest::Remove();
        std::cout << "Dictionary tests passed" << std::endl;
    }

    int GetNumber(){
        int n = 0;
        std::cin >> n;
        return n;
    }
    void PrintMainOptions(){
        std::cout << "0 - Run tests" << std::endl;
        std::cout << "1 - Work with Bree" << std::endl;
        std::cout << "2 - Work with Dictionary" << std::endl;
        std::cout << "3 - Demonstration of cache" << std::endl;
        std::cout << "4 - Exit" << std::endl;
    }

    void PrintBTreeOptions(){
        std::cout << "1 - Insert value" << std::endl;
        std::cout << "2 - Delete random value" << std::endl;
        std::cout << "3 - Delete value" << std::endl;
    }

    void PrintDicOptions(){
        std::cout << "1 - Add pair(int,int)" << std::endl;
        std::cout << "2 - Delete by key" << std::endl;
        std::cout << "3 - Check if dictionary contains key" << std::endl;
        std::cout << "4 - Get value by key" << std::endl;
    }
    void CreateRandomBtree (){
        srand(std::time(nullptr));
        for (int i = 0; i < 15 ; ++i)
            Btree->Insert(rand()%50);
        std::cout << "BTree was randomly created:" << std::endl;
        std::cout << Btree->Traverse() << std::endl;
    }
    void InsertVal(){
        Btree->Insert(GetNumber());
        std::cout << Btree->Traverse() << std::endl;
    }
    void DeleteRandomVal(){
        srand(std::time(nullptr));
        while (true){
            try {
                int _rand = rand()%50;
                Btree->Delete(_rand);
                std::cout << "Element " << _rand << " was deleted" <<std::endl;
                std::cout << Btree->Traverse() << std::endl;
                break;
            } catch (const std::logic_error& e) {
                continue;
            }
        }
    }
    void DeleteManualVal(){
        try{
        Btree->Delete(GetNumber());
        std::cout << Btree->Traverse() << std::endl;
        } catch (const std::logic_error& e){
            std::cout << "There is not such element in BTree" << std::endl;
        }
    }

    void CreateRandomDic(){
        srand(std::time(nullptr));
        for (int i = 0; i < 10 ; ++i) {
            dic->Add(i,rand()%50);
        }
        std::cout << "Dictionary was randomly created:" << std::endl;
        std::cout << dic->ToString() << std::endl;
    }
    void Add(){
        std::cout << "Key:" << std::endl;
        int key = GetNumber();
        std::cout << "Value:" << std::endl;
        int value = GetNumber();
        try {
            dic->Add(key, value);
            std::cout << dic->ToString() << std::endl;
        } catch (const std::logic_error& e) {
            std::cout << "Key already exists in Map" << std::endl;
        }
    }
    void Delete(){
        try {
            int a = GetNumber();
            dic->Remove(a);
            std::cout << dic->ToString() << std::endl;
        } catch (const std::logic_error& e) {
            std::cout << "There is not this key in Map" << std::endl;
        }
    }
    void Contains(){
        int key = GetNumber();
        if (dic->ContainsKey(key)){
            std::cout << "Yes" << std::endl;
        } else
            std::cout << "No" << std::endl;
    }
    void Get(){
        try {
            int key = GetNumber();
            std::cout <<  "Value for a key " << key << " is " << dic->Get(key) << std::endl;
        } catch (const std::logic_error& e) {
            std::cout << "This is not such a key in Map" << std::endl;
        }
    }

    void CacheDemo(){

        auto* arr = new Person[1000];
        for (int j = 0; j < 1000 ; ++j) {
            arr[j] = Person(j);
        }
        auto List = ListSequence<Person>(arr, 1000);

        CachedList* list = new CachedList(&List);
        std::cout << "List of Persons with ID form 0 to 999 was created" << std::endl;
        std::cout << "Making 500 Get-requests to ID's from 0 to 99..." << std::endl;
        srand(std::time(nullptr));
        for (int k = 0; k < 500 ; ++k) {
            int a = rand()%100;
            list->Get(a);
        }
        std::cout << "List of ID's in cache:" << std::endl;

        for (int l = 0; l <1000 ; ++l) {
            try {
                std::cout << list->cache->Get(l).ToString()  << std::endl;
            } catch (std::logic_error& e){
                continue;
            }
        }

        std::cout << "Making 1000 Get-requests to ID's from 200 to 400" << std::endl;

        for (int k = 0; k < 1000 ; ++k) {
            int a = rand()%200 + 200;
            list->Get(a);

        }

        std::cout << "List of ID's in cache:" << std::endl;

        for (int l = 0; l <1000 ; ++l) {
            try {
                std::cout << list->cache->Get(l).ToString()  << std::endl;
            } catch (std::logic_error& e){
                continue;
            }
        }
        std::cout << "Making 1000 Get-requests to ID's from 500 to 510" << std::endl;

        for (int k = 0; k < 1000 ; ++k) {
            int a = rand()%11 + 500;
            list->Get(a);

        }

        std::cout << "List of ID's in cache:" << std::endl;

        for (int l = 0; l <1000 ; ++l) {
            try {
                std::cout << list->cache->Get(l).ToString()  << std::endl;
            } catch (std::logic_error& e){
                continue;
            }
        }
    }








};


#endif //SEM2LAB2_UI_H
