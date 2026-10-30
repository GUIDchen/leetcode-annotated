# 题目：1565. 按月统计订单数与顾客数（Unique Orders and Customers Per Month）
# 思路：先用 invoice > 20 过滤订单，再把订单日期转成「年-月」字符串，按月份分组聚合并把索引还原成列。
# 时间复杂度：O(n)，只做一次过滤与一次分组聚合；空间复杂度：O(m)，m 为不同月份的数量。
import pandas as pd  # 导入 pandas，用 DataFrame 做表格运算


def unique_orders_and_customers(orders: pd.DataFrame) -> pd.DataFrame:  # orders 是订单表，返回按月统计的结果表
    filtered_orders = orders[orders["invoice"] > 20]  # 布尔索引：只保留发票金额大于 20 的订单
    filtered_orders["month"] = (  # 新增 month 列，保存每笔订单所属的月份
        filtered_orders["order_date"].dt.to_period("M").astype(str)  # 日期先转成月度周期再转字符串，形如 "2020-07"
    )  # 赋值表达式结束
    result = (  # 分组聚合的结果表
        filtered_orders.groupby("month")  # 按月份分组
        .agg(  # 对每个分组做聚合
            order_count=("order_id", "count"), customer_count=("customer_id", "nunique")  # 订单数用 count，顾客数用 nunique 去重
        )  # 聚合参数结束
        .reset_index()  # 把分组键 month 从索引还原成普通列
    )  # 聚合表达式结束
    return result  # 返回按月统计的结果表
