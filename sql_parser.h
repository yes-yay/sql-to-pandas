//sri rama jayam
/* sql_parser.h */
#ifndef SQL_PARSER_H
#define SQL_PARSER_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Define QueryInfo structure
typedef struct {
    char query_type[20];        // SELECT, INSERT, UPDATE, DELETE
    char table_name[50];        // Name of the table
    char columns[10][50];       // Array of column names
    int column_count;           // Number of columns
    char conditions[256];       // WHERE conditions
    char values[10][50];        // Values for INSERT/UPDATE
    int value_count;            // Number of values
    char join_table[50];        // Name of table to join with
    char join_condition[256];   // Join condition
    char group_by[50];         // GROUP BY column
    char order_by[50];         // ORDER BY column
    char order_direction[5];    // ASC or DESC
} QueryInfo;

// Function declarations
void init_query_info();
void generate_pandas_code(QueryInfo *query);

extern QueryInfo current_query;

#endif