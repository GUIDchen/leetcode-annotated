# 3673. Find Zombie Sessions（查找僵尸会话）
# 核心思路：按 (session_id, user_id) 分组聚合出时长与各类事件次数，再筛出时长够长、点击率低、无购买且滚动多的会话。
# 复杂度：时间 O(n log n)（分组与排序），空间 O(n)。
import pandas as pd  # 导入 pandas 库


def find_zombie_sessions(app_events: pd.DataFrame) -> pd.DataFrame:  # 找出满足条件的“僵尸会话”
    if not pd.api.types.is_datetime64_any_dtype(app_events["event_timestamp"]):  # 时间列不是 datetime 类型时先做类型转换
        app_events["event_timestamp"] = pd.to_datetime(app_events["event_timestamp"])  # 把时间戳解析为 datetime 类型

    grouped = app_events.groupby(["session_id", "user_id"])  # 按会话与用户分组

    result = grouped.agg(  # 对每组做聚合统计，一次算出四个指标
        session_duration_minutes=(  # 会话时长（分钟）
            "event_timestamp",  # 基于时间戳列计算
            lambda x: (x.max() - x.min()).total_seconds() // 60,  # 最晚时间减最早时间，再换算成整分钟
        ),
        scroll_count=("event_type", lambda x: (x == "scroll").sum()),  # 统计滚动事件次数
        click_count=("event_type", lambda x: (x == "click").sum()),  # 统计点击事件次数
        purchase_count=("event_type", lambda x: (x == "purchase").sum()),  # 统计购买事件次数
    ).reset_index()  # 把分组键还原成普通列

    result = result[  # 按“僵尸会话”的四个条件过滤
        (result["session_duration_minutes"] >= 30)  # 时长至少 30 分钟
        & (result["click_count"] / result["scroll_count"] < 0.2)  # 点击次数与滚动次数之比低于 0.2
        & (result["purchase_count"] == 0)  # 没有任何购买记录
        & (result["scroll_count"] >= 5)  # 滚动次数至少 5 次
    ]

    result = result.sort_values(  # 按滚动次数降序、会话号升序排序
        by=["scroll_count", "session_id"], ascending=[False, True]  # 指定排序键与各自的升降序
    ).reset_index(drop=True)  # 重置索引并丢弃旧索引

    return result[["session_id", "user_id", "session_duration_minutes", "scroll_count"]]  # 返回题目要求的四列结果
