# 题目：3057. 员工项目分配（Employees Project Allocation）
# 思路：先把项目表与员工表按 employee_id 连接，再求各团队的平均工作量并回填成新列，筛出工作量高于团队平均值的记录。
# 时间复杂度：O(n log n)，主要来自分组与排序；空间复杂度：O(n)，连接表与平均值表都随规模线性增长。
import pandas as pd  # 引入 pandas，用于连接、分组与排序


def employees_with_above_avg_workload(  # project：项目分配表；employees：员工表（含姓名与团队）
    project: pd.DataFrame, employees: pd.DataFrame  # 两个入参的续行
) -> pd.DataFrame:  # 返回工作量高于所属团队平均值的员工记录
    merged_df = pd.merge(project, employees, on="employee_id")  # 用 employee_id 连接，给每条项目分配补上员工姓名与团队
    avg_workload_per_team = merged_df.groupby("team")["workload"].mean().reset_index()  # 求出每个团队的平均工作量
    merged_df = pd.merge(  # 把团队平均工作量作为新列并回明细表
        merged_df, avg_workload_per_team, on="team", suffixes=("", "_avg")  # 两表都有 workload 列，用 suffixes 区分：明细保持原名，平均值加 _avg 后缀
    )  # 连接语句结束
    ans = merged_df[merged_df["workload"] > merged_df["workload_avg"]]  # 只保留个人工作量严格大于团队平均值的行
    ans = ans[["employee_id", "project_id", "name", "workload"]]  # 只保留题目需要的四列
    ans = ans.rename(columns={"name": "employee_name", "workload": "project_workload"})  # 按题目要求重命名列：name 改为 employee_name，workload 改为 project_workload
    return ans.sort_values(by=["employee_id", "project_id"])  # 按 employee_id、project_id 升序排序后返回
