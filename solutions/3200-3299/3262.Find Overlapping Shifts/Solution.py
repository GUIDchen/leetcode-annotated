# 题目：3262. 查找重叠的班次（Find Overlapping Shifts）🔒
# 思路：把班次表按 employee_id 自连接，得到同一员工的两两班次对；用「t1 开始早于 t2 开始、且 t1 结束晚于 t2 开始」筛出真正重叠的班次对，再按员工分组计数，去掉计数为 0 的组并按员工升序输出。
# 时间复杂度：O(m) 量级，其中 m 为自连接后的班次对数；空间复杂度：O(m)，需保存自连接的中间结果。
import pandas as pd  # 引入 pandas，LeetCode 数据库题以 DataFrame 作为输入与输出


def find_overlapping_shifts(employee_shifts: pd.DataFrame) -> pd.DataFrame:  # employee_shifts 含 employee_id、start_time、end_time 三列；返回每个员工的重叠班次对数
    merged_shifts = employee_shifts.merge(  # 让班次表与自己按 employee_id 做自连接，用后缀区分「前一个班次 t1」与「后一个班次 t2」
        employee_shifts, on="employee_id", suffixes=("_t1", "_t2")  # 连接键为同一员工，左右两表列名分别加上 _t1 / _t2 后缀
    )  # 自连接结果作为待筛选的候选班次对
    overlapping_shifts = merged_shifts[  # 重叠判定开始：t1 的起始时间早于 t2 的起始时间
        (merged_shifts["start_time_t1"] < merged_shifts["start_time_t2"])  # 且 t1 的结束时间晚于 t2 的起始时间，说明两个班次的时间有交集
        & (merged_shifts["end_time_t1"] > merged_shifts["start_time_t2"])  # 两个条件同时成立才算重叠
    ]  # 只保留真正存在重叠的行
    result = (  # 按 employee_id 分组进行聚合
        overlapping_shifts.groupby("employee_id")  # 统计每个员工的重叠班次对数
        .size()  # 把计数结果落成名为 overlapping_shifts 的列
        .reset_index(name="overlapping_shifts")  # 分组结果重新变回普通 DataFrame
    )  # 聚合表达式结束
    result = result[result["overlapping_shifts"] > 0]  # 再过滤一次，只保留计数大于 0 的员工
    result = result.sort_values("employee_id").reset_index(drop=True)  # 按 employee_id 升序排序，并重建从 0 开始的连续索引
    return result  # 返回最终的重叠班次统计表
