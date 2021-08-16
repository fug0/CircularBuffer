#pragma once

template <class T>
class _circularBuffer 
{
public:
    typedef T value_type;
    typedef T& reference;
    typedef const T& const_reference;
    typedef size_t size_type;

    explicit _circularBuffer(size_t capacity = 100) : cb_array(new T[capacity]), cb_array_size(capacity), cb_head(0), cb_tail(0), cb_contents_size(0) {}

    ~_circularBuffer()
    {
        delete[] cb_array;
    }

    reference front()
    {
        return cb_array[cb_head];
    }
    reference back()
    {
        return cb_array[cb_tail];
    }
    const_reference front() const
    {
        return cb_array[cb_head];
    }
    const_reference back() const
    {
        return cb_array[cb_tail];
    }

    void clear()
    {
        cb_head = cb_tail = cb_contents_size = 0;
    }

    void push_back(const value_type& item) {
        if (!cb_contents_size) {
            cb_array[cb_head] = item;
            cb_tail = cb_head;
            ++cb_contents_size;
        }
        else if (cb_contents_size != cb_array_size)
        {
            ++cb_tail;
            ++cb_contents_size;
            if (cb_tail == cb_array_size) { cb_tail = 0; }

            cb_array[cb_tail] = item;
        }
        else {
            if (cb_contents_size != 0)
            {
                ++cb_head;
                --cb_contents_size;
                if (cb_head == cb_array_size) { cb_head = 0; }
            }

            ++cb_tail;
            ++cb_contents_size;
            if (cb_tail == cb_array_size) { cb_tail = 0; }

            cb_array[cb_tail] = item;
        }
    }

    void pop_front()
    {
        if (cb_contents_size != 0)
        {
            ++cb_head;
            --cb_contents_size;
            if (cb_head == cb_array_size) { cb_head = 0; }
        }
    }

    size_type size() const
    {
        return cb_contents_size;
    };
    size_type capacity() const
    {
        return cb_array_size;
    };

    bool is_empty() const
    {
        if (cb_contents_size == 0) { return true; }
        return false;
    }
    bool is_full() const
    {
        if (cb_contents_size == cb_array_size) { return true; }
        return false;
    }

    size_type max_size() const
    {
        return size_type(-1) / sizeof(value_type);
    }
private:
    value_type* cb_array;
    size_type  cb_array_size;
    size_type  cb_head;
    size_type  cb_tail;
    size_type  cb_contents_size;
};