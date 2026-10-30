# 3491. 电话号码前缀 / Phone Number Prefix
# 核心思路：把号码按长度升序排序，任何前缀关系中的短串一定在前，逐个号码检查它前面所有更短的号码是否为它的前缀即可。
# 复杂度：时间 O(n log n + n * L)（L 为号码长度），空间 O(1)（不计排序开销）。
class Solution:  # 定义题解类
    def phonePrefix(self, numbers: List[str]) -> bool:  # 主函数：判断是否不存在一个号码是另一个号码的前缀
        numbers.sort(key=len)  # 按长度升序排序，短号码排在前面
        for i, s in enumerate(numbers):  # 依次检查每个号码
            if any(s.startswith(t) for t in numbers[:i]):  # 在它前面所有更短的号码中查找前缀
                return False  # 存在前缀关系，返回 False
        return True  # 所有号码互不为前缀，返回 True
