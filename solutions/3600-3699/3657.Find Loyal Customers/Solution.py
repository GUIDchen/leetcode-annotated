# 3657. 寻找忠实客户（Find Loyal Customers）
# 核心思路：先按 customer_id 分组聚合出交易总数、退款笔数、最早/最晚交易日期，据此算出退款率与活跃天数，再筛出交易总数不少于 3、退款率小于 20%、活跃至少 30 天的客户并按 id 升序返回。
# 复杂度：时间 O(n + c·log c)，空间 O(n + c)，其中 n 为交易记录条数、c 为客户数。
import pandas as pd  # 导入 pandas，用于按客户分组聚合交易记录


def find_loyal_customers(customer_transactions: pd.DataFrame) -> pd.DataFrame:  # 返回满足条件的忠实客户表（只含 customer_id 一列）
    customer_transactions["transaction_date"] = pd.to_datetime(  # 把交易日期列转成 datetime 类型，便于做日期差计算
        customer_transactions["transaction_date"]  # 待转换的日期列
    )  # 转换调用结束
    grouped = customer_transactions.groupby("customer_id")  # 按 customer_id 分组
    agg_df = grouped.agg(  # 对各组做多项聚合，并把分组键还原成普通列
        total_transactions=("transaction_type", "size"),  # 该客户的交易总条数（purchase 与 refund 都计入）
        refund_count=("transaction_type", lambda x: (x == "refund").sum()),  # 该客户中 transaction_type 为 refund 的条数
        min_date=("transaction_date", "min"),  # 该客户最早一次交易的日期
        max_date=("transaction_date", "max"),  # 该客户最晚一次交易的日期
    ).reset_index()  # 聚合结果转成普通 DataFrame 并重置索引
    agg_df["date_diff"] = (agg_df["max_date"] - agg_df["min_date"]).dt.days  # 活跃天数 = 最晚日期与最早日期相差的天数
    agg_df["refund_ratio"] = agg_df["refund_count"] / agg_df["total_transactions"]  # 退款率 = 退款笔数 / 交易总条数
    result = (  # 下面开始筛选并整理输出结果
        agg_df[  # 从聚合结果中按条件挑行
            (agg_df["total_transactions"] >= 3)  # 条件一：交易总数至少 3 次
            & (agg_df["refund_ratio"] < 0.2)  # 条件二：退款率小于 20%
            & (agg_df["date_diff"] >= 30)  # 条件三：活跃天数至少 30 天
        ][["customer_id"]]  # 只保留 customer_id 这一列
        .sort_values("customer_id")  # 按 customer_id 升序排序
        .reset_index(drop=True)  # 重置索引并丢弃旧索引，使输出行号从 0 开始
    )  # 结果整理结束
    return result  # 返回结果表
