# 3617. Find Students with Study Spiral Pattern / 查找具有螺旋学习模式的学生
# 核心思路：按学生分组并按日期排序，先用相邻日期差过滤断档，再检查科目序列是否为同一周期至少两遍的完整重复，最后汇总时长并按周期长度、总时长降序输出。
# 复杂度：时间复杂度 O(S log S)，空间复杂度 O(S)，S 为会话记录总数（主要开销在分组内排序）。
import pandas as pd  # 引入 pandas 用于表连接、排序与分组


def find_study_spiral_pattern(  # 主函数：找出符合螺旋学习模式的学生并汇总其学习时长
    students: pd.DataFrame, study_sessions: pd.DataFrame  # 形参续行：学生表与学习会话表
) -> pd.DataFrame:  # 返回结果 DataFrame
    study_sessions = study_sessions.copy()  # 复制一份会话数据，避免修改调用方的入参
    study_sessions["session_date"] = pd.to_datetime(study_sessions["session_date"])  # 把日期列统一转成 datetime，便于求相邻间隔

    result = []  # 用列表收集每个符合条件学生的结论

    for student_id, group in study_sessions.groupby("student_id"):  # 按学生编号分组，逐个学生检查
        group = group.sort_values(["session_date", "session_id"]).reset_index(drop=True)  # 组内先按日期、再按会话编号排序，并重置索引
        # One gap longer than two days breaks the whole record. A later fragment
        # is not a separate spiral.
        if len(group) >= 2:  # 至少两次会话才谈得上间隔
            gaps = group["session_date"].diff().dt.days.iloc[1:]  # 计算相邻会话之间的天数差
            if (gaps > 2).any():  # 只要存在超过两天的断档
                continue  # 跳过该学生，不进入模式检查
        _check_pattern(student_id, [row for _, row in group.iterrows()], result)  # 校验该学生的会话序列是否构成完整螺旋

    df_result = pd.DataFrame(  # 把中间结果整理成 DataFrame
        result, columns=["student_id", "cycle_length", "total_study_hours"]  # 指定三列：学生编号、周期长度、总学习时长
    )  # 结束 DataFrame 构造

    if df_result.empty:  # 若没有任何学生满足条件
        return pd.DataFrame(  # 返回带完整列名的空表，保证下游列结构一致
            columns=[  # 依次列出空表的列名
                "student_id",  # 学生编号
                "student_name",  # 学生姓名
                "major",  # 专业
                "cycle_length",  # 周期长度
                "total_study_hours",  # 总学习时长
            ]  # 列名列表结束
        )  # 结束空表构造

    df_result = df_result.merge(students, on="student_id")  # 与学生表按学生编号做内连接，补上姓名与专业
    df_result = df_result[  # 按题目要求的列顺序重排
        ["student_id", "student_name", "major", "cycle_length", "total_study_hours"]  # 列出最终需要的五列
    ]  # 结束列裁剪

    return df_result.sort_values(  # 先按周期长度降序、再按总学习时长降序排序
        by=["cycle_length", "total_study_hours"], ascending=[False, False]  # 指定排序键与降序标志
    ).reset_index(drop=True)  # 重置索引后返回


def _check_pattern(student_id, sessions, result):  # 辅助函数：判断单个学生的会话序列是否为若干遍完整重复的螺旋
    subjects = [row["subject"] for row in sessions]  # 按时间顺序取出每节课的科目
    hours = sum(row["hours_studied"] for row in sessions)  # 累加该学生的总学习时长

    n = len(subjects)  # 会话次数
    # Cycle length is the number of distinct subjects, not an arbitrary divisor.
    cycle_len = len(set(subjects))  # 周期长度等于不同科目的数量
    if cycle_len < 3 or n < cycle_len * 2 or n % cycle_len != 0:  # 周期太短、重复次数不足或不能整除，都不构成螺旋
        return  # 直接返回，不记录该学生

    first_cycle = subjects[:cycle_len]  # 取第一个周期的科目序列
    if subjects != first_cycle * (n // cycle_len):  # 整段序列必须正好是若干个第一周期的重复
        return  # 不满足则返回

    result.append(  # 记录该学生的结论
        {  # 结果字典开始
            "student_id": student_id,  # 学生编号
            "cycle_length": cycle_len,  # 周期长度
            "total_study_hours": hours,  # 总学习时长
        }  # 字典结束
    )  # 结束 append 调用
