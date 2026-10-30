# 题目：1104. 二叉树寻路（Path In ZigZag Labelled Binary Tree）
# 思路：先定位 label 所在层，再从下往上把之字形标号镜像成顺序标号并除以 2 得到父节点，从后往前填答案。
# 时间复杂度：O(log label)，层数即路径长度；空间复杂度：O(log label)，答案数组。
class Solution:  # LeetCode 约定的题解类
    def pathInZigZagTree(self, label: int) -> List[int]:  # label 是之字形标号，要求返回根到它的路径
        x = i = 1  # x 是当前层最左端的顺序标号，i 是层号（根为第 1 层）
        while (x << 1) <= label:  # 下一层起点 x * 2 不超过 label，说明 label 在更深的层
            x <<= 1  # 进入下一层
            i += 1  # 层号加一
        ans = [0] * i  # 先按路径长度开数组，之后从后往前填
        while i:  # 从 label 所在层往上走，i 同时是层号
            ans[i - 1] = label  # 当前层的标号放在对应位置（先填最后一位）
            label = ((1 << (i - 1)) + (1 << i) - 1 - label) >> 1  # 先把之字形标号镜像回顺序标号，再除以 2 得到父节点标号
            i -= 1  # 层号减一，继续往上
        return ans  # 返回从根到 label 的路径
