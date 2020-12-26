
#ifndef SEM2LAB2_DICTIONARYTEST_H
#define SEM2LAB2_DICTIONARYTEST_H
#endif //SEM2LAB2_DICTIONARYTEST_H

#include "../Dictionary/BTreeDictionary.h"
#include <cassert>

namespace dictionaryTest {
    std::function<int(int, int)> cmp = [](int a, int b) { return a > b; };

    void Add() {
        auto dic = new BTreeDictionary<int, int>(cmp);
        dic->Add(5, 1);
        dic->Add(10, 2);
        dic->Add(1, 3);
        dic->Add(0, 4);
        assert(dic->count == 4 & dic->items->root->keys->Get(0)._1() == 5);
    }

    void AddExisting() {
        auto dic = new BTreeDictionary<int, int>(cmp);
        dic->Add(5, 1);
        dic->Add(10, 2);
        dic->Add(1, 3);
        dic->Add(0, 4);
        try {
            dic->Add(5, 100);
            assert(false);
        } catch (const std::logic_error &e) {
            assert(true);
        }
    }

    void Contains() {
        auto dic = new BTreeDictionary<int, int>(cmp);
        dic->Add(5, 1);
        dic->Add(10, 2);
        dic->Add(1, 3);
        dic->Add(0, 4);
        assert(dic->ContainsKey(1));
    }

    void NotContains() {
        auto dic = new BTreeDictionary<int, int>(cmp);
        dic->Add(5, 1);
        dic->Add(10, 2);
        dic->Add(1, 3);
        dic->Add(0, 4);
        assert(!dic->ContainsKey(50));
    }

    void Get(){
        auto dic = new BTreeDictionary<int, int>(cmp);
        dic->Add(5, 1);
        dic->Add(10, 2);
        dic->Add(1, 3);
        dic->Add(0, 4);
        assert(dic->Get(5) == 1);
    }

    void GetMissingElem(){
        auto dic = new BTreeDictionary<int, int>(cmp);
        dic->Add(5, 1);
        dic->Add(10, 2);
        dic->Add(1, 3);
        dic->Add(0, 4);
        try {
            dic->Get(100);
            assert(false);
        } catch (const std::logic_error& e){
            assert(true);
        }

    }

    void Remove(){
        auto dic = new BTreeDictionary<int, int>(cmp);
        dic->Add(5, 1);
        dic->Add(10, 2);
        dic->Add(1, 3);
        dic->Add(0, 4);
        dic->Remove(5);
        assert(dic->count == 3 & dic->items->root->keys->Get(0)._1() == 1);
    }
}