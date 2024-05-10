#include <iostream>
using namespace std;

class BitString 
{
private:
    char* str;
    size_t length;

    bool isValidBitString(const char* c_str) 
    {
        for (size_t i = 0; c_str[i] != '\0'; i++) 
        {
            if (c_str[i] != '0' && c_str[i] != '1') 
            {
                return false;
            }
        }
        return true;
    }

    void free() 
    {
        delete[] str;
        str = nullptr;
        length = 0;
    }

public:
    BitString() : str(nullptr), length(0) 
    {
        str = new char[1];
        str[0] = '\0';
    }

    BitString(const char* c_str) : str(nullptr), length(0) 
    {
        if (isValidBitString(c_str)) 
        {
            length = 0;
            while (c_str[length] != '\0') 
            {
                length++;
            }
            str = new char[length + 1];
            for (size_t i = 0; i < length; i++) 
            {
                str[i] = c_str[i];
            }
            str[length] = '\0';
        }
        else 
        {
            str = new char[1];
            str[0] = '\0';
            length = 0;
        }
    }

    BitString(const BitString& other) : str(nullptr), length(other.length) 
    {
        str = new char[length + 1];
        for (size_t i = 0; i < length; i++) 
        {
            str[i] = other.str[i];
        }
        str[length] = '\0';
    }

    BitString& operator=(const BitString& other) 
    {
        if (this != &other) 
        {
            free();
            length = other.length;
            str = new char[length + 1];
            for (size_t i = 0; i < length; i++) 
            {
                str[i] = other.str[i];
            }
            str[length] = '\0';
        }
        return *this;
    }

    ~BitString() 
    {
        free();
    }

    void changeSign() 
    {
        for (size_t i = 0; i < length; i++) 
        {
            str[i] = (str[i] == '0') ? '1' : '0';
        }

        int carry = 1;
        for (size_t i = length - 1; i >= 0 && carry > 0; i--) 
        {
            int bit = str[i] - '0';
            int sum = bit + carry;
            if (sum == 2) 
            {
                str[i] = '0';
            }
            else 
            {
                str[i] = sum + '0';
                carry = 0;
            }
        }
    }

    BitString operator+(const BitString& other) const 
    {
        size_t maxLength = max(length, other.length);
        size_t newLength = maxLength + 1; 
        char* newStr = new char[newLength + 1];
        for (size_t i = 0; i <= maxLength; i++) 
        {
            newStr[i] = '0';
        }
        newStr[newLength] = '\0';

        int carry = 0;
        for (size_t i = 0; i < maxLength; i++) 
        {
            int bit1 = (length > i) ? str[length - i - 1] - '0' : 0;
            int bit2 = (other.length > i) ? other.str[other.length - i - 1] - '0' : 0;
            int sum = bit1 + bit2 + carry;
            carry = sum / 2;
            newStr[newLength - i - 1] = (sum % 2) + '0';
        }

        if (carry > 0) 
        {
            newStr[0] = '1';
        }
        else {
            for (size_t i = 1; i <= maxLength; i++) 
            {
                newStr[i - 1] = newStr[i];
            }
            newStr[maxLength] = '\0';
        }

        BitString result(newStr);
        delete[] newStr;
        return result;
    }

    bool operator==(const BitString& other) const 
    {
        if (length != other.length) 
        {
            return false;
        }
        for (size_t i = 0; i < length; i++) 
        {
            if (str[i] != other.str[i]) 
            {
                return false;
            }
        }
        return true;
    }

    bool operator!=(const BitString& other) const 
    {
        return !(*this == other);
    }

    void print() const 
    {
        cout << str << endl;
    }
};

int main() 
{
    BitString bitStr1("1101");
    BitString bitStr2("1011");

    BitString bitSum = bitStr1 + bitStr2;

    cout << "bitStr1: ";
    bitStr1.print();
    cout << "bitStr2: ";
    bitStr2.print();
    cout << "bitSum (bitStr1 + bitStr2): ";
    bitSum.print();

    cout << "bitStr1 == bitStr2: " << (bitStr1 == bitStr2) << endl;
    cout << "bitStr1 != bitStr2: " << (bitStr1 != bitStr2) << endl;

    cout << "bitStr1 change sign: ";
    bitStr1.changeSign();
    bitStr1.print();
}

