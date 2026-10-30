# 题目：3058. 没有共同朋友的朋友（Friends With No Mutual Friends）
# 思路：把边表补成双向边，按 user_id2 自连接得到所有 A→B、B→C 的二步路径；凡是一条边 (A, B) 能出现在这种路径的首尾组合里，就说明它有共同朋友，最后用 apply 逐行剔除。
# 时间复杂度：O(E^2)，自连接结果与逐行判断都与边数平方相关；空间复杂度：O(E^2)，自连接中间结果最坏为平方级。
import pandas as pd  # 引入 pandas，用于连接、自连接与布尔索引过滤


def friends_with_no_mutual_friends(friends: pd.DataFrame) -> pd.DataFrame:  # friends：好友关系表（题面保证 user_id1 < user_id2）
    cp = friends.copy()  # 复制一份，避免后续步骤改动传入的原始表
    t = cp[["user_id1", "user_id2"]].copy()  # 先取出需要的两列，作为正向边集合
    t = pd.concat(  # 把正向边与反向边拼在一起，得到无向图的完整边集
        [  # 待拼接的 DataFrame 列表开始
            t,  # 第一项：原有的 (user_id1, user_id2)
            cp[["user_id2", "user_id1"]].rename(  # 第二项：把 user_id2 与 user_id1 对调，构造反向边
                columns={"user_id2": "user_id1", "user_id1": "user_id2"}  # 交换两个列名，使反向边也满足 (起点, 终点) 的列顺序
            ),  # 反向边构造结束
        ]  # 列表结束
    )  # 拼接结束：t 现在包含两个方向的边
    merged = t.merge(t, left_on="user_id2", right_on="user_id2")  # 按中间人 user_id2 自连接，枚举所有 A→B、B→C 的二步路径
    ans = cp[  # 从原始边表里筛掉存在共同朋友的边
        ~cp.apply(  # 对 apply 结果取反：True 表示该边没有共同朋友、需要保留
            lambda x: (x["user_id1"], x["user_id2"])  # 当前这一行的边 (user_id1, user_id2)
            in zip(merged["user_id1_x"], merged["user_id1_y"]),  # 判断该边是否出现在二步路径的 (起点, 终点) 组合里
            axis=1,  # 按行方向（axis=1）逐条边判断
        )  # 逐行判断结束
    ]  # 布尔索引结束，ans 即没有共同朋友的所有边
    return ans.sort_values(by=["user_id1", "user_id2"])  # 按题目要求升序排序后返回
