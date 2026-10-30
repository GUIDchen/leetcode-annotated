# 3764. 最常见的课程组合 / Most Common Course Pairs
# 核心思路：先筛出完成课程数不少于 5 且平均评分不低于 4 的学员，再按完成时间取同一用户的相邻课程对，分组计数后排序。
# 复杂度：时间 O(n log n)，空间 O(n)。
import pandas as pd  # 导入 pandas


def topLearnerCourseTransitions(course_completions: pd.DataFrame) -> pd.DataFrame:  # 统计优秀学员之间最常见的课程前后衔接组合
    grp = course_completions.groupby("user_id")  # 按用户分组
    top_students = grp.filter(  # 过滤出满足条件的用户的全部记录
        lambda df: df.shape[0] >= 5 and df["course_rating"].mean() >= 4  # 条件：完成课程数不少于 5 且课程平均评分不低于 4
    )["user_id"].unique()  # 取出这些优秀学员的 user_id 并去重

    df = course_completions[course_completions["user_id"].isin(top_students)].copy()  # 只保留优秀学员的记录，并复制一份以免改动原表
    df = df.sort_values(["user_id", "completion_date"])  # 按用户与完成时间升序排序，保证课程对的先后顺序
    df["second_course"] = df.groupby("user_id")["course_name"].shift(-1)  # 用 shift(-1) 取同一用户的下一条课程名
    df["first_course"] = df["course_name"]  # 当前课程名作为课程对中的第一门课

    pairs = df[df["second_course"].notna()][["first_course", "second_course"]]  # 去掉没有后继课程的记录，只保留两列课程名

    result = (  # 组装最终的统计结果
        pairs.groupby(["first_course", "second_course"])  # 按课程对分组
        .size()  # 统计每个课程对出现的次数
        .reset_index(name="transition_count")  # 把计数列命名为 transition_count
        .sort_values(  # 按出现次数与课程名排序
            ["transition_count", "first_course", "second_course"],  # 排序键依次为：出现次数、第一门课、第二门课
            ascending=[False, True, True],  # 出现次数降序，两门课程名升序
            key=lambda col: col.str.lower() if col.dtype == "object" else col,  # 字符串列忽略大小写比较，其他列保持原值
        )
        .reset_index(drop=True)  # 丢弃原索引，重排为 0..m-1
    )

    return result  # 返回统计结果
