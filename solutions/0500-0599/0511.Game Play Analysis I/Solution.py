# 题目：511. 游戏玩法分析 I（Game Play Analysis I）
# 思路：按 player_id 分组，对每组的 event_date 取最小值得到首次登录日期，再用 reset_index 把分组键还原成普通列。
# 时间复杂度：O(n)，每条记录只参与一次分组聚合；空间复杂度：O(k)，k 为玩家数，即结果表的行数。
import pandas as pd  # 导入 pandas，本题依赖 DataFrame 的分组聚合能力


def game_analysis(activity: pd.DataFrame) -> pd.DataFrame:  # 题解函数：入参是活动表，返回值是每位玩家首次登录日期的表
    return (  # 用括号把链式调用拆成多行，先算出结果再整体返回
        activity.groupby("player_id")  # 按 player_id 分组，同一玩家的多条记录被聚到一起
        .agg(first_login=("event_date", "min"))  # 对每组的 event_date 取最小值，并把结果列命名为 first_login
        .reset_index()  # 把分组键 player_id 从索引还原成普通列，得到题目要求的表结构
    )  # 结束这个多行表达式
