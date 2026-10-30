# 题目：2468. 根据限制分割消息（Split Message Based on Limit）
# 核心思路：枚举段数 k，用前缀量 sa（编号位数和）、sb（编号位数×k）、sc（标记里 3 个符号×k）算标记总开销，若 limit*k 扣掉开销仍能装下全文就按顺序切分并拼上 <j/k> 标记；取最小的可行 k。
# 时间复杂度：O(n^2)，外层枚举 k、内层切分都不超过 n；空间复杂度：O(n)，存放结果字符串。
class Solution:  # LeetCode 约定的题解类
    def splitMessage(self, message: str, limit: int) -> List[str]:  # 返回按 limit 切分并带编号标记的字符串列表
        n = len(message)  # 原文字符数
        sa = 0  # sa：编号 1..k 的十进制位数之和，随 k 递增累加
        for k in range(1, n + 1):  # 枚举段数 k，最多 n 段（每段至少一个字符）
            sa += len(str(k))  # 把 k 的位数累加进 sa
            sb = len(str(k)) * k  # sb：k 个编号各自的位数占用（都按 k 的位数估算）
            sc = 3 * k  # sc：每个标记里的 '<'、'/'、'>' 共 3 个字符
            if limit * k - (sa + sb + sc) >= n:  # 扣除标记开销后，剩余容量是否够装全文
                ans = []  # 存放本方案的切分结果
                i = 0  # i：已经取走的原文字符数
                for j in range(1, k + 1):  # 逐段生成第 j 段
                    tail = f'<{j}/{k}>'  # 构造编号标记，形如 <j/k>
                    t = message[i : i + limit - len(tail)] + tail  # 取本段能放下的原文前缀，拼上标记
                    ans.append(t)  # 加入结果列表
                    i += limit - len(tail)  # 指针前移，跳过本段已消费的字符
                return ans  # 第一个可行的 k 就是最小段数，直接返回
        return []  # 没有任何 k 可行，返回空列表
