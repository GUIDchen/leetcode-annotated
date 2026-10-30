# 题目：1652. 拆炸弹（Defuse the Bomb）
# 思路：k > 0 时答案是右侧 k 个元素之和，k < 0 时是左侧 |k| 个元素之和，k == 0 时全为 0；用取模实现环形下标。
# 时间复杂度：O(n·|k|)；空间复杂度：O(n)，答案数组。
class Solution:  # LeetCode 约定的题解类
    def decrypt(self, code: List[int], k: int) -> List[int]:  # code 是环形数组，k 表示向右(正)/向左(负)求和个数
        n = len(code)  # 数组长度
        ans = [0] * n  # 答案数组，默认全 0
        if k == 0:  # k == 0 时每个位置都解密为 0
            return ans  # 直接返回全零数组
        for i in range(n):  # 逐位计算答案
            if k > 0:  # k 为正：取当前位置之后 k 个
                for j in range(i + 1, i + k + 1):  # j 从 i+1 走到 i+k，用 j%n 处理环形越界
                    ans[i] += code[j % n]  # 累加右侧元素
            else:  # 否则 k 为负：取当前位置之前 |k| 个
                for j in range(i + k, i):  # j 从 i+k 走到 i-1
                    ans[i] += code[(j + n) % n]  # (j + n) % n 把负下标映射回数组尾部
        return ans  # 返回解密结果
