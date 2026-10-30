# 题目：2882. 删去重复的行（Drop Duplicate Rows）
# 思路：把 email 列作为判重依据，调用 drop_duplicates 保留每个邮箱第一次出现的那一行。
# 时间复杂度：O(n)，n 为行数，逐行哈希判重一次；空间复杂度：O(n)，最坏情况下所有邮箱都不同，需存 n 条记录。
import pandas as pd  # 引入 pandas 以使用 DataFrame 接口


def dropDuplicateEmails(customers: pd.DataFrame) -> pd.DataFrame:  # 入参是客户表，返回按邮箱去重后的表
    return customers.drop_duplicates(subset=['email'])  # subset 限定只比较 email 列，默认 keep='first' 保留首次出现
