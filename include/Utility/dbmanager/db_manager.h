#include "sqlite3.h"
#include <string>
#include <vector>
#include <stdexcept>

class DB_Manager
{
private:
    sqlite3 *db;

public:
    DB_Manager(const std::string &db_name)
    {
        if (sqlite3_open(db_name.c_str(), &db) != SQLITE_OK)
        {
            throw std::runtime_error("Failed to open database: " + std::string(sqlite3_errmsg(db)));
        }
    }
    ~DB_Manager()
    {
        sqlite3_close(db);
    }
    sqlite3 *get_db() const { return db; }

    class DB_Manager_Person
    {
    public:
        static void create_table(sqlite3 *db)
        {
            const char *sql = R"(
                CREATE TABLE IF NOT EXISTS Person (
                    id INTEGER PRIMARY KEY AUTOINCREMENT,
                    name TEXT NOT NULL,
                    age INTEGER,
                    type TEXT,
                    phone TEXT,
                    address TEXT
                );
            )";
            char *err_msg = nullptr;
            if (sqlite3_exec(db, sql, nullptr, nullptr, &err_msg) != SQLITE_OK)
            {
                std::string error = err_msg;
                sqlite3_free(err_msg);
                throw std::runtime_error("SQL error: " + error);
            }
        }

        static int insert_record(sqlite3 *db, const std::string &name, int age, const std::string &type,
                                 const std::string &phone, const std::string &address)
        {
            const char *sql = "INSERT INTO Person (name, age, type, phone, address) VALUES (?, ?, ?, ?, ?);";
            sqlite3_stmt *stmt;
            if (sqlite3_prepare_v2(db, sql, -1, &stmt, nullptr) != SQLITE_OK)
            {
                throw std::runtime_error("Prepare failed: " + std::string(sqlite3_errmsg(db)));
            }
            sqlite3_bind_text(stmt, 1, name.c_str(), -1, SQLITE_STATIC);
            sqlite3_bind_int(stmt, 2, age);
            sqlite3_bind_text(stmt, 3, type.c_str(), -1, SQLITE_STATIC);
            sqlite3_bind_text(stmt, 4, phone.c_str(), -1, SQLITE_STATIC);
            sqlite3_bind_text(stmt, 5, address.c_str(), -1, SQLITE_STATIC);
            if (sqlite3_step(stmt) != SQLITE_DONE)
            {
                sqlite3_finalize(stmt);
                throw std::runtime_error("Insert failed: " + std::string(sqlite3_errmsg(db)));
            }
            int id = static_cast<int>(sqlite3_last_insert_rowid(db));
            sqlite3_finalize(stmt);
            return id;
        }

        static bool delete_record(sqlite3 *db, int id)
        {
            const char *sql = "DELETE FROM Person WHERE id = ?;";
            sqlite3_stmt *stmt;
            if (sqlite3_prepare_v2(db, sql, -1, &stmt, nullptr) != SQLITE_OK)
            {
                throw std::runtime_error("Prepare failed: " + std::string(sqlite3_errmsg(db)));
            }
            sqlite3_bind_int(stmt, 1, id);
            bool success = sqlite3_step(stmt) == SQLITE_DONE && sqlite3_changes(db) > 0;
            sqlite3_finalize(stmt);
            return success;
        }

        static bool update_record(sqlite3 *db, int id, const std::string &name, int age, const std::string &type,
                                  const std::string &phone, const std::string &address)
        {
            const char *sql = "UPDATE Person SET name = ?, age = ?, type = ?, phone = ?, address = ? WHERE id = ?;";
            sqlite3_stmt *stmt;
            if (sqlite3_prepare_v2(db, sql, -1, &stmt, nullptr) != SQLITE_OK)
            {
                throw std::runtime_error("Prepare failed: " + std::string(sqlite3_errmsg(db)));
            }
            sqlite3_bind_text(stmt, 1, name.c_str(), -1, SQLITE_STATIC);
            sqlite3_bind_int(stmt, 2, age);
            sqlite3_bind_text(stmt, 3, type.c_str(), -1, SQLITE_STATIC);
            sqlite3_bind_text(stmt, 4, phone.c_str(), -1, SQLITE_STATIC);
            sqlite3_bind_text(stmt, 5, address.c_str(), -1, SQLITE_STATIC);
            sqlite3_bind_int(stmt, 6, id);
            bool success = sqlite3_step(stmt) == SQLITE_DONE && sqlite3_changes(db) > 0;
            sqlite3_finalize(stmt);
            return success;
        }

        static std::vector<std::string> get_column_values(sqlite3 *db, const std::string &column_name)
        {
            std::string sql = "SELECT " + column_name + " FROM Person;";
            sqlite3_stmt *stmt;
            if (sqlite3_prepare_v2(db, sql.c_str(), -1, &stmt, nullptr) != SQLITE_OK)
            {
                throw std::runtime_error("Prepare failed: " + std::string(sqlite3_errmsg(db)));
            }
            std::vector<std::string> values;
            while (sqlite3_step(stmt) == SQLITE_ROW)
            {
                const unsigned char *val = sqlite3_column_text(stmt, 0);
                values.push_back(val ? std::string(reinterpret_cast<const char *>(val)) : "");
            }
            sqlite3_finalize(stmt);
            return values;
        }

        static std::vector<std::string> get_record_by_column(sqlite3 *db, const std::string &column_name,
                                                             const std::string &value)
        {
            std::string sql = "SELECT * FROM Person WHERE " + column_name + " = ? LIMIT 1;";
            sqlite3_stmt *stmt;
            if (sqlite3_prepare_v2(db, sql.c_str(), -1, &stmt, nullptr) != SQLITE_OK)
            {
                throw std::runtime_error("Prepare failed: " + std::string(sqlite3_errmsg(db)));
            }
            sqlite3_bind_text(stmt, 1, value.c_str(), -1, SQLITE_STATIC);
            std::vector<std::string> record;
            if (sqlite3_step(stmt) == SQLITE_ROW)
            {
                for (int i = 0; i < sqlite3_column_count(stmt); i++)
                {
                    const unsigned char *val = sqlite3_column_text(stmt, i);
                    record.push_back(val ? std::string(reinterpret_cast<const char *>(val)) : "");
                }
            }
            sqlite3_finalize(stmt);
            return record; // Order: id, name, age, type, phone, address
        }
    };

    class DB_Manager_Account
    {
    public:
        static void create_table(sqlite3 *db)
        {
            const char *sql = R"(
                CREATE TABLE IF NOT EXISTS Account (
                    acc_no TEXT PRIMARY KEY,
                    balance REAL NOT NULL,
                    type TEXT NOT NULL,
                    pin TEXT NOT NULL,
                    owner_name INTEGER NOT NULL,
                    FOREIGN KEY (owner_name) REFERENCES Person(id)
                );
            )";
            char *err_msg = nullptr;
            if (sqlite3_exec(db, sql, nullptr, nullptr, &err_msg) != SQLITE_OK)
            {
                std::string error = err_msg;
                sqlite3_free(err_msg);
                throw std::runtime_error("SQL error: " + error);
            }
        }

        static void insert_record(sqlite3 *db, const std::string &acc_no, double balance, const std::string &type,
                                  const std::string &pin, const std::string &owner_name)
        {
            const char *sql = "INSERT INTO Account (acc_no, balance, type, pin, owner_name) VALUES (?, ?, ?, ?, ?);";
            sqlite3_stmt *stmt;
            if (sqlite3_prepare_v2(db, sql, -1, &stmt, nullptr) != SQLITE_OK)
            {
                throw std::runtime_error("Prepare failed: " + std::string(sqlite3_errmsg(db)));
            }
            sqlite3_bind_text(stmt, 1, acc_no.c_str(), -1, SQLITE_STATIC);
            sqlite3_bind_double(stmt, 2, balance);
            sqlite3_bind_text(stmt, 3, type.c_str(), -1, SQLITE_STATIC);
            sqlite3_bind_text(stmt, 4, pin.c_str(), -1, SQLITE_STATIC);
            sqlite3_bind_text(stmt, 5, owner_name.c_str(), -1, SQLITE_STATIC);
            if (sqlite3_step(stmt) != SQLITE_DONE)
            {
                sqlite3_finalize(stmt);
                throw std::runtime_error("Insert failed: " + std::string(sqlite3_errmsg(db)));
            }
            sqlite3_finalize(stmt);
        }

        static bool delete_record(sqlite3 *db, const std::string &acc_no)
        {
            const char *sql = "DELETE FROM Account WHERE acc_no = ?;";
            sqlite3_stmt *stmt;
            if (sqlite3_prepare_v2(db, sql, -1, &stmt, nullptr) != SQLITE_OK)
            {
                throw std::runtime_error("Prepare failed: " + std::string(sqlite3_errmsg(db)));
            }
            sqlite3_bind_text(stmt, 1, acc_no.c_str(), -1, SQLITE_STATIC);
            bool success = sqlite3_step(stmt) == SQLITE_DONE && sqlite3_changes(db) > 0;
            sqlite3_finalize(stmt);
            return success;
        }

        static bool update_record(sqlite3 *db, const std::string &acc_no, double balance, const std::string &type,
                                  const std::string &pin, int owner_name)
        {
            const char *sql = "UPDATE Account SET balance = ?, type = ?, pin = ?, owner_name = ? WHERE acc_no = ?;";
            sqlite3_stmt *stmt;
            if (sqlite3_prepare_v2(db, sql, -1, &stmt, nullptr) != SQLITE_OK)
            {
                throw std::runtime_error("Prepare failed: " + std::string(sqlite3_errmsg(db)));
            }
            sqlite3_bind_double(stmt, 1, balance);
            sqlite3_bind_text(stmt, 2, type.c_str(), -1, SQLITE_STATIC);
            sqlite3_bind_text(stmt, 3, pin.c_str(), -1, SQLITE_STATIC);
            sqlite3_bind_int(stmt, 4, owner_name);
            sqlite3_bind_text(stmt, 5, acc_no.c_str(), -1, SQLITE_STATIC);
            bool success = sqlite3_step(stmt) == SQLITE_DONE && sqlite3_changes(db) > 0;
            sqlite3_finalize(stmt);
            return success;
        }

        static std::vector<std::string> get_column_values(sqlite3 *db, const std::string &column_name)
        {
            std::string sql = "SELECT " + column_name + " FROM Account;";
            sqlite3_stmt *stmt;
            if (sqlite3_prepare_v2(db, sql.c_str(), -1, &stmt, nullptr) != SQLITE_OK)
            {
                throw std::runtime_error("Prepare failed: " + std::string(sqlite3_errmsg(db)));
            }
            std::vector<std::string> values;
            while (sqlite3_step(stmt) == SQLITE_ROW)
            {
                const unsigned char *val = sqlite3_column_text(stmt, 0);
                values.push_back(val ? std::string(reinterpret_cast<const char *>(val)) : "");
            }
            sqlite3_finalize(stmt);
            return values;
        }

        static std::vector<std::string> get_record_by_column(sqlite3 *db, const std::string &column_name,
                                                             const std::string &value)
        {
            std::string sql = "SELECT * FROM Account WHERE " + column_name + " = ? LIMIT 1;";
            sqlite3_stmt *stmt;
            if (sqlite3_prepare_v2(db, sql.c_str(), -1, &stmt, nullptr) != SQLITE_OK)
            {
                throw std::runtime_error("Prepare failed: " + std::string(sqlite3_errmsg(db)));
            }
            sqlite3_bind_text(stmt, 1, value.c_str(), -1, SQLITE_STATIC);
            std::vector<std::string> record;
            if (sqlite3_step(stmt) == SQLITE_ROW)
            {
                for (int i = 0; i < sqlite3_column_count(stmt); i++)
                {
                    const unsigned char *val = sqlite3_column_text(stmt, i);
                    record.push_back(val ? std::string(reinterpret_cast<const char *>(val)) : "");
                }
            }
            sqlite3_finalize(stmt);
            return record; // Order: acc_no, balance, type, pin, owner_name
        }

        static bool account_exists(sqlite3 *db, const std::string &acc_no)
        {
            const char *sql = "SELECT acc_no FROM Account WHERE acc_no = ? LIMIT 1;";
            sqlite3_stmt *stmt;

            // Prepare the SQL statement
            if (sqlite3_prepare_v2(db, sql, -1, &stmt, nullptr) != SQLITE_OK)
            {
                throw std::runtime_error("Prepare failed: " + std::string(sqlite3_errmsg(db)));
            }

            // Bind the account number parameter
            sqlite3_bind_text(stmt, 1, acc_no.c_str(), -1, SQLITE_STATIC);

            // Execute the query and check if a row is returned
            bool exists = (sqlite3_step(stmt) == SQLITE_ROW);

            // Clean up
            sqlite3_finalize(stmt);

            return exists;
        }
    };

    class DB_Manager_Transaction
    {
    public:
        static void create_table(sqlite3 *db)
        {
            const char *sql = R"(
        CREATE TABLE IF NOT EXISTS [Transaction] (
            transaction_id INTEGER PRIMARY KEY AUTOINCREMENT,
            initiator_acc_no TEXT NOT NULL,
            destination_acc_no TEXT NOT NULL,
            timestamp TEXT NOT NULL,
            amount REAL NOT NULL,
            tax_amount REAL NOT NULL,
            type TEXT NOT NULL,
            FOREIGN KEY (initiator_acc_no) REFERENCES Account(acc_no),
            FOREIGN KEY (destination_acc_no) REFERENCES Account(acc_no)
        );
    )";
            char *err_msg = nullptr;
            if (sqlite3_exec(db, sql, nullptr, nullptr, &err_msg) != SQLITE_OK)
            {
                std::string error = err_msg;
                sqlite3_free(err_msg);
                throw std::runtime_error("SQL error: " + error);
            }
        }

        static int insert_record(sqlite3 *db, const std::string &initiator_acc_no, const std::string &destination_acc_no,
                                 const std::string &timestamp, double amount, double tax_amount, const std::string &type)
        {
            const char *sql = "INSERT INTO [Transaction] (initiator_acc_no, destination_acc_no, timestamp, amount, tax_amount, type) "
                              "VALUES (?, ?, ?, ?, ?, ?);";
            sqlite3_stmt *stmt;
            if (sqlite3_prepare_v2(db, sql, -1, &stmt, nullptr) != SQLITE_OK)
            {
                throw std::runtime_error("Prepare failed: " + std::string(sqlite3_errmsg(db)));
            }
            sqlite3_bind_text(stmt, 1, initiator_acc_no.c_str(), -1, SQLITE_STATIC);
            sqlite3_bind_text(stmt, 2, destination_acc_no.c_str(), -1, SQLITE_STATIC);
            sqlite3_bind_text(stmt, 3, timestamp.c_str(), -1, SQLITE_STATIC);
            sqlite3_bind_double(stmt, 4, amount);
            sqlite3_bind_double(stmt, 5, tax_amount);
            sqlite3_bind_text(stmt, 6, type.c_str(), -1, SQLITE_STATIC);
            if (sqlite3_step(stmt) != SQLITE_DONE)
            {
                sqlite3_finalize(stmt);
                throw std::runtime_error("Insert failed: " + std::string(sqlite3_errmsg(db)));
            }
            int id = static_cast<int>(sqlite3_last_insert_rowid(db));
            sqlite3_finalize(stmt);
            return id;
        }

        static bool delete_record(sqlite3 *db, int transaction_id)
        {
            const char *sql = "DELETE FROM [Transaction] WHERE transaction_id = ?;";
            sqlite3_stmt *stmt;
            if (sqlite3_prepare_v2(db, sql, -1, &stmt, nullptr) != SQLITE_OK)
            {
                throw std::runtime_error("Prepare failed: " + std::string(sqlite3_errmsg(db)));
            }
            sqlite3_bind_int(stmt, 1, transaction_id);
            bool success = sqlite3_step(stmt) == SQLITE_DONE && sqlite3_changes(db) > 0;
            sqlite3_finalize(stmt);
            return success;
        }

        static bool update_record(sqlite3 *db, int transaction_id, const std::string &initiator_acc_no,
                                  const std::string &destination_acc_no, const std::string &timestamp,
                                  double amount, double tax_amount, const std::string &type)
        {
            const char *sql = "UPDATE [Transaction] SET initiator_acc_no = ?, destination_acc_no = ?, timestamp = ?, "
                              "amount = ?, tax_amount = ?, type = ? WHERE transaction_id = ?;";
            sqlite3_stmt *stmt;
            if (sqlite3_prepare_v2(db, sql, -1, &stmt, nullptr) != SQLITE_OK)
            {
                throw std::runtime_error("Prepare failed: " + std::string(sqlite3_errmsg(db)));
            }
            sqlite3_bind_text(stmt, 1, initiator_acc_no.c_str(), -1, SQLITE_STATIC);
            sqlite3_bind_text(stmt, 2, destination_acc_no.c_str(), -1, SQLITE_STATIC);
            sqlite3_bind_text(stmt, 3, timestamp.c_str(), -1, SQLITE_STATIC);
            sqlite3_bind_double(stmt, 4, amount);
            sqlite3_bind_double(stmt, 5, tax_amount);
            sqlite3_bind_text(stmt, 6, type.c_str(), -1, SQLITE_STATIC);
            sqlite3_bind_int(stmt, 7, transaction_id);
            bool success = sqlite3_step(stmt) == SQLITE_DONE && sqlite3_changes(db) > 0;
            sqlite3_finalize(stmt);
            return success;
        }

        static std::vector<std::string> get_column_values(sqlite3 *db, const std::string &column_name)
        {
            std::string sql = "SELECT " + column_name + " FROM [Transaction];";
            sqlite3_stmt *stmt;
            if (sqlite3_prepare_v2(db, sql.c_str(), -1, &stmt, nullptr) != SQLITE_OK)
            {
                throw std::runtime_error("Prepare failed: " + std::string(sqlite3_errmsg(db)));
            }
            std::vector<std::string> values;
            while (sqlite3_step(stmt) == SQLITE_ROW)
            {
                const unsigned char *val = sqlite3_column_text(stmt, 0);
                values.push_back(val ? std::string(reinterpret_cast<const char *>(val)) : "");
            }
            sqlite3_finalize(stmt);
            return values;
        }

        static std::vector<std::string> get_record_by_column(sqlite3 *db, const std::string &column_name,
                                                             const std::string &value)
        {
            std::string sql = "SELECT * FROM [Transaction] WHERE " + column_name + " = ? LIMIT 1;";
            sqlite3_stmt *stmt;
            if (sqlite3_prepare_v2(db, sql.c_str(), -1, &stmt, nullptr) != SQLITE_OK)
            {
                throw std::runtime_error("Prepare failed: " + std::string(sqlite3_errmsg(db)));
            }
            sqlite3_bind_text(stmt, 1, value.c_str(), -1, SQLITE_STATIC);
            std::vector<std::string> record;
            if (sqlite3_step(stmt) == SQLITE_ROW)
            {
                for (int i = 0; i < sqlite3_column_count(stmt); i++)
                {
                    const unsigned char *val = sqlite3_column_text(stmt, i);
                    record.push_back(val ? std::string(reinterpret_cast<const char *>(val)) : "");
                }
            }
            sqlite3_finalize(stmt);
            return record; // Order: transaction_id, initiator_acc_no, destination_acc_no, timestamp, amount, tax_amount, type
        }
    };
};