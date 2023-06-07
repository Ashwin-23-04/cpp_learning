#include<iostream>

class Animal{
    private:
        std::string name;
    public:
        Animal(std::string name){
            this->name = name;
        }
        std::string getName(){
            return this->name;
        }
        void setName(std::string name){
            this->name = name;
        }
};

class Iterator{
    public:
        virtual void reset(){}
        virtual Animal current(){}
        virtual Animal next(){}
        virtual Animal back(){}
};

class AnimalIterator : public Iterator{
    private:
        std::vector<Animal> animals;
        int position;
    public:
        AnimalIterator(std::vector<Animal> animals){
            this->animals = animals;
            this->position = 0;
        }
        void reset(){
            position = 0;
        }
        Animal current(){
            return animals.at(position);
        }
        Animal next(){
            if(position == animals.size() - 1){
                std::cout << "No more" << std::endl;
                return animals.at(position);
            }
            return animals.at(++position);
        }
        Animal back(){
            if(position == 0){
                std::cout << "No more" << std::endl;
                return animals.at(position);
            }
            return animals.at(--position);
        }
};

class List{
    public:
        virtual Iterator* iterator(){}
};

class AnimalList : public List{
    private:
        std::vector<Animal> animals;
    public:
        AnimalList(std::vector<Animal> animals){
            this->animals = animals;
        }
        Iterator* iterator(){
            return new AnimalIterator(animals);
        }

};

int main(){
    std::vector<Animal> animals;
    Animal lion("Lion");
    Animal dog("Dog");
    Animal cat("Cat");
    Animal tiger("Tiger");
    animals.push_back(lion);
    animals.push_back(dog);
    // animals.push_back(cat);
    // animals.push_back(tiger);


    List *list = new AnimalList(animals);
    Iterator *iterator = list->iterator();

    Animal currentAnimal = iterator->current();
    std::cout << currentAnimal.getName() << std::endl;
    currentAnimal = iterator->back();
    std::cout << currentAnimal.getName() << std::endl;
    currentAnimal = iterator->next();
    std::cout << currentAnimal.getName() << std::endl;
    // currentAnimal = iterator->next();
    // std::cout << currentAnimal.getName() << std::endl;
    // currentAnimal = iterator->next();
    // std::cout << currentAnimal.getName() << std::endl;
    // currentAnimal = iterator->next();
    // std::cout << currentAnimal.getName() << std::endl;
    return 0;
}