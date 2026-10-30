# 题目：3716. 寻找流失风险客户（Find Churn Risk Customers）
# 思路：先按用户、日期、事件编号排序，取出每个用户的最后一条事件作为当前状态，同时聚合起始日、最后事件日、历史最高月付与降级次数；再筛出「未取消 + 至少降级一次 + 当前金额低于历史最高的一半 + 订阅满 60 天」的客户。
# 时间复杂度：O(n log n)，排序与分组为主；空间复杂度：O(n)，保存排序、分组与合并后的中间表。
import pandas as pd  # 导入 pandas，用 DataFrame 做数据处理


def find_churn_risk_customers(subscription_events: pd.DataFrame) -> pd.DataFrame:  # subscription_events：订阅事件表；返回符合流失风险条件的客户表
    subscription_events["event_date"] = pd.to_datetime(  # 第一步：把事件日期列转成 datetime，便于做日期差
        subscription_events["event_date"]  # 原始日期列（可能是字符串）
    )  # 类型转换表达式结束
    subscription_events = subscription_events.sort_values(  # 按用户、日期、事件编号升序排序
        ["user_id", "event_date", "event_id"]  # 事件编号作为同一天事件内的决胜键，保证顺序确定
    )  # 排序表达式结束
    last_events = (  # 第二步：取每个用户的最后一条事件作为当前状态
        subscription_events.groupby("user_id")  # 按用户分组
        .tail(1)[["user_id", "event_type", "plan_name", "monthly_amount"]]  # 每组取最后一行（排序后即最新事件），只保留需要的列
        .rename(  # 重命名列，便于与聚合表区分
            columns={  # 旧列名 -> 新列名
                "event_type": "last_event_type",  # 最后事件类型（用于排除 cancel）
                "plan_name": "current_plan",  # 当前套餐名
                "monthly_amount": "current_monthly_amount",  # 当前月付金额
            }  # 列名映射结束
        )  # 重命名表达式结束
    )  # 第二步表达式结束

    agg_df = (  # 第三步：按用户聚合出流失判断所需的统计量
        subscription_events.groupby("user_id")  # 按用户分组
        .agg(  # 一次性计算多个聚合列
            start_date=("event_date", "min"),  # 订阅起始日：最早的事件日期
            last_event_date=("event_date", "max"),  # 最后事件日期：最晚的事件日期
            max_historical_amount=("monthly_amount", "max"),  # 历史最高月付金额
            downgrade_count=("event_type", lambda x: (x == "downgrade").sum()),  # 降级事件次数：统计 event_type 等于 downgrade 的行数
        )  # 聚合表达式结束
        .reset_index()  # 把 user_id 从分组索引还原为普通列
    )  # 第三步表达式结束

    merged = pd.merge(agg_df, last_events, on="user_id", how="inner")  # 第四步：按用户内连接聚合表与最后事件表
    merged["days_as_subscriber"] = (  # 第五步：计算订阅天数 = 最后事件日 - 起始日
        merged["last_event_date"] - merged["start_date"]  # 两个日期相减得到 timedelta
    ).dt.days  # 取出整数天数

    result = merged[  # 第六步：按四项流失风险条件筛选
        (merged["last_event_type"] != "cancel")  # 条件一：最后事件不是取消，说明客户仍在订阅
        & (merged["downgrade_count"] >= 1)  # 条件二：至少降级过一次
        & (merged["current_monthly_amount"] < 0.5 * merged["max_historical_amount"])  # 条件三：当前金额不足历史最高的一半
        & (merged["days_as_subscriber"] >= 60)  # 条件四：订阅已满 60 天
    ][  # 接着只挑出输出需要的列
        [  # 输出列清单
            "user_id",  # 客户编号
            "current_plan",  # 当前套餐
            "current_monthly_amount",  # 当前月付金额
            "max_historical_amount",  # 历史最高月付金额
            "days_as_subscriber",  # 订阅天数
        ]  # 输出列清单结束
    ]  # 筛选与取列表达式结束

    result = result.sort_values(  # 第七步：先按订阅天数降序、再按用户编号升序排序
        ["days_as_subscriber", "user_id"], ascending=[False, True]  # 排序键与各自的排序方向
    ).reset_index(drop=True)  # 丢弃旧索引，重建 0..m-1 的连续索引
    return result  # 返回最终结果表
