#pragma once
#include "pch.h"

#define MEMDATA_TESTS
//#define VECTOR_TESTS

#ifdef MEMDATA_TESTS
#include "memdata.h"

TEST(FunctionsForMemData, calculate_capacity) {
    ADD_FAILURE();
}

TEST(ClassMemData, can_create_with_default_constructor) {
    ADD_FAILURE();
}

TEST(ClassMemData, can_create_with_constructor_by_size) {
    ADD_FAILURE();
}

TEST(ClassMemData, can_create_with_constructor_by_initializer_list) {
    ADD_FAILURE();
}

TEST(ClassMemData, can_create_with_init_constructor) {
    ADD_FAILURE();
}

TEST(ClassMemData, can_create_with_copy_constructor) {
    ADD_FAILURE();
}

TEST(ClassMemData, can_create_with_move_constructor) {
    ADD_FAILURE();
}

TEST(ClassMemData, can_is_empty) {
    ADD_FAILURE();
}

TEST(ClassMemData, can_is_full) {
    ADD_FAILURE();
}

TEST(ClassMemData, can_set_memory_for_empty) {
    ADD_FAILURE();
}

TEST(ClassMemData, can_set_memory_for_not_empty) {
    ADD_FAILURE();
}

TEST(ClassMemData, can_set_memory_without_reallocation) {
    ADD_FAILURE();
}

TEST(ClassMemData, can_reset_memory_for_empty) {
    ADD_FAILURE();
}

TEST(ClassMemData, can_reset_memory_for_not_empty_increase) {
    ADD_FAILURE();
}

TEST(ClassMemData, can_reset_memory_for_not_empty_decrease) {
    ADD_FAILURE();
}

TEST(ClassMemData, can_reset_memory_without_reallocation) {
    ADD_FAILURE();
}

TEST(ClassMemData, can_reset_memory_with_shift) {
    ADD_FAILURE();
}

TEST(ClassMemData, can_clear_memory_for_empty) {
    ADD_FAILURE();
}

TEST(ClassMemData, can_clear_memory_for_not_empty) {
    ADD_FAILURE();
}

TEST(ClassMemData, can_assigment) {
    ADD_FAILURE();
}

TEST(ClassMemData, can_move_assigment) {
    ADD_FAILURE();
}

#endif

#ifdef VECTOR_TESTS
#include "vector.h"

TEST(ClassVector, can_create_with_default_constructor) {
    ADD_FAILURE();
}

TEST(ClassVector, can_create_with_constructor_by_size) {
    ADD_FAILURE();
}

TEST(ClassVector, can_create_with_constructor_by_initializer_list) {
    ADD_FAILURE();
}

TEST(ClassVector, can_create_with_init_constructor) {
    ADD_FAILURE();
}

TEST(ClassVector, can_create_with_copy_constructor) {
    ADD_FAILURE();
}

TEST(ClassVector, can_create_with_move_constructor) {
    ADD_FAILURE();
}

TEST(ClassVector, can_is_empty) {
    ADD_FAILURE();
}

TEST(ClassVector, can_is_full) {
    ADD_FAILURE();
}

TEST(ClassVector, can_get_front) {
    ADD_FAILURE();
}

TEST(ClassVector, can_get_back) {
    ADD_FAILURE();
}

TEST(ClassVector, can_set_front) {
    ADD_FAILURE();
}

TEST(ClassVector, can_set_back) {
    ADD_FAILURE();
}

TEST(ClassVector, throw_when_try_get_front_in_empty_vector) {
    ADD_FAILURE();
}

TEST(ClassVector, throw_when_try_get_back_in_empty_vector) {
    ADD_FAILURE();
}

TEST(ClassVector, throw_when_try_set_front_in_empty_vector) {
    ADD_FAILURE();
}

TEST(ClassVector, throw_when_try_set_back_in_empty_vector) {
    ADD_FAILURE();
}

TEST(ClassVector, can_output_with_operator_cout) {
    Vector vec({ 1, 2, 3, 4, 5, 6, 7, 8, 9 });
    std::stringstream out;
    out << vec;
    EXPECT_EQ("{ 1, 2, 3, 4, 5, 6, 7, 8, 9 }", out.str());
}

TEST(ClassVector, can_input_with_operator_cin) {
    Vector vec({ 1, 2, 3, 4, 5, 6, 7, 8, 9 });
    std::stringstream in("9 1 2 3 4 5 6 7 8 9");
    in >> vec;

    EXPECT_EQ(9, vec.size());
    EXPECT_EQ(15, vec.capacity());

    for (size_t i = 0; i < vec.size(); i++) {
        EXPECT_DOUBLE_EQ(vec[i], i + 1);
    }
}

TEST(ClassVector, can_push_front) {
    ADD_FAILURE();
}

TEST(ClassVector, can_push_front_in_empty_vector) {
    ADD_FAILURE();
}

TEST(ClassVector, can_push_front_with_reallocation) {
    ADD_FAILURE();
}

TEST(ClassVector, can_push_back) {
    ADD_FAILURE();
}

TEST(ClassVector, can_push_back_in_empty_vector) {
    ADD_FAILURE();
}

TEST(ClassVector, can_push_back_with_reallocation) {
    ADD_FAILURE();
}

TEST(ClassVector, can_insert) {
    ADD_FAILURE();
}

TEST(ClassVector, can_insert_with_reallocation) {
    ADD_FAILURE();
}

TEST(ClassVector, can_insert_to_front) {
    ADD_FAILURE();
}

TEST(ClassVector, throw_when_try_insert_with_wrong_position) {
    ADD_FAILURE();
}

TEST(ClassVector, can_pop_front) {
    ADD_FAILURE();
}

TEST(ClassVector, can_pop_front_with_reallocation) {
    ADD_FAILURE();
}

TEST(ClassVector, throw_when_try_pop_front_from_empty_vector) {
    ADD_FAILURE();
}

TEST(ClassVector, can_pop_back) {
    ADD_FAILURE();
}

TEST(ClassVector, can_pop_back_with_reallocation) {
    ADD_FAILURE();
}

TEST(ClassVector, throw_when_try_pop_back_from_empty_vector) {
    ADD_FAILURE();
}

TEST(ClassVector, can_correctly_recalc_back_in_area_of_zero) {
    Vector vec;

    for (size_t i = 0; i < 15; i++) {
        vec.push_back(i + 1);
    }

    vec.pop_front();
    vec.push_back(16);

    EXPECT_EQ(15, vec.size());
    EXPECT_EQ(15, vec.capacity());
    EXPECT_DOUBLE_EQ(16.0, vec.back());

    for (size_t i = 0; i < vec.size(); i++) {
        EXPECT_DOUBLE_EQ(vec[i], i + 2);
    }

    vec.pop_back();

    EXPECT_EQ(14, vec.size());
    EXPECT_EQ(15, vec.capacity());
    EXPECT_DOUBLE_EQ(15.0, vec.back());

    for (size_t i = 0; i < vec.size(); i++) {
        EXPECT_DOUBLE_EQ(vec[i], i + 2);
    }
}

TEST(ClassVector, can_correctly_recalc_front_in_area_of_zero) {
    ADD_FAILURE();
}

TEST(ClassVector, can_erase) {
    ADD_FAILURE();
}

TEST(ClassVector, can_erase_front) {
    ADD_FAILURE();
}

TEST(ClassVector, can_erase_back) {
    ADD_FAILURE();
}

TEST(ClassVector, can_erase_with_reallocation) {
    ADD_FAILURE();
}

TEST(ClassVector, throw_when_try_erase_from_empty_vector) {
    ADD_FAILURE();
}

TEST(ClassVector, throw_when_try_erase_with_wrong_position) {
    ADD_FAILURE();
}

TEST(ClassVector, combination_push_pop_insert_erase) {
    Vector vec({ 3, 44, 5, 7, 8 });

    std::stringstream out;
    out << vec;
    EXPECT_EQ("{ 3, 44, 5, 7, 8 }", out.str());
    out.str("");

    vec.pop_front();
    out << vec;
    EXPECT_EQ("{ 44, 5, 7, 8 }", out.str());
    out.str("");

    for (size_t i = 0; i < 4; i++) {
        vec.push_front(3 - i);
    }
    out << vec;
    EXPECT_EQ("{ 0, 1, 2, 3, 44, 5, 7, 8 }", out.str());
    out.str("");

    vec.pop_back();
    out << vec;
    EXPECT_EQ("{ 0, 1, 2, 3, 44, 5, 7 }", out.str());
    out.str("");

    for (size_t i = 0; i < 4; i++) {
        vec.push_back(8 + i);
    }
    out << vec;
    EXPECT_EQ("{ 0, 1, 2, 3, 44, 5, 7, 8, 9, 10, 11 }", out.str());
    out.str("");

    vec.erase(0);
    out << vec;
    EXPECT_EQ("{ 1, 2, 3, 44, 5, 7, 8, 9, 10, 11 }", out.str());
    out.str("");

    vec.erase(3);
    out << vec;
    EXPECT_EQ("{ 1, 2, 3, 5, 7, 8, 9, 10, 11 }", out.str());
    out.str("");

    vec.insert(6, 4);
    out << vec;
    EXPECT_EQ("{ 1, 2, 3, 5, 6, 7, 8, 9, 10, 11 }", out.str());
    out.str("");

    for (size_t i = 0; i < 5; i++) {
        vec.push_back(12 + i);
    }
    out << vec;
    EXPECT_EQ("{ 1, 2, 3, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16 }", out.str());
    out.str("");

    vec.insert(4, 3);
    out << vec;
    EXPECT_EQ("{ 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16 }", out.str());
    out.str("");

    EXPECT_EQ(16, vec.size());
    EXPECT_EQ(30, vec.capacity());

    for (size_t i = 0; i < vec.size(); i++) {
        EXPECT_DOUBLE_EQ(vec[i], i + 1);
    }
}

TEST(ClassVector, can_assigment) {
    ADD_FAILURE();
}

TEST(ClassVector, can_move_assigment) {
    Vector vec_1;
    Vector vec_2;

    for (size_t i = 0; i < 4; i++) {
        vec_1.push_back(5 + i);
    }

    for (size_t i = 0; i < 4; i++) {
        vec_1.push_front(4 - i);
    }

    vec_2 = std::move(vec_1);

    EXPECT_EQ(0, vec_1.size());
    EXPECT_EQ(0, vec_1.capacity());

    EXPECT_EQ(8, vec_2.size());
    EXPECT_EQ(15, vec_2.capacity());

    for (size_t i = 0; i < vec_2.size(); i++) {
        EXPECT_EQ(vec_2[i], i + 1);
    }
}

#endif
