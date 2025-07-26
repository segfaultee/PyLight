#pragma once

#include <string>
#include <optional>
#include <tuple>

namespace python
{
    template<typename T>
    class Result
    {
        public:
            template<typename U>
            static Result<T> success(U&& value)
            {
                Result res;
                res.value = std::forward<U>(value);
                res._error = false;
                return res;
            }
            
            static Result<T> failure(std::string err_msg)
            {
                Result res;
                res.err_msg = std::move(err_msg);
                res._error = true;
                return res;
            }
            
            bool is_success() const { return !_error; }
            bool is_error() const { return _error; }
            
            std::tuple<std::optional<T>, bool> get() { return std::make_tuple(is_success() ? value : std::nullopt, is_success()); }
            const std::string& error_message() const { return err_msg; }
        private:
            T value;
            std::string err_msg;
            bool _error = false;
    };
}
