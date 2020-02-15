/*
 * Template for a vector-like object that is lock protected.
 * Implements deferred locking that is thread safe and follows the rule of three
 *
 * Author: Thomas Maher
 * Version: C++11
 * Modified: 2/15/2020
 *
*/

#include <thread>
#include <mutex>

#ifndef LOCKED_CLASS_HPP
#define LOCKED_CLASS_HPP

template <typename T>
class LockableClass {
  private:
    
    mutable std::mutex the_mutex;

    T* data;
    std::size_t size;


  public:
    
    LockableClass() : data(nullptr), size(0) {}

    LockableClass(std::size_t reserved) : size(reserved) {
      /**
       * Parameterized constructor
       */
      data = new T[size];

      std::fill(data, data+size, T(size));
    }

    LockableClass(const LockableClass& copy) {
      /**
       * Copy constructor
       */
      std::unique_lock<std::mutex> copy_lock(copy.the_mutex);

      // Now we can copy since the object is locked
      size = copy.size;
      data = size ? new T[size] : nullptr;
      std::copy(copy.data, copy.data + copy.size, data);

      // Don't need to call copy_lock.unlock because it gets called
      // automatically when copy_lock goes out of scope
    }

    ~LockableClass() {
      /**
       * Deconstructor
       */
      delete [] data;
    }

    LockableClass& operator=(const LockableClass& copy) {
      /**
       * Copy assignment operator
       *
       * param copy const LockableCLass&
       *    The object to assign values based on
       *
       * return LockableClass&
       *    Return assigned object
       */
      std::unique_lock<std::mutex> this_lock(the_mutex, std::defer_lock);
      std::unique_lock<std::mutex> copy_lock(copy.the_mutex, std::defer_lock);

      // Lock both unique_locks, no deadlock guarentee
      std::lock(this_lock, copy_lock);

      // Assign object now
      if(this != &copy) {
        delete data;
        size = copy.size;
        data = size ? new T[size] : nullptr;
        for(std::size_t i=0; i<size; ++i)
          data[i] = copy.data[i];
      }

      // Don't need to call unlock on unique_locks because they get called
      // automatically when the locks go out of scope

      return *this;
    }

    std::size_t getSize() {
      /**
       * Gets the number of data objects stored
       *
       * return bool 
       *    Returns the size of the data array   
       */
      std::size_t rv;

      the_mutex.lock();
      rv = size;
      the_mutex.unlock();

      return rv;
    }

    T get(std::size_t pos) {
      /**
       * Gets the value at the position pos
       *
       * param pos std::size_t 
       *    The position to get the value from
       *
       * return T 
       *    Returns the object at the given location
       */
      T rv;

      std::unique_lock<std::mutex> this_lock(the_mutex);
      rv = data[pos];

      return rv;
    }

    bool set(std::size_t pos, T val) {
      /**
       * Sets the value at position pos to the value val
       *
       * param pos std::size_t 
       *    Position to change/set value of
       * param val T 
       *    Value to change/set value to
       *
       * return bool
       *    Returns if the value was set or not
       */
      if(pos >= size) // If position is out of range
        return false;
    
      std::unique_lock<std::mutex> this_lock(the_mutex);
      data[pos] = val;

      return true;
    }
};


#endif
