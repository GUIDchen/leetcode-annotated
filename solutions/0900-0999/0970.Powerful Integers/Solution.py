# 题目：970. 强整数（Powerful Integers）
# 思路：双重循环枚举 x 的幂 a 与 y 的幂 b，把满足 a + b <= bound 的和放入集合去重。
# 时间复杂度：O(log_x bound * log_y bound)，两重幂次枚举；空间复杂度：O(答案个数)，集合存储去重结果。
class Solution:  # LeetCode 约定的题解类
    def powerfulIntegers(self, x: int, y: int, bound: int) -> List[int]:  # x、y 是底数，bound 是上界，返回所有不超过 bound 的强整数
        ans = set()  # 集合：自动去重，最后转成列表
        a = 1  # a 从 x 的 0 次幂 1 开始
        while a <= bound:  # 只要 a 不超过上界就继续枚举
            b = 1  # 每轮把 b 重置为 y 的 0 次幂 1
            while a + b <= bound:  # 保证 a + b 不超过上界
                ans.add(a + b)  # 把强整数 a + b 加入集合去重
                b *= y  # 幂次递增
                if y == 1:  # y == 1 时 b 恒为 1，继续循环会死循环，必须跳出
                    break  # 跳出内层循环
            if x == 1:  # x == 1 时 a 恒为 1，同样要跳出外层避免死循环
                break  # 跳出外层循环
            a *= x  # 幂次递增
        return list(ans)  # 集合转成列表返回（顺序不作要求）
