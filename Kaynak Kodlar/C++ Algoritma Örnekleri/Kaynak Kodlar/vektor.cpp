#include<stdio.h>
#include<stdlib.h>

typedef int TYPE;

class Vector {
public:
	Vector();
	Vector(size_t);
	Vector(const Vector &r);
	~Vector();
	void Resize(size_t);
	TYPE Get(size_t index);
	void Set(size_t index, TYPE x);
	void Insert(size_t index, TYPE x);
	void Delete(size_t index);
	void Add(TYPE val);
	void Clear();
	size_t Size() const;
	size_t Capacity() const;
	Vector &operator =(const Vector &r);
	TYPE &operator [](size_t x);
	void Disp();
private:
	TYPE *m_pArray;
	unsigned m_size;
	unsigned m_capacity;
};

Vector::Vector()
{
	m_size = 0;
	m_capacity = 0;
	m_pArray = (TYPE *)malloc(0);
}

Vector::Vector(size_t size)
{
	m_size = 0;
	m_capacity = 10;
	m_pArray = (TYPE *)malloc(sizeof(TYPE) * size);
	
	for (size_t i = 0; i < m_size; ++i)
			m_pArray[i] = 0;
}

Vector::Vector(const Vector &r)
{
	m_size = r.m_size;
	m_capacity = r.m_capacity;

	m_pArray = (TYPE *)malloc(sizeof(TYPE) * r.m_capacity);
	for (size_t i = 0; i < m_size; ++i)
		m_pArray[i] = r.m_pArray[i];
}

Vector::~Vector()
{
	Clear();
}

void Vector::Resize(size_t size)
{
	if (size >= m_capacity)
		m_pArray = (TYPE *)realloc(m_pArray, size * sizeof(TYPE));
	
	m_capacity = size;
}

void Vector::Insert(size_t index, TYPE x)
{
	if (m_size == m_capacity)
		Resize(m_size * 2);

	for (size_t i = m_size; i > index; --i)
		m_pArray[i] = m_pArray[i - 1];
	m_pArray[index] = x;
	m_size++;
}

void Vector::Delete(size_t index)
{
	for (size_t i = index; i < m_size; ++i)
		m_pArray[i] = m_pArray[i + 1];
	m_size--;
}

void Vector::Add(TYPE val)
{
	if (m_size == m_capacity)
		Resize(m_size * 2);
	m_pArray[m_size++] = val;
}

void Vector::Clear()
{
	free(m_pArray);

	m_size = 0;
	m_capacity = 0;
}

Vector &Vector::operator =(const Vector &r)
{
	m_size = r.m_size;
	m_capacity = r.m_capacity;

	Resize(m_capacity);
	for (size_t i = 0; i < m_size; ++i)
		m_pArray[i] = r.m_pArray[i];

	return *this;
}

TYPE Vector::Get(size_t index)
{
	return m_pArray[index];
}

void Vector::Set(size_t index, TYPE x)
{
	m_pArray[index] = x;
}

TYPE &Vector::operator [](size_t x)
{
	return m_pArray[x];
}

void Vector::Disp()
{
	for (size_t i = 0; i < m_size; ++i) {
		printf("%4d",m_pArray[i]);
		((i + 1) % 5 == 0)?putchar('\n'):putchar(' ');
	}
}

int main()
{
	Vector a(10), b(10);

	printf("\n------ADD/DELETE TESTLERi---\n");
	for (int i = 0; i < 17; ++i)
		a.Add(i);

	a.Delete(12);
	b = a;
	b.Disp();

	printf("\n\n 12.eleman: %d", b[12]);

	b.Set(12, 1977);

	printf("\n Degisen 12. eleman :%d\n\n", b.Get(12));

	b.Disp();

	printf("\n--------INSERT TESTi--------\n");
	for (i = 0; i < 4; ++i)
		b.Insert(i * 2, 10);
	
	b.Disp();

	printf("\n--------[] TESTi------------\n");
	for (i = 0; i < 4; ++i)
		b[i] = 50;
	b.Disp();
	return 0;
}
