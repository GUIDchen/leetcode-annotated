# 题目：3322. 英超积分榜排名 III（Premier League Table Ranking III）
# 思路：先用 pandas 算出积分（胜场×3 + 平局）与净胜球，再按 赛季升序、积分降序、净胜球降序、队名升序 排序，
# 最后用 groupby + cumcount 在每个赛季内生成从 1 开始的名次。时间复杂度：O(n log n)（排序主导）；空间复杂度：O(n)。
import pandas as pd  # 引入 pandas，用于表格计算


def process_team_standings(season_stats: pd.DataFrame) -> pd.DataFrame:  # season_stats：各队的赛季统计表；返回补上积分与名次的积分榜
    season_stats["points"] = season_stats["wins"] * 3 + season_stats["draws"]  # 计算积分：胜场 3 分 + 平局 1 分
    season_stats["goal_difference"] = (  # 计算净胜球：进球数 - 失球数（表达式跨行书写）
        season_stats["goals_for"] - season_stats["goals_against"]  # 净胜球 = goals_for - goals_against
    )

    season_stats = season_stats.sort_values(  # 按题目要求的优先级对整表排序
        ["season_id", "points", "goal_difference", "team_name"],  # 排序键依次为：赛季、积分、净胜球、队名
        ascending=[True, False, False, True],  # 赛季升序；积分与净胜球降序；队名升序作为最后的平局决胜
    )

    season_stats["position"] = season_stats.groupby("season_id").cumcount() + 1  # 每个赛季内按当前顺序编号：cumcount 从 0 开始，+1 即名次

    return season_stats[  # 只保留题目要求的列并返回
        ["season_id", "team_id", "team_name", "points", "goal_difference", "position"]  # 输出列清单：赛季、队伍、积分、净胜球、名次
    ]
