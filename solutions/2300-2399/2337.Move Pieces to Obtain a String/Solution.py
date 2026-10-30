# 题目：2337. 移动片段得到字符串（Move Pieces to Obtain a String）
# 核心思路：去掉空位 '_' 后两边非空字符序列必须相同；再比较下标方向——'L' 只能左移（初始下标不小于目标下标），'R' 只能右移（初始下标不大于目标下标）。
# 时间复杂度：O(n)，两次列表推导加一次 zip 比对；空间复杂度：O(n)，存放非空字符及其下标。
class Solution:  # LeetCode 约定的题解类
    def canChange(self, start: str, target: str) -> bool:  # start：初始字符串；target：目标字符串；返回能否变换得到 target
        a = [(v, i) for i, v in enumerate(start) if v != '_']  # start 中所有非空位字符及其下标，顺序与出现顺序一致
        b = [(v, i) for i, v in enumerate(target) if v != '_']  # target 中所有非空位字符及其下标
        if len(a) != len(b):  # 非空字符数量不同，片段无法一一对应
            return False  # 直接返回不可能
        for (c, i), (d, j) in zip(a, b):  # 按顺序配对比较，c/i 来自 start，d/j 来自 target
            if c != d:  # 字符种类不同（'L' 与 'R' 互换）则不可能
                return False  # 返回不可能
            if c == 'L' and i < j:  # 'L' 只能向左移动，初始下标必须不小于目标下标
                return False  # 违反则不可能
            if c == 'R' and i > j:  # 'R' 只能向右移动，初始下标必须不大于目标下标
                return False  # 违反则不可能
        return True  # 全部约束满足，可以变换成功
