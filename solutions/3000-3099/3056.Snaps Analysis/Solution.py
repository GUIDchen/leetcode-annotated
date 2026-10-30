# 题目：3056. 快照分析（Snaps Analysis）
# 思路：按 user_id 连接活动表与年龄表，再按 (年龄段, 活动类型) 汇总时长并透视成两列，最后算 send 与 open 各自的百分比。
# 时间复杂度：O(n log n)，主要来自分组与排序；空间复杂度：O(n)，中间表与透视表都随数据量线性增长。
import pandas as pd  # 引入 pandas，用于表格的连接、分组与透视


def snap_analysis(activities: pd.DataFrame, age: pd.DataFrame) -> pd.DataFrame:  # activities：用户活动表；age：用户年龄段表
    merged_df = pd.merge(activities, age, on="user_id")  # 用 user_id 连接两表，给每条活动补上对应的年龄段
    total_time_per_age_activity = (  # 汇总每个 (年龄段, 活动类型) 组合的总时长
        merged_df.groupby(["age_bucket", "activity_type"])["time_spent"]  # 先按年龄段和活动类型分组，再取出时长列
        .sum()  # 对每组时长求和
        .reset_index()  # 把分组键还原成普通列，得到三列结果
    )  # 汇总表达式结束
    pivot_df = total_time_per_age_activity.pivot(  # 把活动类型从行变成列，做长表转宽表
        index="age_bucket", columns="activity_type", values="time_spent"  # 行索引用年龄段，列用活动类型，单元格值用总时长
    ).reset_index()  # 把年龄段从索引还原成列，方便后面按列名计算
    pivot_df = pivot_df.fillna(0)  # 某年龄段没有某类活动时补 0，避免参与计算时出现 NaN
    pivot_df["send_perc"] = round(  # 计算 send 活动在该年龄段总时长中的占比
        100 * pivot_df["send"] / (pivot_df["send"] + pivot_df["open"]), 2  # 百分比公式：send 时长除以 send 与 open 之和，保留两位小数
    )  # send_perc 赋值语句结束
    pivot_df["open_perc"] = round(  # 计算 open 活动在该年龄段总时长中的占比
        100 * pivot_df["open"] / (pivot_df["send"] + pivot_df["open"]), 2  # 百分比公式：open 时长除以 send 与 open 之和，保留两位小数
    )  # open_perc 赋值语句结束
    return pivot_df[["age_bucket", "send_perc", "open_perc"]]  # 只保留题目要求的三列并返回
