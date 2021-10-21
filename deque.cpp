#include <iostream>
using namespace std;

const int default_size = 10;

template <typename T>
struct Deque_iterator {
    T** node;
    T* cur;
    T* first;
    T* last;


    Deque_iterator() : cur(0), first(0), last(0), node(0) {}
    Deque_iterator(const Deque_iterator<T>& d) : cur(d.cur), first(d.first), last(d.last), node(d.node) {}
    void set_node(T** n) {
        first = *n;
        last = first + default_size;
        node = n;
    } 
    T& operator*() {
        return *cur;
    }
    T* operator->() {
        return &(*operator*());
    }
    size_t operator-(const Deque_iterator<T>& x) {
        return default_size * (node - x.node) + (cur - first) + (x.last - x.cur);
    }
    Deque_iterator<T>& operator++() {
        ++cur;
        if (cur == last) {
            set_node(node + 1);
            cur = first;
        }
        return *this;
    }
    Deque_iterator<T> operator++(int) {
        Deque_iterator<int> tmp = *this;
        ++(*this);
        return tmp;
    }
    Deque_iterator<T>& operator--() {
        if (cur == first) {
            set_node(node - 1);
            cur = last;
        }
        --cur;
        return *this;
    }
    Deque_iterator<T> operator--(int) {
        Deque_iterator<int> tmp = *this;
        --(*this);
        return tmp;
    }

    void operator=(const Deque_iterator<T>& d) {
        cur = d.cur;
        first = d.first;
        last = d.last;
        node = d.node;
    }

};

template <typename T>
class Deque {
    typedef Deque_iterator<T> iterator;
private:
    T** map;
    iterator start;
    iterator finish;
    size_t map_size;

    
    void push_front_aux(const T& v) {
        NeedExtend();
        T** tmp = start.node - 1;
        *tmp = new T[default_size];
        start.set_node(tmp);
        start.cur = start.last - 1;
        *start = v;
    }
    void push_back_aux(const T& v) {
        *finish = v;
        NeedExtend();
        T** tmp = finish.node + 1;
        *tmp = new T[default_size];
        finish.set_node(tmp);
        finish.cur = finish.first;
    }

    void __display() {
        iterator tmp = start;
        while (tmp.cur != finish.cur) {
            cout << *tmp++ << ' ';
        }
    }
public:
    Deque() {
        map_size = default_size;
        map = new T*[map_size];
        T** tmp = map + (map_size >> 1);
        *tmp = new T[default_size];
        start.set_node(tmp);
        finish.set_node(tmp);
        start.cur = finish.cur = start.first;
    }
    iterator begin() { return start; }
    iterator end() { return finish; }
    T& front() { return *start; }
    T& back() {
        iterator tmp = finish;
        --finish;
        return *tmp;
    }


    void NeedExtend() {
        if (start.node == map || finish.node == map + map_size - 1) {
            map_size <<= 1;
            size_t offset_start = start.cur - start.first;
            size_t offset_finish = finish.cur - finish.first;
            T** new_map = new T*[map_size];
            size_t old_size = finish.node - start.node;
            T** n_start = new_map + ((map_size - old_size) >> 1);
            T** tmp = n_start;
            T** former_node = start.node;
            while (former_node <= finish.node) {
                *tmp++ = *former_node++;
            }
            start.set_node(n_start);
            finish.set_node(start.node + old_size);
            start.cur = start.first + offset_start;
            finish.cur = finish.first + offset_finish;
            delete[] map;
            map = new_map;
        }
    }
    void push_front(const T& v) {
        if (start.cur != start.first) {
            //有剩余空间
            --start.cur;
            *start = v;
        } else {
            push_front_aux(v);
        }
    }

    void push_back(const T& v) {
        if (finish.cur + 1 < finish.last) {
            *finish = v;
            finish++;
        } else {
            push_back_aux(v);
        }
    }

    void display() {
        __display();
    }

};

int main() {
    Deque<int> d;
    d.push_front(3);
    for (int i = 0; i < 20; i++)
        d.push_back(i);
    for (int i = 0; i < 20; i++)
        d.push_front(i);
    d.push_back(44);
    d.display();
    return 0;
}