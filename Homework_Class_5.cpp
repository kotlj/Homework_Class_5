
#include <iostream>
#include <fstream>

enum Rtype
{
    Rtype_none,
    Rtype_sea,
    Rtype_lake,
    Rtype_ocean,
    Rtype_liman,
    Rtype_pond,
    Rtype_pool,
    Rtype_oxbow
};

class Reservoir
{
private:
    char* name;
    Rtype type;
    float width;
    float deep;
    float length;

public:
    Reservoir()
    {
        name = new char[5]; 
        name[0] = 'n'; 
        name[1] = 'o'; 
        name[2] = 'n'; 
        name[3] = 'e'; 
        name[4] = '\0';
        type = Rtype_none;
        width = 0;
        deep = 0;
        length = 0;
    }
    Reservoir(char* _name, Rtype _type = Rtype_lake, float _width = 10, float _deep = 10, float _length = 10)
    {
        setName(_name);
        type = _type;
        width = _width;
        deep = _deep;
        length = _length;
    }
    Reservoir(Reservoir& obj)
    {
        this->setName(obj.getName());
        this->type = obj.type;
        this->width = obj.width;
        this->deep = obj.deep;
        this->length = obj.length;
    }

    void copy(Reservoir& obj)
    {
        this->setName(obj.getName());
        this->type = obj.type;
        this->width = obj.width;
        this->deep = obj.deep;
        this->length = obj.length;
    }

    float V()
    {
        return width * length * deep;
    }
    float S()
    {
        return width * length;
    }
    bool areaIsBigger(Reservoir& obj)
    {
        if (this->S() > obj.S())
        {
            return true;
        }
        return false;
    }
    bool areaIsSmaller(Reservoir& obj)
    {
        if (this->S() < obj.S())
        {
            return true;
        }
        return false;
    }
    bool areaIsEqual(Reservoir& obj)
    {
        if (this->S() == obj.S())
        {
            return true;
        }
        return false;
    }
    void show() const
    {
        std::cout << "_____________________________________\n" << name << '\n' << 
            (type == 0 ? "none" : (type == 1 ? "sea" : (type == 2 ? "lake" : (type == 3 ? "ocean" : (type == 4 ? "liman" : 
                (type == 5 ? "pond" : (type == 6 ? "pool" : "oxbow"))))))) << '\n' << "Width: " << width << '\n' << 
            "Length: " << length << '\n' << "Deep: " << deep << '\n';
    }


    char* getName() const
    {
        return name;
    }
    Rtype getType() const
    {
        return type;
    }
    float getWidth() const
    {
        return width;
    }
    float getDeep() const
    {
        return deep;
    }
    float getLength() const
    {
        return length;
    }

    void setName(char* _name)
    {
        int size = 0;
        for (int i = 0; _name[i] != '\0'; i++)
        {
            size++;
        }
        this->name = new char[size + 1];
        this->name[size] = '\0';
        for (int i = 0; _name[i] != '\0'; i++)
        {
            this->name[i] = _name[i];
        }
    }
    void setType(Rtype _type)
    {
        type = _type;
    }
    void setWidth(float _width)
    {
        width = _width;
    }
    void setDeep(float _deep)
    {
        deep = _deep;
    }
    void setLength(float _length)
    {
        length = _length;
    }

    ~Reservoir()
    {
        delete[] name;
    }
};



int main()
{
    int choise = 1;
    int arrSize = 10;
    int nameSize = 20;
    float input = 0;
    Reservoir* arr = new Reservoir[arrSize];
    char* _name = new char[nameSize + 1];
    _name[nameSize] = '\0';
    for (int i = 0; i < arrSize; i++)
    {
        for (int j = 0; j < nameSize; j++)
        {
            _name[j] = char(68 + i);
        }
        arr[i].setName(_name);
        arr[i].setWidth(i);
        arr[i].setLength(i);
        arr[i].setDeep(i);
        arr[i].setType(Rtype(i % 8));
    }
    while (choise != 0)
    {
        std::cout << "Choose option:\n1 - Show array;\n2 - Add member;\n3 - Delete member;\
                    \n4 - Save to file;\n0 - Exit;\n";
        std::cin >> choise;
        if (choise == 1)
        {
            for (int i = 0; i < arrSize; i++)
            {
                arr[i].show();
            }
        }
        else if (choise == 2)
        {
            Reservoir add;
            if (_name != nullptr)
            {
                delete[] _name;
                _name = new char[nameSize];
            }
            std::cout << "Enter name:\n";
            gets_s(_name, nameSize);
            gets_s(_name, nameSize);
            add.setName(_name);
            std::cout << "Enter width:\n";
            std::cin >> input;
            add.setWidth(input);
            std::cout << "Enter length:\n";
            std::cin >> input;
            add.setLength(input);
            std::cout << "Enter deep:\n";
            std::cin >> input;
            add.setDeep(input);
            std::cout << "Choose type: |1 - sea|, |2 - lake|, |3 - ocean|, |4 - liman|, |5 - pond|, \
|6 - pool|, |7 - oxbow|;\n";
            std::cin >> input;
            if (input < 8 && input > 0)
            {
                add.setType(Rtype(input));
            }
            else
            {
                std::cout << "ERROR: INVALID TYPE;";
                add.setType(Rtype_none);
            }
            Reservoir* temple = new Reservoir[arrSize + 1];
            temple[arrSize].copy(add);
            for (int i = 0; i < arrSize; i++)
            {
                temple[i].copy(arr[i]);
            }
            arrSize++;
            delete[] arr;
            arr = temple;
            temple = nullptr;
        }
        else if (choise == 3)
        {
            std::cout << "Enter index of object to delete:\n";
            std::cin >> input;
            Reservoir* temple = new Reservoir[arrSize];
            for (int i = 0; i < arrSize; i++)
            {
                if (i < input)
                {
                    temple[i].copy(arr[i]);
                }
                else if (i > input)
                {
                    temple[i - 1].copy(arr[i]);
                }
            }
            arrSize--;
            delete[] arr;
            arr = temple;
            temple = nullptr;
        }
        else if (choise == 4)
        {
            std::ofstream fileo("ReservoirSave.txt");
            if (fileo.is_open())
            {
                fileo << arrSize << ' ' << '\n';
                for (int i = 0; i < arrSize; i++)
                {
                    fileo << arr[i].getName() << '_'<< arr[i].getWidth() << ' ' << arr[i].getLength() << ' ' <<
                        arr[i].getDeep() << ' ' << arr[i].getType() << " \n";
                }
                fileo.close();
            }
            else
            {
                std::cout << "ERROR: FILE OPEN ERROR;";
            }
        }
/*      else if (choise == 5)
        {
            std::ifstream file("ReservoirSave.txt");
            if (file.is_open())
            {
                int sizeEnd = 0;
                file >> arrSize;
                sizeEnd = file.tellg();
                delete[] arr;
                arr = new Reservoir[arrSize];
                int input;
                for (int i = 0; i < arrSize; i++)
                {
                    file.getline(_name, nameSize, '_');
                    arr[i].setName(_name);
                    file >> input;
                    arr[i].setWidth(input);
                    file >> input;
                    arr[i].setLength(input);
                    file >> input;
                    arr[i].setDeep(input);
                    file >> input;
                    arr[i].setType(Rtype(int(input)));
                }
                file.close();
            }
            else
            {
                std::cout << "ERROR> FILE OPEN ERROR;";
            }
        }
        */
    }
    if (_name != nullptr)
    {
        delete[] _name;
    }
    if (arr != nullptr)
    {
        delete[] arr;
    }
}