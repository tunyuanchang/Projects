#include "function.h"
//#include "11410.h"

namespace oj{
    Vector::Vector(){ //constructor
        begin_ = new Int[0];
        last_ = end_ = begin_;
    }
    Vector::size_type Vector::capacity() const{
        return end_ - begin_;
    }
    Vector::size_type Vector::size() const{
        return last_ - begin_;
    }
    void Vector::pop_back(){
        if(size() > 0) last_--;
    }
    void Vector::push_back(value_type val){
        size_type old_cap = capacity(), new_cap;
        if(size() == old_cap){
            new_cap = (old_cap + 1 < old_cap * 3) ? old_cap * 3 : old_cap + 1 ;
            reserve(new_cap);
        }
        (*last_) = val;
        last_++;
    }
    void Vector::insert(size_type pos,size_type count,value_type val){
        size_type old_cap = capacity(), new_cap;
        if(size() + count > capacity()){
            new_cap = old_cap + ((count < old_cap / 2) ? old_cap / 2 : count);
            reserve(new_cap);
        }
        resize(size() + count);
        for(size_type i = pos + count ; i < size() ; i++)
            begin_[i] = begin_[i - count];
        for(size_type i = pos ; i < pos + count ; i++)
            begin_[i] = val;
    }
		
    void Vector::reserve(size_type new_capacity){
        if(new_capacity <= capacity()) return;
        size_type sz = size();
        pointer new_begin_ = new value_type[new_capacity];
        for(size_type i = 0 ; i < sz ; i++)
            new_begin_[i] = begin_[i];
        delete [] begin_;
        begin_ = new_begin_;
        last_ = new_begin_ + sz;
        end_ = new_begin_ + new_capacity;
        return;
    }
    void Vector::resize(size_type new_size){
        if(new_size > size()){
            reserve(new_size);
            for(int i = size() ; i < new_size ; i++){
                begin_[i] = 0;
            }
        }
		last_ = begin_ + new_size;
        return;
    }
    Vector::~Vector(){
        delete [] begin_;
    }
}