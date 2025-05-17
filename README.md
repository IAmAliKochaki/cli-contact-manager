# 📇 Contact Manager (CLI-Based)

A simple and practical command-line Contact Manager written in **C**, designed for learning and demonstrating structured programming, file persistence, and dynamic memory management. This is a no-frills, real-world-inspired project to manage contacts efficiently using a text-based menu interface.

---

## ✅ Features

- 📥 **Add Contacts** – Supports name, phone, email, and address fields.
- 🔍 **Search Contacts** – Quick lookup by name using **binary search** on sorted data.
- 📄 **View All Contacts** – Neatly lists all saved contacts in order.
- ❌ **Delete Contacts** – Deletes contact by name and updates the list.
- 💾 **Persistent Storage** – Saves all contact data in a binary file (`contacts.dat`).
- 🔢 **Sorted Insertion** – Maintains contacts in alphabetical order by name.
- 📞 **Phone Number Uniqueness** – Prevents duplicate phone numbers.
- 🧠 **Modular Design** – Easy to maintain, extend, and reuse.
- 🛠️  **Inline Helpers** – Useful utilities for trimming input and formatting output.

---

## 📁 Project Structure
  ```
    src/
    ├── main.c # Entry point
    ├── contact.h # Contact struct and utility functions
    ├── contact_manager.c # Core logic (add, delete, search, save, load)
    ├── contact_manager.h
    ├── menu.c # Menu interface and user interactions
    ├── menu.h
    db/
    └── contacts.dat # Binary file to persist contacts
  ```

---

## 🚀 Getting Started

### Build
```bash
gcc -o contact_manager src/*.c
```

### Run
```bash
./contact_manager
```
  Make sure db/ directory exists before the first run.

---

## 📌 Future Improvements

  - **Remove fixed contact limit:**
      Replace static or fixed-size malloc with a dynamically resizable array using realloc to allow unlimited contacts.
      Expand the array automatically as new contacts are added.

  - **Load/Save in Multiple Formats:**
      Support **JSON**, **CSV**, and **TXT** for portability and backup.

  - **Edit Contacts:**
      Allow updating contact details (name, phone, email) without deleting.

  - **Input Validation:**
      Validate emails (proper format) and phone numbers (digits only, optional country code).

  - **Advanced Search:**
      Enable case-insensitive partial matches in name, email, or phone.

  - **Search Result Highlighting:**
      Highlight matched search terms in the output.

  - **Sort Options:**
      Sort contacts by name, phone, or email.
