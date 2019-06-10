#include "byteprint.h"

using namespace std;

char nibble_to_hex(uint8_t i) //функция, которая представляет значение от 0 до 15 в шестнадцатеричном виде
{
    assert( 0x0 <= i && i <= 0xf );
    char digits[] = "0123456789abcdef";
    return digits[i];
}

void print_in_hex(uint8_t byte) //выделение старших разрядов байта и их перемещение (сдвиг) на позиции младших разрядов.
{//печатаем байт как 2 nibble
    cout << nibble_to_hex(byte >> 4) //сдвиг
    << nibble_to_hex(byte & 0xf);//8бит выводит
}
//заключим преоб типов в функцию
//выводим массив байт
void print_in_hex(const void* data, size_t datasize)
{//сonst означает, что данные по адресу, хранимому в указателе, не могут быть изменены через этот указатель.
    const uint8_t* bytes = reinterpret_cast<const uint8_t*>(data); // осуществляет приведение типов без проверки -
   // непосредственное указание компилятору считать биты и преобразовать их в другой тип.
    for( size_t i = 0; i < datasize; i++ )
    {
        print_in_hex( bytes[i] );
        if ( (i + 1) % 16 == 0)
            cout << '\n';
        else
            cout << ' ';
    }
}

char bit_digit(uint8_t byte, uint8_t bit) // печатает байт в двоичном виде
{//проверяем биты, начиная со старшего, и печатаем 0, если бит равен 0, и 1, если бит равен 1
    if( byte & ( 0x1 << bit ) ) //старший бит выделяется маской как 0b10000000(0x1 << 7), младший — маской (0x1 << 0)
        return '1';
    return '0';
}


void print_in_binary(uint8_t byte) //Сдвиги на 7, 6, …, 0 бит
{
    for( int bit = 7; bit >= 0; bit-- )
        cout << bit_digit(byte, bit);
}

void print_in_binary(const void* data, size_t datasize) //приведение типов в двоичную систему.
{
    const uint8_t* bytes = reinterpret_cast<const uint8_t*>(data);
    for (size_t i = 0; i < datasize; i++)
    {
        print_in_binary(bytes[i]);
        // Для удобства чтения: пробелы между байтами, по 4 байта на строку.

        if ( (i + 1) % 4 == 0 )
            cout << '\n';
        else
            cout << ' ';
    }
}

void byte_calc( uint16_t first, uint16_t second, char oper )
{
    uint16_t byteand = first & second;
    uint16_t byteor = first | second;
    uint16_t bytexor = first ^ second;
    switch( oper )
    {
        case '&':
            print_in_hex( &first, sizeof(first) );
            cout << "& ";
            print_in_hex( &second, sizeof(second) );
            cout << "= ";
            print_in_hex( &byteand, sizeof(byteand) );
            cout << "\n";
            print_in_binary( &first, sizeof(first) );
            cout << "& ";
            print_in_binary( &second, sizeof(second));
            cout << "= ";
            print_in_binary( &byteand, sizeof(byteand) );
            break;
        case '|':
            print_in_hex( &first, sizeof(first));
            cout << "| ";
            print_in_hex( &second, sizeof(second) );
            cout << "= ";
            print_in_hex( &byteand, sizeof(byteand) );
            cout << "\n";
            print_in_binary( &first, sizeof(first) );
            cout << "| ";
            print_in_binary( &second, sizeof(second) );
            cout << "= ";
            print_in_binary( &byteor, sizeof(byteor) );
            break;
        case '^':
            print_in_hex( &first, sizeof(first));
            cout << "^ ";
            print_in_hex( &second, sizeof(second) );
            cout << "= ";
            print_in_hex( &byteand, sizeof(byteand) );
            cout << "\n";
            print_in_binary( &first, sizeof(first) );
            cout << "^ ";
            print_in_binary( &second, sizeof(second) );
            cout << "= ";
            print_in_binary( &bytexor, sizeof(bytexor) );
            break;
    }
}
