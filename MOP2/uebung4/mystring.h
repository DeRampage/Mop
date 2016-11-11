#pragma once
/* Deklaration Klasse String  ***********************************/

class MyString
{
public:
		MyString(const MyString &newStr);
		MyString(const char *newStr = "<leer>");
		~MyString(void);
		int Set(const MyString &newStr);
		int Set(const char *newStr);
		inline const char* Get(void) const { return str; };
		inline int GetLength(void) const {return length; };
        /* cast to char* ==> allows direct output to cout */
        inline MyString& operator=(const MyString &op)
        {
            Set(op);
            return *this;
        };
		inline operator const char*()
		{
			return str;
		}
private:
        char *str { nullptr };
        int length = 0;
/* for monitoring of constructor & destructor */
		int id; /* individual object id */
		static int counter; /* to count constructor/destructor calls */
};
