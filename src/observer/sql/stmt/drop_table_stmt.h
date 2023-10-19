#include <string>
#include "sql/stmt/stmt.h"

class Db;

/**
 * @brief 表示删除表的语句
 * @ingroup Statement
 */
class DropTableStmt : public Stmt
{
public:
    DropTableStmt(const std::string& table_name)
        : table_name_(table_name)
    {}
    virtual ~DropTableStmt() = default;

    StmtType type() const override { return StmtType::DROP_TABLE; }

    const std::string& table_name() const { return table_name_; }

    static RC drop(Db* db, const std::string& table_name, Stmt*& stmt);

private:
    std::string table_name_;
}; #pragma once
