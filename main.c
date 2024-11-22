//sri rama jayam
#include "sql_parser.h"

QueryInfo current_query;

void init_query_info() {
    memset(&current_query, 0, sizeof(QueryInfo));
}

void generate_pandas_code(QueryInfo *query) {
    printf("\nGenerated Python/Pandas code:\n");
    printf("import pandas as pd\n\n");
    
    if (strcmp(query->query_type, "SELECT") == 0) {
        printf("# Read the data\n");
        printf("df = pd.read_csv('%s.csv')\n\n", query->table_name);
        
        if (query->join_table[0] != '\0') {
            printf("# Read join table\n");
            printf("df_join = pd.read_csv('%s.csv')\n", query->join_table);
            printf("df = pd.merge(df, df_join, %s)\n\n", query->join_condition);
        }
        
        if (strcmp(query->columns[0], "*") != 0) {
            printf("# Select columns\n");
            printf("df = df[[");
            for (int i = 0; i < query->column_count; i++) {
                printf("'%s'%s", query->columns[i], 
                       (i < query->column_count - 1) ? ", " : "");
            }
            printf("]]\n\n");
        }
        
        if (strlen(query->conditions) > 0) {
            printf("# Apply conditions\n");
            printf("df = df[%s]\n\n", query->conditions);
        }
        
        if (strlen(query->group_by) > 0) {
            printf("# Group by\n");
            printf("df = df.groupby('%s').agg('sum').reset_index()\n\n", 
                   query->group_by);
        }
        
        if (strlen(query->order_by) > 0) {
            printf("# Sort values\n");
            printf("df = df.sort_values('%s', ascending=%s)\n\n", 
                   query->order_by, 
                   strcmp(query->order_direction, "ASC") == 0 ? "True" : "False");
        }
        
        printf("# Display results\n");
        printf("print(df)\n");
    }
    else if (strcmp(query->query_type, "INSERT") == 0) {
        printf("# Read existing data\n");
        printf("df = pd.read_csv('%s.csv')\n\n", query->table_name);
        
        printf("# Create new row\n");
        printf("new_row = pd.DataFrame([{");
        for (int i = 0; i < query->column_count; i++) {
            printf("'%s': %s%s", 
                   query->columns[i], 
                   query->values[i],
                   (i < query->column_count - 1) ? ", " : "");
        }
        printf("}])\n\n");
        
        printf("# Append new row\n");
        printf("df = pd.concat([df, new_row], ignore_index=True)\n");
        printf("df.to_csv('%s.csv', index=False)\n", query->table_name);
    }
    else if (strcmp(query->query_type, "UPDATE") == 0) {
        printf("# Read the data\n");
        printf("df = pd.read_csv('%s.csv')\n\n", query->table_name);
        
        if (strlen(query->conditions) > 0) {
            printf("# Apply update with condition\n");
            printf("df.loc[%s, '%s'] = %s\n", 
                   query->conditions,
                   query->columns[0],
                   query->values[0]);
        } else {
            printf("# Apply update to all rows\n");
            printf("df['%s'] = %s\n", 
                   query->columns[0],
                   query->values[0]);
        }
        
        printf("\n# Save updated data\n");
        printf("df.to_csv('%s.csv', index=False)\n", query->table_name);
    }
    else if (strcmp(query->query_type, "DELETE") == 0) {
        printf("# Read the data\n");
        printf("df = pd.read_csv('%s.csv')\n\n", query->table_name);
        
        if (strlen(query->conditions) > 0) {
            printf("# Delete rows with condition\n");
            printf("df = df[~(%s)]\n", query->conditions);
        }
        
        printf("\n# Save updated data\n");
        printf("df.to_csv('%s.csv', index=False)\n", query->table_name);
    }
    
    printf("\n");
}

int main() {
    printf("SQL to Pandas Converter\n");
    printf("Enter SQL queries (end with semicolon):\n");
    printf("Type 'quit;' to exit\n\n");

    init_query_info();
    
    while(1) {
        printf("SQL> ");
        if (yyparse() != 0) {
            printf("Error in SQL syntax. Please try again.\n");
            int c;
            while ((c = getchar()) != '\n' && c != EOF) { }
            init_query_info();
        }
    }
    
    return 0;
}
