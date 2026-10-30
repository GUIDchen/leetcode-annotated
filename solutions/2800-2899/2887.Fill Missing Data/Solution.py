# 题目：2887. 填充缺失值（Fill Missing Data）
# 思路：pandas 中把 quantity 列的缺失值（NaN）用 fillna(0) 统一填成 0，其余列与行顺序保持不变。
# 时间复杂度：O(n)，n 为行数，fillna 对整列线性扫描；空间复杂度：O(1)，只替换该列的元素，不新建整张表。
import pandas as pd  # 引入 pandas，函数签名用到了 pd.DataFrame


def fillMissingValues(products: pd.DataFrame) -> pd.DataFrame:  # products：含 name、quantity 两列的商品表（quantity 可能有空值）
    products['quantity'] = products['quantity'].fillna(0)  # 取出 quantity 列，把所有缺失值替换为 0，再写回该列
    return products  # 返回填充后的表，列结构与顺序保持不变
