#include <iostream>

class Button{
    public:
        virtual void press() = 0;
};

class MacButton : public Button{
    public:
        void press(){
            std::cout << "Mac Button is Pressed" << std::endl;
        }
};

class WinButton : public Button{
    public:
        void press(){
            std::cout << "Windows Button is Pressed" << std::endl;
        }
};

class TextBox{
    public:
        virtual void show() = 0;
};

class MacTextBox : public TextBox{
    public:
        void show(){
            std::cout << "Mac Text box is showed" << std::endl;
        }
};

class WinTextBox : public TextBox{
    public:
        void show(){
            std::cout << "Windows Text box is showed" << std::endl;
        }
};

class Factory{
    public:
        virtual Button* createButton() = 0;
        virtual TextBox* createTextBox() = 0;
};

class MacFactory : public Factory{
    public:
        Button* createButton(){
            return new MacButton();
        }
        TextBox* createTextBox(){
            return new MacTextBox();
        }
};

class WinFactory : public Factory{
    public:
        Button* createButton(){
            return new WinButton();
        }
        TextBox* createTextBox(){
            return new WinTextBox();
        }
};

class AbstractFactory{
    public:
        Factory* createFactory(std::string os){
            if(os.compare("windows") == 0){
                return new WinFactory();
            }else if(os.compare("mac") == 0){
                return new MacFactory();
            }
            return new MacFactory();
        }
};

int main(){
    AbstractFactory absFactory;
    Factory *factory = absFactory.createFactory("windows");
    // Factory *factory = absFactory.createFactory("mac");
    // Factory *factory = absFactory.createFactory("default");
    Button *button = factory->createButton();
    TextBox *textBox = factory->createTextBox();
    button->press();
    textBox->show();
    return 0;
}