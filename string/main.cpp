#include <iostream>
#include <cstdio>
#include <cstring>

using namespace std;

const size_t MAX_SIZE = 256; //длина строки не превышает 255 символов.
const size_t MAX_EXTENSION = 3;
const char* forbidden =  " *<>?|\"";

int main()
{
    char text[MAX_SIZE];
    cout << "Enter file name: ";
    fgets(text, MAX_SIZE, stdin);//вводим строку, считывает не более max_size - 1 символов и записывает их в массив, на который указывает text; чтение ведется из файлового потока stdin станд поток ввода; симв перевода
    

    char* filename = text;
    filename[strlen(filename) - 1] = '\0';  //strlen возвращает в байтах длину строки и убираем символ перевода строки
    while(true) {//проверяем, чтобы в названии не было символов forbidden
        if( strcspn( filename, forbidden ) == strlen( filename ) ) ;//Длина начального участка строки, не содержащая символов указанных в аргументе//strсspn() — определяет, сколько первых символов строки подряд не относятся к множеству, заданному другой строкой (например, сколько символов с начала строки — не разделители слов);
        else {
            cout << "Invalid format";
            break;
        }
        //нулевой указатель
        if( strchr( filename, ':' ) == nullptr ) ;  //strchr выполняет поиск первого вхождения символа : в filename
        else {
            char* colon = strchr(filename,':');//возвращает указатель
            if( colon - filename + 1 <= 1 ){
            //if( *colon = 1 ) { //проверяет, чтобы : стояло не первым символом
                cout << "Invalid format";
                break;
            }
            while( colon != nullptr ) {
                if( isalpha( filename[colon - filename - 1] ) > 0 && //чтобы до : стяла буква //isalpha() возвращает ненулевое значение, если его аргумент является буквой алфавита (верхнего или нижнего регистра). В противном случае возвращается 0.
                   filename[colon - filename + 1] == '\\')//проверяет, чтобы после : стояли
                    colon = strchr(colon + 1, ':');
                else {
                    cout << "Invalid format";
                    break;
                }
            }
        }
        //проверяет расширение
        if( strrchr( filename, '.' ) == nullptr ) //ищет вхождение символа '.'
            strcat( filename, ".txt" ); //strcat() присоединяет к строке str1 копию строки str2 и завершает строку str1 нулевым символом
        
        
        else {
            char* ext = strrchr( filename, '.' );
            for( int i = 1; ext[i] != '\0'; i ++ )
                *(ext + i) = char(tolower(*(ext + i))); //tolower выполняет преобразование прописных букв в строчные
            if( strncmp( ext, ".txt", MAX_EXTENSION + 1 ) == 0 );//сравнивакм значения двух строк?? // == 0 указывает на то, что содержимое обоих блоков памяти равны.
            else {
                cout << "Invalid format";
                break;
            }
        }
        
        puts(filename); //выводит строку
        
        FILE* file = fopen( filename, "r" ); //Создает файл для записи (по умолчанию файл открывается как текстовый).
        
        if( file == nullptr ) {
            cout << "Invalid file name";
            break;
        }
        fseek(file, 0, SEEK_END);//fseek перемещает указатель позиции в потоке. Устанавливает внутренний указатель положения в файле, в новую позицию, которая определяются путем добавления смещения к исходному положению.
        
        long filesize = ftell(file);//ftell – опрос текущей позиции в потоке данных
        
        
        char* filedata = new char[filesize];//выделение памяти для массива
        rewind( file ); //Устанавливает внутренний указатель положения файла в начальное положение (начало файла)
        fread( filedata, 1, filesize, file ); //fread считывает массив размером — filesize элементов, каждый из которых имеет размер 1 байт, из потока, и сохраняет его в блоке памяти, на который указывает filedata.
        char* fldt = filedata;//указатель на ячейку памяти, где начинается строка
        fldt[filesize] = '\0';//Нулевой символ используется для обозначения конца строки. обращаемся к концу строки
        
        char STR[MAX_SIZE];
        cout << "Enter string: ";
        fgets(STR, MAX_SIZE, stdin);
        char* str = STR;//указатель на ячейку памяти, где начинается строка STR
        *(str + strlen(str) - 1) = '\0';//разименование
        // *(0xabcd00) = '\0'
        int occur = 0;
        while(strstr(fldt, str) != nullptr) { //Функция ищет первое вхождение подстроки str в строке fldt. Возвращает указатель на первое вхождение строки str   в строку fldt, или Нулевой указатель, если последовательность символов строки str не входит в fldt.
            occur ++;
            fldt = strstr(fldt, str) + 1; //переход к след
        }
        cout << "Occurance number: " << occur;
        delete[] filedata;//очистка памяти
        fclose(file);
        break;
    }
    cout << endl;
    return 0;
}
