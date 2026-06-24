#ifndef MYRGR_H
#define MYRGR_H

#include <iostream>
#include <string>
#include <fstream>
#include <iomanip>
#include <limits>
#include <cstring>

using namespace std;

const int MAX_SIZE = 100;

// ==========================================
// СТРУКТУРИ ДАНИХ (Інтернет-магазин)
// ==========================================

struct Product {
    int id;             // Код товару
    char name[50];      // Назва
    float price;        // Ціна
    char unit[20];      // Одиниця виміру (шт, кг, л)
};

struct Client {
    int id;             // Код клієнта
    char lastName[30];  // Прізвище
    char firstName[30]; // Ім'я
    char patronymic[30];// По батькові
    char address[50];   // Адреса
    char phone[20];     // Телефон
    char email[40];     // e-mail
    int isVip;          // Ознака постійного клієнта
};

struct Sale {
    int id;             // Код продажу
    int productId;      // Код товару
    int clientId;       // Код клієнта
    char saleDate[15];  // Дата продажу
    char deliveryDate[15];// Дата доставки
    int quantity;       // Кількість
};

// ==========================================
// ПРОТОТИПИ ФУНКЦІЙ
// ==========================================

void MainMenu();
void ProductMenu();
void ClientMenu();
void SaleMenu();

// Функції для Товарів
void AddProduct();
void ShowProducts();
void SaveProductsTXT();
void SaveProductsBIN();
void LoadProductsBIN();

// Функції для Клієнтів
void AddClient();
void ShowClients();
void SaveClientsTXT();
void SaveClientsBIN();
void LoadClientsBIN();

// Функції для Продажів
void AddSale();
void ShowSales();
void SaveSalesTXT();
void SaveSalesBIN();
void LoadSalesBIN();

// Допоміжні функції
int SafeInputInt(const string& prompt);
float SafeInputFloat(const string& prompt);
void SafeInputString(const string& prompt, char* buffer, int maxSize);

#endif