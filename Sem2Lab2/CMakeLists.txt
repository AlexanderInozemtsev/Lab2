cmake_minimum_required(VERSION 3.15)
project(Sem2Lab2)

set(CMAKE_CXX_STANDARD 20)

add_executable(Sem2Lab2 main.cpp BTree/BTree.h BTree/BTreeNode.h Dictionary/IDictionary.h Dictionary/BTreeDictionary.h "CachedList/Person .h" CachedList/CachedList.h Test/BTreeTest.h Test/DictionaryTest.h UI/UI.h)