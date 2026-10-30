# 题目：1057. 校园自行车分配（Campus Bikes）
# 思路：所有「工人-自行车」配对按（距离, 工人下标, 自行车下标）排序，再贪心配对互不冲突的组合。
# 时间复杂度：O(n·m·log(n·m))，排序为主；空间复杂度：O(n·m)，保存全部候选配对。
class Solution:  # LeetCode 约定的题解类
    def assignBikes(  # 返回每个工人分配到的自行车下标
        self, workers: List[List[int]], bikes: List[List[int]]  # workers 与 bikes 都是坐标列表
    ) -> List[int]:  # 返回长度为工人数的答案数组
        n, m = len(workers), len(bikes)  # n 是工人数，m 是自行车数
        arr = []  # 收集所有 (距离, 工人下标, 自行车下标) 三元组
        for i, j in product(range(n), range(m)):  # 笛卡尔积：枚举每一种工人与自行车的组合
            dist = abs(workers[i][0] - bikes[j][0]) + abs(workers[i][1] - bikes[j][1])  # 曼哈顿距离：横向差绝对值 + 纵向差绝对值
            arr.append((dist, i, j))  # 三元组入表，元组排序时按距离→工人→自行车依次比较
        arr.sort()  # 按题目要求的优先级升序排序
        vis1 = [False] * n  # 记录每个工人是否已经分到车
        vis2 = [False] * m  # 记录每辆车是否已经被占用
        ans = [0] * n  # 答案数组，先填 0 占位
        for _, i, j in arr:  # 按优先级从高到低处理每组配对
            if not vis1[i] and not vis2[j]:  # 双方都空闲才可以配对
                vis1[i] = vis2[j] = True  # 同时标记工人与自行车为已使用
                ans[i] = j  # 记录工人 i 分到自行车 j
        return ans  # 返回分配结果
