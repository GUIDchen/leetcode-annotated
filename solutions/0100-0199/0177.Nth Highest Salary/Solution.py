# 题目：177. 第 N 高的薪水（Nth Highest Salary）
# 思路：去重后按降序排列，取第 N 个；N < 1 或不同薪水不足 N 个时返回一行 None，保持结果表结构不变。
# 时间复杂度：O(n log n)，主要开销在排序；空间复杂度：O(n)，去重后的薪水数组与结果表。
import pandas as pd  # 导入 pandas（LeetCode 判题环境已提供）


def nth_highest_salary(employee: pd.DataFrame, N: int) -> pd.DataFrame:  # 返回第 N 高的薪水，N 由参数传入
    if N < 1:  # N 小于 1 属于非法名次（题面保证 N 从 1 开始，这里做兜底）
        return pd.DataFrame({"getNthHighestSalary(" + str(N) + ")": [None]})  # 列名按题面拼成 getNthHighestSalary(N)，返回一行 None
    unique_salaries = employee.salary.unique()  # employee.salary.unique() 去重后返回 ndarray
    if len(unique_salaries) < N:  # 不同薪水的个数不足 N 个，说明不存在第 N 高
        return pd.DataFrame([None], columns=[f"getNthHighestSalary({N})"])  # 返回一行 None，列名用 f-string 拼成 getNthHighestSalary(N)
    else:  # 否则第 N 高确实存在
        salary = sorted(unique_salaries, reverse=True)[N - 1]  # 降序排序后取下标 N-1 处的值
        return pd.DataFrame([salary], columns=[f"getNthHighestSalary({N})"])  # 把薪水包装成单行单列的结果表返回
