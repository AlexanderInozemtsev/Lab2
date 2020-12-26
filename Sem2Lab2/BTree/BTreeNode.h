

#ifndef SEM2LAB2_BTREENODE_H
#define SEM2LAB2_BTREENODE_H

#include "../../LAB2/ArraySequence.h"
#include <string>
#define ORDER 2
#define KEYS  2*ORDER - 1
#define CHILDREN 2*ORDER

#include <exception>
#include "../../LAB2/Pair.h"
#include <functional>
#include <iostream>
template <class T>
class BTreeNode {
public:
    ArraySequence<T>* keys;
    ArraySequence<BTreeNode*>* children;
    bool isLeaf;
    int currSize;
    std::function<int(T, T)> compare;

public:
    BTreeNode ( bool _isLeaf, std::function<int(T, T)> cmp){
        compare = cmp;
        this->isLeaf = _isLeaf;
        currSize = 0;
        keys = new ArraySequence<T>(KEYS);
        children = new ArraySequence<BTreeNode*>(CHILDREN);
        for (int i = 0; i < CHILDREN ; ++i) {
            children->Set(i, nullptr);
        }
    }

public:
    T FindElem(T key){
        int index = Find(key,0,this->currSize - 1);
        if (index < this->currSize && this->keys->Get(index) == key)
            return this->keys->Get(index);
        else
        if (this->isLeaf)
            throw  std::logic_error("Key wasn't found in B-Tree");
        return this->children->Get(index)->FindElem(key);
    }
    bool Contains(T key){
        int index = Find(key,0,this->currSize - 1);
        if (index < this->currSize && this->keys->Get(index) == key)
            return true;
        else
            if (this->isLeaf)
                return false;
        return this->children->Get(index)->Contains(key);
    }
    void Split(int k, BTreeNode* child_1, int* newNodes){
        auto child_2 = new BTreeNode<T>(child_1->isLeaf, this->compare);
        ++(*newNodes);
        child_2->currSize = ORDER -1;

        for (int i = 0; i < ORDER -1 ; ++i)
            child_2->keys->Set(i,child_1->keys->Get(i + ORDER));

        if (!child_1->isLeaf){
            for (int j = 0; j < ORDER ; ++j)
                child_2->children->Set(j, child_1->children->Get(j + ORDER));
        }

        child_1->currSize = ORDER -1;

        for (int l = currSize; l >= k + 1 ; --l)
            this->children->Set(l + 1, this->children->Get(l));
        this->children->Set(k+1, child_2);

        for (int m = currSize - 1; m >= k ; --m)
            this->keys->Set(m+1, this->keys->Get(m));
        this->keys->Set(k, child_1->keys->Get(ORDER-1));

        ++this->currSize;
    }

    void IfNotFullInsert(T key, int* newNodes){
        int i = this->currSize - 1;
        if (this->isLeaf) {
            for (i; i >= 0 && compare(this->keys->Get(i), key); --i)
                this->keys->Set(i + 1, this->keys->Get(i));//Если лист(заведомо не полный), то вставляем ключ в последовательность ключей
            this->keys->Set(i+1, key);
            ++currSize;
        }

        if (!this->isLeaf){
            for (i; i>= 0 && compare(this->keys->Get(i), key); --i); //Ищем нужное место
            BTreeNode<T>* childToInsert =  this->children->Get(i+1);
            if ( childToInsert->currSize == KEYS){ //Если узел для вставки полон
                Split(i+1,childToInsert, newNodes); // Разбиваем узел для вставки, увеличивая на 1 размер текущего, заведомо не полного узла

                if (compare(key,this->keys->Get(i+1))) //Уточняем узел для вставки с учетом "поднятого" в текущий узел ключа
                    ++i;
            }
            this->children->Get(i+1)->IfNotFullInsert(key,newNodes);
        }
    }

    void Delete(T key, int* deleteNodes){
        int index = Find(key, 0, this->currSize -1);

        if (index < this->currSize && key == this->keys->Get(index)) {
            if (this->isLeaf)
                DeleteInLeaf(index);
            else
                DeleteInNonLeaf(index,deleteNodes);
        }
        else {
            if (this->isLeaf)
                throw std::logic_error("Element to delete wasn't found in B-Tree");

            int wasRightmost = index == this->currSize;

            if (this->children->Get(index)->currSize <= ORDER - 1)
                AddIfNotEnough(index, deleteNodes);

            int sizeReduced = index > this->currSize;
            if (wasRightmost && sizeReduced)
                this->children->Get(index - 1)->Delete(key,deleteNodes);
            else {
                this->children->Get(index)->Delete(key, deleteNodes);
            }
        }
    }
    int Find(T key, int left, int right ){
        int index = 0;
        while (index < this->currSize && compare(key, this->keys->Get(index)))
            ++index;
        return index;
      /*  int mid;
        while (left <= right){
            mid = (left + right)/2;
            if (left == right){
                if (compare(key,this->keys->Get(mid)))
                    return left + 1;
                else
                    return left;
            } else
            if (compare(key,this->keys->Get(mid)))
                left = mid + 1;
            else
                right = mid - 1;
        }
        */
    }
    void DeleteInLeaf (int index){
        for (int i = index + 1; i < this->currSize ; ++i)
            this->keys->Set(i-1,this->keys->Get(i));
        --this->currSize;
    }
    void DeleteInNonLeaf (int index, int* deleteNodes){
        T curr = this->keys->Get(index);

        if (this->children->Get(index)->currSize >= ORDER){
            T formBottom = LeftSubtreeBiggest(index);
            this->keys->Set(index,formBottom);
            this->children->Get(index)->BTreeNode::Delete(formBottom,deleteNodes);
        }
        else
            if (this->children->Get(index + 1)->currSize >= ORDER){
                T formBottom = RightSubtreeSmallest(index);
                this->keys->Set(index,formBottom);
                this->children->Get(index + 1)->BTreeNode::Delete(formBottom,deleteNodes);
            }
            else{
                Merge(index);
                this->children->Get(index)->Delete(curr,deleteNodes);
            }
    }

    T LeftSubtreeBiggest (int index){
        BTreeNode<T> * curr = this->children->Get(index);
        while (!curr->isLeaf)
            curr = curr->children->Get(curr->currSize);
        return curr->keys->Get((curr->currSize) - 1);
    }
    T RightSubtreeSmallest(int index){
        BTreeNode<T> * curr = this->children->Get(index + 1);
        while (!curr->isLeaf)
            curr = curr->children->Get(0);
        return curr->keys->Get(0);
    }

    void RotateFormLeftNode (int index){
        BTreeNode<T>* child = this->children->Get(index);
        BTreeNode<T>* leftNeighbor = this->children->Get(index - 1);

        for (int i = child->currSize - 1 ; i >= 0 ; --i)
            child->keys->Set(i+1,child->keys->Get(i));

        if (!child->isLeaf){
            for (int j = child->currSize; j >= 0 ; --j)
                child->children->Set(j+1,child->children->Get(j));
        }
        child->keys->Set(0,this->keys->Get(index-1));
        if (!child->isLeaf)
            child->children->Set(0,leftNeighbor->children->Get(leftNeighbor->currSize));

        this->keys->Set(index- 1,leftNeighbor->keys->Get(leftNeighbor->currSize -1));

        ++child->currSize;
        --leftNeighbor->currSize;
    }
    void RotateFromRightNode (int index){
        BTreeNode<T>* child = this->children->Get(index);
        BTreeNode<T>* rightNeighbor = this->children->Get(index+1);

        child->keys->Set(child->currSize,this->keys->Get(index));
        ++child->currSize;

        this->keys->Set(index, rightNeighbor->keys->Get(0));

        if (!child->isLeaf) {
            T leftmost = rightNeighbor->children->Get(0)->keys->Get(0);
            child->children->Set(child->currSize, rightNeighbor->children->Get(0));
            //T p =  child->children->Get(child->currSize+1)->keys->Get(0);
            int a = 5;
        }

        for (int i = 0; i < rightNeighbor->currSize - 1 ; ++i)
            rightNeighbor->keys->Set(i, rightNeighbor->keys->Get(i+1));

        if (!rightNeighbor->isLeaf)
            for (int i = 0; i < rightNeighbor->currSize; ++i)
                rightNeighbor->children->Set(i, rightNeighbor->children->Get(i+1));
        --rightNeighbor->currSize;
    }

    void Merge( int index){
        BTreeNode<T>* child = this->children->Get(index);
        BTreeNode<T>* rightNeighbor = this->children->Get(index+1);

        child->keys->Set(ORDER -1, this->keys->Get(index));

        for (int i = 0; i < rightNeighbor->currSize ; ++i)
            child->keys->Set(ORDER + i, rightNeighbor->keys->Get(i));

        if (!child->isLeaf){
            for (int i = 0; i < rightNeighbor->currSize + 1; ++i)
                child->children->Set(ORDER + i, rightNeighbor->children->Get(i));
        }

        for (int j = index; j < this->currSize - 1; ++j)
            this->keys->Set(j, this->keys->Get(j+1));

        for (int j = index + 1; j < this->currSize; ++j)
            this->children->Set(j, this->children->Get(j+1));

        --this->currSize;
        child->currSize += 1 + rightNeighbor->currSize;
        delete(rightNeighbor);
    }

    void AddIfNotEnough (int index, int* deleteNodes){
        if ( index != 0 && this->children->Get(index-1)->currSize >= ORDER)
            RotateFormLeftNode(index);
        else
            if (index != this->currSize && this->children->Get(index+1)->currSize >= ORDER)
                RotateFromRightNode(index);
            else {
                ++(*deleteNodes);
                if (index != this->currSize)
                    Merge(index);
                else
                    Merge(index - 1);
            }
    }
};


#endif //SEM2LAB2_BTREENODE_H
