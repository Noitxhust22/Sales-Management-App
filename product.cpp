#include "product.h"
#include <iostream>
#include <iomanip>
#include <string>
#include <windows.h>
#include <fstream>
#include <vector>
#include <chrono>
#include <ctime>
#include <sstream>
#include <QMainWindow>
#include "mainwindow.h"
#include "ui_mainwindow.h"
using namespace std;


// Product
string Product::getId() {
    return dataId;
}
string Product::getName() {
    return dataName;
}
int Product::getType() {
    return dataType;
}
float Product::getPrice1() {
    return dataPrice1;
}
float Product::getPrice2() {
    return dataPrice2;
}
int Product::getAmount() {
    return dataAmount;
}
void Product::setId(string id) {
    dataId = id;
}
void Product::setName(string name) {
    dataName = name;
}
void Product::setType(int type) {
    dataType = type;
}
void Product::setPrice1(float price1) {
    dataPrice1 = price1;
}
void Product::setPrice2(float price2) {
    dataPrice2 = price2;
}
void Product::setAmount(int amount) {
    dataAmount = amount;
}
void Product::displayProduct(Ui::MainWindow *ui) {
    ui->productListWidget->addItem(QString::fromStdString(getInfo()));
    cout << getId() << " - " << getName() << " - " << getType() << " - " << getPrice1() << " - " << getPrice2() << " - " << getAmount() << endl;
}
string Product::getInfo() {
    string info = dataId + "," + dataName + "," + to_string(dataType) + "," + to_string(dataPrice1) + "," + to_string(dataPrice2) + "," + to_string(dataAmount);
    return info;
}
string Product::getSpecialInfo() {
    return "";
}

// Clearser
string Cleanser::getTypeOfSkin() {
    return dataTypeOfSkin;
}
string Cleanser::getAroma() {
    return dataAroma;
}
void Cleanser::setTypeOfSkin(string typeOfSkin) {
    dataTypeOfSkin = typeOfSkin;
}
void Cleanser::setAroma(string aroma) {
    dataAroma = aroma;
}
void Cleanser::displayProduct(Ui::MainWindow *ui) {
    ui->productListWidget->addItem(QString::fromStdString(dataId + "," + dataName + "," + to_string(dataType) + "," + to_string(dataPrice1) + "," + to_string(dataPrice2) + "," + to_string(dataAmount) + "," + dataTypeOfSkin + "," + dataAroma));
    cout << getId() << " - " << getName() << " - " << getType() << " - " << getPrice1() << " - " << getPrice2() << " - " << getAmount() << " - " << getTypeOfSkin() << " - " << getAroma() << endl;
}
string Cleanser::getInfo() {
    string info = dataId + "," + dataName + "," + to_string(dataType) + "," + to_string(dataPrice1) + "," + to_string(dataPrice2) + "," + to_string(dataAmount) + "," + dataTypeOfSkin + "," + dataAroma;
    return info;
}
string Cleanser::getSpecialInfo() {
    string info = dataTypeOfSkin + "," + dataAroma;
    return info;
}

// Lipstick
string Lipstick::getColor() {
    return dataColor;
}
void Lipstick::setColor(string color) {
    dataColor = color;
}
void Lipstick::displayProduct(Ui::MainWindow *ui) {
    ui->productListWidget->addItem(QString::fromStdString(getInfo()));
    cout << getId() << " - " << getName() << " - " << getType() << " - " << getPrice1() << " - " << getPrice2() << " - " << getAmount() << " - " << getColor() << endl;
}
string Lipstick::getInfo() {
    string info = dataId + "," + dataName + "," + to_string(dataType) + "," + to_string(dataPrice1) + "," + to_string(dataPrice2) + "," + to_string(dataAmount) + "," + dataColor;
    return info;
}
string Lipstick::getSpecialInfo() {
    return dataColor;
}

// Lotion
string Lotion::getBenefit() {
    return dataBenefit;
}
void Lotion::setBenefit(string benifit) {
    dataBenefit = benifit;
}
void Lotion::displayProduct(Ui::MainWindow *ui) {
    ui->productListWidget->addItem(QString::fromStdString(getInfo()));
    cout << getId() << " - " << getName() << " - " << getType() << " - " << getPrice1() << " - " << getPrice2() << " - " << getAmount() << " - " << getBenefit() << endl;
}
string Lotion::getInfo() {
    string info = dataId + "," + dataName + "," + to_string(dataType) + "," + to_string(dataPrice1) + "," + to_string(dataPrice2) + "," + to_string(dataAmount) + "," + dataBenefit;
    return info;
}
string Lotion::getSpecialInfo() {
    return dataBenefit;
}

