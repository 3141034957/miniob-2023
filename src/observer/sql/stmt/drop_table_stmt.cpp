#include "drop_table_stmt.h"
#include "event/sql_debug.h"

RC DropTableStmt::drop(Db* db, const std::string& table_name, Stmt*& stmt)
{
	stmt = new DropTableStmt(drop_table.relation_name);
	sql_debug("drop table statement: table name %s", table_name.c_str());
	return RC::SUCCESS;
}
