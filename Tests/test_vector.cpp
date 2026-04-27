#pragma once
#include "pch.h"
#define MEMDATA_TESTS
#define VECTOR_TESTS

#ifdef MEMDATA_TESTS
#include "memdata.h"
#include <iostream>


//TEST(FunctionsForMemData, calculate_capacity) {
//    MemData md
//    EXPECT_EQ(md.calculate_capacity(10), 10+MEM_STEP);
//    EXPECT_EQ(md.calculate_capacity(0), MEM_STEP);
//}

TEST(ClassMemData, can_create_with_default_constructor) {
    MemData md;
    EXPECT_EQ(md.size(), 0);
    EXPECT_EQ(md.capacity(), 0);

}

TEST(ClassMemData, can_create_with_constructor_by_size) {
    MemData md(5);
    EXPECT_EQ(md.size(), 0);
    EXPECT_EQ(md.capacity(), 5);
}

TEST(ClassMemData, can_create_with_constructor_by_initializer_list) {
    MemData md = { 1.0, 3.4, 1.1 };
    EXPECT_EQ(md.size(), 3);
    EXPECT_EQ(md.capacity(), 3);
    EXPECT_DOUBLE_EQ(md.data()[1], 3.4);
}

TEST(ClassMemData, can_create_with_init_constructor) {
    double a[] = { 3.5, 11, 2.2 };
    MemData md(a, 3);
    EXPECT_EQ(md.size(), 3);
    EXPECT_EQ(md.capacity(), 3);
    EXPECT_DOUBLE_EQ(md.data()[1], 11.0);
}

TEST(ClassMemData, can_create_with_copy_constructor) {
    MemData md1 = { 1.0, 3.4, 1.1 };
    MemData md2(md1);
    EXPECT_EQ(md1.data()[1], md2.data()[1]);
    EXPECT_EQ(md2.size(), 3);
    EXPECT_EQ(md2.capacity(), 3);
}

TEST(ClassMemData, can_create_with_move_constructor) {
    MemData md1 = { 1.0, 3.4, 1.1 };
    MemData md2(std::move(md1));

    EXPECT_EQ(md1.data(), nullptr);
    EXPECT_DOUBLE_EQ(md2.data()[0], 1.0);
    EXPECT_DOUBLE_EQ(md2.data()[1], 3.4);
    EXPECT_DOUBLE_EQ(md2.data()[2], 1.1);
    EXPECT_EQ(md2.size(), 3);
    EXPECT_EQ(md2.capacity(), 3);

    EXPECT_TRUE(md1.is_empty());
}

TEST(ClassMemData, can_is_empty) {
    MemData md;
    EXPECT_TRUE(md.is_empty());
}

TEST(ClassMemData, can_is_full) {
    MemData md2 = { 1.0, 2.0, 3.0 };
    md2.clear_memory();
    EXPECT_EQ(md2.size(), 3);
    EXPECT_EQ(md2.capacity(), 3);
    EXPECT_TRUE(md2.is_full());
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

    md.reset_memory(10,0);

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

    EXPECT_EQ(md.capacity(), 3);
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

    EXPECT_EQ(md.capacity(), old_capacity);
    EXPECT_NE(md.data(), old_data);
    EXPECT_DOUBLE_EQ(md.data()[0], 1.0);
    EXPECT_DOUBLE_EQ(md.data()[1], 2.0);
    EXPECT_DOUBLE_EQ(md.data()[2], 3.0);
}

TEST(ClassMemData, can_reset_memory_with_shift) {
    MemData md = { 1.0, 2.0, 3.0, 4.0, 5.0 };
    const double* old_data = md.data();

    md.reset_memory(3, 2);  // start_index = 2

    EXPECT_EQ(md.capacity(), 3);//Запас все равно создается
    EXPECT_EQ(md.size(), 3);
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
    Vector v1;

    EXPECT_EQ(v1.front_pos(), 0);
    EXPECT_EQ(v1.back_pos(), 0);
    EXPECT_EQ(v1.is_empty(), 1);
}

TEST(ClassVector, can_create_with_constructor_by_size) {
    Vector v1(5);

    EXPECT_EQ(v1.front_pos(), 0);
    EXPECT_EQ(v1.back_pos(), 4);
    EXPECT_EQ(v1.is_empty(), true);
}

TEST(ClassVector, can_create_with_constructor_by_initializer_list) {
    Vector v1 = { 1.0, 3.4, 1.1 };
    EXPECT_EQ(v1.size(), 3);
    EXPECT_EQ(v1.capacity(), 3);
    EXPECT_EQ(v1.front_pos(), 0);
    EXPECT_DOUBLE_EQ(v1.front(), 1.0);
}

TEST(ClassVector, can_create_with_init_constructor) {
    double mass[] = {1.0, 3.4, 1.1};
    Vector v1(mass, 3);
    EXPECT_EQ(v1.size(), 3);
    EXPECT_EQ(v1.capacity(), 3);
    EXPECT_DOUBLE_EQ(v1.front(), 1.0);
}

TEST(ClassVector, can_create_with_copy_constructor) {
    Vector v1 = { 1.0, 3.4, 1.1 };
    Vector v2(v1);
    EXPECT_EQ(v2.size(), 3);
    EXPECT_EQ(v2.capacity(), 3);
    EXPECT_EQ(v1.front_pos(), 0);
    EXPECT_EQ(v2.front_pos(), 0);
    EXPECT_DOUBLE_EQ(v2.front(), 1.0);
}

TEST(ClassVector, can_create_with_move_constructor) {
    Vector v1 = { 1.0, 3.4, 1.1 };
    Vector v2(std::move(v1));
    EXPECT_EQ(v2.size(), 3);
    EXPECT_EQ(v2.capacity(), 3);
    EXPECT_DOUBLE_EQ(v2.front(), 1.0);
}

TEST(ClassVector, can_is_empty) {
    Vector v1;
    EXPECT_TRUE(v1.is_empty());
}

TEST(ClassVector, can_is_full) {
    Vector v1 = { 1.0, 3.4, 1.1 };
    EXPECT_TRUE(v1.is_full());
}

TEST(ClassVector, can_get_front) {
    Vector v1 = { 1.0, 3.4, 1.1 };
    EXPECT_EQ(v1.front(), 1.0);
}

TEST(ClassVector, can_get_back) {
    Vector v1 = { 1.0, 3.4, 1.1 };
    EXPECT_EQ(v1.back_pos(), 2);
    EXPECT_EQ(v1.back(), 1.1);
}

TEST(ClassVector, can_set_front) {
    Vector v = { 1.0, 2.0, 3.0 };

    v.set_front() = 10.0;

    EXPECT_DOUBLE_EQ(v.front(), 10.0);
    EXPECT_DOUBLE_EQ(v[0], 10.0);
    EXPECT_DOUBLE_EQ(v[1], 2.0);
    EXPECT_DOUBLE_EQ(v[2], 3.0);

    Vector v2(5);
    for (int i = 0; i < 5; i++) {
        v2.push_back(i * 1.0);
    }
    v2.set_front() = 99.0;
    EXPECT_DOUBLE_EQ(v2.front(), 99.0);
    EXPECT_DOUBLE_EQ(v2[v2.front_pos()], 99.0);
}

TEST(ClassVector, can_set_back) {
    Vector v = { 1.0, 2.0, 3.0 };

    v.set_back() = 30.0;

    EXPECT_DOUBLE_EQ(v.back(), 30.0);
    EXPECT_DOUBLE_EQ(v[2], 30.0);
    EXPECT_DOUBLE_EQ(v[0], 1.0);
    EXPECT_DOUBLE_EQ(v[1], 2.0);

    Vector v2 = { 5.0 };
    v2.set_back() = 50.0;
    EXPECT_DOUBLE_EQ(v2.front(), 50.0);
    EXPECT_DOUBLE_EQ(v2.back(), 50.0);

    Vector v3(10); //capacity = 10+MEM_SIZE = 25
    for (int i = 0; i < 10; i++) {//идем front_pos = [5;14] и заполняем массив
        v3.push_back(i * 1.0);
    }
    v3.set_back() = 99.0;
    EXPECT_DOUBLE_EQ(v3.back(), 99.0);
    EXPECT_DOUBLE_EQ(v3[v3.back_pos()], 99.0);
    EXPECT_DOUBLE_EQ(v3.back_pos(), 14);
}

TEST(ClassVector, throw_when_try_get_front_in_empty_vector) {
    Vector v1;
    EXPECT_THROW(v1.front(), std::out_of_range);
}

TEST(ClassVector, throw_when_try_get_back_in_empty_vector) {
    Vector v1;
    EXPECT_THROW(v1.back(), std::out_of_range);
}

TEST(ClassVector, throw_when_try_set_front_in_empty_vector) {
    Vector v;

    EXPECT_THROW(v.set_front() = 1.0, std::out_of_range);
}

TEST(ClassVector, throw_when_try_set_back_in_empty_vector) {
    Vector v;

    EXPECT_THROW(v.set_back() = 1.0, std::out_of_range);
}

//TEST(ClassVector, can_output_with_operator_cout) {
//    Vector vec({ 1, 2, 3, 4, 5, 6, 7, 8, 9 });
//    std::stringstream out;
//    out << vec;
//    EXPECT_EQ("{ 1, 2, 3, 4, 5, 6, 7, 8, 9 }", out.str());
//}

//TEST(ClassVector, can_input_with_operator_cin) {
//    Vector vec({ 1, 2, 3, 4, 5, 6, 7, 8, 9 });
//    std::stringstream in("9 1 2 3 4 5 6 7 8 9");
//    in >> vec;
//
//    EXPECT_EQ(9, vec.size());
//    EXPECT_EQ(15, vec.capacity());
//
//    for (size_t i = 0; i < vec.size(); i++) {
//        EXPECT_DOUBLE_EQ(vec[i], i + 1);
//    }
//}

TEST(ClassVector, can_push_front) {
    Vector v1 = { 1.0, 3.4, 1.1 };
    v1.push_front(2.5);
    EXPECT_EQ(v1.front(), 2.5);
}

TEST(ClassVector, can_push_front_in_empty_vector) {
    Vector v1; // capacity = 0
    v1.push_front(2.5);
    EXPECT_EQ(v1.front(), 2.5);
    EXPECT_EQ(v1.front_pos(), 5);
    EXPECT_EQ(v1.capacity(), FRONT_BUFFER + MEM_STEP); // в set_memory выделяется буфер - создается массив с позиции FRONT_BUFFER
}

//TEST(ClassVector, can_push_front_with_reallocation) { //в моей реализации этот тест уже учтен выше
//    Vector v1 = { 1.0, 3.4, 1.1 }; //capacity = 3
//    v1.push_front(2.5);
//    EXPECT_EQ(v1.front(), 2.5);
//    EXPECT_EQ(v1.front_pos(), 5);
//    EXPECT_EQ(v1.capacity(), v1.size() + MEM_STEP);
//}

TEST(ClassVector, can_push_back) {
    Vector v1 = { 1.0, 3.4, 1.1 };
    v1.push_back(2.5);
    EXPECT_EQ(v1.back(), 2.5);
    EXPECT_EQ(v1.back_pos(), 3+ FRONT_BUFFER);
}

TEST(ClassVector, can_push_back_in_empty_vector) {
    Vector v1;
    v1.push_back(2.5);
    EXPECT_EQ(v1.back(), 2.5);
    EXPECT_EQ(v1.back_pos(), 5);
    EXPECT_EQ(v1.capacity(), FRONT_BUFFER+MEM_STEP);
}

//TEST(ClassVector, can_push_back_with_reallocation) { //в моей реализации этот тест уже учтен
//    Vector v1 = { 1.0, 3.4, 1.1 };
//    v1.push_back(2.5);
//    EXPECT_EQ(v1.back(), 2.5);
//    EXPECT_EQ(v1.back_pos(), 3);
//}

TEST(ClassVector, can_insert) {
    Vector v1 = { 1.0, 3.4, 1.1 };
    v1.insert(2.5,2);
    for (size_t i = 0; i < v1.size(); i++) {
        EXPECT_EQ(v1[i + v1.front_pos()], 0);
    }
    EXPECT_EQ(v1.capacity(), 4+MEM_STEP+FRONT_BUFFER);
    EXPECT_EQ(v1.size(), 4);
}

//TEST(ClassVector, can_insert_with_reallocation) { // в моей реализации этот тест уже учтен
//    ADD_FAILURE();
//}

TEST(ClassVector, can_insert_to_front) {
    Vector v1 = { 1.0, 3.4, 1.1 };//size = capacity = 3
    EXPECT_EQ(v1.front_pos(), 0);
    v1.insert(2.5, v1.front_pos());//front_pos = 0 //capacity = 4 + 15 = 19
    EXPECT_EQ(v1.front_pos(), FRONT_BUFFER);
    for (size_t i = 0; i < v1.size(); i++) {
        EXPECT_EQ(v1[i + v1.front_pos()], 0);
    }
    EXPECT_EQ(v1.capacity(), 4 + MEM_STEP+FRONT_BUFFER);
    EXPECT_EQ(v1.size(), 4);
}

TEST(ClassVector, throw_when_try_insert_with_wrong_position) {
    Vector v1 = { 1.0, 3.4, 1.1 };
    EXPECT_THROW(v1.insert(2.5, 4), std::out_of_range);
    Vector v2;
    EXPECT_THROW(v2.insert(2.5, 1), std::out_of_range);
    Vector v3 = { 1.0, 3.4, 1.1 };
    EXPECT_THROW(v3.insert(2.5, -1), std::out_of_range);
    
}

TEST(ClassVector, can_pop_front) {
    Vector v = { 1.0, 2.0, 3.0, 4.0, 5.0 };

    EXPECT_EQ(v.size(), 5);
    EXPECT_DOUBLE_EQ(v.front(), 1.0);
    EXPECT_DOUBLE_EQ(v.back(), 5.0);

    v.pop_front();

    EXPECT_EQ(v.size(), 4);
    EXPECT_DOUBLE_EQ(v.front(), 2.0);  // Теперь первый = 2.0
    EXPECT_DOUBLE_EQ(v.back(), 5.0);   // Последний не изменился

    // Удаляем ещё один
    v.pop_front();

    EXPECT_EQ(v.size(), 3);
    EXPECT_DOUBLE_EQ(v.front(), 3.0);
    EXPECT_DOUBLE_EQ(v.back(), 5.0);
}

TEST(ClassVector, can_pop_front_with_reallocation) {
     Vector v(5);  //capacity = 5+15 = 20
     EXPECT_EQ(v.size(), 0);
    // Заполняем данными
    for (int i = 0; i < 5; i++) {
        v.push_back(i * 1.0);
    }
    EXPECT_EQ(v.size(), 5);

    size_t old_capacity = v.capacity();

    // Удаляем элементы (может сжатие памяти, если реализовано)
    v.pop_front();
    v.pop_front();
    v.pop_front();

    EXPECT_EQ(v.size(), 2);
    EXPECT_DOUBLE_EQ(v.front(), 3.0);
    EXPECT_DOUBLE_EQ(v.back(), 4.0);

    // Capacity не должен уменьшиться ниже size
    EXPECT_GE(v.capacity(), v.size());
}

TEST(ClassVector, throw_when_try_pop_front_from_empty_vector) {
    Vector v;

    EXPECT_TRUE(v.is_empty());
    EXPECT_EQ(v.size(), 0);
    EXPECT_THROW(v.pop_front(), std::out_of_range);
}

TEST(ClassVector, can_pop_back) {
    Vector v = { 1.0, 2.0, 3.0, 4.0, 5.0 };

    EXPECT_EQ(v.size(), 5);
    EXPECT_DOUBLE_EQ(v.front(), 1.0);
    EXPECT_DOUBLE_EQ(v.back(), 5.0);

    
    v.pop_back();

    EXPECT_EQ(v.size(), 4);
    EXPECT_DOUBLE_EQ(v.front(), 1.0);  
    EXPECT_DOUBLE_EQ(v.back(), 4.0);   

    
    v.pop_back();

    EXPECT_EQ(v.size(), 3);
    EXPECT_DOUBLE_EQ(v.front(), 1.0);
    EXPECT_DOUBLE_EQ(v.back(), 3.0);
}

TEST(ClassVector, can_pop_back_with_reallocation) {
    
    Vector v(10);

    for (int i = 0; i < 10; i++) {
        v.push_back(i * 1.0);//каждый раз size увеличивается на +1 -> size = 20
    }

    EXPECT_EQ(v.size(), 10);
    size_t old_capacity = v.capacity();

    
    v.pop_back();
    v.pop_back();
    v.pop_back();
    v.pop_back();
    v.pop_back();

    EXPECT_EQ(v.size(), 5);
    EXPECT_DOUBLE_EQ(v.front(), 0.0);
    EXPECT_DOUBLE_EQ(v.back(), 4.0);

    
    EXPECT_GE(v.capacity(), v.size());
}

TEST(ClassVector, throw_when_try_pop_back_from_empty_vector) {
    Vector v;

    EXPECT_TRUE(v.is_empty());
    EXPECT_EQ(v.size(), 0);

    
    EXPECT_THROW(v.pop_back(), std::out_of_range);
}

TEST(ClassVector, pop_front_back_to_empty) {
    Vector v = { 1.0, 2.0, 3.0 };

    v.pop_front();
    v.pop_back();
    v.pop_front();  

    EXPECT_TRUE(v.is_empty());
    EXPECT_EQ(v.size(), 0);
}

TEST(ClassVector, pop_single_element) {
    Vector v = { 42.0 };

    EXPECT_EQ(v.size(), 1);
    EXPECT_DOUBLE_EQ(v.front(), 42.0);
    EXPECT_DOUBLE_EQ(v.back(), 42.0);

    v.pop_front();  

    EXPECT_TRUE(v.is_empty());
    EXPECT_EQ(v.size(), 0);
}

TEST(ClassVector, pop_front_back_alternating) {
    Vector v = { 1.0, 2.0, 3.0, 4.0, 5.0 };

    v.pop_front();  // {2, 3, 4, 5}
    v.pop_back();   // {2, 3, 4}
    v.pop_front();  // {3, 4}
    v.pop_back();   // {3}
    v.pop_front();  // {}

    EXPECT_TRUE(v.is_empty());
    EXPECT_EQ(v.size(), 0);
}

TEST(ClassVector, can_correctly_recalc_back_in_area_of_zero) {
    Vector vec;

    for (size_t i = 0; i < 15; i++) {
        vec.push_back(i + 1); // от i = 5  до i = 19
        EXPECT_DOUBLE_EQ(vec[i+5], i+1);
    }
    EXPECT_EQ(vec.size(), 15);
    EXPECT_EQ(26, vec.capacity());
    vec.pop_front(); // от i = 6 до i = 19
    EXPECT_EQ(vec.size(), 14);
    vec.push_back(16);// от i = 6 до i = 20, capacity = 26;

    EXPECT_EQ(15, vec.size());
    EXPECT_EQ(26, vec.capacity());
    EXPECT_EQ(vec.is_full(), false);
    EXPECT_EQ(20, vec.back_pos());
    EXPECT_DOUBLE_EQ(16.0, vec.back());
    size_t front = vec.front_pos();//6
    EXPECT_EQ(front, 6);
    EXPECT_EQ(2, vec[front]);
    for (size_t i = 0; i < vec.size(); i++) {
        EXPECT_DOUBLE_EQ(vec[i+front], i+2);
    }

    vec.pop_back();

    EXPECT_EQ(14, vec.size());
    EXPECT_EQ(26, vec.capacity());
    EXPECT_DOUBLE_EQ(15.0, vec.back());

    for (size_t i = 0; i < vec.size(); i++) {
        EXPECT_DOUBLE_EQ(vec[i + front], i + 2);
    }
}
TEST(ClassVector, can_correctly_recalc_front_in_area_of_zero) {
    Vector v(10);
    for (int i = 0; i < 10; i++) v.push_back(i * 1.0);

    for (int i = 0; i < 10; i++) v.pop_front();

    EXPECT_TRUE(v.is_empty());

    for (int i = 10; i < 20; i++) v.push_back(i * 1.0);

    EXPECT_EQ(v.size(), 10);
    EXPECT_DOUBLE_EQ(v.front(), 10.0);
    EXPECT_DOUBLE_EQ(v.back(), 19.0);
}

TEST(ClassVector, can_erase) {
    Vector v = { 1.0, 2.0, 3.0, 4.0, 5.0 };
    EXPECT_EQ(v.size(), 5);
    EXPECT_EQ(v.capacity(), 5);
    v.erase(2);

    EXPECT_EQ(v.size(), 4);
    for (size_t i = -2; i < v.size(); i++) {
        EXPECT_DOUBLE_EQ(v[i+v.front()], 0);
    }
}

TEST(ClassVector, can_erase_front) {
    Vector v = { 1.0, 2.0, 3.0, 4.0, 5.0 };

    v.erase(0);

    EXPECT_EQ(v.size(), 4);
    EXPECT_DOUBLE_EQ(v.front(), 2.0);
    EXPECT_DOUBLE_EQ(v.back(), 5.0);
    EXPECT_DOUBLE_EQ(v[1], 2.0);
    EXPECT_DOUBLE_EQ(v[4], 5.0);
}

TEST(ClassVector, can_erase_back) {
    Vector v = { 1.0, 2.0, 3.0, 4.0, 5.0 };

    v.erase(4);

    EXPECT_EQ(v.size(), 4);
    EXPECT_DOUBLE_EQ(v.front(), 1.0);
    EXPECT_DOUBLE_EQ(v.back(), 4.0);
    EXPECT_DOUBLE_EQ(v[0], 1.0);
    EXPECT_DOUBLE_EQ(v[3], 4.0);
}

TEST(ClassVector, can_erase_with_reallocation) {
    Vector v(5);
    for (int i = 0; i < 5; i++) v.push_back(i * 1.0);

    v.erase(0);
    v.erase(0);
    v.erase(0);

    EXPECT_EQ(v.size(), 2);
    EXPECT_DOUBLE_EQ(v.front(), 3.0);
    EXPECT_DOUBLE_EQ(v.back(), 4.0);
    EXPECT_GE(v.capacity(), v.size());
}

TEST(ClassVector, throw_when_try_erase_from_empty_vector) {
    Vector v;

    EXPECT_THROW(v.erase(0), std::out_of_range);
}

TEST(ClassVector, throw_when_try_erase_with_wrong_position) {
    Vector v = { 1.0, 2.0, 3.0 };

    EXPECT_THROW(v.erase(3), std::out_of_range);
    EXPECT_THROW(v.erase(100), std::out_of_range);
}

//TEST(ClassVector, combination_push_pop_insert_erase) {
//    Vector vec({ 3, 44, 5, 7, 8 });
//
//    std::stringstream out;
//    out << vec;
//    EXPECT_EQ("{ 3, 44, 5, 7, 8 }", out.str());
//    out.str("");
//
//    vec.pop_front();
//    out << vec;
//    EXPECT_EQ("{ 44, 5, 7, 8 }", out.str());
//    out.str("");
//
//    for (size_t i = 0; i < 4; i++) {
//        vec.push_front(3 - i);
//    }
//    out << vec;
//    EXPECT_EQ("{ 0, 1, 2, 3, 44, 5, 7, 8 }", out.str());
//    out.str("");
//
//    vec.pop_back();
//    out << vec;
//    EXPECT_EQ("{ 0, 1, 2, 3, 44, 5, 7 }", out.str());
//    out.str("");
//
//    for (size_t i = 0; i < 4; i++) {
//        vec.push_back(8 + i);
//    }
//    out << vec;
//    EXPECT_EQ("{ 0, 1, 2, 3, 44, 5, 7, 8, 9, 10, 11 }", out.str());
//    out.str("");
//
//    vec.erase(0);
//    out << vec;
//    EXPECT_EQ("{ 1, 2, 3, 44, 5, 7, 8, 9, 10, 11 }", out.str());
//    out.str("");
//
//    vec.erase(3);
//    out << vec;
//    EXPECT_EQ("{ 1, 2, 3, 5, 7, 8, 9, 10, 11 }", out.str());
//    out.str("");
//
//    vec.insert(6, 4);
//    out << vec;
//    EXPECT_EQ("{ 1, 2, 3, 5, 6, 7, 8, 9, 10, 11 }", out.str());
//    out.str("");
//
//    for (size_t i = 0; i < 5; i++) {
//        vec.push_back(12 + i);
//    }
//    out << vec;
//    EXPECT_EQ("{ 1, 2, 3, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16 }", out.str());
//    out.str("");
//
//    vec.insert(4, 3);
//    out << vec;
//    EXPECT_EQ("{ 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16 }", out.str());
//    out.str("");
//
//    EXPECT_EQ(16, vec.size());
//    EXPECT_EQ(30, vec.capacity());
//
//    for (size_t i = 0; i < vec.size(); i++) {
//        EXPECT_DOUBLE_EQ(vec[i], i + 1);
//    }
//}

TEST(ClassVector, can_assigment) {
    Vector v1 = { 1.0, 2.0, 3.0 };
    Vector v2;

    v2 = v1;

    EXPECT_EQ(v2.size(), v1.size());
    EXPECT_EQ(v2.capacity(), v1.capacity());
    EXPECT_DOUBLE_EQ(v2[0], 1.0);
    EXPECT_DOUBLE_EQ(v2[1], 2.0);
    EXPECT_DOUBLE_EQ(v2[2], 3.0);
    EXPECT_DOUBLE_EQ(v2.front(), 1.0);
    EXPECT_DOUBLE_EQ(v2.back(), 3.0);

    v1.push_back(4.0);
    EXPECT_EQ(v2.size(), 3);
    EXPECT_EQ(v1.size(), 4);

    Vector v3 = { 10.0, 20.0 };
    v2 = v3;
    EXPECT_EQ(v2.size(), 2);
    EXPECT_DOUBLE_EQ(v2[0], 10.0);
    EXPECT_DOUBLE_EQ(v2[1], 20.0);

    Vector v4;
    v4 = v4;
    EXPECT_TRUE(v4.is_empty());

    Vector v5 = { 5.0, 6.0, 7.0 };
    const Vector& v5_ref = v5;
    Vector v6;
    v6 = v5_ref;
    EXPECT_EQ(v6.size(), 3);
    EXPECT_DOUBLE_EQ(v6[0], 5.0);
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
    size_t front = vec_2.front_pos();
    for (size_t i = 0; i < vec_2.size()+front-1; i++) {
        EXPECT_EQ(vec_2[i+front], i+1);
    }
}

#endif
