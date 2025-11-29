#include "tests.h"
#include "wrapper.h"
#include "engine.h"
#include <iostream>

void test_f3_1() {
    std::cout << "test f3_1: ";
    Subject subj;
    Wrapper<Subject> wrapper(&subj, &Subject::f3, {{"arg1", 0}, {"arg2", 0}});

    Engine engine;
    engine.register_command(&wrapper, "command1");

    std::cout << "executing command1 with {arg2: 7, arg1: 3} -> ";
    engine.execute("command1", {{"arg2", 7}, {"arg1", 3}});
}

void test_f3_2() {
    std::cout << "test f3_2: ";
    Subject subj;
    Wrapper<Subject> wrapper(&subj, &Subject::f3, {{"arg1", 10}, {"arg2", 20}});

    Engine engine;
    engine.register_command(&wrapper, "command2");

    std::cout << "executing command2 with {arg2: 5} (arg1 defaults to 10) -> ";
    engine.execute("command2", {{"arg2", 5}});
}

void test_f3_3() {
    std::cout << "test f3_3: ";
    Subject subj;
    Wrapper<Subject> wrapper(&subj, &Subject::f3, {{"arg1", 100}, {"arg2", 200}});

    Engine engine;
    engine.register_command(&wrapper, "command3");

    std::cout << "executing command3 with {} (all defaults) -> ";
    engine.execute("command3", {});
}

void test_f4_1() {
    std::cout << "test f4_1: ";
    Subject subj;
    Wrapper<Subject> wrapper(&subj, &Subject::f4, {{"arg1", 0}, {"arg2", 0}, {"arg3", 0}});

    Engine engine;
    engine.register_command(&wrapper, "command_f4_1");

    std::cout << "executing command_f4_1 with {arg3: 30, arg1: 10, arg2: 20} -> ";
    engine.execute("command_f4_1", {{"arg3", 30}, {"arg1", 10}, {"arg2", 20}});
}

void test_f4_2() {
    std::cout << "test f4_2: ";
    Subject subj;
    Wrapper<Subject> wrapper(&subj, &Subject::f4, {{"arg1", 1}, {"arg2", 2}, {"arg3", 3}});

    Engine engine;
    engine.register_command(&wrapper, "command_f4_2");

    std::cout << "executing command_f4_2 with {arg2: 20} (arg1=1, arg3=3 defaults) -> ";
    engine.execute("command_f4_2", {{"arg2", 20}});
}

void test_f4_3() {
    std::cout << "test f4_3: ";
    Subject subj;
    Wrapper<Subject> wrapper(&subj, &Subject::f4, {{"arg1", 0}, {"arg2", 0}, {"arg3", 0}});

    Engine engine;
    engine.register_command(&wrapper, "command_f4_3");

    std::cout << "executing command_f4_3 with {arg1: 1, arg2: 2, arg3: 3} -> ";
    engine.execute("command_f4_3", {{"arg1", 1}, {"arg2", 2}, {"arg3", 3}});
    std::cout << "executing command_f4_3 with {arg1: 10, arg2: 20, arg3: 30} -> ";
    engine.execute("command_f4_3", {{"arg1", 10}, {"arg2", 20}, {"arg3", 30}});
}

void test_f5_1() {
    std::cout << "test f5_1: ";
    Subject subj;
    Wrapper<Subject> wrapper(&subj, &Subject::f5, {{"a", 0}, {"b", 0}, {"c", 0}, {"d", 0}});

    Engine engine;
    engine.register_command(&wrapper, "command_f5_1");

    std::cout << "executing command_f5_1 with {d: 40, b: 20, a: 10, c: 30} -> ";
    engine.execute("command_f5_1", {{"d", 40}, {"b", 20}, {"a", 10}, {"c", 30}});
}

void test_f5_2() {
    std::cout << "test f5_2: ";
    Subject subj;
    Wrapper<Subject> wrapper(&subj, &Subject::f5, {{"a", 100}, {"b", 200}, {"c", 300}, {"d", 400}});

    Engine engine;
    engine.register_command(&wrapper, "command_f5_2");

    std::cout << "executing command_f5_2 with {c: 30, a: 10} (b=200, d=400 defaults) -> ";
    engine.execute("command_f5_2", {{"c", 30}, {"a", 10}});
}

void test_f5_3() {
    std::cout << "test f5_3: ";
    Subject subj;
    Wrapper<Subject> wrapper(&subj, &Subject::f5, {{"a", 0}, {"b", 0}, {"c", 0}, {"d", 0}});

    Engine engine;
    engine.register_command(&wrapper, "command_f5_3");

    std::cout << "executing command_f5_3 with {a: -10, b: -20, c: -30, d: -40} -> ";
    engine.execute("command_f5_3", {{"a", -10}, {"b", -20}, {"c", -30}, {"d", -40}});
}

void test_command_not_found() {
    std::cout << "command not found: ";
    Subject subj;
    Wrapper<Subject> wrapper(&subj, &Subject::f3, {{"arg1", 0}, {"arg2", 0}});

    Engine engine;
    engine.register_command(&wrapper, "command4");

    std::cout << "executing nonexistent command -> ";
    try {
        engine.execute("nonexistent", {});
    } catch (const std::exception& e) {
        std::cout << "Exception caught: " << e.what() << std::endl;
    }
}

void unit_test(){
    std::cout << "executing command1 with {arg1: 4, arg2: 5} -> ";
    Subject subj;
    Wrapper<Subject> wrapper(&subj, &Subject::f3, {{"arg1", 0}, {"arg2", 0}});

    Engine engine;
    engine.register_command(&wrapper, "command1");

    engine.execute("command1", {{"arg1", 4}, {"arg2", 5}});
}

void run_tests() {
    std::cout << "unit test from task: ";
    unit_test();
    test_f3_1();
    test_f3_2();
    test_f3_3();
    test_f4_1();
    test_f4_2();
    test_f4_3();
    test_f5_1();
    test_f5_2();
    test_f5_3();
    test_command_not_found();
}