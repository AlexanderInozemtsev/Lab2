
#ifndef SEM2LAB2_BTREEDICTIONARY_H
#define SEM2LAB2_BTREEDICTIONARY_H


#include "IDictionary.h"
#include "../BTree/BTree.h"
#include "../../LAB2/Pair.h"
#include <functional>
#include <string>
#include "../BTree/BTreeNode.h"
#include <stack>
#include <exception>
template <class Key,class T>
class BTreeDictionary: IDictionary<Key,T>{
public:
    BTree<Pair<Key,T>>* items;
    int count;
    int size;
    std::function<int(Key, Key)> cmpKeys;

    std::function<int (Pair<Key,T>,Pair<Key,T>)> cmpPair = [this](Pair<Key,T> fst,Pair<Key,T> snd){
        return cmpKeys(fst._1(),snd._1());
    };
  //  int (*cmpPair(Pair<Key,T> fst, Pair<Key,T> snd))(Pair<Key,T>, Pair<Key,T>){
   //     return (*cmpKeys)(fst._1(),snd._1());
   // }




public:
    BTreeDictionary(std::function<int(Key, Key)> cmpKeys){
        this->cmpKeys = cmpKeys;
        items = new BTree<Pair<Key,T>>(cmpPair);
        count = 0;
        size = 0;
    }

public:
    std::string ToString(){
        return ToStringHelp(this->items->root);
    }
    std::string ToStringHelp(BTreeNode<Pair<Key,T>>* node){
        std::string result = "";

            if (node->isLeaf){
                for (int j = 0; j < node->currSize ; ++j) {
                    result += node->keys->Get(j).ToString() + '\n';
                }
            } else {
                for (int i = 0; i < node->currSize  ; ++i) {
                    result += ToStringHelp(node->children->Get(i));
                    result += node->keys->Get(i).ToString() + '\n';
                }
                result += ToStringHelp(node->children->Get(node->currSize));
            }
        return result;
    }
    void Add(Key key, T value){
        if (this->ContainsKey(key))
            throw std::logic_error(" Key was already inserted in Map");
        size += items->Insert(Pair<Key,T>(key,value));
        ++count;
    }
    virtual int GetCount(){
        return this->count;
    }
    virtual int GetCapacity(){
        return this->size * KEYS;
    }
    virtual T Get(Key key){
        T a = T();
        auto toGet = Pair<Key,T>(key,a);
        try{
            return this->items->FindElem(toGet)._2();
        } catch (const std::logic_error& e){
            throw std::logic_error("Key wasn't found in Map");
        }
    }
    virtual bool ContainsKey(Key key){
        T a = T();
        auto toFind = Pair<Key,T>(key,a);
        bool b = this->items->Contains(toFind);
        return b;
    }
    virtual void Remove(Key key){
        try {
            size -= items->Delete(Pair<Key, T>(key, T()));
        } catch (const std::logic_error& e){
            throw std::logic_error("Key wasn't found in Map");
        }
        --count;
    }
};
#endif //SEM2LAB2_BTREEDICTIONARY_H
