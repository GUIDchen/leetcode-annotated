# 3611. 查找超预订员工 / Find Overbooked Employees
# 核心思路：把会议按 ISO 年 + 周聚合出每人每周的会议总时长，筛出时长 ≥ 20 小时的“高强度周”，再统计每人高强度周数并保留 ≥ 2 周者，按周数降序、姓名升序输出。
# 复杂度：时间 O(M log M)（分组聚合与排序主导），空间 O(M)；M 为会议记录数。
import pandas as pd  # 引入 pandas，用 DataFrame 承载员工与会议两类表


def find_overbooked_employees(  # 题解入口：employees 为员工信息表，meetings 为会议记录表
    employees: pd.DataFrame, meetings: pd.DataFrame  # 两个入参分别是员工表与会议表
) -> pd.DataFrame:  # 返回超预订员工的结果表
    meetings["meeting_date"] = pd.to_datetime(meetings["meeting_date"])  # 把字符串日期解析成日期类型，便于按周切分
    meetings["year"] = meetings["meeting_date"].dt.isocalendar().year  # 取出该日期所在的 ISO 年份（跨年周归属下一年）
    meetings["week"] = meetings["meeting_date"].dt.isocalendar().week  # 取出该日期所在的 ISO 周序号

    week_meeting_hours = (  # 开始统计每人每周的会议总时长
        meetings.groupby(["employee_id", "year", "week"], as_index=False)[  # 按员工、年、周分组，且把分组键保留为普通列
            "duration_hours"  # 取需要求和的时长列
        ]  # 列选择表达式结束
        .sum()  # 对每组时长求和
        .rename(columns={"duration_hours": "hours"})  # 把求和列重命名为 hours
    )  # 分组聚合表达式结束

    intensive_weeks = week_meeting_hours[week_meeting_hours["hours"] >= 20]  # 筛出单周会议总时长不少于 20 小时的“高强度周”

    intensive_count = (  # 开始统计每人拥有多少个高强度周
        intensive_weeks.groupby("employee_id")  # 按员工编号分组
        .size()  # 数出每组的行数，即高强度周个数
        .reset_index(name="meeting_heavy_weeks")  # 整理成普通表并命名为 meeting_heavy_weeks
    )  # 计数表达式结束

    result = intensive_count.merge(employees, on="employee_id")  # 把统计结果与员工表按 employee_id 关联

    result = result[result["meeting_heavy_weeks"] >= 2]  # 只保留高强度周不少于 2 周的员工

    result = result.sort_values(  # 按高强度周数降序、姓名升序排序
        ["meeting_heavy_weeks", "employee_name"], ascending=[False, True]  # 排序键与各自升降序设置
    )  # 排序表达式结束

    return result[  # 只输出题目要求的字段
        ["employee_id", "employee_name", "department", "meeting_heavy_weeks"]  # 待输出的四个字段
    ].reset_index(drop=True)  # 重置为 0 起始的连续整数索引并返回
