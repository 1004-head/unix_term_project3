#include "gtest/gtest.h"
#include "linkedlist.h"
#include "node.h"
#include "textfilewriter.h"

// class LinkedListEnvironment : public ::testing::Environment {
//  public:
//   ~LinkedListEnvironment() override {}

//   // Override this to define how to set up the environment.
//   void SetUp() override {
//         printf("SetUp!");
//         int NUM_OF_MUSIC = 3;
//         music_titles = (char**)malloc(sizeof(char*) * NUM_OF_MUSIC);
//         for (int i=0; i < NUM_OF_MUSIC; i++){
//             music_titles[i] = (char*)malloc(sizeof(char) * MAX_TITLE_SIZE);
//         }
//         music_titles[0] = (char*)"Hello"; 
//         music_titles[1] = (char*)"Enemy"; 
//         music_titles[2] = (char*)"abc";
//   }

//   // Override this to define how to tear down the environment.
//   void TearDown() override {
//         printf("TearDown!");
//         clear();
//         music_titles = nullptr;
//   }
//   char** music_titles = nullptr;
// };


class TestLinkedList : public ::testing::Test {
protected:
    TestLinkedList() = default;
    ~TestLinkedList() = default;
    virtual void SetUp() override {
        printf("SetUp!");
        int NUM_OF_MUSIC = 3;
        music_titles = (char**)malloc(sizeof(char*) * NUM_OF_MUSIC);
        for (int i=0; i < NUM_OF_MUSIC; i++){
            music_titles[i] = (char*)malloc(sizeof(char) * MAX_TITLE_SIZE);
        }
        music_titles[0] = (char*)"Hello"; 
        music_titles[1] = (char*)"Enemy"; 
        music_titles[2] = (char*)"abc";
    }

    virtual void TearDown() override {
        printf("TearDown!");
        clear();
        music_titles = nullptr;
    }

    char** music_titles = nullptr;

};


TEST(TestLinkedList, Empty) {
    Node* node = first_node();
    EXPECT_EQ(node, nullptr);
    EXPECT_EQ(empty(), true);
}

TEST(TestLinkedList, EmptySize) {
    size_t s = size();
    EXPECT_EQ(s, 0u);
}

TEST(TestLinkedList, InsertOne) {
    char* music_title = (char*)malloc(sizeof(char) * MAX_TITLE_SIZE);
    append(1, music_title);
    EXPECT_EQ(size(), 1u);
    clear();
}

TEST(TestLinkedList, RemoveOne) {
    remove(nullptr);
    char* music_title = (char*)malloc(sizeof(char) * MAX_TITLE_SIZE);
    append(1, music_title);
    delete_by_data(music_title);
    EXPECT_EQ(size(), 0u);
    EXPECT_EQ(first_node(), nullptr);
    clear();
}

TEST(TestLinkedList, InsertAndRemoveTitles) {
    int NUM_OF_MUSIC = 3;
    char** music_titles = NULL;
    music_titles = (char**)malloc(sizeof(char*) * NUM_OF_MUSIC);
    for (int i=0; i < NUM_OF_MUSIC; i++){
        music_titles[i] = (char*)malloc(sizeof(char) * MAX_TITLE_SIZE);
    }
    music_titles[0] = (char*)"Hello"; 
    music_titles[1] = (char*)"Enemy"; 
    music_titles[2] = (char*)"abc";
    append(sizeof(music_titles[0]), music_titles[0]);
    append(sizeof(music_titles[1]), music_titles[1]);
    append(sizeof(music_titles[2]), music_titles[2]);
    EXPECT_EQ(size(), 3u);
    EXPECT_EQ(empty(), false);
    delete_by_data(music_titles[0]);
    EXPECT_EQ(size(), 2u);
    EXPECT_EQ(empty(), false);
    delete_by_data(music_titles[1]);
    EXPECT_EQ(size(), 1u);
    EXPECT_EQ(empty(), false);
    delete_by_data(music_titles[2]);
    EXPECT_EQ(size(), 0u);
    EXPECT_EQ(empty(), true);    
    clear();
}

TEST(TestLinkedList, Append) {
    int NUM_OF_MUSIC = 3;
    char** music_titles = NULL;
    music_titles = (char**)malloc(sizeof(char*) * NUM_OF_MUSIC);
    for (int i=0; i < NUM_OF_MUSIC; i++){
        music_titles[i] = (char*)malloc(sizeof(char) * MAX_TITLE_SIZE);
    }
    music_titles[0] = (char*)"Hello"; 
    music_titles[1] = (char*)"Enemy"; 
    music_titles[2] = (char*)"abc";
    append(sizeof(music_titles[0]), music_titles[0]);
    append(sizeof(music_titles[1]), music_titles[1]);
    append(sizeof(music_titles[2]), music_titles[2]);
    EXPECT_STREQ(first_node()->data, music_titles[0]);
    EXPECT_STREQ(last_node()->data, music_titles[2]); 
    clear();
}

TEST(TestLinkedList, AppendLeft) {
    int NUM_OF_MUSIC = 3;
    char** music_titles = NULL;
    music_titles = (char**)malloc(sizeof(char*) * NUM_OF_MUSIC);
    for (int i=0; i < NUM_OF_MUSIC; i++){
        music_titles[i] = (char*)malloc(sizeof(char) * MAX_TITLE_SIZE);
    }
    music_titles[0] = (char*)"Hello"; 
    music_titles[1] = (char*)"Enemy"; 
    music_titles[2] = (char*)"abc";
    append_left(sizeof(music_titles[0]), music_titles[0]);
    append_left(sizeof(music_titles[1]), music_titles[1]);
    append_left(sizeof(music_titles[2]), music_titles[2]);
    EXPECT_STREQ(first_node()->data, music_titles[2]);
    EXPECT_STREQ(last_node()->data, music_titles[0]); 
    clear();
}

TEST(TestLinkedList, NextAndPrev) {
    // int NUM_OF_MUSIC = 3;
    // char** music_titles = NULL;
    // music_titles = (char**)malloc(sizeof(char*) * NUM_OF_MUSIC);
    // for (int i=0; i < NUM_OF_MUSIC; i++){
    //     music_titles[i] = (char*)malloc(sizeof(char) * MAX_TITLE_SIZE);
    // }
    // music_titles[0] = (char*)"Hello"; 
    // music_titles[1] = (char*)"Enemy"; 
    // music_titles[2] = (char*)"abc";
    append_left(sizeof(music_titles[0]), music_titles[0]);
    Node* cur_node = append_left(sizeof(music_titles[1]), music_titles[1]);
    EXPECT_STREQ(cur_node->data, music_titles[1]);
    EXPECT_STREQ(next()->data, music_titles[0]);
    cur_node = append(sizeof(music_titles[2]), music_titles[2]);
    EXPECT_STREQ(cur_node->data, music_titles[2]);
    EXPECT_STREQ(prev()->data, music_titles[0]);
    clear();
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    //::testing::AddGlobalTestEnvironment(new LinkedListEnvironment);
    return RUN_ALL_TESTS();
}