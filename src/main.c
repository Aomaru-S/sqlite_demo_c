#include <stdio.h>
#include <sqlite-amalgamation-3420000/sqlite3.h>
#include "person_dao.h"

int main() {    
    sqlite3 *db = openDb("./sqlite_demo.db");

    if (isExistsPersonTable(db)) {
        deleteAllPersons(db);
    } else {
        createPersonTable(db);
    }

    insertPersons(db);

    printAllPersons(db);

    updatePerson(db);
    
    deletePerson(db);

    printAllPersons(db);

    dropPersonTable(db);

    closeDb(db);

    return 0;
}