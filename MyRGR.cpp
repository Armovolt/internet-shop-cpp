#include "MyRGR.h"

Product products[MAX_SIZE];
int productCount = 0;

Client clients[MAX_SIZE];
int clientCount = 0;

Sale sales[MAX_SIZE];
int saleCount = 0;

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
        cout << "1. Товари\n";
        cout << "2. Клiєнти\n";
        cout << "3. Продажi\n";
        cout << "0. Вихiд\n";
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
        cout << "1. Додати товар\n2. Вивести товари\n3. Зберегти (TXT)\n4. Зберегти (BIN)\n5. Завантажити (BIN)\n0. Назад\n";
        choice = SafeInputInt("Вибiр: ");
        switch (choice) {
            case 1: AddProduct(); break;
            case 2: ShowProducts(); break;
            case 3: SaveProductsTXT(); break;
            case 4: SaveProductsBIN(); break;
            case 5: LoadProductsBIN(); break;
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

void ShowProducts() {
    if (productCount == 0) { cout << "Порожньо.\n"; return; }
    cout << string(80, '-') << "\n";
    cout << "| " << left << setw(4) << "Код" 
         << " | " << left << setw(41) << "Назва товару" 
         << " | " << left << setw(10) << "Цiна" 
         << " | " << left << setw(12) << "Од. вимiру" << " |\n";
    cout << string(80, '-') << "\n";
    for (int i = 0; i < productCount; i++) {
        cout << "| " << left << setw(4) << products[i].id 
             << " | " << left << setw(41) << products[i].name 
             << " | " << left << setw(10) << products[i].price 
             << " | " << left << setw(12) << products[i].unit << " |\n";
    }
    cout << string(80, '-') << "\n";
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
        cout << "1. Додати клiєнта\n2. Вивести клiєнтiв\n3. Зберегти (TXT)\n4. Зберегти (BIN)\n5. Завантажити (BIN)\n0. Назад\n";
        choice = SafeInputInt("Вибiр: ");
        switch (choice) {
            case 1: AddClient(); break;
            case 2: ShowClients(); break;
            case 3: SaveClientsTXT(); break;
            case 4: SaveClientsBIN(); break;
            case 5: LoadClientsBIN(); break;
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

void ShowClients() {
    if (clientCount == 0) { cout << "Порожньо.\n"; return; }
    cout << string(80, '-') << "\n";
    cout << "| " << left << setw(4) << "Код" 
         << " | " << left << setw(15) << "ПIБ" 
         << " | " << left << setw(13) << "Телефон" 
         << " | " << left << setw(14) << "E-mail" 
         << " | " << left << setw(14) << "Адреса" 
         << " | " << left << setw(1) << "V" << " |\n";
    cout << string(80, '-') << "\n";
    for (int i = 0; i < clientCount; i++) {
        string pib = string(clients[i].lastName);
        if (strlen(clients[i].firstName) > 0) pib += " " + string(1, clients[i].firstName[0]) + ".";
        if (strlen(clients[i].patronymic) > 0) pib += string(1, clients[i].patronymic[0]) + ".";
        if (pib.length() > 15) pib = pib.substr(0, 14); // Захист рамки

        cout << "| " << left << setw(4) << clients[i].id 
             << " | " << left << setw(15) << pib 
             << " | " << left << setw(13) << clients[i].phone 
             << " | " << left << setw(14) << clients[i].email 
             << " | " << left << setw(14) << clients[i].address 
             << " | " << left << setw(1) << (clients[i].isVip ? "1" : "0") << " |\n";
    }
    cout << string(80, '-') << "\n";
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
// 3. ПРОДАЖІ ТА ЛОГІКА ЗНИЖОК
// ==========================================
void SaleMenu() {
    int choice;
    do {
        cout << "\n--- ПРОДАЖI ---\n";
        cout << "1. Додати продаж\n2. Вивести продажi\n3. Зберегти (TXT)\n4. Зберегти (BIN)\n5. Завантажити (BIN)\n0. Назад\n";
        choice = SafeInputInt("Вибiр: ");
        switch (choice) {
            case 1: AddSale(); break;
            case 2: ShowSales(); break;
            case 3: SaveSalesTXT(); break;
            case 4: SaveSalesBIN(); break;
            case 5: LoadSalesBIN(); break;
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

    // ЛОГІКА ІНТЕРНЕТ-МАГАЗИНУ (Знижки 2% та VIP-статус > 5000 грн)
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
            totalSum = totalSum * 0.98; // Знижка 2%
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

void ShowSales() {
    if (saleCount == 0) { cout << "Порожньо.\n"; return; }
    cout << string(80, '-') << "\n";
    cout << "| " << left << setw(8) << "Код Прод" 
         << " | " << left << setw(8) << "Код Тов." 
         << " | " << left << setw(8) << "Код Кл." 
         << " | " << left << setw(14) << "Дата продажу" 
         << " | " << left << setw(14) << "Дата доставки" 
         << " | " << left << setw(9) << "Кiлькiсть" << " |\n";
    cout << string(80, '-') << "\n";
    for (int i = 0; i < saleCount; i++) {
        cout << "| " << left << setw(8) << sales[i].id 
             << " | " << left << setw(8) << sales[i].productId 
             << " | " << left << setw(8) << sales[i].clientId 
             << " | " << left << setw(14) << sales[i].saleDate 
             << " | " << left << setw(14) << sales[i].deliveryDate 
             << " | " << left << setw(9) << sales[i].quantity << " |\n";
    }
    cout << string(80, '-') << "\n";
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