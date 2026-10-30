# 3482. 分析组织层级（Analyze Organization Hierarchy）
# 核心思路：先找出 manager_id 为空的 CEO 并递归填出每位员工的层级，再按层级从高到低自底向上把团队人数与预算汇总给上级，最后按题目要求排序取列。
# 复杂度：时间 O(n log n)（瓶颈在排序），空间 O(n)
import pandas as pd  # 引入 pandas，用于表格化数据处理


def analyze_organization_hierarchy(employees: pd.DataFrame) -> pd.DataFrame:  # 返回按层级、预算、姓名排序后的员工层级信息表
    # Copy the input DataFrame to avoid modifying the original  # 复制输入表，避免修改原始数据
    employees = employees.copy()  # 拷贝一份数据，后续只改动副本
    employees["level"] = None  # 新增 level 列，初始为空，等待填入层级

    # Identify the CEO (level 1)  # 找出 manager_id 为空的人，即 CEO
    ceo_id = employees.loc[employees["manager_id"].isna(), "employee_id"].values[0]  # 取出 CEO 的 employee_id
    employees.loc[employees["employee_id"] == ceo_id, "level"] = 1  # CEO 的层级记为 1

    # Recursively compute employee levels  # 递归计算每位员工的层级
    def compute_levels(emp_df, level):  # 递归函数：emp_df 为员工表，level 为当前处理的层级
        next_level_ids = emp_df[emp_df["level"] == level]["employee_id"].tolist()  # 取出当前层级的所有员工编号
        if not next_level_ids:  # 若当前层级没有员工，说明已经递归到最深层
            return  # 直接结束递归
        emp_df.loc[emp_df["manager_id"].isin(next_level_ids), "level"] = level + 1  # 把这些员工的下属层级设为 level + 1
        compute_levels(emp_df, level + 1)  # 继续处理下一层级

    compute_levels(employees, 1)  # 从 CEO 所在的第 1 层开始计算

    # Initialize team size and budget dictionaries  # 初始化团队人数与团队预算字典
    team_size = {eid: 0 for eid in employees["employee_id"]}  # 每位员工的团队人数初始为 0（只统计下属）
    budget = {  # 每位员工的团队预算从自己的薪水开始累计
        eid: salary  # 键为员工编号
        for eid, salary in zip(employees["employee_id"], employees["salary"])  # 值为该员工的薪水
    }  # 结束字典推导式

    # Compute team size and budget for each employee  # 自底向上累加团队人数与预算
    for eid in employees.sort_values("level", ascending=False)["employee_id"]:  # 按层级从高到低遍历，保证先处理完下属
        manager_id = employees.loc[  # 查询该员工的直属上级
            employees["employee_id"] == eid, "manager_id"  # 条件为员工编号等于 eid
        ].values[0]  # 取出 manager_id
        if pd.notna(manager_id):  # 存在上级时才向上汇总
            team_size[manager_id] += team_size[eid] + 1  # 上级的团队人数加上该员工本人及其下属
            budget[manager_id] += budget[eid]  # 上级的团队预算加上该员工团队的总预算

    # Map computed team size and budget to employees DataFrame  # 把算好的团队人数与预算写回员工表
    employees["team_size"] = employees["employee_id"].map(team_size)  # 写入每位员工的团队人数
    employees["budget"] = employees["employee_id"].map(budget)  # 写入每位员工的团队预算

    # Sort the final result by level (ascending), budget (descending), and employee name (ascending)  # 按层级升序、预算降序、姓名升序排序最终结果
    employees = employees.sort_values(  # 开始排序
        by=["level", "budget", "employee_name"], ascending=[True, False, True]  # 指定排序字段与各自的升降序
    )  # 结束排序调用

    return employees[["employee_id", "employee_name", "level", "team_size", "budget"]]  # 只返回题目要求的五个字段
