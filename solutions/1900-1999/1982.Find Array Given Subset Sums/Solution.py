# 题目：1982. 从子集的和还原数组（Find Array Given Subset Sums）
# 思路：把全部子集和整体平移让空集为 0；每轮取剩余最小值当新元素，并从有序表中删掉「含刚确定元素」的那一半和；最后把和等于平移量的子集元素取相反数。
# 时间复杂度：O(n·2^n)，枚举子集求和的代价；空间复杂度：O(2^n)，有序表保存全部子集和。
class Solution:  # LeetCode 约定的题解类
    def recoverArray(self, n: int, sums: List[int]) -> List[int]:  # n：原数组长度；sums：全部 2^n 个子集的和
        m = -min(sums)  # 最小子集和取反，得到把最小值平移到 0 的偏移量
        sl = SortedList(x + m for x in sums)  # SortedList 是有序表，加偏移量后建表，空集对应的和变成 0
        sl.remove(0)  # 删掉 0（空集），剩余最小值就是绝对值最小的那个元素
        ans = [sl[0]]  # 先确定第一个元素：最小的非零子集和
        for i in range(1, n):  # 依次确定第 2 个到第 n 个元素
            for j in range(1 << i):  # 枚举前 i 个已确定元素的 2^i 个子集掩码
                if j >> (i - 1) & 1:  # 只看最高位（第 i-1 位）为 1 的掩码，即子集包含刚确定的元素
                    s = sum(ans[k] for k in range(i) if j >> k & 1)  # 用生成器求该掩码对应的子集和
                    sl.remove(s)  # 从有序表中删掉这一份：未确定的元素会让每个和成对出现，这里只保留另一半
            ans.append(sl[0])  # 删掉一半后，表首元素就是下一个待确定的元素
        for i in range(1 << n):  # 枚举原数组的所有子集，找和等于偏移量 m 的那个
            s = sum(ans[j] for j in range(n) if i >> j & 1)  # 该子集的元素和
            if s == m:  # 平移前该子集和为 0，说明这些元素在原数组中应当取负
                for j in range(n):  # 逐位扫描该子集
                    if i >> j & 1:  # 位为 1 才需要取负
                        ans[j] *= -1  # 原地翻转符号，恢复成原始数组
                break  # 找到即跳出（题目保证解唯一）
        return ans  # 返回还原出的原数组
