# 题目：3060. 时间范围内的用户活动（User Activities within Time Bounds）
# 思路：先按用户与会话开始时间排序，用 groupby 加 shift 取出同用户同类型会话的上一次结束时间，筛选本次开始距上次结束不超过 12 小时的记录，最后去重返回 user_id。
# 时间复杂度：O(n log n)，主要来自排序与分组；空间复杂度：O(n)，新增的上一次会话结束时间列。
import pandas as pd  # 引入 pandas，用于排序、分组位移与时间比较


def user_activities(sessions: pd.DataFrame) -> pd.DataFrame:  # sessions：用户会话表，包含 session_start 与 session_end
    sessions = sessions.sort_values(by=["user_id", "session_start"])  # 先按用户、再按会话开始时间排序，保证同一用户的活动按时间先后排列
    sessions["prev_session_end"] = sessions.groupby(["user_id", "session_type"])[  # 为每条会话补上同用户同类型的上一条会话结束时间
        "session_end"  # 取出参与位移的会话结束时间列
    ].shift(1)  # shift(1) 向下平移一行，即取到上一行（上一次会话）的结束时间
    sessions_filtered = sessions[  # 筛选出满足 12 小时时间窗口的会话
        sessions["session_start"] - sessions["prev_session_end"]  # 本次开始时间与上一次结束时间之差
        <= pd.Timedelta(hours=12)  # 只有差值不超过 12 小时才符合题目的时间范围
    ]  # 布尔索引筛选结束
    return pd.DataFrame({"user_id": sessions_filtered["user_id"].unique()})  # 同一用户可能有多条记录，用 unique() 去重后按 user_id 列返回
