#ifndef CONTAINERINTERFACE_H_INCLUDED
#define CONTAINERINTERFACE_H_INCLUDED

class BADINDEX {};

template <class T>
class containerInterface
{
   public:
	 virtual containerInterface <T>& pushFront(T)                  =0;
	 virtual containerInterface <T>& pushBack(T)                   =0;
	 virtual containerInterface <T>& popFront( ) throw (BADINDEX) =0;
	 virtual containerInterface <T>& popBack( )  throw (BADINDEX) =0;
	 virtual int  getSize() const                                     =0;
	 virtual bool full() const                                     =0;
	 virtual bool empty() const                                    =0;
	 virtual T    front() const                   throw (BADINDEX) =0;
	 virtual T    back() const                    throw (BADINDEX) =0;
	 virtual T&   operator [](int)                throw (BADINDEX) =0;
	 virtual void erase()                                          =0;
	 virtual ~containerInterface(){};
};

#endif // CONTAINERINTERFACE_H_INCLUDED
