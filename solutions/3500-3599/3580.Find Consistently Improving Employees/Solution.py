# 题目：3580. 寻找持续进步的员工 / Find Consistently Improving Employees（中等）
# 核心思路：先按员工编号升序、评价日期降序排序，为每位员工算出评价名次 rn 与上一条评价的分数，得到相邻两次评价的进步量 delta；只取每位员工最近两次评价（rn 为 2、3）聚合出进步总分、条数与最小进步量，筛出两次评价都在进步（count 为 2 且最小进步量为正）的员工，再与员工表连接取姓名，按进步总分降序、姓名升序排列。
# 复杂度：时间复杂度 O(m log m + n log n)，空间复杂度 O(m + n)，其中 m 为评价记录数、n 为员工数。
import pandas as pd  # 导入 pandas 库


def find_consistently_improving_employees(  # 定义主函数，返回持续进步员工的数据框
    employees: pd.DataFrame, performance_reviews: pd.DataFrame  # 参数：员工表与绩效评价表
) -> pd.DataFrame:  # 返回值为 DataFrame
    performance_reviews = performance_reviews.sort_values(  # 对评价记录排序
        ["employee_id", "review_date"], ascending=[True, False]  # 按员工编号升序、评价日期降序（最近的在前）
    )  # 排序结果覆盖原变量
    performance_reviews["rn"] = (  # 计算每位员工内部的评价名次
        performance_reviews.groupby("employee_id").cumcount() + 1  # 分组累计计数从 0 开始，加 1 得到名次
    )  # 名次 1 表示最近一次评价
    performance_reviews["lag_rating"] = performance_reviews.groupby("employee_id")[  # 取同一员工上一条（更早一次）评价的分数
        "rating"  # 对分数列做平移
    ].shift(1)  # shift(1) 向下平移一行，因为已按日期降序排列
    performance_reviews["delta"] = (  # 计算相比上一次评价的进步量
        performance_reviews["lag_rating"] - performance_reviews["rating"]  # 上一条分数减当前分数，正数表示进步
    )  # 每条评价相对上一次的进步量
    recent = performance_reviews[  # 只保留每位员工最近两次评价（rn 为 2、3）
        (performance_reviews["rn"] > 1) & (performance_reviews["rn"] <= 3)  # 名次落在 2 到 3 之间
    ]  # recent 中只保留每位员工最近的两次评价
    improvement = (  # 按员工聚合最近两次评价的进步情况
        recent.groupby("employee_id")  # 按员工编号分组
        .agg(  # 聚合多个统计量
            improvement_score=("delta", "sum"),  # 进步量求和，得到进步总分
            count=("delta", "count"),  # 进步量记录条数
            min_delta=("delta", "min"),  # 最小的一次进步量
        )  # 聚合结束
        .reset_index()  # 把 employee_id 从索引还原为普通列
    )  # improvement 中每行是一位员工的进步统计
    improvement = improvement[  # 筛选持续进步的员工
        (improvement["count"] == 2) & (improvement["min_delta"] > 0)  # 必须有两次评价且每次都在进步
    ]  # 只保留两次评价都进步的员工
    result = improvement.merge(employees[["employee_id", "name"]], on="employee_id")  # 与员工表连接取出姓名
    result = result.sort_values(  # 对结果排序
        by=["improvement_score", "name"], ascending=[False, True]  # 进步总分降序、姓名升序
    )  # 得到排好序的最终结果
    return result[["employee_id", "name", "improvement_score"]]  # 返回指定的三列
