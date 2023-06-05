#include<iostream>

class Image{
    public:
        virtual void display(){}
};

class RealImage : public Image{
    private:
        std::string fileName;
    public:
        RealImage(std::string fileName){
            this->fileName = fileName;
            this->loadFromDisk();
        }
        void display(){
            std::cout << "Displaying Image of file name " << fileName << std::endl;
        }
        void loadFromDisk(){
            std::cout << "Loading Image of file name " << fileName << std::endl;
        }
};

class ProxyImage : public Image{
    private:
        RealImage *realImage;
        std::string fileName;
    public:
        ProxyImage(std::string fileName){
            this->fileName = fileName;
            this->realImage = nullptr;
        }
        void display(){
            if(realImage == nullptr){
                this->realImage = new RealImage(fileName);
            }
            realImage->display();
        }
};

int main(){
    Image *image = new ProxyImage("test.jpg");
    image->display(); // Load and display
    image->display(); // Display from loaded image before
    return 0;
}