#ifndef CARGS_CARGS_HPP
#define CARGS_CARGS_HPP

#include <iostream>
#include <string>
#include <string_view>
#include <unordered_map>
#include <vector>

namespace cargs
{
class Value
{
 public:
    /**
     * @brief Construct a new Value object
     *
     */
    Value()
    {
        //! Do nothing
    }
    /**
     * @brief Destroy the Value object
     *
     */
    ~Value()
    {
        //! Do nothing
    }

 private:
};

class Flag
{
 public:
    /**
     * @brief Construct a new cargs flag object
     *
     */
    Flag()
    {
        //! Do nothing
    }
    /**
     * @brief Destroy the cargs flag object
     *
     */
    ~Flag()
    {
        //! Do nothing
    }

    /**
     * @brief Get the short hint object
     *
     * @return char
     */
    inline char get_short_hint() const
    {
        return _short_hint;
    }

    /**
     * @brief Get the long hint object
     *
     * @return std::string
     */
    inline std::string get_long_hint() const
    {
        return _long_hint;
    }

    /**
     * @brief Get the description object
     *
     * @return std::string
     */
    inline std::string get_description() const
    {
        return _description;
    }

 private:
    char _short_hint;
    std::string _long_hint;
    std::string _description;
};

class Result
{
 public:
    /**
     * @brief Construct a new cargs result object
     *
     */
    Result()
    {
        //! Do nothing
    }
    /**
     * @brief Destroy the cargs result object
     *
     */
    ~Result()
    {
        //! Do nothing
    }

    /**
     * @brief Get the wrong arguments object
     *
     * @return std::vector<std::string>
     */
    std::vector<std::string> get_wrong_arguments() const
    {
        //! Do nothing
        return std::vector<std::string>();
    }

    /**
     * @brief
     *
     * @param hint
     * @return Flag&
     */
    Flag& operator[](const std::string& hint)
    {
        return _flags[hint];
    }

 private:
    std::unordered_map<std::string, Flag> _flags;
    std::vector<std::string> _unknown_args;
};

class Cargs
{
 public:
    /**
     * @brief Default constructor for Cargs
     */
    Cargs()
    {
        //! Do nothing
    }

    /**
     * @brief Construct a new Cargs object
     *
     * @param command_name
     */
    Cargs(const std::string& command_name) : _command_name(command_name)
    {
        //! Do nothing
    }

    /**
     * @brief Default destructor for Cargs
     */
    ~Cargs()
    {
        //! Do nothing
        for (Cargs* sub_command_ptr : _sub_commands)
            delete sub_command_ptr;
    }

    /**
     * @brief
     *
     * @param command_name
     * @return Cargs&
     */
    [[nodiscard]] Cargs& add_command(const std::string& command_name)
    {
        //! Do nothing
        (void)command_name;
        _sub_commands.push_back(new Cargs(command_name));
        return *this;
    }

    /**
     * @brief
     *
     * @param short_hint
     * @param long_hint
     * @param description
     * @param flag
     * @return Cargs&
     */
    [[maybe_unused]] Cargs& add_flag(char short_hint,
                                     const std::string& long_hint,
                                     const std::string& description,
                                     Value value)
    {
        //! Do nothing
        (void)short_hint;
        (void)long_hint;
        (void)description;
        (void)value;
        return *this;
    }

    /**
     * @brief
     *
     * @param short_hint
     * @param long_hint
     * @param description
     * @param flag
     * @return Cargs&
     */
    [[maybe_unused]] Cargs& operator()(char short_hint,
                                       const std::string& long_hint,
                                       const std::string& description,
                                       Value value)
    {
        return add_flag(short_hint, long_hint, description, value);
    }

    /**
     * @brief
     *
     * @param argc
     * @param argv
     * @return Result
     */
    Result parse_args(int argc, char* argv[])
    {
        //! Do nothing
        (void)argc;
        (void)argv;
        return Result();
    }

    /**
     * @brief Get the similar flags object
     *
     * @param long_hint
     * @return std::vector<Flag>
     */
    Flag get_similar_flag(const std::string& long_hint, double epsilon = 1e-6)
    {
        //! Do nothing
        (void)long_hint;
        (void)epsilon;
        return Flag();
    }

 protected:
 private:
    std::vector<Cargs*> _sub_commands;
    std::string _command_name;
    size_t _command_level{ 0 };
};

class Utils
{
 public:
    /**
     * @brief
     *
     * @param s1
     * @param s2
     * @return size_t
     */
    static size_t levenshtein_distance(const std::string_view& s1,
                                       const std::string_view& s2)
    {
        (void)s1;
        (void)s2;
        return 0;
    }
};

}  // namespace cargs

#endif