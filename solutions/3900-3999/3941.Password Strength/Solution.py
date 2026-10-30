# 3941. 密码强度 / Password Strength
# 核心思路：用集合去重后，对每种不同字符按小写 1 分、大写 2 分、数字 3 分、其他 5 分累加。
# 复杂度：时间 O(n)，空间 O(1)（字符集大小固定）。
class Solution:  # 题解类定义
    def passwordStrength(self, password: str) -> int:  # 主函数：计算密码强度
        st = set(password)  # 转成集合，只保留不同字符
        ans = 0  # 强度总分
        for ch in st:  # 遍历每一种不同字符
            if ch.islower():  # 小写字母
                ans += 1  # 加 1 分
            elif ch.isupper():  # 大写字母
                ans += 2  # 加 2 分
            elif ch.isdigit():  # 数字字符
                ans += 3  # 加 3 分
            else:  # 其余符号字符
                ans += 5  # 加 5 分
        return ans  # 返回总强度
