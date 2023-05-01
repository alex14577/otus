#include <unordered_map>
#include <tuple>
#include <memory>

struct PairHash
{
    std::size_t operator() (const std::pair<size_t, size_t> &pair) const {
        return std::hash<size_t>()(pair.first) ^ std::hash<size_t>()(pair.second);
    }
};

struct KeyEqual {
  bool operator()(const std::pair<std::size_t, std::size_t>& lhs, const std::pair<std::size_t, std::size_t>& rhs) const {
    return lhs.first == rhs.first && lhs.second == rhs.second;
  }
};

template<typename T, T DefaultValue>
// using T = int;
// constexpr T DefaultValue = -1;
class Matrix {
public:
    using iterator = std::unordered_map<std::pair<size_t, size_t>, T, PairHash, KeyEqual>::iterator;

    class Proxy
    {
    public:
        Proxy(Matrix& matrix, size_t x)
            : matrix_(matrix)
            , x_(x)
             {}

        operator T() const 
        {
            auto it = matrix_.values_.find(std::make_pair(x_, y_));
            if(it != matrix_.values_.end())
            {
                return it->second;
            }
            return DefaultValue;
        }

        Proxy operator=(const T& val)
        {
            if( val != DefaultValue)
            {
                matrix_.values_.emplace(std::make_pair(x_, y_), val);
            }
            else
            {
                auto it = matrix_.values_.find(std::make_pair(x_, y_));
                if(it != matrix_.values_.end())
                {
                    matrix_.values_.erase(it);
                }                
            }
            return *this;
        }

        Proxy& operator[](size_t y) 
        {
            y_ = y;
            return *this;
        }

    private:
        Matrix& matrix_;
        size_t x_;
        size_t y_;
    };

    class Iterator
    {
    public:
        Iterator(Matrix& m, iterator it)
            : m_(m),
              it_(it)
        { }

        Iterator& operator++()
        {
            ++it_;
            return *this;
        }

        Iterator& operator=(const Iterator& other)
        {
            it_ = other.it_;
            return *this;
        }

        bool operator!=(const Iterator& other) const
        {
            return it_ != other.it_;
        }

        std::tuple<size_t, size_t, T> operator*() const
        {
            auto [x, y] = it_->first;
            return std::make_tuple(x, y, it_->second);
        }

    private:
        Matrix& m_;
        iterator it_;
    };

    Proxy operator[](size_t x) {
        return Proxy(*this, x);
    }

    size_t size()
    {
        return values_.size();
    }

    Iterator begin()
    {
        return Iterator(*this, values_.begin());
    }

    Iterator end()
    {
        return Iterator(*this, values_.end());
    }

    private:
        std::unordered_map<std::pair<size_t, size_t>, T, PairHash, KeyEqual> values_;
};