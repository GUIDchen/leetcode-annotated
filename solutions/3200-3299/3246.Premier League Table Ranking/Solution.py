# 题目：3246. 英超积分榜排名（Premier League Table Ranking）
# 思路：先算积分，再用 rank 按积分降序求名次，最后按积分降序、队名升序排序并只保留要求的列。
# 时间复杂度：O(m log m)，排序占主导；空间复杂度：O(m)，存放新增列与排序结果。
import pandas as pd  # # 用 pandas 做表格计算


def calculate_team_standings(team_stats: pd.DataFrame) -> pd.DataFrame:  # # 输入球队统计表，返回带积分和名次的排名表
    team_stats["points"] = team_stats["wins"] * 3 + team_stats["draws"]  # # 计算积分：胜场 3 分、平局 1 分，结果写回新列 points
    team_stats["position"] = team_stats["points"].rank(method="min", ascending=False)  # # 按积分降序排名；method="min" 让同分球队并列同名次，后续名次按 RANK 规则跳号
    team_stats = team_stats.sort_values(  # # 按积分降序、队名升序排序，保证同分时队名靠前的排前面
        by=["points", "team_name"], ascending=[False, True]  # # 排序键：points 从高到低，team_name 从低到高
    )  # # sort_values 调用结束
    return team_stats[["team_id", "team_name", "points", "position"]]  # # 只保留题目要求的四列并按该顺序返回
