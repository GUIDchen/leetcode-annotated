# 题目：2888. 重塑数据：连结（Reshape Data Concatenate）
# 思路：两张表列完全相同，用 pd.concat 沿行方向（axis=0）上下堆叠，并用 ignore_index=True 重排索引。
# 时间复杂度：O(n)，n 为两表行数之和（含重建索引）；空间复杂度：O(n)，结果需要容纳全部行。
import pandas as pd  # 引入 pandas，函数签名用到了 pd.DataFrame


def concatenateTables(df1: pd.DataFrame, df2: pd.DataFrame) -> pd.DataFrame:  # df1、df2：列名相同、待纵向拼接的两张表
    return pd.concat([df1, df2], ignore_index=True)  # 先把两表放进列表按行拼接，ignore_index 丢弃原索引并生成 0..n-1 连续索引
