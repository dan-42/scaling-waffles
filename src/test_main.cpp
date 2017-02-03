/*
    Copyright 2013 Adobe Systems Incorporated
    Distributed under the MIT License (see license at
    http://stlab.adobe.com/licenses.html)

    This file is intended as example code and is not production quality.
*/

#include <cassert>
#include <memory>
#include <vector>

using namespace std;

/******************************************************************************/
// Library

template <typename T>
void draw(const T& x, ostream& out, size_t position)
{ out << string(position, ' ') << x << endl; }

class object_t {
  public:
    template <typename T>
    object_t(T x) : self_(make_unique<model<T>>(move(x)))
    { std::cout << "ctor" << std::endl; }

    object_t(const object_t& x) : self_(x.self_->copy_())
    {
      std::cout << "ctor copy" << std::endl;

    }
    object_t(object_t&&) noexcept = default;

    object_t& operator=(const object_t& x)
    { object_t tmp(x); *this = move(tmp); return *this;

      std::cout << "copy assign" << std::endl;
    }
    object_t& operator=(object_t&&) noexcept = default;

    friend void draw(const object_t& x, ostream& out, size_t position)
    { x.self_->draw_(out, position); }

  private:
    struct concept_t {
        virtual ~concept_t() = default;
        virtual unique_ptr<concept_t> copy_() const = 0;
        virtual void draw_(ostream&, size_t) const = 0;
    };
    template <typename T>
    struct model final : concept_t {
        model(T x) : data_(move(x)) { }
        unique_ptr<concept_t> copy_() const override { return make_unique<model>(*this); }
        void draw_(ostream& out, size_t position) const
        { draw(data_, out, position); }

        T data_;
    };

   unique_ptr<const concept_t> self_;
};

using document_t = vector<object_t>;

void draw(const document_t& x, ostream& out, size_t position)
{
    out << string(position, ' ') << "<document>" << endl;
    for (auto& e : x) draw(e, out, position + 2);
    out << string(position, ' ') << "</document>" << endl;
}

using history_t = vector<document_t>;

void commit(history_t& x) { assert(x.size()); x.push_back(x.back()); }
void undo(history_t& x) { assert(x.size()); x.pop_back(); }
document_t& current(history_t& x) { assert(x.size()); return x.back(); }

/******************************************************************************/
// Client

class my_class_t {
    /* ... */
};

void draw(const my_class_t&, ostream& out, size_t position)
{ out << string(position, ' ') << "my_class_t" << endl; }

int main()
{
    history_t h(1);

    cout << "EMPLACE()--------------------------" << endl;
    current(h).emplace_back(0);
    current(h).emplace_back(string("Hello!"));

    cout << "DRAW()--------------------------" << endl;
    draw(current(h), cout, 0);
    cout << "--------------------------" << endl;

    cout << "COMMIT()--------------------------" << endl;
    commit(h);

    cout << "EMPLACE()--------------------------" << endl;
    current(h).emplace_back(current(h));
    current(h).emplace_back(my_class_t());
    current(h)[1] = string("World");

    cout << "DRAW()--------------------------" << endl;
    draw(current(h), cout, 0);
    cout << "--------------------------" << endl;

    undo(h);

    draw(current(h), cout, 0);
}
