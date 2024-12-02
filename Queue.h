//
// Created by hussa on 3/4/2024.
//
#include "iostream"
template<class T>
class Queue{
    T* arr;
    int sizeq;
public:
    class Iterator;
    class ConstIterator;
    class EmptyQueue{};
    Iterator begin();
    Iterator end();
    ConstIterator begin() const;
    ConstIterator end() const;
    Queue()
    {
        try {
            arr = new T[1];
        }
        catch (const std::bad_alloc& b)
        {
            throw;
        }
        this->sizeq=1;
    }
    Queue(const Queue& q1)
    {
        try {

            this->arr = new T[q1.sizeq];
        }
        catch (const std::bad_alloc& b)
        {
            throw;
        }
        for (int i = 0; i < q1.sizeq -1; ++i) {
            this->arr[i]=q1.arr[i];
        }
        this->sizeq=q1.sizeq;
    }
    Queue& operator=(const Queue& q1)
    {
        T *tmp;
        if(this==&q1)
        {
            return *this;
        }
        try {
            tmp= new T[q1.sizeq];
        }
        catch (const std::bad_alloc& b)
        {
            throw;
        }
        for (int i = 0; i < q1.sizeq - 1; ++i) {
            tmp[i]=q1.arr[i];
        }
        delete []this->arr;
        this->sizeq=q1.sizeq;
        this->arr=tmp;
        return *this;
    }
    ~Queue()
    {
        delete[]this->arr;
    }
    void pushBack(T object)
    {
        T *tmp;

        this->sizeq++;
        try {
            tmp = new T[this->sizeq];
        }
        catch (const std::bad_alloc& b)
        {
            throw;
        }
        for (int i = 0; i <this->sizeq-2 ; ++i) {
            tmp[i]=this->arr[i];
        }
        tmp[this->sizeq-2]=object;
        delete[]this->arr;
        this->arr=tmp;
    }
    T& front()
    {
        if(this->sizeq==1)
        {
            throw EmptyQueue();
        }
        return this->arr[0];
    }
    const T& front() const
    {
        if (this->sizeq == 1)
        {
            throw EmptyQueue();
        }
        return this->arr[0];
    }
    void popFront()
    {
        if(this->sizeq==1)
        {
            throw EmptyQueue();
        }
        T *tmp;
        try {
            tmp = new T[this->sizeq-1];
        }
        catch (const std::bad_alloc& b)
        {
            throw;
        }
        this->sizeq--;
        for (int i = 0; i <this->sizeq-1 ; ++i) {
            tmp[i]=this->arr[i+1];
        }
        delete[] this->arr;
        this->arr=tmp;
    }
    int size()const{
        return this->sizeq-1;
    }
};
template<class T>
typename Queue<T>::ConstIterator Queue<T>::begin() const {
    return ConstIterator(this,0);
}
template<class T>
typename Queue<T>::ConstIterator Queue<T>::end() const  {
    return ConstIterator(this,this->sizeq-1);
}
template<class T>
typename Queue<T>::Iterator Queue<T>::begin(){
    return Iterator(this,0);
}
template<class T>
typename Queue<T>::Iterator Queue<T>::end()  {
    return Iterator(this,this->sizeq-1);
}


template<class S, typename D>
Queue<S> filter(Queue<S>& q1, D theFunction ) {
    Queue<S> tmp;
    for (S& object:q1) {
        if (theFunction(object)) {
            tmp.pushBack(object);
        }
    }
    return tmp;
}
template<class S, typename D>
 Queue<S> filter(const Queue<S>& q1, D theFunction) {
    Queue<S> tmp;
    for ( typename Queue<S>::ConstIterator it = q1.begin() ; it != q1.end();  ++it )
    {
        if (theFunction(*it)) {
            tmp.pushBack(*it);
        }
    }
    return tmp;
}
template<class T, typename S>
void transform(Queue<T> &q1,S theFunction)
{
    Queue<T> tmp = Queue<T>();
    for (T& object:q1)
    {
        tmp.pushBack(theFunction(object));
    }
    q1 = tmp;

}
template<class M,class S, typename D>
S reduce(const Queue<M> q, S first, D theFunction)
{
    // check size

    for (M object:q)
    {
         first =theFunction(first,object);
    }

    return first;
}





template<class T>
class Queue<T>::Iterator {
    Queue<T> *q1;
    int index;
    Iterator(Queue<T> *q1, int index);
    friend class Queue<T>;
public:
    bool operator!=(Queue<T>::Iterator& it)const;
    Iterator operator++(int);
    T& operator*() const;
    Iterator& operator++();
    class InvalidOperation{};
};
template<class T>
Queue<T>::Iterator::Iterator(Queue<T> *q1, int index) {
    this->q1=q1;
    this->index=index;

}
template<class T>
bool Queue<T>::Iterator::operator!=( Queue<T>::Iterator& it) const {

    if(this->q1 != it.q1)
    {
        return true;
    }
    if(this->index != it.index){
        return true;
    }
    return false;
}
template<class T>
typename Queue<T>::Iterator& Queue<T>::Iterator::operator++(){
    if (this->index == q1->sizeq - 1) {
        throw InvalidOperation();
    }

    ++this->index;
    return *this;
}
template<class T>
typename Queue<T>::Iterator Queue<T>::Iterator::operator++(int)
{
    Queue<T>::Iterator result=*this;
    ++*this;
    return result;
}
template<class T>
 T& Queue<T>::Iterator::operator*() const{
    return q1->arr[this->index];
}



template<class T>
class Queue<T>::ConstIterator {
    const Queue<T>* q1;
    int index;
    ConstIterator(const Queue<T> *q1, int index);
    friend class Queue<T>;
public:
    bool operator!=(const Queue<T>::ConstIterator& it)const;
    ConstIterator operator++(int);
    T& operator*() const;
    ConstIterator& operator++();
    class InvalidOperation{};
};
template<class T>
Queue<T>::ConstIterator::ConstIterator(const Queue<T> *q1, int index)  {
    this->q1=q1;
    this->index=index;

}
template<class T>
bool Queue<T>::ConstIterator::operator!=(const Queue<T>::ConstIterator& it) const {

    if(this->q1 != it.q1)
    {
        return true;
    }
    if(this->index != it.index){
        return true;
    }
    return false;
}
template<class T>
typename Queue<T>::ConstIterator& Queue<T>::ConstIterator::operator++(){
    if (this->index == q1->sizeq - 1) {
        throw InvalidOperation();
    }

    ++this->index;
    return *this;
}
template<class T>
typename Queue<T>::ConstIterator Queue<T>::ConstIterator::operator++(int)
{
    Queue<T>::ConstIterator result=*this;
    ++*this;
    return result;
}
template<class T>
// changed to const refrence!
T& Queue<T>::ConstIterator::operator*() const{
    return q1->arr[this->index];
}