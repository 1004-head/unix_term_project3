#include "gtest/gtest.h"
#include "textfilewriter.h"
#include "linkedlist.h"
#include "node.h"

#define MAX_TITLE_SIZE 50;

TEST(TestFileWriterTest, WriteTextFile) {
    	char file_name[14] = "20220517.list";
	
	write_file(file_name);
	
	EXPECT_EQ(access(file_name, F_OK), 0);
}

TEST(TestFileReaderTest, ReadTextFile) {
    char file_name[14] = "20220517.list";
    int NUM_OF_MUSIC = 0;
    char** music_titles;
    FILE* file = fopen(file_name, "r");

    fscanf(file, "%d\n", &NUM_OF_MUSIC);
    
    music_titles = (char**)malloc(sizeof(char*) * NUM_OF_MUSIC);

    for (int i=0; i < NUM_OF_MUSIC; i++){
        music_titles[i] = (char*)malloc(sizeof(char) * MAX_TITLE_SIZE);
    }

    for (int i =0; i < NUM_OF_MUSIC; i++) {
        fgets(music_titles[i], MAX_TITLE_SIZE, file);
        music_titles[i][strlen(music_titles[i])-1] = 0;
    }

    fclose(file);

    EXPECT_EQ(NUM_OF_MUSIC, 2);
    EXPECT_STREQ(music_titles[0], "Hello");
    EXPECT_STREQ(music_titles[1], "Enemy");

    GTEST_SKIP() << NUM_OF_MUSIC << " " << music_titles[0] << " " << music_titles[1];
    for (int i =0; i < NUM_OF_MUSIC; i++)
        free(music_titles[i]);
}
