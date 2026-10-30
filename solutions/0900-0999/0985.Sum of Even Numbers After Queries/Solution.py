# 题目：985. 查询后的偶数和（Sum of Even Numbers After Queries）
# 思路：先算初始偶数和，每个查询先减掉旧值（若为偶数），加上 v 后再加回新值（若为偶数），把当前和追加到答案。
# 时间复杂度：O(n+q)，每个元素和查询各处理一次；空间复杂度：O(q)，答案列表。
class Solution:  # LeetCode 约定的题解类
    def sumEvenAfterQueries(  # nums 是原数组，queries 每项为 [加数, 下标]
        self, nums: List[int], queries: List[List[int]]  # 方法签名第二行：类型标注
    ) -> List[int]:  # 返回值是每次查询后的偶数和列表
        s = sum(x for x in nums if x % 2 == 0)  # 生成式求和得到初始偶数和
        ans = []  # ans 收集每次查询后的结果
        for v, i in queries:  # 依次取出加数 v 与下标 i
            if nums[i] % 2 == 0:  # 旧值是偶数，先从和中减掉
                s -= nums[i]  # 减去旧值
            nums[i] += v  # 把 v 加到 nums[i] 上
            if nums[i] % 2 == 0:  # 新值是偶数，需要重新计入
                s += nums[i]  # 加上新值
            ans.append(s)  # 记录本次查询后的偶数和
        return ans  # 返回全部答案
