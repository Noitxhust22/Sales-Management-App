#include "mainwindow.h"
#include "ui_mainwindow.h"
#include<iostream>
#include <QDebug>
#include <QString>
#include <QMessageBox>
#include "product.h"

using namespace std;

void displayProductVector(vector<unique_ptr<Product>> & p,Ui::MainWindow *ui) {
    for (int i = 0; i < p.size(); i++) {
        p[i]->displayProduct(ui);
    }
    cout << "===================" << endl;
}

void displayFilterProductVector(vector<unique_ptr<Product>>& filterP, vector<int> sortIndexs, Ui::MainWindow *ui) {
    ui->productListWidget->clear();
    for (int i = 0; i < sortIndexs.size(); i++) {
        filterP[sortIndexs[i]]->displayProduct(ui);
    }
    cout << "===================" << endl;
}

int findProductByName(vector<unique_ptr<Product>> & p, string name) {
    int index = -1;
    for (int i = 0; i < p.size(); i++) {
        if (p[i]->getName().compare(name) == 0) {
            index = i;
            break;
        }
    }
    return index;
}

int addOldProductByName(vector<unique_ptr<Product>> & p, string name, float price1, int amount) {
    int checkIndex = findProductByName(p, name);
    if (checkIndex == -1) return 0;

    if (name.compare("")==0) return 0;
    if (price1==-1) return 0;
    if (amount==-1) return 0;

    p[checkIndex]->setPrice1((p[checkIndex]->getPrice1() * p[checkIndex]->getAmount() + price1 * amount) / (amount + p[checkIndex]->getAmount()));
    p[checkIndex]->setAmount(p[checkIndex]->getAmount() + amount);
    return 1;
}

int addNewProductByName(vector<unique_ptr<Product>> & p, string name, int type, float price1, float price2, int amount, string typeOfSkin, string aroma, string color, string benefit) {
    int checkIndex = findProductByName(p, name);
    if (checkIndex != -1) return 0;

    time_t t = time(0);
    stringstream ss;
    string id;
    ss << t;
    ss >> id;
    if (name.compare("")==0) return 0;
    if (type==-1) return 0;
    if (price1==-1) return 0;
    if (price2==-1) return 0;
    if (amount==-1) return 0;

    if (type == 0) {
        if (typeOfSkin.compare("")==0) return 0;
        if (aroma.compare("")==0) return 0;
        p.push_back(unique_ptr<Product>(new Cleanser(id, name, type, price1, price2, amount, typeOfSkin, aroma)));
    }
    if (type == 1) {
        if (color.compare("")==0) return 0;
        p.push_back(unique_ptr<Product>(new Lipstick(id, name, type, price1, price2, amount, color)));
    }
    if (type == 2) {
        if (benefit.compare("")==0) return 0;
        p.push_back(unique_ptr<Product>(new Lotion(id, name, type, price1, price2, amount, benefit)));
    }
    return 1;
}

int removeProductByName(vector<unique_ptr<Product>> & p, string name) {
    int removeIndex = findProductByName(p, name);

    if (name.compare("")==0) return 0;

    if (removeIndex == -1) {
        return -1;
    }

    p.erase(next(p.begin(), removeIndex));
    return 1;
}

int saleProductByName(vector<unique_ptr<Product>> & p, string name, int amount) {
    if (name.compare("")==0) return -2;
    if (amount==-1) return -2;

    int checkIndex = findProductByName(p, name);
    // not found
    if (checkIndex == -1) return 0;
    // not enough
    if (p[checkIndex]->getAmount() < amount) return -1;
    // if enough and equal, then minus amount
    if (p[checkIndex]->getAmount() >= amount) {
        p[checkIndex]->setAmount(p[checkIndex]->getAmount() - amount);
        return 1;
    }
}

vector<int> filterProduct(vector<unique_ptr<Product>>& p, vector<unique_ptr<Product>>& filterP, vector<int> sortIndexs, int filterType) {
    filterP.clear();
    sortIndexs.clear();
//   filter type = -1 -> initial
    if (filterType == -1) {
        int cnt = 0;
        for (int i = 0; i < p.size(); i++) {
            if (p[i]->getType() == 0) {
                string id = p[i]->getId();
                string name = p[i]->getName();
                int type = p[i]->getType();
                float price1 = p[i]->getPrice1();
                float price2 = p[i]->getPrice2();
                int amount = p[i]->getAmount();
                string specialInfo = p[i]->getSpecialInfo();

                // Split Start specialInfo
                string delim = ",";
                int cnt = 0;
                //cout << myText << endl;
                auto start = 0U;
                auto end = specialInfo.find(delim);
                string typeOfSkin;
                string aroma;
                while (end != string::npos)
                {
                    //cout << cnt << endl;
                    string value = specialInfo.substr(start, end - start);
                    //cout << value << endl;

                    if (cnt == 0) typeOfSkin = value;
                    start = end + delim.length();
                    end = specialInfo.find(delim, start);
                }
                string value = specialInfo.substr(start, end);
                //cout << value << endl;
                aroma = value;
                cnt++;
                // Split End specialInfo

                //cout << specialInfo << " - " << typeOfSkin << " - " << aroma << endl;
                filterP.push_back(unique_ptr<Product>(new Cleanser(id, name, type, price1, price2, amount, typeOfSkin, aroma)));
            }
            if (p[i]->getType() == 1) {
                string id = p[i]->getId();
                string name = p[i]->getName();
                int type = p[i]->getType();
                float price1 = p[i]->getPrice1();
                float price2 = p[i]->getPrice2();
                int amount = p[i]->getAmount();
                string color = p[i]->getSpecialInfo();
                filterP.push_back(unique_ptr<Product>(new Lipstick(id, name, type, price1, price2, amount, color)));
            }
            if (p[i]->getType() == 2) {
                string id = p[i]->getId();
                string name = p[i]->getName();
                int type = p[i]->getType();
                float price1 = p[i]->getPrice1();
                float price2 = p[i]->getPrice2();
                int amount = p[i]->getAmount();
                string benefit = p[i]->getSpecialInfo();
                filterP.push_back(unique_ptr<Product>(new Lipstick(id, name, type, price1, price2, amount, benefit)));
            }
            sortIndexs.push_back(cnt);
            cnt += 1;
        }
    }

//   filter type = 0 -> filter cleanser
    if (filterType == 0) {
        int cnt = 0;
        for (int i = 0; i < p.size(); i++) {
            if (p[i]->getType() == 0) {
                sortIndexs.push_back(cnt);
                cnt += 1;

                string id = p[i]->getId();
                string name = p[i]->getName();
                int type = p[i]->getType();
                float price1 = p[i]->getPrice1();
                float price2 = p[i]->getPrice2();
                int amount = p[i]->getAmount();
                string specialInfo = p[i]->getSpecialInfo();

                // Split Start specialInfo
                string delim = ",";
                int cnt = 0;
                //cout << myText << endl;
                auto start = 0U;
                auto end = specialInfo.find(delim);
                string typeOfSkin;
                string aroma;
                while (end != string::npos)
                {
                    //cout << cnt << endl;
                    string value = specialInfo.substr(start, end - start);
                    //cout << value << endl;

                    if (cnt == 0) typeOfSkin = value;
                    start = end + delim.length();
                    end = specialInfo.find(delim, start);
                }
                string value = specialInfo.substr(start, end);
                //cout << value << endl;
                aroma = value;
                cnt++;
                // Split End specialInfo

                //cout << specialInfo << " - " << typeOfSkin << " - " << aroma << endl;
                filterP.push_back(unique_ptr<Product>(new Cleanser(id, name, type, price1, price2, amount, typeOfSkin, aroma)));
            }

        }
    }

//	 filter type = 1 -> filter lipstick
    if (filterType == 1) {
        int cnt = 0;
        for (int i = 0; i < p.size(); i++) {
            if (p[i]->getType() == 1) {
                sortIndexs.push_back(cnt);
                cnt += 1;
                string id = p[i]->getId();
                string name = p[i]->getName();
                int type = p[i]->getType();
                float price1 = p[i]->getPrice1();
                float price2 = p[i]->getPrice2();
                int amount = p[i]->getAmount();
                string color = p[i]->getSpecialInfo();
                filterP.push_back(unique_ptr<Product>(new Lipstick(id, name, type, price1, price2, amount, color)));
            }
        }
    }

//	 filter type = 2 -> filter lotion
    if (filterType == 2) {
        int cnt = 0;
        for (int i = 0; i < p.size(); i++) {
            if (p[i]->getType() == 2) {
                sortIndexs.push_back(cnt);
                cnt += 1;
                string id = p[i]->getId();
                string name = p[i]->getName();
                int type = p[i]->getType();
                float price1 = p[i]->getPrice1();
                float price2 = p[i]->getPrice2();
                int amount = p[i]->getAmount();
                string benefit = p[i]->getSpecialInfo();
                filterP.push_back(unique_ptr<Product>(new Lipstick(id, name, type, price1, price2, amount, benefit)));
            }
        }
    }

    return sortIndexs;
}

vector<int> sortProduct(vector<unique_ptr<Product>>& filterP, vector<int> sortIndexs, int sortType) {
    vector<float> priceVector;
    for (int i = 0; i < filterP.size(); i++) {
        priceVector.push_back(filterP[i]->getPrice2());
    }

    // sortType = -1 -> initial
    if (sortType == -1) {
        sortIndexs.clear();
        for (int i = 0; i < filterP.size(); i++) {
            sortIndexs.push_back(i);
        }
    }

    // sortType = 0 -> sort by price lowest
    if (sortType == 0) {
        for (int i = 0; i < priceVector.size() - 1; i++) {
            for (int j = i + 1; j < priceVector.size(); j++) {
                if (priceVector[i] >= priceVector[j]) {
                    float tmp = priceVector[i];
                    priceVector[i] = priceVector[j];
                    priceVector[j] = tmp;
                    int tmp2 = sortIndexs[i];
                    sortIndexs[i] = sortIndexs[j];
                    sortIndexs[j] = tmp2;
                }
            }
        }
    }

    // sortType = 1 -> sort by price lowest
    if (sortType == 1) {
        for (int i = 0; i < priceVector.size() - 1; i++) {
            for (int j = i + 1; j < priceVector.size(); j++) {
                if (priceVector[i] <= priceVector[j]) {
                    float tmp = priceVector[i];
                    priceVector[i] = priceVector[j];
                    priceVector[j] = tmp;
                    int tmp2 = sortIndexs[i];
                    sortIndexs[i] = sortIndexs[j];
                    sortIndexs[j] = tmp2;
                }
            }
        }
    }

    return sortIndexs;
}

void readDataFile(vector<unique_ptr<Product>> & p, string fileName){
    string myText;
    ifstream MyReadFile(fileName);

    while (getline(MyReadFile, myText)) {
        string s = myText;
        string delim = ",";
        int cnt = 0;

        auto start = 0;
        auto end = s.find(delim);

        string id;
        string name;
        int type = -1;
        float price1;
        float price2;
        int amount;
        string typeOfSkin;
        string aroma;
        string color;
        string benefit;

        while (end != string::npos)
        {
            string value = s.substr(start, end - start);

            if (cnt == 0) id = value;
            if (cnt == 1) name = value;
            if (cnt == 2) type = stoi(value);
            if (cnt == 3) price1 = stof(value);
            if (cnt == 4) price2 = stof(value);
            if (cnt == 5) amount = stoi(value);
            if (type == 0) {
                if (cnt == 6) typeOfSkin = value;
            }
            cnt++;
            start = end + delim.length();
            end = s.find(delim, start);
        }
        string value = s.substr(start, end);
        if (type == 0) aroma = value;
        if (type == 1) color = value;
        if (type == 2) benefit = value;

        if (type == 0) p.push_back(unique_ptr<Product>(new Cleanser(id, name, type, price1, price2, amount, typeOfSkin, aroma)));
        if (type == 1) p.push_back(unique_ptr<Product>(new Lipstick(id, name, type, price1, price2, amount, color)));
        if (type == 2) p.push_back(unique_ptr<Product>(new Lotion(id, name, type, price1, price2, amount, benefit)));
    }
    MyReadFile.close();
}

void updateDataFile(vector<unique_ptr<Product>> & p, string fileName) {
    ofstream myfile;
    myfile.open(fileName);
    for (int i = 0; i < p.size(); i++) {
        //p[i].displayProduct();
        myfile << p[i]->getInfo();
        if (i != p.size() - 1) {
            myfile << "\n";
        }
    }
    myfile.close();
}

vector<unique_ptr<Product>> p;
string fileName = "D:\\Code\\Code C++\\Qt creator\\linh-product2\\dataProduct.txt";

vector<unique_ptr<Product>> filterP;
vector<int> sortIndexs;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    //Event
    connect(ui->addNewProductBtn,SIGNAL(clicked()),this, SLOT(addNewProduct()));
    connect(ui->addOldProductBtn,SIGNAL(clicked()),this, SLOT(addOldProduct()));
    connect(ui->filterSortBtn,SIGNAL(clicked()),this, SLOT(filterSortProduct()));
    connect(ui->saleProductBtn,SIGNAL(clicked()),this, SLOT(saleProduct()));
    connect(ui->removeProductBtn,SIGNAL(clicked()),this, SLOT(removeProduct()));

    readDataFile(p, fileName);

    // initial Filter and Sort

    sortIndexs = filterProduct(p, filterP, sortIndexs, -1);
    sortIndexs = sortProduct(filterP, sortIndexs, -1);

    displayFilterProductVector(filterP, sortIndexs, ui);

    updateDataFile(p, fileName);

}

void MainWindow::addNewProduct()
{
    string name;
    int type;
    float price1;
    float price2;
    int amount;
    string typeOfSkin;
    string aroma;
    string color;
    string benefit;

    name = ui->nameAddLineEdit->text().toStdString();
    typeOfSkin = ui->typeOfSkinAddLineEdit->text().toStdString();
    aroma = ui->aromaAddLineEdit->text().toStdString();
    color = ui->colorAddLineEdit->text().toStdString();
    benefit = ui->benefitAddLineEdit->text().toStdString();

    if (ui->typeAddLineEdit->text().toStdString().compare((""))==0) type = -1;
    else type =ui->typeAddLineEdit->text().toInt();

    if (ui->price1AddLineEdit->text().toStdString().compare((""))==0) price1 = -1;
    else price1 =ui->price1AddLineEdit->text().toFloat();

    if (ui->price2AddLineEdit->text().toStdString().compare((""))==0) price2 = -1;
    else price2 =ui->price2AddLineEdit->text().toFloat();

    if (ui->amountAddLineEdit->text().toStdString().compare((""))==0) amount = -1;
    else amount =ui->amountAddLineEdit->text().toInt();

//    cout << name << "-" <<type<<"-"<<price1<<"-"<<price2<<"-"<<typeOfSkin<<"-"<<aroma<<"-"<<color<<"-"<<benefit<<endl;

    int status = addNewProductByName(p, name, type, price1, price2, amount, typeOfSkin, aroma, color, benefit);

    if (status ==0){
        QMessageBox::about(this, "Add Product Error","There are something wrong");
    }
    else if (status ==1){
        updateDataFile(p,fileName);
        QMessageBox::about(this, "Add Product Successfully","Ban da them thanh cong");
        ui->nameAddLineEdit->setText("");
        sortIndexs = filterProduct(p, filterP, sortIndexs, -1);
        sortIndexs = sortProduct(filterP, sortIndexs, -1);
        displayFilterProductVector(filterP,sortIndexs,ui);
    }


//    QMessageBox::about(this, "Add Product","Ban da them thanh cong");
}

void MainWindow::addOldProduct()
{
    string name;
    float price1;
    int amount;

    name = ui->nameAddOldLineEdit->text().toStdString();

    if (ui->price1AddOldLineEdit->text().toStdString().compare((""))==0) price1 = -1;
    else price1 =ui->price1AddOldLineEdit->text().toFloat();

    if (ui->amountAddOldLineEdit->text().toStdString().compare((""))==0) amount = -1;
    else amount =ui->amountAddOldLineEdit->text().toInt();

//    cout << name << "-" <<type<<"-"<<price1<<"-"<<price2<<"-"<<typeOfSkin<<"-"<<aroma<<"-"<<color<<"-"<<benefit<<endl;

    int status = addOldProductByName(p, name, price1, amount);

    if (status ==0){
        QMessageBox::about(this, "Add Product Error","There are something wrong");
    }
    else if (status ==1){
        updateDataFile(p,fileName);
        QMessageBox::about(this, "Add Product Successfully","Ban da them thanh cong");
        ui->nameAddLineEdit->setText("");
        sortIndexs = filterProduct(p, filterP, sortIndexs, -1);
        sortIndexs = sortProduct(filterP, sortIndexs, -1);
        displayFilterProductVector(filterP,sortIndexs,ui);
    }


//    QMessageBox::about(this, "Add Product","Ban da them thanh cong");
}

void MainWindow::filterSortProduct(){
    int status = 1;
    int filterType;
    int sortType;

    if (ui->filterLineEdit->text().toStdString().compare((""))==0) filterType = -1;
    else {
        filterType =ui->filterLineEdit->text().toInt();
        if (filterType<0||filterType>2) status = 0;
    }

    if (ui->sortLineEdit->text().toStdString().compare((""))==0) sortType = -1;
    else {
        sortType =ui->sortLineEdit->text().toInt();
        if (sortType<0||sortType>1) status = 0;
    }


    if (status ==1){
        sortIndexs = filterProduct(p,filterP,sortIndexs,filterType);
        sortIndexs = sortProduct(filterP,sortIndexs,sortType);
        ui->productListWidget->clear();
        displayFilterProductVector(filterP,sortIndexs,ui);
    }
    else if (status ==0){
        QMessageBox::about(this, "Filter Error","There are something wrong");
    }
}

void MainWindow::saleProduct(){
    string name;
    int amount;

    name = ui->nameSaleLineEdit->text().toStdString();

    if (ui->amountSaleLineEdit->text().toStdString().compare((""))==0) amount = -1;
    else amount =ui->amountSaleLineEdit->text().toInt();

    cout << name << "-" << amount << endl;

    int status = saleProductByName(p, name, amount);

    if (status ==-2){
        QMessageBox::about(this, "Sale Product Error","Please enter information");
    }
    else if (status ==1){
        updateDataFile(p,fileName);
        QMessageBox::about(this, "Sale Product Successfully","Ban da ban thanh cong");
        ui->nameSaleLineEdit->setText("");
        ui->amountSaleLineEdit->setText("");
        sortIndexs = filterProduct(p, filterP, sortIndexs, -1);
        sortIndexs = sortProduct(filterP, sortIndexs, -1);
        displayFilterProductVector(filterP,sortIndexs,ui);
    }
    else if (status ==0){
        QMessageBox::about(this, "Sale Product Error","Khong co");
    }
    else {
        QMessageBox::about(this, "Sale Product Error","Khong du");
    }


//    QMessageBox::about(this, "Add Product","Ban da them thanh cong");
}

void MainWindow::removeProduct(){
    string name;

    name = ui->nameRemoveLineEdit->text().toStdString();

    int status = removeProductByName(p, name);

    if (status ==0){
        QMessageBox::about(this, "Remove Product Error","Please enter information");
    }
    else if (status ==1){
        updateDataFile(p,fileName);
        QMessageBox::about(this, "Remove Product Successfully","Ban da xoa thanh cong");
        ui->nameSaleLineEdit->setText("");
        ui->amountSaleLineEdit->setText("");
        sortIndexs = filterProduct(p, filterP, sortIndexs, -1);
        sortIndexs = sortProduct(filterP, sortIndexs, -1);
        displayFilterProductVector(filterP,sortIndexs,ui);
    }
    else if (status == -1){
        QMessageBox::about(this, "Remove Product Error","Khong co");
    }

}

MainWindow::~MainWindow()
{
    delete ui;
}

