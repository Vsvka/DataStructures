
//libraries
#include <iostream>
#include <stdexcept>

using namespace std;


//code for part 1
template<class T>
class Queue {
    
    struct N { T d; N* n; N(T v):d(v),n(nullptr){} };
    N *f=nullptr, *t=nullptr;

public:

    ~Queue(){ while(f){ N* x=f; f=f->n; delete x; } }
    bool empty() const { return !f; }

    void push(T v){
        N* x = new N(v);
        if (!t) f = t = x;
        else { t->n = x; t = x; }
    }

    void pop(){
        if (empty()) throw runtime_error("Queue empty");
        N* x = f;
        f = f->n;
        if (!f) t = nullptr;
        delete x;
    }

    T& front(){
        if (empty()) throw runtime_error("Queue empty");
        return f->d;
    }
};


//code for part 2
template<class T>
class Quack {

    struct N { T d; N *p,*n; N(T v):d(v),p(nullptr),n(nullptr){} };
    N *f=nullptr, *t=nullptr;

public:

    ~Quack(){ while(f){ N* x=f; f=f->n; delete x; } }
    bool empty() const { return !f; }

    void push_front(T v){
        N* x = new N(v);
        x->n = f;
        if (f) f->p = x;
        else   t = x;
        f = x;
    }

    void push_back(T v){
        N* x = new N(v);
        x->p = t;
        if (t) t->n = x;
        else   f = x;
        t = x;
    }

    void pop_front(){
        if (empty()) throw runtime_error("Quack empty");
        N* x = f;
        f = f->n;
        if (f) f->p = nullptr;
        else   t = nullptr;
        delete x;
    }

    void pop_back(){
        if (empty()) throw runtime_error("Quack empty");
        N* x = t;
        t = t->p;
        if (t) t->n = nullptr;
        else   f = nullptr;
        delete x;
    }

    T& front(){
        if (empty()) throw runtime_error("Quack empty");
        return f->d;
    }
    T& back(){
        if (empty()) throw runtime_error("Quack empty");
        return t->d;
    }
};

//main(for output)
int main() {

    Queue<int> que;
    que.push(15); que.push(23); que.push(42);

    cout << "Fifo queue: ";
    while (!que.empty()) {
        cout << que.front() << " ";
        que.pop();
    }
    cout << "\n";

    Quack<string> dendque;
    dendque.push_back("world");
    dendque.push_front("hello");
    dendque.push_back("!");

    cout << "Quack front: " << dendque.front()
              << ", back: " << dendque.back() << "\n";

    dendque.pop_front();
    cout << "Pop_front, front: " << dendque.front() << "\n";

    dendque.pop_back();
    cout << "Pop_back, back: " << dendque.front() << "\n";

    return 0;
}
