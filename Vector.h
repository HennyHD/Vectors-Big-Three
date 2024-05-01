#pragma once
#include <iostream>
using namespace std;
namespace Vector
{
	template<typename T>
	class vector
	{
	public:
		//constructors
		vector() : sz{ 0 }, elem{ nullptr }, space{ 0 } {}
		//prevents vector<int> v = 5;
		explicit vector(size_t s) : sz{ s }, elem{ new T[s] }, space{ s } {}
		// copy constructor
		vector(const vector&);
		// copy assignment
		vector& operator=(const vector&);
		// destructor
		~vector() { delete[] elem; cout << "Destructor called" << endl; }
		// checked access
		T& at(size_t n);
		// checked access
		const T& at(size_t n) const;
		// unchecked access
		T& operator[](size_t n);
		// unchecked access
		const T& operator[](size_t n) const;
		// the current size
		size_t size() const { return sz; };
		// grow
		void resize(size_t newsize);
		// add element
		void push_back(T d);
		// get more space
		void reserve(size_t newalloc);
		// current available space
		int capacity() const { return space; }

	private:
		size_t sz;
		T* elem;
		size_t space;
	};

	template<typename T>
	T& vector<T>::operator[](size_t n)
	{
		return elem[n];
	}

	struct out_of_range_ {};

	template<typename T>
	const T& vector<T>::operator[](size_t n) const
	{
		return elem[n];
	}

	template<typename T>
	const T& vector<T>::at(size_t n) const
	{
		if (n < 0 || n >= sz) throw out_of_range_();
		return elem[n];
	}

	template<typename T>
	T& vector<T>::at(size_t n)
	{
		if (n < 0 || n >= sz) throw out_of_range_();
		return elem[n];
	}

	template<typename T>  //copy constructor, object to object
	vector<T>::vector(const vector<T>& a)
		: sz{ a.sz }, elem{ new T[a.sz] }, space{ a.sz }
	{
		cout << "Copy constructor" << endl;
		for (size_t i = 0; i < sz; i++) elem[i] = a.elem[i];
	}

	template<typename T> //copy assignment
	vector<T>& vector<T>::operator=(const vector<T>& a)
	{
		cout << "Copy assignment" << endl;
		if (this == &a) return *this; //check if it's the same value
		if (space >= a.sz) //check if we have room in space
		{
			for (size_t i = 0; i < a.sz; i++) elem[i] = a.elem[i];
			sz = a.sz;
			return *this;
		}
		//else if we had no room in space.  We will create a larger space and move the elements over to a new heap.
		T* p = new T[a.sz];
		for (size_t i = 0; i < a.sz; i++) p[i] = a.elem[i];
		delete[] elem;
		sz = a.sz;
		space = a.sz;
		elem = p;
		return *this;
	}

	template<typename T> //increase size and transfer elements over.  Meaning we can use pushbacks then the previous function will be called if space is maxed out.
	void vector<T>::reserve(size_t newalloc)
	{
		if (newalloc <= space) return;
		T* p = new T[newalloc];
		for (size_t i = 0; i < sz; i++) p[i] = elem[i];
		delete[] elem;
		elem = p;
		space = newalloc;
	}

	template<typename T>  //the increased size on the heap for reserve also means that the new space is not initialized to 0 or another number.  We will do that here with resize.
	void vector<T>::resize(size_t newsize)
	{
		reserve(newsize);
		for (size_t i = sz; i < newsize; i++) elem[i] = T();
		sz = newsize;
	}

	template<typename T>
	void vector<T>::push_back(T d)
	{
		if (sz == 0) reserve(8);  //if size is empty, reserve empty
		else if (sz == space) reserve(2 * space);  //double space if space is full
		elem[sz] = d;
		++sz;
	}

	template<typename T>
	ostream& operator<<(ostream& os, const vector<T>& v)
	{
		for (size_t i = 0; i < v.size(); i++) os << v.at(i) << " ";
		return os;
	}

}
