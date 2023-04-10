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

        T& operator[](size_t y) 
        {
            CheckTempObj();
            auto key = std::pair(x_, y);
            matrix_.curElOut_ = matrix_.values_.find(key);
            if(matrix_.curElOut_ == matrix_.values_.end())
            {
                matrix_.tempObj_.first = key;
                matrix_.tempObj_.second = DefaultValue;
                matrix_.curElOut_ = matrix_.values_.end();
                return matrix_.tempObj_.second;
            }
            return matrix_.curElOut_->second;
        }

        void CheckTempObj()
        {
            if(matrix_.tempObj_.second != DefaultValue) // Добавление
            {
                // Добавление, если значение выданной ячейки из Proxy::operator[] изменилось
                auto& [key, val] = matrix_.tempObj_;
                matrix_.values_[key] = std::move(val);
                matrix_.tempObj_.second = DefaultValue;
                matrix_.size_++;
            }
            else if(matrix_.curElOut_ != matrix_.values_.end()) 
            {
                // Удаление, если на предыдущем шаге элементу присвоили значение по умолчанию
                auto& [key, val] = *matrix_.curElOut_;
                if(val == DefaultValue)
                {
                    matrix_.values_.erase(matrix_.curElOut_);
                    matrix_.size_--;
                    matrix_.curElOut_ = matrix_.values_.end();
                }           
            }
        }

    private:
        Matrix& matrix_;
        size_t x_;
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
        Proxy(*this, 0).CheckTempObj();
        return size_;
    }

    Iterator begin()
    {
        Proxy(*this, 0).CheckTempObj();
        return Iterator(*this, values_.begin());
    }

    Iterator end()
    {
        Proxy(*this, 0).CheckTempObj();
        return Iterator(*this, values_.end());
    }

    private:
        std::unordered_map<std::pair<size_t, size_t>, T, PairHash, KeyEqual> values_;
        size_t size_{0};

         // Хранит x, y, T от предыдущего вызова T& operator[](size_t y) 
        std::pair<std::pair<size_t,size_t>, T> tempObj_{std::pair<size_t, size_t>(0,0), DefaultValue};
        iterator curElOut_;
};