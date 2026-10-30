# 题目：185. 部门工资前三高的所有员工（Department Top Three Salaries）
# 思路：先按（工资, 部门）去重后取每部门前 3 个不同工资，取最小值作为该部门入围线；再按部门补部门名，筛出工资不低于入围线的员工。
# 时间复杂度：O(n log n)，分组取前 3 需要排序；空间复杂度：O(n)，新增两列辅助数据。
import pandas as pd  # 导入 pandas，判题环境已提供


def top_three_salaries(  # 参数分两行书写，保持仓库的格式化风格
    employee: pd.DataFrame, department: pd.DataFrame  # employee：员工表；department：部门表
) -> pd.DataFrame:  # 返回部门名、员工名、工资三列
    salary_cutoff = (  # 每个部门的入围工资线，结果是按 departmentId 索引的 Series
        employee.drop_duplicates(["salary", "departmentId"])  # 先对工资与部门去重，避免同一工资出现多次占掉名次
        .groupby("departmentId")["salary"]  # 按部门分组，只关心工资列
        .nlargest(3)  # 每组取最大的 3 个不同工资；不足 3 个时有多少取多少
        .groupby("departmentId")  # 再按部门分组
        .min()  # 取这三档中的最小值，即该部门前三高的门槛
    )  # 括号结束，得到每个部门的门槛工资
    employee["Department"] = department.set_index("id")["name"][  # 用部门表的 id→name 映射，给每个员工补上部门名
        employee["departmentId"]  # 按员工的 departmentId 逐个取对应部门名
    ].values  # 取 numpy 数组按位置对齐赋值，避免索引错位
    employee["cutoff"] = salary_cutoff[employee["departmentId"]].values  # 把部门门槛工资按 departmentId 对齐到每个员工
    return employee[employee["salary"] >= employee["cutoff"]].rename(  # 筛出工资不低于本部门门槛的员工
        columns={"name": "Employee", "salary": "Salary"}  # 按题目要求重命名两列
    )[["Department", "Employee", "Salary"]]  # 只取这三列并固定输出顺序
