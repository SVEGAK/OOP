#pragma once
#include "pch.h"
#define MEMDATA_TESTS
//#define VECTOR_TESTS

#ifdef MEMDATA_TESTS
#include "memdata.h"



TEST(FunctionsForMemData, calculate_capacity) {
    EXPECT_EQ(calculate_capacity(10), 25);
    EXPECT_EQ(calculate_capacity(0), 0);
}

TEST(ClassMemData, can_create_with_default_constructor) {
    MemData md;
    EXPECT_EQ(md.size(), 0);
}

TEST(ClassMemData, can_create_with_constructor_by_size) {
    MemData md(5);
    EXPECT_EQ(md.size(), 5);
    EXPECT_EQ(md.capacity(), 20);
}

TEST(ClassMemData, can_create_with_constructor_by_initializer_list) {
    MemData md = { 1.0, 3.4, 1.1 };
    EXPECT_EQ(md.size(), 3);
    EXPECT_EQ(md.capacity(), 18);
    EXPECT_DOUBLE_EQ(md.data()[1], 3.4);
}

TEST(ClassMemData, can_create_with_init_constructor) {
    double a[] = { 3.5, 11, 2.2 };
    MemData md(a, 3);
    EXPECT_EQ(md.size(), 3);
    EXPECT_EQ(md.capacity(), 18);
    EXPECT_DOUBLE_EQ(md.data()[1], 11.0);
}

TEST(ClassMemData, can_create_with_copy_constructor) {
    MemData md1 = { 1.0, 3.4, 1.1 };
    MemData md2(md1);
    EXPECT_EQ(md1.data()[1], md2.data()[1]);
    EXPECT_EQ(md2.size(), 3);
}

TEST(ClassMemData, can_create_with_move_constructor) {
    MemData md1 = { 1.0, 3.4, 1.1 };
    MemData md2(std::move(md1));

    EXPECT_EQ(md1.data(), nullptr);
    EXPECT_DOUBLE_EQ(md2.data()[0], 1.0);
    EXPECT_DOUBLE_EQ(md2.data()[1], 3.4);
    EXPECT_DOUBLE_EQ(md2.data()[2], 1.1);
    EXPECT_EQ(md2.size(), 3);
    EXPECT_EQ(md2.capacity(), 18);

    EXPECT_TRUE(md1.is_empty());
}

TEST(ClassMemData, can_is_empty) {
    MemData md;
    EXPECT_TRUE(md.is_empty());
}

TEST(ClassMemData, can_is_full) {
    MemData md1;
    EXPECT_TRUE(md1.is_full());

    MemData md2 = { 1.0, 2.0, 3.0 };
    md2.clear_memory();
    EXPECT_EQ(md2.size(), 3);
    EXPECT_EQ(md2.capacity(), 3+MEM_STEP);
    EXPECT_FALSE(md2.is_full());
}

TEST(ClassMemData, can_set_memory_for_empty) {
    MemData md1;
    EXPECT_NO_THROW(md1.set_memory(md1.size()));
    EXPECT_NE(md1.data(), nullptr);
}

TEST(ClassMemData, can_set_memory_for_not_empty) {
    MemData md1(5);
    EXPECT_NO_THROW(md1.set_memory(md1.size()));
    EXPECT_NE(md1.data(), nullptr);
}

TEST(ClassMemData, can_set_memory_without_reallocation) {
    MemData md1 = { 1.0, 2.0, 3.0 };
    EXPECT_NO_THROW(md1.set_memory(md1.size()));
    EXPECT_NE(md1.data(), nullptr);
}

TEST(ClassMemData, can_reset_memory_for_empty) {
    MemData md;

    md.reset_memory(10,0);

    EXPECT_EQ(md.capacity(), 25);
    EXPECT_NE(md.data(), nullptr);
}

TEST(ClassMemData, can_reset_memory_for_not_empty_increase) {
    MemData md = { 1.0, 2.0, 3.0 };
    const double* old_data = md.data();

    md.reset_memory(10);

    EXPECT_EQ(md.capacity(), 25);
    EXPECT_EQ(md.size(), 10);
    EXPECT_NE(md.data(), old_data);
    EXPECT_DOUBLE_EQ(md.data()[0], 1.0);
    EXPECT_DOUBLE_EQ(md.data()[1], 2.0);
    EXPECT_DOUBLE_EQ(md.data()[2], 3.0);
}

TEST(ClassMemData, can_reset_memory_for_not_empty_decrease) {
    MemData md = { 1.0, 2.0, 3.0, 4.0, 5.0 };
    const double* old_data = md.data();

    md.reset_memory(3);

    EXPECT_EQ(md.capacity(), 18);
    EXPECT_EQ(md.size(), 3);
    EXPECT_NE(md.data(), old_data);
    EXPECT_DOUBLE_EQ(md.data()[0], 1.0);
    EXPECT_DOUBLE_EQ(md.data()[1], 2.0);
    EXPECT_DOUBLE_EQ(md.data()[2], 3.0);
}

TEST(ClassMemData, can_reset_memory_without_reallocation) {
    MemData md = { 1.0, 2.0, 3.0 };
    const double* old_data = md.data();
    size_t old_capacity = md.capacity();

    md.reset_memory(old_capacity);

    EXPECT_EQ(md.capacity(), old_capacity+MEM_STEP);
    EXPECT_NE(md.data(), old_data);
    EXPECT_DOUBLE_EQ(md.data()[0], 1.0);
    EXPECT_DOUBLE_EQ(md.data()[1], 2.0);
    EXPECT_DOUBLE_EQ(md.data()[2], 3.0);
}

TEST(ClassMemData, can_reset_memory_with_shift) {
    MemData md = { 1.0, 2.0, 3.0, 4.0, 5.0 };
    const double* old_data = md.data();

    md.reset_memory(5, 2);  // start_index = 2

    EXPECT_EQ(md.capacity(), 5+MEM_STEP);
    EXPECT_EQ(md.size(), 5);
    EXPECT_NE(md.data(), old_data);
    EXPECT_DOUBLE_EQ(md.data()[0], 3.0);
    EXPECT_DOUBLE_EQ(md.data()[1], 4.0);
    EXPECT_DOUBLE_EQ(md.data()[2], 5.0);
}

TEST(ClassMemData, can_clear_memory_for_empty) {
    MemData md1;
    md1.clear_memory();
    EXPECT_EQ(md1.data(), nullptr);
}

TEST(ClassMemData, can_clear_memory_for_not_empty) {
    MemData md1 = { 1.0, 2.0, 3.0, 4.0, 5.0 };
    md1.clear_memory();
    EXPECT_EQ(md1.data(), nullptr);
}

TEST(ClassMemData, can_assigment) {
    MemData md1 = { 1.0, 2.0, 3.0 };
    MemData md2;

    md2 = md1;

    EXPECT_EQ(md2.size(), 3);
    EXPECT_NE(md2.data(), md1.data());
    EXPECT_DOUBLE_EQ(md2.data()[0], 1.0);
    EXPECT_DOUBLE_EQ(md2.data()[1], 2.0);
    EXPECT_DOUBLE_EQ(md2.data()[2], 3.0);
}

TEST(ClassMemData, can_move_assigment) {
    MemData md1 = { 1.0, 2.0, 3.0 };
    const double* md1_data = md1.data();
    MemData md2;

    md2 = std::move(md1);

    EXPECT_EQ(md2.size(), 3);
    EXPECT_EQ(md2.data(), md1_data);
    EXPECT_DOUBLE_EQ(md2.data()[0], 1.0);   

    EXPECT_EQ(md1.size(), 0);
    EXPECT_EQ(md1.data(), nullptr);
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
