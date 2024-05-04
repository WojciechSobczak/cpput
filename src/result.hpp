#pragma once

#include <variant>
#include <string_view>
#include <span>
#include <concepts>
#include <memory>

namespace cpput 
{

template<typename T>
concept simple_type = std::integral<T> || std::same_as<T, bool> || std::floating_point<T>;

template<typename T>
concept unique_pointer = std::same_as<T, std::unique_ptr<typename T::element_type>>;

template<typename T>
concept shared_pointer = std::same_as<T, std::shared_ptr<typename T::element_type>>;

template<typename T>
concept no_cost_copy_type = simple_type<T> ||
    std::is_pointer_v<T> ||
    std::is_enum_v<T> ||
    std::same_as<T, std::string_view> ||
    std::same_as<T, std::span<typename T::element_type>> ||
    shared_pointer<T>;

template<typename value_type, typename error_type>
class [[nodiscard]] result : protected std::variant<value_type, error_type> {
public:
    using std::variant<value_type, error_type>::variant;

    [[nodiscard]]
    bool has_value() const noexcept {
        return std::holds_alternative<value_type>(*this);
    }

    [[nodiscard]]
    bool has_error() const noexcept {
        return std::holds_alternative<error_type>(*this);
    }

    [[nodiscard]]
    value_type get_value() const requires(no_cost_copy_type<value_type> && !unique_pointer<value_type>) {
        return std::get<value_type>(*this);
    }

    [[nodiscard]]
    value_type& get_value() requires(!no_cost_copy_type<value_type> && !unique_pointer<value_type>) {
        return std::get<value_type>(*this);
    }

    [[nodiscard]]
    const value_type& get_value() const requires(!no_cost_copy_type<value_type> && !unique_pointer<value_type>) {
        return std::get<value_type>(*this);
    }

    [[nodiscard]]
    error_type get_error() requires(no_cost_copy_type<error_type> && !unique_pointer<error_type>) {
        return std::get<error_type>(*this);
    }

    [[nodiscard]]
    error_type& get_error() requires(!no_cost_copy_type<error_type> && !unique_pointer<error_type>) {
        return std::get<error_type>(*this);
    }

    [[nodiscard]]
    const error_type& get_error() const requires(!no_cost_copy_type<error_type> && !unique_pointer<error_type>) {
        return std::get<error_type>(*this);
    }

    [[nodiscard]]
    value_type&& release_value() {
        return std::move(std::get<value_type>(*this));
    }

    [[nodiscard]]
    error_type&& release_error() {
        return std::move(std::get<error_type>(*this));
    }
};

template<typename error_type>
class [[nodiscard]] result<void, error_type> : protected std::variant<std::monostate, error_type> {
private:
    using std::variant<std::monostate, error_type>::variant;

public:
    explicit result(error_type&& error) : std::variant<>(std::forward<>(error)) {};
    explicit result(error_type& error) : std::variant<>(error) {};

    [[nodiscard]]
    bool is_success() const noexcept {
        return !hasError();
    }

    [[nodiscard]]
    bool has_error() const noexcept {
        return std::holds_alternative<error_type>(*this);
    }

    [[nodiscard]]
    error_type get_error() requires(no_cost_copy_type<error_type> && !unique_pointer<error_type>) {
        return std::get<error_type>(*this);
    }

    [[nodiscard]]
    error_type& get_error() requires(!no_cost_copy_type<error_type> && !unique_pointer<error_type>) {
        return std::get<error_type>(*this);
    }

    [[nodiscard]]
    const error_type& get_error() const requires(!no_cost_copy_type<error_type> && !unique_pointer<error_type>) {
        return std::get<error_type>(*this);
    }

    [[nodiscard]]
    error_type&& release_error() {
        return std::move(getError());
    }
};


};