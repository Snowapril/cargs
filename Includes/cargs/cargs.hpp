#ifndef CARGS_CARGS_HPP
#define CARGS_CARGS_HPP

#include <iostream>
#include <string>
#include <string_view>
#include <unordered_map>
#include <vector>

namespace cargs
{
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
     * @brief Construct a new Flag object
     *
     * @param short_hint
     * @param long_hint
     * @param description
     */
    Flag(char short_hint, const std::string& long_hint,
         const std::string& description, Value value)
        : _short_hint(short_hint),
          _long_hint(long_hint),
          _description(description),
          _value(value)
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
    char _short_hint{ 0 };
    std::string _long_hint;
    std::string _description;
    Value _value;
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
    Cargs(const std::string& command_name, size_t command_level = 0)
        : _command_name(command_name), _command_level(command_level)
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
        _sub_commands.push_back(new Cargs(command_name, _command_level + 1));
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
        _flags.emplace_back(short_hint, long_hint, description, value);
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
    Flag get_similar_flag(const std::string& long_hint,
                          double similar_percentage = 5e-1)
    {
        size_t min_distance = std::numeric_limits<size_t>::max();
        const size_t i_epsilon =
            static_cast<size_t>(long_hint.size() * similar_percentage);
        const Flag* candidate_ptr = nullptr;

        for (const auto& flag : _flags)
        {
            size_t distance =
                Utils::levenshtein_distance(long_hint, flag.get_long_hint());
            if (distance > i_epsilon && min_distance > distance)
            {
                min_distance = distance;
                candidate_ptr = &flag;
            }
        }

        return min_distance == std::numeric_limits<size_t>::max()
                   ? (*candidate_ptr)
                   : Flag();
    }

 protected:
 private:
    std::string _command_name;
    std::vector<Cargs*> _sub_commands;
    std::vector<Flag> _flags;
    size_t _command_level{ 0 };
};

}  // namespace cargs

#endif