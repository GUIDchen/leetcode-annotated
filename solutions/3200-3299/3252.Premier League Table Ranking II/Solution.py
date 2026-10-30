# 题目：3252. 英超积分榜排名 II（Premier League Table Ranking II）
# 思路：用 pandas 先算积分（胜 3 平 1），再用 rank(method="min") 排名次，随后按名次阈值用 np.where 划分 Tier 1/2/3，最后排序并选出四列。
# 时间复杂度：O(n log n)，主要由排序与排名决定；空间复杂度：O(n)，用于存放积分、名次、档位等新增列。
import pandas as pd  # 导入 pandas，题面要求用 DataFrame 完成统计


def calculate_team_tiers(team_stats: pd.DataFrame) -> pd.DataFrame:  # 入参 team_stats：球队统计表；返回题目要求的四列分级表
    team_stats["points"] = team_stats["wins"] * 3 + team_stats["draws"]  # 胜一场得 3 分、平一场得 1 分，算出每队积分
    team_stats["position"] = (  # 开始计算名次：积分高者名次靠前
        team_stats["points"].rank(method="min", ascending=False).astype(int)  # rank(method="min") 让并列队伍取最小名次，再转成整数
    )
    total_teams = len(team_stats)  # 球队总数，用来把积分榜均分成三个档位
    team_stats["tier"] = np.where(  # 用 np.where 按名次阈值划分档位
        team_stats["position"] <= np.ceil(total_teams / 3.0),  # 前 1/3（向上取整）的队伍属于 Tier 1
        "Tier 1",  # 满足条件时填入的档位名
        np.where(  # 否则继续判断是否落在前 2/3 之内
            team_stats["position"] <= np.ceil(2 * total_teams / 3.0), "Tier 2", "Tier 3"  # 前 2/3 为 Tier 2，其余队伍为 Tier 3
        ),
    )
    team_stats = team_stats.sort_values(  # 按积分降序、队名升序排列，得到最终榜单顺序
        by=["points", "team_name"], ascending=[False, True]  # 两个排序键分别对应降序（False）与升序（True）
    )
    return team_stats[["team_name", "points", "position", "tier"]]  # 只保留题目要求的四列并返回
