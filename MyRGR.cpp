#include "MyRGR.h"

Product products[MAX_SIZE];
int productCount = 0;

Client clients[MAX_SIZE];
int clientCount = 0;

Sale sales[MAX_SIZE];
int saleCount = 0;

// ==========================================
// ВИРІВНЮВАННЯ ТАБЛИЦЬ
// ==========================================
int GetUTF8Length(const string& str) {
    int length = 0;
    for (char c : str) {
        if ((c & 0xC0) != 0x80) length++;
    }
    return length;
}

string AlignString(const string& str, int width) {
    int len = GetUTF8Length(str);
    string result = str;
    if (len < width) result.append(width - len, ' ');
    return result;
}

string GetFirstChar(const string& str) {
    if (str.empty()) return "";
    int len = 1;
    while (len < str.length() && (str[len] & 0xC0) == 0x80) len++;
    return str.substr(0, len);
}

// ==========================================
// БЕЗПЕЧНИЙ ВВІД
// ==========================================
int SafeInputInt(const string& prompt) {
    int value;
    while (true) {
        cout << prompt;
        if (cin >> value) {
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            return value;
        } else {
            cout << "Помилка! Введiть цiле число.\n";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
    }
}

float SafeInputFloat(const string& prompt) {
    float value;
    while (true) {
        cout << prompt;
        if (cin >> value) {
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            return value;
        } else {
            cout << "Помилка! Введiть число.\n";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
    }
}

void SafeInputString(const string& prompt, char* buffer, int maxSize) {
    cout << prompt;
    string input;
    getline(cin, input);
    strncpy(buffer, input.c_str(), maxSize - 1);
    buffer[maxSize - 1] = '\0';
}

// ==========================================
// ГОЛОВНЕ МЕНЮ
// ==========================================
void MainMenu() {
    setlocale(LC_ALL, ""); 
    int choice;
    do {
        cout << "\n=========================================\n";
        cout << " IНТЕРНЕТ-МАГАЗИН (Головне меню)\n";
        cout << "=========================================\n";
        cout << "1. Товари\n2. Клiєнти\n3. Продажi\n0. Вихiд\n";
        cout << "=========================================\n";
        choice = SafeInputInt("Ваш вибiр: ");

        switch (choice) {
            case 1: ProductMenu(); break;
            case 2: ClientMenu(); break;
            case 3: SaleMenu(); break;
            case 0: cout << "Роботу завершено!\n"; break;
            default: cout << "Некоректний вибiр!\n"; break;
        }
    } while (choice != 0);
}

// ==========================================
// 1. ТОВАРИ
// ==========================================
void ProductMenu() {
    int choice;
    do {
        cout << "\n--- ТОВАРИ ---\n";
        cout << "1. Додати товар\n2. Вивести товари\n3. Редагувати\n4. Сортувати\n5. Зберегти (TXT)\n6. Зберегти (BIN)\n7. Завантажити (BIN)\n0. Назад\n";
        choice = SafeInputInt("Вибiр: ");
        switch (choice) {
            case 1: AddProduct(); break;
            case 2: ShowProducts(); break;
            case 3: EditProduct(); break;
            case 4: SortProducts(); break;
            case 5: SaveProductsTXT(); break;
            case 6: SaveProductsBIN(); break;
            case 7: LoadProductsBIN(); break;
        }
    } while (choice != 0);
}

void AddProduct() {
    if (productCount >= MAX_SIZE) return;
    Product p;
    p.id = SafeInputInt("Код товару: ");
    SafeInputString("Назва: ", p.name, 50);
    p.price = SafeInputFloat("Цiна: ");
    SafeInputString("Одиниця вимiру (шт, кг, л): ", p.unit, 20);
    products[productCount++] = p;
    cout << "Товар додано!\n";
}

void ShapkaProducts() {
    cout << string(80, '-') << "\n";
    cout << "| " << AlignString("Код", 4) 
         << " | " << AlignString("Назва товару", 41) 
         << " | " << AlignString("Цiна", 10) 
         << " | " << AlignString("Од. вимiру", 12) << " |\n";
    cout << string(80, '-') << "\n";
}

void ShowProducts() {
    if (productCount == 0) { cout << "Порожньо.\n"; return; }
    ShapkaProducts();
    for (int i = 0; i < productCount; i++) {
        cout << "| " << left << setw(4) << products[i].id 
             << " | " << AlignString(products[i].name, 41) 
             << " | " << left << setw(10) << products[i].price 
             << " | " << AlignString(products[i].unit, 12) << " |\n";
    }
    cout << string(80, '-') << "\n";
}

void EditProduct() {
    int id = SafeInputInt("Введiть код товару для редагування: ");
    for(int i=0; i<productCount; i++) {
        if(products[i].id == id) {
            cout << "Вводьте новi данi:\n";
            SafeInputString("Назва: ", products[i].name, 50);
            products[i].price = SafeInputFloat("Цiна: ");
            SafeInputString("Одиниця вимiру: ", products[i].unit, 20);
            cout << "Товар оновлено!\n";
            return;
        }
    }
    cout << "Товар з таким кодом не знайдено.\n";
}

void SortProducts() {
    for(int i=0; i<productCount-1; i++) {
        for(int j=0; j<productCount-i-1; j++) {
            if(products[j].id > products[j+1].id) {
                Product temp = products[j];
                products[j] = products[j+1];
                products[j+1] = temp;
            }
        }
    }
    cout << "Товари вiдсортовано за кодом!\n";
}

void SaveProductsTXT() {
    ofstream f("Goods.txt");
    for (int i=0; i<productCount; i++) f << products[i].id << "|" << products[i].name << "|" << products[i].price << "|" << products[i].unit << "\n";
    f.close(); cout << "Збережено у Goods.txt\n";
}
void SaveProductsBIN() {
    FILE *f = fopen("Goods.dat", "wb"); fwrite(products, sizeof(Product), productCount, f); fclose(f);
}
void LoadProductsBIN() {
    FILE *f = fopen("Goods.dat", "rb"); if(f) { productCount = fread(products, sizeof(Product), MAX_SIZE, f); fclose(f); }
}

// ==========================================
// 2. КЛІЄНТИ
// ==========================================
void ClientMenu() {
    int choice;
    do {
        cout << "\n--- КЛIЄНТИ ---\n";
        cout << "1. Додати клiєнта\n2. Вивести клiєнтiв\n3. Редагувати\n4. Сортувати\n5. Зберегти (TXT)\n6. Зберегти (BIN)\n7. Завантажити (BIN)\n0. Назад\n";
        choice = SafeInputInt("Вибiр: ");
        switch (choice) {
            case 1: AddClient(); break;
            case 2: ShowClients(); break;
            case 3: EditClient(); break;
            case 4: SortClients(); break;
            case 5: SaveClientsTXT(); break;
            case 6: SaveClientsBIN(); break;
            case 7: LoadClientsBIN(); break;
        }
    } while (choice != 0);
}

void AddClient() {
    if (clientCount >= MAX_SIZE) return;
    Client c;
    c.id = SafeInputInt("Код клiєнта: ");
    SafeInputString("Прiзвище: ", c.lastName, 30);
    SafeInputString("Iм'я: ", c.firstName, 30);
    SafeInputString("По батьковi: ", c.patronymic, 30);
    SafeInputString("Адреса: ", c.address, 50);
    SafeInputString("Телефон: ", c.phone, 20);
    SafeInputString("E-mail: ", c.email, 40);
    c.isVip = SafeInputInt("Постiйний клiєнт? (1-Так, 0-Нi): ");
    clients[clientCount++] = c;
    cout << "Клiєнта додано!\n";
}

void ShapkaClients() {
    cout << string(80, '-') << "\n";
    cout << "| " << AlignString("Код", 4) 
         << " | " << AlignString("ПIБ", 15) 
         << " | " << AlignString("Телефон", 13) 
         << " | " << AlignString("E-mail", 16) 
         << " | " << AlignString("Адреса", 12) 
         << " | " << AlignString("V", 1) << " |\n";
    cout << string(80, '-') << "\n";
}

void ShowClients() {
    if (clientCount == 0) { cout << "Порожньо.\n"; return; }
    ShapkaClients();
    for (int i = 0; i < clientCount; i++) {
        string pib = string(clients[i].lastName);
        if (strlen(clients[i].firstName) > 0) pib += " " + GetFirstChar(clients[i].firstName) + ".";
        if (strlen(clients[i].patronymic) > 0) pib += GetFirstChar(clients[i].patronymic) + ".";

        cout << "| " << left << setw(4) << clients[i].id 
             << " | " << AlignString(pib, 15) 
             << " | " << AlignString(clients[i].phone, 13) 
             << " | " << AlignString(clients[i].email, 16) 
             << " | " << AlignString(clients[i].address, 12) 
             << " | " << left << setw(1) << (clients[i].isVip ? "1" : "0") << " |\n";
    }
    cout << string(80, '-') << "\n";
}

void EditClient() {
    int id = SafeInputInt("Введiть код клiєнта для редагування: ");
    for(int i=0; i<clientCount; i++) {
        if(clients[i].id == id) {
            cout << "Вводьте новi данi:\n";
            SafeInputString("Прiзвище: ", clients[i].lastName, 30);
            SafeInputString("Iм'я: ", clients[i].firstName, 30);
            SafeInputString("По батьковi: ", clients[i].patronymic, 30);
            SafeInputString("Адреса: ", clients[i].address, 50);
            SafeInputString("Телефон: ", clients[i].phone, 20);
            SafeInputString("E-mail: ", clients[i].email, 40);
            clients[i].isVip = SafeInputInt("Постiйний клiєнт? (1-Так, 0-Нi): ");
            cout << "Клiєнта оновлено!\n";
            return;
        }
    }
    cout << "Клiєнта з таким кодом не знайдено.\n";
}

void SortClients() {
    for(int i=0; i<clientCount-1; i++) {
        for(int j=0; j<clientCount-i-1; j++) {
            if(clients[j].id > clients[j+1].id) {
                Client temp = clients[j];
                clients[j] = clients[j+1];
                clients[j+1] = temp;
            }
        }
    }
    cout << "Клiєнтiв вiдсортовано за кодом!\n";
}

void SaveClientsTXT() {
    ofstream f("Clients.txt");
    for (int i=0; i<clientCount; i++) f << clients[i].id << "|" << clients[i].lastName << "|" << clients[i].phone << "\n";
    f.close(); cout << "Збережено у Clients.txt\n";
}
void SaveClientsBIN() {
    FILE *f = fopen("Clients.dat", "wb"); fwrite(clients, sizeof(Client), clientCount, f); fclose(f);
}
void LoadClientsBIN() {
    FILE *f = fopen("Clients.dat", "rb"); if(f) { clientCount = fread(clients, sizeof(Client), MAX_SIZE, f); fclose(f); }
}

// ==========================================
// 3. ПРОДАЖІ
// ==========================================
void SaleMenu() {
    int choice;
    do {
        cout << "\n--- ПРОДАЖI ---\n";
        cout << "1. Додати продаж\n2. Вивести продажi\n3. Редагувати\n4. Сортувати\n5. Зберегти (TXT)\n6. Зберегти (BIN)\n7. Завантажити (BIN)\n0. Назад\n";
        choice = SafeInputInt("Вибiр: ");
        switch (choice) {
            case 1: AddSale(); break;
            case 2: ShowSales(); break;
            case 3: EditSale(); break;
            case 4: SortSales(); break;
            case 5: SaveSalesTXT(); break;
            case 6: SaveSalesBIN(); break;
            case 7: LoadSalesBIN(); break;
        }
    } while (choice != 0);
}

void AddSale() {
    if (saleCount >= MAX_SIZE) return;
    Sale s;
    s.id = SafeInputInt("Код продажу: ");
    s.productId = SafeInputInt("Код товару: ");
    s.clientId = SafeInputInt("Код клiєнта: ");
    SafeInputString("Дата продажу: ", s.saleDate, 15);
    SafeInputString("Дата доставки: ", s.deliveryDate, 15);
    s.quantity = SafeInputInt("Кiлькiсть: ");

    float price = 0;
    for (int i = 0; i < productCount; i++) {
        if (products[i].id == s.productId) { price = products[i].price; break; }
    }

    int clientIndex = -1;
    for (int i = 0; i < clientCount; i++) {
        if (clients[i].id == s.clientId) { clientIndex = i; break; }
    }

    if (clientIndex != -1 && price > 0) {
        float totalSum = price * s.quantity;
        
        if (clients[clientIndex].isVip == 1) {
            totalSum = totalSum * 0.98; 
            cout << "\n*** Застосовано знижку 2%! Сума до оплати: " << totalSum << " грн ***\n";
        } else {
            cout << "\n*** Сума до оплати: " << totalSum << " грн ***\n";
            if (totalSum > 5000) {
                clients[clientIndex].isVip = 1;
                cout << "*** Вiтаємо! Клiєнт здiйснив покупку понад 5000 грн i стає Постiйним (VIP)! ***\n";
            }
        }
    } else {
        cout << "\n(Увага: Товар або клiєнт з таким кодом ще не створенi. Сума не розрахована).\n";
    }

    sales[saleCount++] = s;
    cout << "Продаж успiшно зафiксовано!\n";
}

void ShapkaSales() {
    cout << string(80, '-') << "\n";
    cout << "| " << AlignString("Код Прод", 8) 
         << " | " << AlignString("Код Тов.", 8) 
         << " | " << AlignString("Код Кл.", 8) 
         << " | " << AlignString("Дата продажу", 14) 
         << " | " << AlignString("Дата доставки", 14) 
         << " | " << AlignString("Кiлькiсть", 9) << " |\n";
    cout << string(80, '-') << "\n";
}

void ShowSales() {
    if (saleCount == 0) { cout << "Порожньо.\n"; return; }
    ShapkaSales();
    for (int i = 0; i < saleCount; i++) {
        cout << "| " << left << setw(8) << sales[i].id 
             << " | " << left << setw(8) << sales[i].productId 
             << " | " << left << setw(8) << sales[i].clientId 
             << " | " << AlignString(sales[i].saleDate, 14) 
             << " | " << AlignString(sales[i].deliveryDate, 14) 
             << " | " << left << setw(9) << sales[i].quantity << " |\n";
    }
    cout << string(80, '-') << "\n";
}

void EditSale() {
    int id = SafeInputInt("Введiть код продажу для редагування: ");
    for(int i=0; i<saleCount; i++) {
        if(sales[i].id == id) {
            cout << "Вводьте новi данi:\n";
            sales[i].productId = SafeInputInt("Код товару: ");
            sales[i].clientId = SafeInputInt("Код клiєнта: ");
            SafeInputString("Дата продажу: ", sales[i].saleDate, 15);
            SafeInputString("Дата доставки: ", sales[i].deliveryDate, 15);
            sales[i].quantity = SafeInputInt("Кiлькiсть: ");
            cout << "Продаж оновлено!\n";
            return;
        }
    }
    cout << "Продаж з таким кодом не знайдено.\n";
}

void SortSales() {
    for(int i=0; i<saleCount-1; i++) {
        for(int j=0; j<saleCount-i-1; j++) {
            if(sales[j].id > sales[j+1].id) {
                Sale temp = sales[j];
                sales[j] = sales[j+1];
                sales[j+1] = temp;
            }
        }
    }
    cout << "Продажi вiдсортовано за кодом!\n";
}

void SaveSalesTXT() {
    ofstream f("Sales.txt");
    for (int i=0; i<saleCount; i++) f << sales[i].id << "|" << sales[i].productId << "|" << sales[i].quantity << "\n";
    f.close(); cout << "Збережено у Sales.txt\n";
}
void SaveSalesBIN() {
    FILE *f = fopen("Sales.dat", "wb"); fwrite(sales, sizeof(Sale), saleCount, f); fclose(f);
}
void LoadSalesBIN() {
    FILE *f = fopen("Sales.dat", "rb"); if(f) { saleCount = fread(sales, sizeof(Sale), MAX_SIZE, f); fclose(f); }
}