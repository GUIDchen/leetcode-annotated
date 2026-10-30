# 题目：183. 从不订购的客户（Customers Who Never Order）
# 思路：用 isin 判断客户 id 是否出现在订单表的 customerId 里，再取反筛出从未下单的客户，只保留姓名列并改名。
# 时间复杂度：O(n + m)，做一次集合成员判断；空间复杂度：O(n + m)，isin 内部构造的集合与结果表。
import pandas as pd  # 导入 pandas，判题环境已提供


def find_customers(customers: pd.DataFrame, orders: pd.DataFrame) -> pd.DataFrame:  # customers：客户表；orders：订单表
    # 原文注释：选出 id 不在订单表 customerId 列里的客户
    df = customers[~customers["id"].isin(orders["customerId"])]  # isin 给出布尔序列，~ 取反即「没有下过单」的客户行

    # 原文注释：只保留 name 列，并把它重命名为 Customers
    df = df[["name"]].rename(columns={"name": "Customers"})  # 双重方括号取子表（DataFrame），rename 满足输出列名要求

    return df  # 返回结果表
