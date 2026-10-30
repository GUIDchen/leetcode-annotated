# 3808. Find Emotionally Consistent Users | 寻找情绪一致的用户
# 核心思路：先按 (user_id, reaction) 统计条数，再按用户求最大条数 mx_cnt 与总条数 total_cnt，保留 mx_cnt/total_cnt >= 0.6 且 total_cnt >= 5 的用户，最后与明细表按 (user_id, 最大条数) 回连，得到每个用户的主导情绪。
# 复杂度：时间 O(n + u * r)（一次分组聚合 + 一次连接，n 为反馈条数）；空间 O(n + u * r)。
import pandas as pd  # 导入 pandas，用于表格分组与连接
from decimal import Decimal, ROUND_HALF_UP  # 导入 Decimal 与四舍五入模式，用于精确控制两位小数的舍入


def find_emotionally_consistent_users(reactions: pd.DataFrame) -> pd.DataFrame:  # 返回所有“主导情绪占比 >= 0.6 且反馈总数 >= 5”的用户及其主导情绪
    t = reactions.groupby(["user_id", "reaction"]).size().reset_index(name="cnt")  # 统计每个用户每种情绪的条数，得到 (user_id, reaction, cnt) 明细

    s = (  # 按 user_id 汇总每个用户的最大条数与总条数（多行表达式开始）
        t.groupby("user_id")  # 按用户分组
        .agg(mx_cnt=("cnt", "max"), total_cnt=("cnt", "sum"))  # 同时求最大次数 mx_cnt 与全部次数之和 total_cnt
        .reset_index()  # 把分组键还原成普通列
    )  # 用户汇总表构造结束

    s["reaction_ratio"] = (  # 计算主导情绪占比 = mx_cnt / total_cnt（多行表达式开始）
        s["mx_cnt"]  # 分子：出现次数最多的那种情绪的条数
        .div(s["total_cnt"])  # 除以该用户的反馈总条数（浮点除法）
        .apply(  # 对每个比例做定点舍入
            lambda x: float(  # 把舍入后的 Decimal 转回 float
                Decimal(str(x)).quantize(Decimal("0.00"), rounding=ROUND_HALF_UP)  # 量化到两位小数 0.00，并采用 ROUND_HALF_UP（真正的四舍五入）
            )  # float 转换结束
        )  # apply 结束
    )  # 占比列计算结束

    s = s[(5 * s["mx_cnt"] >= 3 * s["total_cnt"]) & (s["total_cnt"] >= 5)]  # 筛选：5*mx_cnt >= 3*total_cnt 即占比 >= 0.6，且总条数 >= 5；用整数乘法避免浮点误差

    merged = pd.merge(  # 把用户汇总表与明细表连接，定位每个用户的主导情绪
        s[["user_id", "mx_cnt", "reaction_ratio"]],  # 左表：用户、最大条数、占比
        t,  # 右表：用户-情绪-条数明细
        left_on=["user_id", "mx_cnt"],  # 左表连接键：用户与该用户的最大条数
        right_on=["user_id", "cnt"],  # 右表连接键：用户与该情绪的条数（两者相等即为主导情绪）
    )  # 连接完成，得到 (user_id, reaction, cnt=mx_cnt, reaction_ratio)

    result = (  # 整理最终结果表（多行表达式开始）
        merged[["user_id", "reaction", "reaction_ratio"]]  # 只保留用户、情绪、占比三列
        .rename(columns={"reaction": "dominant_reaction"})  # 把 reaction 列重命名为主导情绪
        .sort_values(by=["reaction_ratio", "user_id"], ascending=[False, True])  # 按占比降序、user_id 升序排序
        .reset_index(drop=True)  # 丢弃旧索引，重建 0..n-1 的连续索引
    )  # 结果表构造结束

    return result  # 返回结果表
