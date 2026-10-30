# 题目：184. 部门工资最高的员工（Department Highest Salary）
# 思路：员工表与部门表按部门 id 合并，用 groupby + transform 求出每个部门的最高工资，再筛出工资等于本部门最高值的员工。
# 时间复杂度：O(n log n)，merge 与分组各一遍；空间复杂度：O(n)，合并后的宽表与最高工资列。
import pandas as pd  # 导入 pandas，判题环境已提供


def department_highest_salary(  # 参数分两行书写，保持仓库的格式化风格
    employee: pd.DataFrame, department: pd.DataFrame  # employee：员工表；department：部门表
) -> pd.DataFrame:  # 返回部门名、员工名、工资三列
    # 原文注释：按 departmentId 与部门表的 id 合并两张表
    merged = employee.merge(department, left_on='departmentId', right_on='id')  # 同名列自动加 _x/_y 后缀，部门名落到 name_y

    # 原文注释：求每个部门的最高工资
    max_salaries = merged.groupby('departmentId')['salary'].transform('max')  # transform 把组内最大值广播回每一行，长度与 merged 一致，便于逐行比较

    # 原文注释：筛选出各部门工资最高的员工
    top_earners = merged[merged['salary'] == max_salaries]  # 用布尔掩码保留工资等于本部门最高值的行，允许并列

    # 原文注释：取出需要输出的列并重命名
    result = top_earners[['name_y', 'name_x', 'salary']].copy()  # name_y 是部门名、name_x 是员工名；copy 避免后续改名触发警告
    result.columns = ['Department', 'Employee', 'Salary']  # 按题目要求一次性设定三列列名

    return result  # 返回结果表
