# 题目：3705. Find Golden Hour Customers（3705. 寻找黄金时段客户）
# 核心思路：先把下单时间转成 datetime 并标记是否落在午市/晚市黄金时段，再按客户聚合出订单数、高峰单数、平均评分与有效评分个数，最后按四项指标过滤并排序。
# 复杂度：时间 O(n log n)（分组聚合与排序），空间 O(n)（中间结果表）。
import pandas as pd  # 导入 pandas 并简写为 pd，用于表格与分组运算
import numpy as np  # 导入 numpy（原解法保留的依赖，本题未直接调用）


def find_golden_hour_customers(restaurant_orders: pd.DataFrame) -> pd.DataFrame:  # 题解入口：restaurant_orders 为订单一览表，返回筛选后的客户表
    df = restaurant_orders.copy()  # 复制一份数据，避免就地修改入参
    df["order_timestamp"] = pd.to_datetime(df["order_timestamp"])  # 把下单时间列由字符串转换为 datetime 类型，便于取时间部分
    df["is_peak_hour"] = df["order_timestamp"].dt.time.between(  # 取每条订单的时间部分，判断是否落在午市高峰 11:00–14:00
        pd.to_datetime("11:00:00").time(), pd.to_datetime("14:00:00").time()  # 构造午市高峰的左、右边界时间
    ) | df["order_timestamp"].dt.time.between(  # 按位或：再叠加晚市高峰的判断（18:00–21:00）
        pd.to_datetime("18:00:00").time(), pd.to_datetime("21:00:00").time()  # 构造晚市高峰的左、右边界时间
    )  # 得到布尔列 is_peak_hour，True 表示该订单处于黄金时段
    grouped = (  # 按客户聚合出后续过滤需要的各项统计量
        df.groupby("customer_id")  # 以客户编号分组
        .agg(  # 对每组做多项聚合
            total_orders=("order_timestamp", "count"),  # 总订单数（对时间列计数即行数）
            peak_hour_count=("is_peak_hour", "sum"),  # 高峰订单数：布尔列求和即 True 的个数
            average_rating=("order_rating", lambda x: x.dropna().mean()),  # 剔除空值后的平均评分
            non_null_rating_count=("order_rating", lambda x: x.notna().sum()),  # 非空评分个数，用于判断评分覆盖率
        )  # 聚合参数结束
        .reset_index()  # 把分组键 customer_id 还原成普通列
    )  # 得到客户级的宽表 grouped
    grouped["average_rating"] = grouped["average_rating"].round(2)  # 平均评分四舍五入保留两位小数
    grouped["peak_hour_percentage"] = (  # 计算黄金时段订单占比（百分数）
        grouped["peak_hour_count"] / grouped["total_orders"] * 100  # 高峰单数 ÷ 总单数 × 100
    ).round()  # 占比四舍五入取整
    filtered = grouped[  # 用四个条件筛出黄金时段客户
        (grouped["total_orders"] >= 3)  # 条件一：总订单数不少于 3 单
        & (5 * grouped["peak_hour_count"] >= 3 * grouped["total_orders"])  # 条件二：高峰订单占比不低于 60%（交叉相乘避免浮点误差）
        & (grouped["average_rating"] >= 4.0)  # 条件三：平均评分不低于 4.0
        & (grouped["non_null_rating_count"] / grouped["total_orders"] >= 0.5)  # 条件四：有评分的订单占比不低于 50%
    ]  # 筛选条件结束
    filtered = filtered.sort_values(  # 对结果做排序
        by=["average_rating", "customer_id"], ascending=[False, False]  # 先按平均评分降序，再按客户编号降序
    )  # 排序参数结束
    return filtered[  # 只取题目要求输出的四列
        ["customer_id", "total_orders", "peak_hour_percentage", "average_rating"]  # 输出列顺序与题面一致
    ]  # 函数返回结果表
