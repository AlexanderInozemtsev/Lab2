

#include <functional>
#include "../BTree/BTree.h"
#include <cassert>
#include <exception>
#ifndef SEM2LAB2_BTREETEST_H
#define SEM2LAB2_BTREETEST_H


namespace btreeTest {
    std::function<int(int, int)> cmp = [](int a, int b) { return a > b; };

    void GetFromEmpty() {
        auto Btree = new BTree<int>(cmp);
        try {
            Btree->FindElem(0);
            assert(false);
        } catch (const std::logic_error &e) {
            assert(true);
        }
    }

    void DeleteInEmpty() {
        auto Btree = new BTree<int>(cmp);
        try {
            Btree->Delete(0);
            assert(false);
        } catch (const std::logic_error &e) {
            assert(true);
        }
    }

    void Insert() {
        auto Btree = new BTree<int>(cmp);
        Btree->Insert(5);
        Btree->Insert(10);
        Btree->Insert(1);
        Btree->Insert(0);
        assert(Btree->size == 4 & Btree->root->keys->Get(0) == 5);
    }

    void DeleteFromNonLeaf() {
        auto Btree = new BTree<int>(cmp);
        Btree->Insert(5);
        Btree->Insert(10);
        Btree->Insert(1);
        Btree->Insert(0);
        Btree->Delete(5);
        assert(Btree->size == 3 & Btree->root->keys->Get(0) == 1);
    }

    void DeleteFromLeaf() {
        auto Btree = new BTree<int>(cmp);
        Btree->Insert(5);
        Btree->Insert(10);
        Btree->Insert(1);
        Btree->Insert(0);
        Btree->Delete(10);
        assert(Btree->size == 3 & Btree->root->keys->Get(0) == 1);
    }

    void Contains() {
        auto Btree = new BTree<int>(cmp);
        Btree->Insert(5);
        Btree->Insert(10);
        Btree->Insert(1);
        Btree->Insert(0);
        assert(Btree->Contains(1));
    }

    void NotContains() {
        auto Btree = new BTree<int>(cmp);
        Btree->Insert(5);
        Btree->Insert(10);
        Btree->Insert(1);
        Btree->Insert(0);
        assert(!Btree->Contains(50));
    }

    void FindMissingElement() {
        auto Btree = new BTree<int>(cmp);
        Btree->Insert(5);
        Btree->Insert(10);
        Btree->Insert(1);
        Btree->Insert(0);
        try {
            Btree->FindElem(50);
            assert(false);
        } catch (const std::logic_error &e) {
            assert(true);
        }
    }
}
#endif //SEM2LAB2_BTREETEST_H
