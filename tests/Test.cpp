#include <iostream>
#include <string>
#include "Tables/Table.h"
#include "Tables/Column.h"
#include "Tables/NumericalColumn.h"

int main() {

    tables::Column<int> col1;
    tables::Column<std::string> col3;
    tables::Column<float> col2;
    tables::ColumnBase* col1P;
    tables::ColumnBase* col2P;
    tables::Table table;
    

    //col1P = (tables::ColumnBase*) &col1;

    //col1P = new tables::NumericalColumn<double>;
    
    col1.add(1);
    col1.add(2);
    col2.add(3.0);
    col2.add(4.0);
    col3.add("Tim");
    col3.add("Oborn");

    //table.addColumn<int>("Ints", col1);
    //table.addColumn<float>(col2);
    table.addColumn<std::string>("Strings", col3);
    table.col<std::string>("Stringss");

    table.print();
/*
    table.col<std::string>("Strings").row(1) = "bo";
    table.print();
    
    table.at<std::string>("Strings", 1) = "bro";
    //table.removeCol("Ints");
    table.print();

    std::cout << table.col<int>("Ints").sum() << "\n";
    std::cout << table.sum<float>("Floats") << "\n";
/*
    table.addColumn(col1);
    table.addColumn(col2);
    table.addColumn(col3);
    table.print();

    table.col<std::string>(2).row(1) = "bo";
    table.print();
    
    table.at<std::string>(2, 1) = "bro";
    table.removeCol(0);
    table.print();

    std::cout << table.col<int>(0).sum() << "\n";
    std::cout << table.sum<float>(1) << "\n";
 */   //delete col1P;
    return 0;
}
