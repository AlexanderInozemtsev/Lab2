

#ifndef SEM2LAB2_CACHEDLIST_H
#define SEM2LAB2_CACHEDLIST_H

#include "../../LAB2/ListSequence.h"
#include "../../LAB2/ArraySequence.h"
#include "Person .h"
#include "../Dictionary/BTreeDictionary.h"
#include "../../LAB2/Pair.h"
#include <exception>
#include "../../Sem2Lab1/Sorter/InsertionSorter.h"
#include <iostream>
#define CacheSize  100
std::function<int (int,int)> cmp1 = [](int a, int b){return  a> b;};
int cmpPair(Pair<int,int> fst,Pair<int,int> snd){
    return fst._1()>snd._1();
}
class CachedList {
public:
    ListSequence<Person>* seq;
    BTreeDictionary<int,Person>* cache;
    ArraySequence<Pair<int,int>> numberOfUsages;
    InsertionSorter<Pair<int,int>> sorter;
public:
    CachedList(ListSequence<Person>* seq){
        this->seq = seq;
        cache =  new BTreeDictionary<int,Person>(cmp1);
        numberOfUsages  =  ArraySequence<Pair<int,int>>(CacheSize);
        for (int i = 0; i < CacheSize ; ++i)
            numberOfUsages.Set(i, Pair<int,int>(INT_MAX,0));

    }
    int FindToDelete(){
        this->numberOfUsages  = sorter.Sort(&numberOfUsages,cmpPair);
        int id = numberOfUsages.Get(0)._2();
        return id;
    }
    void AddUsage(int id){
        for (int i = 0; i < CacheSize ; ++i) {
            Pair<int,int> curr = numberOfUsages.Get(i);
            if (curr._2() == id)
                numberOfUsages.Set(i, Pair<int,int>(curr._1()+1,id));
        }
    }
    Person Get(int id){
        if (cache->ContainsKey(id)){
            Person result = cache->Get(id); // const&
            AddUsage(id);
            return result;
        } else
            {
            Person result = seq->Get(id);
            if (cache->GetCount() < CacheSize){
                cache->Add(result.id, result);
                numberOfUsages.Set( cache->GetCount()-1, Pair<int,int>(0,result.id));
            }
            else {
                int key = FindToDelete();
                cache->Remove(key);
                cache->Add(result.id,result);
                numberOfUsages.Set(CacheSize - cache->GetCount(), Pair<int,int>(0,result.id));
            }
            return result;
        }
    }
};


#endif //SEM2LAB2_CACHEDLIST_H
