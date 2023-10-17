/* Copyright (c) 2021 OceanBase and/or its affiliates. All rights reserved.
miniob is licensed under Mulan PSL v2.
You can use this software according to the terms and conditions of the Mulan PSL v2.
You may obtain a copy of Mulan PSL v2 at:
         http://license.coscl.org.cn/MulanPSL2
THIS SOFTWARE IS PROVIDED ON AN "AS IS" BASIS, WITHOUT WARRANTIES OF ANY KIND,
EITHER EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO NON-INFRINGEMENT,
MERCHANTABILITY OR FIT FOR A PARTICULAR PURPOSE.
See the Mulan PSL v2 for more details. */

//
// Created by Meiyi
//

#include <mutex>
#include "sql/parser/parse.h"
#include "common/log/log.h"
#include "sql/expr/expression.h"

RC parse(char *st, ParsedSqlNode *sqln);

CalcSqlNode::~CalcSqlNode()
{
  for (Expression *expr : expressions) {
    delete expr;
  }
  expressions.clear();
}

ParsedSqlNode::ParsedSqlNode() : flag(SCF_ERROR)
{}

ParsedSqlNode::ParsedSqlNode(SqlCommandFlag _flag) : flag(_flag)
{}

void ParsedSqlResult::add_sql_node(std::unique_ptr<ParsedSqlNode> sql_node)
{
  sql_nodes_.emplace_back(std::move(sql_node));
}

////////////////////////////////////////////////////////////////////////////////

int sql_parse(const char *st, ParsedSqlResult *sql_result);

RC parse(const char *st, ParsedSqlResult *sql_result)
{
  sql_parse(st, sql_result);
  return RC::SUCCESS;
}

int value_init_date(Value *value, const char *v)
{
  value->type = DATES;
  int y, m, d;
  sscanf(v, "%d-%d-%d", &y, &m, &d);  // not check return value eq 3, lex guarantee
  bool b = check_date(y, m, d);
  if (!b)
    return -1;
  int dv      = y * 10000 + m * 100 + d;
  value->data = malloc(sizeof(dv));  // TODO:check malloc failure
  memcpy(value->data, &dv, sizeof(dv));
  return 0;
}

bool check_date(int y, int m, int d)
{
  static int mon[] = {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
  bool       leap  = (y % 400 == 0 || (y % 100 && y % 4 == 0));
  return y > 0 && (m > 0) && (m <= 12) && (d > 0) && (d <= ((m == 2 && leap) ? 1 : 0) + mon[m]);
}

case INTS:
case DATES: {
  // 没有考虑大小端问题
  // 对int和float，要考虑字节对齐问题,有些平台下直接转换可能会跪
  int left   = *(int *)left_value;
  int right  = *(int *)right_value;
  cmp_result = left - right;
} break;

case INTS:
case DATES: {
  i1 = *(int *)pdata;
  i2 = *(int *)pkey;
  if (i1 > i2)
    return 1;
  if (i1 < i2)
    return -1;
  if (i1 == i2)
    return 0;
} break;

const char *ATTR_TYPE_NAME[] = {"undefined", "chars", "ints", "floats", "dates"};

switch (field->type()) {
    case INTS:
    case DATES: {
      deserialize_stream.clear();  // 清理stream的状态，防止多次解析出现异常
      deserialize_stream.str(file_value);

      int int_value;
      deserialize_stream >> int_value;
      if (!deserialize_stream || !deserialize_stream.eof()) {
        errmsg << "need an integer but got '" << file_values[i] << "' (field index:" << i << ")";

        rc = RC::SCHEMA_FIELD_TYPE_MISMATCH;
      } else {
        value_init_integer(&record_values[i], int_value);
      }
    }

case DATES: {
      int  value   = *(int *)(record + field_meta->offset());
      char buf[16] = {0};
      snprintf(buf,
          sizeof(buf),
          "%04d-%02d-%02d",
          value / 10000,
          (value % 10000) / 100,
          value % 100);  // 注意这里月份和天数，不足两位时需要填充0
      tuple.add(buf, strlen(buf));
    } break;
