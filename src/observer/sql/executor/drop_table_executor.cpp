#include "event/session_event.h"
#include "storage/db/db.h"
#include "drop_table_executor.h"
#include "event/sql_debug.h"

RC DropTableExecutor::execute(SQLStageEvent* sql_event)
{
    Stmt* stmt = sql_event->stmt();
    Session* session = sql_event->session_event()->session();
    ASSERT(stmt->type() == StmtType::DROP_TABLE,
        "drop table executor can not run this command: %d", static_cast<int>(stmt->type()));

    DropTableStmt* drop_table_stmt = static_cast<DropTableStmt*>(stmt);

    const char* table_name = drop_table_stmt->table_name().c_str();
    RC rc = session->get_current_db()->drop_table(table_name); // 假设有一个名为 drop_table 的函数用于删除表

    sql_debug("drop table executor: table name %s", table_name);

    return rc;
}