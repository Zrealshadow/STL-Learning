#include <gtest/gtest.h>
#include "AVLTree.hpp"

// Demonstrate some basic assertions.
TEST(AVLTestUnit, AVLTestCreation) {
    std::vector<int> init_v = {17, 12, 19, 10, 15, 18, 25, 8, 11, 13, 16, 22};
    AVLTree<int> tree = AVLTree<int>(init_v);
    EXPECT_EQ(tree.getHeight(), 3); 
}

TEST(AVLTestUnit, AVLTestfind){
    std::vector<int> init_v = {17, 12, 19, 10, 15, 18, 25, 8, 11, 13, 16, 22};
    std::vector<int> init_notInV = {1,2,3,4,5,6,7};
    AVLTree<int> tree = AVLTree<int>(init_v);
    for(int i = 0; i < init_v.size(); i++){
        AVLTree<int>::TreePointer node = tree.find(init_v.at(i));
        EXPECT_NE(node, nullptr);
        EXPECT_EQ(node->data, init_v.at(i));
    }

    for(int i = 0; i < init_notInV.size(); i++){
        AVLTree<int>::TreePointer node = tree.find(init_notInV.at(i));
        EXPECT_EQ(node, nullptr);
    }

    std::vector<int> path = {17, 19, 25, 22};
    std::vector<int> find_path = tree.findPath(22);
    EXPECT_EQ(path.size(), find_path.size());
    for(int i = 0; i < path.size(); i++){
        EXPECT_EQ(path.at(i), find_path.at(i));
    }
}

TEST(AVLTestUnit, AVLTestTraversal){
    std::vector<int> init_v = {17, 12, 19, 10, 15, 18, 25, 8, 11, 13, 16, 22};
    /*
                    17
               12        19
            10    15   18   25
         8  11  13 16      22

    */
    AVLTree<int> tree = AVLTree<int>(init_v);
    std::vector<int> in_order_v = {17, 12, 10, 8, 11, 15, 13, 16, 19, 18, 25, 22};
    std::vector<int> pre_order_v = {8, 10, 11, 12, 13, 15, 16, 17, 18, 19, 22, 25};
    std::vector<int> pre_order_tree = tree.pre_order_traversal();
    std::vector<int> in_order_tree = tree.in_order_traversal();
    EXPECT_TRUE(in_order_tree == in_order_v);
    EXPECT_TRUE(pre_order_tree == pre_order_v);
}


TEST(AVLTestUnit,AVLTreeInsert_RR_Rotation){
    std::vector<int> init_v = {18, 10, 20, 19, 30};
    AVLTree<int> tree = AVLTree<int>(init_v);
    EXPECT_EQ(tree.getHeight(), 2);
    tree.Insert(33);
    // TEST
    EXPECT_EQ(tree.getRoot()->data, 20);
    std::vector<int> in_order_tree = tree.in_order_traversal();
    std::vector<int> in_order_tree_true = {20, 18, 10, 19, 30, 33};
    EXPECT_EQ(in_order_tree, in_order_tree_true);

    //clear data
    init_v.clear();
    tree.Clear();
    // small tree

    init_v = {18, 20};
    tree.Insert(init_v); 
    tree.Insert(30);  
    in_order_tree = tree.in_order_traversal();
    in_order_tree_true = {20, 18, 30};
    EXPECT_EQ(in_order_tree, in_order_tree_true);
    
}


TEST(AVLTestUnit, AVLTreeInsert_LL_Rotation){
    std::vector<int> init_v = {18, 14, 20, 12, 16};
    AVLTree<int> tree = AVLTree<int>(init_v);
    EXPECT_EQ(tree.getHeight(), 2);
    tree.Insert(11);
    // TEST
    EXPECT_EQ(tree.getRoot()->data, 14);
    std::vector<int> in_order_tree = tree.in_order_traversal();
    std::vector<int> in_order_tree_true = {14, 12, 11, 18, 16, 20};
    EXPECT_EQ(in_order_tree, in_order_tree_true);

    //clear data
    init_v.clear();
    tree.Clear();
    // small tree

    init_v = {18, 14};
    tree.Insert(init_v); 
    tree.Insert(11);  
    in_order_tree = tree.in_order_traversal();
    in_order_tree_true = {14, 11, 18};
    EXPECT_EQ(in_order_tree, in_order_tree_true);
}

TEST(AVLTestUnit, AVLTreeInsert_LR_Rotation){
    std::vector<int> init_v = {18, 10, 20, 19, 30};
    AVLTree<int> tree = AVLTree<int>(init_v);
    EXPECT_EQ(tree.getHeight(), 2);
    tree.Insert(33);
    // TEST
    EXPECT_EQ(tree.getRoot()->data, 20);
    std::vector<int> in_order_tree = tree.in_order_traversal();
    std::vector<int> in_order_tree_true = {20, 18, 10, 19, 30, 33};
    EXPECT_EQ(in_order_tree, in_order_tree_true);


    //clear data
    init_v.clear();
    tree.Clear();
    // small tree

    init_v = {18, 10};
    tree.Insert(init_v); 
    tree.Insert(16);  
    in_order_tree = tree.in_order_traversal();
    in_order_tree_true = {16, 10, 18};
    EXPECT_EQ(in_order_tree, in_order_tree_true);

}

TEST(AVLTestUnit, AVLTreeInsert_RL_Rotation){
     /*
            18
        14          24
                20      27
                    23

            20
         18     24
      14      23    27     
     */
    std::vector<int> init_v = {18, 14, 24, 20, 27};
    AVLTree<int> tree = AVLTree<int>(init_v);
    EXPECT_EQ(tree.getHeight(), 2);
    tree.Insert(23);
    std::vector<int> in_order_tree = tree.in_order_traversal();
    std::vector<int> in_order_tree_true = {20, 18, 14, 24, 23, 27};
    EXPECT_EQ(in_order_tree, in_order_tree_true);

    /* 
        18               23
           24    =>  18       24
         23
    */

   //clear data
    init_v.clear();
    tree.Clear();
    // small tree

    init_v = {18, 24};
    tree.Insert(init_v); 
    tree.Insert(23);  
    in_order_tree = tree.in_order_traversal();
    in_order_tree_true = {23, 18, 24};
    EXPECT_EQ(in_order_tree, in_order_tree_true);
}


TEST(AVLTestUnit, AVLTestInsert) {


}


TEST(AVLTestUnit, AVLTestErase) {


}

TEST(AVLTestUnit, AVLTestErase_LL_Rotation){


}

TEST(AVLTestUnit, AVLTestErase_RR_Rotation){

}

TEST(AVLTestUnit, AVLTestErase_RL_Rotation){

}

TEST(AVLTestUnit, AVLTestErase_LR_Rotation){

}