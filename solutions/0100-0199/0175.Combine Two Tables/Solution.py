# 题目：175. 组合两个表（Combine Two Tables）
# 思路：以 person 为左表、按 personId 左连接 address，保证没有地址的人也会保留；再从结果中挑出题目要求的四列。
# 时间复杂度：O(P + A)，pandas 哈希连接一遍扫描；空间复杂度：O(P)，需要保存合并后的结果表。
import pandas as pd  # 导入 pandas（LeetCode 判题环境已提供，无需额外安装）


def combine_two_tables(person: pd.DataFrame, address: pd.DataFrame) -> pd.DataFrame:  # 把 Person 与 Address 两张表组合，输出 firstName、lastName、city、state 四列
    return pd.merge(left=person, right=address, how="left", on="personId")[  # 以 person 为左表、按 personId 做左外连接，保证没有地址的人也不会被丢掉
        ["firstName", "lastName", "city", "state"]  # 只保留题目要求的四列，顺序也要一致
    ]  # 结束列选择并返回结果表
