#ifndef WRAPPER_H
#define WRAPPER_H

#include <iostream>
#include <map>
#include <vector>
#include <functional>
#include <string>
#include <utility> 


class Subject {
public:
    void f3(int arg1, int arg2);
    void f4(int arg1, int arg2, int arg3);  
    void f5(int a, int b, int c, int d);   
};

template<typename T>
class Wrapper {
public:
    using MethodType = std::function<void(T&, const std::map<std::string, int>&)>;

    template<typename... Args>
    Wrapper(T* obj, void (T::*method)(Args...), const std::map<std::string, int>& defaults);

    void call(const std::map<std::string, int>& args);

private:
    T* obj_;
    MethodType call_wrapper_;

    template<typename... Args>
    void call_method(T& obj, void (T::*method)(Args...), const std::vector<int>& ordered_args);

    template<typename... Args, size_t... Is>
    void call_method_impl(T& obj, void (T::*method)(Args...), const std::vector<int>& args, std::index_sequence<Is...>);

    std::vector<int> get_args_in_order(const std::map<std::string, int>& defaults, const std::map<std::string, int>& provided);
};


template<typename T>
template<typename... Args>
Wrapper<T>::Wrapper(T* obj, void (T::*method)(Args...), const std::map<std::string, int>& defaults)
    : obj_(obj), call_wrapper_([=](T& o, const std::map<std::string, int>& args) {
        call_method(o, method, get_args_in_order(defaults, args));
    }) {}

template<typename T>
void Wrapper<T>::call(const std::map<std::string, int>& args) {
    call_wrapper_(*obj_, args);
}

template<typename T>
template<typename... Args>
void Wrapper<T>::call_method(T& obj, void (T::*method)(Args...), const std::vector<int>& ordered_args) {
    call_method_impl(obj, method, ordered_args, std::index_sequence_for<Args...>{});
}

template<typename T>
template<typename... Args, size_t... Is>
void Wrapper<T>::call_method_impl(T& obj, void (T::*method)(Args...), const std::vector<int>& args, std::index_sequence<Is...>) {
    (obj.*method)(static_cast<int>(args[Is])...);
}

template<typename T>
std::vector<int> Wrapper<T>::get_args_in_order(const std::map<std::string, int>& defaults, const std::map<std::string, int>& provided) {
    std::vector<int> result;
    for (const auto& pair : defaults) {
        auto key = pair.first;
        auto value = provided.count(key) ? provided.at(key) : pair.second;
        result.push_back(value);
    }
    return result;
}

#endif 