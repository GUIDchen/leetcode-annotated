# 题目：176. 第二高的薪水（Second Highest Salary）
# 思路：先对 salary 去重，再用 nlargest(2) 取最大的两个值中的第二个；不同薪水不足两个时返回一列 None，而不是空表。
# 时间复杂度：O(n)，去重与取前二都是线性；空间复杂度：O(n)，保存去重后的薪水列。
import pandas as pd  # 导入 pandas（LeetCode 判题环境已提供）


def second_highest_salary(employee: pd.DataFrame) -> pd.DataFrame:  # 返回第二高的薪水；不存在时返回 None 组成的一行
    # Drop any duplicate salary values to avoid counting duplicates as separate salary ranks
    # 中文：先对 salary 去重，避免重复值被当成不同名次
    unique_salaries = employee["salary"].drop_duplicates()  # 取出 salary 列并去掉重复值，得到互不相同的薪水

    # Sort the unique salaries in descending order and get the second highest salary
    # 中文：降序取最大的两个，其中最后一个是第二高
    second_highest = (  # 开始计算第二高薪水（在括号内跨行书写）
        unique_salaries.nlargest(2).iloc[-1] if len(unique_salaries) >= 2 else None  # 至少两个不同值时取第 2 大，否则记为 None
    )  # 括号表达式结束

    # If the second highest salary doesn't exist (e.g., there are fewer than two unique salaries), return None
    # 中文：没有第二高（不同薪水不足两个）时返回一列 None，而不是空结果
    if second_highest is None:  # 判断是否不存在第二高薪水
        return pd.DataFrame({"SecondHighestSalary": [None]})  # 返回只含一行 None 的表，列名必须是 SecondHighestSalary

    # Create a DataFrame with the second highest salary
    # 中文：把结果包装成题目要求的列名
    result_df = pd.DataFrame({"SecondHighestSalary": [second_highest]})  # 用算出的薪水构造结果表

    return result_df  # 返回结果表
