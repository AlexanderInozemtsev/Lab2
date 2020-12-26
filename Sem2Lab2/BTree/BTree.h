

#ifndef SEM2LAB2_BTREE_H
#define SEM2LAB2_BTREE_H

#include <functional>
#include "../../LAB2/Pair.h"
#include "../../LAB2/ArraySequence.h"
#include "BTreeNode.h"
#include <string>
#include <exception>
template <class T>
class BTree{
public:
    BTreeNode<T>* root;
    std::function<int (T,T)> compare;
    int size;
public:
    BTree (){
        root = nullptr;
    }
    BTree (std::function<int(T,T)> cmp){
        root = nullptr;
        compare = cmp;
        size = 0;
    }


    std::string Traverse(){
        if (this->root == nullptr)
            return "Empty tree";
        return this->Traverse_Help(this->root) + "\n";
    }
    std::string Traverse_Help(BTreeNode<T>* currNode){
        std::string result;
        result +="{";
        for (int i = 0; i < currNode->currSize ; ++i)
            result += std::to_string(currNode->keys->Get(i)) += " ";
        result += "}";
        if (!currNode->isLeaf) {
            result += "(";
            for (int j = 0; j < currNode->currSize + 1; ++j) {
                result += Traverse_Help(currNode->children->Get(j));
            }
            result += ")";
        }
        return result;
    }

    int Insert(T key){
        ++size;
        int newNodes = 0;
        if (root == nullptr) { //Если дерево пусто
            root = new BTreeNode<T>(true,compare);
            root->keys->Set(0,key);
            root->currSize = 1;
            ++newNodes;
        }

        else{
            if (root->currSize == KEYS){ //Если корень полон
                auto newRoot = new BTreeNode<T>(false, compare);
                ++newNodes;
                newRoot->children->Set(0,this->root);
                newRoot->Split(0,this->root,&newNodes);
                //Уточняем позицию для вставки с учетом однго "поднятого" из старого корня ключа
                newRoot->children->Get(compare(key,newRoot->keys->Get(0)) ? 1 : 0)->IfNotFullInsert(key,&newNodes);
                this->root = newRoot;
            }
            else
                root->IfNotFullInsert(key, &newNodes);
        }
        return newNodes;
    }

    int Delete(T key){
        int deleteNodes = 0;
        if (!root)
            throw std::logic_error("Deletion from empty B-Tree");
        try {
            root->Delete(key, &deleteNodes);
            --size;
        } catch (const std::logic_error& e){
            throw e;
        }

        if (root->currSize == 0){
            BTreeNode<T>* tmp = root;
            if (root->isLeaf)
                root = nullptr;
            else
                root = root->children->Get(0);
            delete(tmp);
            ++deleteNodes;
        }
        return deleteNodes;
    }

    bool Contains(T key){
        if (!root)
            return false;
        else {
            bool a = this->root->Contains(key);
            return a;
        }
    }
    T FindElem (T key) {
        if(!root){
            throw std::logic_error("Key wasn't found in B-Tree");
            }
        else {
            return this->root->FindElem(key);
        }
    }
};


#endif //SEM2LAB2_BTREE_H
