# 3586. 寻找 COVID 康复患者（Find COVID Recovery Patients）
# 核心思路：先取每位患者首次阳性日期，再取其后的首次阴性日期，相减得到康复天数，最后关联病人表并按康复天数、姓名排序。
# 复杂度：时间复杂度 O((n + m) log(n + m))，空间复杂度 O(n + m)，其中 n 为检测记录数、m 为患者数。
import pandas as pd  # 导入 pandas，题目要求返回 DataFrame


def find_covid_recovery_patients(  # 主函数：求每位患者的康复时间
    patients: pd.DataFrame, covid_tests: pd.DataFrame  # 参数：病人表与检测记录表
) -> pd.DataFrame:  # 返回包含康复时间的病人表
    covid_tests["test_date"] = pd.to_datetime(covid_tests["test_date"])  # 把检测日期转成 datetime，便于比较与相减

    pos = (  # 统计每位患者的首次阳性日期
        covid_tests[covid_tests["result"] == "Positive"]  # 筛出所有阳性检测记录
        .groupby("patient_id", as_index=False)["test_date"]  # 按患者分组并保留 test_date 列
        .min()  # 取组内最早的检测日期
    )  # 结束首次阳性日期计算
    pos.rename(columns={"test_date": "first_positive_date"}, inplace=True)  # 把结果列重命名为首次阳性日期

    neg = covid_tests.merge(pos, on="patient_id")  # 把首次阳性日期合并回检测表
    neg = neg[  # 筛选出阳性之后的阴性检测记录
        (neg["result"] == "Negative") & (neg["test_date"] > neg["first_positive_date"])  # 结果阴性且日期晚于首次阳性日期
    ]  # 结束筛选
    neg = neg.groupby("patient_id", as_index=False)["test_date"].min()  # 取每位患者首次转阴的日期
    neg.rename(columns={"test_date": "first_negative_date"}, inplace=True)  # 把结果列重命名为首次阴性日期

    df = pos.merge(neg, on="patient_id")  # 合并两个日期表，只保留既阳性又转阴的患者
    df["recovery_time"] = (  # 计算康复耗时
        df["first_negative_date"] - df["first_positive_date"]  # 首次阴性日期减去首次阳性日期
    ).dt.days  # 时间差转换成天数

    out = df.merge(patients, on="patient_id")[  # 关联病人信息并挑选需要输出的列
        ["patient_id", "patient_name", "age", "recovery_time"]  # 输出列：患者编号、姓名、年龄、康复时间
    ]  # 结束列选择
    return out.sort_values(by=["recovery_time", "patient_name"]).reset_index(drop=True)  # 按康复时间、姓名升序排序并重置索引
