  
/**
 * TODO: Complete this class!
 */

/// Your welcome
#include <assert.h>
#include <iostream>
#include <string>
#include <cstdio>

//
template <typename T>
class MyVector
{
	public:
		
		/*******************
		 * Static constants
		 ******************/
		
		/// Default capacity
		static constexpr size_t DEFAULT_CAPACITY = 64;
		
		/// Minimum capacity
		static constexpr size_t MINIMUM_CAPACITY = 8;
		
		/*****************************
		 * Constructors / Destructors
		 ****************************/
		
		/// Normal constructor
		MyVector(size_t capacity = MyVector::DEFAULT_CAPACITY) {
			if (capacity < MyVector::MINIMUM_CAPACITY)
			{
				capacity = MyVector::MINIMUM_CAPACITY;
			}
			this->elements_ = new T[capacity];
			this->capacity_ = capacity;
			this->size_ = 0;
 
			// TODO: Your code here
		}
		
		/// Copy constructor
		MyVector(const MyVector& other) {
			if (this != &other)
			{
				delete[] this->elements_;
				this->elements_ = new T[other.capacity()];
				for(size_t i = 0; i < other.size_; i++)
				{
					this->elements_[i] = other.at(i);
				}
				this->capacity_ = other.capacity();
				this->size_ = other.size();
			}
			// TODO: Your code here
		}
		
		/**
		 * Destructor
		 * Should call clear() so each element gets its destructor called.
		 * Then, de-allocate the internal array and make it a nullptr, if its not already a nullptr.
		 */
		~MyVector() {
			this->clear();
			if (this->elements_ != nullptr)
			{
				delete[] this->elements_;
			    this->elements_ = nullptr;
			}
			// TODO: Your code here
		}
		
		/************
		 * Operators
		 ************/
		
		///	Assignment operator
		MyVector& operator=(const MyVector& rhs) 
		{
		     
		    if (this != &rhs)
			{
				clear();
				copyOther(rhs);
			}
			return *this;
			// TODO: Your code here
		}
		
		/// Operator overload to at()
		T& operator[](size_t index) const 
		{
		    if (index >= 0 && index < this->size_)
		    {
			    return this->elements_[index];
			}
			else
			{
                throw std::out_of_range("Index out of range");
            }
			// TODO: Your code here
		}
		
		/************
		 * Accessors
		 ************/
		
		/// Return the number of valid elements in our data
		size_t size() const {
			return this->size_;
			// TODO: Your code here
		}
		
		/// Return the capacity of our internal array
		size_t capacity() const {
			return this->capacity_;
			// TODO: Your code here
		}
		
		/**
		 * Check whether our vector is empty
		 * Return true if we have zero elements in our array (regardless of capacity)
		 * Otherwise, return false
		 */
		bool empty() const {
			if (this->size_ == 0)
            {
                return true;
            }
            return false;
			// TODO: Your code here
		}
		
		/// Return a reference to the element at an index
		T& at(size_t index) const {
		    if (index >= 0 && index < this->size_)
		    {
			    return this->elements_[index];
			}
			else
			{
                throw std::out_of_range("Index out of range");
            }
		 
			
			// TODO: Your code here
		}
		
		/***********
		 * Mutators
		 ***********/
		
		/**
		 * Reserve capacity in advance, if our capacity isn't currently large enough.
		 * Useful if we know we're about to add a large number of elements, and we'd like to avoid the overhead of many internal changes to capacity.
		 */
		void reserve(size_t capacity) {
			 if (capacity > this->capacity_)
			 {
				changeCapacity(capacity);
			 }
			// TODO: Your code here
		}
		
		/**
		 * Set an element at an index.
		 * Throws range error if outside the size boundary.
		 * Returns a reference to the newly set element (not the original)
		 */
		T& set(size_t index, const T& element) 
        {
            if (index >= this->size_)
            {
                throw std::out_of_range("Index out of range: cannot set");
            }
            this->elements_[index].~T(); //calling destructor for old element 
            new (&this->elements_[index]) T(element); //copy construct to overwrite the old element
            return this->elements_[index];
			// TODO: Your code here
		}
		
		/**
		 * Add an element onto the end of our vector, increasing the size by 1
		 * Should rely on the insert() function to avoid repeating code.
		 * Returns a reference to the newly inserted element
		 */
		T& push_back(const T& element) {
		    return insert(this->size_, element);
			// TODO: Your code here
		}
		
		/**
		 * Remove the last element in our vector, decreasing the size by 1
		 * Should rely on the erase() function to avoid repeating code.
		 * Returns the new size.
		 */
		size_t pop_back() {
		
		    if (this->size_ == 0)
		    {
		      throw std::out_of_range("Index out of range: cannot insert"); 
            
		    }
 
			return erase(this->size_ - 1);
			// TODO: Your code here
		}
		
		/**
		 * Insert an element at some index in our vector, increasing the size by 1
		 * 
		 * Scoot all elements at index and beyond, one to the right. This
		 * makes a "hole" available at the index, where you can then place
		 * the new element.
		 * 
		 * Returns a reference to the newly added element (not the original).
		 */
		T& insert(size_t index, const T& element) {

			if (index < 0 || index > this->size_)
            {
                throw std::out_of_range("Index out of range: cannot insert"); 
            }
		    
			if(this->size_ == this->capacity_)
			{
				// If the capacity is reached, double it
                reserve(this->capacity_*2);
			}

			for (size_t i = this->size_; i > index; i--) 
			{
				this->elements_[i] = this->elements_[i - 1];
			}
			
			this->elements_[index] = element;

			this->size_++;

			return this->elements_[index];
			// TODO: Your code here
		}
		
		/**
		 * Erase one element in our vector at the specified index, decreasing the size by 1.
		 * 
		 * This means you'd then have to scoot elements to the left to fill the "hole"
		 * 	left by the erased element.
		 * 
		 * Throws std::range_error if the index is out of bounds.
		 * 
		 * Calls the erased element's destructor.
		 * 
		 * Returns the new size.
		 */
		size_t erase(size_t index) 
		{
 
		    if (this->size_ == 0)
		    {
		        throw std::out_of_range("Index out of range: cannot erase");
		    }
		    
			if  (index >= this->size_)
            {
                throw std::out_of_range("Index out of range: cannot erase");
            }
            
            if (this->size_ == 1)
		    {
		        this->size_ = 0;
		        return 0;
		    }
 
			this->elements_[index].~T();

 			for (size_t i = index; i < this->size_ - 1; i++) 
			{
				this->elements_[i] = this->elements_[i + 1];
			}

			this->size_--;
			
			if (this->size_ < this->capacity_/3)
			{
				changeCapacity(this->capacity_/2);
			}

            return this->size_;
			// TODO: Your code here
		}
		
		/**
		 * Calls each element's destructor, then clears our internal
		 * data by setting size to zero and resetting the capacity.
		*/
		void clear() {
			for (size_t i = 0; i < this->size_;  i++) //going through each elements destructor 
			{
				this->elements_[i].~T();  //calls destructor for type T
			}
			 
			this->size_ = 0; //sets size to 0
 
			// TODO: Your code here
		}
	
	/**
	 * Begin private members and methods.
	 * Private methods can often contain useful helper functions,
	 * or functions to reduce repeated code.
	*/
	private:
		
		/// Number of valid elements currently in our vector
		size_t size_ = 0;
		
		/// Capacity of our vector; The actual size of our internal array
		size_t capacity_ = 0;
		
		/**
		 * Our internal array of elements of type T.
		 * Starts off as a null pointer.
		 */
		T* elements_ = nullptr;
		
		/**
		 * Helper function that is called whenever we need to change the capacity of our vector
		 * Should throw std::range_error when asked to change to a capacity that cannot hold our existing elements.
		 * It's probably a good idea to make an additional helper function that decides
		 * 	whether to change capacity at all (and to what new capacity), that your public functions can rely upon.
		 */
		void changeCapacity(size_t c) {
			if ( c >= this->size_ )
			{
				T* new_array = new T[c];
				for (size_t i = 0; i <= this->size_ - 1; i++)
				{
					new_array[i] = this->elements_[i];
				}
				delete [] this->elements_;
				this->elements_ = new_array;
				this->capacity_ = c;
			}
			// TODO: Your code here
		}
		
		/**
		 * Copy another vector's elements into our own, by value.
		 * Does not simply copy the other vector's array's pointer
		 * Does not care about matching the capacity exactly.
		 * This is a helper function relied upon by the copy constructor and the assignment operator,
		 * 	to avoid repeated code.
		 * 
		 * You will probably want to make additional helper functions to make this one easier.
		 * Here is a suggested strategy for copying the internal array:
		 * 1. Deallocate the current array for 'this' (if it is already allocated)
		 * 2. Allocate a new array for 'this' of the appropriate size
		 * 3. Use a loop to copy elements one-by-one (by value)
		 * 4. Copy other relevant properties from the 'other' to 'this'
		 */
		void copyOther(const MyVector& other) {
			
			if (this->elements_ != nullptr)
			{
				delete[] this->elements_;
			}

			this->capacity_ = other.capacity_;
			this->size_ = other.size_;
			this->elements_ = new T[this->capacity_];

			for (size_t i = 0; i < this->size_; i++)
			{
				this->elements_[i] = other.elements_[i];
  		    }

			// TODO: Your code here
		}
};
