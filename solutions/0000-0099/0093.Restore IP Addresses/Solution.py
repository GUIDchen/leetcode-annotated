# 题目：93. 复原 IP 地址（Restore IP Addresses）
# 思路：回溯切分，每段长度 1~3 且数值不超过 255、不能有前导 0；恰好切满 4 段且用完全部字符时收集答案。
# 时间复杂度：O(3^4 · n)，每段最多 3 种长度、共 4 段，拼接字符串还需 O(n)；空间复杂度：O(4)，递归深度与临时段列表。
class Solution:  # LeetCode 约定的题解类
    def restoreIpAddresses(self, s: str) -> List[str]:  # s 是待切分的数字串，返回所有合法 IPv4 地址
        def check(i: int, j: int) -> int:  # 判断 s[i..j] 这一段是否是合法段（题目原签名的返回类型照抄不改）
            if s[i] == "0" and i != j:  # 长度大于 1 却以 '0' 开头，属于前导 0，不合法
                return False  # 直接否决这一段
            return 0 <= int(s[i : j + 1]) <= 255  # 数值在 0~255 之间才合法

        def dfs(i: int):  # 回溯函数：i 是下一段的起始下标
            if i >= n and len(t) == 4:  # 字符用尽且恰好 4 段，得到一个合法地址
                ans.append(".".join(t))  # 用点号把各段拼成标准 IPv4 形式
                return  # 递归出口，回到上一层
            if i >= n or len(t) >= 4:  # 字符用完却不足 4 段，或已满 4 段还有剩余字符，都非法
                return  # 剪枝返回
            for j in range(i, min(i + 3, n)):  # 枚举本段结尾：长度最多 3 位，且不能越界
                if check(i, j):  # 只有这一段合法才继续往下切
                    t.append(s[i : j + 1])  # 把当前段放进路径
                    dfs(j + 1)  # 从下一段起点继续递归
                    t.pop()  # 撤销这一段，尝试其他长度

        n = len(s)  # 字符串长度，供 dfs 判断出口
        ans = []  # 结果列表：保存所有合法地址
        t = []  # 回溯路径：保存已经切出的各段
        dfs(0)  # 从第 0 个字符开始切分
        return ans  # 返回所有合法地址
