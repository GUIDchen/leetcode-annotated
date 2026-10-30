# 题目：570. 至少有5名直接下属的经理（Managers with at Least 5 Direct Reports）
# 核心思路：先按 managerId 分组统计直接下属人数，筛出人数 >= 5 的经理 id，再与员工表按 id 内连接取出姓名。
# 时间复杂度：O(n)，分组与连接各需线性扫描；空间复杂度：O(n)，需保存分组结果与中间表。
import pandas as pd  # 引入 pandas，LeetCode 的 Python 数据题用 DataFrame 表示表数据


def find_managers(employee: pd.DataFrame) -> pd.DataFrame:  # employee 为 Employee 表，含 id/name/managerId/reports
    # Group the employees by managerId and count the number of direct reports
    manager_report_count = (  # 统计每个经理的直接下属人数，结果存成新的两列表
        employee.groupby("managerId").size().reset_index(name="directReports")  # 按 managerId 分组求行数（即下属数），并把计数列命名为 directReports
    )  # 语句收尾：得到 managerId + directReports 两列

    # Filter managers with at least five direct reports
    result = manager_report_count[manager_report_count["directReports"] >= 5]  # 布尔索引只留下下属人数 >= 5 的经理记录

    # Merge with the Employee table to get the names of these managers
    result = result.merge(  # 把筛选出的经理 id 与员工表连接，从而拿到这些经理的姓名
        employee[["id", "name"]], left_on="managerId", right_on="id", how="inner"  # 左表用 managerId 去匹配右表的 id，内连接只保留匹配成功的行
    )  # 语句收尾：连接后结果表同时包含 managerId 与 name 等列

    # Select only the 'name' column and drop the 'id' and 'directReports' columns
    result = result[["name"]]  # 题目只要求输出 name 一列，因此丢弃其余列

    return result  # 返回只含经理姓名的结果表
