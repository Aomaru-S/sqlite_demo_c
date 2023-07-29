#include <stdio.h>
#include <stdlib.h>
#include <sqlite-amalgamation-3420000/sqlite3.h>
#include "person_dao.h"

sqlite3 *openDb(char *dbPath) {
    sqlite3 *db;
    int result = sqlite3_open_v2(dbPath, &db, SQLITE_OPEN_READWRITE | SQLITE_OPEN_CREATE, NULL);
    if (result != SQLITE_OK) {
        printf(sqlite3_errmsg(db));
        exit(result);
    }

    printf("Database opened.\n\n");
    return db;
}

int isExistsPersonTable(sqlite3 *db) {
    sqlite3_stmt *prepareStatement;
    char sql[] = "select count(*) from sqlite_master where type='table' and name='person'";
    printf("SQL> %s\n", sql);

    int result = sqlite3_prepare_v2(db, sql, -1, &prepareStatement, 0);
    if (result != SQLITE_OK) {
        printf(sqlite3_errmsg(db));
        exit(result);
    }

    sqlite3_step(prepareStatement);
    int count = sqlite3_column_int(prepareStatement, 0);
    printf("%d\n\n", count);

    sqlite3_finalize(prepareStatement);

    return count >= 1;
}

void createPersonTable(sqlite3 *db) {
    char sql[] = "create table person ("
        "id text primary key,"
        "name text,"
        "age integer)";
    printf("SQL> %s\n", sql);

    int result = sqlite3_exec(db, sql, NULL, NULL, NULL);
    if (result != SQLITE_OK) {
        printf(sqlite3_errmsg(db));
        exit(result);
    }

    printf("person\n\n");
}

void insertPersons(sqlite3 *db) {
    char sql[] = "insert into person values"
        "('001', 'Taro Yamamoto', 24),"
        "('002', 'Hanako Tanaka', 23)";
    printf("SQL> %s\n", sql);

    int result = sqlite3_exec(db, sql, NULL, NULL, NULL);
    int affectedRows = sqlite3_changes(db);
    if (result != SQLITE_OK) {
        printf(sqlite3_errmsg(db));
        exit(result);
    }

    printf("%d rows inserted.\n\n", affectedRows);
}

void updatePerson(sqlite3 *db) {
    char sql[] = "update person set name = 'Hanako Yamamoto' where id = '002'";
    printf("SQL> %s\n", sql);

    int result = sqlite3_exec(db, sql, NULL, NULL, NULL);
    int affectedRows = sqlite3_changes(db);
    if (result != SQLITE_OK) {
        printf(sqlite3_errmsg(db));
        exit(result);
    }

    printf("%d rows updated.\n\n", affectedRows);
}

void deletePerson(sqlite3 *db) {
    char sql[] = "delete from person where id = '001'";
    printf("SQL> %s\n", sql);

    int result = sqlite3_exec(db, sql, NULL, NULL, NULL);
    int affectedRows = sqlite3_changes(db);
    if (result
     != SQLITE_OK) {
        printf(sqlite3_errmsg(db));
        exit(result);
    }

    printf("%d rows deleted.\n\n", affectedRows);
}

void deleteAllPersons(sqlite3 *db) {
    char sql[] = "delete from person";
    printf("SQL> %s\n", sql);

    int result = sqlite3_exec(db, sql, NULL, NULL, NULL);
    int affectedRows = sqlite3_changes(db);
    if (result != SQLITE_OK) {
        printf(sqlite3_errmsg(db));
        exit(result);
    }

    printf("%d rows deleted.\n\n", affectedRows);
}

void printAllPersons(sqlite3 *db) {
    char sql[] = "select * from person";
    printf("SQL> %s\n", sql);

    sqlite3_stmt *prepareStatement;
    int result = sqlite3_prepare_v2(db, sql, -1, &prepareStatement, 0);
    if (result != SQLITE_OK) {
        printf(sqlite3_errmsg(db));
        exit(result);
    }

    printf("======== Person ========\n");
    result = sqlite3_step(prepareStatement);
    while (result == SQLITE_ROW) {
        printf("%s | %s | %d\n",
            sqlite3_column_text(prepareStatement, 0),
            sqlite3_column_text(prepareStatement, 1),
            sqlite3_column_int(prepareStatement, 2)
        );
        result = sqlite3_step(prepareStatement);
    }
    printf("\n");

    result = sqlite3_finalize(prepareStatement);
    if (result != SQLITE_OK) {
        printf(sqlite3_errmsg(db));
        exit(result);
    }
}

void dropPersonTable(sqlite3 *db) {
    char sql[] = "drop table person";
    printf("SQL> %s\n", sql);

    int result = sqlite3_exec(db, sql, NULL, NULL, NULL);
    if (result != SQLITE_OK) {
        printf(sqlite3_errmsg(db));
        exit(result);
    }

    printf("person\n\n");
}

void closeDb(sqlite3 *db) {
    int result = sqlite3_close_v2(db);
    if (result != SQLITE_OK) {
        printf(sqlite3_errmsg(db));
        exit(result);
    }

    printf("Database closed.\n\n");
}