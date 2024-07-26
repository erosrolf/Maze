#include "../src/core/cave.h"

#include <gtest/gtest.h>

TEST(Cave, tests_cave_metod_initFromFile) {
  s21::Cave cave;
  bool return_res = cave.initFromFile("../src/resources/cave01");
  ASSERT_EQ(return_res, true);
  ASSERT_EQ(cave.getRows(), 4);
  ASSERT_EQ(cave.getCols(), 4);
}

TEST(Cave, tests_cave_init_from_file_incorrect_file) {
  s21::Cave cave;
  bool return_res = cave.initFromFile("../src/resources/no_such_file");
  ASSERT_EQ(return_res, false);
  ASSERT_EQ(cave.getRows(), 0);
  ASSERT_EQ(cave.getCols(), 0);
}

TEST(Cave, tests_cave_init_from_file_incorrect_in_file) {
  s21::Cave cave;
  bool return_res = cave.initFromFile("../src/resources/cave04_incorrect");
  ASSERT_EQ(return_res, false);
}

TEST(Cave, tests_cave_metod_numberOfNeighbors_01) {
  s21::Cave cave(1, 1);
  ASSERT_EQ(cave.numberOfNeighbors(0, 0, cave.getData()), 8);
}

TEST(Cave, tests_cave_metod_numberOfNeighbors_02) {
  s21::Cave cave(3, 3);
  ASSERT_EQ(cave.numberOfNeighbors(1, 1, cave.getData()), 0);
}

TEST(Cave, tests_cave_generate_cave_kMutation) {
  s21::Cave cave;
  bool return_res = cave.initFromFile("../src/resources/cave02");
  s21::Cave::GenerationResult res = cave.stepOfGeneration(0, 1);
  ASSERT_EQ(res, s21::Cave::GenerationResult::kMutation);
  ASSERT_EQ(return_res, true);
  ASSERT_EQ(cave.getRows(), 4);
  ASSERT_EQ(cave.getCols(), 4);
}

TEST(Cave, tests_cave_generate_cave_kInvalidParams_1) {
  s21::Cave cave;
  bool return_res = cave.initFromFile("../src/resources/cave02");
  s21::Cave::GenerationResult res = cave.stepOfGeneration(0, 8);
  ASSERT_EQ(res, s21::Cave::GenerationResult::kInvalidParams);
  ASSERT_EQ(return_res, true);
  ASSERT_EQ(cave.getRows(), 4);
  ASSERT_EQ(cave.getCols(), 4);
}

TEST(Cave, tests_cave_generate_cave_kInvalidParams_2) {
  s21::Cave cave;
  bool return_res = cave.initFromFile("../src/resources/cave02");
  s21::Cave::GenerationResult res = cave.stepOfGeneration(-1, 7);
  ASSERT_EQ(res, s21::Cave::GenerationResult::kInvalidParams);
  ASSERT_EQ(return_res, true);
  ASSERT_EQ(cave.getRows(), 4);
  ASSERT_EQ(cave.getCols(), 4);
}

TEST(Cave, tests_cave_generate_cave_many) {
  s21::Cave cave;
  bool return_res = cave.initFromFile("../src/resources/cave03");
  s21::Cave::GenerationResult res = cave.stepOfGeneration(0, 1);
  ASSERT_EQ(res, s21::Cave::GenerationResult::kMutation);
  ASSERT_EQ(return_res, true);
  ASSERT_EQ(cave.getRows(), 4);
  ASSERT_EQ(cave.getCols(), 4);
}
