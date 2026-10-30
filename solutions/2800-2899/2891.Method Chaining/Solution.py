# 题目：2891. 方法链（Method Chaining）
# 思路：方法链一次写完——布尔索引筛出 weight > 100 的动物，再按 weight 降序排序，最后只取 name 一列。
# 时间复杂度：O(n log n)，排序为主导项（筛选 O(n)）；空间复杂度：O(n)，筛选与排序都会产生中间副本。
import pandas as pd  # 引入 pandas，函数签名用到了 pd.DataFrame


def findHeavyAnimals(animals: pd.DataFrame) -> pd.DataFrame:  # animals：含 name、species、age、weight 四列的动物表
    return animals[animals['weight'] > 100].sort_values('weight', ascending=False)[  # 第一步用布尔索引筛出体重 > 100 的行，第二步按 weight 降序排序，第三步开始选取列
        ['name']  # 用列名列表只保留 name 列，得到题目要求的一列结果
    ]  # 方法链收尾：返回按体重降序排列的 name 列
