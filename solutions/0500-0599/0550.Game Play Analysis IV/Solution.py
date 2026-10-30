# 题目：550. 游戏玩法分析 IV（Game Play Analysis IV）
# 思路：按 player_id 分组求出每位玩家的首次登录日期并广播成新列，再筛出「登录日期 = 首次登录日期 + 1 天」的行，用其行数除以玩家总数得到占比。
# 时间复杂度：O(n log n)，主要开销是分组求最小值；空间复杂度：O(n)，新增一列并保存筛选结果。
import pandas as pd  # 引入 pandas，题目要求用 DataFrame 编程


def gameplay_analysis(activity: pd.DataFrame) -> pd.DataFrame:  # activity 是活动表，返回「首次登录次日又登录」的玩家占全部玩家的比例
    activity["first"] = activity.groupby("player_id").event_date.transform(min)  # 按玩家分组求最早登录日期，transform(min) 把结果广播成与每行等长的列
    activity_2nd_day = activity[  # 开始筛选：条件为「登录日期恰好等于首次登录日期 + 1 天」
        activity["first"] + pd.DateOffset(1) == activity["event_date"]  # DateOffset(1) 表示加一天，会自动处理月末、年末等日期边界
    ]  # 布尔索引结束

    return pd.DataFrame(  # 按题目要求返回只含一列 fraction 的 DataFrame
        {"fraction": [round(len(activity_2nd_day) / activity.player_id.nunique(), 2)]}  # 次日登录的记录行数 / 玩家总数，round 保留两位小数
    )  # DataFrame 构造函数结束
