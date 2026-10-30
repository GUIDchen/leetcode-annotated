# 题目：181. 超过经理收入的员工（Employees Earning More Than Their Managers）
# 思路：员工表自连接（员工.managerId = 经理.id），筛出工资高于其经理的行，只保留姓名列并改名。
# 时间复杂度：O(n)，merge 与向量化比较各扫一遍；空间复杂度：O(n)，自连接产生的新表。
import pandas as pd  # 导入 pandas，判题环境已提供


def find_employees(employee: pd.DataFrame) -> pd.DataFrame:  # employee：员工表，含 id、name、salary、managerId
    merged = employee.merge(  # 把员工表与自己合并，得到「员工 + 其经理」的宽表
        employee, left_on="managerId", right_on="id", suffixes=("", "_manager")  # 左边按 managerId、右边按 id 关联；右侧同名列自动加 _manager 后缀
    )  # 括号结束，merge 完成
    result = merged[merged["salary"] > merged["salary_manager"]][["name"]]  # 筛出工资大于经理工资的员工，只留姓名列
    result.columns = ["Employee"]  # 按题目要求把列名改成 Employee
    return result  # 返回结果表
