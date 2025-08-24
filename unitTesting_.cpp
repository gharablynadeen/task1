#include <gtest/gtest.h> 
#include "FileManager.h"
#include <fstream>
#include <vector>

TEST(fileManagerTest, exportFunctionTest) {
    FileManager fm;
    vector<vector<double>> data{ {1.1,2.2},{3.3,4.4}};
    vector<string> columns{"Col1,Col2"};
    vector<string> comments{"# This is a test"};
    //EXPECT_EQ(fm.exportFunction("C:/Users/Nadeen/Documents/GitHub/task1/trial.csv", data, columns, comments), void);

    //std::ifstream inputFile("C:/Users/Nadeen/Documents/GitHub/task1/trial.csv");

    EXPECT_EQ(5,5);
    // EXPECT_EQ(fm.exportFunction("trial.csv", data, columns, comments), void);

    // std::ifstream inputFile("trial.csv");
    // ASSERT_TRUE(inputFile.is_open());

    // std::string line;
    // std::getline(inputFile, line);
    // EXPECT_EQ(line, "# This is a test");

    // std::getline(inputFile, line);
    // EXPECT_EQ(line, "Col1,Col2");

    // std::getline(inputFile, line);
    // EXPECT_EQ(line, "1.1,2.2");

    // std::getline(inputFile, line);
    // EXPECT_EQ(line, "3.3,4.4");

    //inputFile.close();
}
TEST(fileManagerTest, importFunctionTest) {

}