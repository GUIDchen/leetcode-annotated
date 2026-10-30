# 3832. 查找具有持续行为模式的用户 / Find Users with Persistent Behavior Patterns（困难）
# 核心思路：先剔除同一天有多次动作的记录，再按 (用户, 动作) 分组用“日期减组内排名”得到连续区间标识，聚合出每个连续段的长度，最后筛出长度≥5 的段并按用户取最长的一条。
# 复杂度：多次分组与排序，时间 O(n log n)，空间 O(n)。
import pandas as pd  # 导入 pandas 用于表格处理


def find_behaviorally_stable_users(activity: pd.DataFrame) -> pd.DataFrame:  # 返回每个用户持续时间最长的连续 5 天以上同一动作的记录
    activity['action_date'] = pd.to_datetime(activity['action_date'])  # 把 action_date 转成日期类型，便于做日期减法运算

    # Filter users with only a single action per day
    df = activity.assign(  # 复制一份数据，并新增 cnt 列记录“同一用户同一天的动作条数”
        cnt=activity.groupby(['user_id', 'action_date'])['action'].transform('count')  # 按 (用户, 日期) 分组统计动作条数，transform 把结果广播回每一行
    )  # 得到附带 cnt 列的新表
    df = df[df['cnt'] == 1].sort_values(['user_id', 'action', 'action_date'])  # 只保留每天恰好一条动作的记录，并按用户、动作、日期排序

    # Identify consecutive intervals
    df['rn'] = df.groupby(['user_id', 'action'])['action_date'].rank(method='first')  # 组内按日期给出 1,2,3… 的排名，作为连续天数的计数器
    df['grp'] = df['action_date'] - pd.to_timedelta(df['rn'], unit='D')  # 日期减去排名：连续日期的差值相同，因此同一连续段得到同一个基准日期

    # Aggregate streaks
    streaks = (  # 按 (用户, 动作, 连续段标识) 做聚合，得到每条“连续行为链”
        df.groupby(['user_id', 'action', 'grp'])  # 分组键决定一条链的唯一身份
        .agg(  # 对每条链做聚合统计
            streak_length=('action_date', 'count'),  # 链的长度 = 该链的记录条数
            start_date=('action_date', 'min'),  # 链的起始日期
            end_date=('action_date', 'max'),  # 链的结束日期
        )  # 各列的聚合方式定义完毕
        .reset_index()  # 把分组键从索引还原为普通列
    )  # 得到每条连续行为链的统计表 streaks

    # Filter and get the longest streak for each user
    res = streaks[streaks['streak_length'] >= 5].sort_values(  # 保留长度 ≥ 5 的链，并准备排序
        ['streak_length', 'user_id'], ascending=[False, True]  # 先按链长降序、再按用户 id 升序排列，便于后续取每组第一条
    )  # 排序完成，最长的链排在最前面

    return res.groupby('user_id').head(1)[  # 按用户分组后取第一条，即该用户最长的持续行为链
        ['user_id', 'action', 'streak_length', 'start_date', 'end_date']  # 只输出题目要求的五列
    ]  # 只保留需要的五列作为最终输出
