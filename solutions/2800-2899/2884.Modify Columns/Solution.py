# 题目：2884. 修改列（Modify Columns）
# 思路：对 salary 列做原地复合赋值，整列乘以 2 覆盖原值，然后返回这个 DataFrame。
# 时间复杂度：O(n)，n 为行数，每行做一次乘法；空间复杂度：O(1)，就地覆盖该列而不额外分配整张表。
import pandas as pd  # 引入 pandas 以使用 DataFrame 接口


def modifySalaryColumn(employees: pd.DataFrame) -> pd.DataFrame:  # 入参是员工表，返回 salary 翻倍后的表
    employees['salary'] *= 2  # 复合赋值，等价于 employees['salary'] = employees['salary'] * 2
    return employees  # 返回被修改过的表，作为本题结果
