# 题目：3338. 第二高的薪水 II（Second Highest Salary II）
# 思路：按 dept 分组后用 dense rank 对 salary 降序排名，再筛出名次恰好为 2 的员工，只留 emp_id 与 dept 并按 emp_id 排序。
# 时间复杂度：O(n log n)，分组排名与排序主导；空间复杂度：O(n)，用于新增 rk 列与结果集。
import pandas as pd  # 导入 pandas，LeetCode 判题环境中已预装并约定别名为 pd


def find_second_highest_salary(employees: pd.DataFrame) -> pd.DataFrame:  # employees 是员工表，含 emp_id、dept、salary 等列，返回只含 emp_id 与 dept 的表
    employees["rk"] = employees.groupby("dept")["salary"].rank(  # 按部门分组，对薪水做密集排名，结果写回新列 rk（会就地修改入参）
        method="dense", ascending=False  # dense：并列名次不跳号；ascending=False：薪水越高名次越靠前（第 1 名薪水最高）
    )  # rank 调用的右括号，结束参数列表
    second_highest = employees[employees["rk"] == 2][["emp_id", "dept"]]  # 筛选每个部门中 rk == 2 的行，再取出 emp_id、dept 两列
    return second_highest.sort_values(by="emp_id")  # 按 emp_id 升序排序后返回，满足题目要求的输出顺序
