#ifndef PERSON_DAO_H 
#define PERSON_DAO_H
#include <sqlite-amalgamation-3420000/sqlite3.h>

sqlite3 *openDb(char *dbPath);
int isExistsPersonTable(sqlite3 *db);
void createPersonTable(sqlite3 *db);
void insertPersons(sqlite3 *db);
void updatePerson(sqlite3 *db);
void deletePerson(sqlite3 *db);
void deleteAllPersons(sqlite3 *db);
void printAllPersons(sqlite3 *db);
void dropPersonTable(sqlite3 *db);
void closeDb(sqlite3 *db);

#endif