# 📘 Address Book Management System (C Project)

A simple and efficient Address Book application written in **C** that allows users to create, view, search, edit, delete, and store contacts using file handling and modular programming concepts.

---

## 🚀 Features

### ✅ Create New Contact

* Add Name, Phone Number, and Email
* Input validation for all fields
* Prevents duplicate phone numbers and emails

### 🔍 Search Contact

Search by:

* Name
* Phone Number
* Email

### ✏️ Edit Contact

* Edit existing contact details
* Supports multiple matching records
* Update name, phone number, or email

### ❌ Delete Contact

* Delete using name / phone / email
* Handles duplicate matches safely
* Shifts records properly after deletion

### 📄 List All Contacts

Sort contacts by:

* Name
* Phone
* Email
* Default order (no sorting)

### 💾 Save & Load Contacts

* Contacts stored in `contacts.csv`
* Auto-load on program start
* Saves total count and individual records

---

## 📂 Project Structure

```
AddressBook
│
├── main.c
├── contact.c
├── contact.h
├── file.c
├── file.h
├── populate.c
├── populate.h
├── contacts.csv   (auto-generated)
└── README.md
```

---

## ⚙️ How It Works

### 1. Structures

```c
typedef struct {
    char name[50];
    char phone[20];
    char email[50];
} Contact;

typedef struct {
    Contact contacts[100];
    int contactCount;
} AddressBook;
```

---

### 2. Modular Functions

* Create → `createContact()`
* Search → `searchContact()`
* Edit → `editContact()`
* Delete → `deleteContact()`
* List → `listContacts()`
* Save → `saveContactsToFile()`
* Load → `loadContactsFromFile()`

---

## 🛠️ Installation & Compilation

### Compile

```bash
gcc main.c contact.c file.c populate.c -o address_book
```

### Run

```bash
./address_book
```

---

## 📋 Sample Menu

```
Address Book Menu:
1. Create contact
2. Search contact
3. Edit contact
4. Delete contact
5. List all contacts
6. Save contacts
7. Exit
Enter your choice:
```

---

## 📁 File Storage Format (contacts.csv)

Example:

```
#3
John Doe,9876543210,john@example.com
Alice,9988776655,alice@example.com
Bob,8877665544,bob@example.com
```

---

## 🧪 Dummy Data (Optional for Testing)

Enable inside `initialize()`:

```c
populateAddressBook(addressBook);
```

---

## 👩‍💻 Author

**K. Y. Vyshnavi Devi**
Address Book Management System — C Programming

---

## 🌟 Future Enhancements

* Dynamic memory allocation
* Encryption for contact file
* Enable cloud sync integration in future versions
* Add backup and restore functionality
* Develop a GUI version using C with Qt

---

⭐ If you like this project, feel free to star the repository!
