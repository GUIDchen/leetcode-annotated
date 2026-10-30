# 3497. Analyze Subscription Conversion / 3497. 分析订阅转化
# 核心思路：剔除 cancelled 记录后按用户与行为类型求平均时长，分别取出 free_trial 与 paid 的平均值，再按 user_id 内连接并升序输出。
# 复杂度：时间 O(n log n)（分组与排序），空间 O(n)。

import pandas as pd  # 引入 pandas 处理数据表


def analyze_subscription_conversion(user_activity: pd.DataFrame) -> pd.DataFrame:  # 入参为用户行为表，返回每位用户的试用与付费平均时长
    df = user_activity[user_activity["activity_type"] != "cancelled"]  # 剔除取消订阅的记录，只保留有效行为

    df_grouped = (
        df.groupby(["user_id", "activity_type"])["activity_duration"]  # 按用户与行为类型分组，取活动时长列
        .mean()  # 求每组的平均时长
        .add(0.0001)  # 加上极小量修正浮点误差，避免四舍五入时出现偏差
        .round(2)  # 保留两位小数
        .reset_index()  # 把分组键还原成普通列，得到扁平表
    )

    df_free_trial = (
        df_grouped[df_grouped["activity_type"] == "free_trial"]  # 取出免费试用行为的记录
        .rename(columns={"activity_duration": "trial_avg_duration"})  # 把时长列改名为试用平均时长
        .drop(columns=["activity_type"])  # 删除已用过、无需保留的行为类型列
    )

    df_paid = (
        df_grouped[df_grouped["activity_type"] == "paid"]  # 取出付费行为的记录
        .rename(columns={"activity_duration": "paid_avg_duration"})  # 把时长列改名为付费平均时长
        .drop(columns=["activity_type"])  # 删除已用过、无需保留的行为类型列
    )

    result = df_free_trial.merge(df_paid, on="user_id", how="inner").sort_values(  # 按 user_id 内连接，只保留两种行为都有的用户
        "user_id"  # 连接键，同时作为排序依据
    )

    return result  # 返回按 user_id 升序排列的最终结果表
