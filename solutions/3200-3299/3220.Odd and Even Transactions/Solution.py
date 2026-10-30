# 题目：3220. 奇数和偶数交易（Odd and Even Transactions）
# 思路：用 where 把金额按奇偶拆成 odd_sum / even_sum 两列（不满足条件的位置填 0），再按日期分组求和并按日期排序。
# 时间复杂度：O(n log n)，分组与排序主导；空间复杂度：O(n)，新增列与结果表都需要线性空间。
import pandas as pd  # 引入 pandas，本题的输入输出都是 DataFrame


def sum_daily_odd_even(transactions: pd.DataFrame) -> pd.DataFrame:  # transactions：包含 amount、transaction_date 的交易表
    transactions["odd_sum"] = transactions["amount"].where(  # 新增一列 odd_sum：只保留奇数金额，其余位置填 0
        transactions["amount"] % 2 == 1, 0  # 条件：金额为奇数时保留原值，否则取 0
    )
    transactions["even_sum"] = transactions["amount"].where(  # 新增一列 even_sum：只保留偶数金额，其余位置填 0
        transactions["amount"] % 2 == 0, 0  # 条件：金额为偶数时保留原值，否则取 0
    )

    result = (  # 用链式调用构造结果表
        transactions.groupby("transaction_date")  # 按交易日期分组，同一天的多笔交易会被聚合到一起
        .agg(odd_sum=("odd_sum", "sum"), even_sum=("even_sum", "sum"))  # 对每组分别对 odd_sum、even_sum 两列求和并命名
        .reset_index()  # 把分组键从索引还原成普通列
    )

    result = result.sort_values("transaction_date")  # 按日期升序排序，满足题目输出顺序要求

    return result  # 返回包含日期、奇数和、偶数和三列的结果表
