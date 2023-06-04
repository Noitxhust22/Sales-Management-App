#ifndef PRODUCT_H
#define PRODUCT_H
#include <iostream>
#include <QMainWindow>
#include <iomanip>
#include <string>
#include <windows.h>
#include <fstream>
#include <vector>
#include <chrono>
#include <ctime>
#include <sstream>

#include "mainwindow.h"
using namespace std;

class Product {
protected:
    string dataId;
    string dataName;
    int dataType;
    float dataPrice1;
    float dataPrice2;
    int dataAmount;

public:
    Product(string id, string name, int type, float price1, float price2, int amount) {
        dataId = id;
        dataName = name;
        dataType = type;
        dataPrice1 = price1;
        dataPrice2 = price2;
        dataAmount = amount;
    }

    string getId();
    string getName();
    int getType();
    float getPrice1();
    float getPrice2();
    int getAmount();

    void setId(string id);
    void setName(string name);
    void setType(int type);
    void setPrice1(float price1);
    void setPrice2(float price2);
    void setAmount(int amount);

public:
    virtual void displayProduct(Ui::MainWindow *ui);
    virtual string getInfo();
    virtual string getSpecialInfo();

};

class Cleanser :public Product {
public:
    string dataTypeOfSkin;
    string dataAroma;
    Cleanser(string id, string name, int type, float price1, float price2, int amount, string typeOfSkin, string aroma)
        :Product(id, name, type, price1, price2, amount) {
        dataTypeOfSkin = typeOfSkin;
        dataAroma = aroma;
    }

public:
    void displayProduct(Ui::MainWindow *ui);
    string getTypeOfSkin();
    string getAroma();
    void setTypeOfSkin(string typeOfSkin);
    void setAroma(string aroma);
    string getInfo();
    string getSpecialInfo();
};

class Lipstick :public Product {
public:
    string dataColor;
    Lipstick(string id, string name, int type, float price1, float price2, int amount, string color)
        :Product(id, name, type, price1, price2, amount) {
        dataColor = color;
    }
public:
    void displayProduct(Ui::MainWindow *ui);
    string getColor();
    void setColor(string color);
    string getInfo();
    string getSpecialInfo();
};

class Lotion :public Product {
public:
    string dataBenefit;
    Lotion(string id, string name, int type, float price1, float price2, int amount, string benefit)
        :Product(id, name, type, price1, price2, amount) {
        dataBenefit = benefit;
    }
public:
    void displayProduct(Ui::MainWindow *ui);
    string getBenefit();
    void setBenefit(string benefit);
    string getInfo();
    string getSpecialInfo();
};


#endif // PRODUCT_H
