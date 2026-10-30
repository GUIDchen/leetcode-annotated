# 题目：3384. 球队传球成功的优势得分（Team Dominance by Pass Success）
# 思路：把传球表分别按「传球人」「接球人」连接球队表得到双方队名；再由时间戳切上半场/下半场，同队记 +1、异队记 -1，最后按队名与半场求和。
# 时间复杂度：O(p log p)，p 为传球数（归并与排序主导）；空间复杂度：O(p)，保存连接后的中间表。
import pandas as pd  # 导入 pandas，用 DataFrame 做数据处理


def calculate_team_dominance(teams: pd.DataFrame, passes: pd.DataFrame) -> pd.DataFrame:  # teams：球员-球队表；passes：传球记录表；返回每队每半场的优势得分
    passes_with_teams = passes.merge(  # 第一步：把每次传球与「传球人」的球队连接起来
        teams, left_on="pass_from", right_on="player_id", suffixes=("", "_team_from")  # 以 pass_from = player_id 连接，suffixes 让左边列名不变、球队列加 _team_from
    ).merge(  # 链式调用，接着连接「接球人」的球队
        teams,  # 再次连接球队表
        left_on="pass_to",  # 这次用 pass_to 与 player_id 对齐
        right_on="player_id",  # 接球人的球员编号列
        suffixes=("_team_from", "_team_to"),  # 两边球队列分别加 _team_from 与 _team_to 后缀以区分
    )  # 连接表达式结束
    passes_with_teams["half_number"] = passes_with_teams["time_stamp"].apply(  # 第二步：由时间戳判断是上半场还是下半场
        lambda x: 1 if x <= "45:00" else 2  # 时间字符串按字典序比较，<= 45:00 记为上半场 1，否则为下半场 2
    )  # apply 表达式结束
    passes_with_teams["dominance"] = passes_with_teams.apply(  # 第三步：逐行判断这次传球是否成功
        lambda row: 1 if row["team_name_team_from"] == row["team_name_team_to"] else -1,  # 传球双方同队记 +1（成功），不同队记 -1（被对手断下）
        axis=1,  # axis=1 表示按行应用
    )  # apply 表达式结束
    result = (  # 第四步：按「传出方球队 + 半场」聚合求和
        passes_with_teams.groupby(["team_name_team_from", "half_number"])["dominance"]  # 分组键是传出方队名与半场编号，只取 dominance 列
        .sum()  # 对 dominance 求和
        .reset_index()  # 把分组索引还原成普通列
    )  # 聚合表达式结束
    result.columns = ["team_name", "half_number", "dominance"]  # 重命名列，使输出符合题目要求的列名
    result = result.sort_values(by=["team_name", "half_number"])  # 按队名、半场排序，保证结果稳定
    return result  # 返回最终结果表
