#include <iostream>
using namespace std;
//if the program cannot run, please delete all statement: exit(-1);
template <class T>
void quickSort(T s[], int start, int end)
{
    if (start < end) {
        int i = start, j = end;
        T x = s[start];
        while (i < j) {
            while (i < j && s[j] >= x) j--;
            if(i < j) s[i++] = s[j];
            while (i < j && s[i]< x) i++;
            if(i < j) s[j--] = s[i];}
        s[i] = x;
        quickSort(s, start, i-1); quickSort(s, i+1, end);}
}

template<class T>
class MyList{
private:
	T *a;
	int size, size_a;

    void double_space()
    {
        size_a *= 2;
        T *tmp = new T[size_a];
        for (int i=0; i<size; ++i) tmp[i]=a[i];
        a = tmp;
    }

public:
	MyList()
	{
		size_a = 1; size = 0;
		a = new T [size_a];
	}

	MyList(int num, const T &item)
	{
	    try {
	        if (num<0) {num = 0; throw(1);}} 
		catch(int) {cout << "The length should >= 0!\nPlease check the length!\n"; exit(-1);}
	    size_a = size = num;
        a = new T [size_a];
        for (int i=0; i<size; ++i) a[i] = item;
	}

	MyList(const MyList &l)
	{
	    size_a = size = l.size;
	    a = new T [size_a];
	    for (int i=0; i<size; ++i) a[i] = l.a[i];
	}

    MyList(T *arr, int len)
    {
        try {
	        if (len<0) {len = 0; throw(1);}} 
		catch(int) {cout << "The length should >= 0!\nPlease check the length!\n"; exit(-1);}
        size_a = size = len;
        a = new T [size_a];
        for (int i=0; i<size; ++i) a[i] = arr[i];
    }

    void insert(int index, const T &item)
    {
        try {
	        if (index<0) {index = 0; cout << "The index should >= 0!\n"; throw(1);}
	        else if (index>size) {index = size; cout << "The index should <= the size!\n"; throw(2);}}
	    catch(int) {cout << "Please check the index!\n"; exit(-1);}
        ++size;
        while (size > size_a) double_space();
        for (int i=size-1; i>index; --i) a[i] = a[i-1];
        a[index] = item;
    }

    void push(const T &item) {insert(size, item);}

    void erase(int start, int end)
    {
        if (start < 0) start = 0;
        if (end >= size) end = size - 1;
        for (int i=end+1; i<size; ++i) a[i+start-end-1] = a[i];
        size = size + start - end - 1;
    }

    T pop()
    {
        try {
            if (size==0) throw(1);
            else --size;} 
		catch(int) {T tmp; cout << "Cannot pop an empty list!\n"; return tmp; exit(-1);}
        return a[size];
    }

    void remove(const T &item)
    {
        bool flag = true;
        for (int i=0; i<size; ++i)
            if (a[i] == item) {
				erase(i, i); 
				flag = false; 
				break;}
        if (flag) cout << "Cannot found " << item << "!\n";
    }

    void clean() {size = 0;}

    int get_size() {return size;}

    T get_item(int index)
    {
        if (index < 0) index += size;
        try {
	        if (index < 0) {index = 0; cout << "The index should >= 0!\n"; throw(1);}
	        else if (index >= size) {index = size-1; cout << "The index should < the size!\n"; throw(2);}}
	    catch(int) {cout << "Please check the index!\n"; exit(-1);}
        return a[index];
    }

    MyList get_item(int start, int end)
    {
        MyList<T> tmp;
        if (start < 0) start += size;
        if (end < 0) end += size;
        try {
            if (start<0 || end<0) {cout << "The index should >=\0!\n"; throw(1);}
            else if (start>=size || end>=size) {cout << "The index should < the size!\n"; throw(2);}}
        catch(int) {start = 0; end = size - 1;
             		cout << "Please check the index!\n"; exit(-1);}
        if (start <= end)
            for (int i=start; i<=end; ++i) tmp.push(a[i]);
        return tmp;
    }

    int count(const T &item)
    {
        int cnt = 0;
        for (int i=0; i<size; ++i)
            if (a[i] == item) ++cnt;
        return cnt;
    }

    void reverse()
    {
        T tmp;
        for (int i=0; i<size/2; ++i) {tmp = a[size-1-i]; a[size-1-i] = a[i]; a[i] = tmp;}
    }

    void sort(bool less=true)
    {
        quickSort(a, 0 ,size-1);
        if (!less) reverse();
    }

    friend MyList operator + (const MyList &l1, const MyList &l2)
    {
        MyList<T> l;
        int i;
        while (l.size_a < l1.size_a + l2.size_a) l.double_space();
        l.size = l1.size + l2.size;
        for (i=0; i<l1.size; ++i) l.a[i] = l1.a[i];
        for (i=0; i<l2.size; ++i) l.a[i+l1.size] = l2.a[i];
        return l;
    }

    friend MyList operator + (const MyList &l1, const T &item)
    {
        MyList<T> tmp(l1);
        tmp.push(item);
        return tmp;
    }

    MyList &operator += (const MyList &l) {*this = *this + l;}

    MyList &operator += (const T &item) {push(item);}

    MyList &operator = (const MyList &l)
    {
        while (size_a < l.size_a) double_space();
        size = l.size;
        for (int i=0; i<size; ++i) a[i] = l.a[i];
    }

    T &operator [](int index)
    {
        if (index < 0) index += size;
        try {
            if (index < 0) {index = 0; cout << "The index should >= 0!\n"; throw(1);}
	        else if (index >= size) {index = size-1; cout << "The index should < the size!\n"; throw(2);}}
	    catch(int) {cout << "Please check the index!\n"; exit(-1);}
        return (a[index]);
    }

    friend ostream & operator<<(ostream &os, const MyList &obj)
    {
        os << "[";
        if (obj.size > 0) {
            for (int i=0; i<obj.size-1; ++i) os << obj.a[i] << ", ";
            os << obj.a[obj.size-1] <<"]";}
        else os << "]";
        return os;
    }

	~MyList() {delete [] a;}
};

int main()
{
	MyList<int> a, b;
	int i;
	for (i=0; i<5; ++i)
		a.push(i);
	cout << a << endl; 
	a[3] = 15;
	cout << a << endl; 
	a.sort();
	cout << a << endl; 
	a.reverse();
	cout << a << endl; 
	a += 12;
	cout << a << endl; 
	for (i=0; i<a.get_size(); ++i)
		cout << a[i] << " ";
	cout << endl;
    b = a.get_item(4, -3);
    cout << b << endl; 
	b = a.get_item(3, -1);
	cout << b << endl; 
	a += b;
	cout << a << endl; 
	for (i=0; i<a.get_size(); ++i)
		cout << a.get_item(i) << " ";
	cout << endl;
	cout << a.count(5) << endl;
	b.clean();
	cout << b << endl; 
	cout << b.get_size() << endl;
	a.erase(2, 5);
	cout << a << endl; 
	b = a + a;
	cout << b << endl; 
	b.insert(3, 116);
	cout << b << endl; 
	b.remove(4);
	cout << b << endl; 
	MyList<double> c(10, 3.14);
	for (i=0; i<100; ++i)
		c.push(1.1*i);
	cout << c.get_item(100, 105) << endl;
    return 0;
}


