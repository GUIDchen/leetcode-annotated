# 题目：2890. 重塑数据：融合（Reshape Data Melt）
# 思路：pd.melt 把「宽表」拉成「长表」——product 作为 id_vars 固定保留，其余列名收进 quarter，列值收进 sales。
# 时间复杂度：O(n)，n 为输出行数（输入行数 × 非 id 列数）；空间复杂度：O(n)，结果需要容纳全部展开的行。
import pandas as pd  # 引入 pandas，函数签名用到了 pd.DataFrame


def meltTable(report: pd.DataFrame) -> pd.DataFrame:  # report：product 列 + 各季度销量列构成的宽表
    return pd.melt(report, id_vars=['product'], var_name='quarter', value_name='sales')  # 保留 product，把列名映射为 quarter、数值映射为 sales
